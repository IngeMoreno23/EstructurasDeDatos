
#include <iostream>
#include <stdexcept>
#include <string>

class out_of_range: public std::exception{
    public:
        out_of_range(const std::string & _errorMessage);
        virtual const char* what() const noexcept override;
    private: 
        std::string errorMessage;
        
};

const char* out_of_range::what() const noexcept{
    return errorMessage.c_str();
}

out_of_range::out_of_range(const std::string & _errorMessage): errorMessage(_errorMessage){}
