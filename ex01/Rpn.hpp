#pragma once

#include <string>
#include <stack>

class Rpn {

    private:
        std::stack<int> _executorStack;

    public:
        Rpn( void );
        Rpn( char *str );
        Rpn( const Rpn &src );
        Rpn& operator=( const Rpn &src );
        ~Rpn();
        int	    evaluate( std::string exp );
        void    doOperation( std::stack<int> &stack, std::string c );


 };

