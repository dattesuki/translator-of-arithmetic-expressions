﻿//
//  
//
//  Created by Daniil Litvyakov on 18.11.2024.
//
#pragma once
#include "string_to_term.h"


bool IsOpenBracket(char t) {
    if ((t == '(') || (t == '[') || (t == '{')) return 1;
    return 0;
}

bool IsCloseBracket(char t) {
    if ((t == ')') || (t == ']') || (t == '}')) return 1;
    return 0;
}

char GetOpenBracket(char t) {
    if (t == ')') return '(';
    if (t == ']') return '[';
    if (t == '}') return '{';
    return 0;
}

bool check_bracket(std::string Expression) {
    Stack<char> st;

    for (int i = 0; i < Expression.length(); i++) {
        if (IsOpenBracket(Expression[i])) {
            st.push(Expression[i]);
        }
        if (IsCloseBracket(Expression[i])) {
            if (st.IsEmpty()) return false;
            else {
                if (st.get() != GetOpenBracket(Expression[i])) return false;
                else {
                    if (st.IsEmpty() == 0) (st.pop());
                    else return false;
                }
            }
        }
    }

    if (st.IsEmpty() != 1) { return false; }

    return true;
}


std::map<types, char> type_status{
    {number,0},{letter,0}, {operation, 1} , {open_bracket,2},{close_bracket ,3}
};


bool check_terms(Vector<Term*> terms) {
    char status=0;
    status = type_status[terms[0]->GetType()];
    for (size_t i = 1; i < terms.size(); ++i) {
        if (status == 0 || status == 3) {
            if (type_status[terms[i]->GetType()] == 0 || type_status[terms[i]->GetType()] == 2) return false;
            else status = type_status[terms[i]->GetType()];
        }
        
        else{
            if ((type_status[terms[i]->GetType()] == 1) || (type_status[terms[i]->GetType()] == 3)) return false;
            else status = type_status[terms[i]->GetType()];
        }
    }
    if ((terms.back()->GetType() == operation) || (terms.back()->GetType() == open_bracket)) return false;
    return true;
}