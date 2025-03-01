#pragma once
#ifndef DOCTOR_H
#define DOCTOR_H

#include <string>

using namespace std;

enum Specialty {
    CARDIOLOGY,
    DERMATOLOGY,
    NEUROLOGY,
    PEDIATRICS,
    RADIOLOGY,
    SURGERY
};

struct Doctor {
    int id;
    string firstName;
    string lastName;
    Specialty specialty;
    int experience;
    string phoneNumber;
    string email;
};

#endif 
