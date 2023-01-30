#include "user.h"
#include "book.h"
#include "memory.h"
#include <iostream>
#include <fstream>

using namespace std;

response<book> memory::getBookByIsbn(string isbn)
{
    book empty_book;
    for (int i = 0; i < books.size(); i++)
    {
        if(books[i].ISBN == isbn)
            return response<book>(true,"",books[i]);
    }
    return response<book>(false,"Book Not Found...!",empty_book);
}


short_response memory::rewrite_users()
{
    fstream file;
    remove("users");
    file.open("users");
    if(!file)
        return short_response(false,"could not open users file successfully!");
    for (int i = 0; i < this->users.size(); i++)
    {
        file << users[i] << endl;
    }
    file.close();

}
short_response memory::rewrite_books()
{
    fstream file;
    remove("books");
    file.open("books");
    if(!file)
        return short_response(false,"could not open books file successfully!");
    for (int i = 0; i < books.size(); i++)
    {
        file << books[i] << endl;
    }
    file.close();

}
short_response memory::rewrite_logs()
{
    fstream file;
    remove("logs");
    file.open("logs");
    if(!file)
        return short_response(false,"could not open logs file successfully!");
    for (int i = 0; i < logs.size(); i++)
    {
        file << logs[i] << endl;
    }
    file.close();

}

short_response memory::rewrite_all_files()
{
    rewrite_users();
    rewrite_books();
    rewrite_logs();
    return short_response(true,"");
}



