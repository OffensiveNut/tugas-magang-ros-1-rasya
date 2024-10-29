#include "mahasiswa.h"

string feedback;
// Fungsi callback untuk menerima feedback dari dosen
void feedbackCallback(const std_msgs::String::ConstPtr &msg) {
    ROS_INFO("Tanggapan Dosen: %s", msg->data.c_str());
    feedback = msg->data; // Simpan feedback
}

// Implementasi konstruktor mahasiswa
mahasiswa::mahasiswa(string Name, int sks) : name(Name), maxSKS(sks) {}

// Implementasi getter
string mahasiswa::getname() const { return name; }
int mahasiswa::getmaxSKS() const { return maxSKS; }
int mahasiswa::getcurrentSKS() const { return currentSKS; }
int mahasiswa::getsisaSKS() const { return maxSKS - currentSKS; }
vector<matkul> mahasiswa::getMatkulPilihan() const { return matkulPilihan; }

// Menambahkan mata kuliah
void mahasiswa::addmatkul(const matkul &Matkul) {
    if (currentSKS + Matkul.sks <= maxSKS) {
        matkulPilihan.push_back(Matkul);
        currentSKS += Matkul.sks;
    } else {
        cout << "Tidak bisa menambah mata kuliah, melebihi batas SKS.\n";
    }
}

// Menghapus mata kuliah
void mahasiswa::removematkul(int index) {
    if (index >= 0 && index < matkulPilihan.size()) {
        currentSKS -= matkulPilihan[index].sks;
        matkulPilihan.erase(matkulPilihan.begin() + index);
    } else {
        cout << "Indeks tidak valid.\n";
    }
}

// Convert data mahasiswa menjadi string
string mahasiswa::toString() {
    std::ostringstream outStream;
    outStream << "Nama         : " << name << "\n";
    outStream << "Batas / Sisa : " << maxSKS << " / " << getsisaSKS() << " SKS\n";
    outStream << std::string(40, '-') << "\n";
    outStream << std::left << std::setw(5) << "No" << "|"
              << std::left << std::setw(30) << "Nama Mata Kuliah" << "| SKS\n";
    outStream << std::string(40, '-') << "\n";

    for (size_t i = 0; i < matkulPilihan.size(); ++i) {
        outStream << std::left << std::setw(5) << (i + 1) << "|"
                  << std::left << std::setw(30) << matkulPilihan[i].name << "| "
                  << matkulPilihan[i].sks << "\n";
    }

    return outStream.str();
}

// Menampilkan daftar mata kuliah
void displayMatkul(const vector<matkul> &daftarMatkul) {
    cout << left << setw(5) << "No" << "|" << left << setw(30) << "Nama Mata Kuliah" << "| SKS\n";
    cout << string(40, '-') << endl;
    for (size_t i = 0; i < daftarMatkul.size(); ++i) {
        cout << left << setw(5) << (i + 1) << "|"
             << left << setw(30) << daftarMatkul[i].name << "| "
             << daftarMatkul[i].sks << endl;
    }
}
