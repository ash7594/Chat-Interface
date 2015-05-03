#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<string.h>
#include<stdio.h>
#include<process.h>
#include<windows.h>

void login();

char extra[50];
char user[50];
char pe[100][50];
int io=0;
int cr=0;

class reviewc  //review chats
{
public:
char ib[50];
int ctno;
}revc;

class time2chat
{
public:
int yorn; //yes(1) or no(-1) or (0)when jst text
char ib[50]; //initiated by
char ct[10]; //chat type (group/personal)
int ctno; //chat type number
int nom; //no. of members
char mem[50]; //members involved
char text[1000]; //chat text
}t2c;

class senddata
{
public:
char me[50];
char ct[10]; // (group/personal)
int oso; //offers sent out
int ctno; // corresponding no.
}sd;

class user_me
{
public:
char cme[50]; //chats me (file name for all chats)/same as username
char mme[53]; //msg me (file name for msgs)
char ime[54]; //info me (file name for basic info class user_me)
int noc; //no. of conference rooms
int nop; //no. of personalised chats
}ume;

class msgcenter
{
public:
int noro; //new(1) or old(0)
int num; //group/personal chat record number of me
char mtype[10]; //msg type (group/msg/personal)
char pac[100][50]; //people also chatting
char msgs[50]; //msg sender
char msgr[50]; //msg receiver
char msg[2000]; //message
}msgc;


class userpass
{
public:
char usern[50];
char passw[50];
}u1,u2;



void welcome()
{
int a=11;

textcolor(14);
gotoxy(37,13);
cprintf("ASH.LINK");  //37-44

textcolor(15);
gotoxy(5,2);
cprintf("ASHUTOSH NATH");
gotoxy(5,3);
cprintf("-------------");

gotoxy(8,4);
cprintf("AGARWAL");
gotoxy(8,5);
cprintf("-------");

gotoxy(7,23);
cprintf("NIT TRICHY");
gotoxy(7,24);
cprintf("----------");

gotoxy(62,2);
cprintf("COMPUTER SCIENCE");
gotoxy(62,3);
cprintf("----------------");

gotoxy(66,4);
cprintf("AND ENGG");
gotoxy(66,5);
cprintf("--------");

gotoxy(61,23);
cprintf("(C)COPYRIGHT 2013");
gotoxy(61,24);
cprintf("-----------------");

for(int i=2;i<=11;i+=2)
{
for(int j=36-i;j<=45+i;j++)
{
textcolor(7);
gotoxy(j,12-i);
cprintf("*");
gotoxy(j,14+i);
cprintf("*");
}
}


for(int i=1;i<=12;i++)
{
for(int j=13-i;j<=13+i;j++)
{
textcolor(12);
gotoxy(35-i,j);
cprintf("*");
gotoxy(46+i,j);
cprintf("*");
}
}


while(!kbhit())
{

gotoxy(1,1);


for(int i=2;i<=12;i++)
{
for(int j=13-i;j<=13+i;j++)
{
textcolor(0);
gotoxy(35-i,j);
cprintf("*");
gotoxy(46+i,j);
cprintf("*");
}

for(int j=13-i+1;j<=13+i-1;j++)
{
textcolor(12);
gotoxy(35-i+1,j);
cprintf("*");
gotoxy(46+i-1,j);
cprintf("*");
}

Sleep(40);
}

for(int j=1;j<=25;j++)
{
textcolor(12);
gotoxy(23,j);
cprintf("*");
gotoxy(58,j);
cprintf("*");
}

}
getch();
}



