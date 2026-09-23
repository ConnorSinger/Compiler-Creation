#include<iostream>
#include<fstream>

using namespace std;

const int PRIME = 2003;

int ebhash2(char *str)
        {
                char *p=str;
                unsigned h=*p;
                while(*++p) h = (h<<1)^*p++;
                return h%PRIME;
        }
int main()
        {
        char name[20];
        int freq[PRIME];
        int hvalue;
        ifstream fin("reserve.txt");
        ofstream fout("hashvalue.txt");

        while(fin>>name)
                {
                hvalue = ebhash2(name);
                cout<<name<<"  "<<hvalue<<endl;
                fout<<hvalue<<"  ";
                }
        fin.close();
        fout.close();
        for(int i=0; i<=PRIME; i++)
                {
                        freq[i]=0;
                }
                fin.open("hashvalue.txt");
                while(fin>>hvalue)
                {
                        freq[hvalue]=freq[hvalue]+1;
                        if(freq[hvalue]>1)
                        {
                                cout<<hvalue<<"colide:"<<freq[hvalue]-1<<endl;
                        }
                }

        }
