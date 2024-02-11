#include <sstream>
#include <iomanip>
#include "clothing.h"
#include "util.h"
using namespace std;

Clothing::Clothing(const std::string& category, const std::string& name, double price, int qty,std::string& size, std::string& brand) : 
  Product(category, name, price, qty),
  size_(size),
  brand_(brand)
{

}
Clothing::~Clothing() {
}
std::set<std::string> Clothing::keywords() const  {  //returns keywords that the product is assosiated with
  //in product name
  //in brand 
  
  set<std::string> brandwords = parseStringToWords(brand_);
  set<std::string> keywords = parseStringToWords(name_);
  for (std::set<std::string>::iterator it = brandwords.begin();it!=brandwords.end();++it) {
    keywords.insert(*it);
  }

  return keywords;

}
std::string Clothing::displayString() const {
    std::stringstream productinfo;
    productinfo << name_ << "\nSize: " << size_ << " Brand: " << brand_ << "\n";
    productinfo << std::fixed << std::setprecision(2) << price_ << " " << qty_ << " left.";
    return productinfo.str();
}

void Clothing::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << size_ << "\n" << brand_ << endl;
}