void availonline()
{
fstream f;
int s,j=0,k=-1;
char ch1;
pe[0][0]='\0';

b4:
while(!kbhit())
{
pe[j][k+1]='\0';
clrscr();
cout<<"The ppl currently online are:\n\n";
f.open("online.dat",ios::in|ios::binary);
f.seekg(0,ios::end);
s=f.tellg()/sizeof(userpass);
f.seekg(0,ios::beg);
for(int i=0;i<s;i++)
{
f.read((char *)&u1,sizeof(u1));
if(io==1 && strcmp(user,u1.usern)==0)
continue;

cout<<u1.usern<<endl;
}
f.close();

if(cr==3)
cout<<"Enter a person: "<<pe[j];

Sleep(100);
}

if(cr==3)
{
pe[j][++k]=getch();
if(pe[j][k]==8)
k=k-2;
else if(pe[j][k]==13)
{
pe[j][k]='\0';
cout<<"\n\nEnter more ppl? (y/n): ";
b5:
cin>>ch1;
switch(ch1)
{
case 'y':
case 'Y': j++;k=-1;goto b4;
case 'n':
case 'N': goto makelist;
default: cout<<"\n\nINVALID. Enter 'y' or 'n': "; goto b5;
}
}
pe[j][k+1]='\0';
goto b4;

makelist:

f.open(ume.ime,ios::in|ios::binary);
f.read((char *)&ume,sizeof(ume));
ume.noc+=1;
f.close();
f.open(ume.ime,ios::out|ios::binary);
f.write((char *)&ume,sizeof(ume));
f.close();

strcpy(msgc.mtype,"group");
strcpy(msgc.msgs,ume.cme);
msgc.noro=1;
msgc.num=ume.noc;
sd.ctno=ume.noc;

for(int i=0;i<=j;i++)
strcpy(msgc.pac[i],pe[i]);

for(int i=0;i<=j;i++)
{
strcpy(msgc.msgr,pe[i]);
strcpy(extra,pe[i]);
strcat(extra,"msg");
f.open(extra,ios::app|ios::binary);
f.write((char *)&msgc,sizeof(msgc));
f.close();
}

f.open("C:/Program Files/cc.txt",ios::out);
strcpy(sd.me,ume.cme);
strcpy(sd.ct,"group");
sd.oso=j+1;
f.write((char *)&sd,sizeof(sd));
f.close();

ShellExecute(NULL,"open","createchat.exe",NULL,NULL,SW_SHOWNORMAL);
cr=0;
login();
}
getch();
}

void loginstat()
{
fstream fup,f;
int ch1;char ch2;
int ups,s,s1;
start:
clrscr();
cout<<"1. Login";
cout<<"\n2. Create account";
cout<<"\n3. Show accounts";
cout<<"\n4. Currently online";
cout<<"\n5. Exit";
cout<<"\n\nEnter choice: ";
cin>>ch1;

fup.open("userpass.dat",ios::app|ios::binary);
fup.close();
fup.open("online.dat",ios::app|ios::binary);
fup.close();

if(ch1==2)
{
clrscr();
cout<<"Enter username: ";
b1:
gets(u1.usern);
fup.open("userpass.dat",ios::in|ios::binary);

fup.seekg(0,ios::end);
s=fup.tellg()/sizeof(userpass);
fup.seekg(0,ios::beg);

for(int i=0;i<s;i++)
{
fup.read((char *)&u2,sizeof(u2));
if(strcmpi(u1.usern,u2.usern)==0)
{
cout<<"\nusername exists. enter new username: ";
fup.close();
goto b1;
}
}
fup.close();

cout<<"\nEnter password: ";
gets(u1.passw);
fup.open("userpass.dat",ios::app|ios::binary);
fup.write((char *)&u1,sizeof(u1));
fup.close();

cout<<"\nAccount created";
getch();
goto start;
}

else if(ch1==1)
{
clrscr();
b2:
cout<<"Enter username: ";
gets(u1.usern);

cout<<"\nEnter password: ";
gets(u1.passw);
fup.open("userpass.dat",ios::in|ios::binary);

fup.seekg(0,ios::end);
s1=fup.tellg()/sizeof(userpass);
fup.seekg(0,ios::beg);

for(int i=0;i<s1;i++)
{
fup.read((char *)&u2,sizeof(u2));
if(strcmp(u1.usern,u2.usern)==0 && strcmp(u1.passw,u2.passw)==0)
{
fup.close();
strcpy(user,u1.usern);
io=1;
cout<<"\nlogged in.\n\n";
f.open("online.dat",ios::app|ios::binary);
f.write((char *)&u1,sizeof(u1));
f.close();

strcpy(ume.cme,u1.usern);
strcat(ume.cme,"msg");
strcpy(ume.mme,ume.cme);
strcpy(ume.cme,u1.usern);
strcat(ume.cme,"info");
strcpy(ume.ime,ume.cme);
strcpy(ume.cme,u1.usern);

f.open(ume.cme,ios::app|ios::binary);
f.close();
f.open(ume.mme,ios::app|ios::binary);
f.close();
f.open(ume.ime,ios::app|ios::binary);
f.close();

f.open(ume.ime,ios::in|ios::binary);
f.seekg(0,ios::end);
s=f.tellg()/sizeof(user_me);
f.seekg(0,ios::beg);
if(s!=0)
f.read((char *)&ume,sizeof(user_me));
f.close();

if(s==0)
{
f.open(ume.ime,ios::out|ios::binary);
ume.noc=ume.nop=0;
f.write((char *)&ume,sizeof(ume));
f.close();
}

getch();

f.open("C:/Program Files/me.txt",ios::out);
f.write((char *)&ume,sizeof(ume));
f.close();

ShellExecute(NULL,"open","hiddenread.exe",NULL,NULL,SW_SHOWNORMAL);

login();
goto start;
}
}
fup.close();

cout<<"\n\nInvalid. Try again? (y/n): ";
b3:
cin>>ch2;
switch(ch2)
{
case 'y':
case 'Y': goto b2;
case 'n':
case 'N': goto start;
default: cout<<"\n\nINVALID. Enter 'y' or 'n': "; goto b3;
}
}

else if(ch1==3)
{
while(!kbhit())
{
clrscr();
fup.open("userpass.dat",ios::in|ios::binary);
fup.seekg(0,ios::end);
ups=fup.tellg()/sizeof(userpass);
if(ups==0)
cout<<"\n\nNO ACCOUNTS";
else
{
fup.seekg(0,ios::beg);
for(int i=0;i<ups;i++)
{
fup.read((char *)&u1,sizeof(u1));
cout<<u1.usern<<"\n\n";
}
}
fup.close();
Sleep(500);
}
getch();
goto start;
}

else if(ch1==4)
{
availonline();
goto start;
}

else if(ch1==5)
exit(0);

}


