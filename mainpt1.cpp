#include "Search.h"
#include "Classifier.h"
#include "Validator.h"
#include <iostream>
#include <time.h>
#include <cstdlib>


using namespace std;

int main(){

    srand(time(NULL));

    Search* search = new Search();

    int input;
    vector<Feature*> allFeatures;

    cout << "Welcome to Jorge and Nikhil's Feature Selection Algorithm." << endl << "Please enter total number of features: ";

    cin >> input;

    //Set up features here
    for (int i = 0; i < input; i++) {
        Feature* temp = new Feature(i + 1);
        allFeatures.push_back(temp);
    }

    cout << "Type the number of the algorithm you want to run" << endl << "1. Forward Selection" << endl << "2. Backward Elimination" << endl;

    cin >> input;

    if (input == 1){
        search->forwardSelection(allFeatures);
    }

    else if (input == 2){
        search->backwardElimination(allFeatures);
    }

    else {
        cout << "Something went wrong." << endl;
        exit(1);
    }

    return 0;
}