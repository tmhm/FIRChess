#ifndef CCHESSBOARD_H
#define CCHESSBOARD_H
//====

#include <windows.h>

class cChessBoard
{
public:
	cChessBoard(/*unsigned int cnt*/);
	~cChessBoard();
	void keyRecTrack(COORD &crPost);//跟踪轨迹，传释放的棋位
	void ChessPut(bool flag , COORD SitePut);  //释放棋子，flag：0 黑棋； 1 白棋
	void putOneBoardBit(COORD xy);  //放一bit棋盘

private:
	
	static 		HANDLE hOut,hIn;

	int m_ichesscnt;   //

	BYTE m_chessBoardBit[15][15];
	COORD			m_crWhitePosLast, m_crWhitePosNew;    //上一次，本次//黑棋子位
	COORD			m_crBlackPosLast, m_crBlackPosNew;    //上一次，本次//白棋子位

	void setPos(HANDLE hCon, int x, int y);


};



  

//==
#endif


