#include "stdafx.h"
#include <windows.h>
//#include <stdio.h>
//#include <conio.h>
#include "cBaseAI.h"
//#include <iostream.h>


cBaseAI::cBaseAI(/*unsigned int cnt*/)
{
	m_iBitscore=0;  //棋位的分数
	m_iBitRank=0;	//棋位的排名
	m_bBitDisplayState=0;	//棋位的显示状态   0-unshowed  1-showed;
//	bool m_bBitDisplayState;	//棋位的显示状态   0-unshowed  1-showed;
	m_bBitWOrBState=0;	//棋位黑/白状态 0-黑；1-白
	m_bIsMan=0;	//是否是人走的棋位， 0-机器走的棋子，1-人走的。
}

cBaseAI::~cBaseAI()
{
//	close
}

void cBaseAI::setVirXY(cBaseAI &base ,int x,int y)
{
	base.m_virX = x;  //棋子的虚拟坐标X   
	base.m_virY = y;	 //棋子的虚拟坐标Y
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




