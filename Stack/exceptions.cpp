#include <iostream>
#include <stdexcept>
#include <string>

class stack_overflow: public std::exception{
    public:
        stack_overflow(const std::string & _errorMessage);
        virtual const char* what() const noexcept override;
    private: 
        std::string errorMessage;
        
};

const char* stack_overflow::what() const noexcept{
    return errorMessage.c_str();
}

stack_overflow::stack_overflow(const std::string & _errorMessage): errorMessage(_errorMessage){}