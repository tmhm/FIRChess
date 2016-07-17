#ifndef CCHESSER_H
#define CCHESSER_H
//====

#include <windows.h>

#include "cChessPiece.h"
#include "cChessBoard.h"
#include "cHMI.h"

//--------------------------����Ϊ�����ò�����
enum Forbidden  //����״̬
{
	ThreeThrForb = 1,
		FourFouForb,
		FourThrThrForb,
		FourFouThrForb,
		FourThrForb,
		LongForb,
		FourFouThrThrForb

};
enum IfWiner  //Ӯ״̬
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

enum GameSta  //���״̬
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
 
//���� �����뾶�� �ɸ���
const int conRadiusOption = 3;

//========================
// ��������������Χ    ����ѡ��һ��
//#define  RadiusOptionTwo	2
//#define  RadiusOptionThree	3
//#define  RadiusOptionFour	4
#define  RadiusOptionFive	5

//--------------------------����Ϊ�����ò�����

class cChesser : public cHMI
{
public:
	cChesser();
	~cChesser();
	
	void PhyToVirtualBit(COORD &physical, int &virX,int &virY); //����������� �任Ϊ���Ӷ���ı��x��y 
	void VirtualToPhyBit(int &virX,int &virY ,COORD &physical); //�����Ӷ���ı��x��y  �任Ϊ ���������

	//�������ӳɹ����
	bool bPlayOnceChess(bool playsta, //���������Ⱥ��֣� ���� 0 -�ڣ� ����  2- ��   ��Ϊ��Զ�Ǻ�������
						COORD &ret);  //�ش������ӣ�����������


	bool bGetChessDisplaySta(cChessPiece &bit);//��ȡһ�����ӵ���ʾ״̬����
	int bGetChessScore(cChessPiece &bit);//��ȡһ�����ӵķ�������

	int iGetReadyChessCnt();//��ȡ������������

	int iChesserOperating(int hmOrhh,int fOrb ,COORD &tempPoint);  //�ɸ����ֲ�������

	bool iGameIsWinCheck(cChessPiece &bit, bool whoBit ,int &forbiddenSta ,int &gameSta,int &winSta);   //�ж���Ӯ����������

	bool bResetOnceBit(cChessPiece &bit);  //���һ���µ���

	void MakeEndGame();//eng game

	bool MachGiveOnceStep(COORD &bit,bool whob); //����ȥ������һ�����Է������ӵ�����λ�ã� ���شβ�������

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
	
	int m_iWinState;	//�Ƿ�Ӯ״̬
	int m_iForbiddenSta;	//����״̬
	static	COORD m_iMostValBit_Vir ;   //����Ҫ����
	static	COORD m_iSeconedValBit_Vir;   //�ڶ���Ҫ����
	int m_bHumAndMachMode;	//0-�˻�ģʽ��1-����ģʽ
	int  m_bMachIsFront;	//0-�����˺�  1-���Ȼ���
	int m_lastGameSta;


	cChessPiece cChPiece[15][15];

	cChessBoard cBoaOfCher;



};





//==
#endif