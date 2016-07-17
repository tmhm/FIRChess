#include "stdafx.h"
#include <windows.h>
//#include <stdio.h>
//#include <conio.h>
#include "cHMI.h"
#include "cChesser.h"

HANDLE cHMI::hOut = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE cHMI::hIn  = GetStdHandle(STD_INPUT_HANDLE);

cHMI::cHMI(/*unsigned int cnt*/)
{

}

cHMI::~cHMI()
{
 
}

void cHMI::FirAlert(COORD xy ,char *ch)//警告交互
{
	COORD xyTemp=xy;
	
	SetConsoleCursorPosition(hOut, xyTemp); 
	xyTemp.Y +=1;
	printf("┏━━━━━━━━━━━━━━━━━┓");	SetConsoleCursorPosition(hOut, xyTemp); xyTemp.Y +=1;
	printf("┃                                  ┃");	SetConsoleCursorPosition(hOut, xyTemp); xyTemp.Y -=1;xyTemp.X +=2;
	printf("┗━━━━━━━━━━━━━━━━━┛"); SetConsoleCursorPosition(hOut, xyTemp); 
	printf(ch);

}


void cHMI::SelectOption(COORD xyBottom,  //选择坐标上下限		仅限上下键选择，space确认
				   COORD xyTop, 
				   COORD &re)	//返回选择的坐标
{
	SetSignOpt(100, 1);
	SetConsoleCursorPosition(hOut, xyBottom);

	DWORD			dwRes;
	WORD			dwState=0;
	INPUT_RECORD	keyRec;
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	COORD hmipos;

	bool keySpaceDoFlagTemp=0;  //未按下确认释放棋子键
	while(!keySpaceDoFlagTemp)  //没有按键一直扫描
	{
 		ReadConsoleInput(hIn, &keyRec, 1, &dwRes);

		if (keyRec.EventType == KEY_EVENT && keyRec.Event.KeyEvent.bKeyDown)
		{			// 
				GetConsoleScreenBufferInfo(hOut, &bInfo);
				hmipos = bInfo.dwCursorPosition;
				dwState = keyRec.Event.KeyEvent.wVirtualKeyCode;
				if(dwState == VK_UP){
					hmipos.Y -= 1;
					if(hmipos.Y<xyBottom.Y)	hmipos.Y +=(xyTop.Y  - xyBottom.Y +1) ;  //上下循环选择试问效果
				}else if(dwState == VK_DOWN){	//
					hmipos.Y += 1;				
					if(hmipos.Y>xyTop.Y)	hmipos.Y -=(xyTop.Y  - xyBottom.Y +1);  //上下循环选择试问效果
				}
				else if(dwState == VK_SPACE){
					keySpaceDoFlagTemp=1;
				}
				SetConsoleCursorPosition(hOut, hmipos);
		}
	}
	re.X =hmipos.X;
	re.Y =hmipos.Y;
	
}

void cHMI::showHMPlus()
{
	setPos(hOut, 40, 8);
	printf("┃   a.先手模式                   ┃");	setPos(hOut, 40, 9);
	printf("┃   b.后手模式                   ┃");	setPos(hOut, 40, 10);
	printf("┗━━━━━━━━━━━━━━━━┛");	setPos(hOut, 40, 11);
}
void cHMI::showHMPlusSelectF() //先手显示
{
	setPos(hOut, 40, 6);
	printf("┃您的游戏模式为：                ┃");	setPos(hOut, 40, 7);
	printf("┃  1.单人模式                    ┃");	setPos(hOut, 40, 8);  
	printf("┃   a.先手模式                   ┃");	setPos(hOut, 40, 9);
	printf("┃Enjoy yourself!(↑↓←→& space)┃");	setPos(hOut, 40, 10);
	printf("┗━━━━━━━━━━━━━━━━┛");	setPos(hOut, 40, 11);
}
void cHMI::showHMPlusSelectB() //后手显示
{
	setPos(hOut, 40, 6);
	printf("┃您的游戏模式为：                ┃");	setPos(hOut, 40, 7);
	printf("┃  1.单人模式                    ┃");	setPos(hOut, 40, 8);  
	printf("┃   b.后手模式                   ┃");	setPos(hOut, 40, 9);
	printf("┃Enjoy yourself!(↑↓←→& space)┃");	setPos(hOut, 40, 10);
	printf("┗━━━━━━━━━━━━━━━━┛");	setPos(hOut, 40, 11);
}

