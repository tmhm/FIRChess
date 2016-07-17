
//#include "stdafx.h"
//#include <iostream>  // 用system("color 3f");     

#include "stdafx.h"
#include <windows.h>
#include <stdio.h>
#include <conio.h>
#include "cChessBoard.h"
//#include <iostream.h>
#include "cHMI.h"
//extern static 		HANDLE hOut,hIn;

HANDLE cChessBoard::hOut = GetStdHandle(STD_OUTPUT_HANDLE);
HANDLE cChessBoard::hIn  = GetStdHandle(STD_INPUT_HANDLE);

cChessBoard::cChessBoard(/*unsigned int cnt*/)
{
		int line=0;
		int row=0;
		//system ("mode con cols=56 lines=20");          //设置窗口大小
	//	HANDLE hOut;
	//    hOut = GetStdHandle(STD_OUTPUT_HANDLE);
		SetConsoleTextAttribute(hOut, 0x30|0);
//system("color 0x07");                            //?¨ò?′°?ú??é?
//system("cls"); 
		COORD size = {80, 25};
		SetConsoleScreenBufferSize(hOut,size); // 重新设置缓冲区大小

		SMALL_RECT rc = {0,0, 80-1, 25-1}; // 重置窗口位置和大小
        SetConsoleWindowInfo(hOut,true ,&rc);
		SetConsoleTitle("五子棋"); // 设置窗口标题
	//	CloseHandle(hOut);
		for(line=0;line<15;line++)
		{
			   if(!line)
			   {
				   setPos(hOut,2,2);
				   for(row=0;row<15;row++)
				   {
					   if(!row)  
						   printf("┌");
					   else if(14==row)  
						   printf("┐");
					   else
						   printf("┬");
				   }				
			   }else if(line==14)
			   {
				   setPos(hOut,2,1*line+2);
				   for(row=0;row<15;row++)
				   {
					   if(!row)  
						   printf("└");
					   else if(14==row)  
						   printf("┘");
					   else 
						   printf("┴");
				   }

			   }else
			   {
				   setPos(hOut,2,line*1+2);
				   for(row=0;row<15;row++)
				   {
						if(!row)  
						{
							printf("├");
						}	
					   else if(14==row)  
						   printf("┤");
					   else
						   printf("┼");
				   }

			   }

		}
		printf("\n\n\n");

	//	CloseHandle(hOut);   //关闭句柄即不能控制输出控制台！
		

}

cChessBoard::~cChessBoard()
{
	CloseHandle(hOut);  
	CloseHandle(hIn);  
	
}

//private:

//	int chessant;
//	int chesser[15][15];

void cChessBoard::putOneBoardBit(COORD xy)  //放一bit棋盘
{
	SetConsoleTextAttribute(hOut, 0x30|0);
	if( 2==xy.X)
	{ 
						  
		if( 2==xy.Y)  {setPos(hOut,2,2);  printf("┌");}
		else if(16==xy.Y) {setPos(hOut,2,16);  printf("└");}
		else {setPos(hOut,2,xy.Y);  printf("├");}
	}
	else if(30==xy.X)
	{
		if( 2==xy.Y)  {setPos(hOut,2,2);  printf("┐");}
		else if(16==xy.Y) {setPos(hOut,2,16);  printf("┘");}
		else {setPos(hOut,2,xy.Y);  printf("┤");}
	}else
	{
		setPos(hOut,xy.X,xy.Y);  printf("┼");
	}
}

void cChessBoard::setPos(HANDLE hCon, int x, int y)
	{
		COORD pos = {x, y};
	 //  HANDLE hOut;
	//   hOut = GetStdHandle(STD_OUTPUT_HANDLE);
       SetConsoleCursorPosition(hCon, pos);
	 //  CloseHandle(hOut);
	}


void cChessBoard::keyRecTrack(COORD &crPost)   //返回释放棋子的物理位置
{
	DWORD			dwRes;
	WORD			dwState=0;
	INPUT_RECORD	keyRec;

static 	COORD			crStart={16, 9}, crPos;
	CONSOLE_SCREEN_BUFFER_INFO bInfo;

//	HANDLE hIn = GetStdHandle(STD_INPUT_HANDLE);
//	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);

	bool csuccess=0;
	CONSOLE_CURSOR_INFO cINFO;
	GetConsoleCursorInfo(hOut ,&cINFO);
	cINFO.dwSize=100;
	cINFO.bVisible=1;
	SetConsoleCursorInfo(hOut,&cINFO);

//	crPos.X=8*2;
//	crPos.Y=9;
	SetConsoleCursorPosition(hOut, crStart);

	bool keySpaceDoFlag=0;  //未按下确认释放棋子键

	while(!keySpaceDoFlag)  //没有按键一直扫描
	{
 		ReadConsoleInput(hIn, &keyRec, 1, &dwRes);

		if (keyRec.EventType == KEY_EVENT && keyRec.Event.KeyEvent.bKeyDown)
		{			// 
		//	if (keyRec.Event.KeyEvent.bKeyDown)		
		//	{
				GetConsoleScreenBufferInfo(hOut, &bInfo);
				crPos = bInfo.dwCursorPosition;
				dwState = keyRec.Event.KeyEvent.wVirtualKeyCode;
				if(dwState == VK_UP){
					crPos.Y -= 1;
					if(crPos.Y<2)	crPos.Y=16;
				}else if(dwState == VK_DOWN){	//
					crPos.Y += 1;		
					if(crPos.Y>16)	crPos.Y=2;
				}else if(dwState == VK_LEFT){	//
					crPos.X -= 2;		
					if(crPos.X<2)	crPos.X=30;
				}else if(dwState == VK_RIGHT){	//
					crPos.X += 2;
					if(crPos.X>30)	crPos.X=2;
				}else if(dwState == VK_SPACE){
					keySpaceDoFlag=1;
					//crPosLast.X=crPosNew.X;
					//crPosLast.Y=crPosNew.Y;
					crPost.X=crPos.X;
					crPost.Y=crPos.Y;
					crStart.X=crPos.X;
					crStart.Y=crPos.Y;

				}
				SetConsoleCursorPosition(hOut, crPos);
		//	}
		}

	}
//	CloseHandle(hOut);   //关闭句柄即不能控制输出控制台！
}

void cChessBoard::ChessPut(bool flag , COORD SitePut)   // 0  黑棋； 1  白棋
{
//	HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
			// setPos(SitePut.X,SitePut.Y);
			  SetConsoleCursorPosition(hOut, SitePut);
			  if(!flag){
				SetConsoleTextAttribute(hOut, 0x30|0);    //0x00  fore  black； 0x30 over blue    黑棋
			  }else{
				SetConsoleTextAttribute(hOut, 0x30|0x0f);  //0x30 over  blue ; 0x0f fore  white   白棋
			  }
			  printf("●");

//	 SetConsoleCursorPosition(hOut, SitePut);
//	 SetConsoleTextAttribute(hOut, 0x30|0x0f);  //0x30 over  blue ; 0x0f fore  white
//	 printf("●");
}



//};
