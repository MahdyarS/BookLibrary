#include <iostream>
#include <vector>
#include "memory.h"
#include "response.h"
#include "short_response.h"
#include "date.h"
#include "user.h"
#include "date.h"

using namespace std;

memory mem;
book bookService;
user userService;
user thisUser;

user login_handler()
{
    string username,password;
    while (true)
    {
        cout << "Enter your username:";
        cin >> username;
        cout << "Enter your password";
        cin >> password;
        response<user> res = userService.login(username,password,mem);
        cout << res.message << endl;

        if(res.succeeded)
            return res.data;

        cout << "Retry your login process" << endl;
    }

}

void show_admin_commands()
{
    cout << "1 - Confirm book delivery" << endl;
    cout << "2 - Search book" << endl;
    cout << "3 - Add book" << endl;
    cout << "4 - Update book"  << endl;
    cout << "5 - Add User"  << endl;
    cout << "6 - Update User" << endl;
}

void show_user_commands()
{
    cout << "1 - Search book" << endl;
    cout << "2 - Borrow book" << endl;
    cout << "3 - Deliver book" << endl;
}

void show_commands()
{
    if(thisUser.is_admin().data)
        show_admin_commands();
    else
        show_user_commands();
    cout << "Please Enter the number of the command that you want to execute:";
}


void search_handler()
{
    string searchkey;
    cout << "Please enter a part of the title or ISBN or author or subject of the book you are looking for:";
    cin >> searchkey;
    response<vector<book>> res = bookService.search(searchkey,mem);
    if(!res.succeeded)
    {
        cout << res.message << endl;
        return;
    }
    cout << "ISBN" << "\t" << "title" << "\t" << "shelf_number" << "\t" << "authors" << "\t" << "edition" << "\t" << "publisher" << "\t" << "published_year"
     << "\t" << "length" << "\t" << "subjects" << "\t" << "is_borrowed" << endl;

    cout << "----------------------------------------------------------------------------------------------------------------------------" << endl;

    for (int i = 0; i < res.data.size(); i++)
        cout << res.data[i] << endl;

}

void borrow_handler()
{
    cout << "Enter the ISBN of the book that you want to borrow:";
    string isbn;
    cin >> isbn;
    short_response res = thisUser.borrow(isbn,mem);
    cout << res.message;
}

void delivery_handler()
{
    cout << "Enter the ISBN of the book that you want to deliver:";
    string isbn;
    short_response res = thisUser.confirm_delivery(isbn,mem);
    cout << res.message << endl;
}

void addBook_handler()
{
    cout << "Enter the book that you want to add with the following format:" << endl;
    cout << "ISBN" << "\t" << "title" << "\t" << "shelf_number" << "\t" << "authors" << "\t" << "edition" << "\t" << "publisher" << "\t" << "published_year"
     << "\t" << "length" << "\t" << "subjects" << "\t" << "is_borrowed" << endl;
    book b;
    cin >> b;
    response<book> res = bookService.add_book(b,mem);
    cout << res.message << endl;
}

void updateBook_handler()
{
    cout << "Enter the book that you want to update with the following format:" << endl;
    cout << "ISBN" << "\t" << "title" << "\t" << "shelf_number" << "\t" << "authors" << "\t" << "edition" << "\t" << "publisher" << "\t" << "published_year"
     << "\t" << "length" << "\t" << "subjects" << "\t" << "is_borrowed" << endl;
    book b;
    cin >> b;
    response<book> res = bookService.update_book(b,mem);
    cout << res.message << endl;
}

void addUser_handler()
{
    cout << "Enter the users data that you want to add with the following format:" << endl;
    cout << "username" << " " << "firstName" << " " << "lastName" << " " << "password" << " " << "birthday" << " " << "isAdmin" << endl;
    user u;
    cin >> u;
    response<user> res = userService.add_user(u,mem);
    cout << res.message << endl;
}

void updateUser_handler()
{
    cout << "Enter the users data that you want to update with the following format:" << endl;
    cout << "username" << " " << "firstName" << " " << "lastName" << " " << "password" << " " << "birthday" << " " << "isAdmin" << endl;
    user u;
    cin >> u;
    response<user> res = userService.update_user(u,mem);
    cout << res.message << endl;
}



int main()
{
    bookService.load_books(mem);
    userService.load_users(mem);

    thisUser = login_handler();

    while(true)
    {
        show_commands();
        int commandId;
        cin >> commandId;
        if(thisUser.is_admin().data)
        {
            switch (commandId)
            {
            case 1:
                delivery_handler();
                break;
            case 2:
                search_handler();
                break;
            case 3:
                addBook_handler();
                break;
            case 4:
                updateBook_handler();
                break;
            case 5:
                addUser_handler();
                break;
            case 6:
                updateUser_handler();
                break;

            default:
                cout << "Invalid command requested!" << endl;
                break;
            }
        }
        else
        {
            if(commandId == 1)
                search_handler();
            else if(commandId == 2)
                borrow_handler();
            else if(commandId == 3)
                delivery_handler();
            else
                cout << "Invalid command requested!" << endl;
        }

    }


    return 0;
}
