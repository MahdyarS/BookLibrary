

#ifndef MEMORY_H
#define MEMORY_H

#include <iostream>
#include <vector>
#include <fstream>
#include "user.h"
#include "book.h"
#include "reservation_log.h"
#include "response.h"
#include "short_response.h"



using namespace std;

class memory
{
public:
    vector<user> users;
    vector<book> books;
    vector<reservation_log> logs;

    response<book> getBookByIsbn(string isbn);

    short_response rewrite_users();
    short_response rewrite_books();
    short_response rewrite_logs();

    short_response rewrite_all_files();
};

#endif // MEMORY_H
