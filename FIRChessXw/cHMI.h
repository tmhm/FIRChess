#ifndef CHMI_H
#define CHMI_H
//====

#include <windows.h>

//#include "cChessBoard.h"
//#include "cChessPiece.h"

const COORD AlertXY={40,13};
const COORD	crEndHmi={2, 19};
enum endCaseOption
{
	EndCaseIsEnd=1,
		EndCaseIsRestart
};

class cHMI
{
public:
	cHMI();
	~cHMI();
	void FirAlert(COORD xy ,char *ch);  //(/*int argc, char* argv[]*/)
	void SetSignOpt(int sigNum, bool showSta);  //sigNum��С  0��100   ��show   0������ʾ  1-show   
	void SelectOption(COORD xyBottom,COORD xyTop,COORD &re);	//����һ��ѡ��
	void ShowHMI();
	void DynamicShowHmi();    //��Ϸ�еĽ�����ʾ��

	void PutOneBit(bool flag , COORD SitePut);   // 0  ���壻 1  ����

	void GetGameMode(int &hhOrhm, int &foreOrBl); 

//	int EndOnceGameOption(COORD endxy , int whowin);  //����һ�֣���ʾ�򣬼�����һ�֣������˳�
	int EndOnceGameOption(COORD endxy , int whowin ,int hhorhn ,int forbOrBla);


//	void FIRStart(COORD &tempPoint);//
//	int  FirModeSwitch(void);
//	void ChessPut(bool flag , COORD SitePut);  //�ͷ����ӣ�flag��0 ���壻 1 ����
//	void chessPerGrade(int *chessP[15][15]);


	void setPos(HANDLE hCon, int x, int y);
//	void GetHmiCurPot();	
//	void Set
//private:

	static 		HANDLE hOut,hIn;

private:

	void showHMPlus();
//	void showHHPlus();

	void showHMPlusSelect();
	void showHMPlusSelectF(); //�˻�������ʾ
	void showHMPlusSelectB(); //�˻�������ʾ

	void showHHPlusSelect(); //������ʾ

	//��Ϸģʽ:	1-������Ϸ		2-˫����Ϸ������ǰ����
	int m_iGameModeHMorHH;	

	int m_iGameModeForeorBlack;		//�Ⱥ���ѡ��   1-- �����֣�2--�˺���
	
//	cChessBoard cChboard;
//	cChessPiece cChpiece;
	


};

#endif   //