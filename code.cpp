#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <ctime>
#include <fstream>
using namespace std;

class Booking {
private:
    int lapangan;
    int jam;
    int durasi;
    string nama;
    string nomorTelepon;
    string metodePembayaran;
    double biaya;
    string tanggalBooking;

public:
    // Getters
    int getLapangan() const { return lapangan; }
    int getJam() const { return jam; }
    int getDurasi() const { return durasi; }
    string getNama() const { return nama; }
    string getNomorTelepon() const { return nomorTelepon; }
    string getMetodePembayaran() const { return metodePembayaran; }
    double getBiaya() const { return biaya; }
    string getTanggalBooking() const { return tanggalBooking; }

    // Setters
    void setBookingDetails(int lap, int j, int dur, string n, string telp, 
                          string metode, double by, string tgl) {
        lapangan = lap;
        jam = j;
        durasi = dur;
        nama = n;
        nomorTelepon = telp;
        metodePembayaran = metode;
        biaya = by;
        tanggalBooking = tgl;
    }
};

class Lapangan {
private:
    int nomor;
    vector<bool> jamKosong;

public:
    Lapangan(int num) : nomor(num), jamKosong(24, true) {}
    
    bool isJamKosong(int jam) const { return jamKosong[jam]; }
    void setJamStatus(int jam, bool status) { jamKosong[jam] = status; }
    int getNomor() const { return nomor; }
};

class BejoFutsalSystem {
private:
    vector<Lapangan> lapangan;
    vector<Booking> bookings;
    const string adminPassword = "admin123";

    string getCurrentDateTime() {
        time_t now = time(0);
        tm* ltm = localtime(&now);
        
        string tanggal = to_string(ltm->tm_mday) + "/" + 
                        to_string(1 + ltm->tm_mon) + "/" + 
                        to_string(1900 + ltm->tm_year) + " " +
                        to_string(ltm->tm_hour) + ":" +
                        to_string(ltm->tm_min);
        return tanggal;
    }

    double hitungBiaya(int jam, int durasi) {
        double harga = 0;
        for (int i = 0; i < durasi; i++) {
            if (jam >= 18 && jam < 24) { 
                harga += 120000;
            } else if (jam >= 6 && jam < 18) {
                harga += 90000;
            } else {
                return -1; 
            }
            jam++;
        }
        return harga;
    }

    void cetakNota(const Booking& booking) {
        cout << "\n" << string(40, '=') << endl;
        cout << "           NOTA BOOKING LAPANGAN           " << endl;
        cout << "               BEJO FUTSAL            " << endl;
        cout << string(40, '=') << endl;
        cout << "No. Booking   : FSC" << booking.getTanggalBooking().substr(0,2) 
             << booking.getLapangan() << booking.getJam() << endl;
        cout << "Tanggal      : " << booking.getTanggalBooking() << endl;
        cout << string(40, '-') << endl;
        cout << "Nama         : " << booking.getNama() << endl;
        cout << "No. Telepon  : " << booking.getNomorTelepon() << endl;
        cout << string(40, '-') << endl;
        cout << "Detail Booking:" << endl;
        cout << "Lapangan     : " << booking.getLapangan() << endl;
        cout << "Jam Mulai    : " << setfill('0') << setw(2) << booking.getJam() << ":00" << endl;
        cout << "Durasi       : " << booking.getDurasi() << " jam" << endl;
        cout << "Jam Selesai  : " << setfill('0') << setw(2) 
             << booking.getJam() + booking.getDurasi() << ":00" << endl;
        cout << string(40, '-') << endl;
        cout << "Pembayaran:" << endl;
        cout << "Metode       : " << booking.getMetodePembayaran() << endl;
        cout << "Total Biaya  : Rp " << fixed << setprecision(0) << booking.getBiaya() << endl;
        cout << string(40, '=') << endl;
        cout << "         Terima Kasih Atas Kunjungan         " << endl;
        cout << "    Silahkan Datang 15 Menit Sebelumnya    " << endl;
        cout << string(40, '=') << endl << endl;
    }

public:
    BejoFutsalSystem() {
        // Initialize dengan 2 lapangan
        lapangan.push_back(Lapangan(1));
        lapangan.push_back(Lapangan(2));
    }

    void displayDaftarHarga() {
        cout << "\n=== DAFTAR HARGA ===" << endl;
        cout << "06:00 - 17:59 : Rp 90.000/jam" << endl;
        cout << "18:00 - 23:59 : Rp 120.000/jam" << endl;
    }

