package bot;

public class Initialization {
	String s;
	String bos;
	int Gprice=100,Ggap=2,number=100;
	public Initialization(String bop) {
		bop=this.bos;
		
		if (bop=="b") {
			buy();
		}
		else 
		{
			sell();
		}
	}
	

	public String buy() {
		double price=Gprice+Math.random();
		s="p,"+bos + "," + String.valueOf(price);
		s=s + "," + String.valueOf(number);
		return s;
	}
	
	public String sell() {
		double price=Gprice+Math.random()-Ggap;
		s="p,"+bos + "," + String.valueOf(price);
		s=s + "," + String.valueOf(number);
		return s;
	}
	
}
