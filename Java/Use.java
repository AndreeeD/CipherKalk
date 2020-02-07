
public class Use {

	public static void main(String[] args) {
		
		//Esempi di cifratura
		System.out.println("----------CIFRATURA----------");
		String phrase = "Programmazione ad oggetti";
		System.out.println("Testo in chiaro: " + phrase);
		
		//Cifrario a sostituzione
		System.out.println("\nSOSTITUZIONE");
		System.out.println("Numero spostamenti: " + 4);
		X x;
		try {
			x = new Sostituzione(phrase,4);
			x.codifica();
			x.stampa();
		}catch(Errori e) { System.out.println(e.getC()); } 
		System.out.println("\n");
		
		//Cifrario di Vigenere
		System.out.println("VIGENERE");
		String key = "ab";
		System.out.println("Chiave: " + key);
		char[] CipherString;
		Vigenere vig;
		try {
			x = new Vigenere(phrase,key);
			x.codifica();
			x.stampa();
			System.out.println("\nStringa di cifratura: ");
			vig = (Vigenere) x; //Downcast X -> Vigenere
			CipherString = vig.getCipherString();
			for(int i=0;i<vig.getPhrase().length();++i) System.out.print(CipherString[i]);
		}catch(Errori e) { System.out.println(e.getC()); }
		System.out.println("\n");
		
		//Cifrario di Vernam
		System.out.println("VERNAM");
		key = "abababababababababababa";
		System.out.println("Chiave: " + key);
		Vernam ve;
		try {
			x = new Vernam(phrase,key);
			x.codifica();
			x.stampa();
			ve = (Vernam) x; //Downcast X -> Vernam
			System.out.println("\nStringa di cifratura: ");
			CipherString = ve.getCipherString();
			for(int i=0;i<ve.getPhrase().length();++i) System.out.print(CipherString[i]);
		}catch(Errori e) { System.out.println(e.getC()); }
		System.out.println("\n");
		
		//Esempi di decifratura
		System.out.println("----------DECIFRATURA----------");
		phrase = "PSohrBMnAAipnf AE OHGftUI";
		System.out.println("Testo cifrato: " + phrase);
		
		//Cifrario di Vigenere
		System.out.println("\nVIGENERE");
		key = "ab";
		System.out.println("Chiave: " + key);
		try {
			vig = new Vigenere(phrase,key);
			vig.codificaRev();
			vig.stampa();
			System.out.println("\nStringa di cifratura: ");
			CipherString = vig.getCipherString();
			for(int i=0;i<vig.getPhrase().length();++i) System.out.print(CipherString[i]);
		}catch(Errori e) { System.out.println(e.getC()); }
		System.out.println("\n");
		
		//Cifrario di Vernam
		System.out.println("VERNAM");
		key = "abababababababababababa";
		System.out.println("Chiave: " + key);
		try {
			ve = new Vernam(phrase,key);
			ve.codificaRev();
			ve.stampa();
			System.out.println("\nStringa di cifratura: ");
			CipherString = ve.getCipherString();
			for(int i=0;i<ve.getPhrase().length();++i) System.out.print(CipherString[i]);
		}catch(Errori e) { System.out.println(e.getC()); }
		System.out.println("\n");

		//Possibili errori in input dell'utente e conseguenze
		System.out.println("----------ERRORI DI INPUT----------");
		
		//Frase che contiene caratteri diversi da quelli alfabetici e spazi
		phrase = "Progr4mmazione ad 0ggetti"; 
		System.out.println("Testo in chiaro: " + phrase);
		
		System.out.println("\nSOSTITUZIONE");
		System.out.println("N spostamenti: " + 4);
		Sostituzione s;
		try {
			x = new Sostituzione(phrase,4);
			s = (Sostituzione) x; //Downcast X -> Sostituzione
			x.codifica();
			x.stampa();
		}catch(Errori e) { System.out.println(e.getC()); }
		
		//Frase che contiene solo spazi
		phrase = "    ";
		System.out.println("\nTesto in chiaro: '" + phrase + "'");
		System.out.println("\nSOSTITUZIONE");
		System.out.println("N spostamenti: " + 4);
		try {
			x = new Sostituzione(phrase,4);
			s = (Sostituzione) x; //Downcast X -> Sostituzione
			x.codifica();
			x.stampa();
		}catch(Errori e) { System.out.println(e.getC()); }
		
		phrase = "Programmazione ad oggetti";
		System.out.println("\nTesto in chiaro: " + phrase);
		System.out.println("\nSOSTITUZIONE");
		//Numero di spostamenti scelto >26 o <0
		System.out.println("Numero spostamenti scelto: " + 27);
		try {
			x = new Sostituzione(phrase,27);
			s = (Sostituzione) x; //Downcast X -> Sostituzione
			s.codifica();
			s.stampa();
		}catch(Errori e) { System.out.println(e.getC()); }
		
		System.out.println("\nVIGENERE");
		//Chiave che contiene spazi
		key = "a b";
		System.out.println("Chiave inserita: " + key);
		try {
			x = new Vigenere(phrase,key);
			vig = (Vigenere) x; //Downcast X -> Vigenere
			x.codifica();
			x.stampa();
			System.out.println("\nStringa di cifratura: ");
			CipherString = vig.getCipherString();
			for(int i=0;i<vig.getPhrase().length();++i) System.out.print(CipherString[i]);
		}catch(Errori e) { System.out.println(e.getC()); }
		
		System.out.println("\nVERNAM");
		//Chiave con lunghezza diversa da quella della frase inserita
		key = "abababababaabababababa";
		System.out.println("Chiave inserita: " + key);
		try {
			x = new Vernam(phrase,key);
			ve = (Vernam) x; //Downcast X -> Vernam
			x.codifica();
			x.stampa();
			System.out.println("\nStringa di cifratura: ");
			CipherString = ve.getCipherString();
			for(int i=0;i<ve.getPhrase().length();++i) System.out.print(CipherString[i]);
		}catch(Errori e) { System.out.println(e.getC()); }
		
		System.out.println("\nVERNAM");
		//Chiave che contiene caratteri diversi da quelli alfabetici
		key = "abababa0abaabababababab";
		System.out.println("Chiave inserita: " + key);
		try {
			x = new Vernam(phrase,key);
			ve = (Vernam) x; //Downcast X -> Vernam
			x.codifica();
			x.stampa();
			System.out.println("\nStringa di cifratura: ");
			CipherString = ve.getCipherString();
			for(int i=0;i<ve.getPhrase().length();++i) System.out.print(CipherString[i]);
		}catch(Errori e) { System.out.println(e.getC()); }
	}
}
