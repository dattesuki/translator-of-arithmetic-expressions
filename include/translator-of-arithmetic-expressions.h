#include "check.h"


void FreeMemory(Vector<Term*> terms) {
    while (terms.size() != 0) {
        delete terms.back();
        terms.pop_back();
    }
}

bool Execute() {
    std::string st;
    getline(std::cin, st);
    Vector<Term*> terms, terms2;
    if (!check_bracket(st)) {
        std::cout << "Bad brackets";
        return false;
    }

    terms = String_To_Terms(st);

    if (check_terms(terms) == false) {
        std::cout << "Incorrect sequence in the expression!";
        FreeMemory(terms);
        return false;
    }

    try {
        terms2 = Terms_to_Polish(terms); //terms in polish
        std::cout << "\nResult: ";
        std::cout << Execute(terms2) << std::endl;
        FreeMemory(terms); //it is enough to delete only terms, because for terms2 there was no application of the new operator
        //FreeMemory(terms2);
        return true;
    }
    catch (...) {
        std::cout << "\nBad order";
        FreeMemory(terms);
        //FreeMemory(terms2);
        return false;
    }
}
