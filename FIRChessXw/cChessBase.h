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

virtual void ChessGameStart(cChessBase &chessSt)=0;    //������Ϸ��ʼ 



private:
	//int m_GamePlayerCnt;	//��Ϸ�������
//	int m_GamePlayA;		//A���		��Ϊ����
//	int m_GamePlayB;		//B���		��λ����


};





//==
#endif