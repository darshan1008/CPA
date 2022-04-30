#ifndef _LIST_EXCEPTIONS_H 
#define _LIST_EXCEPTIONS_H 

#include <stdexcept>

// replaces -> DATA_NOT_FOUND error code 
class data_not_found : public std::runtime_error{
public: 
	data_not_found(); 
}; 

// replaces -> LIST_EMPTY error code
class list_empty : public std::runtime_error{
public: 
	list_empty(); 
}; 


#endif /* _LIST_EXCEPTIONS_H */ 