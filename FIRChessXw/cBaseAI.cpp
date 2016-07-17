#include "stdafx.h"
#include <windows.h>
//#include <stdio.h>
//#include <conio.h>
#include "cBaseAI.h"
//#include <iostream.h>


cBaseAI::cBaseAI(/*unsigned int cnt*/)
{
	m_iBitscore=0;  //��λ�ķ���
	m_iBitRank=0;	//��λ������
	m_bBitDisplayState=0;	//��λ����ʾ״̬   0-unshowed  1-showed;
//	bool m_bBitDisplayState;	//��λ����ʾ״̬   0-unshowed  1-showed;
	m_bBitWOrBState=0;	//��λ��/��״̬ 0-�ڣ�1-��
	m_bIsMan=0;	//�Ƿ������ߵ���λ�� 0-�����ߵ����ӣ�1-���ߵġ�
}

cBaseAI::~cBaseAI()
{
//	close
}

void cBaseAI::setVirXY(cBaseAI &base ,int x,int y)
{
	base.m_virX = x;  //���ӵ���������X   
	base.m_virY = y;	 //���ӵ���������Y
}


void cBaseAI::swap(int *p1, int *p2) 
{
      int temp;
      temp = *p1;
      *p1 = *p2;
      *p2 = temp;
}

void cBaseAI::shell( scoreAndBit *a, int d, int len) 
{
       int i, j;
       
       for (i = d - 1; i < len; i++) 
	   {   
           for (j = i + d; j >= i && j < len; j--) 
		   {
                 if (a[j].Score < a[j-d].Score) 
				 {
                      swap(&a[j].Score, &a[j-d].Score);
					  swap(&a[j].X, &a[j-d].X);
					  swap(&a[j].Y, &a[j-d].Y);
                 }
            } 
        }
}

void cBaseAI::shellSort(scoreAndBit *a, int d, int len) 
{
       while (d >= 1) 
	   {
            shell(a, d, len);
            d = d / 2;
       }
}




