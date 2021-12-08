#include<bits/stdc++.h>
using namespace std;
int main()
{
    ofstream op("lichsuthi.csv");
    string line;
    if (!op.is_open())
        cout<<"Loi mo file"<<endl;
    op<<"Ho Ten,Nam sinh";
    line="";
    for (int i=0;i<10;i++)
    {
        // ostringstream convert;
        // convert << i; 
        // line = line+ "," + "Cau " + convert.str();
        op<<","<<i;
    }
    op.close();
}
