#include "Feature.h"
#include "Validator.h"
#include <cstdlib>
#include <vector>
#include <time.h>
#include <iostream>
#include <string>

using namespace std;

#ifndef NODE_H
#define NODE_H

class Node {
    public:
        vector<Node*> children;
        vector<Feature*> features;
        double accuracy;
        Validator* validator;

    public:
        Node(Validator* validator) {
            this->validator = validator;
            // accuracy = evaluator();
        }

        Node(vector<Feature*> features, Validator* validator){
            for (int i = 0; i < features.size(); i++){
                this->features.push_back(features.at(i));
            }
            this->validator = validator;
            // accuracy = evaluator();
        }

        void evaluator(){
            vector<int> subset;
            double result = 0;
            for (int i = 0; i < features.size(); i++) {
                int data = features.at(i)->data;
                subset.push_back(data);
            }
            result = this -> validator -> leave_one_out_validation(subset);

            this->accuracy = result * 100;
        }
        
        void addChild(Node* child){
            this->children.push_back(child);
        }

        void addFeature(Feature* feature){
            this->features.push_back(feature);
        }

        string printFeatures(){
            string print;
            print += "{ ";
            for (int i = 0; i < features.size(); i++){
                print += to_string(features.at(i)->data) + " ";
            }
            print += "}";
            return print;
        }
};

#endif