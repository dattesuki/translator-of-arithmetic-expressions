//
//  Транслятор арифметических выражений
//
//  Created by Daniil Litvyakov on 18.11.2024.
//

#include "check.h"

using namespace std;


void FreeMemory(Vector<Term*> terms) {
    while (terms.size() != 0) {
        delete terms.back();
        terms.pop_back();
    }
}

bool Execute() {
    string st;
    Vector<Term*> terms, terms2;
    getline(cin, st);
    if (!check_bracket(st)) {
        cout << "Bad brackets";
        return false;
    }

    terms = String_To_Terms(st);

    if (check_terms(terms) == false) {
        cout << "Incorrect sequence in the expression!";
        FreeMemory(terms);
        return false;
    }

    try {
        terms2 = Terms_to_Polish(terms); //terms in polish
        cout << "\nResult: " << ExecutePostfix(terms2) << endl;
        FreeMemory(terms); //it is enough to delete only terms, because for terms2 there was no application of the new operator
        //FreeMemory(terms2);
        return true;
    }
    catch (...) {
        cout << "\nBad order";
        FreeMemory(terms);
        //FreeMemory(terms2);
        return false;
    }
}

int main() { 

    Execute();

    return 0; 
}