//void cHMI::showHHPlus()
//{
//	setPos(hOut, 40, 8);
//	printf("┃  a.先手模式                    ┃");	setPos(hOut, 40, 9);
//	printf("┃  b.后手模式                    ┃");	setPos(hOut, 40, 10);
//	printf("┗━━━━━━━━━━━━━━━━┛");	setPos(hOut, 40, 11);
//}

void cHMI::showHHPlusSelect()  //人人显示
{
	setPos(hOut, 40, 6);
	printf("┃您的游戏模式为：                ┃");	setPos(hOut, 40, 7);
	printf("┃  2.双人模式                    ┃");	setPos(hOut, 40, 8);  
	printf("┃    默认黑棋先行                ┃");	setPos(hOut, 40, 9);
	printf("┃Enjoy yourself!(↑↓←→& space)┃");	setPos(hOut, 40, 10);
	printf("┗━━━━━━━━━━━━━━━━┛");	setPos(hOut, 40, 11);
}
void cHMI::ShowHMI()
{
		//HANDLE hOut;
		COORD hmiposSD={42,7}, hmiposFB={40,2};//,hmipos;
		COORD hmiposHMmode ={42,7},hmiposHHmode ={42,8};
		COORD hmiposHMplusDown ={42,8},hmiposHHPlusUp ={42,9};
		COORD hmiposHMplusFo ={42,8},hmiposHHPlusBl ={42,9};
		COORD cReCur={0,0};
		//HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
	    //hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hOut, 0x30|0);

		//SetConsoleCursorPosition(hout, hmiposHome);
		setPos(hOut, 40, 2);
		printf("┏━━━━━━━━━━━━━━━━┓");	setPos(hOut, 40, 3);
		printf("┃NOTE:                           ┃");	setPos(hOut, 40, 4);
		printf("┃请使用方向键选择，space键确定！ ┃");	setPos(hOut, 40, 5);
		printf("┃                                ┃");	setPos(hOut, 40, 6);
		printf("┃游戏模式：                      ┃");	setPos(hOut, 40, 7);
		printf("┃  1.单人模式                    ┃");	setPos(hOut, 40, 8);   //(√)
		printf("┃  2.双人模式                    ┃");	setPos(hOut, 40, 9);
		printf("┗━━━━━━━━━━━━━━━━┛");	setPos(hOut, 40, 10);

		SelectOption(hmiposHMmode,hmiposHHmode,cReCur);
		if(cReCur.Y == hmiposHMmode.Y){
			m_iGameModeHMorHH=1;	//单人游戏
			showHMPlus();
			SelectOption(hmiposHMplusDown,hmiposHHPlusUp,cReCur);
			if(cReCur.Y == hmiposHMplusFo.Y){//先手模式
				m_iGameModeForeorBlack =1;	
				showHMPlusSelectF();
			}
			else if(cReCur.Y == hmiposHHPlusBl.Y){//后手模式
					m_iGameModeForeorBlack =2;	
					showHMPlusSelectB(); 
			}

		}
		else if(cReCur.Y == hmiposHHmode.Y){
			m_iGameModeHMorHH=2;	//双人游戏  ，默认先后手，不设置！
			showHHPlusSelect();
		}
}

void cHMI::PutOneBit(bool flag,COORD SitePut)  // 0  黑棋； 1  白棋
{
			  SetConsoleCursorPosition(hOut, SitePut);
			  if(!flag){
				SetConsoleTextAttribute(hOut, 0x30|0);    //0x00  fore  black； 0x30 over blue    黑棋
			  }else{
				SetConsoleTextAttribute(hOut, 0x30|0x0f);  //0x30 over  blue ; 0x0f fore  white   白棋
			  }
			  printf("●");

}

void cHMI::setPos(HANDLE hCon, int x, int y)  // 将光标定位到位置（x，y）
	{
		COORD pos = {x, y};
        SetConsoleCursorPosition(hCon, pos); 
	}

