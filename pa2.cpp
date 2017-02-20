//pa2.cpp
//Samuel Stall

#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "pa2.h"

using namespace std;

int main(int argc, char* argv[]) {

	programMode(argc, argv);

	List l;

	for(int i = 0; i < 32; i++) {
		l.addNode("Free");
	}

	l.printList();

	return 0;
}

void programMode(int argc, char* argv[]) {

	if(argc != 2) {
		cout << "Invalid number of arguments. Exiting program." << endl;
		exit(EXIT_SUCCESS);
	}
	else if(strcmp(argv[1], "worst") == 0) {
		cout << "Using worst fit algorithm" << endl;
	}
	else if(strcmp(argv[1], "best") == 0) {
		cout << "Using best fit algorithm" << endl;
	}
	else{
		cout << "Invalid argument. Valid inputs: best/worst. Exiting" << endl;
		exit(EXIT_SUCCESS);
	}
}