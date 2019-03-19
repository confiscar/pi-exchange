package bot;

import java.text.SimpleDateFormat;
import java.util.Date;

public class Initialization {
	String s;
	String bos;
	double Gprice=0,Ggap=0;
	int amount=10000;
	int Gnumber = 10; 
	int buyCount = 0;
	int sellCount = 0;
	int orderId = 0;
	store data = new store();

	boolean buy = true;
	public Initialization(double price, double gap) {
		Gprice=price;
		Ggap=gap;
	}


	public void initial() {
		if (buy){
			buy();
			buy= false;
		}	
		else {
			sell();
			buy = true;
		}
			
		if (sellCount == Gnumber) {
			sender.initialize = false;
			
			// show time when initialisation finish
			SimpleDateFormat df = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
			System.out.println(df.format(new Date()));
		}
			
	}
	

	public void buy() {
		double price=Gprice+Math.random();
		s="p,b," + String.valueOf(price);
		s=s + "," + String.valueOf(amount) + "," + String.valueOf(++orderId) + "\n";
		data.addb(orderId, price, amount, buyCount);
		buyCount++;
	}
	
	public void sell() {
		double price=Gprice+Math.random()-Ggap;
		s="p,s," + String.valueOf(price);
		s=s + "," + String.valueOf(amount) + "," + String.valueOf(++orderId) + "\n";
		data.adds(orderId, price, amount, sellCount);
		sellCount++;
	}
	
	public String send() {
		return s;
	}
	
	public void ID(int id) {
		String type;
		type = data.matchid(id);
		Gprice = data.getprice();
		if (type == "buy") {
			buyCount = data.getindex();
			buy();
		}
		else {
			sellCount = data.getindex();
			sell();
		}
	}
	
	
}
