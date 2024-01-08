#include <iostream>
#include <string>
#include <vector>
#include <conio.h>
#include <iomanip>
#include <numeric> 
#include <map>
#include <unordered_map>
#include <functional>

using namespace std;

// DEKLARASI STRUCT

// Struktur data untuk admin (username & password)
struct Admin {
	string username;
	string password;
};

vector<Admin> listAdmin;

struct Barang {
	string nama;
	string kategori;
	string satuan;
	int jumlah;
};

struct Ruangan {
	string nama;
	vector<Barang> inventaris;
};

struct Gedung {
	string nama;
	vector<Ruangan> listRuangan;
};

struct Kolom {
	string nama;
	string field;
	string align;
};


// DEKLARASI VARIABLE

map<int, string> menuUtama = {
	{0, "Keluar"},
	{1, "Pilih Gedung"},
	{2, "Tambah Gedung"},
	{3, "Edit Gedung"},
	{4, "Hapus Gedung"},
	{5, "Log Out"},
};

map<int, string> menuRuangan = {
	{0, "Kembali ke Menu Utama"},
	{1, "Inventaris Ruangan"},
	{2, "Tambah Ruangan"},
	{3, "Edit Ruangan"},
	{4, "Hapus Ruangan"},
};

map<int, string> menuInventaris = {
	{0, "Kembali ke Menu Ruangan"},
	{1, "Tambah Barang"},
	{2, "Edit Barang"},
	{3, "Hapus Barang"},
};

vector<Gedung> daftarGedung;

map<int, Kolom> daftarKolom = {
	{0, {"No", "-", "right"}},
	{1, {"Barang", "nama", "left"}},
	{2, {"Kategori", "kategori", "right"}},
	{3, {"Jumlah", "jumlah", "right"}},
	{4, {"Satuan", "satuan", "right"}}
};


// DEKLARASI FUNGSI 
// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Tampilan & Proses Login >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void tampilanLogin();
void tambahkanPengguna(vector<Admin>& listAdmin);
bool proseslogin(string& username, string& password, const vector<Admin>& listAdmin);
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> MENU UTAMA <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
int tampilDanPilihMenu(map<int, string> daftarMenu, string title);
void tampilkanDaftarGedung(vector<Gedung> daftar = daftarGedung);
void tambahGedung();
void pilihGedung();
void editNamaGedung(Gedung& gedung);
void hapusGedung();
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> MENU RUANGAN <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
void tampilkanDaftarRuangan(vector<Ruangan> daftar, string nama_gedung);
void tambahRuangan(Gedung& gedung);
void invetarisRuangan(vector<Ruangan>& list, string nama_gedung);
void editNamaRuangan(Ruangan& ruangan);
void hapusRuangan(Gedung& gedung);
// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> INVENTARIS <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
string ambilDataInventarisDenganNamaKolom(const Barang& barang, const string& nama_kolom);
void tampilkanDaftarInventaris(vector<Barang>& daftar);
void tambahBarangInventaris(Ruangan& ruangan);
void editBarang(Barang& barang);
void hapusBarang(Ruangan& ruangan);

int main() 
{
	tampilanLogin();

	while (true) {
		system("cls");
		tampilkanDaftarGedung();

		switch (tampilDanPilihMenu(menuUtama, "Menu Utama")) {
		case 1:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Pilih Gedung
			if (daftarGedung.size()) pilihGedung();
			else {
				cout << "Daftar Gedung kosong!" << endl;
				system("pause");
			}
			break;
		case 2:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Tambah Gedung
			cin.ignore();
			tambahGedung();
			break;
		case 3:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Edit Gedung
			if (!daftarGedung.empty()) {
				system("cls");
				tampilkanDaftarGedung();
				size_t idGedung;
				cout << "Masukkan nomor Gedung yang akan diedit: ";
				cin >> idGedung;

				if (idGedung > 0 && idGedung <= daftarGedung.size()) {
					editNamaGedung(daftarGedung[idGedung - 1]);
				}
				else {
					cout << "Nomor Gedung tidak valid!" << endl;
					system("pause");
				}
			}
			else {
				cout << "Daftar Gedung kosong!" << endl;
				system("pause");
			}
			break;
		case 4:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Hapus Gedung
			hapusGedung();
			break;
		case 5:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Log Out
			system("cls");
			tampilanLogin();
			break;
		case 0:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Keluar
			cout << "Good Bye!" << endl;
			return 0;
		default:
			break;
		}
	}

	return 0;
}

