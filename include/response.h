#include <iostream>

#ifndef RESPONSE_H
#define RESPONSE_H

using namespace std;

template <typename T>
class response
{
public:
    bool succeeded;
    string message;
    T data;

    response(bool s,string m,T data);//:succeeded(s),message(m),data(d){}

};

#endif // RESPONSE_H
