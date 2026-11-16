import os
import pandas as pd
import matplotlib.pyplot as plt

ARQUIVO = "Base_Dados_OrbitShop_v3.xlsx"
SAIDA = "saidas"
os.makedirs(SAIDA, exist_ok=True)

def titulo(t):
    print("\n" + "=" * 70 + f"\n{t}\n" + "=" * 70)

# ---------------------------------------------------------------- 1. CARGA
clientes   = pd.read_excel(ARQUIVO, sheet_name="Clientes")
produtos   = pd.read_excel(ARQUIVO, sheet_name="Produtos")
pedidos    = pd.read_excel(ARQUIVO, sheet_name="Pedidos")
itens      = pd.read_excel(ARQUIVO, sheet_name="Itens_Pedido")
tickets    = pd.read_excel(ARQUIVO, sheet_name="Tickets_Suporte")
avaliacoes = pd.read_excel(ARQUIVO, sheet_name="Avaliacoes")

pedidos["data_pedido"] = pd.to_datetime(pedidos["data_pedido"])
pedidos["ano"] = pedidos["data_pedido"].dt.year
pedidos["semestre"] = pedidos["ano"].astype(str) + "-S" + ((pedidos["data_pedido"].dt.month > 6) + 1).astype(str)
pedidos["trimestre"] = pedidos["data_pedido"].dt.to_period("Q").astype(str)
pedidos["mes"] = pedidos["data_pedido"].dt.to_period("M")
pedidos["cancelado"] = pedidos["status"] == "cancelado"
pedidos["cancel_ou_dev"] = pedidos["status"].isin(["cancelado", "devolvido"])

tickets["data_abertura"] = pd.to_datetime(tickets["data_abertura"])
tickets["mes"] = tickets["data_abertura"].dt.to_period("M")

# ------------------------------------------------------------ 2. AUDITORIA
titulo("AUDITORIA DA BASE")
print("Pedidos com valor_total nulo:", pedidos["valor_total"].isna().sum())
print("Itens com desconto_aplicado nulo:", itens["desconto_aplicado"].isna().sum())

# preco_praticado JÁ tem o desconto embutido: preco_praticado = preco_unitario * (1 - desconto)
chk = itens.merge(produtos[["id", "preco_unitario"]], left_on="produto_id", right_on="id", suffixes=("", "_p"))
chk = chk.dropna(subset=["desconto_aplicado"])
ok = ((chk["preco_praticado"] - chk["preco_unitario"] * (1 - chk["desconto_aplicado"])).abs() < 0.02 * chk["preco_unitario"]).mean()
print(f"Linhas em que preco_praticado = preco_unitario*(1-desconto): {ok:.1%}")
print("=> não aplicar o desconto de novo. Receita do item = quantidade * preco_praticado")

itens["receita"] = itens["quantidade"] * itens["preco_praticado"]

# ----------------------------------------- 3. CONFLITO CAMILA x ROGÉRIO
titulo("CONFLITO: cancelamento por diferentes definições")
def resumo(g):
    return pd.Series({
        "pedidos": len(g),
        "cancelados": g["cancelado"].sum(),
        "taxa_canc_%": g["cancelado"].mean() * 100,
        "taxa_canc+dev_%": g["cancel_ou_dev"].mean() * 100,
    })

for col in ["ano", "semestre", "trimestre"]:
    t = pedidos.groupby(col).apply(resumo, include_groups=False).round(2)
    print(f"\nPor {col}:\n", t)

a = pedidos.groupby("ano").apply(resumo, include_groups=False)
var_cont = (a.loc[2024, "cancelados"] / a.loc[2023, "cancelados"] - 1) * 100
var_taxa = (a.loc[2024, "taxa_canc_%"] / a.loc[2023, "taxa_canc_%"] - 1) * 100
print(f"\nVariação 2024 vs 2023 -> contagem de cancelados: {var_cont:+.1f}% | taxa: {var_taxa:+.1f}%")

# ------------------------------------------------------------------- Q2
titulo("Q2: pedidos por status")
q2 = pedidos["status"].value_counts().to_frame("qtd")
q2["%"] = (q2["qtd"] / q2["qtd"].sum() * 100).round(2)
print(q2)
q2.to_csv(f"{SAIDA}/q2_status.csv")

