//pa2.h

#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <cmath>

using namespace std;

void programMode(int argc, char* argv[]);
int mainMenu();
int userInputInt();

struct node {
	string data;
	node* next;
};

class ProgramList {
private:
	node* head;
	node* curr;
	node* temp;
public:
	ProgramList();
	void addNode(string addData);
	void removeProgram(string &removeData);
	bool addProgram(string addData, int programSize, char* argv[]);
	void printList();
};

ProgramList::ProgramList() {
	head = NULL;
	curr = NULL;
	temp = NULL;
}

//Adds a new node to the List
void ProgramList::addNode(string addData) {
	node* p = new node;
	p->next = NULL;
	p->data = addData;

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

//Removes a node from the List if it exists in the List
void ProgramList::removeProgram(string &removeData) {
	curr = head;
	bool nodeExist = false;
	int pages = 0;

	while(curr != NULL) {

		if(curr-> data == removeData) {
			curr-> data = "Free";
			nodeExist = true;
			pages++;
		}
		else {
			curr = curr-> next;
		}

	}

	if(nodeExist && pages != 0) {
		cout << "Program " << removeData << " successfully killed, " << pages << " page(s) reclaimed." << endl;
	}
	else {
		cout << "Program " << removeData << " not found." << endl;
	}
	curr = NULL;

}

//Replaces a node, finding the place for it using the best or worst fit algotrithm
bool ProgramList::addProgram(string addData, int pagesRequired, char* argv[]) {
	curr = head;
	int pages = 0;
	int nodeIndex = 0;

	if(strcmp(argv[1], "worst") == 0) {
		int spaceMax = 0;
		int nodeIndexMax = 0;
		while(curr != NULL) {
			if(curr-> data == addData) {
				cout << "Error, program " << addData << " already running." << endl;
				return false;
			}
			else if(curr-> data == "Free") {
				nodeIndex++;
				pages++;
			}
			else if(curr-> data != "Free") {
				if(pages > spaceMax) {
					spaceMax = pages;
					nodeIndexMax = nodeIndex - pages + 1;
					pages = 0;
					nodeIndex++;
					cout << spaceMax << "S";
					cout << nodeIndexMax << "I";
				}
				else{
					pages = 0;
					nodeIndex++;
				}

			}
			curr = curr-> next;
		}

		if(nodeIndexMax > 31) {
			cout << "Error, not enough available memory for program " << addData << endl;
			return false;
		}
			
		curr = head;
		if(spaceMax <= pagesRequired) {
			for(int i = 0; i < nodeIndexMax; i++) {
				curr = curr-> next;
			}
			for(int i = 0; i < pagesRequired; i++) {
				curr-> data = addData;
				curr = curr-> next;
			}

			return true;
		}
	return false;

	}
	else if(strcmp(argv[1], "best") == 0) {

	} 

}

//Prints all data stored in the List
void ProgramList::printList() {
	curr = head;

	for(int i = 0; i < 4; i++) {
		for(int j = 0; j < 8; j++) {
			if(curr-> data == "Free") {
				cout << curr-> data << " ";
				curr = curr-> next;
			}
			else {
				cout << curr-> data << "  ";
				curr = curr-> next;
			}
		}
		cout << endl;
	}

	cout << endl;
}