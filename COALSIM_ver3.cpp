#include <iostream>
#include <vector>
#include <string>
#include <windows.h>
using namespace std;

vector <int> AR(1,0), IR(1,0), PC(1,0), ACCM(1,0), B(1,0), TR(1,0), OPR(1,0), IPR(1,0), CPR(1,0);
int CARRY = 0, IEN = 0;


vector <string> totalops = {
    "STA","INP","LDA","ADD","AND","OR_fn","SUB","SWP","CMP","LDB",   
    "STB","NEG","SEA","JMP","BSA","STZ","NOT","CLA","ROTL","ROTR",   
    "ROTLC","ROTRC","BPA","DMG","ENCR","DECR","LOADB","STOREB",      
    "ADDB","SUBB","ANDB","ORB","MOVB","OUT","ION","IOF",             
    "MULTB","DIVB","JMPZ"                                            
};

vector <string> RAM(4097,"");
vector <int>    DATARAM(4097,0);

int nofinst    = 0;
int ramdog     = 0;
int exec_counter = 0;   


void execution();       

void INP(int x)   { IPR[0]=x; ACCM[0]=x; }
void STA(int x)   { DATARAM[x]=ACCM[0]; AR[0]=x; }
void LDA(int x)   { ACCM[0]=DATARAM[x]; AR[0]=x; }
void ADD(int x)   { ACCM[0]+=DATARAM[x]; AR[0]=x; }
void AND(int x)   { ACCM[0]=ACCM[0]&DATARAM[x]; AR[0]=x; }
void OR_fn(int x) { ACCM[0]=ACCM[0]|DATARAM[x]; AR[0]=x; }
void SUB(int x)   { ACCM[0]-=DATARAM[x]; AR[0]=x; }
void NEG()        { ACCM[0]=-(ACCM[0]); }
void SEA(int x)   { ACCM[0]=x; }
void NOT_fn()     { ACCM[0]=~ACCM[0]; }
void CLA()        { ACCM[0]=0; }
void OUT_fn()     { OPR[0]=ACCM[0]; cout<<"OUTPUT: "<<OPR[0]<<endl; }
void ION()        { IEN=1; }
void IOF()        { IEN=0; }
void STZ(int x)   { DATARAM[x]=0; AR[0]=x; }
void DMG(int x)   { ACCM[0]-=x; }



void JMP(int x)
{
    exec_counter = x;          
}

void BSA(int x)
{

    DATARAM[x] = exec_counter;
    AR[0]      = x;
    exec_counter = x + 1;     
}


void BPA(int x)
{
    if(ACCM[0] > 0) exec_counter = x;
}


void JMPZ(int x)
{
    if(ACCM[0] == 0) exec_counter = x;
}


void ENCR(int x)
{
    IPR[0] = x;
    int key  = x % 10;
    int text = 0;
    if(key != x)
    {
        text     = (x - key) / 10;
        ACCM[0]  = (text + key) % 26;
        OPR[0]   = (text + key) % 26;
    }
    else
    {
        ACCM[0]  = text + key;
        OPR[0]   = text + key;
    }
}

void DECR(int x)
{
    IPR[0] = x;
    int key  = x % 10;
    int text = 0;
    if(x == 0)        { ACCM[0] = 0; return; }
    if(key != x)
    {
        text     = (x - key) / 10;
        ACCM[0]  = (text + (26 - key)) % 26;
        OPR[0]   = (text + (26 - key)) % 26;
    }
    else
    {
        ACCM[0]  = 26 - key;
        OPR[0]   = 26 - key;
    }
}


void LOADB(int x)  { B[0]=DATARAM[x]; AR[0]=x; }
void STOREB(int x) { DATARAM[x]=B[0]; AR[0]=x; }
void ADDB()        { ACCM[0]+=B[0]; }
void SUBB()        { ACCM[0]-=B[0]; }
void ANDB()        { ACCM[0]=ACCM[0]&B[0]; }
void ORB()         { ACCM[0]=ACCM[0]|B[0]; }
void MOVB()        { B[0]=ACCM[0]; }
void MULTB()       { ACCM[0]=ACCM[0]*B[0]; }
void DIVB()        { if(B[0]!=0) ACCM[0]=ACCM[0]/B[0]; else cout<<"DIVB: division by zero"<<endl; }


void SWP(int x)
{
    TR[0]=DATARAM[x]; DATARAM[x]=ACCM[0]; ACCM[0]=TR[0]; AR[0]=x;
}

void CMP(int x)
{
    B[0]=DATARAM[x]; AR[0]=x;
    if     (ACCM[0]>B[0]) CPR[0]=8;
    else if(ACCM[0]<B[0]) CPR[0]=4;
    else                   CPR[0]=2;
}

void LDB(int x) { B[0]=DATARAM[x]; AR[0]=x; }
void STB(int x) { DATARAM[x]=B[0]; AR[0]=x; }


void ROTL()
{
    unsigned short v=(unsigned short)ACCM[0];
    ACCM[0]=(int)((v<<1)|(v>>15));
}
void ROTR()
{
    unsigned short v=(unsigned short)ACCM[0];
    ACCM[0]=(int)((v>>1)|(v<<15));
}
void ROTLC()
{
    unsigned short v=(unsigned short)ACCM[0];
    int nc=(v>>15)&1;
    ACCM[0]=(int)((v<<1)|CARRY);
    CARRY=nc;
}
void ROTRC()
{
    unsigned short v=(unsigned short)ACCM[0];
    int nc=v&1;
    ACCM[0]=(int)((v>>1)|(CARRY<<15));
    CARRY=nc;
}


