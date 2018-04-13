#include <iostream>

using namespace std;


class Copy{
public:
	Copy(int b){
		for(int i = 0 ;i < sizeof(arr)/sizeof(int); i++ ){
			arr[i] = b + i;
		}
	}

	void Print(){
		for(int i = 0 ;i < sizeof(arr)/sizeof(int); i++ ){
			cout << arr[i] ;	
		}	
		cout << endl;
	}

	int arr[10];

};


int main(){
	
	int a5[5] = {5};
	auto b5 = a5;

	typedef int TChar[5];
	TChar c5(a5);
	for(int i = 0 ;i < 5; i++ ){
		cout << a5[i] << "," ;	
	}	
	cout << endl;

	for(int i = 0 ;i < 5; i++ ){
		cout <<  b5[i] << "," ;	
	}	
	cout << endl;


	Copy a(1);
	a.Print();
	Copy b = a;
	b.Print();
	return 0;
}