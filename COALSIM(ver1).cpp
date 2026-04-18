#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
// #include <unistd.h>
using namespace std;

//REGISTERS
vector <int> AR (1, 0);
vector <int> IR (1, 0);
vector <int> PC (1, 0);
vector <int> ACCM (1, 0);
vector <int> B (1, 0);
vector <int> TR (1, 0);
vector <int> OPR (1, 0);
vector <int> IPR (1, 0);
vector <int> CPR (1, 0);

//MEMORY
vector <string> RAM (4096, "");

//FLIPFLOPS
int IEN = 0;
int FGI = 0;
int FGO = 0;


// How many instructions would you be writing in memory today?
int nofinst = 0;

void memorystuff()
{
    string x = "";
    int i = 0;
    cout << endl;
    cout << "Instructions: " << endl;
    getline(cin, x);
    while(x != "Complete")
    {
        getline(cin, x);
        RAM[i] = x;
        i++;
    }

    /* if "x == phalana dhimkana" switch statements of operations */

    system("cls");
}

void howmanyins()
{
    cout << "\t\t\t\tWelcome to the Basic Computer (Silly Processor)" << endl;
    cout << endl;
    cout << "How many instructions would you be writing in memory today?" << endl;
    cin >> nofinst;
    cout << "Thank you for letting me know!" << endl;
    Sleep(3000);
    system("cls");
}

void mainbackground()
{
    cout << "\t\t\t\t\tWelcome to the Basic Computer (Silly Processor)" << endl;
    cout << endl;
    cout << "    Address Register (AR) |   " << AR[0] << "   |" << "    Instruction Register (IR) |   " << AR[0] << "   |" << endl;
    cout << endl;
    cout << "Comparison Register (CPR) |   " << AR[0] << "   |" << "           Accumulator (ACCM) |   " << AR[0] << "   |" << endl;
    cout << endl;
    cout << "           B Register (B) |   " << AR[0] << "   |" << "      Temporary Register (TR) |   " << AR[0] << "   |" << endl;
    cout << endl;
    cout << "    Output Register (OPR) |   " << AR[0] << "   |" << "          Input Register (IR) |   " << AR[0] << "   |" << endl;
    cout << endl;
    cout << "     Program Counter (PC) |   " << AR[0] << "   |" << endl;
}

void memoryloop()
{
    cout << endl;
    cout << endl;
    cout << "\t\t\t\t\t\t\t\tMEMORY" << endl;
    for(int j = 0; j < nofinst; j++)
    {
        cout << "\t\t\t\t\t\t\t\t| " << RAM[j] << " |" << endl;
    }
}

void menu()
{
    system("color DE");

    string exit = " ";
    howmanyins();
    mainbackground();
    memorystuff();
    mainbackground();
    memoryloop();
    cout << "Would you like to exit? Press E" << endl;
    cin >> exit;
}
int main()
{
    menu();
}