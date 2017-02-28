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
				string addData;	
				int programSize;
	
				cout << "Program name - ";
				cin >> addData;
				cout << "Program size (KB) - ";
				programSize = userInputInt();
				int pagesRequired = ceil((double)programSize / 4);

				if(programSize <= 0) {
					cout << "Error, invalid memory entry for Program " << addData << endl;
				}
				else if(programSize > 128) {
					cout << "Error, not enough memory for Program " << addData << endl;
				}
				else {
					if(l.addProgram(addData, pagesRequired, argv)) {
						cout << "Program " << addData << " added successfully: " << pagesRequired << " page(s) used." << endl; 
					}
				}
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
			cout << std::endl;

			//Converts the character array into an int, throwing an exception if it wasn't able to
			inputI = stoi(inputS,nullptr,0);

		//Catches the exception if thrown by stoi
		} catch(...) {
			cin.ignore(100000, '\n');
			cout << "ERROR: Input not an integer." << endl;
			return 0;
		}
	return inputI;
}