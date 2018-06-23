#include<stdc++.h>
#include<conio.h>
#include "thongtin.h"

using namespace std;

thongtin::thongtin(){}
string thongtin::getusername() {
	return username;
}
string thongtin::getpassword() {
	return password;
}
string thongtin::gethoten() {
	return hoten;
}
string thongtin::getngaysinh() {
	return ngaysinh;
}
bool thongtin::getgioitinh() {
	return gioitinh;
}
string thongtin::getnoio() {
	return noio;
}
void thongtin::setusername(string Usernamee) {
	username = Usernamee;
}
void thongtin::setpassword(string Password) {
	password = Password;
}
void thongtin::sethoten(string Hoten) {
	hoten = Hoten;
}
void thongtin::setngaysinh(string Ngaysinh) {
	ngaysinh = Ngaysinh;
}
void thongtin::setgioitinh(bool Gioitinh) {
	gioitinh = Gioitinh;
}
void thongtin::setnoio(string Noio) {
	noio = Noio;
}