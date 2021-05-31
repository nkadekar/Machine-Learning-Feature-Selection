#ifndef VALIDATOR_H
#define VALIDATOR_H

#include <vector>
#include <string>
#include <fstream>
#include "Classifier.h"
#include "Feature.h"
#include <sstream>

using namespace std;

class Validator {
    public:
        vector<vector<double>> instances;
        vector<double> labels;
        Classifier* classifier;

    public:
        Validator(vector<vector<double>> instances, vector<double> labels) {
            this->classifier = new Classifier();
            this->instances = instances;
            this-> labels = labels;
        }
        
        ~Validator(){
            delete classifier;
        }

        double leave_one_out_validation(vector<int> feature_subset) {

            vector<vector<double>> filtered_instances;

            for (int i = 0; i < instances.size(); i++) {
                vector<double> temp;
                for (int j = 0; j < feature_subset.size(); j++) {
                    temp.push_back(instances.at(i).at(feature_subset.at(j) - 1));
                }
                filtered_instances.push_back(temp);
            }

            int correct_predictions_count = 0;

            for (int i = 0; i < instances.size(); i++) {

                vector<vector<double>> temp_instances = filtered_instances;
                vector<double> temp_labels = labels;

                temp_instances.erase(temp_instances.begin() + i);
                temp_labels.erase(temp_labels.begin() + i);
                
                vector<double> test_instance = filtered_instances.at(i);
                double test_label = labels.at(i);
                
                classifier -> train(temp_instances, temp_labels);
                
                if (classifier -> test(test_instance) == test_label) {
                    correct_predictions_count++;
                }
            }

            // return instances.size();
            return correct_predictions_count / static_cast<double>(instances.size());
        }
};

#endif