// <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<< Tampilan & Proses Login >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>
void tampilanLogin()
{
	string inputUsername, inputPassword;
	bool loginBerhasil = false;

	do {
		loginBerhasil = proseslogin(inputUsername, inputPassword, listAdmin);

		if (!loginBerhasil) {
			char pilihan;
			cout << "Apakah Anda ingin menambahkan admin baru? (y/n): ";
			cin >> pilihan;

			if (pilihan == 'y' || pilihan == 'Y') {
				system("cls");
				tambahkanPengguna(listAdmin);
			}
			else {
				system("cls");
			}
		}
	} while (!loginBerhasil);
	cout << "\nLogin admin berhasil!" << endl;
	system("pause");
	system("cls");
}

void tambahkanPengguna(vector<Admin>& listAdmin)
{
	Admin admin;
	cout << "+-----------------------+" << endl;
	cout << "| Penambahan User Admin |" << endl;
	cout << "+-----------------------+" << endl;
	cout << "Masukkan username admin baru: ";
	cin >> admin.username;
	cout << "Masukkan password admin baru: ";
	cin >> admin.password;

	listAdmin.push_back(admin);
	cout << "Admin berhasil ditambahkan!" << endl;
	system("pause");
	system("cls");
}

bool proseslogin(string& username, string& password, const vector<Admin>& listAdmin)
{
	cout << "+-------------------------------+" << endl;
	cout << "| Selamat datang! Silakan login |" << endl;
	cout << "+-------------------------------+" << endl;
	cout << "Username : ";
	cin >> username;

	cout << "Password : ";
	char ch;
	password = "";
	while ((ch = _getch()) != '\r') {
		if (ch == '\b') {
			if (!password.empty()) {
				cout << "\b \b";
				password.pop_back();
			}
		}
		else {
			cout << '*';
			password.push_back(ch);
		}
	}

	for (const auto& admin : listAdmin) {
		if (admin.username == username && admin.password == password) {
			return true;
		}
	}

	cout << "\nLogin gagal. Coba lagi!" << endl;
	return false;
}

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> MENU UTAMA <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

int tampilDanPilihMenu(map<int, string>daftarMenu, string title) {
	cout << title << ":" << endl;

	for (auto menu : daftarMenu) {
		if (menu.first != 0) {
			cout << " " << menu.first << ") " << menu.second << endl;
		}
	}
	cout << " 0) " << daftarMenu[0] << endl;
	cout << endl;

	while (true) {
		int pilihan;
		cout << "Pilih Menu: ", cin >> pilihan;

		for (auto menu : daftarMenu) {
			if (menu.first == pilihan) return pilihan;
		}

		cout << "Mohon pilih menu yang tersedia!" << endl;
	}

	system("pause");
	return 0;
}

void tampilkanDaftarGedung(vector<Gedung> daftar) {

	cout << " Daftar Gedung" << endl;
	cout << "------------------------------" << endl;

	if (daftar.size()) {
		int number = 1;
		for (Gedung gedung : daftar) {
			cout << " " << number << ". Gedung " << gedung.nama << endl;
			number++;
		}
	}
	else {
		string keterangan = "kosong";
		cout << setw((30 / 2) + (keterangan.length() / 2)) << keterangan << setw((30 / 2) - (keterangan.length() / 2)) << "" << endl;
	}

	cout << endl;
}

