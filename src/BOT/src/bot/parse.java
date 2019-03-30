package bot;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class parse {
	String str;
	String id;
	float []x = new float[5];
	int i = 0;
	public parse(String str) {
		this.str = str;
		run();
	}
	
	public void run() {
		
//		System.out.println(str);
		String regex = "\\d+(\\.\\d+)?";   //regular expression ： extract decimals or integers
		
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(str);
        while (matcher.find()) {
            x[i++] = (float) Double.parseDouble(matcher.group());
//            System.out.println(x[i-1]);
        }
	}
	
	public int getid(int y) {
		return (int)x[y];
	}
	
	

	public float getprice() {
		return x[2];
	}
	
	

	
}