#include <sstream>
#include <iomanip>
#include "book.h"
#include "util.h"

using namespace std;

Book::Book(const std::string& category, const std::string& name, double price, int qty,std::string& isbn, std::string& author) : //why this : ? //do we need to add product name?
  Product(category, name, price, qty),
  ISBN_(isbn),
  author_(author)
  
{
  ///??
}
Book::~Book() 
{

}
std::set<std::string> Book::keywords() const  {  //returns keywords that the product is assosiated with
  //in product name
  //authors name & ISBN 
  
  set<std::string> authorwords = parseStringToWords(author_);
  set<std::string> keywords = parseStringToWords(name_);
  for (std::set<std::string>::iterator it = authorwords.begin();it!=authorwords.end();++it) {
    keywords.insert(*it);
  }
  keywords.insert(ISBN_);

  return keywords;

}
std::string Book::displayString() const {
    std::stringstream productinfo;
    productinfo << name_ << "\nAuthor: " << author_ << " ISBN: " << ISBN_ << "\n";
    productinfo << std::fixed << std::setprecision(2) << price_ << " " << qty_ << " left.";
    return productinfo.str();
}

void Book::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << ISBN_ << "\n" << author_ << endl;
}

