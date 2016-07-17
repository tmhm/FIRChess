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
//	void keyRecTrack(COORD &crPost);//���ٹ켣�����ͷŵ���λ
//	void ChessPut(bool flag , COORD SitePut);  //�ͷ����ӣ�flag��0 ���壻 1 ����

	void chessBitSetScore(int chessBit);

	virtual bool MarkScore(int radii,cBaseAI &bAi ,cBaseAI &nextBit,int &retScore);   //

//	virtual bool CallMoveToAnyBit(cBaseAI &bAi,bool state);
	virtual bool MoveToAnyBit(cBaseAI &bAi,bool state);

	bool bGetDisplaySta(cChessPiece &bit);//��ȡһ�����ӵ���ʾ״̬����
	void SetDisplaySta(cChessPiece &bit);//����һ�����ӵ���ʾ״̬����
	void ResetDisplaySta(cChessPiece &bit);//q���һ�����ӵ���ʾ״̬����


	bool bGetWOrBSta(cChessPiece &bit);//��ȡһ�����ӵĺڰ�����
	void SetWOrBSta(cChessPiece &bit , bool sta);//����һ�����ӵĺڰ�����


	int iGetScore(cChessPiece &bit);//��ȡһ�����ӵķ�������
	void iSetScore(cChessPiece &bit, int score);//����һ�����ӵķ�������


	int iretReadyChessCnt();//��ȡ������������

	void setReadyAllCnt();

private:
	
	static int m_iChessReadyCnt;   //�����Ӹ���  

//	BYTE m_WhitOrBlackSta;	//��/����״̬    uchar
//	bool m_bDisplayState;	//�Ƿ����������̣���ʾ�Ƿ����£�0:��δ���룻1:����ʾ
//	int m_iChessBitScore;//[15][15]; ���ӷ���



//	COORD			crWhitePosLast, crWhitePosNew;    //��һ�Σ�����//������λ
//	COORD			crBlackPosLast, crBlackPosNew;    //��һ�Σ�����//������λ

//	void setPos(HANDLE hCon, int x, int y);


};







//==
#endif