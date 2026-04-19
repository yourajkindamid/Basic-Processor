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

//store names of every operation very stupid idea
vector <string> totalops = {"STA", "INP", "LDA"};


//MEMORY
vector <string> RAM (4096, "");

//FLIPFLOPS
int IEN = 0;
int FGI = 0;
int FGO = 0;


// How many instructions would you be writing in memory today?
int nofinst = 0;


// this integer keeps in check where weve been storing stuff in RAM (v important for ultra Clear btw)
int ramdog = 0;


// our instructions with their own functions :)
void INP(int x)
{
    IPR[0] = x;
    ACCM[0] = x;
}

void STA(int x)
{
    RAM[x] = to_string(ACCM[0]);
}

void LDA(int x)
{
    ACCM[0] = stoi(RAM[x]);
}

// after a successful run of the program and the user wants to restart the program, everything will be cleared to 0 ^_^
void ultra_CLR()
{
    AR[0] = IR[0] = PC[0] = ACCM[0] = B [0] = TR[0] = OPR[0] = IPR[0] = CPR[0] = 0;

    ramdog = 0;

    for(int i = 0; i < 10; i++)
    {
        RAM[i] = "";
    }
}



void checkwhichop(string x, int y)
{
    int cheek = 0;
    for(int i = 0; i < totalops.size(); i++)
    {
        if(x == totalops[i])
        {
            cheek = i;
            break;
        }
        else
        {
            continue;
        }
    }

    switch (cheek)
    {
        case 0:
        STA(y);
        break;

        case 1:
        INP(y);
        break;

        case 2:
        LDA(y);
        break;
    }

}

void memorystuff()
{
    string x = "";
    int y = 0;
    int i = 0;
    cout << endl;
    cout << "Instructions: " << endl;
    cin >> x;

    cout << "Memory Address/Input Value (if none, input zero): " << endl;
    cin >> y;

    RAM[ramdog] = x + " " + to_string(y);

    ramdog++;

    checkwhichop(x, y);

    while(ramdog <= nofinst-1)
    {
        cout << "Instructions: " << endl;
        cin >> x;

        cout << "Memory Address/Input Value (if none, input zero): " << endl;
        cin >> y;

        RAM[ramdog] = x + " " + to_string(y);
        ramdog++;

        checkwhichop(x, y);
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
    cout << "    Address Register (AR) |   " << AR[0] << "   |" << "    Instruction Register (IR) |   " << IR[0] << "   |" << endl;
    cout << endl;
    cout << "Comparison Register (CPR) |   " << CPR[0] << "   |" << "          Accumulator (ACCM) |   " << ACCM[0] << "   |" << endl;
    cout << endl;
    cout << "           B Register (B) |   " << B[0] << "   |" << "       Temporary Register (TR) |   " << TR[0] << "   |" << endl;
    cout << endl;
    cout << "    Output Register (OPR) |   " << OPR[0] << "   |" << "         Input Register (IR) |   " << IPR[0] << "   |" << endl;
    cout << endl;
    cout << "     Program Counter (PC) |   " << PC[0] << "   |" << endl;
}

void memoryloop()
{
    cout << endl;
    cout << "\t\t\t\t\t\t\t\tMEMORY" << endl;
    for(int j = 0; j < 10; j++)
    {
        cout << "\t\t\t\t\t\t\t\t|____" << RAM[j] << "____|" <<  endl;
    }
}

void menu()
{
    system("color DE");

    string exit = " ";
    string situation = " ";
    howmanyins();
    mainbackground();
    memorystuff();
    mainbackground();
    memoryloop();
    cout << "Would you like to exit? Press E or if you wish to stay press N :)" << endl;
    cin >> exit;
    if(exit == "E")
    {
        cout << "Exiting..." << endl;
        Sleep(2000);
    }
    else if(exit == "N"){
        cout << "Would you like to store this data for the next session? Press Y if you do and N if you dont" << endl;
        cin >> situation;
        if(situation == "Y")
        {
            cout << "My name is walter white yo your data is safe lowk" << endl;
            Sleep(3000);
            system("cls");
            menu();
        }
        else
        {
            cout << "Your data is now gone...:(" << endl;
            Sleep(2000);
            ultra_CLR();
            system("cls");
            menu();
        }
    }
}
int main()
{
    menu();
}