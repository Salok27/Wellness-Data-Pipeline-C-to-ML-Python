# Wellness Data Pipeline: C++ to Python ML

## Project Overview
This project is an end-to-end data processing and machine learning pipeline. It takes raw daily wellness data (steps, sleep hours, and self-reported mood), filters it using a custom-built Binary Search Tree (BST) in C++, and feeds the processed data into a Python-based Random Forest Machine Learning model to attempt mood prediction. 

The goal of this project is to demonstrate cross-language integration, custom data structure implementation, and fundamental machine learning workflows.

##  System Architecture

### Phase 1: Data Ingestion & Filtering (C++)
Raw data from `steps_tracker.csv` is read and parsed into a custom **Binary Search Tree (BST)**. 
* The BST uses the daily step count as the key for each node.
* A threshold-based search allows the user to filter out days below a certain step count.
* The filtered subset is exported to `filtered_steps.csv` for the next phase.

### Phase 2: Machine Learning Prediction (Python)
A Python script (`predict_mood.py`) ingests the filtered CSV data.
* Uses `scikit-learn` to encode categorical mood labels.
* Trains a **Random Forest Classifier** to analyze the relationship between physical activity (steps), rest (sleep hours), and emotional well-being (mood).
* Outputs a classification report and accuracy metrics.

##  Important Note on Model Accuracy & Data Limitations
If you run this model, you will notice that the prediction accuracy is relatively low. **This is expected and serves as a demonstration of real-world data limitations.**

Human mood is a highly complex, multi-variable target. The core issue with the data is that **there is very little true correlation between just taking a certain number of steps a day and a specific granular mood** (e.g., distinguishing between "sad", "stressed", and "tired"). 

To achieve a high-accuracy, production-ready model, the dataset would require:
1. **More Features:** Data on diet, screen time, weather, social interactions, and work schedule.
2. **More Volume:** Thousands of continuous days of tracking to establish baseline user habits.
3. **Binary Targeting:** Grouping granular moods into broader "Positive" vs. "Negative" categories rather than predicting 5+ distinct emotional states.

This repository serves as a structural proof-of-concept for building a *data pipeline*, rather than a medically accurate mood predictor. It highlights the engineering work of moving and filtering data efficiently between C++ and Python.

##  Technologies Used
* **C++17:** File I/O, Pointers, Custom Data Structures (BST).
* **Python 3:** Data manipulation and machine learning.
* **Libraries:** `pandas`, `scikit-learn` (RandomForestClassifier, LabelEncoder).
* **Build Tools:** `make` (MinGW32).

##  How to Run

### Prerequisites
* `g++` compiler (MinGW for Windows recommended)
* Python 3.x with `pandas` and `scikit-learn` installed.

### Execution Steps
1. **Compile the C++ code:**
   ```bash
   make
2. **Run the Data Filter:**
   ```bash
   make run_cpp
3. **Run the Machine Learning Model**
   ```bash
   make run_py
4. **Run all at once**
   ``bash
   make run_all

**Screenshots**


*Filtering the raw dataset through the Binary Search Tree*
   <img width="959" height="830" alt="Screenshot 2026-03-19 172107" src="https://github.com/user-attachments/assets/23047905-23f3-44ba-957d-1409a7b86be2" />

*The Random Forest classification report and accuracy score*
<img width="864" height="461" alt="Screenshot 2026-03-19 172121" src="https://github.com/user-attachments/assets/834035b8-59c3-406f-9cab-905f277e7058" />


   
