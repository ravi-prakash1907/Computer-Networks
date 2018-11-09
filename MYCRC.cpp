\
 		        //Cyclic Redundancy Code

#include <conio.h>
#include <iostream.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define M_LEN 80         //Maximum length of message
#define G_LEN 5         //Degree of generator polynomial + 1

void frame(char*,char*,char*);
void transmit(char*,int);
void check(char*,char*);

void main()
{
 char *g;//="10011";  //CRC-12 Generator Polynomial
 char m[M_LEN+1];           //Message
 char t[M_LEN+G_LEN+1];     //Transmitted Frame
 int ch;

 do
 {
  clrscr();
  cout<<"\n                          MAIN  MENU";
  cout<<"\n                          ----------\n\n";
  cout<<"         1. Transmit Message through a NOISELESS Channel\n\n";
  cout<<"         2. Transmit Message through a NOISY Channel\n\n";
  cout<<"         3. Exit\n\n\n";
  cout<<"                   Enter your choice : ";
  cin>>ch;
  switch(ch)
  {
   case 1:
      clrscr();
      cout<<"             Transmit Message through a NOISELESS Channel\n";
      cout<<"             --------------------------------------------\n\n\n";
      cout<<"Enter the Message (Max length="<<M_LEN<<" bits) : ";
      gets(m);
      cout<< "\nEnter Generator Polynomial : ";
      gets(g);
      frame(g,m,t);
      cout<<"\nTransmitted Frame : "; puts(t);
      transmit(t,0);
      cout<<"\nFrame Recieved    : "; puts(t);
      check(g,t);
      break;

   case 2:
      clrscr();
      cout<<"               Transmit Message through a NOISY Channel\n";
      cout<<"               ----------------------------------------\n\n\n";
      cout<<"Enter the Message (Max length="<<M_LEN<<" bits) : ";
      gets(m);
      cout<< "\nEnter Generator Polynomial :";
      gets(g);
      frame(g,m,t);
      cout<<"\nTransmitted Frame : "; puts(t);
      transmit(t,1);
      cout<<"\nFrame Recieved    : "; puts(t);
      check(g,t);
      break;

   case 3:
      exit(0);

   default:
      cout<<"ERROR IN INPUT\n";
      cout<<"Press any key to continue...";
  }
  getch();
 }
 while(ch!=3);
}
/*__________________________________________________________________________*/
void frame(char *g,char *m,char *t)
{
 char rem[G_LEN+1];             //Remainder
 int i,j,k,t_len;
 int m_len=strlen(m);

 strcpy(t,m);
 for(i=m_len;i<m_len+G_LEN-1;i++)
    t[i] = '0';
 t[i] = '\0';
 t_len = strlen(t);

 if(t_len>=G_LEN)
  {
   for(i=0,j=0;i<G_LEN;i++,j++)
     rem[i] = t[j];
   rem[i] = '\0';
   while(j<=t_len)
    {
     for(i=0;i<G_LEN;i++)
	rem[i] = ((rem[i]-'0')^(g[i]-'0')) + '0';
     k = 0;
     while(rem[k]=='0' && k<G_LEN)
       k++;
     for(i=0;i<G_LEN-k;i++)
       rem[i] = rem[i+k];
     while(i<G_LEN && j<t_len)
       rem[i++] = t[j++];
     if(i<G_LEN)
	break;
    }
   rem[i] = '\0';
   i--;
   for(j=t_len-1;i>=0;i--,j--)
     t[j] = rem[i];
  }
}

/*__________________________________________________________________________*/
void transmit(char *t,int ch)
{
 if(ch==0)      //channel is noiseless
   return;      //frame is transmitted without any error
 else
  {             //channel is noisy
   int i,t_len;

   t_len = strlen(t);
   randomize();
   i = random(t_len);
	   //frame is transmitted with a single bit error in (i)th bit
   t[i] = (t[i]=='0')? '1' : '0';
   return;
  }
}

/*__________________________________________________________________________*/
void check(char *g,char *t)
{
 char rem[G_LEN+1];             //Remainder
 int i,j,k;
 int t_len = strlen(t);
 for(i=0,j=0;i<G_LEN;i++,j++)
   rem[i] = t[j];
 rem[i] = '\0';
 while(j<=t_len)
  {
   for(i=0;i<G_LEN;i++)
      rem[i] = ((rem[i]-'0')^(g[i]-'0')) + '0';
   k = 0;
   while(rem[k]=='0' && k<G_LEN)
     k++;
   for(i=0;i<G_LEN-k;i++)
     rem[i] = rem[i+k];
   while(i<G_LEN && j<t_len)
     rem[i++] = t[j++];
   if(i<G_LEN)
      break;
  }
 rem[i] = '\0';
 if(atoi(rem)==0)
   cout<<"\nMessage Recieved Correctly";
 else
   cout<<"\nERROR : Message NOT Recieved Correctly";
}