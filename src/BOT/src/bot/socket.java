package bot;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintStream;
import java.net.Socket;
import java.net.SocketTimeoutException;
 
public class socket {
	public static void main(String[] args) throws IOException {
		String str = null;
		byte[] readResult=new byte[1024];
		
		//客户端请求与本机在8890端口建立TCP连接 
		Socket client = new Socket("192.168.137.8", 8890);
		client.setSoTimeout(10000);
		//获取Socket的输出流，用来发送数据到服务端  
		PrintStream out = new PrintStream(client.getOutputStream());
		boolean flag = true;
		
		
		client.getInputStream().read(readResult);
		String price = new String(readResult);
		System.out.println(price);
		
		
		
		
		while(flag){
			//发送数据到服务端  
			out.print(str);
			out.flush();
			if("exit".equals(str)){
				flag = false;
			}else{
				try{
					//从服务器端接收数据有个时间限制（系统自设，也可以自己设置），超过了这个时间，便会抛出该异常
					//读取信息
					//建议起个新线程专门用来接收信息
					//现在可以等time out自动跳过
					client.getInputStream().read(readResult);
					String echo = new String(readResult);
					System.out.println(echo);
					
					client.getInputStream().read(readResult);
					echo = new String(readResult);
					System.out.println(echo);
					
					client.getInputStream().read(readResult);
					echo = new String(readResult);
					System.out.println(echo);
				}catch(SocketTimeoutException e){
					System.out.println("Time out, No response");
				}
			}
		}
		if(client != null){
	        //如果构造函数建立起了连接，则关闭套接字，如果没有建立起连接，自然不用关闭
			client.close();	//只关闭socket，其关联的输入输出流也会被关闭
		}
	}
}