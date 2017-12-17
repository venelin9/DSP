#ifndef __HASH__
#define __HASH__

#include <iostream>
#include <string>
#include <vector>
using std::vector;
using std::cout;
using std::string;


using hashfun=unsigned (*)(const string&);

class hash{
public:
  hash(unsigned _n, hashfun _f):size(_n), f(_f), count(0) {
    vector<kvpair> empty;
    buckets.assign(size,empty);
  }
  ~hash(){}
  bool haskey(const string &s)const{
    unsigned ix = f(s);
    return locate(s,ix)>=0;
  }
  unsigned& operator[](const string &key){
    unsigned ix=f(key);
    int n=locate(key,ix);
    if (n==-1){
      buckets[ix].push_back(kvpair(key));
      n=buckets[ix].size()-1;
      count++;
    }
    return buckets[ix][n].value;
  }
  const unsigned& operator[](const string &key)const{
    unsigned ix=f(key);
    unsigned n=locate(key,ix);
    return buckets[ix][n].value;
  }

private:
  struct kvpair{
    kvpair(const string &_k, unsigned _v=0):key(_k), value(_v){}
    string key;
    unsigned value;
  };
  unsigned size,count;
  hashfun f;
  vector<vector<kvpair>> buckets;

  int locate (const string &key, unsigned ix)const{
    for (unsigned i(0); i<buckets[ix].size(); i++){
      if (buckets[ix][i].key==key)
      return i;
    }
    return -1;
  }

};



#endif
