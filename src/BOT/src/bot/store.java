package bot;

public class store {
	int number=100;	
	double[][] datab = new double[3][number];// id,price,amount;
	double[][] datas = new double[3][number];	
	double matchPrice;
	int matchindex;
	public store () {
	}
	
	
	
	public void addb(int id,double price,int amount,int index) {
		datab[0][index]=id;
		datab[1][index]=price;
		datab[2][index]=amount;
	}
	
	public void adds(int id,double price,int amount,int index) {
		datas[0][index]=id;
		datas[1][index]=price;
		datas[2][index]=amount;
	}
	
	public String matchid(int id){
		for (int i=0;i<number;i++) {
			if (datab[0][i] == id) {
				matchPrice = datab[1][i]; 
				matchindex = i;
				return("buy");
			}
			if (datas[0][i] == id) {
				matchPrice = datas[1][i]; 
				matchindex = i;
				return("sell");
			}
		}
		return("");
		
	}
	
	public double getprice() {
		return(matchPrice);
	}
	
	public int getindex() {
		return(matchindex);
	}
	
}
