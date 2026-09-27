#include <sstream>
#include "clothing.h"
#include "util.h"
using namespace std;



Clothing::Clothing(const std::string category, const std::string name, double price, int qty,
    const std::string size, const std::string brand)
    : Product(category, name, price, qty){
    size_ = size;
    brand_ = brand;
}

Clothing::~Clothing(){}

std::set<std::string> Clothing::keywords() const {
    set<string> curSet;
    set<string> nameSet = parseStringToWords(name_);
    curSet = setUnion(curSet, nameSet);
    set<string> brandSet = parseStringToWords(brand_);
    curSet = setUnion(curSet, brandSet);
    return curSet;
}

std::string Clothing::displayString() const {
    stringstream ss;
    ss << name_ << "\n";
    ss << "Size: " << size_ << " Brand: " << brand_ << "\n";
    ss << price_ << " " << qty_ << " left.";
    return ss.str();
}

void Clothing::dump(std::ostream& os) const {
    Product::dump(os);
    os << size_ << "\n" << brand_ << endl;
}
