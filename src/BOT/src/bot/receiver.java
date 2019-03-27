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
	
	String initialInfo = "best buy: 0.000000";
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
			System.out.println(echo);
			
			
			
			if (echo.contains(initialInfo)) {
				sender.initialize = true;
				synchronized(main.lock){
					main.lock.notify();
				}
			}	
			
			
			
			
			if(echo.contains("current order"))  {
				parse x= new parse(echo);
				int exchangeID = x.getid(1);
				float price = x.getprice();
				int amount = x.getid(3);
				int status = x.getid(4);
				
				if (status == 0) 
				{
					if (Initialization.buy_turn) {
						buylist.add(new store(exchangeID,price,amount));
						Collections.sort(buylist);
						Initialization.buy_turn = false;
						if ((!sender.initialize)&&(!Initialization.gap)) {
							float best_buy = buylist.get(Initialization.number_stored-1).price;
							float best_sell = selllist.get(0).price;
							
							System.out.println("gap: " + (best_sell - best_buy));
							if ((best_sell - best_buy)>1.5) {
								Initialization.gap = true;
							}
						}
					}
					else {
						selllist.add(new store(exchangeID,price,amount));
						Collections.sort(selllist);
						Initialization.buy_turn = true;
						if ((!sender.initialize)&&(!Initialization.gap)) {
							float best_buy = buylist.get(Initialization.number_stored-1).price;
							float best_sell = selllist.get(0).price;
							System.out.println("gap: " + (best_sell - best_buy));
							if ((best_sell - best_buy)>1.5) {
								Initialization.gap = true;
							}
						}
					}
					
					if (Initialization.gap) {
						System.out.println("cancled: "+ Initialization.cancled);
						sender.cancle = true;
						if (Initialization.cancled == 4) {
							Initialization.cancled = 0;
							Initialization.gap = false;
							continue;
						}
						
						
						
						synchronized(main.lock){
							main.lock.notify();
						}
					}
					
				}		
				
				if ((selllist.size() == Initialization.number_stored ) && (sender.initialize)) {
					//System.out.println(selllist.size());
					sender.initialize = false;
				}
				
				
				if (sender.initialize) {
					synchronized(main.lock){
						main.lock.notify();
					}
				}
				
				if (status == 2) {
					if (Initialization.cancle_buy_turn) {
						System.out.println("buy remove: ");
						buylist.remove(0);
					}
					else {
						System.out.println("sell remove: ");
						selllist.remove(Initialization.number_stored-1);
					}	
					
					sender.cancle = false;
					
					System.out.println("next start:");
					synchronized(main.lock){
						main.lock.notify();
					}	
					
				}
				
				
					
			}
			
			if (echo.contains("previous order")) {
				parse s= new parse(echo);
				int exchangeid = s.getid(1);
				if (exchangeid== buylist.get(Initialization.number_stored-1).id) {
					Initialization.buy_turn=true;
					Initialization.match_price = (float) buylist.get(Initialization.number_stored-1).price;
					buylist.remove(Initialization.number_stored-1);
				}
				else {
					Initialization.buy_turn=false;
					Initialization.match_price = (float) selllist.get(0).price;
					selllist.remove(0);
				}	
				synchronized(main.lock){
					main.lock.notify();
					//System.out.println("notify");
				}
			}
			
//			for (int i=0;i<buylist.size();i++) {
//				System.out.println("id: " + buylist.get(i).id + "   " + buylist.get(i).price );
//			}
//			for (int i=0;i<selllist.size();i++) {
//				System.out.println("id: " + selllist.get(i).id + "   " + selllist.get(i).price );
//			}
			
			
			
		}
		
	}
}