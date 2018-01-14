#include <iostream>
#include "city.h"
#include <assert.h>
#include <fstream>
using std::cout;


void test(){

	City c;
	c.add_street("number", "even", 20);
	c.add_street("number", "prime", 60);
	c.add_street("prime", "number", 60);
	c.add_street("even", "10k", 5000);
	c.add_street("10k", "big",50);
	c.add_street("10k", "big",50);
	c.add_street("prime", "optimus",5220);

	assert(c.has_way("number","big"));
	assert(c.has_way("number","big"));
	assert(c.has_way("number","optimus"));

	c.print();
}

string get_inter(string& s){
	unsigned i=s.find(' ');
	string inter = s.substr(0,i);
	s=s.substr(i+1);
	return inter;
}

void read(){
	std::ifstream file;
	file.open("text.txt");
	string read, temp;
	unsigned i(0);
	while (!file.eof()){
		getline(file,read);
		i=read.find(' ');	
		temp=read.substr(0,i);
		read=read.substr(i+1);
		cout<<temp<<'\n';
		}
	
	file.close();
}

int main(){
	read();

	return 0;
}
