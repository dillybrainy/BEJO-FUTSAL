#include <iostream>
#include <vector>
#include <iomanip>
#include <string>
#include <ctime>
#include <fstream>
using namespace std;

struct Booking {
    int lapangan;
    int jam;
    int durasi;
    string nama;
    string nomorTelepon;
    string metodePembayaran;
    double biaya;
    string tanggalBooking;
};

struct Lapangan {
    int nomor;
    vector<bool> jamKosong;
};

string getDaftarHarga() {
    string harga;
    harga = "\n=== DAFTAR HARGA ===\n";
    harga += "06:00 - 17:59 : Rp 90.000/jam\n";
    harga += "18:00 - 23:59 : Rp 120.000/jam\n";
    return harga;
}

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

void cetakNota(const Booking& booking) {
    cout << "\n" << string(40, '=') << endl;
    cout << "           NOTA BOOKING LAPANGAN           " << endl;
    cout << "               BEJO FUTSAL            " << endl;
    cout << string(40, '=') << endl;
    cout << "No. Booking   : FSC" << booking.tanggalBooking.substr(0,2) 
         << booking.lapangan << booking.jam << endl;
    cout << "Tanggal      : " << booking.tanggalBooking << endl;
    cout << string(40, '-') << endl;
    cout << "Nama         : " << booking.nama << endl;
    cout << "No. Telepon  : " << booking.nomorTelepon << endl;
    cout << string(40, '-') << endl;
    cout << "Detail Booking:" << endl;
    cout << "Lapangan     : " << booking.lapangan << endl;
    cout << "Jam Mulai    : " << setfill('0') << setw(2) << booking.jam << ":00" << endl;
    cout << "Durasi       : " << booking.durasi << " jam" << endl;
    cout << "Jam Selesai  : " << setfill('0') << setw(2) << booking.jam + booking.durasi << ":00" << endl;
    cout << string(40, '-') << endl;
    cout << "Pembayaran:" << endl;
    cout << "Metode       : " << booking.metodePembayaran << endl;
    cout << "Total Biaya  : Rp " << fixed << setprecision(0) << booking.biaya << endl;
    cout << string(40, '=') << endl;
    cout << "         Terima Kasih Atas Kunjungan         " << endl;
    cout << "    Silahkan Datang 15 Menit Sebelumnya    " << endl;
    cout << string(40, '=') << endl << endl;
}