void tambahGedung() {
	system("cls");
	Gedung gedung_baru;

	cout << "Tambah Gedung Baru" << endl;
	cout << " > Nama Gedung: ", getline(cin, gedung_baru.nama);

	daftarGedung.push_back(gedung_baru);
	cout << endl << "Gedung \"" << gedung_baru.nama << "\" berhasil ditambahkan!" << endl;

	system("pause");
}

void pilihGedung() {
	size_t id_gedung;

	while (true) {
		cout << " > Nomor Gedung: ", cin >> id_gedung;

		if (id_gedung <= daftarGedung.size() && id_gedung > 0) {
			break;
		}

		cout << "Mohon pilih nomor gedung yang tersedia (1-" << daftarGedung.size() << ")!" << endl;
	}

	Gedung& gedung = daftarGedung[id_gedung - 1];

	bool stay = true;
	while (stay) {
		system("cls");
		tampilkanDaftarRuangan(gedung.listRuangan, gedung.nama);

		switch (tampilDanPilihMenu(menuRuangan, "Menu Ruangan")) {
		case 0:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Kembali Ke Menu Utama
			stay = false;
			break;
		case 1:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Inventaris Ruangan
			if (gedung.listRuangan.size()) invetarisRuangan(gedung.listRuangan, gedung.nama);
			else {
				cout << "Daftar Ruangan Kosong!" << endl;
				system("pause");
			}
			break;
		case 2:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Tambah Ruangan
			cin.ignore();
			tambahRuangan(gedung);
			break;
		case 3:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Edit Nama Ruangan
			if (!gedung.listRuangan.empty()) {
				system("cls");
				tampilkanDaftarRuangan(gedung.listRuangan, gedung.nama);
				size_t idRuangan;
				cout << "Masukkan nomor Ruangan yang akan diedit: ";
				cin >> idRuangan;

				if (idRuangan > 0 && idRuangan <= gedung.listRuangan.size()) {
					editNamaRuangan(gedung.listRuangan[idRuangan - 1]);
				}
				else {
					cout << "Nomor Ruangan tidak valid!" << endl;
					system("pause");
				}
			}
			else {
				cout << "Daftar Ruangan kosong!" << endl;
				system("pause");
			}
			break;
		case 4:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Hapus Ruangan
			if (!gedung.listRuangan.empty()) {
				hapusRuangan(gedung);
			}
			else {
				cout << "Daftar Ruangan kosong!" << endl;
				system("pause");
			}
			break;
		default:
			break;
		}
	}
}

void editNamaGedung(Gedung& gedung)
{
	string namaBaru;
	cout << "Masukkan nama baru untuk Gedung " << gedung.nama << ": ";
	cin.ignore();
	getline(cin, namaBaru);
	gedung.nama = namaBaru;
	cout << "Nama Gedung berhasil diubah menjadi \"" << gedung.nama << "\"!" << endl;
	system("pause");
}

