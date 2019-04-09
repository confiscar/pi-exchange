package bot;


// store the order. (lowest-highest)
public class store implements Comparable <store> {
	 final int id;
	 final float price;
	 final int amount;
	 int exchangeId;
	
	
	/**
	 * Constructor
	 * @param id - the exchange id
	 * @param price - the price of the order
	 * @param amount - the amount of the order
	 */
	public store( int id,  float price,  int amount) {
		this.id = id;
		this.price = price;
		this.amount = amount;
	}
	
	/**
	 * sort the list
	 */
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
