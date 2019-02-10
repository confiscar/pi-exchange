package bot;

public class change {	
	int number;
	public change (int number) {
		this.number= number;
	}
	
	public double value() {
		double price=0;
		double randomnumber=Math.random()/100;
		price = randomnumber*number;
		return price;
	}
}
