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
	static COORD FirVirtualBitLatest={0,0};		// 记录最新下的棋子  虚拟棋子{0,0} ～{14,14}
	int hmOrHHMode=0;				//游戏模式:	1-单人游戏		2-双人游戏，不分前后手
	int ForeOrBlackMode=0;		//先后手:   1-- 人先手；2--人后手
	cChHmi.GetGameMode(hmOrHHMode,ForeOrBlackMode); 
	myChesser.setGameModeFBOrS(ForeOrBlackMode,hmOrHHMode);
//	cChboard.keyRecTrack(tempPoint);
//	cChboard.ChessPut(0 ,tempPoint);
	while(255 > myChesser.iGetReadyChessCnt())
	{

		myChesser.iChesserOperating(hmOrHHMode, ForeOrBlackMode, FirVirtualBitLatest);

	/*	if(1==hmOrHHMode)//人机模式
		{
			if(1==ForeOrBlackMode) //人先手
			{
				
			}
			else//(2==ForeOrBlackMode)	//人后手
			{
				;
			}

		}
		else if(2==hmOrHHMode) //双人模式 
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



//void cFIRChess::chessPerGrade(int *chessP[15][15])  // 0  黑棋； 1  白棋
//{

//}


