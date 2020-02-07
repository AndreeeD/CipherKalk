
public class Vernam extends Frase implements X{
	private String Key; //Chiave
    private int[] S = new int[200]; //array per numero di spostamenti
    private char[] Risultato = new char[200]; //Testo risultante
    private char[] CipherString = new char[200]; //Stringa di cifratura

    /* Controllo se la chiave inserita rispetta i vincoli imposti (ovvero se e' costituita da soli caratteri alfabetici ed ha una
     * lunghezza uguale a quella del testo inserito) e in caso affermativo trasformo ogni lettera da minuscolo a maiuscolo */
	public Vernam(String phrase, String Key) throws Errori{
		super(phrase);
		int nSpazi=0;
        for(int i=0;i<phrase.length();i++)
            if(phrase.charAt(i) == ' ') nSpazi++;
        if(Key.length() != phrase.length()-nSpazi){
            this.Key = "";
            throw new Errori("Frase e chiave hanno lunghezza diversa!");
        }
        else{
        	String temp = Key.toUpperCase();
    		for(int i=0;i<Key.length();i++) {
    			if(temp.charAt(i)<'A' || temp.charAt(i)>'Z') {
    				this.Key = "";
    				throw new Errori("La chiave deve contenere solo caratteri alfabetici senza spazi!");
    			}
    		}
        }
        this.Key = Key.toUpperCase();
	}
	/* Ritorno il testo risultante */
	public char[] getRisultato() {
		return Risultato;
	}
	/* Ritorno la stringa di cifratura */
	public char[] getCipherString() {
		return CipherString;
	}
	/* Cifro il testo in chiaro */
	public void codifica() {
        buildStringVe();
        String f = getPhrase();
        for(int i=0,j=0;i<f.length();i++){
            if(f.charAt(i)==' ') {Risultato[i] = ' '; }
            else{
                Risultato[i] = getLettera(f.charAt(i),S[j]);
                j++;
            }
        }
    }
	/* Decifro il testo cifrato */
	public void codificaRev() {
        buildStringVe();
        String f = getPhrase();
        for(int i=0,j=0;i<f.length();i++){
            if(f.charAt(i)==' ') Risultato[i] = ' ';
            else{
                Risultato[i] = getLetteraRev(f.charAt(i),S[j]);
                j++;
            }
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
	/* Costruisco la stringa di cifratura e l'array che conterra' il numero di spostamenti da effettuare per ciascuna lettera
	   del testo inserito */
    public void buildStringVe(){
        String f = getPhrase();
        char[] Lett = getAlfa();
        for(int i=0,j=0;i<f.length();i++){
            if(f.charAt(i) == ' ') CipherString[i] = ' ';
            else{
                CipherString[i] = Key.charAt(j);
                j++;
            }
        }
        for(int i=0;i<Key.length();i++){
            for(int j=0;j<26;j++){
                if(Key.charAt(i) == Lett[j]) S[i] = j;
            }
        }
    }
    /* Stampo la frase risultante */
    public void stampa() {
        System.out.println("Frase risultante: ");
        for(int i=0;i<getPhrase().length();i++) System.out.print(Risultato[i]);
    }
}
