#ifndef __CITY__
#define __CITY__

#include <iostream>
#include <vector>
#include <set>
#include <string>
#include <fstream>
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

struct route{
	vector<string> passes;
	unsigned length;
	route(const vector<string>& p, unsigned l): passes(p), length(l){}
};

bool operator < (const route& a, const route& b){
	return a.length<b.length;
}

std::ostream& operator<<(std::ostream& out, const route& r){
	for (unsigned i(0); i<r.passes.size(); i++)
		out<<r.passes[i]<<" -> ";
	out<<r.length<<'\n';
	return out;
}

//Edge + Weight
struct street{
	string source;
	string connects;
	unsigned length;
	street(const string& s, const string& n, unsigned l):source(s), connects(n),length(l){}
	bool operator != (const street& o)const{
		return connects!=o.connects && length != o.length;
	}
	bool operator == (const street& o)const{
		return connects==o.connects && length == o.length;
	}
};

std::ostream& operator << (std::ostream& out, const street& s){
	out<<'('<<s.source<<"->"<<s.connects<<" :"<<s.length<<") ";
	return out;
}

bool operator < (const street& a, const street& b){
	return a.length<=b.length;
}

//Graph
class City{
private:
	vector<set<street> > streets;	
	vector<string> inters;
	unsigned num_of_streets;

	void add_inter(const string& n){
		if (!has_inter(n) && !n.empty()){
			inters.push_back(n);
			streets.push_back({});
		}
	}

	void add_street(const string& a, const string& b, unsigned l){
		if (!a.empty() && !b.empty() && !has_direct_route(a,b)){
			add_inter(a);
			add_inter(b);
			streets[index_of(a,inters)].insert({a,b,l});
			num_of_streets++;
		}
	}

	bool has_inter(const string& n) const{
		if (n.empty()) return false;
		return index_of(n,inters) != -1;
	}

	bool has_direct_route(const string& a, const string& b)const{
		if (!has_inter(a) || !has_inter(b)) return false;
		int i(index_of(a,inters));
		for (set<street>:: iterator it=streets[i].begin(); it!=streets[i].end(); ++it){
			if ((*it).connects==b) return true;
		}
		return false;
	}
	
	//	has_route ->
	bool check_route(const string& a, const string& b, vector<string> visited)const{
		if (has_direct_route(a,b)) return true;
		int i(index_of(a,inters));
		visited.push_back(a);
		for (set<street>:: iterator it=streets[i].begin(); it!=streets[i].end(); ++it){
			if (index_of((*it).connects,visited)==-1){
				if (check_route((*it).connects,b,visited)) return true;
			}
		}
		return false;
	}

	//	distance between 2 adjacent vertexes
	int get_direct_distance(const string& a, const string& b)const {
		if (!has_direct_route(a,b)) return -1;
		int i(index_of(a,inters));
		for (set<street>:: iterator it=streets[i].begin(); it!=streets[i].end(); ++it){
			if ((*it).connects==b) return (*it).length;
		}
		return -1;
	}

	//	distance between 2 vertexes
	int get_route_distance(const vector<string>& r)const{
		int dist(0);
		if (r.empty()) return -1;
		for (unsigned i(0); i<r.size()-1; i++){
			if (!has_direct_route(r[i],r[i+1])) return -1;
			dist+=get_direct_distance(r[i],r[i+1]);
		}
		return dist;
	}
	
	void get_routes(const string& a, const string& b, vector<string> visited, vector<vector<string> >& routes)const {
		visited.push_back(a);
		if (has_direct_route(a,b)) {routes.push_back(visited); }
		int i(index_of(a,inters));
		for (set<street>:: iterator it=streets[i].begin(); it!=streets[i].end(); ++it){
			if (index_of((*it).connects,visited)==-1){
				get_routes((*it).connects,b,visited,routes);
			}
		}
	}

	//	delete vertex
	void close_inter(const string& a){
		if (!has_inter(a)) return;
		int iv(index_of(a,inters));
		inters.erase(inters.begin()+iv);
		streets.erase(streets.begin()+iv);
		for (unsigned i(0); i<streets.size(); i++){
			for (set<street>::iterator it=streets[i].begin(); it!=streets[i].end(); ++it){
				if ((*it).connects == a ) streets[i].erase(it);
			}
		}
	}	
	
	//	
	void check_traversal(const string& a, vector<string> visited, vector<string>& route_trev)const{
		int i(index_of(a,inters));
		visited.push_back(a);
		if (visited.size() == inters.size()) {
			route_trev=visited;	
			return;
		}
		for (set<street>:: iterator it=streets[i].begin(); it!=streets[i].end(); ++it){
			if (index_of((*it).connects,visited)==-1)
				check_traversal( (*it).connects ,visited,route_trev);
		}
	}
	
	
	void check_street_trav(const string& a, vector<street> visited, vector<street>& route_trev)const{
		int i(index_of(a,inters));
		if (visited.size() == num_of_streets) {
			route_trev=visited;	
			return;
		}
		for (set<street>:: iterator it=streets[i].begin(); it!=streets[i].end(); ++it){
			if (index_of((*it), visited)==-1){
				visited.push_back(*it);
				check_street_trav( (*it).connects, visited, route_trev);
				visited.pop_back();
			}
		}
	}


public:
	City():num_of_streets(0){};
	City(const City* o): streets(o->streets), inters(o->inters), num_of_streets(o->num_of_streets){}

