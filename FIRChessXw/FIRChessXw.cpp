// FIRChessXw.cpp : Defines the entry point for the console application.
//
//����汾��1.17
//���뻷����microsoft visual c++ 6.0 (sp6)
//����޸�ʱ�䣺2014-12-10  20��54
//���ߣ�	xiawei
//email��	573352706@qq.com		
//---------------------------------------------------------------------

#include "stdafx.h"
#include "cChessBoard.h"
#include "cFIRChess.h"
#include "cFIRChess.h"

int main(/*int argc, char* argv[]*/)
{
//	COORD myTempPoint={9,9};
//	printf(" \n ��ӭʹ�������壬ף����Ϸ���! \n\n");
//	cChessBoard cChboard;

//	cChboard.keyRecTrack(tempPoint);
//	cChboard.ChessPut(0 ,tempPoint);

//myrestart:
	cFIRChess cFIRChessMin;
	cFIRChessMin.ShowHmi();
	cFIRChessMin.FIRStart();

	return 0;
}
