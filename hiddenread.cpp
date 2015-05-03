#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<string.h>
#include<stdio.h>
#include<process.h>
#include<windows.h>
#include<ctype.h>

int nump=1,ks=0;
int rej=0,s=0,wf=-1;
char user[50];
char piic[100][50];
char prej[100][50];
char exited[100][50];
char mytext[1000];
fstream f;

class user_me
{
public:
char cme[50]; //chats me (file name for all chats)/same as username
char mme[53]; //msg me (file name for msgs)
char ime[54]; //info me (file name for basic info class user_me)
int noc; //no. of conference rooms
int nop; //no. of personalised chats
}ume;

class time2chat
{
public:
int yorn; //yes(1) or no(-1) or (0)when jst text
char ib[50]; //initiated by
char ct[10]; //chat type (group/personal)
int ctno; //chat type number
int nom; //no. of members
char mem[50]; //member involved
char text[1000]; //chat text
}t2c;

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


void chat()
{
clrscr();

int ck=0,cl=0;
int rk=-1,rl=-1,j=-1;
int exk=-1;
strcpy(user,msgc.msgs);
strcpy(piic[ck],user);

b4:
while(!kbhit())
{
mytext[j+1]='\0';
clrscr();
ck=0;
rk=-1;
exk=-1;

rej=0;
f.open(ume.cme,ios::in|ios::binary);
f.seekg(0,ios::end);
s=f.tellg()/sizeof(time2chat);
f.seekg(0,ios::beg);

for(int i=0;i<s;i++)
{
f.read((char *)&t2c,sizeof(t2c));
if(strcmp(msgc.mtype,t2c.ct)==0 && msgc.num==t2c.ctno && strcmp(msgc.msgs,t2c.ib)==0)
{
if(t2c.yorn==-1)
{
strcpy(prej[++rk],t2c.mem);
rej++;
}
else if(t2c.yorn==1)
strcpy(piic[++ck],t2c.mem);
if(t2c.yorn==0 && strcmp(t2c.text,"exit()")==0)
strcpy(exited[++exk],t2c.mem);
}
}

for(int i=0;i<=exk;i++)
for(int k=0;k<=ck;k++)
if(strcmp(exited[i],piic[k])==0)
{
strcpy(piic[k],piic[ck-i]);
break;
}

ck=ck-exk-1;

cout<<"ash.connect\nInitiated by: "<<user;
cout<<"\nUsers connected:";
for(int i=0;i<=ck;i++)
cout<<" "<<piic[i]<<",";

cout<<"\nUsers rejected:";
for(int i=0;i<=rk;i++)
cout<<" "<<prej[i]<<",";

cout<<"\nUsers exited:";
for(int i=0;i<=exk;i++)
cout<<" "<<exited[i]<<",";

wf=nump-1-rej-exk-ck-1; //this is ok (checked)
cout<<"\nWaiting for reply from: "<<wf<<"\n\n";

f.seekg(0,ios::beg);

for(int i=0;i<s;i++)
{
f.read((char *)&t2c,sizeof(t2c));
if(strcmp(msgc.mtype,t2c.ct)==0 && msgc.num==t2c.ctno && strcmp(user,t2c.ib)==0)
{
if(t2c.yorn==0)
{
if(strcmp(t2c.text,"exit()")==0)
cout<<"~ "<<t2c.mem<<" left the chat room ~"<<endl;
else
cout<<t2c.mem<<": "<<t2c.text<<endl;
}
}
}

f.close();
cout<<ume.cme<<": "<<mytext;
Sleep(500);
}

mytext[++j]=getch();
if(mytext[j]==8)
j-=2;
else if(mytext[j]==13)
{
mytext[j]='\0';
strcpy(t2c.text,mytext);
strcpy(t2c.ib,user);
strcpy(t2c.ct,msgc.mtype);
t2c.ctno=msgc.num;
strcpy(t2c.mem,ume.cme);
t2c.yorn=0;
t2c.nom=ck+1;

for(int i=0;i<=ck;i++)
{
f.open(piic[i],ios::app|ios::binary);
f.write((char *)&t2c,sizeof(t2c));
f.close();
}
j=-1;
if(strcmp(mytext,"exit()")==0)
exit(0);

goto b4;
}

mytext[j+1]='\0';

goto b4;

}


