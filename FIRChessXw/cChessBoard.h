#ifndef CCHESSBOARD_H
#define CCHESSBOARD_H
//====

#include <windows.h>

class cChessBoard
{
public:
	cChessBoard(/*unsigned int cnt*/);
	~cChessBoard();
	void keyRecTrack(COORD &crPost);//���ٹ켣�����ͷŵ���λ
	void ChessPut(bool flag , COORD SitePut);  //�ͷ����ӣ�flag��0 ���壻 1 ����
	void putOneBoardBit(COORD xy);  //��һbit����

private:
	
	static 		HANDLE hOut,hIn;

	int m_ichesscnt;   //

	BYTE m_chessBoardBit[15][15];
	COORD			m_crWhitePosLast, m_crWhitePosNew;    //��һ�Σ�����//������λ
	COORD			m_crBlackPosLast, m_crBlackPosNew;    //��һ�Σ�����//������λ

	void setPos(HANDLE hCon, int x, int y);


};



  

//==
#endif


