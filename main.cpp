//
//  Польская запись
//
//  Created by Daniil Litvyakov on 18.11.2024.
//

#include "string_to_term.h"

using namespace std;

int main() { 
    string st;
    getline(cin,st);
    Vector<Term*> terms,terms2;
    terms = String_To_Terms(st);
    terms2 = Terms_to_Polish(terms);
    cout << endl<<"Result: " << ExecutePostfix(terms2)<<endl;

    /* Vector<Term*> terms;

    terms.push_back(new Number(5));
    terms.push_back(new Number(4));
    terms.push_back(new Operation('+'));
    terms.push_back(new Number(10));
    terms.push_back(new Number(9));
    terms.push_back(new Operation('-'));
    terms.push_back(new Operation('-'));
    

    cout << ExecutePostfix(terms);

    */
    return 0; }