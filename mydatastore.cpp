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
    for (map<string,set<Product*>>::iterator it1 = keywordMap_.begin(); it1 != keywordMap_.end(); ++it1){
        for (set<Product*>::iterator it2 = (it1->second).begin(); it2 != (it1->second).end(); ++it2){
            delete *it2;
        }
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
}


void MyDataStore::dump(std::ostream& ofile){
    cout << "<products>" << endl;
    for (vector<Product*>::iterator it = products_.begin(); it != products_.end(); ++it){
        (*it)->dump(ofile);
    }
    cout << "</products>" << endl;
    //
    cout << "<users>" << endl;
    for (map<string,User*>::iterator it = users_.begin(); it != users_.end(); ++it){
        ((*it).second)->dump(ofile);
    }
    cout << "</users>" << endl;
}


std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type){
    vector<Product*> curVector;
    set<Product*> curSet;
    for (vector<string>::iterator it = terms.begin(); it != terms.end(); ++it){
        
    }
}