#include <iostream>
#include "city.h"
using std::cout;


void test_read(){
	City c;
	c.read("test_read.txt");
	c.print();
}


void test_basics(){
	City c;
	c.read("test_basics.txt");
	c.print();
	cout<<'\n';
	cout<<"Route A -> G == "<<c.has_route("A","G")<<'\n';
	cout<<"Route B -> A == "<<c.has_route("B","A")<<'\n';
	cout<<"Route B -> H == "<<c.has_route("B","H")<<'\n';
	cout<<'\n';

	c.shortest_routes("A","H");
	c.shortest_routes("F","C");
	cout<<'\n';

	//close an intersection and show shortes routes
	vector<string> closed={"C", "F","D"};
	c.close_inters_shortest_routes("A", "H", closed);
	cout<<'\n';

	cout<<"Chain from A == "<<c.check_cycle("A")<<'\n';
	cout<<"Chain from B == "<<c.check_cycle("B")<<'\n';
	cout<<"Chain from C == "<<c.check_cycle("C")<<'\n';
	cout<<'\n';
	
}

void test_street_traversal(){

	City c;
	c.read("test_street_traversal.txt");
	c.print();
	cout<<'\n';
	c.full_trav_streets();
	cout<<'\n';
}

void test_intersection_traversal(){

	City c;
	c.read("test_intersection_traversal.txt");
	c.print();
	cout<<'\n';
	
	cout<<"Is A connected to everything else == "<<c.full_inter("A")<<'\n';
	cout<<"Is B connected to everything else == "<<c.full_inter("B")<<'\n';
	cout<<'\n';
	
	cout<<"Intersection traversal. Strat: C\n";
	c.full_trav_inters("C");
	cout<<'\n';

	cout<<"Intersection traversal. Strat: A\n";
	c.full_trav_inters("A");
	cout<<'\n';
}

void test_dead_end(){

	City c;
	c.read("test_dead_end.txt");
	c.print();
	cout<<'\n';
	c.find_dead_end();
}

int main(){

//	test_read();
//	test_basics();
//	test_street_traversal();
//	test_intersection_traversal();
//	test_dead_end();

	return 0;
}
