#include<iostream.h>
#include<conio.h>
#include<stdlib.h>
#include<dos.h>
#include<stdio.h>
#include<string.h>
#include<process.h>

//function prototype

void MENU(char menulist[50][50],char mname[50],int mno,int n);

//menu as a doubly linked list queue

struct menu
{
    char data[50];
    int no;
    menu *prev,*next;
}*front,*rear;

//virtual car which acts as an obstacle

void virtualcar(char a[24][80],int x,int y)
{
    a[x%24][y]='|';
    a[x%24][y+1]='|';
    a[(x+1)%24][y]='|';
    a[(x+1)%24][y+1]='|';
}

//to check if the car hits the obstacle car
int virtualcheck(char a[24][80],int x,int y)
{
    if(a[x%24][y]=='.' || a[x%24][y+1]=='.' || a[(x+1)%24][y]=='.' || a[(x+1)%24][y+1]=='.')
    {
	clrscr();
	return(0);
    }
    else
    {
        return(1);
    }
}
void park(char a[24][80],int x, int y)
{
    a[x][y]='P';
}

//to check if the car is parked

int parkcheck(char a[24][80],int x, int y)
{
    if(a[x][y]=='.')
    {
	return(1);
    }
    else{
	return(0);
    }
}

//car down

void card(char a[24][80],int x,int y)
{

    a[x+1][y]='.';
    a[x+1][y+1]='.';
    a[x+2][y]='.';
    a[x+2][y+1]='.';
    a[x][y]='.';
    a[x][y+1]='.';
}

//car up

void caru(char a[24][80],int x,int y)
{

    a[x-1][y]='.';
    a[x-1][y+1]='.';
    a[x-2][y]='.';
    a[x-2][y+1]='.';
    a[x][y]='.';
    a[x][y+1]='.';
}

//car right
void carr(char a[24][80],int x,int y)
{
    a[x][y]='.';
    a[x][y+1]='.';
    a[x][y+2]='.';
    a[x+1][y]='.';
    a[x+1][y+1]='.';
    a[x+1][y+2]='.';
}

//car left

void carl(char a[24][80],int x,int y)
{
    a[x][y]='.';
    a[x][y-1]='.';
    a[x][y-2]='.';
    a[x+1][y]='.';
    a[x+1][y-1]='.';
    a[x+1][y-2]='.';
}

//easy level
void ez(char b[24][80])
{
    int i,j;
    for(i=0;i<24;i++)
    {
	for(j=0;j<80;j++)
	{
	    if(i==0 && j>=26)
		b[i][j]='*';
	    else if(i==8 && j>=52)
		b[i][j]='*';
	    else if(j==26 && i>=1 && i<=15)
		b[i][j]='*';
	    else if(j==52 && i>=8 && i<23)
		b[i][j]='*';
	    else if(i==23 && j>=0 && j<=52)
		b[i][j]='*';
	    else if(i==15 && j>=0 && j<26)
		b[i][j]='*';
	    else if(j==79 && i>0 && i<8)
		b[i][j]='*';
	    else if(i>=16 && i<24 && j==0)
		b[i][j]='*';
	    else
		b[i][j]=' ';
         }
    }
}

//medium level

void med(char a[24][80])
{
    int i,j;
    for(i=0;i<24;i++)
    {
        for(j=0;j<75;j++)
        {
             if(i==0)
            a[i][j]='*';
            else if(i>0 && i<7 && j==0)
                a[i][j]='*';
            else if(i>0 && i<7 && j==74)
                a[i][j]='*';
            else if(i==7 && j<=25)
                a[i][j]='*';
            else if(i==7 && j>=50)
                a[i][j]='*';
            else if(i==23 && j>=25 && j<=50)
                a[i][j]='*';
            else if(i>7   && j==25)
               a[i][j]='*';
            else if(i>7 && j==50)
                a[i][j]='*';
            //else if(i==29 && j>14 && j<34)
            //    cout<<a[i][j];
            else
                a[i][j]=' ';
           // cout<<a[i][j];
        }
    }
}