cores = {"entregue": "#2E86AB", "cancelado": "#E63946", "em_transito": "#F4A261", "devolvido": "#6C757D"}
fig, ax = plt.subplots(figsize=(7, 4))
bars = ax.bar(q2.index, q2["qtd"], color=[cores.get(s, "#999999") for s in q2.index])
ax.set_title(f"Pedidos por status (N = {len(pedidos):,})".replace(",", "."), fontweight="bold")
ax.set_ylabel("Pedidos")
ax.set_ylim(0, q2["qtd"].max() * 1.2)
ax.spines[["top", "right"]].set_visible(False)
for b, p in zip(bars, q2["%"]):
    ax.text(b.get_x() + b.get_width() / 2, b.get_height() + 100,
            f"{int(b.get_height()):,}\n({p:.1f}%)".replace(",", "."), ha="center", fontsize=9)
plt.tight_layout(); plt.savefig(f"{SAIDA}/q2_status.png", dpi=150); plt.close()

# ------------------------------------------------------------------- Q3
titulo("Q3: categorias por receita x volume (pedidos não cancelados)")
ip = itens.merge(produtos, left_on="produto_id", right_on="id", suffixes=("", "_prod"))
ip = ip.merge(pedidos[["id", "status", "mes"]], left_on="pedido_id", right_on="id", suffixes=("", "_ped"))
validos = ip[ip["status"] != "cancelado"]
q3 = validos.groupby("categoria").agg(receita=("receita", "sum"), unidades=("quantidade", "sum"))
q3["preco_medio_unid"] = (q3["receita"] / q3["unidades"]).round(2)
q3["rank_receita"] = q3["receita"].rank(ascending=False).astype(int)
q3["rank_volume"] = q3["unidades"].rank(ascending=False).astype(int)
q3 = q3.sort_values("receita", ascending=False)
print(q3.round(0))
q3.to_csv(f"{SAIDA}/q3_categorias.csv")

# ------------------------------------------------------------------- Q4
titulo("Q4: canal de aquisição x cancelamento e ticket médio")
pc = pedidos.merge(clientes, left_on="cliente_id", right_on="id", suffixes=("", "_cli"))
q4 = pc.groupby("canal_aquisicao").agg(
    pedidos=("id", "count"),
    taxa_canc=("cancelado", "mean"),
    pct_b2b=("segmento", lambda x: (x == "B2B").mean()),
)
q4["taxa_canc"] *= 100
q4["pct_b2b"] *= 100
q4["ticket_medio_todos"] = pc.groupby("canal_aquisicao")["valor_total"].mean()
q4["ticket_medio_sem_canc"] = pc[~pc["cancelado"]].groupby("canal_aquisicao")["valor_total"].mean()
print(q4.round(2))
q4.to_csv(f"{SAIDA}/q4_canal.csv")

# ------------------------------------------------------------------- Q5
titulo("Q5: volume mensal de pedidos")
mensal = pedidos.groupby("mes").size().rename("pedidos").to_frame()
mensal["ano"] = mensal.index.year
mensal["x_mediana_do_ano"] = (mensal["pedidos"] / mensal.groupby("ano")["pedidos"].transform("median")).round(2)
mensal["tickets_abertos"] = tickets.groupby("mes").size()
print(mensal)
print("\nMeses com volume > 1,5x a mediana do ano:")
print(mensal[mensal["x_mediana_do_ano"] > 1.5])
mensal.to_csv(f"{SAIDA}/q5_mensal.csv")

fig, ax = plt.subplots(figsize=(9, 4))
ax.plot(mensal.index.astype(str), mensal["pedidos"], marker="o", color="#2E86AB")
ax.set_title("Pedidos por mês", fontweight="bold")
ax.set_xticks(range(0, len(mensal), 3))
ax.set_xticklabels(mensal.index.astype(str)[::3], rotation=45)
ax.spines[["top", "right"]].set_visible(False)
plt.tight_layout(); plt.savefig(f"{SAIDA}/q5_mensal.png", dpi=150); plt.close()

# ------------------------------------------------------------------- Q6
titulo("Q6: valor_total do pedido x soma dos itens")
soma = itens.groupby("pedido_id")["receita"].sum().rename("soma_itens")
rec = pedidos.merge(soma, left_on="id", right_on="pedido_id", how="left")
rec = rec.dropna(subset=["valor_total"]).copy()
rec["diferenca"] = rec["valor_total"] - rec["soma_itens"]
n = len(rec)
print(f"Pedidos comparados (valor_total preenchido): {n}")
print(f"Pedidos em que bate (dif < R$0,01): {(rec['diferenca'].abs() < 0.01).sum()}")
print(f"Soma valor_total:  R$ {rec['valor_total'].sum():,.2f}")
print(f"Soma dos itens:    R$ {rec['soma_itens'].sum():,.2f}")
print(f"Razão itens/valor_total: {rec['soma_itens'].sum() / rec['valor_total'].sum():.2f}x")
print(f"Correlação por pedido: {rec['valor_total'].corr(rec['soma_itens']):.3f}")
print(f"Pedidos em que itens > valor_total: {(rec['diferenca'] < 0).mean():.1%}")

