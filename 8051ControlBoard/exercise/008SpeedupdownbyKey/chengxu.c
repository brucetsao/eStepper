
/********************************************************

ʵ�ֹ��ܣ���ת_��ת_����ת�ɿ�ֹͣ
ʹ��оƬ��AT89S52
����11.0592MHZ
���뻷����Keil
���ߣ�zhangxinchunleo
��վ��www.ourhc.cn
�Ա��꣺��ϿƼ� http://shop36330473.taobao.com

���������˳��������ѧϰ��ο���������ע����Ȩ��������Ϣ��     
********************************************************/
#include<reg52.h> //���ļ�
#define uchar unsigned char	//�ַ��ͺ궨��
#define uint unsigned int	//���ͺ궨��
uchar tcnt;				    //��ʱ��������ֵ����
uint sec;				    //�ٶ�ֵ����
/********************************************************
 						����λ����
********************************************************/

sbit shi_neng=P1^0;  //	ʹ�ܿ���λ
sbit fang_shi=P1^1;  //	������ʽ����λ
sbit fang_xiang=P1^2;//	��ת�������λ
sbit mai_chong=P1^3; // �������λ

sbit zheng_zhuan=P2^0;	//��ת
sbit fang_zhuan=P2^1;	//��ת


/********************************************************************
                            ��ʱ����
*********************************************************************/
void delay(uchar t)
{
  uchar i,j;
   for(i=0;i<t;i++)
   {
   	 for(j=13;j>0;j--);
	 { ;
	 }
   }
}

/********************************************************************
                        ��ʱ�жϷ�����
*********************************************************************/
void t0(void) interrupt 1 using 0 //��ʱ�жϷ�����
{
	tcnt++; //ÿ��250ust tcnt ��һ
	if(tcnt==1) //��tcnt��������ʱ
	{
		tcnt=0; //���������ټ�
		sec++;
		if(sec==20) //��������ֵԽС�����ת���ٶ�Խ��
		{
			sec=0; //���������ټ�
			mai_chong=~mai_chong; //�������
		}
	}
}

/********************************************************
 						��ʼ��
********************************************************/
void  init()
{
	TMOD=0x02; //��ʱ�������ڷ�ʽ2
	ET0=1;
	EA=1;
	TH0=0x06; //��TH0 TL0 ��ֵ
	TL0=0x06;
	TR0=1; //��ʼ��ʱ
	sec=0;
	mai_chong=1; // �������λ
}

/********************************************************
 						������
********************************************************/

main()
{
    init();		 //�����ʼ��
	shi_neng=0;  //	ʹ�ܿ���λ
	fang_shi=1;  //	������ʽ���� 
	fang_xiang=1;// ���Ʒ���Ϊ��ת
	while(1)
	{
	 if(zheng_zhuan==0){delay(100);shi_neng=1;fang_xiang=0;while(!zheng_zhuan);delay(100);shi_neng=0;fang_xiang=0;}
	 if(fang_zhuan==0){delay(100);shi_neng=1;fang_xiang=1;while(!fang_zhuan);delay(100);shi_neng=0;fang_xiang=1;}
	}
}
/********************************************************
 						����
********************************************************/