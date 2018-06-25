#include<stdc++.h>
#include<conio.h>
#include "thongtin.h"
#include <windows.h> //  dung cho clrscr

#define __STDC_WANT_LIB_EXT1__ 1
#include <time.h>
#include <ctime>
#include <iostream>
#include <filesystem>
#include <string>

/* ************************************************************************************* */
/*                               khai bao bien toan cuc                                  */
/* ************************************************************************************* */
namespace fs = experimental::filesystem;
using namespace std;

string username, password, hoten, ngaysinh, noio;
bool gioitinh;
string cfpass, name, cur;
fstream user_file;
fstream pass_file;
fstream data_file, listfr_file;

thongtin tt;

void showmess();
void detailmess();
void sendmess();
void addfr();
void showfr();
void blockfr();
int kiemtralistfr();
void replace();
//ham xoa man hinh
void clrscr()
{
	COORD origin = { 0, 0 };
	unsigned long len;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	unsigned long size;
	void* handle = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(handle, &csbi);
	size = csbi.dwSize.X * csbi.dwSize.Y;
	FillConsoleOutputCharacter(handle, TEXT(' '), size, origin, &len);
	FillConsoleOutputAttribute(handle, csbi.wAttributes, size, origin, &len);
	SetConsoleCursorPosition(handle, origin);
}
void Exit() {
	exit(0);
}
// tim va kiem tra user+pass
int Search()
{
	clrscr();
	user_file.open("user.txt", ios::in);
	cout << "Login:" << endl;
	cout << "Please enter the username login: ";
	cin >> username;
	cout << "Please enter the password: ";
	cin >> password;

	int index = 0;
	string line;
	int lineuser = -9999, linepass = -9999;

	while (!user_file.eof())
	{
		index++;
		getline(user_file, line);
		if (username == line)
		{
			lineuser = index;
			name = line;
		}
	}
	user_file.close();
	pass_file.open("pass.txt", ios::in);
	index = 0;
	while (!pass_file.eof())
	{
		index++;
		getline(pass_file, line);
		if (index == lineuser)
		{
			if (password == line)
			{
				linepass = index;
			}
		}
	}
	pass_file.close();
	if (lineuser == -9999 || linepass == -9999) { return 0; }
	else {
		return 1;
	}
	_getch();
}

