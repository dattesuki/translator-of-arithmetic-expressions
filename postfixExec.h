//
//  Польская запись
//
//  Created by Daniil Litvyakov on 18.11.2024.
//


#include "stack_queue.h"
#include <map>



std::map<char,int> Op_Priority{
    {'+', 1}, {'-',1}, {'*',2},{'/',2}, {'^',2}
};

enum types { number, operation, open_bracket, close_bracket, letter };

class Term{
protected:
    types type;
    virtual void foo()=0;
public:
    types GetType(){return type;}
    Term() {};
};

class Number:public Term{
private:
    void foo() {};
    double Value;
public:
    double GetNumber(){return Value;}
    Number(double _Value = 0.0):Value(_Value){
        type = number;
    }
};

class Operation:public Term{
    void foo() {};
    char op;
    int priority;
public:
    char GetValue(){return op;}
    int GetPriority(){return priority;}
    Operation(char _op): op(_op){
        type = operation;
        priority = Op_Priority[op];
    }
};

class Open_Bracket:public Term{
    void foo() {};
public:
    Open_Bracket() {
        type = open_bracket;
    }
};


class Close_Bracket :public Term {
    void foo() {};
public:
    Close_Bracket() {
        type = close_bracket;
    }
};

class Letter :public Term {
    void foo() {};
    char value;
public:
    char GetValue() { return value; }
    Letter(char _value): value(_value) {
        type = letter;
    }
};


double ExecutePostfix(Vector<Term*> terms) {
    types current_type;
    Stack<Term*> st;

    double temp1, temp2;


    for (size_t i = 0; i < terms.size(); ++i) {

        current_type = terms[i]->GetType();

        switch (current_type) {

        case(number): {
            st.push(terms[i]);
            break;
        }


        case (operation): {
            temp2 = dynamic_cast<Number*>(st.get())->GetNumber();
            st.pop();
            temp1 = dynamic_cast<Number*>(st.get())->GetNumber();
            st.pop();

            switch (dynamic_cast<Operation*>(terms[i])->GetValue()) {
            case '+': {
                st.push(new Number(temp1 + temp2));
                break;
            }
            case '-': {
                st.push(new Number(temp1 - temp2));
                break;
            }
            case '*': {
                st.push(new Number(temp1 * temp2));
                break;
            }
            case '/': {
                st.push(new Number(temp1 / temp2));
                break;
            }
            case '^': {
                st.push(new Number(pow(temp1,temp2)));
                break;
            }

            }

        }

        }
    }


    return dynamic_cast<Number*>(st.get())->GetNumber();
}




