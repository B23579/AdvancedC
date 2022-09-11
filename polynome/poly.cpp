#include <iostream>
#include <map>
#include <string>
#include<vector>
using namespace std;
#include<cstring>

class Expr {

  private:

  double cons=0;

  class Var {
      private:
      string name_;
      vector<Expr> coef; // the coefficiants should be in order, from degre 0 to the maximun
      public:
      void setLabel(string val){ // record the name of the variable
       this->name_ = val;
        }
        
      void addCoef(Expr cof ){ // to collect a variable coeficiant
         this->coef.push_back(cof);
       }

    vector<Expr>& return_var_coeffs() {return coef;} // to return the variable coefficiants
    
    string name() {return this->name_;} //return variable name
    };

  vector<Var> variable={}; // to record the vector of variable
 

  public:
  void setExpr(double cons){
    this->cons = cons;
  }

  double get_const() const {return this->cons;}; // to return the constance when the expression is a constance or have a constance expression. 

  void setExpr(string label){
      Var x;
      x.setLabel(label);
      this->variable.push_back(x);
    }

    void set_coeffs(vector<Expr>& exp, int index) {
          for(Expr element : exp){
              this->variable[index].addCoef(element);
          }
    }

     map<int,Expr> get_coeffs(Var& x) const {
          map<int,Expr> expr;
          vector<Expr> coef=x.return_var_coeffs();
          int n= coef.size();

          for(int i=0;i<n;i++){
               expr.insert(pair<int,Expr>(i,coef[i]));
            }
          return expr;
      }

    vector<Var> get_variables()const {return this->variable;};
    int get_number_of_variable() const { return this->variable.size();};


    friend ostream& operator<<(ostream& os, const Expr& v)
    {
        int n=v.get_number_of_variable();

        if(n==0){ // imply the expression is the constance
            if(v.get_const()<0){
                cout<< " ";
            os << v.get_const();
            }
            else{
                cout<<" + ";
                os << v.get_const();
            }
            return os;

        }
        else
        {
            vector<Var> name= v.get_variables();
            
            for(int j=0;j<n;j++)
            {
                map<int,Expr> expr = v.get_coeffs(name[j]);
                
                int m=expr.size();

                for(int i=0;i<m;i++)
                {       
                    
                    if(expr[i].get_number_of_variable()>0){ // in the case we have somthing similar to (3-4*y)*x^n
                        cout<<" + (";
                        cout<<expr[i];
                        cout<<")";

                    }
                    else{
                        cout<<expr[i];
                    }
                    cout<<"*"<<name[j].name()<<"^"<<i;
                }
               
            }
            double b = v.get_const();
            if(b!=0){
                cout<<" + ";
                cout<<b;
            }
            
        return os;
        }
    }

    bool equivalent(const Expr& e1 , const Expr& e2) {
        // Let's compare the number of variables
        int n=e1.get_number_of_variable();
        int m=e2.get_number_of_variable();
        vector<Var> name1= e1.get_variables();
        vector<Var> name2= e2.get_variables();
     
        if(n!=m){return false;}
        else if(n==m)
            {
                for(int j=0;j<n;j++)
                {
                    map<int,Expr> expr1 = e1.get_coeffs(name1[j]);
                    map<int,Expr> expr2 = e2.get_coeffs(name2[j]);

                    int numb_coef1=expr1.size();
                    int numb_coef2=expr2.size();                    
                    if(numb_coef1!=numb_coef2){return false;}
                    else
                    {
                        
                        for(int i=0;i<numb_coef1;i++)
                        {
                            if(expr1[i].get_number_of_variable()>0 and (expr1[i].get_number_of_variable()==expr2[i].get_number_of_variable()))
                            { // in the case we have somthing similar to (3-4*y)*x^n
                                equivalent(expr1[i] ,expr2[i] );
                            }
                            else if (expr1[i].get_const()!=expr2[i].get_const()){ return false;}
                        
                            else if(expr1[i].get_number_of_variable()>1 and (expr1[i].get_number_of_variable()!=expr2[i].get_number_of_variable())) { return false;}         
                        } 

                    }
                }

            return true;
        }
        return false;
    }

   
    void expression(){

        // Representation de l'expression 2x
       
        vector<Var> name;
        Expr cont2;
        Expr cont1;
        Expr cont3;
        Expr cont4;
        Expr poly1;
        Expr poly2;

        cont2.setExpr(-2);
        cont1.setExpr(+1);
        cont3.setExpr(3);
        cont4.setExpr(-4);

        // Let's represent and  print f(y) = 3-4*y

        vector<Expr> val1{cont3,cont4};
        poly1.setExpr("y"); // y coef is -4
        poly1.set_coeffs(val1,0);
        cout<< " poly1 = " << poly1;
        cout<<endl;

        // Let's represent and print f(y) = -2x^0 + (3-4*y)*x^1 + 1*x^2.

        vector<Expr> val2{cont2,poly1, cont1};
        poly2.setExpr("x"); // y coef is -4
        poly2.set_coeffs(val2,0);
        cout<< " poly2 = "<< poly2;
        cout<<endl;
        cout<< endl;

        // Let's compare poly1 and poly1
        cout<<" Are ploy1 and poly1 equivalent? " << equivalent(poly1,poly1);
        cout<<endl;

        // Let's compare poly2 and poly2

        cout<<" Are poly2 and poly2 equivalent? " << equivalent(poly2,poly2);
        cout<<endl;

        // Let's compare poly1 and poly2

        cout<<" Are poly1 and poly2 equivalent? " << equivalent(poly1,poly2);
        cout<<endl;
    }
};



int main() {

  // Representation de l'expression 2x
    Expr poly;
    poly.expression();

  return 0;
} 