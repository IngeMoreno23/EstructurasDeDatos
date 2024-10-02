#include <iostream>
#include <stdexcept>
#include <string>

template <class T>
class out_of_range: public std::exception{
    public:
        out_of_range(const std::string & _errorMessage);
        out_of_range(const std::string & _errorMessage, T data); 
        virtual const char* what() const noexcept override;
    private: 
        T value_error;
        std::string errorMessage;
        
};

template <class T>
const char* out_of_range<T>::what() const noexcept{
    return errorMessage.c_str();
}

template <class T>
out_of_range<T>::out_of_range(const std::string & _errorMessage, T data): errorMessage(_errorMessage), value_error(data){}


template <class T>
out_of_range<T>::out_of_range(const std::string & _errorMessage): errorMessage(_errorMessage){}



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