//difficult level
void diff( char a[24][80])
{
    int i,j;
    for(i=0;i<24;i++)
    {
	for(j=0;j<80;j++)
	{
	    if(i==0 || i==23)
		a[i][j]='*';
	    else if(j==79)
		a[i][j]='*';
	    else if(j==24 && i>=7 && i<16)
		a[i][j]='*';
	    else if(i==7 && j<=24)
		a[i][j]='*';
	    else if(i==15 && j<25)
		a[i][j]='*';
	    else if(j==0 && i>0 && i<7)
		a[i][j]='*';
	    else if(j==0 && i>15 && i<23)
		a[i][j]='*';
	    else if(i==7 && j>39 && j<=64)
		a[i][j]='*';
	    else if(i==15 && j>39 && j<=64)
		a[i][j]='*';
	    else if(j==39 && i>=7 && i<16)
		a[i][j]='*';
	    else if(j==64 && i>7 && i<16)
		a[i][j]='*';
	    else
		a[i][j]=' ';
	    //cout<<a[i][j];

	}
   }
}

//checking if car crashed at easy level
int chk(char b[24][80])
{

   int i,j,k=0;
    for(i=0;i<24;i++)
    {
	for(j=0;j<80;j++)
	{
	    if(i==0 && j>=26)
	    {
		if(b[i][j]=='.')
		{
		    k=1;
		    break;
		}
	    }
	    else if(i==8 && j>=52)
	    {
		if(b[i][j]=='.')
		{
		    k=1;
		    break;
		}
	    }

	    else if(j==26 && i>=1 && i<=15)
	    {
		if(b[i][j]=='.')
		{
		    k=1;
		    break;
		}
	    }

	    else if(j==52 && i>=8 && i<23)
	    {
		if(b[i][j]=='.')
		{
		    k=1;
		    break;
		}
	    }

	    else if(i==23 && j>=0 && j<=52)
	    {
		if(b[i][j]=='.')
		{
		    k=1;
		    break;
		}
	    }

	    else if(i==15 && j>=0 && j<26)
	    {
		if(b[i][j]=='.')
		{
		    k=1;
		    break;
		}
	    }

	    else if(j==79 && i>0 && i<8)
	    {
		if(b[i][j]=='.')
		{
		    k=1;
		    break;
		}
	    }

	    else if(i>=16 && i<24 && j==0)
	    {
		if(b[i][j]=='.')
		{
		    k=1;
		    break;
		}
	    }

	}
    }
    if(k==1)
    {
       return(0);
    }
    else
    {
        return(1);
    }
}

//checking if car crashed at medium level
int chkmed(char a[24][80])
{
     int i,j,k=0;
    for(i=0;i<24;i++)
    {
        for(j=0;j<75;j++)
        {
            if(i==0)
            {
		if(a[i][j]=='.')
		{
		    k=1;
		    break;
		}
	    }
	    else if(i>0 && i<7 && j==0)
		{
		if(a[i][j]=='.')
		{
		    k=1;
		    break;
		}
	    }
	    else if(i>0 && i<7 && j==74)
		{
		if(a[i][j]=='.')
		{
		    k=1;
		    break;
		}
	    }
	    else if(i==7 && j<=25)
		{
		if(a[i][j]=='.')
		{
		    k=1;
		    break;
		}
	    }
	    else if(i==7 && j>=50)
		{
		if(a[i][j]=='.')
		{
		    k=1;
		    break;
		}
	    }
	    else if(i==23 && j>=25 && j<=50)
		{
		if(a[i][j]=='.')
		{
		    k=1;
		    break;
		}
	    }
	    else if(i>7   && j==25)
	       {
		if(a[i][j]=='.')
		{
		    k=1;
		    break;
		}
	    }
	    else if(i>7 && j==50)
		{
		if(a[i][j]=='.')
		{
		    k=1;
		    break;
		}
	    }
	}
    }
    if(k==1)
    {
    return(0);
    }
    else
    {
	return(1);
    }
}

