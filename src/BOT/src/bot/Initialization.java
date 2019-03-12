package bot;

import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class Initialization {
	String s;
	double Gprice=0,Ggap=0;
	int amount=10;
	int number_stored = 10000; 
	int orderId = 0;
	final List<store> buylist = new ArrayList<>();
	final List<store> selllist = new ArrayList<>();

	public Initialization(double price, double gap) {
		Gprice=price;
		Ggap=gap;
	}


	public void initial() {
		if (orderId<number_stored)
			initial_buy();
		else 
			initial_sell();
		if (orderId-number_stored == number_stored) 
			sender.initialize = false;
	}
	

	public void initial_buy() {
		double price=Gprice+Math.random()-Ggap;
		s="p,b," + String.valueOf(price);
		s=s + "," + String.valueOf(amount) + "," + String.valueOf(++orderId) + "\n";
		buylist.add(new store(orderId,price,amount));
		Collections.sort(buylist);
	}
	
	public void initial_sell() {
		double price=Gprice+Math.random();
		s="p,s," + String.valueOf(price);
		s=s + "," + String.valueOf(amount) + "," + String.valueOf(++orderId) + "\n";
		selllist.add(new store(orderId,price,amount));
		Collections.sort(selllist);
	}
	
	public String send() {
		return s;
	}
	
	public void response() {
		 if (receiver.matchID == buylist.get(number_stored-1).id) {
			Gprice = buylist.get(number_stored-1).price;
			buy();
		 }
		 else {
			 Gprice = selllist.get(0).price;
			 sell();
		 }
	}
	
	public void buy() {
		double price=Gprice-Math.random()/2;
		s="p,b," + String.valueOf(price);
		s=s + "," + String.valueOf(amount) + "," + String.valueOf(++orderId) + "\n";
		buylist.remove(number_stored-1);
		buylist.add(new store(orderId,price,amount));
		Collections.sort(buylist);
	}
	
	public void sell() {
		double price=Gprice+Math.random()/2;
		s="p,b," + String.valueOf(price);
		s=s + "," + String.valueOf(amount) + "," + String.valueOf(++orderId) + "\n";
		selllist.remove(0);
		selllist.add(new store(orderId,price,amount));
		Collections.sort(selllist);
	}
	

	
	
	
}
