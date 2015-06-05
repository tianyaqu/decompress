#include <Rcpp.h>

using namespace Rcpp;

class ListBuilder {
public:
   ListBuilder() {};
   ~ListBuilder() {};

   inline ListBuilder& add(std::string const& name, SEXP x) {
      names.push_back(name);

      // NOTE: we need to protect the SEXPs we pass in; there is
      // probably a nicer way to handle this but ...
      elements.push_back(PROTECT(x));

      return *this;
   }

   inline operator List() const {
      List result(elements.size());
      for (size_t i = 0; i < elements.size(); ++i) {
         result[i] = elements[i];
      }
      result.attr("names") = wrap(names);
      UNPROTECT(elements.size());
      return result;
   }

   inline operator DataFrame() const {
      List result = static_cast<List>(*this);
      result.attr("class") = "data.frame";
      result.attr("row.names") = IntegerVector::create(NA_INTEGER, XLENGTH(elements[0]));
      return result;
   }

private:
   std::vector<std::string> names;
   std::vector<SEXP> elements;

   ListBuilder(ListBuilder const&) {}; // not safe to copy

};