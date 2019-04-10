package bot;

import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;
import java.net.Socket;
import java.net.UnknownHostException;
import java.util.ArrayList;
import java.util.List;


/**
 * control the socket and the lock; 
 * 
 * @author shenhuan
 */
public class main {
	public static Object lock = new Object();
	 public static void main(String[] args) throws UnknownHostException, IOException{  
		 
		 List<String> records = new ArrayList<String>();
	        String filename = "config.txt";
	        String IPAddress = null;
	        int port = 0;
		 
		 try
		 {
		     BufferedReader reader = new BufferedReader(new FileReader(filename));
		     String line;
		     while ((line = reader.readLine()) != null)
		     {
		         records.add(line);
		     }
		     reader.close();

		     for(int i = 0; i < records.size(); i++){
		         if(records.get(i).contains("IP-Address")){
		             String part[] = records.get(i).split(":");
		             IPAddress = part[1].trim();
		             System.out.println(IPAddress);
		         }
		         else if(records.get(i).contains("Port")){
		             String part[] = records.get(i).split(":");
		             port = Integer.parseInt(part[1].trim());
		             System.out.println(port);
		         }
		     }
		 }
		 catch (Exception e)
		 {
		     System.err.format("Exception occurred trying to read '%s'.", filename);
		     e.printStackTrace();
		 }
		 
		 
		 
		Socket client = new Socket(IPAddress, port);
		
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






