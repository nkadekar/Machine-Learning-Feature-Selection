#include "Search.h"
#include "Classifier.h"
#include "Validator.h"
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
}

int main(){
    vector<vector<double>> train_instances;
    vector<double> train_labels;
    string inputFile;
    int input;

    srand(time(NULL));

    cout << "Welcome to Jorge and Nikhil's nearest neighbor - leave one out validation program." << endl;
    cout << "Which file would you like to to test : " << endl << "1. Small Dataset (10 features)" << endl << "2. Large Dataset (40 features)" << endl;

    cin >> input;

    if (input == 1) {
        inputFile = "small_dataset.txt";
    }
    else if (input == 2) {
        inputFile = "large_dataset.txt";
    }
    else {
        cout << "Something went wrong." << endl;
        exit(1);
    }

    cout << "Please wait while I normalize the data...   ";
    auto start = high_resolution_clock::now();

    normalizeData(inputFile, train_instances, train_labels);

    auto end = high_resolution_clock::now();
    auto duration = duration_cast<microseconds>(end - start);
    cout << "Done! Time taken: " << duration.count() << " microseconds" << endl;

    vector<int> threefiveseven = {3, 5, 7};
    vector<int> onefifteentwentyseven = {1, 15, 27};

    Validator* validator = new Validator(train_instances, train_labels);

    double result;

    if (input == 1) {
        auto start = high_resolution_clock::now();
        cout << "Using features subset {3, 5, 7}" << endl;
        result = validator -> leave_one_out_validation(threefiveseven);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        cout << "Accuracy = " << result << ". Time taken: " << duration.count() << " microseconds" << endl;
    }
    else if (input == 2) {
        auto start = high_resolution_clock::now();
        cout << "Using features subset {1, 15, 27}" << endl;
        result = validator -> leave_one_out_validation(onefifteentwentyseven);
        auto end = high_resolution_clock::now();
        auto duration = duration_cast<microseconds>(end - start);
        cout << "Accuracy = " << result << ". Time taken: " << duration.count() << " microseconds" << endl;
    }

    return 0;
}