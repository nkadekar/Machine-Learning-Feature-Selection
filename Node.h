#include "Feature.h"
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

    public:
        Node() {
            accuracy = evaluator();
        }

        Node(vector<Feature*> features){
            for (int i = 0; i < features.size(); i++){
                this->features.push_back(features.at(i));
            }
            accuracy = evaluator();
        }

        double evaluator(){
            double random = rand() % 1000 / 10.0;
            return random;
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