//checking if car crashes at difficult level
int chkdiff( char b[24][80])
{
    int i,j;
    int k=0;
    for(i=0;i<24;i++)
    {
	for(j=0;j<80;j++)
	{
	    if(i==0 || i==23)
		{
		    if(b[i][j]=='.')
		{
		    k=1;
		    break;
		}
		}
	    else if(j==79)
		{
		if(b[i][j]=='.')
		{
		    k=1;
		    break;
		}
	    }

	    else if(j==24 && i>=7 && i<16)
		{
		if(b[i][j]=='.')
		{
		    k=1;
		    break;
		}
	    }

	    else if(i==7 && j<=24)
		{
		if(b[i][j]=='.')
		{
		    k=1;
		    break;
		}
	    }

	    else if(i==15 && j<25)
		{
		if(b[i][j]=='.')
		{
		    k=1;
		    break;
		}
	    }

	    else if(j==0 && i>0 && i<7)
		{
		if(b[i][j]=='.')
		{
		    k=1;
		    break;
		}
	    }

	    else if(j==0 && i>15 && i<23)
		{
		if(b[i][j]=='.')
		{
		    k=1;
		    break;
		}
	    }

	    else if(i==7 && j>39 && j<=64)
		{
		if(b[i][j]=='.')
		{
		    k=1;
		    break;
		}
	    }

	    else if(i==15 && j>39 && j<=64)
		{
		if(b[i][j]=='.')
		{
		    k=1;
		    break;
		}
	    }

	    else if(j==39 && i>=7 && i<16)
		{
		if(b[i][j]=='.')
		{
		    k=1;
		    break;
		}
	    }

	    else if(j==64 && i>7 && i<16)
		{
		if(b[i][j]=='.')
		{
		    k=1;
		    break;
		}
	    }
         }
    }
    if(k==1)
    {
       return(0);
    }
    else
    {
        return(1);
    }
}

