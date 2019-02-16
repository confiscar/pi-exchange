package bot;

public class store {
	int number=100;	
	double[][] datab = new double[3][number];// id,price,amount;
	double[][] datas = new double[3][number];	
	
	public store () {
	}
	
	
	
	public void addb(int id,double price,int amount,int index) {
		datab[0][index]=id;
		datab[1][index]=price;
		datab[2][index]=index;
	}
	
	public void adds(int id,double price,int amount,int index) {
		datas[0][index]=id;
		datas[1][index]=price;
		datas[2][index]=index;
	}
		
		
	
	
	
	
}
