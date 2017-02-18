class Main{
    public static void main(String[] a) {
	System.out.println(new A().A1());
    }
}

class A {

	public int A1() {
		int b;
		int[] c; 
		int e;		
		c = new int[4];					
		c[1] = 5;
		b = c[2];
		e = c.length;
		return 0;
	}
	
	public int A3() {
		int a;					
		a = 5;
		if (a<4) {
			while (a < 8){
				a = a+1;
			}
			a = 9;
		} else {
			a = 8;
		}
		return 7;
	}
}
