package bot;



public class Initialization {
	String s,sc; 
	float Gprice=0,Ggap=0;
	float valvevalue=(float) 0.5;
	int amount=10;
	
	public static int number_stored = 2000; 
	int orderId = 0;
	
	public static Boolean buy_turn = true;
	public static Boolean cancel_buy_turn = true;
	public static float match_price = 0;
	public static Boolean gap = false;
	public static int canceld = 0;
	
	int countsell,countbuy;
	
	/**
	 * Constructor
	 * @param set_price - this is a special number which is used to initialize buy and sell price
	 * @param gap - the gap between set_price and best buy or sell price
	 */
	public Initialization(float set_price, float gap) {
		Gprice=set_price;
		Ggap=gap;
	}

	
	
	
	/**
	 * initialize the buy price and sell price one by one
	 */
	public void initial() {
		if (buy_turn) {
			initial_buy();
			}
		else {
			initial_sell();
		}
		
	}
	
	
	/**
	 * initialize the buy order string 
	 */
	public void initial_buy() {
		float price=(float) (Gprice-Math.random()-Ggap);
		s="p,b," + String.valueOf(price);
		s=s + "," + String.valueOf(amount) + "," + String.valueOf(++orderId) + "\n";
	}
	
	/**
	 * initialize the sell order string 
	 */
	public void initial_sell() {
		float price=(float) (Gprice+Math.random()+Ggap);
		s="p,s," + String.valueOf(price);
		s=s + "," + String.valueOf(amount) + "," + String.valueOf(++orderId) + "\n";
	}
	
	/**
	 * return the order string
	 */
	public String send() {
		return s;
	}
	
	/**
	 * return the cancel string
	 */
	public String sendcancel() {
		canceld++;
		return sc;
	}
	
	/**
	 * choose which order should be sent
	 */
	public void response() {
		 if (buy_turn) {
			 buy();
		 }
		 else {
			 sell();
		 }
	}
	
	
	
	
	/**
	 * create the buy order string which used to supplement
	 */
	public void buy() {
		float price=(float) (match_price-Math.random()/2);
		s="p,b," + String.valueOf(price);
		s=s + "," + String.valueOf(amount) + "," + String.valueOf(++orderId) + "\n";
		countbuy++;
	}
	/**
	 * create the sell order string which used to supplement
	 */
	public void sell() {
		float price=(float) (match_price+Math.random()/2);
		s="p,s," + String.valueOf(price);
		s=s + "," + String.valueOf(amount) + "," + String.valueOf(++orderId) + "\n";
		countsell++;
	}
	
	
	/**
	 * create cancel string and order string
	 */
	public void gap() {
			float price;
			int cancelnumber = number_stored / 20;
			System.out.println(" count buy: " + countbuy +" count sell: " + countsell);
			if (canceld <= cancelnumber) {
				buy_turn = true;
				cancel_buy_turn = true;
				sc = "c,b,"+ String.valueOf(receiver.buylist.get(0).price)+","+String.valueOf(receiver.buylist.get(0).id);
				
				price=(float) (receiver.buylist.get(receiver.buylist.size()-1).price +Math.random()/100 );
				s="p,b," + String.valueOf(price);
				s += "," + String.valueOf(amount) + "," + String.valueOf(++orderId) + "\n";
			}
			else {
				buy_turn = false;
				cancel_buy_turn = false;
				sc = "c,s,"+ String.valueOf(receiver.selllist.get(receiver.selllist.size()-1).price)+","+String.valueOf(receiver.selllist.get(receiver.selllist.size()-1).id);
				
				price=(float) (receiver.selllist.get(0).price - Math.random()/100);
				s="p,s," + String.valueOf(price);
				s+= "," + String.valueOf(amount) + "," + String.valueOf(++orderId) + "\n";
			}
	}
}
