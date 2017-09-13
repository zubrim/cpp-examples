/*!
\brief An example of redirecting (emulating) std::cin
	------------------------------------------------------
	Purpose:
	- Say you have a library that takes input from the console and processes it.
	You may want to generate sucn input in you program and feed it automatically to the library.
*/
#include "cin_buf.h"
#include <iostream>
#include <string>
#include <streambuf>

int main(int argc, char* argv[]) {
	std::string in;
	cin_buf custom_cin_buf("abc def");
	std::streambuf *original_cin_buf_ptr = std::cin.rdbuf();
	// let's change to the custom buffer
	std::cin.rdbuf(&custom_cin_buf);
	std::cin >> in;
	std::cout << "\nYour input was: " << in << std::endl;
	// let's change to the original buffer
	std::cin.rdbuf(original_cin_buf_ptr);
	std::cout << "Input your string: ";
	std::cin >> in;
	std::cout << "Your input was: " << in << std::endl;

	system("pause");
}