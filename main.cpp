#include "Search.h"
#include "Classifier.h"
#include "Validator.h"
#include "Feature.h"
#include "Node.h"
#include <iostream>
#include <time.h>
#include <cstdlib>
#include <chrono>

using namespace std;
using namespace std::chrono;

inline double converter(string IEEE) {

    string nums = IEEE.substr(0, IEEE.find('e'));
    string exps = IEEE.substr(IEEE.find('e') + 1, 4);

    double num = stod(nums);
    int exp = stoi(exps);

    if (exp <= 0) {
        for (int i = exp; i < 0; i++) {
            num = num / 10;
        }
    }
    else {
        for (int i = 0; i < exp; i++) {
            num = num * 10;
        }
    }

    return num;
}

inline void normalizeData(string inputFile, vector<vector<double>>& train_instances, vector<double>& train_labels) {
    ifstream inFS;

    inFS.open(inputFile);

    if (!inFS.is_open()){
        cout << "Error opening " << inputFile << endl;
        exit(1);
    }

    stringstream inSS;
    string inputLine;

    while(getline(inFS, inputLine)){
        inSS << inputLine;
        // cout << inputLine << endl;
        string IEEE;
        inSS >> IEEE;
        train_labels.push_back(converter(IEEE));
        vector<double> temp;
        while (inSS >> IEEE) {
            temp.push_back(converter(IEEE));
        }
        train_instances.push_back(temp);
        temp.clear();
        inSS.clear();
    }
    
    ///////////////////////////////////////////////////////////////////
    cout << "This dataset has " << train_instances.at(0).size() << " features (not including the class attribute), with " << train_labels.size() << " instances." << endl;

    cout << "Please wait while I normalize the data...   ";

    vector<double> mean(train_instances.at(0).size(), 0.0);
    vector<double> standardDeviation(train_instances.at(0).size(), 0.0);

    //Mean
    for (int i = 0; i < train_instances.size(); i++){
        for (int j = 0; j < train_instances.at(i).size(); j++) {
            mean.at(j) += train_instances.at(i).at(j);
        }
    }
    for (int i = 0; i < mean.size(); i++){
        mean.at(i) = mean.at(i) / train_instances.size();
    }

    //StandardDeviation
    for (int i = 0; i < train_instances.size(); i++){
        for (int j = 0; j < train_instances.at(i).size(); j++) {
            standardDeviation.at(j) += pow((train_instances.at(i).at(j) - mean.at(j)), 2);
        }
    }
    for (int i = 0; i < standardDeviation.size(); i++) {
        standardDeviation.at(i) = sqrt(standardDeviation.at(i) / train_instances.size());
    }

    //zscaling
    for (int i = 0; i < train_instances.size(); i++){
        for (int j = 0; j < train_instances.at(i).size(); j++) {
            train_instances.at(i).at(j) = (train_instances.at(i).at(j) - mean.at(j)) / standardDeviation.at(j);
        }
    }
    cout << "Done!" << endl;
}

int main(){

    srand(time(NULL));

    int input;
    string inputFile;  //small_dataset_part3.txt

    cout << "Welcome to Jorge and Nikhil's Feature Selection Algorithm." << endl;

    cout << "Type in the name of the file to test: ";

    cin >> inputFile;

    cout << "Type the number of the algorithm you want to run" << endl << "1. Forward Selection" << endl << "2. Backward Elimination" << endl;

    cin >> input;

    vector<vector<double>> train_instances;
    vector<double> train_labels;

    normalizeData(inputFile, train_instances, train_labels);

    Validator* validator = new Validator(train_instances, train_labels);

    Search* search = new Search(validator);
    vector<Feature*> allFeatures;

    for(int i = 0; i < train_instances.at(0).size(); i++) {
        Feature* temp = new Feature(i + 1);
        allFeatures.push_back(temp);
    }

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