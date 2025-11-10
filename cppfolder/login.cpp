#include "../hppfolder/login.hpp"
string Login::hashPassword(const string &password){
hash<string> hashing;
return to_string(hashing(password));
}
void Login:: regist(){
    string user,pass;
    cout<<"Enter user name: ";
    cin>>user;
    cout<<"Enter password: ";
    cin>>pass;
    string hashpass=hashPassword(pass);
    ifstream filecheck(file);
    string u,v;
    while(filecheck>>u>>v){
        if(u==user){
            cout<<"User name aldready exist";
            return;
        }
    }
    filecheck.close();
    ofstream filereg(file,ios::app){
        if(filereg.is_open()){
            filereg<<user<<" "<<hashed<<endl;
            cout<<"Registered successfully!\n";
            filereg.close();
        }
        else{
            cout<<"could not open file!!\n"
        }
    }

}
bool Login::login(){
    string user,pass;
    cout<<"Enter user name: ";
    cin>>user;
    cout<<"Enter password: ";
    cin>>pass;
    string hashpass=hashPassword(pass);
     ifstream fileuser(file);
    string u,v;
    while(filecheck>>u>>v){
        if(!fileuser.is_open()){
            cout<<"No data found! \n";
            return false;
        }

    }
    string u,v;
    while(fileuser>>u>>v){
        if(u==user && v==pass){
            cout<<"Login successfull!\n";
            return true;
        }
    }
    cout<<"Invalid!\n";
    return false;
}
