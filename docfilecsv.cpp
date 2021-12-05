#include<bits/stdc++.h>
using namespace std;
int main()
{
    ifstream ip("tk.csv");
    string hoten, diachi, namsinh, taikhoan, matkhau;
    if (!ip.is_open())
        cout<<"Loi mo file"<<endl;
    while (ip.good())
    {
        getline(ip,hoten,',');
        getline(ip,diachi,',');
        getline(ip,namsinh,',');
        getline(ip,taikhoan,',');
        getline(ip,matkhau,'\n');

        cout<<"Name: "<<hoten<<"\n";
        cout<<"Diachi: "<<diachi<<"\n";
        cout<<"Nam: "<<namsinh<<"\n";
        cout<<"Tk: "<<taikhoan<<"\n";
        cout<<"Mk: "<<matkhau<<"\n";
        cout<<"--------------------"<<endl;

    }
    ip.close();
}
