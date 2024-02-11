#ifndef BOOK_H
#define BOOK_H
#include <iostream>
#include <string>
#include <set>
#include <vector>
#include <algorithm>
#include "product.h"


class Book : public Product {
  public:
    Book(const std::string& category, const std::string& name, double price, int qty,std::string& isbn, std::string& author);
    ~Book();
    virtual std::set<std::string> keywords() const; 
    virtual std::string displayString() const;
    virtual void dump(std::ostream &os) const;
		//virtual bool isMatch(std::vector<std::string>& searchTerms) const;

  private:
  std::string ISBN_;
  std::string author_;
};
#endif