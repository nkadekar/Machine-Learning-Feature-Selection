#include "Node.h"
#include "Feature.h"
#include <algorithm>

#ifndef SEARCH_H
#define SEARCH_H

class Search {
    private:
        Node* start;
    public:
        Search() {
            this -> start = nullptr;
        }
        void forwardSelection(vector<Feature*> allFeatures){
            this->start = new Node();
            Node* curr = nullptr;
            for (int i = 0; i < allFeatures.size(); i++) {
                start->addChild(new Node(allFeatures.at(i)));
            }

            int bestResultIndex = 0;
            double bestResult = 0.0;
            for (int i = 0; i < start->children.size(); i++){
                if (start->children.at(i)->evaluator() > bestResult) {
                    bestResultIndex = i;
                }
                bestResult = max(bestResult, start->children.at(i)->evaluator());
            }
            if (start->evaluator() > bestResult){
                
                //do something
                
                return;
            }

            
        }
        void backwardElimination(vector<Feature*> allFeatures){

        }
};




#endif