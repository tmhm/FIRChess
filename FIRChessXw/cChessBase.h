#ifndef CCHESSBASE_H
#define CCHESSBASE_H
//====

#include <windows.h>

//#include "cChessBoard.h"
//#include "cChessPiece.h"
//#include "cHMI.h"

class cChessBase
{
public:
	cChessBase();
	~cChessBase();

virtual void ChessGameStart(cChessBase &chessSt)=0;    //棋类游戏开始 



private:
	//int m_GamePlayerCnt;	//游戏玩家数量
//	int m_GamePlayA;		//A玩家		定为先手
//	int m_GamePlayB;		//B玩家		定位后手


};





//==
#endif