void hapusGedung()
{
	if (daftarGedung.empty()) {
		cout << "Daftar Gedung kosong!" << endl;
		system("pause");
		return;
	}
	system("cls");
	tampilkanDaftarGedung();
	size_t idGedung;
	cout << "Masukkan nomor Gedung yang akan dihapus: ";
	cin >> idGedung;
	if (idGedung > 0 && idGedung <= daftarGedung.size()) {
		string namaGedung = daftarGedung[idGedung - 1].nama;
		cout << "Apakah Anda yakin ingin menghapus Gedung " << daftarGedung[idGedung - 1].nama << "? (y/n): ";
		char pilihan;
		cin >> pilihan;
		if (pilihan == 'y' || pilihan == 'Y') {
			daftarGedung.erase(daftarGedung.begin() + (idGedung - 1));
			cout << "Gedung berhasil dihapus!" << endl;
			system("pause");
			system("cls");
		}
		else {
			cout << "Penghapusan dibatalkan." << endl;
			system("pause");
			system("cls");
		}
	}
	else {
		cout << "Nomor gedung tidak valid." << endl;
		system("pause");
		system("cls");
	}
}

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> MENU RUANGAN <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void tampilkanDaftarRuangan(vector<Ruangan> daftar, string nama_gedung) {
	cout << " Gedung " << nama_gedung << " | Daftar Ruangan" << endl;
	cout << "----------------------------------------" << endl;

	if (daftar.size()) {
		int number = 1;
		for (Ruangan ruang : daftar) {
			cout << " " << number << ". Ruangan " << ruang.nama << endl;
			number++;
		}
	}
	else {
		string keterangan = "kosong";
		cout << setw((40 / 2) + (keterangan.length() / 2)) << keterangan << setw((40 / 2) - (keterangan.length() / 2)) << "" << endl;
	}

	cout << endl;
}

void tambahRuangan(Gedung& gedung) {
	system("cls");
	Ruangan ruangan_baru;

	cout << "Tambah Ruangan Baru" << endl;
	cout << " > Nama Ruangan: ", getline(cin, ruangan_baru.nama);

	gedung.listRuangan.push_back(ruangan_baru);
	cout << endl << "Ruangan \"" << ruangan_baru.nama << "\" berhasil ditambahkan!" << endl;

	system("pause");
}

void editNamaRuangan(Ruangan& ruangan)
{
	string namaBaru;
	cout << "Masukkan nama baru untuk Ruangan " << ruangan.nama << ": ";
	cin.ignore();
	getline(cin, namaBaru);
	ruangan.nama = namaBaru;
	cout << "Nama Ruangan berhasil diubah menjadi \"" << ruangan.nama << "\"!" << endl;
	system("pause");
}

void hapusRuangan(Gedung& gedung)
{
	if (gedung.listRuangan.empty()) {
		cout << "Daftar Ruangan kosong!" << endl;
		system("pause");
		return;
	}

	system("cls");
	tampilkanDaftarRuangan(gedung.listRuangan, gedung.nama);
	size_t idRuangan;
	cout << "Masukkan nomor Ruangan yang akan dihapus: ";
	cin >> idRuangan;

	if (idRuangan > 0 && idRuangan <= gedung.listRuangan.size()) {
		string namaRuangan = gedung.listRuangan[idRuangan - 1].nama;
		cout << "Apakah Anda yakin ingin menghapus Ruangan " << gedung.listRuangan[idRuangan - 1].nama << "? (y/n): ";
		char pilihan;
		cin >> pilihan;

		if (pilihan == 'y' || pilihan == 'Y') {
			gedung.listRuangan.erase(gedung.listRuangan.begin() + (idRuangan - 1));
			cout << "Ruangan berhasil dihapus!" << endl;
			system("pause");
			system("cls");
		}
		else {
			cout << "Penghapusan dibatalkan." << endl;
			system("pause");
			system("cls");
		}
	}
	else {
		cout << "Nomor ruangan tidak valid." << endl;
		system("pause");
		system("cls");
	}
}

// >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>> INVENTARIS <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<

