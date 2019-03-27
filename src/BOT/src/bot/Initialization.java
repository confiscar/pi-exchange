package bot;



public class Initialization {
	String s,sc;
	float Gprice=0,Ggap=0;
	float valvevalue=(float) 0.5;
	int amount=10;
	
	public static int number_stored = 10; 
	int orderId = 0;
	
	public static Boolean buy_turn = true;
	public static Boolean cancle_buy_turn = true;
	public static float match_price = 0;
	public static Boolean gap = false;
	public static int cancled = 0;
	
	int countsell,countbuy;
	
	public Initialization(float price, float gap) {
		Gprice=price;
		Ggap=gap;
	}


	public void initial() {
		
		if (buy_turn) {
			initial_buy();
			}
		else {
			initial_sell();
		}
		
	}
	public void initial_buy() {
		float price=(float) (Gprice+Math.random()-Ggap);
		s="p,b," + String.valueOf(price);
		s=s + "," + String.valueOf(amount) + "," + String.valueOf(++orderId) + "\n";
	}
	
	public void initial_sell() {
		float price=(float) (Gprice+Math.random()+Ggap);
		s="p,s," + String.valueOf(price);
		s=s + "," + String.valueOf(amount) + "," + String.valueOf(++orderId) + "\n";
	}
	
	public String send() {
		return s;
	}
	
	public String sendcancle() {
		cancled++;
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
		float price=(float) (match_price-Math.random()/2);
		s="p,b," + String.valueOf(price);
		s=s + "," + String.valueOf(amount) + "," + String.valueOf(++orderId) + "\n";
		countbuy++;
	}
	
	public void sell() {
		float price=(float) (match_price+Math.random()/2);
		s="p,s," + String.valueOf(price);
		s=s + "," + String.valueOf(amount) + "," + String.valueOf(++orderId) + "\n";
		countsell++;
	}
	
	

	
	public void gap() {
			float price;
			int canclenumber = 4,canclebuy;
			//float Proportion;
			//Proportion= countbuy/(countsell+countbuy);
			//canclebuy = canclenumber-(int) Math.ceil(Proportion*canclenumber) ;
			
			System.out.println(" count buy: " + countbuy +" count sell: " + countsell);
			//System.out.println(" cancle buy: " + canclebuy);
			
			
			//if (cancled==0) {
			//	Gprice -= (Proportion*2-1) * valvevalue;
			//}
			
			if (cancled<=4) {
				buy_turn = true;
				cancle_buy_turn = true;
				sc = "c,b,"+ String.valueOf(receiver.buylist.get(0).price)+","+String.valueOf(receiver.buylist.get(0).id);
				price=(float) (Gprice+Math.random()/2-Ggap/2);
				//price=Gprice+Math.random()/(1/((1-Proportion)*valvevalue))-Ggap;
				s="p,b," + String.valueOf(price);
				s += "," + String.valueOf(amount) + "," + String.valueOf(++orderId) + "\n";
			}
			else {
				buy_turn = false;
				cancle_buy_turn = false;
				sc = "c,s,"+ String.valueOf(receiver.selllist.get(number_stored-1).price)+","+String.valueOf(receiver.selllist.get(number_stored-1).id);
				price=(float) (Gprice+Math.random()/4+Ggap);
				//price =Gprice+Math.random()/(1/(Proportion*valvevalue))+Ggap;
				s="p,s," + String.valueOf(price);
				s+= "," + String.valueOf(amount) + "," + String.valueOf(++orderId) + "\n";
			}
			
			
	}
}
