#include "cin_buf.h"

/// \brief One of the three overrided functions for a stream buffer.
int cin_buf::underflow() {
	if (gptr() < egptr()) {
		return *gptr();
	}
	return traits_type::eof();
}

/*!
	\brief Constructor.
	\param[in] input_string Input to be read from the redirected cin
	\return custom buffer filled with chars from the input_string
*/
cin_buf::cin_buf(const std::string input_string) : buffer(input_string) {
	char *start = &buffer[0u]; // this conversion works only in C++ 11
	setg(start, start, start + buffer.size());
};