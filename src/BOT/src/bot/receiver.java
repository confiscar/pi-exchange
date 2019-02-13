package bot;

import java.io.IOException;
import java.io.PrintStream;
import java.net.Socket;

public class receiver extends Thread{
	Socket client = null;
	public static double price = 0;
	public static String bs = "o";
	
	public receiver(Socket client) {
		this.client = client;
	}
	
	
	public void run() {
		byte[] readResult=new byte[1024];
		while (true) {
			client.getInputStream().read(readResult);
			String echo = new String(readResult);
			
			
			if(echo.equals("sell price: 0.000000, buy price: 0.000000"))  {
				sender.status = 1;
			}
			
			
			if (echo.equals("")) {
				price = 0;
				bs = "";
				sender.status = 2;
				
			}
			
		
		}
		
		
		
		
	}
	
	
}
