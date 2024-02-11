#ifndef MYDATASTORE_H
#define MYDATASTORE_H
#include <string>
#include <set>
#include <vector>
#include "datastore.h"
#include "util.h"
#include "product.h" ////?????
#include <map>

class MyDataStore : public DataStore {
  public:
		~MyDataStore();
    void addProduct(Product* p) override;
    void addUser(User* u) override;
    std::vector<Product*> search(std::vector<std::string>& terms, int type) override;
    void dump(std::ostream& ofile) override;

    //ADD to cart (ADD username hit_result_index)
    ///takes in a index from the search results
    void addToCart(const std::string& username,int hit_result_index);


    //viewing cart (VIEWCART username)
    void viewCart(const std::string& username);

    //Buying cart (BUYCART username)
    void buyCart(const std::string& username);

    //saving the database??

  protected:
    std::vector<Product*> products;
    std::map<std::string, User*> users;
    std::map<std::string, std::vector<Product*>> carts;
    std::vector<Product*> lastSearchResults;
    std::map<std::string, std::set<Product*>> keywordMap;


};
#endif