//printing the map
void p(char b[24][80])
{
    clrscr();
    int i,j;

    for(i=0;i<24;i++)
    {
	cout<<"\n";

	for(j=0;j<75;j++)
	{
	    cout<<b[i][j];
	}
    }
}
//using * for design purpose
//checking if the user passed the level or not
int result(char a[24][80],int g,int difficult)
{
    int x,y,check,tempx,tempy,c,ezgame,medgame,hardgame;

    if(g==1)
    {
	ezgame=difficult;
    check=0,tempx=0,tempy=25,c=0;
    ez(a);

    carr(a,20,3);
    park(a,24,80);
    p(a);
    x=20;
    y=3;
    while(ezgame==1)
    {
    c++;
    if(c%40000==0)
    {
	    clrscr();
	    tempx=(tempx+1)%24;
	    ez(a);
	    if(check==0)
	    {


		carr(a,x,y);


	    }
	    else
	    if(check==1)
	    {


		carl(a,x,y);


	    }
	    else
	    if(check==2)
	    {
		caru(a,x,y);
	    }
	    else
	    if(check==3)
	    {
		card(a,x,y);
	    }
	    park(a,4,72);
	    parkcheck(a,4,72);
	    p(a);
    }
    if(kbhit())
    {
	park(a,4,72);
	switch(getch())
	{
	case 'a':
	    y--;
	    ez(a);
	    carl(a,x,y);
	    p(a);
	    medgame=parkcheck(a,4,72);


	    ezgame=chk(a);

	    check=1;
	    break;
	case 'd':
	    y++;
	    ez(a);
	    carr(a,x,y);
	    p(a);
	    medgame=parkcheck(a,4,72);
	    ezgame=chk(a);
	    check=0;
	    break;
	case 'w':
	    x--;
	    ez(a);
	    caru(a,x,y);
	    p(a);
	    medgame=parkcheck(a,4,72);
	    ezgame=chk(a);
	    check=2;
	    break;
	case 's':
	    x++;
	    ez(a);
	    card(a,x,y);
	    p(a);
	    medgame=parkcheck(a,4,72);
	    ezgame=chk(a);
	    check=3;
	    break;
	}
    }
    if(medgame==1)
    {
	ezgame=0;
    }
    }
    return(medgame);
    }
    else if(g==2)
    {
	medgame=difficult;
    check=2;
    tempx=0;
    tempy=40;
    c=0;
    med(a);
    carr(a,20,30);
    park(a,4,72);
    p(a);
    x=20;
    y=30;
    while(medgame)
    {
    park(a,4,72);
    c++;
    virtualcar(a,tempx,tempy);

    if(c%40000==0)
    {
	    clrscr();
	    tempx=(tempx+1)%24;
	    med(a);
	    if(check==0)
	    {
		 virtualcar(a,tempx,tempy);
		carr(a,x,y);
	               medgame=virtualcheck(a,tempx,tempy);
	    }
	    else
	    if(check==1)
	    {
		 virtualcar(a,tempx,tempy);
		carl(a,x,y);
	              medgame=virtualcheck(a,tempx,tempy);
	    }
	    else
	    if(check==2)
	    {
		 virtualcar(a,tempx,tempy);
                     	caru(a,x,y);
	               medgame=virtualcheck(a,tempx,tempy);
	    }
	    else
	    if(check==3)
	    {
		 virtualcar(a,tempx,tempy);
		card(a,x,y);
	    medgame=virtualcheck(a,tempx,tempy);
	    }
	    park(a,4,72);
	    hardgame=parkcheck(a,4,72);
	    p(a);
    }
    medgame=virtualcheck(a,tempx,tempy);
    if(kbhit())
    {
	park(a,4,72);
	switch(getch())
	{
	case 'a':
	    y--;
	    med(a);
	    carl(a,x,y);
	    p(a);
	    hardgame=parkcheck(a,4,72);
	    medgame=virtualcheck(a,tempx,tempy);
	    medgame=chkmed(a);
	    check=1;
	    break;
	case 'd':
	    y++;
	    med(a);
	    carr(a,x,y);
	    p(a);
	    hardgame=parkcheck(a,4,72);
	    medgame=virtualcheck(a,tempx,tempy);
	    medgame=chkmed(a);
	    check=0;
	    break;
	case 'w':
	    x--;
	    med(a);
	    caru(a,x,y);
	    p(a);
	    hardgame=parkcheck(a,4,72);
	    medgame=virtualcheck(a,tempx,tempy);
	    medgame=chkmed(a);
	    check=2;
	    break;
	case 's':
	    x++;
	    med(a);
	    card(a,x,y);
	    p(a);
	    hardgame=parkcheck(a,4,72);
	    medgame=virtualcheck(a,tempx,tempy);
	    medgame=chkmed(a);
	    check=3;
	    break;
	}
    }
    if(hardgame==1)
    {
	medgame=0;
    }
    }
    return(hardgame);
    }
    else if(g==3)
    {
    hardgame=difficult;
    int temp=0;
    check=0;
    tempx=0;
    int tempx2=0;
    tempy=28;
    int tempy2=32;
    c=0;
    int c2=20000;
    diff(a);
    carr(a,20,3);
    park(a,4,4);
    p(a);
    x=20;
    y=3;
    while(hardgame)
    {
    c++;
    c2++;
    virtualcar(a,tempx,tempy);
    virtualcar(a,tempx2,tempy2);
    if(c%40000==0)
    {
	    clrscr();
	    tempx=(tempx+1)%24;
	    diff(a);
	    if(check==0)
	    {
		 virtualcar(a,tempx,tempy);
		 virtualcar(a,tempx2,tempy2);
		carr(a,x,y);
	    hardgame=virtualcheck(a,tempx,tempy);
	    }
	    else
	    if(check==1)
	    {
		 virtualcar(a,tempx,tempy);
		 virtualcar(a,tempx2,tempy2);
		carl(a,x,y);
	    hardgame=virtualcheck(a,tempx,tempy);
	    }
	    else
	    if(check==2)
	    {
		 virtualcar(a,tempx,tempy);
		 virtualcar(a,tempx2,tempy2);
		caru(a,x,y);
	    hardgame=virtualcheck(a,tempx,tempy);
	    }
	    else
	    if(check==3)
	    {
		 virtualcar(a,tempx,tempy);
		 virtualcar(a,tempx2,tempy2);
		card(a,x,y);
	    hardgame=virtualcheck(a,tempx,tempy);
	    }
	    park(a,4,4);
	    temp=parkcheck(a,4,4);
	    p(a);
    }
    if(c2%20000==0)
    {
	    clrscr();
	    tempx2=(tempx2+1)%24;
	    diff(a);
	    if(check==0)
	    {
	 virtualcar(a,tempx,tempy);
		 virtualcar(a,tempx2,tempy2);
		carr(a,x,y);
	    hardgame=virtualcheck(a,tempx2,tempy2);
	    }
	    else
	    if(check==1)
	    {
	  virtualcar(a,tempx,tempy);
		 virtualcar(a,tempx2,tempy2);
		carl(a,x,y);
	    hardgame=virtualcheck(a,tempx2,tempy2);
	    }
	    else
	    if(check==2)
	    {
		 virtualcar(a,tempx2,tempy2);
		 virtualcar(a,tempx,tempy);
		caru(a,x,y);
	    hardgame=virtualcheck(a,tempx2,tempy2);
	    }
	    else
	    if(check==3)
	    {

		 virtualcar(a,tempx2,tempy2);
		 virtualcar(a,tempx,tempy);
		card(a,x,y);
	    hardgame=virtualcheck(a,tempx2,tempy2);
	    }
	    park(a,4,4);
	    temp=parkcheck(a,4,4);
	    p(a);
    }
    hardgame=virtualcheck(a,tempx,tempy);
    if(hardgame==1)
    {
    hardgame=virtualcheck(a,tempx2,tempy2);
    }
    if(kbhit())
    {
	park(a,4,4);
	switch(getch())
	{
	case 'a':
	    y--;
	    diff(a);
	    carl(a,x,y);
	    p(a);
	    temp=parkcheck(a,4,4);
	    hardgame=virtualcheck(a,tempx,tempy);
	    hardgame=virtualcheck(a,tempx2,tempy2);
	    hardgame=chkdiff(a);
	    check=1;
	    break;
	case 'd':
	    y++;
	    diff(a);
	    carr(a,x,y);
	    p(a);
	    temp=parkcheck(a,4,4);
	    hardgame=virtualcheck(a,tempx,tempy);
	    hardgame=virtualcheck(a,tempx2,tempy2);
	    hardgame=chkdiff(a);
	    check=0;
	    break;
	case 'w':
	    x--;
	    diff(a);
	    caru(a,x,y);
	    p(a);
	    temp=parkcheck(a,4,4);
	    hardgame=virtualcheck(a,tempx,tempy);
	    hardgame=virtualcheck(a,tempx2,tempy2);
	    hardgame=chkdiff(a);
	    check=2;
	    break;
	case 's':
	    x++;
	    diff(a);
	    card(a,x,y);
	    p(a);
	    temp=parkcheck(a,4,4);
	    hardgame=virtualcheck(a,tempx,tempy);
	    hardgame=virtualcheck(a,tempx2,tempy2);
	    hardgame=chkdiff(a);

	    check=3;
	    break;
	}
    }
    if(temp==1)
    {
	hardgame=0;
    }
    }
    return(temp);
}
}

