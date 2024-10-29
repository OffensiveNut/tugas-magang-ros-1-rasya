# tugas-magang-ros-1-rasya
### cara kerja kode saya
1. mahasiswa membuat & mengedit FRS, jika sudah, kirim ke dosen menggunakan topic "FRS" lalu mahasiswa akan menunggu respon dari dosen.
2. dosen akan menerima data FRS dari mahasiswa lalu memberikan feedback berupa string melalui topic "FEEDBACK".
3. mahasiswa yang telah menerima feedback akan diberi prompt apakah ingin melanjutkan mengedit atau menyudahi.
4. jika memilih menyudahi, maka mahasiswa akan mengpublish sinyal end bertipe data std_msgs::Empty melalui topic "END" dan break dari loop.
5. kode dosen menerima signal end akan menghentikan node menggunakan ros::shutdown();

### struktur executeable mahasiswa
- mahasiswa.h berisi deklarasi fungsi, class, dan variabel.
- mahasiswa.cpp berisi implementasi dari fungsi, class, dan variabel yang ada di mahasiswa.h.
- main.cpp merupakan kode utama yang berisi main function yang akan menjalankan logic program

executable dosen tidak saya pisah karena kode nya sedikit
