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
	
	
	@Test
	public void test_sell() {
		Initialization initial = new Initialization(100, 1);
		//assume that the matched price is 100, this method will create a new sell order to replace it to meet the gap
		initial.match_price = 100; 
		initial.sell(); 
		String[] s = initial.s.split(",");
		assertEquals("p",s[0]);
		assertEquals("s",s[1]);
		assertEquals(100,Double.parseDouble(s[2]),0.5);  //random price from 99.5 to 100.5
		assertEquals("10",s[3]); //initial amount is 10
		assertEquals("1\n",s[4]); // first orderID is 1
	}	
	
	
	@Test
	public void test_gap1() {
		//in the case of "canceld <= cancelnumber", which by default: canceled = 0 and cancelnumber = 100 initially
		//hence there is no need to change their value to get to this condition
		Initialization initial = new Initialization(100, 1);
		//assume that the matched price is 100, this method will create a new sell order to replace it to meet the gap
		initial.match_price = 100; 
		for(int i=1;i<=10;i++) {
			receiver.buylist.add(new store(i,100+i,10)); //exchangeID: 1-10, price: 100.x - 110.x, amount = 10
			receiver.selllist.add(new store(i,90+i,10));  //exchangeID, 1-10, price: 90.x - 100.x, amount = 10
		}
		initial.gap();
		//if (canceld <= cancelnumber), test the String s and sc to see if they are having the correct value
		String[] test_sc = initial.sc.split(","); //this should get the first order in the buylist
		//expecting "c,b,101.0,1"
		assertEquals("c",test_sc[0]);
		assertEquals("b",test_sc[1]);
		assertEquals("101.0",test_sc[2]);
		assertEquals("1",test_sc[3]);

		String[] test_s = initial.s.split(","); //this should get the last order in the buylist and modify its price using random
		//expecting "p,b,"+110.x+",10,1"
		assertEquals("p",test_s[0]);
		assertEquals("b",test_s[1]);		
		assertEquals(110,Double.parseDouble(test_s[2]),0.01);  //random price from 110.0 to 110.01
		assertEquals("10",test_s[3]);
		assertEquals("1\n",test_s[4]);
	}	
	
	
	@Test
	public void test_gap2() {
		//in the case of "canceld > cancelnumber", which by default: canceled = 0 and cancelnumber = 100 initially
		//hence there "cancled"'s value need to be modified to get to this condition
		Initialization initial = new Initialization(100, 1);
		//assume that the matched price is 100, this method will create a new sell order to replace it to meet the gap
		initial.match_price = 100; 
		for(int i=1;i<=10;i++) {
			receiver.buylist.add(new store(i,100+i,10)); //exchangeID: 1-10, price: 100.x - 110.x, amount = 10
			receiver.selllist.add(new store(i,90+i,10));  //exchangeID, 1-10, price: 90.x - 100.x, amount = 10
		}
		initial.canceld = 101;
		initial.gap();
		//if (canceld > cancelnumber), test the String s and sc to see if they are having the correct value
		String[] test_sc = initial.sc.split(",");  //this should get the last order in the selllist

		//expecting "c,s,100.0,10"
		assertEquals("c",test_sc[0]);
		assertEquals("s",test_sc[1]);
		assertEquals("100.0",test_sc[2]);
		assertEquals("10",test_sc[3]);

		String[] test_s = initial.s.split(",");  //this should get the first order in the selllist and modify its price using random
		System.out.println(initial.s);
		//expecting "p,s,"+90.x+",10,1"
		assertEquals("p",test_s[0]);
		assertEquals("s",test_s[1]);		
		assertEquals(90.99,Double.parseDouble(test_s[2]),0.01);  //random price from 90.99x to 91.0
		assertEquals("10",test_s[3]);
		assertEquals("1\n",test_s[4]);
	}	
	
}
