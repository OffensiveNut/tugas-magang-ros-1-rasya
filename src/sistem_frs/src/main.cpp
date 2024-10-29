#include "mahasiswa.h"

int main(int argc, char **argv)
{
    string TempName;
    int TempSKS;
    mahasiswa mahasigma("", 0);

    ros::init(argc, argv, "mahasiswa");
    ros::NodeHandle nh;
    ros::Publisher mahasiswa_pub = nh.advertise<std_msgs::String>("FRS", 1000);
    ros::Publisher end_pub = nh.advertise<std_msgs::Empty>("END", 1000);
    ros::Subscriber feedback_sub = nh.subscribe("FEEDBACK", 1000, feedbackCallback);

    vector<matkul> daftarMatkul = {
        {"Aljabar Linear", 3},
        {"Basis Data", 4},
        {"Dasar Pemrograman", 3},
        {"Sistem Digital", 3},
        {"Kalkulus", 3}};

    cout << "Masukkan nama mahasiswa: ";
    getline(cin, TempName);
    cout << "Masukkan maksimum SKS mahasiswa: ";
    cin >> TempSKS;
    cin.ignore();
    cout << endl;

    mahasigma = mahasiswa(TempName, TempSKS);

    while (true)
    {
        cout << "Mata kuliah yang terdaftar:\n";
        cout << mahasigma.toString();

        cout << "\n1. Tambah Mata Kuliah\n2. Hapus Mata Kuliah\n3. Selesai & Submit\nPilih opsi: ";
        int editOption;
        cin >> editOption;
        cin.ignore();

        if (editOption == 1)
        {
            cout << "\nMata kuliah yang tersedia:\n";
            displayMatkul(daftarMatkul);

            cout << "\nPilih indeks mata kuliah yang ingin ditambahkan: ";
            int index;
            cin >> index;
            cin.ignore();
            cout << endl;

            if (index > 0 && index <= daftarMatkul.size())
            {
                mahasigma.addmatkul(daftarMatkul[index - 1]);
            }
            else
            {
                cout << "Indeks tidak valid. Silakan coba lagi.\n";
            }
        }
        else if (editOption == 2)
        {
            cout << "\nPilih mata kuliah yang ingin dihapus: ";
            int removeIndex;
            cin >> removeIndex;
            cin.ignore();
            cout << endl;
            mahasigma.removematkul(removeIndex - 1);
        }
        else if (editOption == 3)
        {
            if (ros::ok())
            {
                std_msgs::String msg;
                msg.data = mahasigma.toString();
                mahasiswa_pub.publish(msg);
                ROS_INFO("FRS Mahasiswa: %s", msg.data.c_str());
            }

            cout << "Menunggu feedback dari dosen...\n";
            feedback.clear(); // Kosongkan feedback sebelumnya
            while (feedback.empty() && ros::ok())
            {
                ros::spinOnce(); // Proses callback untuk menerima feedback
            }
            cout << "Edit FRS lagi? (y/n) ";
            char option;
            cin >> option;
            if (option == 'y')
            {
                continue; // Kembali ke awal loop
            }
            else
            {
                std_msgs::Empty end_msg;
                end_pub.publish(end_msg);
                ROS_INFO("Mengirim sinyal untuk mengakhiri program.");
                break;
            }
        }
        else
        {
            cout << "Opsi tidak valid.\n";
        }
    }
    return 0;
}
