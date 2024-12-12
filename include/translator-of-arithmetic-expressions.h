#pragma once
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
    catch (std::string error) {
        std::cout <<error;
        FreeMemory(terms);
        //FreeMemory(terms2);
        return false;
    }
    catch (...) {
        std::cout << "\nBad order";
        FreeMemory(terms);
        //FreeMemory(terms2);
        return false;
    }
}



void ExecuteFewExpressions() {
    std::string st;
    Vector<Term*> terms, terms2;
    std::cout << "Enter a new arithmetic expression in a new line\nIf you want to stop typing, enter 0\n\n";
    getline(std::cin, st);
    
    while (st != "0") {
        if (!check_bracket(st)) {
            std::cout << "Bad brackets";
            continue;
        }

        terms = String_To_Terms_with_few_expressions(st);

        if (check_terms(terms) == false) {
            std::cout << "Incorrect sequence in the expression!";
            FreeMemory(terms);
        }

        try {
            terms2 = Terms_to_Polish(terms); //terms in polish
            std::cout << "Result: ";
            std::cout << Execute(terms2) << std::endl;
            FreeMemory(terms); //it is enough to delete only terms, because for terms2 there was no application of the new operator
        }
        catch (std::string error) {
            std::cout << error;
            FreeMemory(terms);
        }
        //catch (...) {
          //  std::cout << "Bad order";
            //FreeMemory(terms);
        //}
        std::cout << std::endl;
        st = std::string();
        while(st=="") getline(std::cin, st);
    }
}
