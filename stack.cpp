#include<iostream>

#include<stack>

// stack is LIFO collection 

void printstackelement(std::stack<int> stack){
	// this funtion ask for the top elment on the stack and pop it again and again untill stack is empty


	while( !stack.empty()){
		std:: cout<<  stack.top()<<std::endl;
		stack.pop();
		}
	
	}

int main(){
	// function empty, size, push, pop, top 

	std::stack<int> numberStack;

	numberStack.push(1);
	numberStack.push(6);
	numberStack.push(5); // push function is use to add element on the stack 


	if(numberStack.empty())
		std::cout<< "Stack is empty"<< std::endl;

	else
		std::cout << "Stack is not empty"<<std::endl;

		std::cout<<"Size of stack is "<< numberStack.size()<<std::endl;


	std:: cout<<"Let's  remove elment on the stack "<< std:: endl;

	numberStack.pop(); // pop remouve elment of the stack

	std:: cout<< " size of stack is  " <<  numberStack.size()<<std::endl; 

	std::cout<<"Let's print the elements in the stack " << std::endl;

	printstackelement(numberStack);
}
