package bot;

import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;

// control the socket and the lock; 

public class main {
	public static Object lock = new Object();
	 public static void main(String[] args) throws UnknownHostException, IOException{  
		 
		Socket client = new Socket("192.168.137.220", 8890);
		
		client.setSoTimeout(0);
		
		System.out.println("client initialized");
		
		sender s = new sender(client, lock);  
        s.start();  
		
        synchronized(lock){
			try {
				lock.wait(10);
			} catch (InterruptedException e1) {
				e1.printStackTrace();
			}
		}
        
		receiver r = new receiver(client, lock);  
        r.start();  
		
        
	 }
}
