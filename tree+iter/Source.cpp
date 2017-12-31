#include "tree.h"
#include <iostream>
using std::cout;

int main(){
  tree<int> t;
  t.add(1, "");
  t.add(2, "L");
  t.add(3, "R");
  t.add(4, "LL");
  t.add(5, "LR");

  for (tree<int>::Iterator i=t.begin(); i!=t.end(); ++i){
    
    cout<<*i<<'\n';
  }
  return 0;
}
