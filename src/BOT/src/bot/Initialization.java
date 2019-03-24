package bot;



public class Initialization {
	String s,sc;
	double Gprice=0,Ggap=0;
	double valvevalue=0.5;
	int amount=10;
	
	public static int number_stored = 10; 
	int orderId = 0;
	
	public static Boolean buy_turn = true;
	public static double match_price = 0;
	public static Boolean gap = false;
	public static int cancled = 0;
	
	int countsell,countbuy;
	
	public Initialization(double price, double gap) {
		Gprice=price;
		Ggap=gap;
	}


	public void initial() {
		
		if (buy_turn) {
			initial_buy();
			buy_turn = false;
			}
		else {
			initial_sell();
			buy_turn = true; 
		}
		
	}
	public void initial_buy() {
		double price=Gprice+Math.random()-Ggap;
		s="p,b," + String.valueOf(price);
		s=s + "," + String.valueOf(amount) + "," + String.valueOf(++orderId) + "\n";
	}
	
	public void initial_sell() {
		double price=Gprice+Math.random()+Ggap;
		s="p,s," + String.valueOf(price);
		s=s + "," + String.valueOf(amount) + "," + String.valueOf(++orderId) + "\n";
	}
	
	public String send() {
		return s;
	}
	
	public String sendcancle() {
		return sc;
	}
	

	public void response() {
		 if (buy_turn) {
			 buy();
		 }
		 else {
			 sell();
		 }
	}
	
	public void buy() {
		double price=match_price-Math.random()/2;
		s="p,b," + String.valueOf(price);
		s=s + "," + String.valueOf(amount) + "," + String.valueOf(++orderId) + "\n";
		countbuy++;
	}
	
	public void sell() {
		double price=match_price+Math.random()/2;
		s="p,s," + String.valueOf(price);
		s=s + "," + String.valueOf(amount) + "," + String.valueOf(++orderId) + "\n";
		countsell++;
	}
	
	

	
	public void gap() {
			double price;
			int canclenumber = 100,canclebuy;
			double Proportion;
			Proportion= countbuy/(countsell+countbuy);
			canclebuy = canclenumber-(int) Math.ceil(Proportion*canclenumber) ;
			if (cancled==0) {
				Gprice -= (Proportion*2-1) * valvevalue;
			}
			
			if (cancled<canclebuy) {
				sc = "c,b,"+ String.valueOf(receiver.buylist.get(number_stored-1).price)+String.valueOf(receiver.buylist.get(number_stored-1).exchangeId);
				
				price=Gprice+Math.random()/(1/((1-Proportion)*valvevalue))-Ggap;
				s="p,b," + String.valueOf(price);
				s += "," + String.valueOf(amount) + "," + String.valueOf(++orderId) + "\n";
			}
			else {
				sc = "c,s,"+ String.valueOf(receiver.selllist.get(0).price)+String.valueOf(receiver.selllist.get(0).exchangeId);
				
				price =Gprice+Math.random()/(1/(Proportion*valvevalue))+Ggap;
				s="p,s," + String.valueOf(price);
				s+= "," + String.valueOf(amount) + "," + String.valueOf(++orderId) + "\n";
			}
	}
}
