#ifndef CFIRCHESS_H
#define CFIRCHESS_H
//====

#include <windows.h>

#include "cChessBoard.h"
#include "cChessPiece.h"
#include "cHMI.h"
#include "cChessBase.h"
#include "cChesser.h"

class cFIRChess : public cChessBase
{
public:
	cFIRChess();
	~cFIRChess();

	void FIRStart(/*COORD &FirtempPoint*/);//
	int  FirModeSwitch(void);

	virtual void ChessGameStart(cChessBase &chessSt);


	void ShowHmi();


private:
	
	cChessBoard cChboard;

//	cChessPiece cChPiece[15][15];					
	cHMI		cChHmi;

	cChesser	myChesser;


};





//==
#endif