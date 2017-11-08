#ifndef __THREE__
#define __THREE__

#include <iostream>
#include <assert.h>
#include <vector>
#include <string>
#include <fstream>
using std::cout;

template <class t>
struct node{
  node<t> *left, *right;
  t data;
  bool lchildless()const{
    return (!left);
  }
  bool rchildless()const{
    return (!right);
  }
  node(t _d): data(_d), left(nullptr), right(nullptr){}
  node():left(nullptr),right(nullptr){}
};


template <class t>
class three{
private:
  node<t>* root;
  void add(t d, const char* p, node<t> *&r){
    if (!r) {
      r=new node<t>(d);
      return;
    }
    if(p[0]=='L') {add(d,p+1,r->left); return;}
    if(p[0]=='R') {add(d,p+1,r->right); return;}
    cout<<"Incorrect path.\n";
    assert(false);
  }
  void print(node<t> *r)const{
    if (!r) return;
    cout<<r->data<<'\n';
    print(r->left);
    print(r->right);
  }
  bool find(t d, node<t> *r)const{
    if (!r) return false;
    if (r->data==d) return true;
    return find(d, r->left) || find(d, r->right);
  }

  void del(node<t> *r){
    if(!r) return;
    del(r->left);
    del(r->right);
    delete r;
  }
  unsigned count(node<t> *r)const{
    if (!r) return 0;
    return 1+count(r->left)+count(r->right);
  }
  unsigned countE(node<t> *r)const{
    if (!r) return 0;
    if (r->data%2==0) return 1+countE(r->left)+countE(r->right);
    return 0+countE(r->left)+countE(r->right);
  }
  unsigned searchCount(bool (*pred)(const t&), node<t> *r)const{
    unsigned x(0);
    if (!r) return 0;
    if (pred(r->data)) x = 1;
    return x+searchCount(pred, r->left)+searchCount(pred,r->right);
  }
  unsigned height(node<t> *r)const{
    if (!r) return 0;
    unsigned _l(height(r->left)), _r(height(r->right));
    return 1+ (_l >= _r ? _l : _r);
  }
  unsigned leaves(node<t> *r)const{
    if (!r) return 0;
    if (r->lchildless() && r->rchildless()) return 1;
    return leaves(r->left) + leaves(r->right);
  }
  t maxleaf(node<t> *r)const{
    if (!r) return NULL;
    if (r->lchildless() && r->rchildless()) return r->data;
    t _l(maxleaf(r->left)), _r(maxleaf(r->right));
    return (_l > _r ? _l : _r );
  }
  t& getel(const char *s, node<t> *r)const{
    if (s[0]=='\0') return r->data;
    if (s[0]=='L') return getel(s+1, r->left);
    if (s[0]=='R') return getel(s+1, r->right);
  }
  void check(node<t> *r, std::vector<t> &v){
    if (!r) return;
    if (r->lchildless() && r->rchildless()) v.push_back(r->data);
    check(r->left,v);
    check(r->right,v);
    return;
  }
  std::vector<t> listleaves(std::vector<t> &v){
    check(root,v);
    return v;
  }
  void check_str(const t& x, node<t>* r, std::string &st)const{
        if (r->data==x) return;
        if (find(x, r->left)){
          st+='L';
          check_str(x, r->left,st);
          return;
        }
        if (find(x,r->right)){
          check_str(x, r->right ,st);
          st+='R';
          return;
        }
  }

  void pretty(node<t> *r, unsigned n){
    if (r->left) 
	pretty(r->left, n+1);
    for (unsigned i(0); i<n; i++) 
	cout<<'\t';
    cout<<r->data<<'\n';
    if (r->right)
	pretty(r->right, n+1);
  }

public:
  
  void pretty(){
      if (!root) return;
      pretty(root,0);
  }

  std::string findtrace(const t& x)const{
    if (!root) return "Error";
    if (root->data==x) return "Root";
    if (!find(x, root)) return "Not found";
    std::string st("");
    check_str(x, root, st);
    return st;
  }

  std::vector<t> listleaves(){
      std::vector<t> v;
      if (!root) return v;
      return listleaves(v);
  }

  t& getel(const char *s)const{
    return getel(s, root);
  }
  t maxleaf()const{
    if (!root) return NULL;
    return maxleaf(root);
  }
  unsigned leaves()const{
    if (!root) return 0;
    return leaves(root);
  }
  unsigned height()const{
    if (!root) return 0;
    return height(root);
  }

  unsigned searchCount(bool (*pred)(const t&))const{
    if (!root) return 0;
    return searchCount(pred, root);
  }

  unsigned count()const{
    if (!root) return 0;
    return count(root);
  }

  bool find(t d)const{
    if (!root) return false;
    return find(d, root);
  }

  void print()const{
    if(!root) return;
      print(root);
  }

  void add(t d, const char *p){
    add(d,p,root);
  }
  ~three(){ del(root); }
  three():root(nullptr){}
};





#endif
