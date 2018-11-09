/*	DVR	*/

#include<iostream.h>
#include<conio.h>

char all[30], nbh[10], init, via[30];
int i, j, r, netNbh, delay[10], vtNbh[10][30], ans[10][30], fRoute[30];

void getMap()
{
 clrscr();
  cout<<"\nEnter the no of router: ";
  cin>>r;

  for(i=0;i<r;i++)
    all[i] = 65+i;
  all[i] = '\0';

  cout<<"All routers are named b/w \'A\' to \'"<<char(64+r)<<"\' !";

  cout<<"\n\nEnter the name of initial router: ";
  cin>>init;
  cout<<"\nEnter the no of neighbouring router of \'"<<init<<"\': ";
  cin>>netNbh;

  cout<<"Enter the names of neighbouring router: ";
  for(i=0;i<netNbh;i++)
    cin>>nbh[i];
  nbh[i] = '\0';
}
void getTable()
{
 clrscr();
   for(i=0;i<netNbh;i++)
   {
     cout<<"\nEnter the delay time of \'"<<nbh[i]<<"\' from \'"<<init<<"\': ";
     cin>>delay[i];
   }

 for(j=0;j<netNbh;j++)
 {
  clrscr();
   cout<<"\nEnter the vector table of \'"<<nbh[j]<<"\',:\n\n";

   for(i=0;i<r;i++)
   {
      cout<<"From \'"<<all[i]<<"\': ";
      cin>>vtNbh[j][i];
   }
 }
}

void result()
{
 clrscr();

  for(i=0;i<netNbh;i++)
  {
    for(j=0;j<r;j++)
    {
      ans[i][j] = delay[i]+vtNbh[i][j];
    }
  }
}

int small(int x[], int size)
{
  int temp = x[0];
  for(int c=0; c<size; c++)
    if(temp>x[c])
      temp = x[c];

  return temp;
}

void best()
{
  int a[10];

  for(j=0;j<r;j++)
  {
    for(i=0;i<netNbh;i++)
      a[i] = ans[i][j];

    fRoute[j] = small(a, netNbh);

    for(i=0;i<netNbh;i++)
      if(a[i] == fRoute[j])
      {
	via[j] = nbh[i];
	break;
      }
  }
}

//		MAIN FUNCTION		//

void main()
{
    getMap();
    getTable();
    result();

  cout<<" Result() is well..";
  getch();
    best();
  for(i=0;i<netNbh;i++)
  {
   clrscr();
    cout<<"\nD.V.R. Table of \'"<<init<<"\', via \'"<<nbh[i]<<"\', to:\n";
    for(j=0;j<r;j++)
    {
      cout<<"\n\'"<<all[j]<<"\': "<<ans[i][j];
    }
    getch();
  }

   clrscr();
    cout<<"\nD.V.R. Table best route from \'"<<init<<"\', to:\n";
    for(j=0;j<r;j++)
    {
      cout<<"\n\'"<<all[j]<<"\':\t"<<fRoute[j];
      if(fRoute[j]/10 == 0)
	cout<<" ";
      cout<<"  (via \'"<<via[j]<<"\')";
    }

  getch();
}