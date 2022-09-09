
#include "ECanVci.h"
#include <string.h>
#include<stdio.h>
#define OS_UNIX
#include "unistd.h"
#include "time.h"


INIT_CONFIG pInit;
        int res;


        ERR_INFO ErrInfo;
        CAN_OBJ pSend;
        CAN_OBJ rx;
          DWORD pD;
int main(int argc, char *argv[])
{
   // QCoreApplication a(argc, argv);

int res,i,j,len=0,sendnum=0,sendnum1=0,resnum=0,resnum2=0;
CAN_OBJ pSend[2];
CAN_OBJ rx;
pInit.AccCode=0;
pInit.AccMask=0xffffff;
pInit.Filter=0;
pInit.Timing0=0x00;
pInit.Timing1=0x1c;
pInit.Mode=0;
pInit.Reserved =0;

res=OpenDevice(4,0,0);
printf("opendevice:%d\r\n",res);

       // getchar();
if(res==0)
return 1;
        res=InitCAN(4,0,0,&pInit);
      printf("InitCAN 1 value: %d\n", res);

         res=StartCAN(4,0,0);
       printf("StartCAN 1 value: %d\n", res);


        res=InitCAN(4,0,1,&pInit);
       printf("InitCAN 2 value: %d\n", res);

         res=StartCAN(4,0,1);
       printf("StartCAN 2 value: %d\n", res);
	res=OpenDevice(4,1,0);
	printf("opendevice2:%d\r\n",res);
     	 

               res=InitCAN(4,1,0,&pInit);
             printf("InitCAN2: 1 value: %d\n", res);

                res=StartCAN(4,1,0);
             printf("StartCAN2: 1 value: %d\n", res);




              res=InitCAN(4,1,1,&pInit);
             printf("InitCAN2: 2 value: %d\n", res);

                res=StartCAN(4,1,1);
              printf("StartCAN2: 2 value: %d\n", res);

               getchar();

usleep(1000);

        pSend[0].ID=0;

        pSend[0].DataLen=8;
        pSend[0].ExternFlag=1;
        pSend[0].RemoteFlag=0;
        pSend[0].Data[0]=0x01;
        pSend[0].Data[1]=0x02;
        pSend[0].Data[2]=0x03;
        pSend[0].Data[3]=0x00;
        pSend[0].Data[4]=0x05;
        pSend[0].Data[5]=0x06;
        pSend[0].Data[6]=0x07;
        pSend[0].Data[7]=0x08;
        pSend[0].SendType=0;

        pSend[1].ID=1;

        pSend[1].DataLen=8;
        pSend[1].ExternFlag=1;
        pSend[1].RemoteFlag=0;
        pSend[1].Data[0]=0x01;
        pSend[1].Data[1]=0x02;
        pSend[1].Data[2]=0x03;
        pSend[1].Data[3]=0x00;
        pSend[1].Data[4]=0x05;
        pSend[1].Data[5]=0x06;
        pSend[1].Data[6]=0x07;
        pSend[1].Data[7]=0x08;
        pSend[1].SendType=0;



        for(j=0;j<3;j++)
   {
      for(i=0;i<50;i++)
      {

          pSend[0].ID=1;
           pSend[1].ID=2;
        res=Transmit(4,0,0,&pSend[0],1);
  		sendnum=sendnum+res;
	res=Transmit(4,1,0,&pSend[0],1);
  		sendnum1=sendnum1+res;

        // printf("Transmit 1 value: %d ID:%d\n", res,pSend.ID);
  //usleep(100);
//pSend.ID=pSend.ID+1;
    //    res=Transmit(1,0,1,&pSend,1);
       // if (res==0)
        // printf("Transmit 2 value: %dID:%d\n", res,pSend.ID);
        //ReadErrInfo(1,0,0,&ErrInfo);
        pSend[0].Data[3]=(pSend[0].Data[3]+0x01)&0xff;
        //printf("TX: %x\n",pSend.ID);



 //printf("Receive1 can2: value: %d ID:%d\n", len,rx.ID);
//len=Receive(1,0,1,&rx,1,0);

//if (len==1)
//printf("Receive1 can2: value: %d ID:%d\n", len,rx.ID);
//len=Receive(1,1,0,&rx,1,0);

//if (len==1)
//printf("Receive2 can1: value: %d ID:%d\n", len,rx.ID);

        //printf("ErrInfo.ErrCode: %x\n",ErrInfo.ErrCode);
       }

      usleep(10000);
      for (i=0;i<500;i++)
      {      
	len=Receive(4,0,1,&rx,1,0);

          if (len==1)
          {
         resnum++;
          }
      }
      printf("sendnum:%d   resnum:%d\r\n", sendnum,resnum);
      getchar();



        for (i=0;i<500;i++)
        {

            if (Receive(4,1,1,&rx,1,0))
            {
           resnum2++;
            }
                }
        printf("sendnum1:%d   resnum2:%d\r\n", sendnum1,resnum2);
        getchar();



       }


res=CloseDevice(4,0);

//res=CloseDevice(1,1);
  printf("CloseDevice: %d\n", res);
res=CloseDevice(4,1);
  printf("CloseDevice1: %d\n", res);
    return 0;

   

}

