#ifndef __NODE__
#define __NODE__



struct node
{
	int data;
	node* next;
	node(int x):data(x), next(nullptr) {}
	node() {}
};







#endif // !__NODE__
