class Main{
    public static void main(String[] a) {
	System.out.println(new A().A4());
    }
}

class A {

	// public int A1() {
		// int b;
		// int[] c; 
		// int e;		
		// c = new int[4];					
		// c[1] = 5;
		// b = c[2];
		// e = c.length;
		// return 0;
	// }
	
	// public int A2() {
		// int a;					
		// a = 5;
		// if (a<4) {
			// while (a < 8){
				// a = a+1;
			// }
			// a = 9;
		// } else {
			// a = 8;
		// }
		// return 7;
	// }
	
	// public int A3(int n) {
		// boolean b1;
		// boolean b2;
		// b1 = false;
		// b2 = true;
		// int a;
		// a = 0;
		// if (b2) {
			// a = 1;
		// } else {
			// a = 2;
		// }
		// if (b1) {
			// a = 3;
		// }
		// while (a < 5) {
			// b1 = true;
			// a = a + 1;
		// }
		// return 999;
	// }
	
	public int A4() {
		return 0;
	}
	
	// public int A5() {
		// int a;					
		// a = 5;
		// if (a<4) {
			// while (a < 8){
				// a = a+1;
			// }
			// a = 9;
		// } else {
			// a = 8;
		// }
		// return 7;
	// }
	
	public int A3(int n) {
		boolean b1;
		boolean b2;
		int a;
		b1 = false;
		b2 = true;		
		a = 0;
		if (b2) {
			a = 1;
		} else {
			a = 2;
		}
		if (b1) {
			a = 3;
		} else {
			a = 2;
		}
		while (a < 5) {
			b1 = true;
			a = a + 1;
		}
		return 999;
	}
}
