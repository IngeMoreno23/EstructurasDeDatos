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



class bad_argument: public std::exception{
    public:
        bad_argument(const std::string & _errorMessage);
        virtual const char* what() const noexcept override;
    private: 
        std::string errorMessage;
        
};

bad_argument::bad_argument(const std::string & _errorMessage): errorMessage(_errorMessage){}

const char* bad_argument::what() const noexcept{
    return errorMessage.c_str();
}


class out_of_rangeStack: public std::exception{
    public:
        out_of_rangeStack(const std::string & _errorMessage);
        virtual const char* what() const noexcept override;
    private: 
        std::string errorMessage;
        
};

const char* out_of_rangeStack::what() const noexcept{
    return errorMessage.c_str();
}

out_of_rangeStack::out_of_rangeStack(const std::string & _errorMessage): errorMessage(_errorMessage){}
