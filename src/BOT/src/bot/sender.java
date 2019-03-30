package bot;

import java.io.IOException;
import java.io.PrintStream;
import java.net.Socket;


// send order to the server

public class sender extends Thread {
	public static boolean initialize = false;
	
	Object lock;
	String str = null;
	Socket client = null;

	public static Boolean cancle = true; // Alternate between cancellation and supplement
	
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
		
		Initialization a = new Initialization(100,1); 
		
		
		while(true) {
			// wait to be waked up by receiver class
			synchronized(main.lock){
				try {
					//System.out.println("waiting");
					main.lock.wait();
				} catch (InterruptedException e1) {
					e1.printStackTrace();
				}
			}
			
			// send order to initialize
			if (initialize) {
					a.initial();
					str=a.send();
					System.out.println("send: " + str);
					out.print(str);
					out.flush();
			}
			
			
			// send order when order have been matched
			if ((!initialize) &&(!Initialization.gap)) {
				a.response();
				str = a.send();
				System.out.println("matched send: " + str);
				out.print(str);
				out.flush();
				
			}
			
			
			
			// cancel order when gap is large
			if ((Initialization.gap) && (cancle)) {
				a.gap();
				str = a.sendcancle();
				System.out.println("cancle send: " + str);
				out.print(str);
				out.flush();
			}
			
			// send order when the order have been canceled
			if ((Initialization.gap) && (!cancle)) {
				str = a.send();
				System.out.println("str send: " + str);
				out.print(str);
				out.flush();
			}
			
			

			
		}		
			
	}
		
		
		
		
}
	

