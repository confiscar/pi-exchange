package bot;

import static org.junit.Assert.*;

import org.junit.Test;

public class InitializationTest {


	
	@Test
	public void test_initial_buy() {
		Initialization initial1 = new Initialization(100, 1);
		initial1.initial_buy(); 
		parse parse1 = new parse(initial1.s); //which is "p,b,#RandomPrice,#amount,#orderID"
		String[] s = initial1.s.split(",");
		assertEquals("p",s[0]);
		assertEquals("b",s[1]);
		assertEquals(98.5,Double.parseDouble(s[2]),0.5);  //random price from 98.0 to 99.0
		assertEquals("10",s[3]); //initial amount is 10
		assertEquals("1\n",s[4]); // first orderID is 1
	}

}
