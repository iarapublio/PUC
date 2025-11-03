//main java
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


//main c

int main() {
	setlocale(LC_ALL, "");
	wchar_t str[100];
	fgetws(str, sizeof(str), stdin);
	str[wcscspn(str, L"\n")] = L'\0';
	

	while (wcscmp(str, L"FIM")) { //strcmp pra widechar
		if (ehPalindromo(str)) {
			wprintf(L"SIM\n");
		}
		else {
			wprintf(L"NAO\n");
		}
		fgetws(str, sizeof(str), stdin);
		str[wcscspn(str, L"\n")] = L'\0';
	}

	return 0; 