// login
void Login()
{
	bool cinfail;
	int chon;
	int check = Search();
	if (check == 0) { cout << "login fail"; _getch(); }
	else {
		cout << "login success: " << name << endl;
		cur = name;
		cout << "chon menu: [1]showmess [2]detailmess [3]sendmess [4]Addfriend [5]showfr [6]block [7]exit" << endl;
		cout << "ban chon so: ";
		cin >> chon;
		do {
			cinfail = cin.fail();
			cin.clear();
			cin.ignore(10000, '\n');
		} while (cinfail == true); {
			switch (chon) {
			case 1:
				showmess();
				break;
			case 2:
				detailmess();
				break;
			case 3:
				sendmess();
				break;
			case 4:
				addfr();
				break;
			case 5:
				showfr();
				break;
			case 6:
				blockfr();
				break;
			case 7:
				Exit();
			}
		}
	}
	_getch();
}
// ghi file
void writetofile() {
	user_file.open("user.txt", ios::app);
	pass_file.open("pass.txt", ios::app);
	data_file.open("mess" + username + ".txt", ios::app);
	listfr_file.open("list" + username + ".txt", ios::out);

	tt.setusername(username);
	tt.setpassword(password);
	tt.sethoten(hoten);
	tt.setngaysinh(ngaysinh);
	tt.setgioitinh(gioitinh);
	tt.setnoio(noio);

	user_file << tt.getusername() << endl;
	pass_file << tt.getpassword() << endl;
	data_file << tt.gethoten() << "," << tt.getngaysinh() << "," << tt.getgioitinh() << "," << tt.getnoio() << endl;
	listfr_file.close();
	data_file.close();
	user_file.close();
	pass_file.close();
}
// dang ky
void Register() {
	clrscr();
	string userlogin;
	cout << "Please enter the username: ";
	cin >> username;
	cout << "Please enter the password: ";
	cin >> password;
	cout << "Please enter the Name: ";
	cin >> hoten;
	cout << "Please enter the Year of Birth: ";
	cin >> ngaysinh;
	cout << "Please enter the Gender Nam(1) or Nu(0): ";
	cin >> gioitinh;
	cout << "Please renter your address: ";
	cin >> noio;
	cout << "Please enter your password again: ";
	cin >> cfpass;
	user_file.open("user.txt", ios::in);
	vector<string> us;
	while (!user_file.eof())
	{
		getline(user_file, userlogin);
		us.push_back(userlogin);
	}
	user_file.close();
	int check = 0;
	for (auto v:us) {
		if (username == v){check = 0;break;}
		else{check = 1;}
	}
	if (check==0) {cout << "user exists"; _getch();}
	else
	{
		writetofile();
		cout << "Account successfully created !!!" << endl;
		_getch();
	}
}
// logout
void logout()
{
	cur = "";
	cout << cur;
	_getch();
}
//////
//******* Module 2  ********
// Get current date/time, format is YYYY-MM-DD.HH:mm:ss
string dtime;
void currentDateTime() {
	// Current date/time based on current system
	time_t now = time(0);
	// convert now to string form
	dtime = ctime(&now);
}
// cat chuoi
const vector<string> explode(const string& s, const char& c)
{
	string buff{ "" };
	vector<string> v;
	for (auto n : s)
	{
		if (n != c) buff += n; else
			if (n == c && buff != "") { v.push_back(buff); buff = ""; }
	}
	if (buff != "") v.push_back(buff);
	return v;
}
void showmess()
{
	string infor;
	int index = 0;
	data_file.open("mess" + name + ".txt", ios::in);
	getline(data_file, infor);
	while (!data_file.eof())
	{
		index++;
		getline(data_file, infor);
		if (infor.find("I-" + name) != string::npos) {
			cout << infor << endl;
		}
	}
	data_file.close();
	_getch();
}
void detailmess()
{
	string infor;
	int num;
	vector<string> numlines;
	data_file.open("mess" + name + ".txt", ios::in);
	getline(data_file, infor);
	while (!data_file.eof())
	{
		getline(data_file, infor);
		numlines.push_back(infor);
	}
	cout << "Nhap dong ban muon xem: ";
	cin >> num;
	int n = numlines.size();
	for (int i = 0; i < n - 1; i++) {
		if (i == (num - 1)) {
			vector<string> v{ explode(numlines[i], ':') };
			cout << "sender: " << v[0] << endl;
			cout << "content: " << v[1] << endl;
			cout << "time: " << v[2];
			cout << ":" << v[3];
			cout << ":" << v[4] << endl;
		}
	}
	data_file.close();
	_getch();
}
void sendmess()
{
	string fri, send;
	fstream you, fr;
	int check = 0;
	currentDateTime();
	cout << "input friend:";
	cin >> fri;
	ifstream readfile_block;
	string line;
	readfile_block.open("bl" + username + ".txt");
	while (getline(readfile_block, line))
	{
		if (fri == line) {
			check = 0;
		}
		else { check = 1; }
	}
	if (check==0) {
		cout << "|----- Fall !!! You have been Blocked ----|" << endl;
	}
	else
	{
		you.open("mess" + name + ".txt", ios::app);
		string a;
		fr.open("mess" + fri + ".txt", ios::app);
		bool ret = fr.fail();
		if (ret == false) {
			cout << "friend exist" << endl;
			cout << "send mess to friend: ";
			cin.ignore();
			getline(cin, send);
			you << "I-" << name + ": " << send << " : " << dtime;
			fr << "		" << "sender-" << name + ":" << send << " : " << dtime;
			you.close();
			fr.close();
			cout << "|----- Gui thanh cong !!! ----|" << endl;
		}
		else {
			cout << " friend don't exist";
		}
	}
	readfile_block.close();
	_getch();
}

