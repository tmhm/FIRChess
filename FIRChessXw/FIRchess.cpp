#include "stdafx.h"
#include <windows.h>
//#include <stdio.h>
//#include <conio.h>
#include "cFIRChess.h"
#include "cChesser.h"


cFIRChess::cFIRChess(/*unsigned int cnt*/)
{

}

cFIRChess::~cFIRChess()
{
//	close
}

int  cFIRChess::FirModeSwitch(void)
{
	return 0;
}
	
	


void cFIRChess::FIRStart(/*COORD &FirtempPoint*/)
{
	static COORD FirVirtualBitLatest={0,0};		// ��¼�����µ�����  ��������{0,0} ��{14,14}
	int hmOrHHMode=0;				//��Ϸģʽ:	1-������Ϸ		2-˫����Ϸ������ǰ����
	int ForeOrBlackMode=0;		//�Ⱥ���:   1-- �����֣�2--�˺���
	cChHmi.GetGameMode(hmOrHHMode,ForeOrBlackMode); 
	myChesser.setGameModeFBOrS(ForeOrBlackMode,hmOrHHMode);
//	cChboard.keyRecTrack(tempPoint);
//	cChboard.ChessPut(0 ,tempPoint);
	while(255 > myChesser.iGetReadyChessCnt())
	{

		myChesser.iChesserOperating(hmOrHHMode, ForeOrBlackMode, FirVirtualBitLatest);

	/*	if(1==hmOrHHMode)//�˻�ģʽ
		{
			if(1==ForeOrBlackMode) //������
			{
				
			}
			else//(2==ForeOrBlackMode)	//�˺���
			{
				;
			}

		}
		else if(2==hmOrHHMode) //˫��ģʽ 
		{
			if( 0 == (myChesser.iGetReadyChessCnt()%2))
				myChesser.bPlayOnceChess(0, tempPoint);
			else 
				myChesser.bPlayOnceChess(1, tempPoint);
		}
   */
	
	}
}

void cFIRChess::ChessGameStart(cChessBase &chessSt)
{

//	cChboard.keyRecTrack(tempPoint);
//	cChboard.ChessPut(0 ,tempPoint);
	//myChesser.PutOneBit(

//	COORD Pos_temp={0,0};

//	chessSt.ShowHmi();
//	chessSt.FIRStart(Pos_temp);
//	while(myChesser.iGetReadyChessCnt<255)
//	{
//		myChesser.bPlayOnceChess(0, Pos_temp);
//	}

}

void cFIRChess::ShowHmi()
{
	cChHmi.ShowHMI();

}



//void cFIRChess::chessPerGrade(int *chessP[15][15])  // 0  ���壻 1  ����
//{

//}