    void editStatusLapangan() {
        cout << "\n=== Status Lapangan ===" << endl;
        for (int i = 0; i < 2; i++) {
            cout << "\nLapangan " << i + 1 << ":" << endl;
            for (int j = 6; j < 24; j++) {
                cout << setfill('0') << setw(2) << j << ":00 : " 
                     << (lapangan[i].isJamKosong(j) ? "Kosong" : "Terisi") << endl;
            }
        }
        
        int nomorLapangan, jam;
        cout << "\nMasukkan nomor lapangan (1-2): ";
        cin >> nomorLapangan;
        
        if (nomorLapangan < 1 || nomorLapangan > 2) {
            cout << "Nomor lapangan tidak valid!" << endl;
            return;
        }
        
        cout << "Masukkan jam (6-23): ";
        cin >> jam;
        
        if (jam < 6 || jam > 23) {
            cout << "Jam tidak valid!" << endl;
            return;
        }
        
        bool newStatus = !lapangan[nomorLapangan - 1].isJamKosong(jam);
        lapangan[nomorLapangan - 1].setJamStatus(jam, newStatus);
        cout << "\nStatus lapangan " << nomorLapangan << " jam " << setfill('0') 
             << setw(2) << jam << ":00 diubah menjadi " 
             << (newStatus ? "kosong" : "terisi") << endl;
    }

    void bookingLapangan() {
        displayDaftarHarga();
        
        int pilihanLapangan, jam, durasi;
        cout << "\nPilih lapangan (1-2): ";
        cin >> pilihanLapangan;

        if (pilihanLapangan < 1 || pilihanLapangan > 2) {
            cout << "Nomor lapangan tidak valid!" << endl;
            return;
        }

        cout << "Masukkan jam mulai (6-23): ";
        cin >> jam;

        if (jam < 6 || jam > 23) {
            cout << "Jam tidak valid!" << endl;
            return;
        }

        cout << "Masukkan durasi (dalam jam): ";
        cin >> durasi;

        if (jam + durasi > 24) {
            cout << "Jam selesai melampaui batas waktu!" << endl;
            return;
        }

        // Check availability
        for (int i = 0; i < durasi; i++) {
            if (!lapangan[pilihanLapangan - 1].isJamKosong(jam + i)) {
                cout << "Jam yang Anda pilih tidak tersedia!" << endl;
                return;
            }
        }

        double totalBiaya = hitungBiaya(jam, durasi);
        if (totalBiaya == -1) {
            cout << "Waktu tidak valid untuk perhitungan harga!" << endl;
            return;
        }

        string nama, nomorTelepon, metodePembayaran;
        cout << "Masukkan nama Anda: ";
        cin.ignore();
        getline(cin, nama);

        cout << "Masukkan nomor telepon Anda: ";
        getline(cin, nomorTelepon);

        cout << "Pilih metode pembayaran (Gopay (081334660482)/QRIS): ";
        getline(cin, metodePembayaran);

        // Mark time slots as booked
        for (int i = 0; i < durasi; i++) {
            lapangan[pilihanLapangan - 1].setJamStatus(jam + i, false);
        }

        // Create new booking
        Booking newBooking;
        newBooking.setBookingDetails(pilihanLapangan, jam, durasi, nama, 
                                   nomorTelepon, metodePembayaran, totalBiaya, 
                                   getCurrentDateTime());
        bookings.push_back(newBooking);

        cetakNota(newBooking);
    }

    void lihatHistoriPurchase() {
        if (bookings.empty()) {
            cout << "\nBelum ada data booking!" << endl;
            return;
        }

        cout << "\n=== HISTORI BOOKING ===" << endl;
        for (size_t i = 0; i < bookings.size(); i++) {
            cout << "\nBooking ke-" << i + 1 << ":" << endl;
            cout << "Tanggal      : " << bookings[i].getTanggalBooking() << endl;
            cout << "Nama         : " << bookings[i].getNama() << endl;
            cout << "Lapangan     : " << bookings[i].getLapangan() << endl;
            cout << "Jam Mulai    : " << setfill('0') << setw(2) 
                 << bookings[i].getJam() << ":00" << endl;
            cout << "Durasi       : " << bookings[i].getDurasi() << " jam" << endl;
            cout << "Total Biaya  : Rp " << fixed << setprecision(0) 
                 << bookings[i].getBiaya() << endl;
        }
        cout << string(30, '=') << endl;
    }

