#ifndef CCHESSPIECE_H
#define CCHESSPIECE_H
//====

#include <windows.h>

#include "cBaseAI.h"



class cChessPiece:public cBaseAI
{
public:
	cChessPiece();
	~cChessPiece();
//	void keyRecTrack(COORD &crPost);//跟踪轨迹，传释放的棋位
//	void ChessPut(bool flag , COORD SitePut);  //释放棋子，flag：0 黑棋； 1 白棋

	void chessBitSetScore(int chessBit);

	virtual bool MarkScore(int radii,cBaseAI &bAi ,cBaseAI &nextBit,int &retScore);   //

//	virtual bool CallMoveToAnyBit(cBaseAI &bAi,bool state);
	virtual bool MoveToAnyBit(cBaseAI &bAi,bool state);

	bool bGetDisplaySta(cChessPiece &bit);//获取一个棋子的显示状态属性
	void SetDisplaySta(cChessPiece &bit);//设置一个棋子的显示状态属性
	void ResetDisplaySta(cChessPiece &bit);//q清掉一个棋子的显示状态属性


	bool bGetWOrBSta(cChessPiece &bit);//获取一个棋子的黑白属性
	void SetWOrBSta(cChessPiece &bit , bool sta);//设置一个棋子的黑白属性


	int iGetScore(cChessPiece &bit);//获取一个棋子的分数属性
	void iSetScore(cChessPiece &bit, int score);//设置一个棋子的分数属性


	int iretReadyChessCnt();//获取已下棋子数量

	void setReadyAllCnt();

private:
	
	static int m_iChessReadyCnt;   //已下子个数  

//	BYTE m_WhitOrBlackSta;	//黑/白子状态    uchar
//	bool m_bDisplayState;	//是否已载入棋盘，表示是否已下，0:还未载入；1:已显示
//	int m_iChessBitScore;//[15][15]; 棋子分数



//	COORD			crWhitePosLast, crWhitePosNew;    //上一次，本次//黑棋子位
//	COORD			crBlackPosLast, crBlackPosNew;    //上一次，本次//白棋子位

//	void setPos(HANDLE hCon, int x, int y);


};







//==
#endif