void login()
{
int ch1,s,chec=0;
int mno,noo=0;
fstream f,f1;

start1:
clrscr();

cout<<"ASH.CONNECT";
cout<<"\n\n1. Available ppl onlyn.";
cout<<"\n2. Create chat room.";
cout<<"\n3. Messages.";
cout<<"\n4. Send Message.";
cout<<"\n5. logout.";
cout<<"\n\nEnter choice: ";
cin>>ch1;

if(ch1==1)
{
availonline();
goto start1;
}


else if(ch1==2)
{
cr=3;
availonline();
}


else if(ch1==3)
{
chec=0;
noo=0;
clrscr();
cout<<"MESSAGES\n\n";

f.open(ume.mme,ios::in|ios::binary);
f.seekg(0,ios::end);
s=f.tellg()/sizeof(msgcenter);
f.seekg(0,ios::beg);

if(s==0)
{
f.close();
cout<<"No messages. Reverting to main menu...";
Sleep(2000);
goto start1;
}

for(int i=1;i<=s;i++)
{
f.read((char *)&msgc,sizeof(msgc));
if(strcmp(msgc.mtype,"msg")==0)
{
chec++;
cout<<chec<<". "<<msgc.msgs;
if(msgc.noro==1)
cout<<" (NEW)";
cout<<endl;
}
}
f.close();

if(chec==0)
{
cout<<"No messages. Reverting to main menu...";
Sleep(2000);
goto start1;
}

cout<<"\nEnter Message number to view: ";
cin>>mno;

if(mno==0)
goto start1;

chec=0;
clrscr();
f.open(ume.mme,ios::in|ios::binary);

for(int i=1;i<=s;i++)
{
f.read((char *)&msgc,sizeof(msgc));
if(strcmp(msgc.mtype,"msg")==0)
chec++;
if(chec==mno)
{
cout<<"Message sender: "<<msgc.msgs<<"\n\n";
cout<<msgc.msg;
if(msgc.noro==1)
noo=1;
f.close();
goto e1;
}
}
e1:

chec=0;
if(noo=1)
{
noo=0;
f.open(ume.mme,ios::in|ios::out|ios::binary);
for(int i=1;i<=s;i++)
{
f.read((char *)&msgc,sizeof(msgc));
if(strcmp(msgc.mtype,"msg")==0)
chec++;
if(chec==mno)
{
f.seekp((-1)*sizeof(msgcenter),ios::cur);
msgc.noro=0;
f.write((char *)&msgc,sizeof(msgc));
f.close();
goto e2;
}
}
e2:
}

getch();
goto start1;
}


else if(ch1==4)
{
clrscr();
cout<<"Enter receiver ID: ";
cin>>msgc.msgr;
cout<<"\n\nEnter the message: ";
gets(msgc.msg);
cout<<"\n\nMESSAGE SENT";
msgc.noro=1;
strcpy(msgc.mtype,"msg");
strcpy(msgc.msgs,ume.cme);
strcpy(extra,msgc.msgr);
strcat(extra,"msg");
f.open(extra,ios::app|ios::binary);
f.write((char *)&msgc,sizeof(msgc));
f.close();

getch();
goto start1;
}


else if(ch1==5)
{
f.open("online.dat",ios::in|ios::binary);
f1.open("tempr.dat",ios::out|ios::binary);

f.seekg(0,ios::end);
s=f.tellg()/sizeof(userpass);
f.seekg(0,ios::beg);

for(int i=0;i<s;i++)
{
f.read((char *)&u1,sizeof(u1));
if(strcmp(user,u1.usern)!=0)
f1.write((char *)&u1,sizeof(u1));
}
f.close();
f1.close();
remove("online.dat");
rename("tempr.dat","online.dat");
io=0;
loginstat();
}

}


void main()
{
welcome();
loginstat();
}
