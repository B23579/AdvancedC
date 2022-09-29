#include<iostream>
#include<string>

using namespace std;

class Person{
    private: 
        int Age;
        string Name;
    public:
        Person(){}
        Person(int age, string name){
            Age = age;
            Name = name;
            cout<< "Normal constructor"<< "\n";
        }

        Person(Person &p){
            Age =p.Age;
            Name = p.Name;
            cout<<"Copy constructor"<< "\n";
        }

        Person& operator=(Person &p){
            Age = p.Age;
            Name = p.Name;
            cout<<"copy assigment"<<"\n";
            return *this;
        }

    Person& operator=(Person&& p){
        this->Age = p.Age;
        this->Name = p.Name;
        cout<<"move assigment" << endl;
        return *this;

    }
    void getAge(int age){
        Age=age;
    }

    void getName(string name){
        Name = name;
    }

    friend ostream& operator<<(ostream& os, Person &p){
        os<<p.Age << " "<<p.Name<<endl;
        return os;
    }

};


int main(){
    Person b(23,"tot");
    cout<<b << endl;
    Person f(b);
    cout<<f<<endl;
    f.getAge(78);
    f.getName("tobi");
    cout<<f<<endl;
    Person o;
    o= b;
    cout<<o<<endl;
    o=move(b);
    cout<<o<<endl;
    return 0;
}