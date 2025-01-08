#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

// Base class for a Person
class Person
{
protected:
    string name;
    int age;

public:
    Person(const string &name, int age) : name(name), age(age) {}
    virtual void display() const = 0;

    // Getter for age
    int getAge() const
    {
        return age;
    }
};

// Derived class for a Patient
class Patient : public Person
{
private:
    string ailment;

public:
    Patient(const string &name, int age, const string &ailment)
        : Person(name, age), ailment(ailment) {}

    void display() const override
    {
        cout << "Patient Name: " << name << ", Age: " << age
             << ", Ailment: " << ailment << endl;
    }

    string getName() const { return name; }
    string getAilment() const { return ailment; }
};

// Class to manage appointments
class Appointment
{
private:
    string patientName;
    string doctorName;
    string date;
    string time;

public:
    Appointment(const string &patientName, const string &doctorName, const string &date, const string &time)
        : patientName(patientName), doctorName(doctorName), date(date), time(time) {}

    void display() const
    {
        cout << "Appointment: Patient: " << patientName
             << ", Doctor: " << doctorName
             << ", Date: " << date
             << ", Time: " << time << endl;
    }

    string getPatientName() const { return patientName; }
    string getDate() const { return date; }
    string getTime() const { return time; }
};

// Main system class
class MedicalSystem
{
private:
    vector<Patient> patients;
    vector<Appointment> appointments;

public:
    // Add a new patient
    void addPatient()
    {
        string name, ailment;
        int age;

        cout << "Enter patient's name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter patient's age: ";
        cin >> age;
        cout << "Enter patient's ailment: ";
        cin.ignore();
        getline(cin, ailment);

        patients.emplace_back(name, age, ailment);
        cout << "Patient added successfully!\n";
    }

    // Schedule an appointment
    void addAppointment()
    {
        string patientName, doctorName, date, time;

        cout << "Enter patient's name: ";
        cin.ignore();
        getline(cin, patientName);

        if (find_if(patients.begin(), patients.end(), [&](const Patient &p)
                    { return p.getName() == patientName; }) == patients.end())
        {
            cout << "Patient not found! Please add the patient first.\n";
            return;
        }

        cout << "Enter doctor's name: ";
        getline(cin, doctorName);
        cout << "Enter appointment date (YYYY-MM-DD): ";
        getline(cin, date);
        cout << "Enter appointment time (HH:MM): ";
        getline(cin, time);

        appointments.emplace_back(patientName, doctorName, date, time);
        cout << "Appointment scheduled successfully!\n";
    }

    // Display all patients
    void displayPatients() const
    {
        if (patients.empty())
        {
            cout << "No patients registered.\n";
            return;
        }

        cout << "\nList of Patients:\n";
        for (const auto &patient : patients)
        {
            patient.display();
        }
    }

    // Display all appointments
    void displayAppointments() const
    {
        if (appointments.empty())
        {
            cout << "No appointments scheduled.\n";
            return;
        }

        cout << "\nList of Appointments:\n";
        for (const auto &appointment : appointments)
        {
            appointment.display();
        }
    }

    // Save data to file
    void saveToFile() const
    {
        ofstream outFile("medical_data.txt");

        outFile << "Patients:\n";
        for (const auto &patient : patients)
        {
            outFile << patient.getName() << "," << patient.getAilment() << "," << patient.getAge() << endl;
        }

        outFile << "\nAppointments:\n";
        for (const auto &appointment : appointments)
        {
            outFile << appointment.getPatientName() << "," << appointment.getDate() << "," << appointment.getTime() << endl;
        }

        outFile.close();
        cout << "Data saved successfully to medical_data.txt\n";
    }

    // Load data from file
    void loadFromFile()
    {
        ifstream inFile("medical_data.txt");
        if (!inFile)
        {
            cout << "No data file found.\n";
            return;
        }

        patients.clear();
        appointments.clear();
        string line, name, ailment, age, date, time, doctorName, patientName;

        while (getline(inFile, line))
        {
            if (line == "Patients:")
            {
                while (getline(inFile, line) && !line.empty())
                {
                    auto pos1 = line.find(',');
                    auto pos2 = line.find(',', pos1 + 1);

                    name = line.substr(0, pos1);
                    ailment = line.substr(pos1 + 1, pos2 - pos1 - 1);
                    age = line.substr(pos2 + 1);

                    patients.emplace_back(name, stoi(age), ailment);
                }
            }
            else if (line == "Appointments:")
            {
                while (getline(inFile, line) && !line.empty())
                {
                    auto pos1 = line.find(',');
                    auto pos2 = line.find(',', pos1 + 1);
                    auto pos3 = line.find(',', pos2 + 1);

                    patientName = line.substr(0, pos1);
                    doctorName = line.substr(pos1 + 1, pos2 - pos1 - 1);
                    date = line.substr(pos2 + 1, pos3 - pos2 - 1);
                    time = line.substr(pos3 + 1);

                    appointments.emplace_back(patientName, doctorName, date, time);
                }
            }
        }

        inFile.close();
        cout << "Data loaded successfully from medical_data.txt\n";
    }
};

// Main function
int main()
{
    MedicalSystem system;
    int choice;

    do
    {
        cout << "\n1. Add Patient\n2. Schedule Appointment\n3. Display Patients\n4. Display Appointments\n5. Save to File\n6. Load from File\n7. Exit\n";
        cout << "Choose an option: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            system.addPatient();
            break;
        case 2:
            system.addAppointment();
            break;
        case 3:
            system.displayPatients();
            break;
        case 4:
            system.displayAppointments();
            break;
        case 5:
            system.saveToFile();
            break;
        case 6:
            system.loadFromFile();
            break;
        case 7:
            cout << "Exiting program...\n";
            break;
        default:
            cout << "Invalid option! Try again.\n";
        }
    } while (choice != 7);

    return 0;
}
