import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;
import java.sql.Time;


public class Main {
	public static void main(String[] args) throws UnknownHostException, IOException{  
		 

		long time = System.currentTimeMillis() + 60000;
		
		Socket client = new Socket("192.168.137.191", 8890);
		client.setSoTimeout(0);
		Sender s = new Sender(client, time);  
        s.start();  
		
        
//        Socket client1 = new Socket("192.168.137.191", 8890);
//		client1.setSoTimeout(0);
//		Sender s1 = new Sender(client1, time);  
//        s1.start();
//		
//        
//        Socket client2 = new Socket("192.168.137.191", 8890);
//		client2.setSoTimeout(0);
//		Sender s2 = new Sender(client2, time);  
//        s2.start();
//        
//        
//        Socket client3 = new Socket("192.168.137.191", 8890);
//		client3.setSoTimeout(0);
//		Sender s3 = new Sender(client3, time);  
//        s3.start();
//        
//        
//        Socket client4 = new Socket("192.168.137.191", 8890);
//		client4.setSoTimeout(0);
//		Sender s4 = new Sender(client4, time);  
//        s4.start();
//        
//        
//        Socket client5 = new Socket("192.168.137.191", 8890);
//		client5.setSoTimeout(0);
//		Sender s5 = new Sender(client5, time);  
//        s5.start();
//        
//        
//        Socket client6 = new Socket("192.168.137.191", 8890);
//		client6.setSoTimeout(0);
//		Sender s6 = new Sender(client6, time);  
//        s6.start();
//        
//        
//        Socket client7 = new Socket("192.168.137.191", 8890);
//		client7.setSoTimeout(0);
//		Sender s7 = new Sender(client7, time);  
//        s7.start();
	 }
}
