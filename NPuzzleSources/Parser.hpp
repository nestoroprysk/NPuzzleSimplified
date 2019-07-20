#pragma once

#include "Types.hpp"

#include <vector>

namespace Parser {

class ParseError : public std::exception
{
public:
    ParseError(const std::string i_error) : m_error(i_error){}
    const char* what() const noexcept override{ return m_error.c_str(); }
private:
    const std::string m_error;
};

Matrix parseFile(const std::string& i_file_name);
Matrix parseContent(const std::vector<std::string>& i_content);

// Expects N and only then the body of the matrix
void validate(const std::vector<std::size_t>& i_numbers);

}
