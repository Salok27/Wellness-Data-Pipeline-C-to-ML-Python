"""
Project: Wellness Data Pipeline (C++ to Python ML)
Author: Salok Samant
Description: 
This script ingests fitness and sleep data filtered by a 
custom C++ Binary Search Tree and trains a Random Forest 
Classifier to predict user mood based on activity levels.

"""

import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.ensemble import RandomForestClassifier
from sklearn.metrics import accuracy_score, classification_report
from sklearn.preprocessing import LabelEncoder
import sys
import warnings

warnings.filterwarnings('ignore')

def main():
    print("Initializing Machine Learning Pipeline...")
    
    try:
        df = pd.read_csv('filtered_steps.csv')
        print(f"[SUCCESS] Loaded {len(df)} records from filtered_steps.csv")
    except FileNotFoundError:
        print("\n[ERROR] Could not find 'filtered_steps.csv'.")
        print("Please run the C++ wellness_tracker in your terminal first to generate the data.")
        sys.exit(1)

    if len(df) < 10:
        print("\n[WARNING] Not enough data points to train a reliable model.")
        print("Run the C++ tracker again with a lower step threshold (e.g., 0) to extract more data.")
        sys.exit(1)

   
    label_encoder = LabelEncoder()
    df['mood_encoded'] = label_encoder.fit_transform(df['mood'])

   
    X = df[['steps', 'sleep_hours']]
    y = df['mood_encoded']

    X_train, X_test, y_train, y_test = train_test_split(X, y, test_size=0.2, random_state=42)

    print("Training Random Forest model...\n")
    model = RandomForestClassifier(n_estimators=100, random_state=42)
    model.fit(X_train, y_train)

    predictions = model.predict(X_test)
    accuracy = accuracy_score(y_test, predictions)

    print("==============================================")
    print(f" AI Model Accuracy: {accuracy * 100:.2f}%")
    print("==============================================\n")

    print("Detailed Classification Report:")
    target_names = [str(cls) for cls in label_encoder.classes_]
    print(classification_report(y_test, predictions, target_names=target_names, zero_division=0))

if __name__ == "__main__":
    main()