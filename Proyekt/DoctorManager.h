#ifndef DOCTORMANAGER_H
#define DOCTORMANAGER_H

#include "Doctor.h"

class DoctorManager {
private:
    Doctor** doctors;
    int capacity;
    int count;

    void resize() {
        capacity *= 2;
        Doctor** newDoctors = new Doctor * [capacity];
        for (int i = 0; i < count; ++i) {
            newDoctors[i] = doctors[i];
        }
        delete[] doctors;
        doctors = newDoctors;
    }

public:
    DoctorManager() : capacity(10), count(0) {
        doctors = new Doctor * [capacity];
    }

    ~DoctorManager() {
        for (int i = 0; i < count; ++i) {
            delete doctors[i];
        }
        delete[] doctors;
    }

    void addDoctor(Doctor* doctor) {
        if (count == capacity) {
            resize();
        }
        doctors[count++] = doctor;
    }

    void updateDoctor(int id, Doctor* updatedDoctor) {
        for (int i = 0; i < count; ++i) {
            if (doctors[i]->id == id) {
                *doctors[i] = *updatedDoctor;
                return;
            }
        }
    }

    void deleteDoctor(int id) {
        for (int i = 0; i < count; ++i) {
            if (doctors[i]->id == id) {
                delete doctors[i];
                for (int j = i; j < count - 1; ++j) {
                    doctors[j] = doctors[j + 1];
                }
                --count;
                return;
            }
        }
    }

    Doctor** getDoctors(int& outCount) const {
        outCount = count;
        return doctors;
    }

    Doctor** searchDoctorsByName(const std::string& namePart, int& outCount) const {
        Doctor** results = new Doctor * [count];
        outCount = 0;
        for (int i = 0; i < count; ++i) {
            if (doctors[i]->firstName.find(namePart) != std::string::npos || doctors[i]->lastName.find(namePart) != std::string::npos) {
                results[outCount++] = doctors[i];
            }
        }
        return results;
    }
};

#endif 
