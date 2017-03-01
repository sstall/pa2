//pa2.cpp
//Samuel Stall

#include "pa2.h"

using namespace std;

int main(int argc, char* argv[]) {

	programMode(argc, argv);

	//Initializes Programlist, creating 32 nodes containing "Free" as the data
	ProgramList l;

	for(int i = 0; i < 32; i++) {
		l.addNode("Free");
	} 

	int userChoice = 0;

	do{
		userChoice = mainMenu();

		switch(userChoice) {
			//Add program
			case 1: {
				menuAdd(l, argv);
				break;
			} 
			//Kill program
			case 2: {
				string removeData;

				cout << "Program name - ";
				cin >> removeData;

				l.removeProgram(removeData);
				break;
			}
			//Fragmentation
			case 3: {
				cout << "There are " << l.fragments() << " fragment(s)." << endl;
				break;
			}
			//Print memory
			case 4: {
				l.printList();
				break;
			}
			//Exit
			case 5: {

				break;
			}
		}
	}while(userChoice != 5);

	return 0;
}

void programMode(int argc, char* argv[]) {
	cout << endl;

	if(argc != 2) {
		cout << "Invalid number of arguments. Valid arguments: best/worst." << endl;
		exit(EXIT_SUCCESS);
	}
	else if(strcmp(argv[1], "worst") == 0) {
		cout << "Using worst fit algorithm" << endl;
	}
	else if(strcmp(argv[1], "best") == 0) {
		cout << "Using best fit algorithm" << endl;
	}
	else{
		cout << "Invalid argument. Valid arguments: best/worst." << endl;
		exit(EXIT_SUCCESS);
	}
}

int mainMenu() {

	int inputI = 0;
	do{
		cout << "1. Add Program \n2. Kill Program \n3. Fragmentation \n4. Print memory \n5. Exit \n" << endl;
		inputI = userInputInt();

		if(inputI < 1 || inputI > 5) {
			cout << "Invalid input." << endl;
		}

	}while((inputI < 1 || inputI > 5));

	return inputI;
}

int userInputInt() {
	string inputS;
	int inputI = 0;
	try {
			cin >> inputS;
			cout << endl;

			//Converts the character array into an int, throwing an exception if it wasn't able to
			inputI = stoi(inputS,nullptr,0);

		//Catches the exception if thrown by stoi
		} catch(...) {
			cin.ignore(100000, '\n');
			cout << "Error, Input not an integer." << endl;
			return 0;
		}
	return inputI;
}

//Function for handling the input for program name and size and then calling the addProgram function on the ProgramList object
void menuAdd(ProgramList &l, char* argv[]) {
	string addData;	
	int programSize;
	
	cout << "Program name - ";
	cin >> addData;
	cout << "Program size (KB) - ";
	programSize = userInputInt();
	int pagesRequired = ceil((double)programSize / 4);

	if(programSize <= 0) {
		cout << "Error, Invalid memory entry for Program " << addData << endl;
	}
	else if(programSize > 128) {
		cout << "Error, Not enough memory for Program " << addData << endl;
	}
	else {
		if(l.addProgram(addData, pagesRequired, argv)) {
			cout << "Program " << addData << " added successfully: " << pagesRequired << " page(s) used." << endl; 
		}
		else {
			cout << "Error, Not enough memory for Program " << addData << endl;
		}
	}
}

//Inializes all pointers to NULL
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
				curr = NULL;
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
			curr = NULL;
			return true;
		}
		else {
			curr = NULL;
			return false;
		}

	}
	else {
		int nodeIndexBest = 0;
		int pagesMin = 32;
		count = 0;

		while(curr-> next != NULL) {
			
			if(curr-> data == addData) {
				cout << "Error, Program " << addData << " already running." << endl;
				curr = NULL;
				return false;
			}

			if(curr-> data == "Free") {

				while(curr-> data == "Free") {

					if(curr-> next != NULL) {
						count++;
						curr = curr-> next;
						countStart++;
					}
					else {
						break;
					}

				}

				if(count >= pagesRequired) {

					if(count < pagesMin) {
						pagesMin = count;
						nodeIndexBegin = countStart - count;
						nodeIndexBest = nodeIndexBegin;
					} 
				}
			}
			else if(curr-> next != NULL) {
				curr = curr->next;
				countStart++;
			}

			count = 0;

		}

		if(pagesMin >= pagesRequired) {
			curr = head;
			for(int i = 0; i < nodeIndexBest; i++) {
				curr = curr-> next;
			}
			for(int i = 0; i < pagesRequired; i++) {
				curr-> data = addData;
				curr = curr-> next;
			}
			curr = NULL;
			return true;
		}
		else {
			curr = NULL;
			return false;
		}

	}

}

//Finds how many fragments are present in the ProgramList
int ProgramList::fragments() {
	curr = head;
	int count = 0;

	while(curr-> next != NULL) {

		if(curr-> data != "Free") {
			count++;

			while(curr-> next != NULL)
				if(curr-> data == "Free") {
					break;
				}
				else {
					curr = curr-> next;
				}
		}

		if(curr-> next == NULL) {
			break;
		}

		curr = curr-> next;
	}

	return count;
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