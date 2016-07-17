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

class cBaseAI  //用来派生，每颗棋子具有AI的属性
{
public:
	cBaseAI();
	~cBaseAI();
	void setVirXY(cBaseAI &base ,int x,int y);

	virtual bool MarkScore(int radii,cBaseAI &bAi ,cBaseAI &nextBit,int &retScore)=0;   //

	void swap(int *p1, int *p2);
	void shell(scoreAndBit *a, int d, int len);
	void shellSort(scoreAndBit *a, int d, int len);


//跳到棋盘任何一点,已经按棋子的分布标号。传入的棋子对象即对应它的位置，
//state :0-黑棋		1-白棋
//return ture 成功   
virtual bool MoveToAnyBit(cBaseAI &bAi,bool &state)=0;	

//private:

	//-每位棋子的基本属性量-------
	int m_virX;  //棋子的虚拟坐标X   
	int m_virY;	 //棋子的虚拟坐标Y
	int m_iBitscore;   //棋位的分数
	int m_iBitRank;	   //棋位的排名
	bool m_bBitDisplayState;	//棋位的显示状态   0-unshowed  1-showed;
	bool m_bBitWOrBState;	    //棋位黑/白状态 0-黑；1-白
	bool m_bIsMan;   	//是否是人走的棋位， 0-机器走的棋子，1-人走的。


	
	


};





//==
#endif