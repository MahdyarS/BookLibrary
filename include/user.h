

#ifndef USER_H
#define USER_H


#include <iostream>
#include "date.h"
#include "response.h"
#include "short_response.h"
#include "memory.h"
using namespace std;

class user
{
private:
    friend ostream &operator<<( std::ostream &, const user & );
    friend istream &operator>>( std::istream &, user & );

    string username;
    string firstName;
    string lastName;
    string password;
    date birthday;
    bool isAdmin;

public:
    user();//to create a user to use the empty object just to use the static methods. because the stupid c++ do not let us to use static methods without creating objs :/
    user(string uname,string fname,string lname, string psswd,date bd);
    short_response add_user(string uname,string fname,string lname, string psswd,string rpt_psswd,date bd,memory& mem);
    response<user> login(string usernaem,string password,memory mem);
    response<user> update_user(user u,memory& mem);
    short_response borrow(string isbn,memory& mem);
    short_response confirm_delivery(string isbn,memory& mem);
    //response<book> add_book(book book);
    //response<book> update_book(book book);
    //short_response delete_user(string username);
    short_response load_users(memory& mem);
    short_response write_all_users(memory& mem);
    response<bool> is_admin();
};

#endif // USER_H
