//
//  Транслятор арифметических выражений
//
//  Created by Daniil Litvyakov on 18.11.2024.
//

#include "check.h"

using namespace std;

void Execute() {
    string st;
    getline(cin, st);
    try {
        check_bracket(st);
    }
    catch (...) {
        cout << "Bad brackets";
    }

    Vector<Term*> terms, terms2;
    try {
    terms = String_To_Terms(st);
    terms2 = Terms_to_Polish(terms);
        cout << endl << "Result: " << ExecutePostfix(terms2) << endl;
    }
    catch (...) {
        cout << "\nBad order";
    }
}

int main() { 

    Execute();

    return 0; 
}