//sigNum大小  0～100   ；show   0，不显示  1-show   
void cHMI::SetSignOpt(int sigNum, bool showSta)
{
	CONSOLE_CURSOR_INFO cINFO;    //  光标状态
	GetConsoleCursorInfo(hOut ,&cINFO);

	cINFO.dwSize=sigNum;
	cINFO.bVisible=showSta;

	SetConsoleCursorInfo(hOut,&cINFO);  //  光标状态	
}

void cHMI::DynamicShowHmi()
{
	
}


void cHMI::GetGameMode(int &hhOrhm, int &foreOrBl)// 传送游戏模式参数
{
	 //游戏模式:	1-单人游戏		2-双人游戏，不分前后手
	hhOrhm   =  m_iGameModeHMorHH;	

	foreOrBl =  m_iGameModeForeorBlack;		//先后手选择   1-- 人先手；2--人后手
}

//BlackPlayerWin, WhitePlayerWin,
int cHMI::EndOnceGameOption(COORD endxy , int whowin ,int hhorhn ,int forbOrBla)  //结束一局，显示框，继续下一局，还是退出
{

	COORD xyTemp=endxy;
	COORD endPosT={2,18};
	
	SetConsoleCursorPosition(hOut, xyTemp); 
	xyTemp.Y +=1;
	printf("┏━━━━━━━━━━━━━━━━━┓");	SetConsoleCursorPosition(hOut, xyTemp); xyTemp.Y +=1;
	printf("┃                                  ┃");	SetConsoleCursorPosition(hOut, xyTemp); xyTemp.Y -=1;xyTemp.X +=2;
	printf("┗━━━━━━━━━━━━━━━━━┛"); SetConsoleCursorPosition(hOut, xyTemp); 
	if(BlackPlayerWin ==whowin)
	{
	//	printf("黑棋已胜! Enter--重来；Esc--退出");
		if( 1 ==hhorhn )
		{//dan ren 
			if( 1 == forbOrBla) //ren zai qian 
			{
				printf("您赢了!请按Esc--退出,谢谢使用!");
			
			}else{
				printf("您输了!请按Esc--退出,谢谢使用!");
			}
		}else
		{
			printf("黑棋获胜!请按Esc--退出,谢谢使用!");
		}
		
		SetConsoleCursorPosition(hOut, endPosT);
	}else if(WhitePlayerWin ==whowin)
	{
		if( 1 ==hhorhn )
		{//dan ren 
			if( 2 == forbOrBla) //ren zai qian 
			{
				printf("您赢了!请按Esc--退出,谢谢使用!");
			
			}else{
				printf("您输了!请按Esc--退出,谢谢使用!");
			}
		}
		else{
		//	printf("白棋已胜! Enter--重来；Esc--退出");
			printf("白棋获胜!请按Esc--退出,谢谢使用!");
		}
		SetConsoleCursorPosition(hOut, endPosT);
	}

	DWORD			dwRes;
	WORD			dwState=0;
	INPUT_RECORD	keyRec;

//	COORD			crEndHmi={16, 9}, crPos;

	//CONSOLE_SCREEN_BUFFER_INFO bInfoEnd;

	bool csuccess=0;
	CONSOLE_CURSOR_INFO cINFO;
	GetConsoleCursorInfo(hOut ,&cINFO);
	cINFO.dwSize=17;
	cINFO.bVisible=1;
	SetConsoleCursorInfo(hOut,&cINFO);


//	SetConsoleCursorPosition(hOut, crEndHmi);

	bool keySpaceDoFlag=0;  //未按下确认释放棋子键

	while(!keySpaceDoFlag)  //没有按键一直扫描
	{
 		ReadConsoleInput(hIn, &keyRec, 1, &dwRes);

		if (keyRec.EventType == KEY_EVENT && keyRec.Event.KeyEvent.bKeyDown)
		{// 
				dwState = keyRec.Event.KeyEvent.wVirtualKeyCode;
				if(dwState == VK_ESCAPE)
				{   
					keySpaceDoFlag =1;
					return EndCaseIsEnd;
				}
				else if(dwState == VK_RETURN)
				{	//
					keySpaceDoFlag =1;
					return EndCaseIsRestart;
				}
		}

	}
	return 0;
}


