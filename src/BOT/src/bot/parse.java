package bot;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class parse {
	String str;
	String id;
	int []x = new int[5];
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
		
		String regex = "\\d+";
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(str);
        while (matcher.find()) {
            x[++i] = Integer.parseInt(matcher.group());
            //System.out.println(x);
        }
	}
	
	public int getid() {
		return x[2];
	}
	
	
	

	
}