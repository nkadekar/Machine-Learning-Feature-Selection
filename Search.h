#include "Node.h"
#include "Feature.h"
#include "Validator.h"
#include <algorithm>
#include <iostream>

#ifndef SEARCH_H
#define SEARCH_H

class Search {
    private:
        Node* start;
        Validator* validator;

    public:
        Search(Validator* validator) {
            this -> start = nullptr;
            this->validator = validator;
        }
        void forwardSelection(vector<Feature*> allFeatures){
            this -> start = new Node(this->validator);
            start -> evaluator();
            Node* curr = start;

            cout << "Using no features and \"random\" evaluation, I get an accuracy of " << start->accuracy << '%' << endl << endl;

            while(!allFeatures.empty()) {

                for (int i = 0; i < allFeatures.size(); i++) {
                    Node* temp = new Node(curr -> features, this->validator);
                    temp -> addFeature(allFeatures.at(i));
                    temp -> evaluator();
                    curr->addChild(temp);
                }

                int bestResultIndex = 0;
                double bestResult = 0.0;
                for (int i = 0; i < curr->children.size(); i++){
                    double evalValue = curr->children.at(i) -> accuracy;
                    cout << "Using feature(s)" << curr->children.at(i)->printFeatures() << " = " << evalValue << '%' << endl;
                    if (evalValue > bestResult) {
                        bestResultIndex = i;
                    }
                    bestResult = max(bestResult, evalValue);
                }

                if (curr->accuracy > bestResult){
                    
                    cout << endl << "(Warning, Accuracy has decreased!)" << endl
                         << "Finished Search, best feature subset is " << curr -> printFeatures() << ", which has an accuracy of " << curr -> accuracy << '%' << endl;
                    
                    return;
                }
                
                cout << endl << "Feature set " << curr->children.at(bestResultIndex)->printFeatures() << " was best, accuracy is " << curr->children.at(bestResultIndex)->accuracy << '%' << endl << endl;

                allFeatures.erase(allFeatures.begin() + bestResultIndex);

                curr = curr -> children.at(bestResultIndex);
            }

            cout << "Finished Search, best feature subset is " << curr -> printFeatures() << ", which has an accuracy of " << curr -> accuracy << '%' << endl;

            return;
            
        }
        void backwardElimination(vector<Feature*> allFeatures){
            this -> start = new Node(allFeatures, this->validator);
            start -> evaluator();
            Node* curr = start;

            cout << "Using all features and \"random\" evaluation, I get an accuracy of " << start->accuracy << '%' << endl << endl;

            while(!curr->features.empty()) {

                for (int i = 0; i < curr->features.size(); i++) {
                    curr->addChild(removeNodeFeature(curr, i));
                }

                int bestResultIndex = 0;
                double bestResult = 0.0;
                for (int i = 0; i < curr->children.size(); i++){
                    if (!(curr->features.size() == 1)) {
                        double evalValue = curr->children.at(i) -> accuracy;
                        cout << "Using feature(s)" << curr->children.at(i)->printFeatures() << " = " << evalValue << '%' << endl;
                        if (evalValue > bestResult) {
                            bestResultIndex = i;
                        }
                        bestResult = max(bestResult, evalValue);
                    }
                }

                if (curr->accuracy > bestResult){
                    

                    cout << endl << "(Warning, Accuracy has decreased!)" << endl
                         << "Finished Search, best feature subset is " << curr -> printFeatures() << ", which has an accuracy of " << curr -> accuracy << '%' << endl;
                    
                    return;
                }
                
                cout << endl << "Feature set " << curr->children.at(bestResultIndex)->printFeatures() << " was best, accuracy is " << curr->children.at(bestResultIndex)->accuracy << '%' << endl << endl;

                allFeatures.erase(allFeatures.begin() + bestResultIndex);

                curr = curr -> children.at(bestResultIndex);
            }

            cout << "Finished Search, best feature subset is " << curr -> printFeatures() << ", which has an accuracy of " << curr -> accuracy << '%' << endl;

            return;
        }

        Node* removeNodeFeature(Node* node, int index) {
            Node* temp = new Node(node->features, this->validator);
            temp->features.erase(temp->features.begin() + index);
            temp -> evaluator();
            return temp;
        }
};




#endif