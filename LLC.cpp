#include <iostream>
#include <stdlib.h>

using namespace std;


template <typename ElementType>
class LLC{
	public:
		LLC();
		//LLC(const ElementType & str);
		LLC(const LLC<ElementType>& list);
		~LLC();
		void operator=(LLC<ElementType>& list);
//		LLC operator+(LLC& list);
//		void operator+=(int n);
		bool contains(const ElementType & str);
		bool insert(const ElementType & str);
		void remove(const ElementType & str); 
		ElementType popFirst();
		void shuffle();
		void head(int n);
		ElementType tail();
		template <typename ElementType2>
		friend ostream& operator<<(ostream& os, LLC<ElementType2>& list);
		int len();
		void join(LLC<ElementType> other);
		bool nonEmpty();
		
		//template <typename ElementType2>
		class Node{
			public:
				Node();
				Node(ElementType str);
				void deleteNext();
				void deleteAll();
				Node tail();
				void operator=(const Node &node);
				ElementType data;
				Node *next;
		};
		Node *first;
		Node *last;
};



template <typename ElementType>
LLC<ElementType>::LLC(){
	first = new Node();
}

template <typename ElementType>
LLC<ElementType>::LLC(const LLC<ElementType> & list){
	Node *temp = list.first;
	Node *prev = nullptr;
	while (temp != nullptr){
		Node * pos = new Node();
		pos->data = temp->data;
		pos->next = nullptr;
		if (prev == nullptr){
	 		first = pos;
		}else{
			prev->next = pos;
		}
		last = pos;
		temp = temp->next;
		prev = pos;
	}
}

/*A destructor that frees the entire list*/
template <typename ElementType>
LLC<ElementType>::~LLC(){
	if (first == nullptr){
		first->deleteAll();
	}
}

template <typename ElementType>
LLC<ElementType>::Node::Node(){
	//data = NULL;
	next = nullptr;
}

/*Deletes the next value in the linked list, then referenced to the one after*/
template <typename ElementType>
void LLC<ElementType>::Node::deleteNext(){
	Node *temp = this->next;
	next = next->next;
	delete temp;
}

/*destructor that frees the entire list*/		//recursive call DEBUG TODO
template <typename ElementType>
void LLC<ElementType>::Node::deleteAll(){
	Node *pos = next;
	if(pos != nullptr){
		pos->deleteAll();
	}
	delete this;
}

template <typename ElementType>
LLC<ElementType>::Node::Node(ElementType str){
	data = str;
	next = nullptr;
}

template <typename ElementType>
void LLC<ElementType>::Node::operator=(const Node & node){
	data = node.data;
	next = node.next;
}

/*takes another LLC object as a parameter, makes a copy of the list it contains, 
and stores the copy in the LLC object on the left side of the =. 
Any elements in the list being assigned to should be destroyed (i.e they should 
be deleted and no longer found in LLC object on the left side of the = operator).*/
template <typename ElementType>
void LLC<ElementType>::operator=(LLC<ElementType> &list){
	first->deleteAll();
	Node *temp = list.first;
	Node *prev = nullptr;
	while (temp != nullptr){
		Node * pos = new Node();
		pos->data = temp->data;
		pos->next = nullptr;
		if (prev == nullptr){
	 		first = pos;
		}else{
			prev->next = pos;
		}
		last = pos;
		temp = temp->next;
		prev = pos;
	}
}

/*makes a new list that includes copies of the elements in the two operand lists.*/
//template <typename ElementType>
/*LLC<ElementType> LLC<ElementType>::operator+(LLC<ElementType>& list){					//TODO
	LLC<ElementType> listCopy;
	listCopy.join(*this);
	listCopy.join(list);
	return listCopy;
}
*/
/*takes an integer parameter (say n), and moves the first item of the list to the 
end of the list, n times. So a list that begins as: [one, two, three, four] and 
then carries out mylist += 2; would become: [three, four, one, two]*/
//template <typename ElementType>
/*void LLC<ElementType>::operator+=(int n){					//TODO
	LLC<ElementType> retVal1;
	LLC<ElementType> retVal2;
	Node<ElementType> *pos = first;
	for(int i = 0; i<n; i++){
		retVal1.insert(pos->next->data);
		pos = pos->next;
	}
	while(pos->next != nullptr){
		retVal2.insert(pos->next->data);
	}

	retVal2.join(retVal1);
	*this = retVal2;
}
*/
/*ElementType as a parameter and returns True if the string is in the list, False otherwise*/
template <typename ElementType>
bool LLC<ElementType>::contains(const ElementType & str){				//DONE
	Node *pos = first;

	while (pos->next != nullptr) {
		if (pos->next->data ==str) return true;
		pos = pos->next;
	} return (pos->data == str);
}

