#include <sstream>
#include "mydatastore.h"

using namespace std;


// The destructor should delete all the dynamically allocated products & users
MyDataStore::~MyDataStore(){
    for (vector<Product*>::iterator it = products_.begin(); it != products_.end(); ++it){
        delete *it;
    }
    for (map<string, User*>::iterator it = users_.begin(); it != users_.end(); ++it){
        delete (it->second);
    }
}

// constructor that practically doesn't do anything
MyDataStore::MyDataStore(){}


void MyDataStore::addProduct(Product* p){
    products_.push_back(p);
    std::set<std::string> kws = p->keywords();
    for (std::set<std::string>::iterator it = kws.begin(); it != kws.end(); ++it){
        keywordMap_[*it].insert(p);
    }
}


void MyDataStore::addUser(User* u){
    users_.insert({u -> getName(), u});
    carts_[u->getName()]; // creates an empty cart
}


bool MyDataStore::addCart(const string& username, Product* p){
    map<string, vector<Product*> >::iterator it = carts_.find(username);
    if (it == carts_.end()) return false;
    it -> second.push_back(p);
    return true;
}


bool MyDataStore::viewCart(const string& username){
    map<string, vector<Product*> >::iterator it = carts_.find(username);
    if (it == carts_.end()) return false;
    vector<Product*>& cart = it->second;
    for (size_t i = 0; i < cart.size(); ++i){
        cout << "Item " << i + 1 << endl;
        cout << cart[i]->displayString() << endl;
        cout << endl;
    }
    return true;
}


bool MyDataStore::buyCart(const string& username){
    map<string, vector<Product*> >::iterator it = carts_.find(username);
    if (it == carts_.end()) return false;
    User* u = users_[username];
    vector<Product*>& cart = it->second;
    // items that can't be bought are kept, in their original order
    vector<Product*> remaining;
    for (size_t i = 0; i < cart.size(); ++i){
        Product* p = cart[i];
        if (p->getQty() > 0 && u->getBalance() >= p->getPrice()){
            p->subtractQty(1);
            u->deductAmount(p->getPrice());
        }
        else {
            remaining.push_back(p);
        }
    }
    cart = remaining;
    return true;
}


void MyDataStore::dump(std::ostream& ofile){
    ofile << "<products>" << endl;
    for (vector<Product*>::iterator it = products_.begin(); it != products_.end(); ++it){
        (*it)->dump(ofile);
    }
    ofile << "</products>" << endl;
    //
    ofile << "<users>" << endl;
    for (map<string,User*>::iterator it = users_.begin(); it != users_.end(); ++it){
        ((*it).second)->dump(ofile);
    }
    ofile << "</users>" << endl;
}


std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
    //type: 0 for AND, 1 for OR.
    set<Product*> curSet;
    for (vector<string>::iterator it = terms.begin(); it != terms.end(); ++it){
        // products with this keyword (empty if no product has it)
        set<Product*> termSet;
        map<string, set<Product*> >::iterator found = keywordMap_.find(*it);
        if (found != keywordMap_.end()) termSet = found->second;

        // AND starts from the first term's set, not an empty set
        if (it == terms.begin()) curSet = termSet;
        else if (type == 0) curSet = setIntersection(curSet, termSet);
        else curSet = setUnion(curSet, termSet);
    }
    return vector<Product*>(curSet.begin(), curSet.end());
}