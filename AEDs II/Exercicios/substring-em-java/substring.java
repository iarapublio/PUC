import java.util.Scanner;

public class Substring {

	/*
	 * FUNÃ‡ÃƒO VERIFICA FIM
	 */
	public static boolean verificaFim(String str, String chave) {
		boolean fim = false;

		if (str.length() == chave.length()) {
			fim = true;

			for (int i=0; i < str.length(); i++) {
				if (str.charAt(i) != chave.charAt(i)) {
					fim = false;
					i = str.length();
				}
			}
		}

		return fim;
	}

	/*
	 * FUNÃ‡ÃƒO VERIFICA FIM BASE
	 */
	public static boolean verificaFim(String str) {
		return verificaFim(str, "FIM");
	}

	/*
	 * FUNÃ‡ÃƒO SUBSTRING MAIS LONGA
	 */
	public static int substringLong(String str) {
		int maior = 0;

		// comeÃ§a o laÃ§o Ã  partir do primeiro caractere da string e vai atÃ© o tamanho da string
		for (int i=0; i < str.length(); i++) {
			int cont = 0;
			
			// laÃ§o j em funÃ§Ã£o de i e vai atÃ© o tamanho da string
			for (int j=i; j < str.length(); j++) {
				boolean rep = false;

				// laÃ§o k em funÃ§Ã£o de i e vai atÃ© o tamanho j
				for (int k = i; k < j; k++) {

					// se for o caracter se repetir entra no if
					if (str.charAt(k) == str.charAt(j)) {
						rep = true;
						k = j;
					}
				}

				// se for repetido, o laÃ§o j termina 
				if (rep) {
					 j = str.length();
				}
				// se nÃ£o, o contador aumenta e o laÃ§o j continua
				else {
					cont++; 

					if (cont > maior) {
						maior = cont;
					}
				}
			}
		}

		return maior;
	}

	/*
	 * FUNÃ‡ÃƒO MAIN
	 */
	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		String str = sc.next();

		while (!verificaFim(str)) {
			System.out.println(substringLong(str));
			str = sc.next();
		}

		sc.close();
	}

}
