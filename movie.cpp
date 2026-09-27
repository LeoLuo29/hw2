#include <sstream>
#include "movie.h"
#include "util.h"
using namespace std;


Movie::Movie(const std::string category, const std::string name, double price, int qty,
    const std::string genre, const std::string rating)
    : Product(category, name, price, qty){
    genre_ = genre;
    rating_ = rating;
}

Movie::~Movie(){}

std::set<std::string> Movie::keywords() const {
    set<string> curSet;
    set<string> nameSet = parseStringToWords(name_);
    curSet = setUnion(curSet, nameSet);
    curSet.insert(convToLower(genre_));
    return curSet;
}

std::string Movie::displayString() const {
    stringstream ss;
    ss << name_ << "\n";
    ss << "Genre: " << genre_ << " Rating: " << rating_ << "\n";
    ss << price_ << " " << qty_ << " left.";
    return ss.str();
}

void Movie::dump(std::ostream& os) const {
    Product::dump(os);
    os << genre_ << "\n" << rating_ << endl;
}