/////////
////******* Module 3  ********
vector<string> GetFileNamesInDirectory(string directory) {
	vector<std::string> files;
	WIN32_FIND_DATA fileData;
	HANDLE hFind;
	if (!((hFind = FindFirstFile(directory.c_str(), &fileData)) == INVALID_HANDLE_VALUE)) {
		while (FindNextFile(hFind, &fileData)) {
			files.push_back(fileData.cFileName);
		}
	}
	FindClose(hFind);
	return files;
}
vector <string> chuoi;
string addfriend, inputfr;
void addfr()
{
	vector<string> vFileNames = GetFileNamesInDirectory("*.txt");
	//vector<string> vFileNames = GetFileNamesInDirectory("C: \ *.txt");
	string s, sub, infor;
	int index = 0;
	currentDateTime();
	cout << "friend: ";
	int n = vFileNames.size();
	for (int i = 0; i < n; i++) {
		s = vFileNames[i];
		int pos = s.find("mess");
		if (pos == 0) {
			// lay sau vi tri s
			sub = s.substr(pos + 4);
			/*
			// cach 1
			//convert sub ve char
			char *str = const_cast< char *>(sub.c_str());
			// cat chuoi
			char * p = strtok(str, ".");
			cout << "friend: " << p << " ";
			*/
			// cach 2
			//convert sub ve char 
			char * cstr = new char[sub.length()];
			// coppy chuoi
			strcpy(cstr, sub.c_str());
			// cat chuoi
			char * p = strtok(cstr, ".");
			if (p == username) {
				continue;
			}
			else {
				index++;
				chuoi.push_back(p);
				cout << index << ":" << p << "  ";
			}
		}
	}
	cout << endl;
	/********************** add friend ***************************/
	//listfr_file.open("list" + username + ".txt", ios::out | ios::in | ios::app);
	vector<string> add;
ktra:
	int check = kiemtralistfr();
	if (check == 0) {
		listfr_file.open("list" + username + ".txt",ios::in);
		while (!listfr_file.eof())
		{
			getline(listfr_file, infor);
			add.push_back(infor);
		}
		listfr_file.close();
		listfr_file.open("list" + username + ".txt", ios::app);
		int nn = add.size();
		for (int i = 0; i < nn;i++) {
			int bien = addfriend.compare(add[i]);
			if (bien == 1) {
				cout << "add thanh cong";
				listfr_file << addfriend << " : " << dtime;
				break;
			}
			else
			{
				cout << "da co ban trong danh sach";
				break;
			}
		}
		listfr_file.close();
	}
	else { cout << "khong co ten tai khoan hoac ten chua duoc dang ky" << endl; goto ktra; }
	listfr_file.close();
	_getch();
}
int kiemtralistfr() {
	cout << "add friend to list: ";
	cin >> addfriend;
	int n = chuoi.size();
	for (int i = 0; i < n; i++)
	{
		if (addfriend == chuoi[i]) {
			return 0;
		}
	}
	return 1;
}
void showfr()
{
	string readlistfr;
	listfr_file.open("list" + username + ".txt", ios::in);
	while (!listfr_file.eof())
	{
		getline(listfr_file, readlistfr);
		cout << readlistfr << endl;
	}
	listfr_file.close();
	_getch();
}
void blockfr()
{
	string infor;
	listfr_file.open("list" + username + ".txt", ios::in);
	vector<string> vec, vc;
	while (!listfr_file.eof())
	{
		getline(listfr_file, infor);
		vec.push_back(infor);
	}
	cout << "friend: ";
	vector<string>::iterator vv = vec.begin();
	while (vv != vec.end() - 1) {
		vector<string> vecter1{ explode(*vv, ':') };
		vector<string>::iterator vecter2 = vecter1.begin();
		while (vecter2 != vecter1.end())
		{
			cout << vecter2[0] << " ";
			vc.push_back(vecter2[0]);
			break;
		}
		vv++;
	}
	cout << endl;
	cout << "friend want to delete:";
	cin >> inputfr;
	inputfr = inputfr + " ";
	listfr_file.close();
	ofstream Block_File;
	ifstream file_block;
	Block_File.open("bl" + username + ".txt", ios::app);
	string line;
	int check = 0;
	vector<string>::iterator vcc = vc.begin();
	file_block.open("bl" + username + ".txt", ios::in);
	file_block.seekg(0, ios::end);
	int length = file_block.tellg();
	if (length == 0) {
		// ...do something with empty file...  
		Block_File << inputfr << endl;
		cout << "+----- Block " << inputfr << " thanh cong !!! -----+" << endl;
	}
	else
	{
		while (vcc != vc.end())
		{
			if (inputfr == vcc[0]) {
				/*string str3, str1 = "bl-";
				char *str = const_cast< char *>(str3.c_str());
				char *strbl = const_cast< char *>(str1.c_str());
				char *inpfr = const_cast< char *>(inputfr.c_str());
				strcpy(str, strbl);
				strcat(str, inpfr);
				stringstream myStreamString;
				myStreamString << str;
				string myString = myStreamString.str();
				vcc[0].replace(vcc[0].find(inputfr), inputfr.size(), myString);
				cout << vcc[0];*/

				while (getline(file_block, line)) {
					if (inputfr == line) { check = 0; break; }
					else { check = 1; }
				}
				file_block.close();
			}
			vcc++;
		}
		if (check == 0) {
			cout << inputfr << "da trong ds block !!! -----+" << endl;
		}
		else {
			Block_File << vcc[0] << endl; 
			cout << "+----- Block " << vcc[0] << " thanh cong !!! -----+" << endl;
		}
	}
	file_block.close();
	Block_File.close();
	_getch();
}
void replace()
{
	
}
// main
void print_menu() {
	cout << "Danh sach lua chon:\r\n";
	cout << "\t1. [1] Login\r\n";
	cout << "\t2. [2] Register\r\n";
	cout << "\t2. [3] Logout\r\n";
	cout << "\t3. [4] Exit\r\n";
	cout << "\r\n>> Chon (1->4) tuong ung : ";
}
int main()
{
	int choice = 0;
	do {
		system("cls");
		print_menu();
		fflush(stdin);
		cin >> choice;
		switch (choice) {
		case 1:
			Login();
			break;
		case 2:
			Register();
			break;
		case 3:
			logout();
			break;
		case 4:
			break;
		default:
			printf("\r\n>> Ban chon sai, an phim bat ki de chon lai..");
			_getch();
		}
		if (choice == 4)
		{
			break;
		}
	} while (1);
	// Stop to view
	printf("\r\n>> Nhap phim bat ki de ket thuc chuong trinh...");
	_getch();
	return 0;
}