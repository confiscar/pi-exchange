package bot;

import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;

public class main {
	 public static void main(String[] args) throws UnknownHostException, IOException{  
		 
		Socket client = new Socket("192.168.137.8", 8890);
		client.setSoTimeout(10000);
		 
		receiver r = new receiver(client);  
        r.start();  
		
        receiver s = new receiver(client);  
        s.start();  
		
	 }
}
