#include <iostream>
#include <fstream>
#include <string>
#include <limits>  // For numeric limits
#include <stdexcept>  // For exception handling

using namespace std;

class HMS {
public:
    // Default constructor to display a welcome message
    HMS() {
        cout << endl;
        cout << "Welcome to City Hospital, Pune!" << endl;
    }

    // Methods in this class
    void addDoctor();
    void displayDoctors();
    void addPatient();
    void displayPatients();
    void dischargePatient();
    void addNurse();
    void displayNurses();
    void addNonMedicalStaff();
    void displayNonMedicalStaff();
};

// Function to add doctor details
void HMS::addDoctor() {
    ofstream outFile("doctors.txt", ios::app);
    if (!outFile) {
        cerr << "Error opening doctors.txt for writing." << endl;
        return;
    }

    string name, specialization;
    cout << "Enter Doctor's Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);

    cout << "Enter Specialization: ";
    getline(cin, specialization);

    outFile << name << "," << specialization << endl;
    outFile.close();
    cout << endl << "Doctor added successfully!\n";
}

// Function to display all doctor details (from doctors.txt)
void HMS::displayDoctors() {
    ifstream inFile("doctors.txt");
    if (!inFile) {
        cerr << "Error opening doctors.txt for reading." << endl;
        return;
    }

    string line;
    cout << "\n--- List of Doctors ---\n\n";
    while (getline(inFile, line)) {
        cout << line << endl;
    }
    inFile.close();
}

// Function to add patient details
void HMS::addPatient() {
    ofstream outFile("patients.txt", ios::app);
    if (!outFile) {
        cerr << "Error opening patients.txt for writing." << endl;
        return;
    }

    string name, diagnosis, bloodGroup, gender;
    int age, patientID;

    // Handle invalid patient ID input
    while (true) {
        try {
            cout << "Enter Patient's ID: ";
            cin >> patientID;
            if (cin.fail()) {
                throw invalid_argument("Invalid input! Patient ID must be a number.");
            }
            break;
        } catch (const invalid_argument& e) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << e.what() << " Please try again.\n";
        }
    }

    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    cout << "Enter Patient's Name: ";
    getline(cin, name);

    cout << "Enter Age: ";
    cin >> age;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    cout << "Enter Diagnosis: ";
    getline(cin, diagnosis);

    cout << "Enter Blood Group: ";
    getline(cin, bloodGroup);

    cout << "Enter Gender: ";
    getline(cin, gender);

    outFile << patientID << "," << name << "," << age << "," << diagnosis << ","
            << bloodGroup << "," << gender << endl;
    outFile.close();
    cout << "Patient added successfully!\n";
}

// Function to display all patient details (from patients.txt)
void HMS::displayPatients() {
    ifstream inFile("patients.txt");
    if (!inFile) {
        cerr << "Error opening patients.txt for reading." << endl;
        return;
    }

    string line;
    cout << "\n--- List of Patients ---\n";
    while (getline(inFile, line)) {
        cout << line << endl;
    }
    inFile.close();
}

// Function to discharge a patient (delete from patients.txt)
void HMS::dischargePatient() {
    ifstream inFile("patients.txt");
    if (!inFile) {
        cerr << "Error opening patients.txt for reading." << endl;
        return;
    }

    ofstream tempFile("temp.txt");  // Temporary file to store remaining data
    if (!tempFile) {
        cerr << "Error creating temporary file." << endl;
        return;
    }

    int dischargeID;
    cout << "Enter the ID of the patient to discharge: ";
    cin >> dischargeID;

    string line;
    bool patientFound = false;

    // Copy all patients except the one to be discharged
    while (getline(inFile, line)) {
        size_t pos = line.find(',');
        int currentID = stoi(line.substr(0, pos));  // Extract patient ID

        if (currentID == dischargeID) {
            patientFound = true;
            cout << "Patient with ID " << dischargeID << " has been discharged.\n";
        } else {
            tempFile << line << endl;
        }
    }

    inFile.close();
    tempFile.close();

    if (patientFound) {
        remove("patients.txt");
        rename("temp.txt", "patients.txt");
    } else {
        cout << "No patient found with ID " << dischargeID << ".\n";
        remove("temp.txt");
    }
}

