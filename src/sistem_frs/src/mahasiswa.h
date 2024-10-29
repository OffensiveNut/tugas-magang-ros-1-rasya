#ifndef MAHASISWA_H
#define MAHASISWA_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <ros/ros.h>
#include <std_msgs/String.h>
#include <std_msgs/Empty.h>
#include <sstream>

using namespace std;

extern string feedback; // di definisikan di mahasiswa.cpp, kalo disini entah kenapa error

void feedbackCallback(const std_msgs::String::ConstPtr &msg);

struct matkul {
    string name;
    int sks;
    matkul(string Name, int Sks) : name(Name), sks(Sks) {}
};

class mahasiswa {
private:
    string name;
    int maxSKS;
    int currentSKS = 0;
    vector<matkul> matkulPilihan;

public:
    mahasiswa(string Name, int sks);
    string getname() const;
    int getmaxSKS() const;
    int getcurrentSKS() const;
    int getsisaSKS() const;
    vector<matkul> getMatkulPilihan() const;
    void addmatkul(const matkul &Matkul);
    void removematkul(int index);
    string toString();
};

void displayMatkul(const vector<matkul> &daftarMatkul);

#endif // MAHASISWA_H
