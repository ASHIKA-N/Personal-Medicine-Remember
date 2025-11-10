#pragma once
#include<iostream>
#include<fstream>
#include<string>
#include<functional>
using namespace std;
class Login{
private:
string file="user.txt";
string hashPassword(const string &password);
public:
void regist();
bool login();
};