void invetarisRuangan(vector<Ruangan>& list, string nama_gedung) {
	size_t id_ruangan;

	while (true) {
		cout << " > Nomor Ruangan: ", cin >> id_ruangan;

		if (id_ruangan <= list.size() && id_ruangan > 0) {
			break;
		}

		cout << "Mohon pilih nomor ruangan yang tersedia (1-" << list.size() << ")!" << endl;
	}

	Ruangan& ruangan = list[id_ruangan - 1];

	bool stay = true;
	while (stay) {
		system("cls");
		cout << " Gedung " << nama_gedung << " | Ruangan " << ruangan.nama << " | Daftar Inventaris" << endl;
		tampilkanDaftarInventaris(ruangan.inventaris);

		switch (tampilDanPilihMenu(menuInventaris, "Menu Inventaris")) {
		case 0:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Kembali ke Menu Ruangan
			stay = false;
			break;
		case 1:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Tambah Barang
			cin.ignore();
			tambahBarangInventaris(ruangan);
			break;
		case 2:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Edit Barang
			if (!ruangan.inventaris.empty()) {
				system("cls");
				tampilkanDaftarInventaris(ruangan.inventaris);
				size_t idBarangEdit;
				cout << "Masukkan nomor Barang yang akan diedit: ";
				cin >> idBarangEdit;

				if (idBarangEdit > 0 && idBarangEdit <= ruangan.inventaris.size()) {
					editBarang(ruangan.inventaris[idBarangEdit - 1]);
				}
				else {
					cout << "Nomor Barang tidak valid!" << endl;
					system("pause");
				}
			}
			else {
				cout << "Daftar Barang kosong!" << endl;
				system("pause");
			}
			break;
		case 3:                        // >>>>>>>>>>>>>>>>>>>>>>>>> Hapus Barang
			if (!ruangan.inventaris.empty()) {
				hapusBarang(ruangan);
			}
			else {
				cout << "Daftar Barang kosong!" << endl;
				system("pause");
			}
			break;
		default:
			break;
		}
	}
}

string ambilDataInventarisDenganNamaKolom(const Barang& barang, const string& nama_kolom) {
	static const unordered_map<string, function<string(const Barang&)>> field_map = {
		{"nama", [](const Barang& barang) { return barang.nama; }},
		{"kategori", [](const Barang& barang) { return barang.kategori; }},
		{"jumlah", [](const Barang& barang) { return to_string(barang.jumlah); }},
		{"satuan", [](const Barang& barang) { return barang.satuan; }}
	};

	auto it = field_map.find(nama_kolom);
	if (it != field_map.end())
		return it->second(barang);
	else
		throw invalid_argument("Field name not found");
}

void tampilkanDaftarInventaris(vector<Barang>& daftar) {
	vector<int> column_width;
	int columns_width = 0;
	int key = 0;

	for (auto& kolom : daftarKolom) {
		int field_length = kolom.second.nama.length() + 2;

		column_width.push_back(field_length);
		columns_width += field_length;
		columns_width++;
	}

	int columns_data_width = column_width[0] + 1;
	for (Barang barang : daftar) {
		key = 0;
		for (auto& kolom : daftarKolom) {
			if (key != 0) {
				string field_value = ambilDataInventarisDenganNamaKolom(barang, kolom.second.field);
				int value_length = static_cast<int>(field_value.length()) + 2;

				column_width[key] = max(column_width[key], value_length);
				columns_data_width += value_length;
				columns_data_width++;
			}
			key++;
		}
	}

	columns_width = max(columns_width, columns_data_width);

	// Horizontal Line
	string line = "+";

	for (int width : column_width) {
		for (int i = 0; i < width; i++) {
			line += "-";
		}
		line += "+";
	}


	// Table Header
	cout << line << endl;

	key = 0;
	for (auto& kolom : daftarKolom) {
		if (key == 0) cout << char(179);;

		cout << setw(column_width[key]) << left << " " + kolom.second.nama;
		cout << char(179);

		key++;
	}
	cout << endl;

	// Table Body
	cout << line << endl;
	if (daftar.size()) {
		int number = 1;
		for (Barang barang : daftar) {
			key = 0;
			cout << char(179);
			for (auto& kolom : daftarKolom) {
				cout << setw(column_width[key]) << (kolom.second.align == "right" ? right : left) << (kolom.second.align == "right" ? "" : " ") + (key == 0 ? to_string(number) : ambilDataInventarisDenganNamaKolom(barang, kolom.second.field)) + (kolom.second.align == "right" ? " " : "");
				key++;
				cout << char(179);
			}
			number++;
			cout << endl;
		}
	}
	else {
		string text = "kosong";
		cout << char(179) << setw((columns_width / 2) + (text.length() / 2)) << right << text << setw((columns_width / 2) - (text.length() / 2)) << " " << char(179) << endl;
	}
	cout << line << endl;

	cout << endl;
}

