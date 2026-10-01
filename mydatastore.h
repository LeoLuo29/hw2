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
    // Each returns false if username doesn't exist
    // Appends p to the end of username's cart
    bool addCart(const std::string& username, Product* p);
    // Prints username's cart in the order items were added
    bool viewCart(const std::string& username);
    // Buys cart items in order; items out of stock or too expensive stay in the cart
    bool buyCart(const std::string& username);


private:
    std::vector<Product*> products_;
    std::map<std::string, User*> users_;
    // keyword -> products with it
    std::map<std::string, std::set<Product*> > keywordMap_;
    // username -> cart, in the order items were added
    std::map<std::string, std::vector<Product*> > carts_;
};




#endif