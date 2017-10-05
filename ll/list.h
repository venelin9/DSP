#ifndef __LIST__
#define __LIST__
#include "node.h"


class list
{
public:
	list();
	~list();
	void print()const ;
	void push_back(int);
	void pop();

private:
	node* start;
	
	void pop(node*);
	void print(node*)const;
	void push_back(int, node*);

};






#endif // !__LIST__