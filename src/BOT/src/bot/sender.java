package bot;

import java.io.PrintStream;
import java.net.Socket;

public class sender extends Thread {
	public static int status = 0;
	int Gnumber = 100;
	String str = null;
	Socket client = null;
	double newPrice = 0; 
	int id = 2 * Gnumber + 1;
	int amount = 10; 
	
	public sender(Socket client) {
		this.client = client;
	}
	
	
	
	public void run() {
		PrintStream out = new PrintStream(client.getOutputStream());
		while(true) {
			if (status == 1) {
				Initialization Gb = new Initialization("b"); 
				for (int i=0;i <= Gnumber; i++) {
					str=Gb.buy();
					str=str + "," + String.valueOf(i);
					out.print(str);
					out.flush();
					str=null;
				}
				
				Initialization Gs = new Initialization("s"); 
				for (int i=Gnumber+1 ;i <= Gnumber*2; i++) {
					str=Gs.sell();
					str=str + "," + String.valueOf(i);
					out.print(str);
					out.flush();
					str=null;
				}	
				status = 0;
			}
			
			if (status == 2) {
				str = "p,"+receiver.bs+",";
				if (receiver.bs == "b") {
					buy b = new buy(receiver.price,Gnumber);
					newPrice = b.getPrice(); 
				}
				else {
					sell s = new sell(receiver.price,Gnumber);
					newPrice = s.getPrice();
				}
				str = str + String.valueOf(newPrice) + "," + String.valueOf(amount) + "," + String.valueOf(id);
				out.print(str);
				out.flush();
				status = 0;
			}
			
				
		}
			
			
			
	}
		
		
		
		
}
	

