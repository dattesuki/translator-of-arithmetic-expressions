//
//  Транслятор арифметических выражений
//
//  Created by Daniil Litvyakov on 18.11.2024.
//

#include "check.h"

using namespace std;

double Execute() {
    string st;
    Vector<Term*> terms, terms2;
    getline(cin, st);
    try {
        check_bracket(st);
    }
    catch (...) {
        cout << "Bad brackets";
    }

    terms = String_To_Terms(st);

    if (check_terms(terms) == false) cout << "Error!";
    else {
        try {
            terms2 = Terms_to_Polish(terms);
            cout << "\nResult: "<<ExecutePostfix(terms2)<<endl;
        }
        catch (...) {
            cout << "\nBad order";
            return 0;
        }
    }
}

int main() { 

    Execute();

    return 0; 
}