void main()
{
char ch1;
HWND window;
AllocConsole();
window=FindWindowA("ConsoleWindowClass",NULL);
ShowWindow(window,0);

f.open("C:/Program Files/me.txt",ios::app);
f.close();
f.open("C:/Program Files/me.txt",ios::in);
f.seekg(0,ios::end);
s=f.tellg();
f.seekg(0,ios::beg);

f.read((char *)&ume,sizeof(ume));
f.close();

remove("C:/Program Files/me.txt");

if(s==0)
{
cout<<"\a";
Sleep(2000);
cout<<"\a";
exit(0);
}

while(1)
{

f.open(ume.mme,ios::in|ios::binary);
f.seekg(0,ios::end);
s=f.tellg()/sizeof(msgcenter);
f.seekg(0,ios::beg);

for(int i=0;i<s;i++)
{
f.read((char *)&msgc,sizeof(msgc));
if(msgc.noro==1 && strcmp(msgc.mtype,"msg")!=0)
{
f.close();

f.open(ume.mme,ios::in|ios::out|ios::binary);
f.seekp(i*sizeof(msgcenter),ios::beg);
msgc.noro=0;
f.write((char *)&msgc,sizeof(msgc));
f.close();

f.open("C:/Program Files/me.txt",ios::out);
f.write((char *)&ume,sizeof(ume));
f.close();
ShellExecute(NULL,"open","hiddenread.exe",NULL,NULL,SW_SHOWNORMAL);

strcpy(piic[0],msgc.msgs);
for(int j=1;;j++)
{
if(isalnum(msgc.pac[j-1][0])!=0)
{
strcpy(piic[j],msgc.pac[j-1]);
nump++;
}
else
goto nx1;
}
nx1:

strcpy(t2c.ib,msgc.msgs);
strcpy(t2c.mem,ume.cme);
strcpy(t2c.ct,msgc.mtype);
t2c.ctno=msgc.num;

ShowWindow(window,1);
cout<<msgc.msgs<<" wants to start "<<msgc.mtype<<" chat with you...\n\n";

if(strcmp(msgc.mtype,"group")==0)
{
cout<<"The other ppl asked are:\n";
for(int j=0;;j++)
{
if(isalnum(msgc.pac[j][0])!=0)
{
if(strcmp(msgc.pac[j],ume.cme)!=0)
cout<<msgc.pac[j]<<", ";
}
else
goto nx2;
}
}
nx2:

cout<<"\n\nDo you accept chat offer (y/n): ";
bh:
cin>>ch1;
switch(ch1)
{
case 'y':
case 'Y':
t2c.yorn=1;
for(ks=0;ks<nump;ks++)
{
f.open(piic[ks],ios::app|ios::binary);
f.write((char *)&t2c,sizeof(t2c));
f.close();
}
chat();

case 'n':
case 'N':
t2c.yorn=-1;
for(ks=0;ks<nump;ks++)
{
f.open(piic[ks],ios::app|ios::binary);
f.write((char *)&t2c,sizeof(t2c));
f.close();
}
exit(0);
default: cout<<"\n\nINVALID. Enter 'y' or 'n': "; goto bh;
}
}
}

f.close();

f.open("online.dat",ios::in|ios::binary);
f.seekg(0,ios::end);
s=f.tellg()/sizeof(userpass);
f.seekg(0,ios::beg);

for(int i=0;i<s;i++)
{
f.read((char *)&u1,sizeof(u1));
if(strcmp(u1.usern,ume.cme)==0)
goto next;
}
f.close();
exit(0);
next:
f.close();

Sleep(500);
}

}
