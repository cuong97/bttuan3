#pragma once
#include<stdc++.h>
#include<string>

using namespace std;

class thongtin
{
public:
		string username;
		string password;
		string hoten;
		string ngaysinh;
		bool gioitinh;
		string noio;
public:
	thongtin();
	string getusername();
	string getpassword();
	string gethoten();
	string getngaysinh();
	bool getgioitinh();
	string getnoio();

	void setusername(string username);
	void setpassword(string pasword);
	void sethoten(string hoten);
	void setngaysinh(string ngaysinh);
	void setgioitinh(bool gioitinh);
	void setnoio(string noio);
};