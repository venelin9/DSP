#include <iostream>
#include <assert.h>
#include "three.h"
#include <vector>
#include <string>
using std::cout;

bool gr50(const int &a){
  if (a>=50) return true;
  return false;
}

void test2(){
  three<int> t;
  t.add(-5,"");
  t.add(50,"L");
  t.add(20,"LR");
  t.add(-25,"LL");
  t.add(25,"R");
  t.add(100,"RR");
  // std::vector<int> v=t.listleaves();
  // for (auto i = v.begin(); i != v.end(); ++i)
  // std::cout << *i << ' ';
  // cout<<'\n';
  // cout<<t.findtrace(100)<<'\n';
//  cout<<t.findtrace(25)<<'\n';
  t.pretty();
  cout<<"---------------\n|Tests2 Passed!|\n---------------";
}

void test1(){
  three<int> t;
  t.add(-5,"");
  t.add(50,"L");
  t.add(20,"LR");
  t.add(-25,"LL");
  t.add(25,"R");
  t.add(100,"RR");
  // t.print();
  // assert(t.find(50));
  // assert(!t.find(999));
  // assert(t.count()==5);
  // assert(t.countE()==4);
  // assert(t.searchCount(gr50)==2);
  // assert(t.height()==3);
  // assert(t.leaves()==3);
  //assert(t.maxleaf()==100);
  // cout<<t.getel("LL")<<'\n';

  cout<<"---------------\n|Tests1 Passed!|\n---------------";
}


int main(){

  //test1();
  test2();

  return 0;
}
