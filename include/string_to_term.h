//
//  
//
//  Created by Daniil Litvyakov on 18.11.2024.
//
#include "postfixExec.h"
#include <string>


struct Letters {
	unsigned int UpperCase : 26;
	unsigned int LowerCase : 26;
	Letters() :UpperCase(0), LowerCase(0) {};
};





bool IsOperator(char t) {
	if ((t == '+') || (t == '-') || (t == '*') || (t == '/') || (t == '^')) return true;
	else return false;
}

bool IsNumeral(char t) {
	if ((t >= '0') && (t <= '9')) return true;
	else return false;
}

Vector<Term*> String_To_Terms(std::string input_string) {
	Vector<Term*> terms;
	Letters A;

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
			if (dot == true) throw std::logic_error("double dot");
			dot = true;
		}
		
		if ((count != 0) && !(IsNumeral(input_string[i])) && (input_string[i] != '.') && (input_string[i] != ',')) {
			terms.push_back(new Number(temp));
			temp = 0;
			dot = false;
			count = 0;
			count_after_dot = 0;
		}
		

		if (IsOperator(input_string[i])) terms.push_back(new Operation(input_string[i]));

		if (input_string[i] == '(') terms.push_back(new Open_Bracket());

		if (input_string[i] == ')') terms.push_back(new Close_Bracket());

		if ((input_string[i]) >= 65 && (input_string[i] <= 90)) {
			terms.push_back(new Letter(input_string[i]));
			A.UpperCase |= (1 << (input_string[i] - 65));
		}

		if ((input_string[i]) >= 97 && (input_string[i] <= 122)) {
			terms.push_back(new Letter(input_string[i]));
			A.LowerCase |= (1 << (input_string[i] - 97));
		}

		}


	//���� ����� �� ��������� �����
	if (count != 0) {
		terms.push_back(new Number(temp));
	}



	double temp_cin;
	std::map<char,double> MapLetter;
	if ((A.LowerCase != 0) || (A.UpperCase != 0)) {
		std::cout << "\nInitialize the variables:\n";
		for (int i = 0; i < 26; ++i) {
			if (A.UpperCase & (1 << i)) {
				std::cout << char(65 + i) << " = ";
				std::cin >> temp_cin;
				MapLetter[char(65 + i)] = temp_cin;
			}
		}
		for (int i = 0; i < 26; ++i) {
			if (A.LowerCase & (1 << i)) {
				std::cout << char(97 + i) << " = ";
				std::cin >> temp_cin;
				MapLetter[char(97 + i)] = temp_cin;
			}
		}
		//������ ���� �� ����� � ������� ������(������)
		for (int i = 0; i < terms.size(); ++i) {
			if (terms[i]->GetType() == letter) {
				terms[i] = new Number(MapLetter[dynamic_cast<Letter*>(terms[i])->GetValue()]);
			}
		}

	}



	return terms;
}






Vector<Term*> Terms_to_Polish(Vector<Term*> old_terms){
	Vector<Term*> terms;
	Stack<Term*> st;
	for (size_t i = 0; i < old_terms.size(); ++i) {
		//���� �������
		if ((old_terms[i]->GetType() == number) || (old_terms[i]->GetType() == letter)) {
			terms.push_back(old_terms[i]);
		}

		//���� ��������
		if (old_terms[i]->GetType() == operation){
			while (!(st.IsEmpty())) {
				if ((dynamic_cast<Operation*>(old_terms[i])->GetPriority()) <= (dynamic_cast<Operation*>(st.get())->GetPriority())) {
					terms.push_back(st.get());
					st.pop();
				}
				else break;
			}
			st.push(old_terms[i]);
		}

		//���� ������
		if (old_terms[i]->GetType() == open_bracket) {

		}

		if (old_terms[i]->GetType() == close_bracket) {

		}
	}

	while ((!(st.IsEmpty()))) {
		terms.push_back(st.get());
		st.pop();
	}

	return terms;
}



	




void Execute() {
	using namespace std;
	string st;
	getline(cin, st);
	Vector<Term*> terms, terms2;
	terms = String_To_Terms(st);
	terms2 = Terms_to_Polish(terms);
	cout << endl << "Result: " << ExecutePostfix(terms2) << endl;
}