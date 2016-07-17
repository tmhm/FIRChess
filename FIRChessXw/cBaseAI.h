#ifndef CBASEAI_H
#define CBASEAI_H
//====

#include <windows.h>

//#include "cChessBoard.h"
//#include "cChessPiece.h"
//#include "cHMI.h"
enum bitScore
{
	fiveScore=99625,
		liveFour = 20575,
		sigleFour= 8096,
		liveThree= 2048,
		sigleThree=800,
		liveTwo   =355,
		sigleTwo  =100,
		liveOne   =25,
		sigleOne  =10,
		HaveOne = 5,
		Unlive    =0
};

struct scoreAndBit
{
	int Score;
		int X;
		int Y;
	//	bool flag;
	//	int orderCnt;

};//scoreAndBit stibitScore;

class cBaseAI  //����������ÿ�����Ӿ���AI������
{
public:
	cBaseAI();
	~cBaseAI();
	void setVirXY(cBaseAI &base ,int x,int y);

	virtual bool MarkScore(int radii,cBaseAI &bAi ,cBaseAI &nextBit,int &retScore)=0;   //

	void swap(int *p1, int *p2);
	void shell(scoreAndBit *a, int d, int len);
	void shellSort(scoreAndBit *a, int d, int len);


//���������κ�һ��,�Ѿ������ӵķֲ���š���������Ӷ��󼴶�Ӧ����λ�ã�
//state :0-����		1-����
//return ture �ɹ�   
virtual bool MoveToAnyBit(cBaseAI &bAi,bool &state)=0;	

//private:

	//-ÿλ���ӵĻ���������-------
	int m_virX;  //���ӵ���������X   
	int m_virY;	 //���ӵ���������Y
	int m_iBitscore;   //��λ�ķ���
	int m_iBitRank;	   //��λ������
	bool m_bBitDisplayState;	//��λ����ʾ״̬   0-unshowed  1-showed;
	bool m_bBitWOrBState;	    //��λ��/��״̬ 0-�ڣ�1-��
	bool m_bIsMan;   	//�Ƿ������ߵ���λ�� 0-�����ߵ����ӣ�1-���ߵġ�


	
	


};





//==
#endif