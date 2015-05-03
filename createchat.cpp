#include<iostream.h>
#include<conio.h>
#include<fstream.h>
#include<string.h>
#include<stdio.h>
#include<process.h>
#include<windows.h>

int rej=0,s=0,wf=-1;
char user[50];
char piic[100][50]={"\0"};
char prej[100][50]={"\0"};
char exited[100][50]={"\0"};
char mytext[1000];
fstream f;

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

void chat()
{
clrscr();
int ck=0,cl=0;
int rk=-1,rl=-1,j=-1;
int exk=-1;

b4:
while(!kbhit())
{
clrscr();
mytext[j+1]='\0';
strcpy(piic[0],user);

ck=0;
rk=-1;
exk=-1;

rej=0;
f.open(user,ios::in|ios::binary);
f.seekg(0,ios::end);
s=f.tellg()/sizeof(time2chat);
f.seekg(0,ios::beg);

for(int i=0;i<s;i++)
{
f.read((char *)&t2c,sizeof(t2c));
if(strcmp(sd.ct,t2c.ct)==0 && sd.ctno==t2c.ctno && strcmp(user,t2c.ib)==0)
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

wf=sd.oso-rej-exk-ck-1; //this is ok (checked)
cout<<"\nWaiting for reply from: "<<wf<<"\n\n";

f.seekg(0,ios::beg);

for(int i=0;i<s;i++)
{
f.read((char *)&t2c,sizeof(t2c));
if(strcmp(sd.ct,t2c.ct)==0 && sd.ctno==t2c.ctno && strcmp(user,t2c.ib)==0)
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
cout<<user<<": "<<mytext;

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
strcpy(t2c.ct,sd.ct);
t2c.ctno=sd.ctno;
strcpy(t2c.mem,user);
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
f.open("C:/Program Files/cc.txt",ios::app);
f.close();
f.open("C:/Program Files/cc.txt",ios::in);
f.seekg(0,ios::end);
s=f.tellg();
f.seekg(0,ios::beg);

f.read((char *)&sd,sizeof(sd));
f.close();
remove("C:/Program Files/cc.txt");

if(s==0)
{
cout<<"\a";
Sleep(2000);
cout<<"\a";
exit(0);
}

strcpy(user,sd.me);

while(1)
{
clrscr();
cout<<"Waiting for atleaast one member to accept...\n\n";

f.open(user,ios::in|ios::binary);
f.seekg(0,ios::end);
s=f.tellg()/sizeof(time2chat);
f.seekg(0,ios::beg);

rej=0;
for(int i=0;i<s;i++)
{
f.read((char *)&t2c,sizeof(t2c));
if(strcmp(sd.ct,t2c.ct)==0 && sd.ctno==t2c.ctno && strcmp(user,t2c.ib)==0)
{
if(t2c.yorn==-1)
{
rej++;
cout<<"("<<t2c.mem<<" has declined chat offer)\n";
if(rej==sd.oso)
{
f.close();
cout<<"\nThe selected member(s) rejected your offer\nEnding Chat Room...";
Sleep(3000);
goto closeit;
}
}
else if(t2c.yorn==1)
{
f.close();
chat();
}
}
}
f.close();
Sleep(500);
}
closeit:
}

