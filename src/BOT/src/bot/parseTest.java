package bot;

import static org.junit.Assert.*;

import org.junit.Test;

public class parseTest {


	
	@Test
	public void testRun() {
		parse test1 = new parse("order ID: 1, exchange ID: 2, price: 99.5, amount: 100, status: 0");
		assertEquals(1,test1.getid(0));
		assertEquals(2,test1.getid(1));
		assertEquals(99.5,test1.getprice(),0.001); //because getprice() == (float) getid(2)
		assertEquals(100,test1.getid(3));
		assertEquals(0,test1.getid(4));

	}

}
