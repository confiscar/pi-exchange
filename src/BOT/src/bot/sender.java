package bot;

import java.io.IOException;
import java.io.PrintStream;
import java.net.Socket;

public class sender extends Thread {
	public static int status = 0;
	Object lock;
	int Gnumber = 100;
	String str = null;
	Socket client = null;
	double newPrice = 0; 
	int id = 2 * Gnumber + 1;
	int amount = 10; 
	
	int buyCount = 0;
	int sellCount = 0;
	int orderId = 0;
	int iterationCount = 0;
	
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
					System.out.println("waiting");
					main.lock.wait();
				} catch (InterruptedException e1) {
					e1.printStackTrace();
				}
			}
			
			if(buyCount < 100 && status == 1) {
				str=Gb.buy();
				str=str + "," + String.valueOf(++orderId) + "\n";
				System.out.println("send: " + str);
				status = 0;
				out.print(str);
				out.flush();
				str=null;
				buyCount ++;
			}
			
			if(sellCount < 100 && status == 1) {
				str=Gs.sell();
				str=str + "," + String.valueOf(++orderId) + "\n";
				System.out.println("send: " + str);
				status = 0;
				out.print(str);
				out.flush();
				str=null;
				sellCount ++;
			}
			
//			if (status == 1) {
//				Initialization Gb = new Initialization("b"); 
//				for (int i=0;i <= Gnumber; i++) {
//					str=Gb.buy();
//					str=str + "," + String.valueOf(i) + "\n";
//					System.out.println(str);
//					out.print(str);
//					out.flush();
//					str=null;
//					status = 0;
//				}
//				
//				
//				for (int i=Gnumber+1 ;i <= Gnumber*2; i++) {
//					
//				}	
//				status = 0;
//			}
			
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
	

