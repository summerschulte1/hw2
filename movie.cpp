#include <sstream>
#include <iomanip>
#include "movie.h"
#include "util.h"
using namespace std;

Movie::Movie(const std::string& category, const std::string& name, double price, int qty,std::string& genre, std::string& rating) : 
  Product(category, name, price, qty),
  genre_(genre),
  rating_(rating)
{

}
Movie::~Movie() {
}
std::set<std::string> Movie::keywords() const {  //returns keywords that the product is assosiated with
  //in product name
  //in brand 
  
  set<std::string> genrewords = parseStringToWords(genre_);
  set<std::string> keywords = parseStringToWords(name_);
  for (std::set<std::string>::iterator it = genrewords.begin();it!=genrewords.end();++it) {
    keywords.insert(*it);
  }

  return keywords;

}
std::string Movie::displayString() const {
    std::stringstream productinfo;
    productinfo << name_ << "\nGenre: " << genre_ << " Rating: " << rating_ << "\n";
    productinfo << std::fixed << std::setprecision(2) << price_ << " " << qty_ << " left.";
    return productinfo.str();
}

void Movie::dump(std::ostream& os) const
{
    os << category_ << "\n" << name_ << "\n" << price_ << "\n" << qty_ << "\n" << genre_ << "\n" << rating_ << endl;
}


