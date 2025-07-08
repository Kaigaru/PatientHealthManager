# PatientHealthManager

# 🩺 Health Interpreter

**Health Interpreter** is a C program that manages patient health data by reading from a text file, processing the records into a linked list, and offering several health-related operations such as BMI calculation, patient search, and listing unhealthy individuals.

## 📌 Features

When you run the program, it:
- Initializes a **linked list of patients** by reading from an external `.txt` file
- Sorts the list using **insertion sort** based on patient details
- Allows you to:
  - 📝 **Insert a new patient**
  - 📈 **Calculate and update BMI** for all patients
  - 🔍 **Search for a patient** by name
  - ⚠️ **Highlight unhealthy patients** based on BMI thresholds
  - 👥 **Display all patients** and their health info

## 🧠 How It Works

1. **Data Initialization**:
   - Reads health data (name, age, weight, height) from a `.txt` file
   - Builds a sorted linked list using **insertion sort**

2. **BMI Calculation**:
   - Uses the formula:  
     `BMI = weight (kg) / (height (m) × height (m))`
   - Classifies patients as **healthy** or **unhealthy** based on BMI

3. **Dynamic Operations**:
   - You can add new patients and the list stays sorted
   - Search is performed by name (first or full)
   - Health status updates are reflected automatically
     
Sample Input Format (patients.txt):
Name;Surname;dd/mm/yyyy;height;weight;BMI
Hefty;Smurf;03/04/1960;1.70;49;NA

