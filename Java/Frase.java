
public class Frase {
	private String Phrase; //Testo in input
	//Array con le lettere dell'alfabeto
	private final char[] alfa = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z'};
	
	/* Effuttuo i controlli per vedere se la frase rispetta i vincoli(ovvero se e' costituita da soli caratteri alfabetici e spazi)
	 e in caso affermativo trasformo ogni lettera da minuscolo a maiuscolo, ignorando gli spazi */
	public Frase(String phrase) throws Errori{
		super();
		int nspazi = 0;
        for(int i=0;i<phrase.length();i++){ //Controllo se la frase costituita da soli spazi
            if(phrase.charAt(i) == ' ') nspazi++;
        }
        if(nspazi == phrase.length()){
            this.Phrase = "";
            throw new Errori("La frase non puo' contenere solo spazi!");
        }
        else {
			String temp = phrase.toUpperCase();
			for(int i=0;i<phrase.length();i++) { //Controllo se la frase da caratteri alfabetici e spazi
				if(temp.charAt(i)<'A' || temp.charAt(i)>'Z') {
					if(temp.charAt(i)!=' ') {
						this.Phrase = "";
						throw new Errori("La frase in chiaro deve contenere solo caratteri alfabetici e spazi!");
					}
				}
			}
			this.Phrase = temp;
        }
	}
	/* Ritorno la frase inserita */
	public String getPhrase() {
		return Phrase;
	}
	/* Ritorno l'elenco delle lettere dell'alfabeto */
	public char[] getAlfa() {
		return alfa;
	}
	/* Trovo e ritorno la lettera che si trova 'pos' posizioni dopo rispetto a 'c' */
	public char getLettera(char c,int pos) {
        char l;
        int temp = 0;
        for(int i=0;i<26;i++){
            if(alfa[i]==c){
                temp = i;
                break;
            }
        }
        if(25-temp >= pos)
            l = alfa[temp+pos];
        else{
            pos = pos - (25-temp) -1;
            l = alfa[pos];
        }
        return l;
    }
}
