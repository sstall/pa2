//pa2.h

#include "stdio.h"
#include <iostream>

using namespace std;

void programMode(int argc, char* argv[]);

struct node {
	string data;
	node* next;
	bool isEmpty;
};


class List {
private:
	node* head;
	node* curr;

public:
	List();
	void addNode(string data);
	void printList();
};

List::List() {
	head = NULL;
	curr = NULL;
}

void List::addNode(string data) {
	node* p = new node;
	p->next = NULL;
	p->data = data;

	if(head != NULL) {
		curr = head;

		while(curr-> next != NULL) {
			curr = curr-> next;
		}
		curr-> next = p;
	}
	else {
		head = p;
	}
}

void List::printList() {
	curr = head;

	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 8; j++) {
			if(curr-> data == "Free") {
				cout << curr-> data << " ";
				curr = curr-> next;
			}
			else {
				cout << curr-> data << " ";
				curr = curr-> next;
			}
		}
		cout << "\n";
	}
}