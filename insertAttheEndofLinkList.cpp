#include<iostream>


class Node {

	public:

	int Value;
	Node* Next;
	
	};

void insertAtTheend(Node** head, int newValue){
	//1. Prepare a newNode
		Node* newNode = new Node();
		newNode->Value = newValue;
	//2. If linked lisk is empty, newNode will be a head node 
		if(*head ==NULL){	
			*head = newNode;
			return;
			}
		//3. Find the last node 
			Node* last = *head;
		while(last->Next !=NULL){
			last = last->Next;
			}

		//4. Insert newNode after last node(at the end)
		last->Next= newNode;
	}

void insertAtThefront(Node** head,int newValue){
	//1. Prepare a newNode
	Node* newNode = new Node();

	newNode->Value = newValue;

	//2. Put it in front of current head 
	newNode->Next = *head;
	
	// 3. Move head of the list to point to the newNode

	*head = newNode;
	}

void printlist(Node* n){ // this function need to receive the head element to print  
	while(n!=NULL){
		std::cout<<n->Value<<std::endl;
		n= n->Next;		
		}
	}

int main(){
	Node* head= new  Node(); //pointer to the firt element of the link list
	Node* second = new Node();
	Node* third = new Node();

	head->Value=1; //-> we use it when we are dealing with pointer
	head->Next = second; // we are linking the list here  
	second->Value=2;
	second->Next = third;
	third->Value = 3;
	third->Next=NULL; // because link is the last element of the list.  

	insertAtTheend(&head,4);
	printlist(head);
	return 0;
}
