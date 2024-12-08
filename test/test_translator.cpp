#include "translator-of-arithmetic-expressions.h"
#include <gtest.h>
//#include <sstream> // to std::istringstream

TEST(Check, last_operation) {
	testing::internal::CaptureStdout();
	std::istringstream MyInput("5.5 + 4.5 + ");
	std::streambuf* originalCinBuffer = std::cin.rdbuf();
	std::cin.rdbuf(MyInput.rdbuf());
	Execute();
	std::cin.rdbuf(originalCinBuffer);
	std::string output1 = testing::internal::GetCapturedStdout();
	testing::internal::CaptureStdout();
	std::cout << "Incorrect sequence in the expression!";
	std::string output2 = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output1, output2);

	//input:5.5 + 4.5 +
	//output:Incorrect sequence in the expression!
}

TEST(Check, divided_by_zero) {
	testing::internal::CaptureStdout();
	std::istringstream MyInput("5.5 / 0 ");
	std::streambuf* originalCinBuffer = std::cin.rdbuf();
	std::cin.rdbuf(MyInput.rdbuf());
	Execute();
	std::cin.rdbuf(originalCinBuffer);
	std::string output1 = testing::internal::GetCapturedStdout();
	testing::internal::CaptureStdout();
	std::cout << "\nResult: DivideByZero";
	std::string output2 = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output1, output2);

	//input:5.5 / 0
	//output:Incorrect sequence in the expression!
}

TEST(Check, only_open_bracket) {
	testing::internal::CaptureStdout();
	std::istringstream MyInput("(5.5 + 4.5"); 
	std::streambuf* originalCinBuffer = std::cin.rdbuf();
	std::cin.rdbuf(MyInput.rdbuf()); 
	Execute();
	std::cin.rdbuf(originalCinBuffer); 
	std::string output1 = testing::internal::GetCapturedStdout();
	testing::internal::CaptureStdout();
	std::cout << "Bad brackets";
	std::string output2 = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output1, output2);

	//input:(5.5 + 4.5
	//output:Bad brackets
}

TEST(Check, only_close_bracket) {
	testing::internal::CaptureStdout();
	std::istringstream MyInput("5.5 + 4.5)"); 
	std::streambuf* originalCinBuffer = std::cin.rdbuf(); 
	std::cin.rdbuf(MyInput.rdbuf()); 
	Execute();
	std::cin.rdbuf(originalCinBuffer);
	std::string output1 = testing::internal::GetCapturedStdout();
	testing::internal::CaptureStdout();
	std::cout << "Bad brackets";
	std::string output2 = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output1, output2);

	//5.5 + 4.5)
	//
	//Bad brackets
}

TEST(Check, open_bracket_more_than_close_bracket) {
	testing::internal::CaptureStdout();
	std::istringstream MyInput("(5 + (5.5 + 4.5)"); 
	std::streambuf* originalCinBuffer = std::cin.rdbuf(); 
	std::cin.rdbuf(MyInput.rdbuf());
	Execute();
	std::cin.rdbuf(originalCinBuffer); 
	std::string output1 = testing::internal::GetCapturedStdout();
	testing::internal::CaptureStdout();
	std::cout << "Bad brackets";
	std::string output2 = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output1, output2);

	//(5 + (5.5 + 4.5)
	//
	//Bad brackets
}

TEST(Check, close_bracket_more_than_open_bracket) {
	testing::internal::CaptureStdout();
	std::istringstream MyInput("(5 + 5.5) + 4.5)"); 
	std::streambuf* originalCinBuffer = std::cin.rdbuf(); 
	std::cin.rdbuf(MyInput.rdbuf()); 
	Execute();
	std::cin.rdbuf(originalCinBuffer); 
	std::string output1 = testing::internal::GetCapturedStdout();
	testing::internal::CaptureStdout();
	std::cout << "Bad brackets";
	std::string output2 = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output1, output2);

	//(5 + 5.5) + 4.5)
	//
	//Bad brackets
}

TEST(Check, complex_sequence_of_brackets) {
	testing::internal::CaptureStdout();
	std::istringstream MyInput("5*(6+(5/(4-3))+2)+2"); 
	std::streambuf* originalCinBuffer = std::cin.rdbuf(); 
	std::cin.rdbuf(MyInput.rdbuf()); //  std::cin to MyInput
	bool temp = Execute();
	std::cin.rdbuf(originalCinBuffer); 
	std::string output1 = testing::internal::GetCapturedStdout();

	testing::internal::CaptureStdout();
	std::cout << "Bad brackets";
	std::string output2 = testing::internal::GetCapturedStdout();
	EXPECT_EQ(temp,true);

	//5*(6+(5/(4-3))+2)+2
	//
	//not Bad brackets
}



TEST(Check_Brackets, logic_error_of_brackets) {
	testing::internal::CaptureStdout();
	std::istringstream MyInput("(5+6))+(7+8"); 
	std::streambuf* originalCinBuffer = std::cin.rdbuf();
	std::cin.rdbuf(MyInput.rdbuf()); 
	Execute();
	std::cin.rdbuf(originalCinBuffer); 
	std::string output1 = testing::internal::GetCapturedStdout();
	
	testing::internal::CaptureStdout();
	std::cout << "Bad brackets";
	std::string output2 = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output1, output2);

	//(5+6))+(7+8
	//
	//Bad brackets
}