// Function to add nurse details
void HMS::addNurse() {
    ofstream nurseFile("nurses.txt", ios::app);
    if (!nurseFile) {
        cerr << "Error opening nurses.txt for writing." << endl;
        return;
    }

    string name, department;
    long id;

    cout << "Enter Nurse's Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);

    cout << "Enter Nurse's Department: ";
    getline(cin, department);

    // Handle invalid nurse ID input
    while (true) {
        try {
            cout << "Enter Nurse's ID: ";
            cin >> id;
            if (cin.fail()) {
                throw invalid_argument("Invalid input! Nurse ID must be a number.");
            }
            break;
        } catch (const invalid_argument& e) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << e.what() << " Please try again.\n";
        }
    }

    nurseFile << name << "," << department << "," << id << endl;
    nurseFile.close();
    cout << "Nurse added successfully!\n";
}

// Function to display all nurse details (from nurses.txt)
void HMS::displayNurses() {
    ifstream nurseFile("nurses.txt");
    if (!nurseFile) {
        cerr << "Error opening nurses.txt for reading." << endl;
        return;
    }

    string line;
    cout << "\n--- List of Nurses ---\n";
    while (getline(nurseFile, line)) {
        cout << line << endl;
    }
    nurseFile.close();
}

// Function to add non-medical staff details
void HMS::addNonMedicalStaff() {
    ofstream nonMedicalFile("non_medical_staff.txt", ios::app);
    if (!nonMedicalFile) {
        cerr << "Error opening non_medical_staff.txt for writing." << endl;
        return;
    }

    string name, role;
    long id;

    cout << "Enter Staff's Name: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    getline(cin, name);

    cout << "Enter Role: ";
    getline(cin, role);

    // Handle invalid staff ID input
    while (true) {
        try {
            cout << "Enter Staff's ID: ";
            cin >> id;
            if (cin.fail()) {
                throw invalid_argument("Invalid input! Staff ID must be a number.");
            }
            break;
        } catch (const invalid_argument& e) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << e.what() << " Please try again.\n";
        }
    }

    nonMedicalFile << name << "," << role << "," << id << endl;
    nonMedicalFile.close();
    cout << "Non-medical staff added successfully!\n";
}

// Function to display all non-medical staff details
void HMS::displayNonMedicalStaff() {
    ifstream nonMedicalFile("non_medical_staff.txt");
    if (!nonMedicalFile) {
        cerr << "Error opening non_medical_staff.txt for reading." << endl;
        return;
    }

    string line;
    cout << "\n--- List of Non-Medical Staff ---\n";
    while (getline(nonMedicalFile, line)) {
        cout << line << endl;
    }
    nonMedicalFile.close();
}

int main() {
    HMS hospital;
    int choice;

    while (true) {
        cout << "\n---- Hospital Management System ----" << endl;
        cout << "1. Add Doctor\n2. View Doctors\n";
        cout << "3. Add Patient\n4. View Patients\n";
        cout << "5. Discharge Patient\n";
        cout << "6. Add Nurse\n7. View Nurses\n";
        cout << "8. Add Non-Medical Staff\n9. View Non-Medical Staff\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: hospital.addDoctor(); break;
            case 2: hospital.displayDoctors(); break;
            case 3: hospital.addPatient(); break;
            case 4: hospital.displayPatients(); break;
            case 5: hospital.dischargePatient(); break;
            case 6: hospital.addNurse(); break;
            case 7: hospital.displayNurses(); break;
            case 8: hospital.addNonMedicalStaff(); break;
            case 9: hospital.displayNonMedicalStaff(); break;
            case 10: exit(0);
            default: cout << "Invalid choice! Please try again.\n";
        }
    }

    return 0;
}