    void downloadHistoriPurchase() {
        if (bookings.empty()) {
            cout << "\nBelum ada data booking untuk didownload!" << endl;
            return;
        }

        string filename = "history_purchase.txt";
        ofstream file(filename);

        if (!file.is_open()) {
            cout << "Gagal membuat file!" << endl;
            return;
        }

        file << "=== HISTORI BOOKING LAPANGAN BEJO FUTSAL ===" << endl;
        for (size_t i = 0; i < bookings.size(); i++) {
            file << "\nBooking ke-" << i + 1 << ":" << endl;
            file << "Tanggal      : " << bookings[i].getTanggalBooking() << endl;
            file << "Nama         : " << bookings[i].getNama() << endl;
            file << "Lapangan     : " << bookings[i].getLapangan() << endl;
            file << "Jam Mulai    : " << setfill('0') << setw(2) 
                 << bookings[i].getJam() << ":00" << endl;
            file << "Durasi       : " << bookings[i].getDurasi() << " jam" << endl;
            file << "Total Biaya  : Rp " << fixed << setprecision(0) 
                 << bookings[i].getBiaya() << endl;
            file << string(30, '=') << endl;
        }

        file.close();
        cout << "\nHistory purchase berhasil didownload ke file '" << filename 
             << "'!" << endl;
    }

    void hapusBooking() {
        if (bookings.empty()) {
            cout << "\nBelum ada data booking untuk dihapus!" << endl;
            return;
        }

        cout << "\n=== Hapus Data Booking ===" << endl;
        lihatHistoriPurchase();

        int no;
        cout << "Masukkan nomor booking yang akan dihapus: ";
        cin >> no;

        if (no < 1 || no > static_cast<int>(bookings.size())) {
            cout << "Nomor booking tidak valid!" << endl;
            return;
        }

        bookings.erase(bookings.begin() + no - 1);
        cout << "\nData booking berhasil dihapus!" << endl;
    }

    bool validateAdminPassword(const string& password) {
        return password == adminPassword;
    }

    void run() {
        int menu;
        do {
            cout << "\n=== Aplikasi Booking Lapangan Bejo Futsal ===" << endl;
            cout << "1. Admin" << endl;
            cout << "2. Pembeli" << endl;
            cout << "3. Keluar" << endl;
            cout << "Pilih menu: ";
            cin >> menu;

            switch (menu) {
            case 1: {
                string password;
                cout << "Masukkan password admin: ";
                cin >> password;

                if (validateAdminPassword(password)) {
                    int pilihanAdmin;
                    do {
                        cout << "\n=== Menu Admin ===" << endl;
                        cout << "1. Edit Status Lapangan" << endl;
                        cout << "2. Lihat Histori Purchase" << endl;
                        cout << "3. Hapus Data Booking" << endl;
                        cout << "4. Download History Purchase" << endl;
                        cout << "5. Kembali ke Menu Utama" << endl;
                        cout << "Pilih menu: ";
                        cin >> pilihanAdmin;

                        switch (pilihanAdmin) {
                        case 1:
                            editStatusLapangan();
                            break;
                        case 2:
                            lihatHistoriPurchase();
                            break;
                        case 3:
                            hapusBooking();
                            break;
                        case 4:
                            downloadHistoriPurchase();
                            break;
                        case 5:
                            break;
                        default:
                            cout << "Menu tidak valid!" << endl;
                        }
                    } while (pilihanAdmin != 5);
                } else {
                    cout << "Password salah!";
                }
                break;
            }
            case 2: {
                int pilihanPembeli;
                do {
                    cout << "\n=== Menu Pembeli ===" << endl;
                    cout << "1. Booking Lapangan" << endl;
                    cout << "2. Kembali ke Menu Utama" << endl;
                    cout << "Pilih menu: ";
                    cin >> pilihanPembeli;

                    switch (pilihanPembeli) {
                    case 1:
                        bookingLapangan();
                        break;
                    case 2:
                        break;
                    default:
                        cout << "Menu tidak valid!" << endl;
                    }
                } while (pilihanPembeli != 2);
                break;
            }
            case 3:
                cout << "Terima kasih telah menggunakan aplikasi ini!" << endl;
                break;
            default:
                cout << "Menu tidak valid!" << endl;
            }
        } while (menu != 3);
    }
};

int main() {
    BejoFutsalSystem system;
    system.run();
    return 0;
}