//main game
void newgame(int l1,int l2,int l3)
{
    char a[24][80],menu1[50][50]={"PLAY AGAIN","MAIN MENU"};
    int temp=0,k=0;
    if(l3==0)
    {
	if(l2==0)
	{
	    if(l1==0)
	    {
		k=result(a,1,1);
		if(k!=1)
		{
		    MENU(menu1,"CRASHED...!!",2,2);
		}
		else
		{
		    newgame(1,0,0);
		    l1=1;
		}
	    }
	    else
	    {
	    k=result(a,2,1);
	    if(k==0)
	    {
		MENU(menu1,"CRASHED...!!",3,2);
	    }
	    else
	    {
		l2=1;
		newgame(1,1,0);
	    }
	    }
	}
	else
	{
	    k=result(a,3,1);
	    if(k==0)
	    {
	    MENU(menu1,"CRASHED...!!",4,2);
	    }
	    else
	    {
	    l3=1;
	    clrscr();
	    textcolor(6);
	    cout<<"\n\n\n\n\t\t";
	    cprintf("*************************************");
	    cout<<"\n\t\t";
	    cprintf("*                                   *");
	    cout<<"\n\t\t";
	    cprintf("*           YOU WIN                 *");
	    cout<<"\n\t\t";
	    cprintf("*                                   *");
	    cout<<"\n\t\t";
	    cprintf("*************************************");
	    delay(2000);
	    }
	}

    }
}

void instruction()
{
	    clrscr();
	    textcolor(6);
	    cout<<"\n\n\n\n\t\t";
	    cprintf("*************************************");
	    cout<<"\n\t\t";
	    cprintf("*           INSTRUCTIONS            *");
	    cout<<"\n\t\t";
	    cprintf("*************************************");
	    textcolor(7);
	    cout<<"\n\t\t";cprintf("'w' - Move up");
	    cout<<"\n\t\t";cprintf("'s' - Move down");
	    cout<<"\n\t\t";cprintf("'a' - Move left");
	    cout<<"\n\t\t";cprintf("'d' - Move right");
	    cout<<"\n\t\t";cprintf(":::: - Represents the Car");
	    getch();
}

