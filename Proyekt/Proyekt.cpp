#include <iostream>
#include <conio.h>
#include <windows.h>
#include <iomanip>
#include "Doctor.h"
#include "DoctorManager.h"

using namespace std;

enum MenuOption {
    ADD_DOCTOR,
    UPDATE_DOCTOR,
    DELETE_DOCTOR,
    GET_DOCTORS,
    EXIT
};

void setConsoleColor(WORD color) {
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleTextAttribute(hConsole, color);
}

void displayHeader() {
    setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY);
    cout << "\n========================================\n";
    cout << "||            HOSPITAL MENU           ||\n";
    cout << "========================================\n";
    setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
}

void displayMenu(MenuOption selectedOption) {
    const char* options[] = { "Add Doctor", "Update Doctor", "Delete Doctor", "Get Doctors", "Exit" };

    cout << "\n----------------------------------------\n";
    for (int i = 0; i < 5; ++i) {
        if (i == selectedOption) {
            setConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
            cout << " >> " << options[i] << " <<\n";
            setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
        else {
            cout << "    " << options[i] << "\n";
        }
    }
    cout << "----------------------------------------\n";
}

Specialty getSpecialtyFromInput() {
    const char* specialties[] = { "Cardiology", "Dermatology", "Neurology", "Pediatrics", "Radiology", "Surgery" };
    int specialtyChoice = 0;
    char key;

    while (true) {
        system("cls");
        displayHeader();
        cout << "\nSelect Specialty:\n";
        cout << "----------------------------------------\n";
        for (int i = 0; i < 6; ++i) {
            if (i == specialtyChoice) {
                setConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
                cout << " >> " << specialties[i] << " <<\n";
                setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
            }
            else {
                cout << "    " << specialties[i] << "\n";
            }
        }
        cout << "----------------------------------------\n";

        key = _getch();
        switch (key) {
        case 75: 
            if (specialtyChoice > 0) specialtyChoice--;
            break;
        case 77: 
            if (specialtyChoice < 5) specialtyChoice++;
            break;
        case 13: 
            return static_cast<Specialty>(specialtyChoice);
        case 27: 
            return static_cast<Specialty>(-1); 
        }
    }
}

string getSpecialtyName(Specialty specialty) {
    switch (specialty) {
    case CARDIOLOGY: return "Cardiology";
    case DERMATOLOGY: return "Dermatology";
    case NEUROLOGY: return "Neurology";
    case PEDIATRICS: return "Pediatrics";
    case RADIOLOGY: return "Radiology";
    case SURGERY: return "Surgery";
    default: return "Unknown";
    }
}

void displayDoctors(Doctor** doctors, int count, int selectedDoctor) {
    cout << "\n----------------------------------------\n";
    for (int i = 0; i < count; ++i) {
        if (i == selectedDoctor) {
            setConsoleColor(FOREGROUND_RED | FOREGROUND_INTENSITY);
            cout << " >> " << doctors[i]->firstName << " " << doctors[i]->lastName << " (" << getSpecialtyName(doctors[i]->specialty) << ") <<\n";
            setConsoleColor(FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
        }
        else {
            cout << "    " << doctors[i]->firstName << " " << doctors[i]->lastName << " (" << getSpecialtyName(doctors[i]->specialty) << ")\n";
        }
    }
    cout << "----------------------------------------\n";
}

void displayDoctorDetails(Doctor* doctor) {
    cout << "\nDoctor Details:\n";
    cout << "----------------------------------------\n";
    cout << "ID: " << doctor->id << "\n";
    cout << "First Name: " << doctor->firstName << "\n";
    cout << "Last Name: " << doctor->lastName << "\n";
    cout << "Specialty: " << getSpecialtyName(doctor->specialty) << "\n";
    cout << "Experience: " << doctor->experience << " years\n";
    cout << "Phone Number: " << doctor->phoneNumber << "\n";
    cout << "Email: " << doctor->email << "\n";
    cout << "----------------------------------------\n";
}

int main() {
    DoctorManager manager;
    MenuOption selectedOption = ADD_DOCTOR;
    char key;

    while (true) {
        system("cls");
        displayHeader();
        displayMenu(selectedOption);

        key = _getch();
        switch (key) {
        case 72:
            if (selectedOption > 0) selectedOption = static_cast<MenuOption>(selectedOption - 1);
            break;
        case 80:
            if (selectedOption < EXIT) selectedOption = static_cast<MenuOption>(selectedOption + 1);
            break;
        case 13:
            if (selectedOption == EXIT) return 0;

            int id, experience;
            string firstName, lastName, phoneNumber, email;
            Specialty specialty;

            system("cls");
            displayHeader();

            switch (selectedOption) {
            case ADD_DOCTOR:
                cout << "\n[ ADD DOCTOR ]\n";
                cout << "----------------------------------------\n";
                cout << "Enter ID: ";
                cin >> id;
                cout << "Enter First Name: ";
                cin >> firstName;
                cout << "Enter Last Name: ";
                cin >> lastName;
                specialty = getSpecialtyFromInput();
                if (specialty == static_cast<Specialty>(-1)) goto main_menu; 
                cout << "Enter Experience (years): ";
                cin >> experience;
                cout << "Enter Phone Number: ";
                cin >> phoneNumber;
                cout << "Enter Email: ";
                cin >> email;

                manager.addDoctor(new Doctor{ id, firstName, lastName, specialty, experience, phoneNumber, email });
                break;

            case UPDATE_DOCTOR: {
                int updateCount;
                Doctor** updateDoctors = manager.getDoctors(updateCount);
                int selectedUpdateDoctor = 0;
                while (true) {
                    system("cls");
                    displayHeader();
                    displayDoctors(updateDoctors, updateCount, selectedUpdateDoctor);

                    key = _getch();
                    switch (key) {
                    case 72: 
                        if (selectedUpdateDoctor > 0) selectedUpdateDoctor--;
                        break;
                    case 80: 
                        if (selectedUpdateDoctor < updateCount - 1) selectedUpdateDoctor++;
                        break;
                    case 27:
                        goto main_menu;
                    case 13: 
                        cout << "\n[ UPDATE DOCTOR ]\n";
                        cout << "----------------------------------------\n";
                        cout << "Enter New First Name: ";
                        cin >> firstName;
                        cout << "Enter New Last Name: ";
                        cin >> lastName;
                        specialty = getSpecialtyFromInput();
                        if (specialty == static_cast<Specialty>(-1)) goto main_menu; 
                        cout << "Enter New Experience (years): ";
                        cin >> experience;
                        cout << "Enter New Phone Number: ";
                        cin >> phoneNumber;
                        cout << "Enter New Email: ";
                        cin >> email;

                        manager.updateDoctor(updateDoctors[selectedUpdateDoctor]->id, new Doctor{ updateDoctors[selectedUpdateDoctor]->id, firstName, lastName, specialty, experience, phoneNumber, email });
                        goto main_menu;
                    }
                }
            }

            case DELETE_DOCTOR: {
                int deleteCount;
                Doctor** deleteDoctors = manager.getDoctors(deleteCount);
                int selectedDeleteDoctor = 0;
                while (true) {
                    system("cls");
                    displayHeader();
                    displayDoctors(deleteDoctors, deleteCount, selectedDeleteDoctor);

                    key = _getch();
                    switch (key) {
                    case 72: 
                        if (selectedDeleteDoctor > 0) selectedDeleteDoctor--;
                        break;
                    case 80:
                        if (selectedDeleteDoctor < deleteCount - 1) selectedDeleteDoctor++;
                        break;
                    case 27: 
                        goto main_menu;
                    case 13: 
                        cout << "\n[ DELETE DOCTOR ]\n";
                        cout << "----------------------------------------\n";
                        cout << "Are you sure you want to delete " << deleteDoctors[selectedDeleteDoctor]->firstName << " " << deleteDoctors[selectedDeleteDoctor]->lastName << "? (y/n): ";
                        char confirm;
                        cin >> confirm;
                        if (confirm == 'y' || confirm == 'Y') {
                            manager.deleteDoctor(deleteDoctors[selectedDeleteDoctor]->id);
                        }
                        goto main_menu;
                    }
                }
            }

            case GET_DOCTORS: {
                int count;
                Doctor** doctors = manager.getDoctors(count);
                int selectedDoctor = 0;
                while (true) {
                    system("cls");
                    displayHeader();
                    displayDoctors(doctors, count, selectedDoctor);

                    key = _getch();
                    switch (key) {
                    case 72: 
                        if (selectedDoctor > 0) selectedDoctor--;
                        break;
                    case 80: 
                        if (selectedDoctor < count - 1) selectedDoctor++;
                        break;
                    case 27:
                        goto main_menu;
                    case 13: 
                        system("cls");
                        displayHeader();
                        displayDoctorDetails(doctors[selectedDoctor]);
                        cout << "\nPress any key to return to the main menu...";
                        _getch();
                        goto main_menu;
                    }
                }
            }
            }
            break;
        }
    main_menu:
        continue;
    }

    return 0;
}
