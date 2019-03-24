package bot;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class parse {
	String str;
	String id;
	double []x = new double[5];
	int i = 0;
	public parse(String str) {
		this.str = str;
		run();
	}
	
	public void run() {
		//String regEx = "[^0-9]";
		//Pattern p = Pattern.compile(regEx);
		//Matcher m = p.matcher(str);
		//String string = m.replaceAll(" ").trim();
		//String[] strArr = string.split(" ");
		
//		System.out.println(str);
		String regex = "\\d+(\\.\\d+)?";
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(str);
        while (matcher.find()) {
            x[i++] = Double.parseDouble(matcher.group());
//            System.out.println(x[i-1]);
        }
	}
	
	public int getid(int y) {
		return (int)x[y];
	}
	
	

	public double getprice() {
		return x[2];
	}
	
	

	
}