//pa2.cpp
//Samuel Stall

#include "pa2.h"

using namespace std;

int main(int argc, char* argv[]) {

	programMode(argc, argv);

	//Initializes Programlist, then creates 32 nodes containing "Free" as the data
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

//Takes in the command line arguments and checks whether the proper arguments were provided, exiting the program if they were not
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

//Prints main menu, taking user input via the userInputInt function and checks that the input is a valid option
int mainMenu() {

	int inputI = 0;
	do{
		cout << endl;
		cout << "1. Add Program \n2. Kill Program \n3. Fragmentation \n4. Print memory \n5. Exit \n" << endl;
		
		try{
			inputI = userInputInt();
		}
		catch(...) {
			cin.ignore(100000, '\n');
			cout << "Error, Input not an integer." << endl;
			return 0;
		}

		if(inputI < 1 || inputI > 5) {
			cout << "Invalid input." << endl;
		}



	}while((inputI < 1 || inputI > 5));

	return inputI;
}

//Takes in user input inside of the function, attempts to convert the string into an int, and returns the int if successful. If the input
//was not of type int, an exception is thrown and caught in the method that called userInputInt()
int userInputInt() {
	string inputS;
	int inputI = 0;
	cin >> inputS;
	cout << endl;

	//Converts the character array into an int, throwing an exception if it wasn't able to
	inputI = stoi(inputS,nullptr,0);

		
	return inputI;
}

//Function for handling the input for program name and size and then calling the addProgram function on the ProgramList object
void menuAdd(ProgramList &l, char* argv[]) {
	string programName;	
	int programSize;
	
	cout << "Program name - ";
	cin >> programName;
	cout << "Program size (KB) - ";
	//Takes input via the userInputInt() method, if anything but an int was inputted, an exception is thrown by the method and caught by the catch statement here
	try {
		programSize = userInputInt();
		int pagesRequired = ceil((double)programSize / 4);

		//Checks if memory inputs are in bounds
		if(programSize <= 0) {
			cout << "Error, Invalid memory entry for Program " << programName << endl;
		}
		else if(programSize > 128) {
			cout << "Error, Not enough memory for Program " << programName << endl;
		}
		else {
			if(l.addProgram(programName, pagesRequired, argv)) {
				cout << "Program " << programName << " added successfully: " << pagesRequired << " page(s) used." << endl; 
			}
		}
	}
	catch(...) {
		cout << "Error, Memory input not an integer." << endl;
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
bool ProgramList::addProgram(string &addData, int pagesRequired, char* argv[]) {
	curr = head;
	int nodeIndexBegin = 0;
	int index = 0;
	int count = 1;

	//Finds the worst index for the program to be placed into 
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
				nodeIndexBegin = index;

				while(curr-> data == "Free") {
					if(curr-> next != NULL) {
						count++;
						index++;
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
				index++;

				//Catch edge case when at the end of the list to check if the last index is Free or not
				if(curr-> data == "Free" && curr-> next == NULL) {
					nodeIndexBegin = index;
					count++;
					index++;

					if(count > pagesMax) {
						pagesMax = count;
						nodeIndexWorst = nodeIndexBegin;
					} 
				} 
			}
		}

		//Adds the program to the list using the index found by the prior process if it will fit into what's available and then return true
		//otherwise return false
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
			cout << "Error, Not enough memory for Program " << addData << endl;
			return false;
		}

	}
	//Finds the best index for the program to be placed into
	else {
		int nodeIndexBest = 0;
		int pagesMin = 32;
		count = 0;

		while(curr-> next != NULL) {
			//If the program already exists, prints error message and returns false
			if(curr-> data == addData) {
				cout << "Error, Program " << addData << " already running." << endl;
				curr = NULL;
				return false;
			}

			if(curr-> data == "Free") {

				while(curr-> data == "Free") {

					if(curr-> next != NULL) {
						count++;
						index++;
						curr = curr-> next;
					}
					else {
						break;
					}

				}

				if(count >= pagesRequired) {

					if(count < pagesMin) {
						pagesMin = count;
						nodeIndexBegin = index - count;
						nodeIndexBest = nodeIndexBegin;
					} 
				}

			}
			else if(curr-> next != NULL) {
				curr = curr->next;
				index++;

				//Catch edge case when at the end of the list to check if the last index is Free or not
				if(curr-> data == "Free" && curr-> next == NULL) {
					count++;
					index++;

					if(count >= pagesRequired) {

						if(count < pagesMin) {
							pagesMin = count;
							nodeIndexBegin = index - count;
							nodeIndexBest = nodeIndexBegin;
						} 
					}
				} 
			}
			count = 0;

		}

		//Adds the program to the list using the index found by the prior process if it will fit into what's available and then return true
		//otherwise return false
		if(pagesMin >= pagesRequired) {
			curr = head;
			for(int i = 0; i < nodeIndexBest; i++) {
				curr = curr-> next;
			}
			for(int i = 0; i < pagesRequired; i++) {
				//Catch edge case if the entire memory is filled and the index is invalid
				if(curr-> data == "Free") {
					curr-> data = addData;
					curr = curr-> next;
				}
				else {
					cout << "Error, Not enough memory for Program " << addData << endl;
					return false;
				}
			}
			curr = NULL;
			return true;
		}
		else {
			curr = NULL;
			cout << "Error, Not enough memory for Program " << addData << endl;
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
		else {
			curr = curr-> next;

			//Check edge case of a program being in the last memory slot
			if(curr-> next == NULL) {
				if(curr-> data != "Free") {
					count++;
				}
				break;
			}
		}
	}

	return count;
}

//Prints all data stored in the List in 4 by 8 formatting 
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