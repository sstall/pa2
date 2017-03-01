//pa2.h

#include "stdio.h"
#include <stdlib.h>
#include <string.h>
#include <iostream>
#include <cmath>

using namespace std;

class ProgramList;
void programMode(int argc, char* argv[]);
void menuAdd(ProgramList &l, char* argv[]);
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
	int fragments();
	void printList();
};


