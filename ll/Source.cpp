#include <iostream>
#include "node.h"
#include "list.h"
using std::cout;

int main() {
	
	list f;
	f.push_back(100);

	f.push_back(123);
	
	f.push_back(555);

	f.pop();
	
	f.print();

	getchar();
	return 0;
}