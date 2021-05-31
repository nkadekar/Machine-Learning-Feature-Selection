#ifndef CLASSIFIER_H
#define CLASSIFIER_H

#include <vector>
#include <string>
#include <fstream>
#include "Node.h"
#include <sstream>
#include <cmath>
#include <bits/stdc++.h>

using namespace std;

class Classifier {
    public:
        vector<vector<double>> train_instances;
        vector<double> train_labels;

    public: 
        Classifier() {}

        void train(vector<vector<double>> train_instances, vector<double> train_labels) {
            this->train_instances = train_instances;
            this->train_labels = train_labels;
        }

        double test(vector<double> test_instance) {
            double minDistanceLabel = INT_MAX;
            double minDistance = INT_MAX;

            for (int i = 0; i < train_instances.size(); i++) {
                double distance = euclideanDistance(train_instances.at(i), test_instance);
                if (minDistance > distance) {
                    minDistance = distance;
                    minDistanceLabel = train_labels.at(i);
                }
            }
            return minDistanceLabel;
        }

        double euclideanDistance(vector<double> trained_instance, vector<double> test_instance){
            double sum = 0;
            for (int i = 0; i < trained_instance.size(); i++){
                sum += pow((trained_instance.at(i) - test_instance.at(i)), 2);
            }
            return sqrt(sum);
        }
};

#endif