TEST(Check_Sequence, two_operator) {
	testing::internal::CaptureStdout();
	std::istringstream MyInput("5+4-3-*3+5");
	std::streambuf* originalCinBuffer = std::cin.rdbuf();
	std::cin.rdbuf(MyInput.rdbuf());
	bool temp = Execute();
	std::cin.rdbuf(originalCinBuffer);
	std::string output1 = testing::internal::GetCapturedStdout();


	//testing::internal::CaptureStdout();
	//std::cout << "Incorrect sequence in the expression!";
	//std::string output2 = testing::internal::GetCapturedStdout();
	EXPECT_EQ(temp,false);

	//5+4-3-*3+5
	//
	//Incorrect sequence in the expression!
}

TEST(Check_Sequence, two_number) {
	testing::internal::CaptureStdout();
	std::istringstream MyInput("5 + 5 5");
	std::streambuf* originalCinBuffer = std::cin.rdbuf();
	std::cin.rdbuf(MyInput.rdbuf());
	bool temp = Execute();
	std::cin.rdbuf(originalCinBuffer);
	std::string output1 = testing::internal::GetCapturedStdout();

	testing::internal::CaptureStdout();
	std::cout << "Incorrect sequence in the expression!";
	std::string output2 = testing::internal::GetCapturedStdout();
	EXPECT_EQ(temp,false);

	//5 + 5 5
	//
	//Incorrect sequence in the expression!
}

TEST(Check_Sequence, bad_first_term) {
	testing::internal::CaptureStdout();
	std::istringstream MyInput("- 5 + 5 * 2");
	std::streambuf* originalCinBuffer = std::cin.rdbuf();
	std::cin.rdbuf(MyInput.rdbuf());
	bool temp = Execute();
	std::cin.rdbuf(originalCinBuffer);
	std::string output1 = testing::internal::GetCapturedStdout();

	testing::internal::CaptureStdout();
	std::cout << "\nBad order";
	std::string output2 = testing::internal::GetCapturedStdout();
	EXPECT_EQ(temp,false);

	//- 5 + 5 * 2
	//
	//Bad order
}

TEST(Check_Sequence, bad_last_term) {
	testing::internal::CaptureStdout();
	std::istringstream MyInput("5 + 5 * 2 -");
	std::streambuf* originalCinBuffer = std::cin.rdbuf();
	std::cin.rdbuf(MyInput.rdbuf());
	bool temp = Execute();
	std::cin.rdbuf(originalCinBuffer);
	std::string output1 = testing::internal::GetCapturedStdout();

	testing::internal::CaptureStdout();
	std::cout << "\nBad order";
	std::string output2 = testing::internal::GetCapturedStdout();
	EXPECT_EQ(temp, false);

	//5 + 5 * 2 -
	//
	//Bad order
}

TEST(Check_Sequence, hard_bad_sequence) {
	testing::internal::CaptureStdout();
	std::istringstream MyInput("5+4-(3*3+)5");
	std::streambuf* originalCinBuffer = std::cin.rdbuf();
	std::cin.rdbuf(MyInput.rdbuf());
	bool temp = Execute();
	std::cin.rdbuf(originalCinBuffer);
	std::string output1 = testing::internal::GetCapturedStdout();

	testing::internal::CaptureStdout();
	std::cout << "Incorrect sequence in the expression!";
	std::string output2 = testing::internal::GetCapturedStdout();
	EXPECT_EQ(temp,false);

	//5+4-(3*3+)5
	//
	//Incorrect sequence in the expression!
}

TEST(Check_Sequence, one_term) {
	testing::internal::CaptureStdout();
	std::istringstream MyInput("5");
	std::streambuf* originalCinBuffer = std::cin.rdbuf();
	std::cin.rdbuf(MyInput.rdbuf());
	Execute();
	std::cin.rdbuf(originalCinBuffer);
	std::string output1 = testing::internal::GetCapturedStdout();

	testing::internal::CaptureStdout();
	std::cout << "\nResult: 5\n";
	std::string output2 = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output1, output2);

	//5
	//
	//Result: 5
}

TEST(Check_Sequence, two_term) {
	testing::internal::CaptureStdout();
	std::istringstream MyInput("5+");
	std::streambuf* originalCinBuffer = std::cin.rdbuf();
	std::cin.rdbuf(MyInput.rdbuf());
	bool temp = Execute();
	std::cin.rdbuf(originalCinBuffer);
	std::string output1 = testing::internal::GetCapturedStdout();

	testing::internal::CaptureStdout();
	std::cout << "\nBad order";
	std::string output2 = testing::internal::GetCapturedStdout();
	EXPECT_EQ(temp,false);

	//5
	//
	//Bad order
}


