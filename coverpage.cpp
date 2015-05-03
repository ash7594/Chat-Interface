#include<iostream.h>
#include<conio.h>
#include<stdio.h>
#include<windows.h>
void main()
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
cprintf("COPYRIGHT@ ASH.INC");
gotoxy(61,24);
cprintf("------------------");

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


while(1)
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