void tambahBarangInventaris(Ruangan& ruangan) {
	system("cls");
	Barang barang;

	cout << "Tambah Barang" << endl;
	cout << " > Nama: ", getline(cin, barang.nama);
	cout << " > Kategori: ", getline(cin, barang.kategori);
	cout << " > Jumlah: ", cin >> barang.jumlah;
	cin.ignore();
	cout << " > Satuan: ", getline(cin, barang.satuan);

	ruangan.inventaris.push_back(barang);
	cout << endl << "Barang \"" << barang.nama << "\" berhasil ditambahkan ke Ruangan " << ruangan.nama << "!" << endl;

	system("pause");
}

void editBarang(Barang& barang)
{
	cout << "Edit Informasi Barang " << barang.nama << ":" << endl;
	cout << "1. Nama: " << barang.nama << endl;
	cout << "2. Kategori: " << barang.kategori << endl;
	cout << "3. Jumlah: " << barang.jumlah << endl;
	cout << "4. Satuan: " << barang.satuan << endl;

	int option;
	cout << "Pilih nomor informasi yang akan diedit (0 untuk kembali): ";
	cin >> option;

	switch (option) {
	case 1:
		cout << "Masukkan nama baru: ";
		cin.ignore();
		getline(cin, barang.nama);
		cout << "Nama Barang berhasil diubah menjadi \"" << barang.nama << "\"!" << endl;
		break;
	case 2:
		cout << "Masukkan kategori baru: ";
		cin.ignore();
		getline(cin, barang.kategori);
		cout << "Kategori Barang berhasil diubah menjadi \"" << barang.kategori << "\"!" << endl;
		break;
	case 3:
		cout << "Masukkan jumlah baru: ";
		cin >> barang.jumlah;
		cout << "Jumlah Barang berhasil diubah menjadi \"" << barang.jumlah << "\"!" << endl;
		break;
	case 4:
		cout << "Masukkan satuan baru: ";
		cin.ignore();
		getline(cin, barang.satuan);
		cout << "Satuan Barang berhasil diubah menjadi \"" << barang.satuan << "\"!" << endl;
		break;
	case 0:
		cout << "Pengeditan dibatalkan." << endl;
		break;
	default:
		cout << "Nomor informasi tidak valid." << endl;
		break;
	}

	system("pause");
}

void hapusBarang(Ruangan& ruangan)
{
	if (ruangan.inventaris.empty()) {
		cout << "Daftar Barang kosong!" << endl;
		system("pause");
		return;
	}

	system("cls");
	tampilkanDaftarInventaris(ruangan.inventaris);
	size_t idBarang;
	cout << "Masukkan nomor Barang yang akan dihapus: ";
	cin >> idBarang;

	if (idBarang > 0 && idBarang <= ruangan.inventaris.size()) {
		string namaBarang = ruangan.inventaris[idBarang - 1].nama;
		cout << "Apakah Anda yakin ingin menghapus Barang " << ruangan.inventaris[idBarang - 1].nama << "? (y/n): ";
		char pilihan;
		cin >> pilihan;

		if (pilihan == 'y' || pilihan == 'Y') {
			ruangan.inventaris.erase(ruangan.inventaris.begin() + (idBarang - 1));
			cout << "Barang berhasil dihapus!" << endl;
			system("pause");
			system("cls");
		}
		else {
			cout << "Penghapusan dibatalkan." << endl;
			system("pause");
			system("cls");
		}
	}
	else {
		cout << "Nomor barang tidak valid." << endl;
		system("pause");
		system("cls");
	}
}
