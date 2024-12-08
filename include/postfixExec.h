//
//  
//
//  Created by Daniil Litvyakov on 18.11.2024.
//
#pragma once
#include "stack_queue.h"
#include <map>
#include "cmath"


std::map<char,int> Op_Priority{
    {'+', 1}, {'-',1}, {'*',2},{'/',2}, {'^',3}
};

enum types { number, operation, open_bracket, close_bracket, letter };

class Term{
protected:
    types type;
    virtual void foo() {};
    Term() {};
public:
    types GetType(){return type;}
};

class Number:public Term{
private:
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
public:
    char GetValue(){return op;}
    int GetPriority(){return priority;}
    Operation(char _op): op(_op){
        type = operation;
        priority = Op_Priority[op];
    }
};

class Open_Bracket:public Term{
    //int priority = 0;
public:
    //int GetPriority() { return priority; }
    Open_Bracket() {
        type = open_bracket;
    }
};


class Close_Bracket :public Term {
public:
    Close_Bracket() {
        type = close_bracket;
    }
};

class Letter :public Term {
    char value;
public:
    char GetValue() { return value; }
    Letter(char _value): value(_value) {
        type = letter;
    }
};


double Execute(Vector<Term*> terms) {
    types current_type;
    Stack<Term*> st;

    double temp1, temp2;


    for (size_t i = 0; i < terms.size(); ++i) {

        current_type = terms[i]->GetType();

        switch (current_type) {

        case(number): {
            st.push(new Number(dynamic_cast<Number*>(terms[i])->GetNumber()));
            break;
        }


        case (operation): {
            temp2 = dynamic_cast<Number*>(st.get())->GetNumber();
            delete st.get();
            st.pop();
            temp1 = dynamic_cast<Number*>(st.get())->GetNumber();
            delete st.get();
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
                if (temp2 == 0.0) throw std::string{ "DivideByZero" };
                st.push(new Number(temp1 / temp2));
                break;
            }
            case '^': {
                st.push(new Number(pow(temp1, temp2)));
                break;
            }

            }

        }

        }
    }


    return dynamic_cast<Number*>(st.get())->GetNumber();
}




