#pragma once
#include <streambuf>
#include <string>

///This class realizes a custom stream buffer for std::cin.
class cin_buf : public std::streambuf {
private:
	std::string buffer;
protected:
	virtual int underflow() override;
public:
	cin_buf(const std::string input_string);
};