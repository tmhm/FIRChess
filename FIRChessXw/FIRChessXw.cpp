// FIRChessXw.cpp : Defines the entry point for the console application.
//
//程序版本：1.17
//编译环境：microsoft visual c++ 6.0 (sp6)
//最后修改时间：2014-12-10  20：54
//作者：	xiawei
//email：	573352706@qq.com		
//---------------------------------------------------------------------

#include "stdafx.h"
#include "cChessBoard.h"
#include "cFIRChess.h"
#include "cFIRChess.h"

int main(/*int argc, char* argv[]*/)
{
//	COORD myTempPoint={9,9};
//	printf(" \n 欢迎使用五子棋，祝您游戏愉快! \n\n");
//	cChessBoard cChboard;

//	cChboard.keyRecTrack(tempPoint);
//	cChboard.ChessPut(0 ,tempPoint);

//myrestart:
	cFIRChess cFIRChessMin;
	cFIRChessMin.ShowHmi();
	cFIRChessMin.FIRStart();

	return 0;
}
