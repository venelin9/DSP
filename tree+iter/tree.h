#ifndef __TREE__
#define __TREE__

#include <iostream>
using std::cout;
#include <stack>
using std::stack;

template <class t>
struct node{
  node<t> *left, *right;
  t data;
  node (t _d):data(_d),left(nullptr),right(nullptr){}
  node():left(nullptr), right(nullptr){}
};

template <class t>
struct task{
  task(){}
  task(node<t> *n, bool b):nod(n), toprint(b){}
  node<t> *nod;
  bool toprint;
};


template <class t>
class tree{
public:
  tree():root(nullptr){}
  ~tree(){ del(root); }
  void add(t d, const char *p){
    add(d,p,root);
  }

  class Iterator{
public:
  Iterator(node<t>* r){
    if(r){
      st.push(task<t>(r,false));
    windstack();
    }
  }
  bool operator!=(const Iterator &o)const{
    if (st.empty() && o.st.empty()) return false;
    if (st.empty()!=o.st.empty()) return true;
    if (st.top().nod==o.st.top().nod) return false;
    if (st.top().toprint==o.st.top().toprint) return false;
    return true;
  }
  t operator*()const{
    return st.top().nod->data;
  }
  t operator*(){
    return st.top().nod->data;
  }
  void operator++(){
      st.pop();
      windstack();
  }
private:
  stack<task<t>> st;
  void windstack(){
      while (!st.empty() && st.top().toprint==false){
        task<t> crr=st.top();
        st.pop();

        if (crr.nod->right)
          st.push(task<t>(crr.nod->right,false));

        st.push(task<t>(crr.nod,true));

        if (crr.nod->left)
          st.push(task<t>(crr.nod->left,false));
      }
  }
  };

  Iterator begin()const{
    return Iterator(root);
  }
  Iterator end()const{
    return Iterator(nullptr);
  }

private:
  node<t>* root;
  void add(t d, const char *p, node<t> *&r){
    if (!r){
      r = new node<t>(d);
      return;
    }
    if (p[0]=='L') {
      add(d, p+1, r->left);
      return;
    }
    if (p[0]=='R'){
      add(d, p+2, r->right);
      return;
    }
    cout<<"Error.\n";
  }
  void del(node<t> *r){
    if (!r) return;
    del(r->left);
    del(r->right);
    delete r;
  }


};



#endif
