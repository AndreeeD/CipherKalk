
public class Errori extends Throwable {
	private String c;

	public Errori(String c) {
		super();
		this.c = c;
	}
	public String getC() {
		return c;
	}	
}