TEST(Execute, test_sum) {
	testing::internal::CaptureStdout();
	std::istringstream MyInput("5.5 + 4.5"); 
	std::streambuf* originalCinBuffer = std::cin.rdbuf();
	std::cin.rdbuf(MyInput.rdbuf()); 
	Execute();
	std::cin.rdbuf(originalCinBuffer); 
	std::string output1 = testing::internal::GetCapturedStdout();
	
	testing::internal::CaptureStdout();
	std::cout << "\n";
	std::cout << "Result: 10";
	std::cout<<"\n";
	std::string output2 = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output1, output2);
	//5.5 + 4.5
	//
	//Result: 10
}


TEST(Execute, test_sum_with_variables) {
	testing::internal::CaptureStdout();
	std::istringstream MyInput("a + b\n5\n15.5"); 
	std::streambuf* originalCinBuffer = std::cin.rdbuf();
	std::cin.rdbuf(MyInput.rdbuf()); 
	Execute();
	std::cin.rdbuf(originalCinBuffer); 
	std::string output1 = testing::internal::GetCapturedStdout();
	
	testing::internal::CaptureStdout();
	std::cout << "\nInitialize the variables:\n";
	std::cout << "a = b = \n";
	std::cout << "Result: 20.5";
	std::cout << "\n";
	std::string output2 = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output1, output2);
	//a + b
	//Initialize the variables:
	//a = 5
	//b = 15.5
	//Result: 20.5
}



TEST(Execute, test_mul) {
	testing::internal::CaptureStdout();
	std::istringstream MyInput("5.5 * 3"); 
	std::streambuf* originalCinBuffer = std::cin.rdbuf();
	std::cin.rdbuf(MyInput.rdbuf()); 
	Execute();
	std::cin.rdbuf(originalCinBuffer); 
	std::string output1 = testing::internal::GetCapturedStdout();
	
	testing::internal::CaptureStdout();
	std::cout << "\n";
	std::cout << "Result: 16.5";
	std::cout << "\n";
	std::string output2 = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output1, output2);
	//5.5 * 3
	//
	//Result: 16.5
}


TEST(Execute, test_mul_with_variables) {
	testing::internal::CaptureStdout();
	std::istringstream MyInput("a * b\n2.5\n6"); 
	std::streambuf* originalCinBuffer = std::cin.rdbuf();
	std::cin.rdbuf(MyInput.rdbuf()); 
	Execute();
	std::cin.rdbuf(originalCinBuffer); 
	std::string output1 = testing::internal::GetCapturedStdout();
	
	testing::internal::CaptureStdout();
	std::cout << "\nInitialize the variables:\n";
	std::cout << "a = b = \n";
	std::cout << "Result: 15";
	std::cout << "\n";
	std::string output2 = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output1, output2);
	//a*b
	// 
	//Initialize the variables:
	//a = 2.5
	//b = 6
	// 
	//Result: 15
}

TEST(Execute, soft_sequence) {
	testing::internal::CaptureStdout();
	std::istringstream MyInput("5^2*3+1");
	std::streambuf* originalCinBuffer = std::cin.rdbuf();
	std::cin.rdbuf(MyInput.rdbuf());
	Execute();
	std::cin.rdbuf(originalCinBuffer);
	std::string output1 = testing::internal::GetCapturedStdout();

	testing::internal::CaptureStdout();
	std::cout << "\n";
	std::cout << "Result: 76";
	std::cout << "\n";
	std::string output2 = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output1, output2);
	//5^2*3+1
	// 
	//Result: 76
}


TEST(Execute, hard_sequence) {
	testing::internal::CaptureStdout();
	std::istringstream MyInput("((5^(1+1) - (2*10/2 + 15)))");
	std::streambuf* originalCinBuffer = std::cin.rdbuf();
	std::cin.rdbuf(MyInput.rdbuf());
	Execute();
	std::cin.rdbuf(originalCinBuffer);
	std::string output1 = testing::internal::GetCapturedStdout();

	testing::internal::CaptureStdout();
	std::cout << "\n";
	std::cout << "Result: 0";
	std::cout << "\n";
	std::string output2 = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output1, output2);
	//((5^(1+1) - (2*10/2 + 15)))
	// 
	//Result: 0
}

TEST(Execute, hard_sequence_with_variables) {
	testing::internal::CaptureStdout();
	std::istringstream MyInput("5+(a+b*3^1)*c - 15\n5.5\n1.5\n1");
	std::streambuf* originalCinBuffer = std::cin.rdbuf();
	std::cin.rdbuf(MyInput.rdbuf());
	Execute();
	std::cin.rdbuf(originalCinBuffer);
	std::string output1 = testing::internal::GetCapturedStdout();

	testing::internal::CaptureStdout();
	std::cout << "\nInitialize the variables:\n";
	std::cout << "a = b = c = \n";
	std::cout << "Result: 0";
	std::cout << "\n";
	std::string output2 = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output1, output2);
	//5+(a+b*3^1)*c - 20
	// 
	//Initialize the variables:
	//a = 5.5
	//b = 1.5
	//c = 1
	// 
	//Result: 0
}

