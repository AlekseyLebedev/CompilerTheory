class BinarySearch{
    public static void main(String[] a){
	System.out.println(a);
    }
}

class MyVisitor extends Visitor {

    public int visit(Tree n){
	int nti ;

	if (n.GetHas_Right()){
	    r = n.GetRight() ;
	    nti = r.accept(this) ; }
	else nti = 0 ;

	System.out.println(n.GetKey());

	if (n.GetHas_Left()) {
	    l = n.GetLeft(); 
	    nti =l.accept(this) ; }
	else nti = 0 ;

	return 0;
    }

}
