package bot;


public class buy {
	private double price;
	private int number;
	public buy(double price, int number) {
		this.price=price;
		this.number=number;
		adjustPrice();
	}
	
	public double getPrice() {
		return price;
	}
	
	
	public void adjustPrice() {
		change ap =new change (number);
		price = price + ap.value();
	}
}
