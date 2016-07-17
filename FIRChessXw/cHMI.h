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
	void SetSignOpt(int sigNum, bool showSta);  //sigNum大小  0～100   ；show   0，不显示  1-show   
	void SelectOption(COORD xyBottom,COORD xyTop,COORD &re);	//跟踪一次选择
	void ShowHMI();
	void DynamicShowHmi();    //游戏中的交互显示；

	void PutOneBit(bool flag , COORD SitePut);   // 0  黑棋； 1  白棋

	void GetGameMode(int &hhOrhm, int &foreOrBl); 

//	int EndOnceGameOption(COORD endxy , int whowin);  //结束一局，显示框，继续下一局，还是退出
	int EndOnceGameOption(COORD endxy , int whowin ,int hhorhn ,int forbOrBla);


//	void FIRStart(COORD &tempPoint);//
//	int  FirModeSwitch(void);
//	void ChessPut(bool flag , COORD SitePut);  //释放棋子，flag：0 黑棋； 1 白棋
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
	void showHMPlusSelectF(); //人机先手显示
	void showHMPlusSelectB(); //人机后手显示

	void showHHPlusSelect(); //人人显示

	//游戏模式:	1-单人游戏		2-双人游戏，不分前后手
	int m_iGameModeHMorHH;	

	int m_iGameModeForeorBlack;		//先后手选择   1-- 人先手；2--人后手
	
//	cChessBoard cChboard;
//	cChessPiece cChpiece;
	


};

#endif   //