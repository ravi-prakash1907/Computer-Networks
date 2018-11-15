/*		Stop & Wait		*/

#include<iostream.h>
#include<string.h>
#include<stdio.h>
#include<conio.h>
#include<dos.h>

#define TIMEOUT 5
#define MAX_SEQ 1
#define maxPackets 20

#define inc(c) if(c<MAX_SEQ) c++; else c=0;

class packet
{
  public:
    char data[20];
};

class frame
{
  public:
    int kind;
    int seq;
    int ack;
    packet info;
    int err;

};

frame DATA;
typedef enum{frame_arrival,err,timeout,no_event} event_type;

//typedef enum{ frameRecieved, blanck } event_type;

void frmNetworkLayer(packet *);
void toNetworkLayer(packet *);
void toPhysicalLayer(frame *);
void frmPhysicalLayer(frame *);
void wait_for_event_sender(event_type *);
void wait_for_event_reciever(event_type *);
void reciever();
void sender();

int i=1, totalPackets;

char turn, mainInfo[20];
int connectionStatus=1;

//--------------------main--------------------//

void main()
{
 clrscr();

   cout<<"\n\t\t\t"
       <<"IMPLEMENTATION OF STOP & WAIT ARQ"
       <<"\n\t\t     "
       <<"_______________________________________";

   cout<<"\n\n  Enter total no. of packets to be transmitted (max 20): ";
   cin>>totalPackets;
    totalPackets = (totalPackets>maxPackets) ? maxPackets:totalPackets;

 clrscr();

 randomize();
   for( ; connectionStatus; )
   {
     sender();
     delay(400);
     reciever();
   }

   cout<<"\n\nTRANSMISSION COMPLETE";

 getch();
}

///////////////////////////////////////////////

void sender()
{
 static int frame_to_send=0;
 static frame *s;               //  static frame s;
 packet buffer;
 event_type event;
 static int flag=0;
 
 if(flag==0)
 {
  frmNetworkLayer(&buffer);
  s->info = buffer;
  s->seq = frame_to_send;
  cout<<"  SENDER:  Info = "<<s->info.data<<"  Seq No = "<<s->seq;
  turn = 'r';
  toPhysicalLayer(s);
  flag = 1;
 }
 
wait_for_event_sender(&event);
 
 wait_for_event_sender(&event);
 if(turn=='s')
  {
   if(event==frameRecieved)
    {
      frmNetworkLayer(&buffer);
      inc(frame_to_send);
      s->info = buffer;
      s->seq = frame_to_send;
      cout<<"  SENDER:  Info = "<<s->info.data<<"  Seq No = "<<s->seq;
      turn = 'r';
      toPhysicalLayer(s);
    }
   if(event==timeout)
    {
      cout<<"SENDER : Resending Frame             ";
      turn = 'r';
      toPhysicalLayer(s);
    }
  }
}

void reciever()
{
 static int frame_expected=0;
 frame *r,*s;
 event_type event;

 wait_for_event_reciever(&event);
 if(turn=='r')
  {
   if(event==frameRecieved)
    {
     frmPhysicalLayer(r);
     if(r->seq==frame_expected)
      {
       toNetworkLayer(&r->info);
       inc(frame_expected);
      }
     else
       cout<<"RECIEVER : Acknowledgement Resent\n";

     turn = 's';
     toPhysicalLayer(s);
    }
     
   if(event==err)
    {
      cout<<"RECIEVER : Garbled Frame\n";
      turn = 's';     //if frame not recieved
    }                 //sender shold send it again
  }
}

/////////////////////////////////////////////////////

void frmNetworkLayer(packet *buffer)
{
   cout<<"\nEnter data to be sent: ";
   gets(mainInfo);
   cout<<endl;
   strcpy((*buffer).data, mainInfo);
   i++;
}

void toPhysicalLayer(frame *s)
{
  s->err = random(4);   //non zero means no error and error = 0
  DATA = *s;
}

void toNetworkLayer(packet *buffer)
{
 cout<<"   |   RECIEVER: Packet \'"<<(*buffer).data<<"\' recieved , Ack Sent\n";
 if(i>totalPackets)
   //connectionStatus = 0;    //old
   /*   new     */
   {
        connectionStatus = 1;
        cout<<"\nDISCONNECTED";
   }
}

void frmPhysicalLayer(frame *buffer)
{
 *buffer = DATA;
}

/////////////////////////////////////////////////////

void wait_for_event_sender(event_type * e)
{
 static int timer=0;

 if(turn=='s')
  {
   timer++;
   if(timer==TIMEOUT)
    {
     *e = timeout;
     cout<<"SENDER : Ack not recieved=> TIMEOUT\n";
     timer = 0;
     return;
    }
   if(DATA.err==0)
     *e = err;
   else
    {
     timer = 0;
     *e = frameRecieved;
    }
  }
}

void wait_for_event_reciever(event_type * e)
{
 if(turn=='r')
  {
   if(DATA.err==0)
     *e = err;
   else
     *e = frameRecieved;
  }
}
