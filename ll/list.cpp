#include "list.h"
#include <iostream>
using std::cout;

void list::pop() {
	if (start == nullptr) return;
	if (start->next == nullptr) {
		delete start;
		start = nullptr;
		return;
	}
	pop(start);
}


void list::pop(node* top) {
	if (top->next->next == nullptr) {
		delete top->next;
		top->next = nullptr;
		return;
	}
	pop(top->next);
}


void list::push_back(int x) {
	if (start == nullptr) {
		start = new node(x);
		return;
	}
	push_back(x, start);
}

void list::push_back(int x, node* top) {
	if (top->next == nullptr) {
		top->next = new node(x);
		return;
	}
	push_back(x, top->next);
	
}


void list::print(node* top)const {
	if (top == nullptr) return;
	else {
		cout << top->data << '\n';
		print(top->next);
		return;
	}
}

void list::print()const {
	print(start);
}

list::list():start(nullptr) {}


list::~list()
{
}