/*inserts a copy of the ElementType passed as a parameter, into the “back” of the list (that is, after the element pointed to by last or tail), returning True if the string is inserted successfully, False (not expected) otherwise*/
template <typename ElementType>
bool LLC<ElementType>::insert(const ElementType & str){				//DONE
	/*if(!nonEmpty()) {
		first->data = str;
		last = first;
		if (last != first) return false;
	}*/
	//else {
		Node *pos = first;
		while(pos->next != nullptr){
			pos = pos->next;
		}
		pos->next = new Node();
		pos->next->data = str;
		last = pos->next;
		if (last != pos->next) return false;
	//}
	return true;
}

template <typename ElementType>
ElementType LLC<ElementType>::popFirst(){
	ElementType retVal = first->next->data;
	Node *temp = first;
	first = first->next;
	delete temp;
	return retVal;
}

/*removes all ElementTypes that match the parameter, from the list*/
template <typename ElementType>
void LLC<ElementType>::remove(const ElementType & str){				//DONE
	Node *pos = first; 
	while(pos->next->next != nullptr){	
		if(first->next->data == str){
		popFirst();
		}
		else if(pos->next->data == str) {
			pos->deleteNext();
		}
		pos = pos->next;
	}
	if (last->data == str){	
		last = pos;
		last->deleteNext();
	}

}

/*shuffles list, creates new empty list, and then randomizes the order of each element in original list, then reassignes the old list to the new list*/	
template <typename ElementType>
void LLC<ElementType>::shuffle(){								//DONE
	LLC<ElementType> *newList = new LLC<ElementType>();
	for (int N = len(); N >0; N--)// &&(len() >= 1))
	{
		LLC<ElementType>::Node * pos = first;
		int j = rand() % N;
		for (int i = 1; i < j+1; i++){
//			cout << i << " " << j << " " <<  pos->next->data << endl;
			pos = pos->next;
		}
//		cout << "a" << endl;
		if(first != pos){
		newList->insert(pos->next->data);
		pos->deleteNext();
		}
		else newList->insert(popFirst());
//		cout << *newList << endl << *this << endl;
	}
	
	for (int N = newList->len(); N>0; N--){
		insert(newList->popFirst());
	}
}

/*method that prints the first n ElementType in the list, with the following format: 
 * [ElementType1, ElementType, ElementType3, … , ElementTypeN]*/			
 													//DONE
template <typename ElementType>
void LLC<ElementType>::head(int n){
	if (n > len()){
		cout << "NUMBER LARGER THAN LENGTH" << endl;
	}
	Node *pos = first;
	string retVal = "[";
	for (int i = 0; (i< n) && (pos != last); i++){
		retVal += pos->next->data;
		if (pos->next !=nullptr) pos = pos->next;
		if (pos != last && i < n-1) retVal += ", ";
	}
	retVal += "]";
	cout << retVal << endl;
}

/*prints and returns copy of last ElementType of list*/
template <typename ElementType>
ElementType LLC<ElementType>::tail(){						//DONE
	cout << last->data << endl;
	return last->data;
}
								//DONE
//overloaded friend funct for <<//outputs the entire list, in the same format as head()
//ex	https://msdn.microsoft.com/en-us/library/1z2f6c2k.aspx	//TODO fix
template <typename ElementType>
ostream& operator<<(ostream& os, LLC<ElementType> &list){
	os << "[";
	int i = 0;
	int n = list.len();
	for (typename LLC<ElementType>::Node *pos = list.first;pos->next != nullptr; pos = pos->next){
		os << pos->next->data;
		if (pos != list.last && i <n-1) os<< ", ";
		i++;
	}
	os << "]";
	return os;
}

/*method that returns the number of elements in the list*/	//DONE
template <typename ElementType>
int LLC<ElementType>::len(){
	if (first->next == nullptr) return 0;
	Node *pos = first;
	int i = 0;
	while(pos->next != nullptr){
		i++;
		pos = pos->next;
	} return i;
}

/*function that causes all elements of other to be moved into this list*/	
template <typename ElementType>
void LLC<ElementType>::join(LLC<ElementType> other){				//DONE
	Node *pos = other.first;
	while (pos->next != nullptr){
		insert(pos->next->data);
		pos = pos->next;
	}
}



template <typename ElementType>
bool LLC<ElementType>::nonEmpty(){
	return (first == nullptr);
}
