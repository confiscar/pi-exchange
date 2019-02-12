package bot;

import java.io.IOException;
import java.io.PrintStream;
import java.net.Socket;


public class receiver extends Thread throws IOException {
	public void run() {
		byte[] readResult=new byte[1024];
		
		
		Socket client = new Socket("192.168.137.8", 8890);
		client.setSoTimeout(10000);
		
		
		while (true) {
		client.getInputStream().read(readResult);
		String echo = new String(readResult);
		
		if(echo.equals("sell price: 0.000000, buy price: 0.000000"))  {
			sender.status = 1;
		}
		
		
		
		
		
		
		}
		
		
		
		
	}
	
	
}
