#include <iostream>

#ifndef SHORT_RESPONSE_H
#define SHORT_RESPONSE_H

using namespace std;

class short_response
{
public:

    short_response(bool s,string m);//:succeeded(s),message(m){}

    bool succeeded;
    string message;
};

#endif // SHORT_RESPONSE_H
