package bot;

import static org.junit.Assert.*;

import org.junit.Test;

public class InitializationTest {

//These two tests are for the initialization functionality
	
	@Test
	public void test_initial_buy() {
		Initialization initial = new Initialization(100, 1);
		initial.initial_buy(); 
		String[] s = initial.s.split(",");
		assertEquals("p",s[0]);
		assertEquals("b",s[1]);
		assertEquals(98.5,Double.parseDouble(s[2]),0.5);  //random price from 98.0 to 99.0
		assertEquals("10",s[3]); //initial amount is 10
		assertEquals("1\n",s[4]); // first orderID is 1
	}

	@Test
	public void test_initial_sell() {
		Initialization initial = new Initialization(100, 1);
		initial.initial_sell(); 
		String[] s = initial.s.split(",");
		assertEquals("p",s[0]);
		assertEquals("s",s[1]);
		assertEquals(101.5,Double.parseDouble(s[2]),0.5);  //random price from 101.0 to 102.0
		assertEquals("10",s[3]); //initial amount is 10
		assertEquals("1\n",s[4]); // first orderID is 1
	}	
	
	
//These tests are for the liquidity providing functionality
	
	@Test
	public void test_buy() {
		Initialization initial = new Initialization(100, 1);
		//assume that the matched price is 100, this method will create a new buy order to replace it to meet the gap
		initial.match_price = 100; 
		initial.buy(); 
		String[] s = initial.s.split(",");
		assertEquals("p",s[0]);
		assertEquals("b",s[1]);
		assertEquals(100,Double.parseDouble(s[2]),0.5);  //random price from 99.5 to 100.5
		assertEquals("10",s[3]); //initial amount is 10
		assertEquals("1\n",s[4]); // first orderID is 1
	}	
	
}
