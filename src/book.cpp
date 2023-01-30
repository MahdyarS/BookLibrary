#include <iostream>
#include <vector>
#include <string>
#include "book.h"
#include "memory.cpp"

using namespace std;


istream &operator>>( std::istream &input, book &b )
{
    input >>b.ISBN;
    input >>b.title;
    input >>b.shelf_number;
    input >>b.authors;
    input >>b.edition;
    input >>b.publisher;
    input >>b.published_year;
    input >>b.length;
    input >>b.subjects;
    input >>b.is_borrowed;
}

ostream &operator<<( std::ostream & out, const book &b )
{
    out << b.ISBN << " " << b.title << " " << b.shelf_number << " " << b.authors << " " << b.edition << " " << b.publisher << " " << b.published_year
     << " " << b.length << " " << b.subjects << " " << b.is_borrowed;
}



book::book(){}
book::book(string isbn,string t,
            int s_num,string as,
            int edtn,string pblsher,
            int pu_year,int len,string subs):ISBN(isbn),title(t),shelf_number(s_num),
authors(as),edition(edtn),publisher(pblsher),published_year(pu_year),subjects(subs){}

short_response add_book(book b,memory& mem)
{
    fstream file;
    file.open("books",ios::out);
    if(!file)
        return short_response(false,"could not open books file successfully");

    file << endl << b;

    file.close();

    mem.books.push_back(b);

}



response<vector<book>> book::search(string searchkey,memory mem)
{
    vector<book> res;
    for (int i = 0; i < mem.books.size(); i++)
    {
        if(mem.books[i].title.find(searchkey) > -1)
            res.push_back(mem.books[i]);
        else if(mem.books[i].authors.find(searchkey) > -1)
            res.push_back(mem.books[i]);
        else if(mem.books[i].subjects.find(searchkey) > -1)
            res.push_back(mem.books[i]);
        else if(mem.books[i].ISBN == searchkey)
            res.push_back(mem.books[i]);
    }
    if(res.size() > 0)
        return response<vector<book>>(true,"operation was done successfully",res);

    return response<vector<book>>(true,"Requested book was not found!",res);

}

short_response book::load_books(memory& mem)
{
    fstream file;
    file.open("books");
    if(!file)
        return short_response(false,"Could not open books file successfully!");
    book b;
    while(file >> b)
    {
        mem.books.push_back(b);
    }
    return short_response(true,"Operation was done successfully!");
}



short_response book::write_all_books(memory mem)
{
    remove("books");
    fstream file;
    file.open("books");
    if(!file)
    {
        return short_response(false,"could not open books file successfully");
    }
    for (int i = 0; i < mem.books.size(); i++)
    {
        file << mem.books[i];
    }
    file.close();
    return short_response(true,"memory updated successfully");

}


response<book> book::update_book(book b,memory& mem)
{
    for (int i = 0; i < mem.books.size(); i++)
    {
        if(b.ISBN == mem.books[i].ISBN)
        {
            mem.books[i] = b;
            short_response res = mem.rewrite_books();
            if(!res.succeeded)
                return response<book>(res.succeeded,res.message,b);
            return response<book>(true,"Book updated successfully!",b);
        }
    }
    return response<book>(false,"ISBN not found!",b);
}



response<bool> book::isBorrowed()
{
    return response<bool>(true,"operation done successfully",is_borrowed);
}


short_response book::toggleState()
{
    is_borrowed = !is_borrowed;
    return short_response(true,"operation was done successfully");
}