void credits()
{
	    clrscr();
	    textcolor(6);
	    cout<<"\n\n\n\n\t\t";
	    cprintf("***********************************************");
	    cout<<"\n\t\t";
	    cprintf("*                   CREDITS                   *");
	    cout<<"\n\t\t";
	    cprintf("***********************************************");
	    textcolor(10);
	    cout<<"\n\t\t";cprintf("TECHNICAL TEAM - Gaurav Jha & Pranav Agarwal");
	    cout<<"\n\t\t";cprintf("TECHNICAL ASSISTANCE - Yash Kakatkar");
	    cout<<"\n\t\t";cprintf("DESIGN HEAD - Yash Kakatkar");
	    cout<<"\n\t\t";cprintf("DESIGN ASSISTANCE - Pranav Agarwal & Gaurav Jha");
	    textcolor(14);
	    cout<<"\n\n\t\t";cprintf("           DEVELOPMENT TEAM");
	    cout<<"\n\t\t";cprintf("           Pranav Agarwal");
	    cout<<"\n\t\t";cprintf("           Gaurav Jha");
	    cout<<"\n\t\t";cprintf("           Yash Kakatkar");
	    getch();
}

//MENU
void MENU(char menulist[50][50],char mname[20],int mno,int n)
{
    struct menu *temp,*head,*t,*point;
    char ch;
    char menu2[50][50]={"NEW GAME","INSTRUCTIONS","CREDITS","EXIT"};
    front=rear=NULL;
    int i;
    for(i=0;i<n;i++)
    {
	temp=new menu;
	strcpy(temp->data,menulist[i]);
	temp->no=i;
	temp->prev=NULL;
	temp->next=NULL;
	if(front==NULL)
	{
	    front=rear=temp;
	    front->next=rear;
	    front->prev=rear;
	    head=front;
	}
	else
	{
	    rear->next=temp;
	    temp->prev=rear;
	    rear=temp;
	}
	rear->next=front;
	front->prev=rear;
	//cout<<rear->no;
	cout<<rear->data;
	cout<<rear->next->data;
	cout<<rear->prev->data;
    }
    point=head;
    while(1)
    {
	clrscr();
	textcolor(14);
	cprintf("============================================================");
	textcolor(10);
	cout<<endl<<"\t\t\t";
	cprintf(mname);
	cout<<endl;
	textcolor(14);
	cprintf("============================================================");
	cout<<endl;
	t=head;
	do
	{
	    if(t->no==point->no)
	    {
		textcolor(11);
		cout<<"\t\t\t";
		cprintf(t->data);
		cout<<endl;
	    }
	    else
	    {
		textcolor(8);
		cout<<"\t\t\t";
		cprintf(t->data);
		cout<<endl;
	    }
	    t=t->next;
	}while(t!=front);
	textcolor(14);
	cprintf("============================================================");
	ch=getch();
	if(ch==0)
	{       ch=getch();
		if(ch==72)
			point=point->prev;
		else if(ch==80)
			point=point->next;
	}
	if(ch==13)
	{
	    if(mno==1)
	    {
		switch(point->no)
		{
		    case 0 :newgame(0,0,0);
		    break;
		    case 1 :instruction();
		    break;
		    case 2 :credits();
		    break;
		    case 3 :exit(0);
		}
	    }
	    else if(mno==2)
	    {
		switch(point->no)
		{
		    case 0 :newgame(0,0,0);
		    break;
		    case 1 :MENU(menu2,"MAIN MENU",1,4);
		    break;
		}
	    }
	    else if(mno==3)
	    {
		switch(point->no)
		{
		    case 0 :newgame(1,0,0);
		    break;
		    case 1 :MENU(menu2,"MAIN MENU",1,4);
		    break;
		}
	    }
	    else if(mno==4)
	    {
		switch(point->no)
		{
		    case 0 :newgame(1,1,0);
		    break;
		    case 1 :MENU(menu2,"MAIN MENU",1,4);
		    break;
	}
	}
	}
	delay(150);
    }
}
int main()
{
    int flag=0;
    char a[24][80];
    char menu1[50][50]={"NEW GAME","INSTRUCTIONS","CREDITS","EXIT"};
    MENU(menu1,"MAIN MENU",1,4);
    return(0);
}
