#include "BST.h"
#include <iostream>
#include <fstream>
#include <functional>

BSTNode::BSTNode(WellnessEntry entry) : data(entry), left(nullptr), right(nullptr) {}

BST::BST() : root(nullptr) {}

BST::~BST() {
    deleteTree(root);
}

void BST::deleteTree(BSTNode* node) {
    if (!node) return;
    deleteTree(node->left);
    deleteTree(node->right);
    delete node;
}

void BST::insert(WellnessEntry entry) {
    insertHelper(root, entry);
}

void BST::insertHelper(BSTNode*& node, WellnessEntry entry) {
    if (!node) {
        node = new BSTNode(entry);
    } else if (entry.steps < node->data.steps) {
        insertHelper(node->left, entry);
    } else {
        insertHelper(node->right, entry);
    }
}

void BST::printAboveSteps(int minSteps) {
    if (!root) {
        std::cout << "[INFO] No data to display (tree is empty).\n";
        return;
    }
    printAboveSteps(root, minSteps);
}

void BST::printAboveSteps(BSTNode* node, int minSteps) {
    if (!node) return;
    printAboveSteps(node->left, minSteps);
    if (node->data.steps >= minSteps) {
        std::cout << node->data.date << " | Steps: " << node->data.steps
                  << " | Sleep: " << node->data.sleepHours
                  << " | Mood: " << node->data.mood << std::endl;
    }
    printAboveSteps(node->right, minSteps);
}

void BST::writeAboveStepsToCSV(const std::string& filename, int minSteps) {
    if (!root) {
        std::cerr << "[WARNING] Tree is empty. No data written to file.\n";
        return;
    }

    std::ofstream outFile(filename);
    if (!outFile.is_open()) {
        std::cerr << "Failed to write to " << filename << std::endl;
        return;
    }

    outFile << "date,steps,sleep_hours,mood\n";

    std::function<void(BSTNode*)> writeHelper = [&](BSTNode* node) {
        if (!node) return;
        writeHelper(node->left);
        if (node->data.steps >= minSteps) {
            outFile << node->data.date << ","
                    << node->data.steps << ","
                    << node->data.sleepHours << ","
                    << node->data.mood << "\n";
        }
        writeHelper(node->right);
    };

    writeHelper(root);
    outFile.close();

    std::cout << "\nFiltered results saved to: " << filename << std::endl;
}