b = pc.assign(vt=pc["valor_total"]).groupby("segmento")["vt"].mean()
print(f"\nTicket B2B / B2C pelo valor_total: {b['B2B'] / b['B2C']:.1f}x (a CEO diz ~6x)")
pi = itens.merge(clientes.merge(pedidos[["id", "cliente_id"]], left_on="id", right_on="cliente_id",
                suffixes=("", "_ped"))[["id_ped", "segmento"]].rename(columns={"id_ped": "pedido_id"}), on="pedido_id")
bi = pi.groupby(["pedido_id", "segmento"])["receita"].sum().groupby("segmento").mean()
print(f"Ticket B2B / B2C pela soma dos itens: {bi['B2B'] / bi['B2C']:.1f}x")

# ------------------------------------------------------------------- Q7
titulo("Q7: fornecedores, avaliações e tickets")
av = avaliacoes.merge(produtos, left_on="produto_id", right_on="id", suffixes=("", "_p"))
q7 = av.groupby("fornecedor").agg(
    avaliacoes=("id", "count"),
    nota_media=("nota", "mean"),
    pct_notas_1_2=("nota", lambda x: (x <= 2).mean() * 100),
)
pf = ip[["pedido_id", "fornecedor"]].drop_duplicates()
pf["teve_ticket"] = pf["pedido_id"].isin(tickets["pedido_id"])
q7["pct_pedidos_com_ticket"] = pf.groupby("fornecedor")["teve_ticket"].mean() * 100
q7 = q7.sort_values("nota_media")
print(q7.round(2))
q7.to_csv(f"{SAIDA}/q7_fornecedores.csv")

# Tickets: o pico acompanha fornecedor ou volume de pedidos?
print("\nTickets por mês (e % do volume de pedidos):")
tk = tickets.groupby("mes").size().to_frame("tickets")
tk["pedidos"] = pedidos.groupby("mes").size()
tk["tickets_por_100_pedidos"] = (tk["tickets"] / tk["pedidos"] * 100).round(1)
print(tk)

# Os tickets abrem depois do pedido. Contando pelo MÊS DO PEDIDO, o pico de nov/dez some?
tm = tickets.merge(pedidos[["id", "data_pedido"]], left_on="pedido_id", right_on="id", suffixes=("", "_ped"))
tm["mes_pedido"] = tm["data_pedido"].dt.to_period("M")
tm["mes_ticket"] = tm["data_abertura"].dt.to_period("M")
tm["dias_ate_ticket"] = (tm["data_abertura"] - tm["data_pedido"]).dt.days
print("\nDias entre pedido e abertura do ticket:")
print(tm["dias_ate_ticket"].describe().round(1))
por_mes_pedido = (tm.groupby("mes_pedido").size() / pedidos.groupby("mes").size() * 100).round(1)
print("\nTickets por 100 pedidos, contando pelo mês do pedido:")
print(por_mes_pedido.to_string())
print("\nTickets abertos em dez/2023, por mês do pedido de origem:")
print(tm[tm["mes_ticket"] == "2023-12"]["mes_pedido"].value_counts().sort_index())

# ------------------------------------------------------------------- Q8 (apoio)
titulo("Q8 (apoio): custo do canal paid_search")
base = pc[pc["canal_aquisicao"] != "paid_search"]["cancelado"].mean()
ps = pc[pc["canal_aquisicao"] == "paid_search"]
excesso = ps["cancelado"].sum() - base * len(ps)
val_med = pc[pc["cancelado"]]["valor_total"].mean()
print(f"Taxa de cancelamento nos outros canais: {base:.1%}")
print(f"Taxa em paid_search: {ps['cancelado'].mean():.1%}")
print(f"Cancelamentos em excesso no paid_search: {excesso:.0f} pedidos")
print(f"Valor médio de pedido cancelado: R$ {val_med:,.2f} -> ~R$ {excesso * val_med:,.0f} em valor")
