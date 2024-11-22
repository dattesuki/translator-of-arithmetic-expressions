//
//  
//
//  Created by Daniil Litvyakov on 18.11.2024.
//
#include "postfixExec.h"
#include <string>


bool IsOperator(char t) {
	if ((t == '+') || (t == '-') || (t == '*') || (t == '/')) return true;
	else return false;
}

bool IsNumeral(char t) {
	if ((t >= '0') && (t <= '9')) return true;
	else return false;
}

Vector<Term*> String_To_Terms(std::string input_string) {
	Vector<Term*> terms;

	double temp=0;
	int count=0;
	bool dot = false;
	int count_after_dot = 0;
	for (size_t i = 0; i < input_string.size(); ++i) {

		if (IsNumeral(input_string[i])) {
			if (dot == false) {
				temp *= 10;
				temp += (input_string[i] - '0');
			}
			else {
				temp += (input_string[i] - '0')/pow(10,(++count_after_dot));
			}
			count++;
		}
			if (input_string[i] == '.' || input_string[i] == ',') {
				dot = true;
			}
		
		if ((count != 0) && !(IsNumeral(input_string[i]))) {
			terms.push_back(new Number(temp));
			temp = 0;
			dot = false;
			count = 0;
			count_after_dot = 0;
		}
		

		if (IsOperator(input_string[i])) terms.push_back(new Operation(input_string[i]));

		if (input_string[i] == '(') terms.push_back(new Open_Bracket());

		if (input_string[i] == ')') terms.push_back(new Close_Bracket());

		}


	if (count != 0) {
		terms.push_back(new Number(temp));
	}


	return terms;
}






Vector<Term*> Terms_to_Polish(Vector<Term*>& V){
	Vector<Term*> terms;





}