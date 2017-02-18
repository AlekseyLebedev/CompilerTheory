


int main() {
	int* a = new int [5];
	int b = 1;
	a[1] = 2;
	b = a[2];
	delete a;
	
	return 0;
}