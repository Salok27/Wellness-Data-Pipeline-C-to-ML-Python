#include <iostream>
#include <fstream>
#include <sstream>
#include "BST.h"

int main() {
    BST bst;
    std::ifstream file("steps_tracker.csv");
    std::string line;

    if (!file.is_open()) {
        std::cerr << "Failed to open steps_tracker.csv\n";
        return 1;
    } else {
        std::cout << "[INFO] File opened successfully.\n";
    }

    // Skip the header
    std::getline(file, line);

    int lineCount = 1;
    while (std::getline(file, line)) {
        std::stringstream ss(line);
        std::string date, stepsStr, sleepStr, mood;

        std::getline(ss, date, ',');
        std::getline(ss, stepsStr, ',');
        std::getline(ss, sleepStr, ',');
        std::getline(ss, mood, ',');

        if (date.empty() || stepsStr.empty() || sleepStr.empty() || mood.empty()) {
            std::cerr << "[WARN] Skipping malformed row " << lineCount << ": " << line << "\n";
            lineCount++;
            continue;
        }

        try {
            WellnessEntry entry;
            entry.date = date;
            entry.steps = std::stoi(stepsStr);
            entry.sleepHours = std::stof(sleepStr);
            entry.mood = mood;

            bst.insert(entry);
        } catch (const std::exception& e) {
            std::cerr << "[ERROR] Failed to parse row " << lineCount << ": " << line
                      << " | Reason: " << e.what() << "\n";
            // Don't insert, skip this row
        }

        lineCount++;
    }

    file.close();
    std::cout << "[INFO] Finished loading dataset.\n";

    int minSteps;
    std::cout << "Enter a minimum number of steps to filter the dataset: ";
    while (!(std::cin >> minSteps)) {
        std::cin.clear();
        std::cin.ignore(10000, '\n');
        std::cout << "Please enter a valid integer: ";
    }

    std::cout << "\nEntries with steps >= " << minSteps << ":\n";
    bst.printAboveSteps(minSteps);
    bst.writeAboveStepsToCSV("filtered_steps.csv", minSteps);

    return 0;
}
