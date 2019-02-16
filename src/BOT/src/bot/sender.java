package bot;

import java.io.IOException;
import java.io.PrintStream;
import java.net.Socket;

public class sender extends Thread {
	public static boolean initialize = true;
	
	//public static int status = 0;
	Object lock;
	int Gnumber = 100;
	String str = null;
	Socket client = null;
	double newPrice = 0; 
	int amount = 10; 
	int buyCount = 0;
	int sellCount = 0;
	int orderId = 0;
	store data = new store();
	
	public sender(Socket client, Object lock) {
		this.client = client;
		this.lock = lock;
	}
	
	
	
	public void run() {
		PrintStream out = null;
		try {
			out = new PrintStream(client.getOutputStream());
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		
		Initialization Gb = new Initialization("b"); 
		Initialization Gs = new Initialization("s"); 
		
		while(true) {
			synchronized(main.lock){
				try {
					//System.out.println("waiting");
					main.lock.wait();
				} catch (InterruptedException e1) {
					e1.printStackTrace();
				}
			}
			
			if (initialize) {
				if(buyCount < 100) {
					str=Gb.buy();
					str=str + "," + String.valueOf(++orderId) + "\n";
					System.out.println("send: " + str);
					out.print(str);
					out.flush();
					str=null;
					buyCount ++;
				}
				else {
					str=Gs.sell();
					str=str + "," + String.valueOf(++orderId) + "\n";
					System.out.println("send: " + str);
					out.print(str);
					out.flush();
					str=null;
					sellCount ++;
				}
				if (sellCount == Gnumber) {
					initialize = false;
				}
				
			}
				
			
			
			
			

			
//			if (status == 2) {
//				str = "p,"+receiver.bs+",";
//				if (receiver.bs == "b") {
//					buy b = new buy(receiver.price,Gnumber);
//					newPrice = b.getPrice(); 
//				}
//				else {
//					sell s = new sell(receiver.price,Gnumber);
//					newPrice = s.getPrice();
//				}
//				str = str + String.valueOf(newPrice) + "," + String.valueOf(amount) + "," + String.valueOf(id);
//				out.print(str);
//				out.flush();
//				status = 0;
//			}
			
				
		}
			
			
			
	}
		
		
		
		
}
	

