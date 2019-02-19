package bot;

import java.net.Socket;

public class Initialization {
	String s;
	String bos;
	double Gprice=0,Ggap=0;
	int amount=10;
	int Gnumber = 100; 
	int buyCount = 0;
	int sellCount = 0;
	int orderId = 0;
	store data = new store();

	public Initialization(double price, double gap) {
		Gprice=price;
		Ggap=gap;
	}


	public void initial() {
		if (buyCount<Gnumber)
			buy();
		else 
			sell();
		if (sellCount == Gnumber) 
			sender.initialize = false;
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
