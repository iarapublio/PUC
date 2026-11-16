# Case OrbitShop: análise de cancelamento e qualidade dos dados

Autora: Iara

Este repositório reproduz os números do memo (`Memo_OrbitShop.docx`). Todo número citado lá sai do script `orbitshop.py`.

## Como rodar

1. Coloque `Base_Dados_OrbitShop_v3.xlsx` na mesma pasta do script.
2. Instale as dependências: `pip install pandas openpyxl matplotlib` (pandas 2.2 ou mais novo).
3. Rode: `python orbitshop.py`

O script imprime as análises no terminal e cria a pasta `saidas/` com tabelas em CSV (Q2 a Q7) e dois gráficos (`q2_status.png` e `q5_mensal.png`).

## O que o script faz

| Seção | O que calcula |
|---|---|
| Auditoria | Nulos em `valor_total` e `desconto_aplicado`, e teste de como `preco_praticado` é formado |
| Conflito | Cancelamento por ano, semestre e trimestre, em contagem e em taxa, com e sem devolvidos |
| Q2 | Pedidos por status (tabela e gráfico) |
| Q3 | Receita e volume por categoria, só pedidos não cancelados |
| Q4 | Cancelamento e ticket médio por canal de aquisição |
| Q5 | Pedidos por mês, meses de pico e tickets abertos |
| Q6 | `valor_total` do pedido contra a soma dos itens |
| Q7 | Fornecedores (nota e tickets) e tickets por mês do pedido |
| Q8 (apoio) | Cancelamentos em excesso no canal paid_search e valor aproximado |

As Q1 e Q9 e a recomendação do Q8 são julgamento e estão no memo, não no código.

## Decisões sobre os dados

- **Receita do item** = `quantidade * preco_praticado`. O `preco_praticado` já vem com desconto (bate com `preco_unitario * (1 - desconto)` em ~99% das linhas com desconto preenchido), então não se aplica o desconto de novo. Isso também dispensa preencher os 301 descontos nulos.
- **`valor_total` nulo (79 pedidos):** ficam de fora das comparações de valor (Q4 e Q6) e continuam nas contagens de pedidos.
- **Q6:** `valor_total` e soma dos itens não batem em nenhum pedido. Os itens somam cerca de 4,6x o `valor_total` e a correlação por pedido é ~0. Para o conselho uso o `valor_total`, porque só ele reproduz o "B2B vale ~6x o B2C" citado no case (6,2x; pela soma dos itens dá 1,0x). Não sei qual dos dois está tecnicamente errado, e isso entra na lista de pedidos ao time de dados.
- **Cancelamento:** "cancelado" é o status `cancelado`. Mostro também a versão que inclui `devolvido`, pois a definição muda a conclusão.

## Uso de IA 

Usei o Claude (Anthropic) em quatro momentos:

1. **Entender o case:** o que cada pergunta pedia e o que é um memo e um notebook.
2. **Tratar o Excel em script:** carregar as abas, converter datas, juntar tabelas pelas chaves (`pedido_id`, `cliente_id`, `produto_id`).
3. **Corrigir o meu código:** detalhado abaixo.
4. **Validar as perguntas da Q1:** eu as criei e perguntei à IA se eram pertinentes.
5. **Compilação das informações do README**

### Correções no meu código (antes e depois)

**1. Desconto aplicado duas vezes (erro mais sério)**

Antes:
```python
itens["receita_bruta"] = itens["quantidade"] * itens["preco_praticado"]
itens["receita_liquida"] = itens["receita_bruta"] * (1 - itens["desconto_limpo"])
```
Depois:
```python
itens["receita"] = itens["quantidade"] * itens["preco_praticado"]
```
Efeito: a receita estava subestimada em ~6-7% (Eletrônicos: R$ 25,6M no cálculo antigo, R$ 27,3M no correto). O ranking das categorias não mudou, mas os valores da Q6 mudaram.

**2. Números escritos na mão**

Antes:
```python
print(f"Soma Pedidos.valor_total (14.921 válidos): R$ {rec_valid['valor_total'].sum():,.2f}")
```
Depois:
```python
n = len(rec)
print(f"Pedidos comparados (valor_total preenchido): {n}")
```

**3. Conclusão escrita antes do resultado**

Antes: o título da tabela por trimestre já afirmava que ela "explica a visão 18% -> 16% do CFO".
Depois: tabelas por ano, semestre e trimestre, em contagem e em taxa, com e sem devolvidos, sem conclusão pré-definida. O memo diz que não consegui reproduzir os dois números exatos.

**4. Ticket médio por canal** incluía pedidos cancelados. Agora o script mostra com e sem cancelados.

**5. Cores do gráfico da Q2** dependiam da ordem dos status. Agora vêm de um dicionário por nome do status.

**6. Acrescentado:** gráfico mensal (Q5), tickets por 100 pedidos, teste de qual valor reproduz o "B2B ≈ 6x B2C" (Q6), apoio à Q8 e saída das tabelas em CSV.
