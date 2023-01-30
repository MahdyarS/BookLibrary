


#ifndef BOOK_H
#define BOOK_H

#include <iostream>
#include <vector>
#include "response.h"
#include "short_response.h"
#include "memory.h"



using namespace std;

class book
{
private:
    friend ostream &operator<<( std::ostream &, const book & );
    friend istream &operator>>( std::istream &, book & );
    friend class memory;
    string ISBN;
    string title;
    int shelf_number;
    string authors;
    int edition;
    string publisher;
    int published_year;
    int length;
    string subjects;
    bool is_borrowed;
public:
    book();//to create a user to use the empty object just to use the static methods. because the stupid c++ do not let us to use static methods without creating objs :/
    book(string isbn,string t,int s_num,string as,int edtn,string pblshers,int pu_year,int len,string subs);
    short_response add_book(book b,memory& mem);
    response<vector<book>> search(string searchkey,memory mem);
    response<book> update_book(book book,memory& mem);
    short_response load_books(memory& mem);
    short_response write_all_books(memory mem);
    response<bool> isBorrowed();
    short_response toggleState();
};

#endif // BOOK_H
