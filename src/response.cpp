#include "response.h"

using namespace std;

template <typename T>
response<T>::response(bool s,string m,T d):succeeded(s),message(m),data(d){}

