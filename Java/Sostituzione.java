
public class Sostituzione extends Frase implements X{
	private char[] Risultato = new char[26]; //Testo cifrato
	private int N; //Numero di spostamenti
	
	/* Controllo se n e' corretto */
	public Sostituzione(String phrase, int n) throws Errori{
		super(phrase);
		if(n < 0 || n > 26) {
			n = -1;
			throw new Errori("Numero troppo grande");
		}
		N = n;
	}
	/* Ritorno il testo cifrato */
	public char[] getRisultato() {
		return Risultato;
	}
	/* Cifro il testo in chiaro */
	public void codifica() {
        String f = getPhrase();
        for(int i=0;i<f.length();++i){
            if(f.charAt(i) == ' ') Risultato[i] = ' ';
            else Risultato[i] = getLettera(f.charAt(i),N);
        }
    }
	/* Stampo il testo cifrato */
	public void stampa() {
        System.out.println("Frase risultante: ");
        for(int i=0;i<getPhrase().length();++i) System.out.print(Risultato[i]);
    }
}
