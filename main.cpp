#include <iostream>
#include <stdlib.h>
#include "LLC.cpp"

using namespace std;

int main(){
	LLC<string> myList;

	for (int i = 0; i < 10; i++){ 
		cout << myList.insert(to_string(i)) << endl;	//make it string(i)
		cout << myList << endl;
		cout << myList.len() << endl;;
	}

	for (int i = 0; i < 11; i++){
		myList.head(i);
	}

	cout << endl << "cout funct: " << myList <<endl;

	cout << "contains 1:  " << myList.contains("1") << endl;
	cout << "contains 10: " << myList.contains("10") << endl;
	
	LLC<string> myList2;

	for (int i=10;i<20;i++){
		cout << myList2.insert(to_string(i)) << endl;
	}

//	LLC<string> myList3;
//	myList3 = myList + myList2;
//	cout << myList3 << endl;


	myList.tail();
	myList.join(myList2);
	myList2 = myList;
	cout << myList << endl;
	cout << myList2 << endl;

//	myList+=1;
	myList.insert("5");
	cout << myList << endl;
	//myList.remove("5");
	cout << myList << endl;	
	//myList.remove("0");
	cout << myList << endl;	

	cout << "Contain funct: " << myList.contains("1") << myList.contains("a")<< endl;

	cout << "tail funct: ";
	myList.tail();

	myList.shuffle();
	cout << myList << endl;

	return 0;
}
