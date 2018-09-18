#include <iostream>
#include <cstring>
#include <string>
using namespace std;

const int STRSIZE = 200;
const string WORDS = "a. display by name\tb. display by title\nc.display by bopname\t d. display by preference\n q. quit";

struct BOP {
    char fullname[STRSIZE];
    char title[STRSIZE];
    char bopname[STRSIZE];
    int preference;
};

int main(){
    char choice;
    const int size = 5;
    struct BOP bops[size];

   strcpy(bops[0].fullname,"Wimp Macho");
   strcpy(bops[1].fullname , "Raki Rhodes");
   strcpy(bops[2].fullname , "Celia Laiter");
   strcpy(bops[3].fullname , "Hoppy Hipman");
   strcpy(bops[4].fullname , "Pat Hand");

    cout<<WORDS;        
    cout<<"enter your choice: "<<endl;

    while(choice != 'q'){
        cin.get(choice);
        switch(choice){
            case 'a':
                for(int i =0; i< size; i++){
                    cout<<bops[i].fullname<<endl;
                }
                break;
            case 'b':
                cout<<"b is under construction, get the fuck off"<<endl;
                break;
            case 'c':
                cout<<"c is under construction, get the fuck off"<<endl;
                break;
            case 'd':
                cout<<"d is under construction, get the fuck off"<<endl;
                break;
            default:
                cout<<"once again"<<endl;
                break;
        }
    }
    cout<<"bye"<<endl;
}
