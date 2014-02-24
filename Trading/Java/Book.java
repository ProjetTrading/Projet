
public class Book {
	private String symbol;
	private bidOffer[] bid;
	private bidOffer[] offer;
	
	Book() {
		bid = new bidOffer[10];
		offer = new bidOffer[10];
		symbol = new String("");
	}
	public native String getSymbolBook();
	public native float[] getBidValueBook();
	public native int[] getBidSizeBook();
	public native float[] getOfferValueBook();
	public native int[] getOfferSizeBook();
	
	public void getBook() {
		
		float bidValue[] = getBidValueBook();
		int bidSize[] = getBidSizeBook();
		float offerValue[] = getOfferValueBook();
		int offerSize[] = getOfferSizeBook();
		
		this.symbol = getSymbolBook();
		for(int i=0; i<10; i++) {
			this.setBid(i, bidSize[i], bidValue[i]);
			this.setOffer(i, offerSize[i], offerValue[i]);
		}
		
		return;
	}
	public String getSymbol() {
		return symbol;
	}
	public bidOffer getBid(int i) {
		return bid[i];
	}
	public bidOffer getOffer(int i) {
		return offer[i];
	}
		
	public void setSymbol(String s) {
		symbol = s;
	}
	public void setBid(int i, int s, float v) {
		bid[i].setSize(s);
		bid[i].setValue(v);
	}
	public void setOffer(int i, int s, float v) {
		offer[i].setSize(s);
		offer[i].setValue(v);
	}
		
};
