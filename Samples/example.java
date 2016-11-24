class BubbleSort{
    public static void main(String[] a){
	System.out.println(new BBS().Start(10));
    }
}

class BBS{
    
    int[] number ;
    int size ;		
    public int Start(int sz){	
	return sz ;
    } 
    
    public int Sort(){	
		int i;
		i = size - 1;
		while (i < size) {
			i = 1;
		} 
		return 0 ;
    }
}