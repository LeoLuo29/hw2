#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include "datastore.h"
#include <map>
#include "util.h"



class MyDataStore : public DataStore{
public:
    //doesn't do anything
    MyDataStore();
    // The destructor should delete all the dynamically allocated products
    ~MyDataStore() override;
    void addUser(User* u) override;
    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;
    void addProduct(Product* p) override;
    void dump(std::ostream& ofile) override;
    // some search code should be here



private:
    // keyword -> products with it
    std::vector<Product*> products_;
    std::map<std::string, User*> users_;
    std::map<std::string, std::set<Product*> > keywordMap_;
};




#endif