#include <sstream>
#include "book.h"
#include "util.h"
using namespace std;


Book::Book(const std::string category, const std::string name, double price, int qty,
    const std::string isbn, const std::string author)
    : Product(category, name, price, qty){
    isbn_ = isbn;
    author_ = author;
}

Book::~Book(){}

std::set<std::string> Book::keywords() const {
    set<string> curSet;
    curSet.insert(convToLower(isbn_));
    set<string> nameSet = parseStringToWords(name_);
    curSet = setUnion(curSet, nameSet);
    set<string> authorSet = parseStringToWords(author_);
    curSet = setUnion(curSet, authorSet);
    return curSet;
}


std::string Book::displayString() const {
    stringstream ss;
    ss << name_ << "\n";
    ss << "Author: " << author_ << " ISBN: " << isbn_ << "\n";
    ss << price_ << " " << qty_ << " left.";
    return ss.str();
}


void Book::dump(std::ostream& os) const {
    Product::dump(os);
    os << isbn_ << "\n" << author_ << endl;
}