void editStatusLapangan(vector<Lapangan>& lapangan) {
    cout << "\n=== Status Lapangan ===" << endl;
    for (int i = 0; i < 2; i++) {
        cout << "\nLapangan " << i + 1 << ":" << endl;
        for (int j = 6; j < 24; j++) {
            cout << setfill('0') << setw(2) << j << ":00 : " 
                 << (lapangan[i].jamKosong[j] ? "Kosong" : "Terisi") << endl;
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
    
    lapangan[nomorLapangan - 1].jamKosong[jam] = !lapangan[nomorLapangan - 1].jamKosong[jam];
    cout << "\nStatus lapangan " << nomorLapangan << " jam " << setfill('0') << setw(2) << jam << ":00"
         << " diubah menjadi " << (lapangan[nomorLapangan - 1].jamKosong[jam] ? "kosong" : "terisi") << endl;
}

void lihatHistoriPurchase(const vector<Booking>& bookings) {
    if (bookings.empty()) {
        cout << "\nBelum ada data booking!" << endl;
        return;
    }

    cout << "\n=== HISTORI BOOKING ===" << endl;
    for (size_t i = 0; i < bookings.size(); i++) {
        cout << "\nBooking ke-" << i + 1 << ":" << endl;
        cout << "Tanggal      : " << bookings[i].tanggalBooking << endl;
        cout << "Nama         : " << bookings[i].nama << endl;
        cout << "Lapangan     : " << bookings[i].lapangan << endl;
        cout << "Jam Mulai    : " << setfill('0') << setw(2) << bookings[i].jam << ":00" << endl;
        cout << "Durasi       : " << bookings[i].durasi << " jam" << endl;
        cout << "Total Biaya  : Rp " << fixed << setprecision(0) << bookings[i].biaya << endl;
    }
    cout << string(30, '=') << endl;
}

void downloadHistoriPurchase(const vector<Booking>& bookings) {
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
        file << "Tanggal      : " << bookings[i].tanggalBooking << endl;
        file << "Nama         : " << bookings[i].nama << endl;
        file << "Lapangan     : " << bookings[i].lapangan << endl;
        file << "Jam Mulai    : " << setfill('0') << setw(2) << bookings[i].jam << ":00" << endl;
        file << "Durasi       : " << bookings[i].durasi << " jam" << endl;
        file << "Total Biaya  : Rp " << fixed << setprecision(0) << bookings[i].biaya << endl;
        file << string(30, '=') << endl;
    }

    file.close();
    cout << "\nHistory purchase berhasil didownload ke file '" << filename << "'!" << endl;
}

void hapusBooking(vector<Booking>& bookings) {
    if (bookings.empty()) {
        cout << "\nBelum ada data booking untuk dihapus!" << endl;
        return;
    }

    cout << "\n=== Hapus Data Booking ===" << endl;

    lihatHistoriPurchase(bookings);

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

void tampilkanMenuUtama() {
    cout << "\n=== Aplikasi Booking Lapangan Bejo Futsal ===" << endl;
    cout << "1. Admin" << endl;
    cout << "2. Pembeli" << endl;
    cout << "3. Keluar" << endl;
    cout << "Pilih menu: ";
}

void menuAdmin() {
    cout << "\n=== Menu Admin ===" << endl;
    cout << "1. Edit Status Lapangan" << endl;
    cout << "2. Lihat Histori Purchase" << endl;
    cout << "3. Hapus Data Booking" << endl;
    cout << "4. Download History Purchase" << endl;
    cout << "5. Kembali ke Menu Utama" << endl;
    cout << "Pilih menu: ";
}

void menuPembeli() {
    cout << "\n=== Menu Pembeli ===" << endl;
    cout << "1. Booking Lapangan" << endl;
    cout << "2. Kembali ke Menu Utama" << endl;
    cout << "Pilih menu: ";
}

void bookingLapangan(vector<Lapangan>& lapangan, vector<Booking>& bookings) {
    cout << getDaftarHarga() << endl;
    
    int pilihanLapangan, jam, durasi;

    cout << "Pilih lapangan (1-2): ";
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

    for (int i = 0; i < durasi; i++) {
        if (!lapangan[pilihanLapangan - 1].jamKosong[jam + i]) {
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

    for (int i = 0; i < durasi; i++) {
        lapangan[pilihanLapangan - 1].jamKosong[jam + i] = false;
    }

    Booking booking;
    booking.lapangan = pilihanLapangan;
    booking.jam = jam;
    booking.durasi = durasi;
    booking.nama = nama;
    booking.nomorTelepon = nomorTelepon;
    booking.metodePembayaran = metodePembayaran;
    booking.biaya = totalBiaya;
    booking.tanggalBooking = getCurrentDateTime();
    bookings.push_back(booking);

    cetakNota(booking);
}

int main() {
    vector<Lapangan> lapangan(2, {0, vector<bool>(24, true)});
    vector<Booking> bookings;

    const string adminPassword = "admin123";

    int menu;
    do {
        tampilkanMenuUtama();
        cin >> menu;

        switch (menu) {
        case 1: {
            string password;
            cout << "Masukkan password admin: ";
            cin >> password;

            if (password == adminPassword) {
                int pilihanAdmin;
                do {
                    menuAdmin();
                    cin >> pilihanAdmin;

                    switch (pilihanAdmin) {
                    case 1:
                        editStatusLapangan(lapangan);
                        break;
                    case 2:
                        lihatHistoriPurchase(bookings);
                        break;
                    case 3:
                        hapusBooking(bookings);
                        break;
                    case 4:
                        downloadHistoriPurchase(bookings);
                        break;
                    case 5:
                        break;
                    default:
                        cout << "Pilihan tidak valid!" << endl;
                    }
                } while (pilihanAdmin != 5);
            } else {
                cout << "Password salah!" << endl;
            }
            break;
        }
        case 2: {
            int pilihanPembeli;
            do {
                menuPembeli();
                cin >> pilihanPembeli;

                switch (pilihanPembeli) {
                case 1:
                    bookingLapangan(lapangan, bookings);
                    break;
                case 2:
                    break;
                default:
                    cout << "Pilihan tidak valid!" << endl;
                }
            } while (pilihanPembeli != 2);
            break;
        }
        case 3:
            cout << "Terima kasih telah menggunakan aplikasi ini!" << endl;
            break;
        default:
            cout << "Pilihan tidak valid!" << endl;
        }
    } while (menu != 3);

    return 0;
}
