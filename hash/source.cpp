#include <iostream>
using std::cout;
#include "hash.h"
#include <string>
using std::string;

unsigned fun( const string &s ){
  unsigned p(0);
  for (unsigned i(0); i<s.length(); i++){
    p+=s[i];
  }
  return p%256;
}

int main(){
  hash table(255, fun);
  table["John"]=15;
  cout<<table["John"]<<'\n';
  cout<<table["Joh"]<<'\n';
  return 0;
}
