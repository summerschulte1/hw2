#include "mydatastore.h"
#include <string>
#include <set>
#include <vector>
#include "util.h"
#include <iostream>
using namespace std;

MyDataStore::~MyDataStore() {
    // Assuming products is a std::vector<Product*>
    for (std::vector<Product*>::iterator it = products.begin(); it != products.end(); ++it) {
        delete *it; // Delete each dynamically allocated Product
    }
    products.clear(); // Clear the container

    // Assuming users is a std::map<std::string, User*>
    for (std::map<std::string, User*>::iterator it = users.begin(); it != users.end(); ++it) {
        delete it->second; // Delete each dynamically allocated User
    }
    users.clear(); // Clear the container
}

void MyDataStore::addProduct(Product* p) {
  products.push_back(p);
  //do i need to use a keyword map??
	std::set<std::string> keywords = p->keywords(); 
    for (const std::string& keyword : keywords) {
        keywordMap[keyword].insert(p);
    }
}
void MyDataStore::addUser(User* u) {
  users[u->getName()] = u; //key is the username and value is ur user object
}

void MyDataStore::addToCart(const std::string& username, int hit_result_index) {
  if (hit_result_index >= 0 && hit_result_index < static_cast<int>(lastSearchResults.size())) {
    //its a valid index 
		//cout << "its a valid index" << endl;
    Product* productToAdd = lastSearchResults[hit_result_index];
    if (users.find(username) != users.end()) { // Ensure user exists 
			//cout << "user exists!" << endl;
      carts[username].push_back(productToAdd);   
    }
    else {
      cout << "Invalid request" << endl;
    } 
  }
  else {
		//cout << "the second else" << endl;
    cout << "Invalid request" << endl;
  }
}
std::vector<Product*> MyDataStore::search(std::vector<std::string>& terms, int type) {
  std::vector<Product*> results;
	std::set<Product*> resultSet; // Use a set for intermediate results
  // Normalize search terms to lowercase
  for (size_t i = 0; i < terms.size(); ++i) {
    terms[i] = convToLower(terms[i]);
  }
  if (!terms.empty()) {
        // Find the initial set for the first term
        std::map<std::string, std::set<Product*>>::iterator it = keywordMap.find(terms[0]);
        if (it != keywordMap.end()) { //if the term is in the keywordMap
            resultSet = it->second;
        }

        for (size_t i = 1; i < terms.size(); ++i) { //going through the terms 
            it = keywordMap.find(terms[i]);
            if (it != keywordMap.end()) { //seeing if its in the keywords map
                std::set<Product*> termSet = it->second;
                if (type == 0) { // AND search
                    resultSet = setIntersection(resultSet, termSet);
                } else if (type == 1) { // OR search
                    resultSet = setUnion(resultSet, termSet);
                }
            } else if (type == 0) {
                // For AND search, if any term is not found, clear resultSet
                resultSet.clear();
                break;
            }
        }
    }

    // Convert the resulting set to a vector
   // for (std::set<Product*>::iterator it = results.begin(); it != results.end(); ++it) {
    //    results.push_back(*it);
   // }
	lastSearchResults.assign(resultSet.begin(), resultSet.end());
  return lastSearchResults; // Return the last search results
}

void MyDataStore::viewCart(const std::string& username) {
    // Check if the user exists in the system
    if (users.find(username) == users.end()) {
        std::cout << "Invalid username" << std::endl;
        return;
    }
    // Retrieve the user's cart
    std::vector<Product*>& cart = carts[username];
    //std::cout << "Cart for user: " << username << std::endl;
    for (size_t i = 0; i < cart.size(); ++i) {
        cout << "Item " << i + 1 <<"\n" << cart[i]->displayString() << endl;
    }
}
void MyDataStore::buyCart(const std::string& username) {
    // First, check if the user exists
    std::map<std::string, User*>::iterator userIt = users.find(username);
    if (userIt == users.end()) {
        cout << "Invalid username" << endl;
        return;
    }

    // Get the user's cart
		User* user = userIt->second;
    std::vector<Product*>& cart = carts[username];
		std::vector<Product*> tempcart;

    // Iterate through the cart
    for (std::vector<Product*>::iterator it = cart.begin(); it != cart.end(); /* no increment here */) {
        Product* product = *it;
        double price = product->getPrice();
        int qty = product->getQty();

        // Check if the product is in stock and the user has enough credit
        if (qty > 0 && user->getBalance() >= price) {
            // Deduct the product price from the user's credit
            user->deductAmount(price);
            // Decrease the product quantity
            product->subtractQty(1);
            // Remove the product from the cart
            it = cart.erase(it); // This also moves the iterator to the next item
        } else {
            // If the conditions are not met, leave the item in the cart and move to the next
            ++it;
						//tempcart.push_back(product);
        }
				//create a new cart and if they cant buy it, but it in there and make that their new cart
    }
		//carts[username] = tempcart;
}

void MyDataStore::dump(std::ostream& ofile) {
    ofile << "<products>" << std::endl;
    // Assuming 'products' is a container (e.g., std::vector) of Product pointers
    for (std::vector<Product*>::const_iterator it = products.begin(); it != products.end(); ++it) {
        (*it)->dump(ofile);
    }
    ofile << "</products>" << std::endl;

    ofile << "<users>" << std::endl;
    // Assuming 'users' is a map (e.g., std::map<std::string, User*>)
    for (std::map<std::string, User*>::const_iterator it = users.begin(); it != users.end(); ++it) {
        it->second->dump(ofile);
    }
    ofile << "</users>" << std::endl;
}





