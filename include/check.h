//
//  
//
//  Created by Daniil Litvyakov on 18.11.2024.
//
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

void check_bracket(std::string Expression) {
    Stack<char> st;

    for (int i = 0; i < Expression.length(); i++) {
        if (IsOpenBracket(Expression[i])) {
            st.push(Expression[i]);
        }
        if (IsCloseBracket(Expression[i])) {
            if (st.IsEmpty()) throw std::logic_error("bad brackets");
            else {
                if (st.get() != GetOpenBracket(Expression[i])) throw std::logic_error("bad brackets");
                else {
                    if (st.IsEmpty() == 0) (st.pop());
                    else throw std::logic_error("bad brackets");
                }
            }
        }
    }

    if (st.IsEmpty() != 1) { throw std::logic_error("bad brackets"); }
}




