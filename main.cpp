#include "Search.h"
#include <iostream>
#include <time.h>
#include <cstdlib>

using namespace std;

int main(){
    Search* search = new Search();

    int input;

    cout << "Welcome to Jorge and Nikhil's Feature Selection Algorithm." << endl << "Please enter total number of features: ";

    cin >> input;

    //Set up features here

    cout << "Type the number of the algorithm you want to run" << endl << "1. Forward Selection" << endl << "2. Backward Elimination" << endl;

    cin >> input;

    if (input == 1){
        search->forwardSelection();
    }

    else if (input == 2){
        search->backwardElimination();
    }

    else {
        cout << "Something went wrong." << endl;
        exit(1);
    }

    return 0;
}