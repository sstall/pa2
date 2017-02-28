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

	//Loops until the next node is NULL, looking for any nodes with data that contains the program to be removed
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

	//Prints out whether the program was found and if found, how many pages reclaimed
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
	int nodeIndexBegin = 0;
	int countStart = 0;
	int count = 1;

	if(strcmp(argv[1], "worst") == 0) {
		int nodeIndexWorst = 0;
		int pagesMax = 0;
		
		while(curr-> next != NULL) {
			//If the program already exists, prints error message and returns false
			if(curr-> data == addData) {
				cout << "Error, Program " << addData << " already running." << endl;
				return false;
			}

			if(curr-> data == "Free") {
				nodeIndexBegin = countStart;

				while(curr-> data == "Free") {
					if(curr-> next != NULL) {
						count++;
						countStart++;
						curr = curr-> next;
					}
					else {
						break;
					}

					if(count > pagesMax) {
						pagesMax = count;
						nodeIndexWorst = nodeIndexBegin;
					}
				}
				count = 0;
			}
			else if(curr-> next != NULL) {
				curr = curr-> next;
				countStart++;
			}
		}

		if(pagesMax >= pagesRequired) {
			curr = head;
			for(int i = 0; i < nodeIndexWorst; i++) {
				curr = curr-> next;
			}
			for(int i = 0; i < pagesRequired; i++) {
				curr-> data = addData;
				curr = curr-> next;
			}
			return true;
		}
		else {
			return false;
		}

	}
	else if(strcmp(argv[1], "best") == 0) {
		int nodeIndexBest = 0;
		int pagesMin = 32;
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