package bot;

public class store implements Comparable <store> {
	 final int id;
	 final double price;
	 final int amount;
	
	
	
	public store( int id,  double price,  int amount) {
		this.id = id;
		this.price = price;
		this.amount = amount;
	}
	
	@Override
	public int compareTo(store o) {
		if (price > o.price) {
			return 1;
		}
		else if (price == o.price) {
			return 0;
		}
		else {
			return -1;
		} 
	}
	
	
		
	
	
	
}
