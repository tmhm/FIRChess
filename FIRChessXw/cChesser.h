#ifndef CCHESSER_H
#define CCHESSER_H
//====

#include <windows.h>

#include "cChessPiece.h"
#include "cChessBoard.h"
#include "cHMI.h"

//--------------------------以下为可设置参数区
enum Forbidden  //禁手状态
{
	ThreeThrForb = 1,
		FourFouForb,
		FourThrThrForb,
		FourFouThrForb,
		FourThrForb,
		LongForb,
		FourFouThrThrForb

};
enum IfWiner  //赢状态
{
	NoneWin =1,
	BlackPlayerWin,
	WhitePlayerWin,
	ForbSta
};

//	fiveScore=29625,
//		liveFour = 15575,
//		sigleFour= 4096,
//		liveThree= 2048,
//		sigleThree=500,
//		liveTwo   =255,
//		sigleTwo  =50,
//		liveOne   =25,
//		sigleOne  =5,
//		Unlive    =0

enum GameSta  //棋局状态
{

	FreedomOfFour = 15575,
		SigleFour =4096,
		FreedomOfThree =2048,
		SigleThree =500,
		FreedomOfTwo =255,
		SigleTwo =50,
		FreedomOfOne =25,
		SigleOne =5,
		None = 0
};


//#define  LongForbidden	1
 
//评分 搜索半径； 可更改
const int conRadiusOption = 3;

//========================
// 机器下棋搜索范围    仅能选用一种
//#define  RadiusOptionTwo	2
//#define  RadiusOptionThree	3
//#define  RadiusOptionFour	4
#define  RadiusOptionFive	5

//--------------------------以上为可设置参数区

class cChesser : public cHMI
{
public:
	cChesser();
	~cChesser();
	
	void PhyToVirtualBit(COORD &physical, int &virX,int &virY); //将物理的坐标 变换为棋子对象的标号x，y 
	void VirtualToPhyBit(int &virX,int &virY ,COORD &physical); //将棋子对象的标号x，y  变换为 物理的坐标

	//返回下子成功与否
	bool bPlayOnceChess(bool playsta, //棋手所属先后手， 先手 0 -黑， 后手  2- 白   因为永远是黑棋先行
						COORD &ret);  //回传所下子，更改其属性


	bool bGetChessDisplaySta(cChessPiece &bit);//获取一个棋子的显示状态属性
	int bGetChessScore(cChessPiece &bit);//获取一个棋子的分数属性

	int iGetReadyChessCnt();//获取已下棋子数量

	int iChesserOperating(int hmOrhh,int fOrb ,COORD &tempPoint);  //由该棋手操作所有

	bool iGameIsWinCheck(cChessPiece &bit, bool whoBit ,int &forbiddenSta ,int &gameSta,int &winSta);   //判断输赢，包括禁手

	bool bResetOnceBit(cChessPiece &bit);  //清掉一颗下的子

	void MakeEndGame();//eng game

	bool MachGiveOnceStep(COORD &bit,bool whob); //传进去的是上一步，对方所下子的虚拟位置， 返回次步所下子

	//void MarkbitScoreer(int radii,bool whoBit,cChessPiece &bAi ,cChessPiece &nextBit,int &retScore);
	void MarkbitScoreer(int radii,bool whoBit,cChessPiece &bAi ,int &retScore);

	void ForbiddenCase(int forbOption);

	bool CheckGameSta(cChessPiece &bit,bool whoBit,int &forbiddenSta,int &winSta,int &gameSta,int &retScore);

	void setGameModeFBOrS(int front , int sigleOrdoub);

//	void checkCaseOption(int rad,);
//	void checkCaseOption(int &rad, bool whobtemp, int MachForbFlagTemp,int MachWinstaTemp, int machGameStaTemp,scoreAndBit scoreSt ,int &cnt);
	void checkCaseOption(int &rad, 
						COORD &bitt,
						bool whobtemp, 
						int &MachForbFlagTemp,
						int &MachWinstaTemp, 
						int &machGameStaTemp,
						scoreAndBit *scoreSt,
						int &cnt);

private:
	
	int m_iWinState;	//是否赢状态
	int m_iForbiddenSta;	//禁手状态
	static	COORD m_iMostValBit_Vir ;   //最重要棋子
	static	COORD m_iSeconedValBit_Vir;   //第二重要棋子
	int m_bHumAndMachMode;	//0-人机模式；1-人人模式
	int  m_bMachIsFront;	//0-机先人后  1-人先机后
	int m_lastGameSta;


	cChessPiece cChPiece[15][15];

	cChessBoard cBoaOfCher;



};





//==
#endif