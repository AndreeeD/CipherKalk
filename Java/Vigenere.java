
public class Vigenere extends Frase implements X{
	private String Key; //Chiave
    private char[] Risultato = new char[200]; //Testo risultante
    private char[] CipherString = new char[200]; //Stringa di cifratura
    private int[] S = new int[200]; //Vettore contenente il numero di spostamenti per ogni lettera
    
    /* Controllo se la chiave inserita rispetta i vincoli imposti (ovvero se e' costituita da soli caratteri alfabetici) e in
     * caso affermativo trasformo ogni lettera da minuscolo a maiuscolo */
	public Vigenere(String phrase, String key) throws Errori{
		super(phrase);
		String temp = key.toUpperCase();
		for(int i=0;i<key.length();i++) {
			if(temp.charAt(i)<'A' || temp.charAt(i)>'Z') {
				this.Key = "";
				throw new Errori("La chiave deve contenere solo caratteri alfabetici senza spazi!");
			}
		}
		this.Key = temp;
	}
	/* Ritorno la stringa di cifratura */
	public char[] getCipherString() {
		return CipherString;
	}
	/* Ritorno il testo risultante */
	public char[] getRisultato() {
		return Risultato;
	}
	/* Cifro il testo in chiaro */
	public void codifica() {
        buildStringVig();
        String f = getPhrase();
        for(int i=0;i<f.length();i++){
            if(S[i] != 0) Risultato[i] = getLettera(f.charAt(i),S[i]);
            else Risultato[i] = f.charAt(i);
        }
    }
	/* Decifro il testo cifrato */
	public void codificaRev() {
        buildStringVig();
        String f = getPhrase();
        for(int i=0;i<f.length();i++){
            if(S[i] != 0) Risultato[i] = getLetteraRev(f.charAt(i),S[i]);
            else Risultato[i] = f.charAt(i);
        }
    }
	/* Costruisco la stringa di cifratura e l'array che conterra' il numero di spostamenti da effettuare per ciascuna lettera
	   del testo inserito */
	public void buildStringVig(){
        String f = getPhrase();
        char[] Lett = getAlfa();
        for(int i=0,j=0;i<f.length();i++){
            if(f.charAt(i)!=' '){
                if(j>=Key.length()) j=0;
                CipherString[i] = Key.charAt(j);
                j++;
            }
            else CipherString[i] = ' ';
        }
        for(int i=0;i<f.length();i++){
            if(CipherString[i] != ' '){
                for(int j=0;j<26;j++){
                    if(CipherString[i] == Lett[j]) S[i] = j;
                }
            }
            else S[i] = 0;
        }
    }
	/* Trovo e ritorno la lettera che si trova 'pos' posizioni prima rispetto a 'c' */
	public char getLetteraRev(char c,int pos) {
        char l;
        char[] alfa = getAlfa();
        int temp = 0;
        for(int i=0;i<26;i++){
            if(alfa[i]==c){
                temp = i;
                break;
            }
        }
        if(temp >= pos)
            l = alfa[temp-pos];
        else{
            pos = 26 + (temp-pos);
            l = alfa[pos];
        }
        return l;
    }
	/* Stampo la frase risultante */
    public void stampa() {
    	System.out.println("Frase risultante: ");
        for(int i=0;i<getPhrase().length();++i) System.out.print(Risultato[i]);
    }
}
