#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <ctime>
using namespace std;

static const char alphanum[] =
"0123456789"
"ABCDEFGHIJKLMNOPQRSTUVWXYZ"
"abcdefghijklmnopqrstuvwxyz"
"!@#$%^&*";

int stringLength = 42;

char genRandom()
{

    return alphanum[rand() % 70];
}
char genRandom_nospecialchar()
{
	return alphanum[rand() % 62];
}

int main()
{
    srand(time(0));
    ofstream passwords_file;
    int choice;
    std::string password, username, website_url, password2;
    cout<<"Enter the url of the website here: ";
    cin>>website_url;
    cout<<"Enter your username/email for the website here: ";
    cin>>username;
    cout<<endl;
    for(int i = 0; i < stringLength; i++)
    {
    	password += genRandom();
		password2 += genRandom_nospecialchar();
    }
    cout << "Your strong passwords are listed below"<<endl;
    cout << "1. "<<password << endl;
    cout << "2. "<<password2 << endl;
    cout << "Select which password you want to use(either 1 or 2): ";
    cin>>choice;
    if (choice == 1)
    {
	    cout<<"You choose password 1"<<endl;
		passwords_file.open("passwords.csv", ios::app);
		passwords_file << website_url << ',' << username << ',' << password << endl;
		passwords_file.close();
    } 
    else if (choice == 2)
    {
	    cout<<"You choose password 2"<<endl;
		passwords_file.open("passwords.csv", ios::app);
		passwords_file << website_url << ',' << username << ',' << password2 << endl;
		passwords_file.close();
    }
    else
    {
	    cout<<"You did not enter a valid choice from the list provided"<<endl;
    }
    return 0;
    

}

