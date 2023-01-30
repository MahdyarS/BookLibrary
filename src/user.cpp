#include <iostream>
#include <vector>
#include <fstream>
#include "user.h"
#include "memory.cpp"

using namespace std;

user::user(){}

user::user(string uname,string fname,string lname, string psswd,date bd):username(uname),firstName(fname),lastName(lname),password(psswd),birthday(bd){}

istream &operator>>( istream &input, user &u )
{

    input >> u.username;
    input >> u.firstName;
    input >> u.lastName;
    input >> u.password;
    input >> u.birthday;
    input >> u.isAdmin;

   return input;
}


ostream &operator<<( ostream &output, const user &u )
{
    output << u.username << " " << u.firstName << " " << u.lastName << " " << u.password << " " << u.birthday << " " << u.isAdmin;
    return output;
}


short_response user::add_user(string uname,string fname,string lname, string psswd,string rpt_psswd,date bd,memory& mem)
{
    if(psswd != rpt_psswd)
        return short_response(false,"passwords do not match");
    user user(uname,fname,lname,psswd,bd);
    fstream file;
    file.open("users",ios::out);
    if(!file)
        return short_response(false,"could not open users file successfully");

    file << endl << user;

    file.close();

    mem.users.push_back(user);
}


response<user> user::login(string username,string password,memory mem)
{
    user empty_user;
    for (int i = 0; i < mem.users.size(); i++)
    {
        if(mem.users[i].username == username)
        {
            if(mem.users[i].password == password)
                return response<user>(true,"Welcome "+mem.users[i].firstName,mem.users[i]);

            return response<user>(false,"Wrong Password!",empty_user);
        }
    }

    return response<user>(false,"User Not Found!",empty_user);

}

short_response user::load_users(memory& mem)
{
    fstream file;
    file.open("users");
    if(!file)
        return short_response(false,"Could not open users file successfully!");
    user u;
    while(file >> u)
    {
        mem.users.push_back(u);
    }
    return short_response(true,"Operation was done successfully!");
}



short_response user::write_all_users(memory& mem)
{
    remove("users");
    fstream file;
    file.open("users");
    if(!file)
    {
        return short_response(false,"could not open users file successfully");
    }
    for (int i = 0; i < mem.users.size(); i++)
    {
        file << mem.users[i];
    }
    file.close();
    return short_response(true,"memory updated successfully");

}


response<user> user::update_user(user u,memory& mem)
{
    for (int i = 0; i < mem.users.size(); i++)
    {
        if(u.username == mem.users[i].username)
        {
            mem.users[i] = u;
            short_response res = mem.rewrite_users();
            if(!res.succeeded)
                return response<user>(res.succeeded,res.message,u);
            return response<user>(true,"user updated successfully!",u);
        }
    }
    return response<user>(false,"username not found!",u);
}


short_response user::borrow(string isbn,memory& mem)
{
    response<book> res = mem.getBookByIsbn(isbn);
    if(!res.succeeded)
        return short_response(false,res.message);
    res.data.toggleState();
    res = res.data.update_book(res.data,mem);
    if(!res.succeeded)
        return short_response(false,res.message);
    return short_response(true,"Book borrowed");
}

short_response user::confirm_delivery(string isbn,memory& mem)
{
    response<book> res = mem.getBookByIsbn(isbn);
    if(!res.succeeded)
        return short_response(false,res.message);
    res.data.toggleState();
    res = res.data.update_book(res.data,mem);
    if(!res.succeeded)
        return short_response(false,res.message);
    return short_response(true,"Delivery confirmed successfully!");
}

response<bool> user::is_admin()
{
    return response<bool>(true,"",isAdmin);
}
