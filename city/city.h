#ifndef __CITY__
#define __CITY__

#include <iostream>
#include <vector>
#include <set>
#include <string>
using std::string;
using std::cout;
using std::vector;
using std::set;

template <class T>
int index_of(const T&x, const vector<T>& v){
	for (unsigned i(0); i<v.size(); i++){
		if (v[i]==x) return i;
	}
	return -1;
}

struct street{
	string connects;
	unsigned length;
	street(const string& n, unsigned l):connects(n),length(l){}
};

std::ostream& operator << (std::ostream& out, const street& s){
	out<<'('<<s.connects<<", "<<s.length<<") ";
	return out;
}

bool operator < (const street& a, const street& b){
	return a.length<b.length;
}

class City{
private:
	vector<string> inters;
	vector<set<street> > streets;	
	
	bool has_inter(const string& n) const{
		return index_of(n,inters) != -1;
	}

	bool has_direct_way(const string& a, const string& b)const{
		if (!has_inter(a) || !has_inter(b)) return false;
		int i(index_of(a,inters));
		for (set<street>:: iterator it=streets[i].begin(); it!=streets[i].end(); ++it){
			if ((*it).connects==b) return true;
		}
		return false;
	}
	
	bool check_way(const string& a, const string& b, vector<string>& visited)const{
		if (has_direct_way(a,b)) return true;
		int i(index_of(a,inters));
		visited.push_back(a);
		for (set<street>:: iterator it=streets[i].begin(); it!=streets[i].end(); ++it){
			if (index_of((*it).connects,visited)==-1){
				if (check_way((*it).connects,b,visited)) return true;
			}
		}
		return false;
	}

public:
	City(){};

	bool has_way(const string& a, const string& b) const{
		if (!has_inter(a) || !has_inter(b)) return false;
		if (has_direct_way(a,b)) return true;
		vector<string> visited={};
		return check_way(a,b,visited);
	}

	void print()const{
		for (unsigned i(0); i<inters.size(); i++){
			cout<<inters[i]<<" -> ";
			for (set<street>:: iterator it=streets[i].begin(); it!=streets[i].end(); ++it){
				cout<<*it;
			}
			cout<<'\n';
		}
	}

	void add_inter(const string& n){
		if (!has_inter(n)){
			inters.push_back(n);
			streets.push_back({});
		}
	}

	void add_street(const string& a, const string& b, unsigned l){
		add_inter(a);
		add_inter(b);
		streets[index_of(a,inters)].insert({b,l});
	}

};


#endif
