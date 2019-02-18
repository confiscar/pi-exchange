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
		
		Initialization a = new Initialization(100,2); 
		
		
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
					a.initial();
					str=a.send();
					//System.out.println("send: " + str);
					out.print(str);
					out.flush();
			}
			else {
				a.ID(receiver.matchID);
				str = a.send();
				out.print(str);
				out.flush();
			}
			
		}		
			
	}
		
		
		
		
}
	

