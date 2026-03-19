#ifndef BST_H
#define BST_H

#include <string>

struct WellnessEntry {
    std::string date;
    int steps;
    float sleepHours;
    std::string mood;
};

class BSTNode {
public:
    WellnessEntry data;
    BSTNode* left;
    BSTNode* right;

    BSTNode(WellnessEntry entry);
};

class BST {
private:
    BSTNode* root;
    void insertHelper(BSTNode*& node, WellnessEntry entry);
    void printAboveSteps(BSTNode* node, int minSteps);
    void deleteTree(BSTNode* node);

public:
    BST();
    ~BST();

    void insert(WellnessEntry entry);
    void printAboveSteps(int minSteps);
    void writeAboveStepsToCSV(const std::string& filename, int minSteps);
};

#endif