	//	prints out all dead end streets
	void find_dead_end()const{
		vector<street> dead;
		vector<string> dead_inters;
		for (unsigned i(0); i<inters.size(); i++)
			if (streets[i].empty()) dead_inters.push_back(inters[i]);

		for (unsigned k(0); k<dead_inters.size(); k++){
			for (unsigned i(0); i<streets.size(); i++){
				for (set<street>:: iterator it=streets[i].begin(); it!=streets[i].end(); ++it){
					if ( (*it).connects == dead_inters[k] ) dead.push_back(*it);
				}
			}
		}
		if (dead.empty()) {cout<<">No dead ends found.\n"; return; }
		cout<<">Dead end streets...\n";
		for (unsigned i(0); i<dead.size(); i++)
			cout<<dead[i]<<'\n';
		cout<<">End...\n";
	}

	
	//	prints out a full traversal of edges
	void full_trav_streets()const {
		vector<street> visited={};
		vector<street> route_trev={};
		for (unsigned i(0); i<inters.size() && route_trev.empty(); i++)
			check_street_trav(inters[i], visited, route_trev);
		if (route_trev.empty()) {cout<<">No routes found.\n"; return; }
		cout<<">Traversing the streets...\n";
		for (unsigned i(0); i<route_trev.size(); i++)
			cout<<route_trev[i];
		cout<<"\n>Traversing finished...\n";

	}


	//	checks if a vertex is connected to all others
	bool full_inter(const string& a){
		if (!has_inter(a)) return false;
		unsigned k(index_of(a,inters));
		for (unsigned i(0); i<k; i++){
			bool check(false);
			for(set<street>::iterator it=streets[k].begin(); it!=streets[k].end(); ++it){
				if (inters[i]==(*it).connects) check=true;
			}
			if (!check) return false;
		}
		for (unsigned i(k+1); i<inters.size(); i++){
			bool check(false);
			for(set<street>::iterator it=streets[k].begin(); it!=streets[k].end(); ++it){
				if (inters[i]==(*it).connects) check=true;
			}
			if (!check) return false;
		}
		return true;
	}

	//	prints out a full traversal of vertexes
	void full_trav_inters(const string& a) const {
		vector<string> visited={};
		vector<string> route_trev={};
		check_traversal(a, visited, route_trev);	
		if (route_trev.empty()) {cout<<">No routes found.\n"; return; }
		cout<<">Traversing the intersections...\n";
		for (unsigned i(0); i<route_trev.size(); i++)
			cout<<" -> "<<route_trev[i];
		cout<<"\n>Traversing finished...\n";
	}

	//	checks of a vertex is contained in a loop
	bool check_cycle(const string& a) const{
		if (!has_inter(a)) return false;
		vector<string> visited={};
		return check_route(a,a,visited);
	}

	//	"deletes" edges and print the shortest paths between 2 vertexes
	void close_inters_shortest_routes(const string& a, const string& b, vector<string>& close){
		City d(this);
		for (unsigned i(0); i<close.size(); i++){
			d.close_inter(close[i]);
		}
		cout<<">Closing intersections...\n";
		d.shortest_routes(a,b);
		cout<<">Reopening intersections...\n";
	}

	//	prints out the shortest path between 2 vertexes
	void shortest_routes(const string& a, const string& b){
		if (!has_route(a,b)) return;
		vector<string> visited={};
		vector<vector<string> > routes={};
		get_routes(a,b,visited,routes);
		set<route> sorted_routes={};
		cout<<">Shortest routes:\n";
		for(vector<vector<string> >::iterator i=routes.begin(); i!=routes.end(); ++i){ 
			(*i).push_back(b); 
			sorted_routes.insert({(*i), get_route_distance(*i)});
		}
		unsigned h(1);
		for (set<route>::iterator i=sorted_routes.begin(); i!=sorted_routes.end() && h<=3; ++i, ++h){
			cout<<h<<") "<<(*i);
		}
	}

	//	checks if there is a route between 2 vertexes
	bool has_route(const string& a, const string& b) const{
		if (!has_inter(a) || !has_inter(b)) return false;
		if (has_direct_route(a,b)) return true;
		vector<string> visited={};
		return check_route(a,b,visited);
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

	//	! make sure the file is correctly written before reading (no segmatic check)
	void read(const string& s){
		std::ifstream file;
		file.open(s);
		string line, temp, in;
		int i(0);
		unsigned d(0);
		while (!file.eof()){
			getline(file,line);
			i=line.find(' ');	
			in=line.substr(0,i);
			line=line.substr(i+1);
			add_inter(in);
			while (!line.empty() && i!=-1){
				i=line.find(' ');	
				temp=line.substr(0,i);
				line=line.substr(i+1);
				i=line.find(' ');	
				d=std::stoi(line.substr(0,i));
				line=line.substr(i+1);
				add_street(in,temp,d);
			}
		}
		file.close();
	}
};


#endif
