//
//  main.cpp
//  Польская запись
//
//  Created by Daniil Litvyakov on 18.11.2024.
//

#include <iostream>
//#include "stack_queue.h"
#include "stack"
#include <map>
using namespace std;

map<char,int> Op_Priority{
    {'+', 1}, {'-',1}, {'*',2},{'/',2}
};


enum types{number, operation, open_bracket,close_bracket};

class Term{
protected:
    types type;
public:
    virtual char GetValue()=0;
    virtual double GetNumber()=0;
    types GetType(){return type;}
    Term(){}
    //virtual ~Term(){};
};

class Number:public Term{
private:
    char GetValue(){return '0';};
    double Value;
public:
    double GetNumber(){return Value;}
    Number(double _Value = 0.0):Value(_Value){
        type = number;
    }
};

class Operation:public Term{
    char op;
    int priority;
    double GetNumber(){return 5;};
public:
    char GetValue(){return op;}
    int GetPriority(){return priority;}
    Operation(char _op): op(_op){
        type = operation;
    }
};

class Open_Bracket:public Term{
    char bracket;
public:
    Open_Bracket(): bracket('('){
        type = open_bracket;
    }
};

class Close_Bracket:protected Term{
    char bracket;
public:
    Close_Bracket(): bracket(')'){
        type = close_bracket;
    }
    
    
};




int main() {
    vector<Term*> terms;
    types current_type;
    stack<Term*> st;
   
    terms.push_back(new Number(5));
    terms.push_back(new Number(4));
    terms.push_back(new Operation('+'));
    terms.push_back(new Number(10));
    terms.push_back(new Number(9));
    terms.push_back(new Operation('-'));
    terms.push_back(new Operation('-'));
    
    double temp1, temp2;
    
    for (size_t i = 0; i<terms.size(); ++i){
        current_type = terms[i]->GetType();
        
        switch(current_type){
            case(number):{
                st.push(terms[i]);
                break;
            }
            case (operation):{
                switch (terms[i]->GetValue()) {
                    case '+':{
                        temp2=st.top()->GetNumber();
                        st.pop();
                        temp1=st.top()->GetNumber();
                        st.pop();
                        st.push(new Number(temp1+temp2));
                        break;
                    }
                    case '-':{
                        temp2=st.top()->GetNumber();
                        st.pop();
                        temp1=st.top()->GetNumber();
                        st.pop();
                        st.push(new Number(temp1-temp2));
                        break;
                    }
                }
                
                
                
                
            }
             
                
        }
        
    }
    cout<<"Результат: "<<st.top()->GetNumber()<<endl;
    return 0;
}

//сделать dynamic cast приведение типа Terms к number!!!!!
//чтобы без абстрактного
//https://www.cyberforum.ru/cpp-beginners/thread1875202.html?ysclid=m3mt5yzlq0276544909
