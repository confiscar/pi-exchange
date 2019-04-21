
import java.io.IOException;
import java.io.PrintStream;
import java.net.Socket;
import java.util.ArrayList;
import java.util.List;


// send order to the server

public class Sender extends Thread {	
	Long time;
	String str = null;
	Socket client = null;
	
	
	/**
	 * send information to server and parse it.
	 * choose the corresponding operation.
	 */
	public Sender(Socket client, Long time) {
		this.client = client;
		this.time = time;
	}
	
	/**
	 * send the information.
	 */
	public void run() {
		PrintStream out = null;
		byte[] readResult=new byte[1024];
		int count = 0;
		try {
			out = new PrintStream(client.getOutputStream());
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		Long sum = 0L;
		while(System.currentTimeMillis() < time) {
			
			out.println("p,b,1,1,1");
			out.flush();
			long send = System.nanoTime();
			try {
				client.getInputStream().read(readResult);
				if(readResult[0] != 'c') {
					client.getInputStream().read(readResult);
				}
			} catch (IOException e) {
				e.printStackTrace();
			}
			long response = System.nanoTime();
			
			sum = sum + response - send;
			count ++;
		}
		
		Double avg = (double)sum / (double)count;
		System.out.println("average latency: " + avg/1000000);
		
		System.out.println(count);
				
	}
	
		
}
