package bot;

import java.io.IOException;
import java.net.Socket;
import java.util.ArrayList;
import java.util.Collections;
import java.util.List;

public class receiver extends Thread{
	Socket client = null;
	Object lock;
	sender s = null;
	public static int matchID = 0;
	public static Boolean respon = false;
	
	String initialInfo = "sell price: 0.000000, buy price: 0.000000\n";
	public static List<store> buylist = new ArrayList<>();
	public static List<store> selllist = new ArrayList<>();
	
	public receiver(Socket client, Object lock) {
		this.client = client;
		this.lock = lock;
	}
		
	public void run() {
		byte[] readResult=new byte[1024];
		while (true) {
			try {
				client.getInputStream().read(readResult);
			} catch (IOException e) {
				e.printStackTrace();
			}
			
			String echo = new String(readResult);
			//System.out.println(echo);
			
			if (echo.contains(initialInfo)) {
				sender.initialize = true;
				synchronized(main.lock){
					main.lock.notify();
				}
			}	
			
			if(echo.contains("current order"))  {
				parse x= new parse(echo);
				int exchangeID = x.getid(1);
				double price = x.getprice();
				int amount = x.getid(3);
				int status = x.getid(4);
				
				if (status == 0) 
				{
					if (Initialization.buy_turn) {
						buylist.add(new store(exchangeID,price,amount));
						Collections.sort(buylist);
						Initialization.buy_turn = false;
						if ((!sender.initialize)&&(!Initialization.gap)) {
							double best_buy = buylist.get(Initialization.number_stored-1).price;
							double best_sell = selllist.get(0).price;
							if ((best_sell - best_buy)>1.5) {
								Initialization.gap = true;
								synchronized(main.lock){
									main.lock.notify();
								}
							}
						}
					}
					else {
						selllist.add(new store(exchangeID,price,amount));
						Collections.sort(selllist);
						Initialization.buy_turn = true;
						if ((!sender.initialize)&&(!Initialization.gap)) {
							double best_buy = buylist.get(Initialization.number_stored-1).price;
							double best_sell = selllist.get(0).price;
							if ((best_sell - best_buy)>1.5) {
								Initialization.gap = true;
								synchronized(main.lock){
									main.lock.notify();
								}
							}
						}
					}
				}		
				
				if ((selllist.size() == Initialization.number_stored ) && (sender.initialize)) {
					System.out.println(selllist.size());
					sender.initialize = false;
				}
				
				
				if (sender.initialize) {
					synchronized(main.lock){
						main.lock.notify();
					}
				}
				
				if (status == 2) {
					if (Initialization.buy_turn) {
						buylist.remove(0);
					}
					else {
						selllist.remove(Initialization.number_stored-1);
					}	
					
					if (Initialization.gap) {
						if (Initialization.cancled == 10) {
							Initialization.cancled = 0;
							Initialization.gap = false;
							continue;
						}
						synchronized(main.lock){
							main.lock.notify();
						}
					}	
					
				}
				
				
					
			}
			
			if (echo.contains("previous order")) {
				parse s= new parse(echo);
				int exchangeid = s.getid(1);
				if (exchangeid== buylist.get(Initialization.number_stored-1).id) {
					Initialization.buy_turn=true;
					Initialization.match_price = buylist.get(Initialization.number_stored-1).price;
					buylist.remove(Initialization.number_stored-1);
				}
				else {
					Initialization.buy_turn=false;
					Initialization.match_price = selllist.get(0).price;
					selllist.remove(0);
				}	
				synchronized(main.lock){
					main.lock.notify();
					//System.out.println("notify");
				}		
			}
		}
	}
}