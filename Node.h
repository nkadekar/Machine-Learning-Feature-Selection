#include "Feature.h"
#include <cstdlib>
#include <vector>
#include <time.h>

using namespace std;

#ifndef NODE_H
#define NODE_H

class Node {
    public:
        vector<Node*> children;
        vector<Feature*> features;

    public:
        Node() {}

        Node(Feature* feature){
            this->features.push_back(feature);
        }

        Node(vector<Feature*> features){
            for (int i = 0; i < features.size(); i++){
                this->features.push_back(features.at(i));
            }
        }

        double evaluator(){
            srand(time(NULL));
            double random = rand() % 1000 / 10.0;
            return random;
        }
        
        void addChild(Node* child){
            this->children.push_back(child);
        }
};

#endif