void checkwhichop(string x, int y)
{
    int cheek=0;
    for(int i=0;i<(int)totalops.size();i++)
    {
        if(x==totalops[i]){ cheek=i; break; }
    }
    switch(cheek){
        case  0: STA(y);     break;
        case  1: INP(y);     break;
        case  2: LDA(y);     break;
        case  3: ADD(y);     break;
        case  4: AND(y);     break;
        case  5: OR_fn(y);   break;
        case  6: SUB(y);     break;
        case  7: SWP(y);     break;
        case  8: CMP(y);     break;
        case  9: LDB(y);     break;
        case 10: STB(y);     break;
        case 11: NEG();      break;
        case 12: SEA(y);     break;
        case 13: JMP(y);     break;
        case 14: BSA(y);     break;
        case 15: STZ(y);     break;
        case 16: NOT_fn();   break;
        case 17: CLA();      break;
        case 18: ROTL();     break;
        case 19: ROTR();     break;
        case 20: ROTLC();    break;
        case 21: ROTRC();    break;
        case 22: BPA(y);     break;
        case 23: DMG(y);     break;
        case 24: ENCR(y);    break;
        case 25: DECR(y);    break;
        case 26: LOADB(y);   break;
        case 27: STOREB(y);  break;
        case 28: ADDB();     break;
        case 29: SUBB();     break;
        case 30: ANDB();     break;
        case 31: ORB();      break;
        case 32: MOVB();     break;
        case 33: OUT_fn();   break;
        case 34: ION();      break;
        case 35: IOF();      break;
        case 36: MULTB();    break;
        case 37: DIVB();     break;
        case 38: JMPZ(y);    break;
    }
}

vector <string> m(100,"");
vector <int>    o(100, 0);


void execution()
{
    exec_counter = 0;
    while(exec_counter < nofinst)
    {
        int cur = exec_counter;
        exec_counter++;                     
        checkwhichop(m[cur], o[cur]);       
    }
}


void ultra_CLR()
{
    AR[0]=IR[0]=PC[0]=ACCM[0]=B[0]=TR[0]=OPR[0]=IPR[0]=CPR[0]=0;
    CARRY=0; IEN=0; ramdog=0;
    for(int i=0;i<4096;i++){ RAM[i]=""; DATARAM[i]=0; }
}

void memorystuff()
{
    int i=0;
    nofinst=0;
    cout<<endl;
    while(true)
    {
        cout<<"Instruction ["<<i<<"]: "; cin>>m[i];
        if(m[i]=="END") break;
        cout<<"Memory Address/Input Value (if none, input -1): ";
        cin>>o[i];
        RAM[ramdog]=m[i];
        DATARAM[ramdog]=o[i];
        ramdog++; PC[0]++; i++;
        nofinst++;
    }
    execution();
    RAM[ramdog]="END"; DATARAM[ramdog]=-1; ramdog++;
    system("cls");
}

void howmanyins()
{
    cout<<"\t\t\tWelcome to the 4097 x 17 Processor"<<endl<<endl;
    cout<<"Press ENTER to begin entering instructions."<<endl;
    cin.get();
    system("cls");
}

void mainbackground()
{
    cout<<"\t\t\t\tWelcome to the 4097 x 1 Processor"<<endl<<endl;
    cout<<"    Address Register (AR) |   "<<AR[0]<<"   |    Instruction Register (IR) |   "<<IR[0]<<"   |"<<endl<<endl;
    cout<<"Comparison Register (CPR) |   "<<CPR[0]<<"   |          Accumulator (ACCM) |   "<<ACCM[0]<<"   |"<<endl<<endl;
    cout<<"           B Register (B) |   "<<B[0]<<"   |       Temporary Register (TR) |   "<<TR[0]<<"   |"<<endl<<endl;
    cout<<"    Output Register (OPR) |   "<<OPR[0]<<"   |          Input Register (IPR) |   "<<IPR[0]<<"   |"<<endl<<endl;
    cout<<"     Program Counter (PC) |   "<<PC[0]<<"   |                        CARRY |   "<<CARRY<<"   |"<<endl<<endl;
    cout<<"   Interrupt Enable (IEN) |   "<<IEN<<"   |"<<endl;
}

void memoryloop()
{
    cout<<endl<<"\t\t\t\t\t\t\t\tMEMORY"<<endl;
    for(int j=0;j<15;j++)
    {
        cout<<"\t\t\t\t\t\t\t\t|____"<<RAM[j]<<" "<<DATARAM[j]<<" ____|"<<endl;
    }
    fill(m.begin(),m.end(),"");
    fill(o.begin(),o.end(),0);
}

void menu()
{
    string exit=" ", situation=" ";
    howmanyins();
    mainbackground();
    memorystuff();
    mainbackground();
    memoryloop();
    cout<<"Would you like to exit? Press E or if you wish to stay press N :)"<<endl;
    cin>>exit;
    if(exit=="E")
    {
        cout<<"Exiting..."<<endl; Sleep(2000);
    }
    else if(exit=="N")
    {
        cout<<"Would you like to store this data for the next session? Press Y if you do and N if you dont"<<endl;
        cin>>situation;
        if(situation=="Y")
        {
            cout<<"My name is walter white yo your data is safe lowk"<<endl;
            Sleep(3000); system("cls"); menu();
        }
        else
        {
            cout<<"Your data is now gone...:("<<endl;
            Sleep(2000); ultra_CLR(); system("cls"); menu();
        }
    }
}

int main()
{
    system("color DE");
    menu();
}
