package bot;

public class Parse {
	String price;
	String[] n,m;
	double buyPrice,sellPrice;
	public Parse(String price) {
		this.price = price;
		splitP();
		parseP();
	}
	
	public void splitP() {
		n = price.split(",");
		
	}
	
	public void parseP() {
		m = n[0].split(" ");
		buyPrice = Double.parseDouble(m[2]);
		
		m = n[1].split(" ");
		sellPrice = Double.parseDouble(m[2]);
	}
	
	public double getBP() {
		return buyPrice;
	}
	
	public double getSP() {
		return sellPrice;
	}
	
}
