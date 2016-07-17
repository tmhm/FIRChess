#include "stdafx.h"
#include <windows.h>
//#include <stdio.h>
#include "cBaseAI.h"
#include "cChesser.h"
//#include <iostream.h>
#include "cChessBoard.h"
#include "stdlib.h"

extern   myrestart; 
 	//static	COORD m_iMostValBit_Vir ;   //最重要棋子
//	static	COORD m_iSeconedValBit_Vir;   //第二重要棋子

	COORD cChesser::m_iMostValBit_Vir={0,0};	//
	COORD cChesser::m_iSeconedValBit_Vir={0,0};	//

cChesser::cChesser(/*unsigned int cnt*/)
{
	int tx =0,ty=0;
	for(tx=0;tx<15;tx++)
	{
		for(ty=0;ty<15;ty++)
		{
			cChPiece[tx][ty].setVirXY(cChPiece[tx][ty] , tx,ty);
		}
	}

	m_iWinState = NoneWin;	//是否赢状态
	m_iForbiddenSta =0;	//禁手状态
//	m_iMostValBit_Vir  ={0,0};   //最重要棋子
//	m_iSeconedValBit_Vir ={0,0};   //第二重要棋子
	m_bHumAndMachMode = 0;	//0-人机模式；1-人人模式
	m_bMachIsFront=0;	//0-机先人后  1-人先机后

}

cChesser::~cChesser()
{
 
}
//--------------------------变换---------------------------------------------------------------------
void cChesser::PhyToVirtualBit(COORD &physical, int &virX,int &virY)//将物理的坐标 变换为棋子对象的标号x，y
{
	virX = (physical.X-2)/2;
	virY = physical.Y-2;
} 

void cChesser::VirtualToPhyBit(int &virX,int &virY ,COORD &physical)//将棋子对象的标号x，y  变换为 物理的坐标
{
	physical.X=virX*2+2;
	physical.Y=virY+2;
}
//-----------------------------------------------------------------------------------------------
bool cChesser::bPlayOnceChess(bool    playsta, //棋手所属先后手；  先手--0； 后手--1  
				   COORD  &ret)  //回传所下子的虚拟坐标，更改其属性
{
	COORD	Getpostemp={0,0};
	int		virBit_x=0,virBit_y=0;
	
	cBoaOfCher.keyRecTrack(Getpostemp);  //返回物理位置
	PhyToVirtualBit(Getpostemp, virBit_x, virBit_y);	//

	if(!bGetChessDisplaySta(cChPiece[virBit_x][virBit_y]))//此处还未有棋子
	{
		cChPiece[virBit_x][virBit_y].SetDisplaySta(cChPiece[virBit_x][virBit_y]); //标注已下子

		if(!playsta){
			PutOneBit(0 , Getpostemp); // 0  黑棋； 1  白棋
			cChPiece[virBit_x][virBit_y].SetWOrBSta(cChPiece[virBit_x][virBit_y], playsta); //
		}
		else{
			PutOneBit(1 , Getpostemp); // 0  黑棋； 1  白棋
			cChPiece[virBit_x][virBit_y].SetWOrBSta(cChPiece[virBit_x][virBit_y], playsta);
		}
		ret.X = virBit_x;
		ret.Y = virBit_y;
		return true;
	}
	else
		return false;
}

//-------------------------显示状态---------------------------------------
//用类声明变量， 就会构造对象！！
bool cChesser:: bGetChessDisplaySta(cChessPiece &bit)//获取一个棋子的显示状态属性
{
	return bit.m_bBitDisplayState;
}

//-------------------------------棋子分数属性-------------------------
int cChesser::bGetChessScore(cChessPiece &bit)//获取一个棋子的分数属性
{
	return bit.m_iBitscore;
}

int cChesser::iGetReadyChessCnt()//获取已下棋子数量
{
//	int temp=0;
//	temp =cChPiece[0][0].iretReadyChessCnt();
//	return temp;
	return cChPiece[0][0].iretReadyChessCnt();
}

void cChesser::setGameModeFBOrS(int front ,int sigleOrdoub)
{
	m_bMachIsFront  = front;
	m_bHumAndMachMode = sigleOrdoub;	//0-人机模式；1-人人模式
//	
}

//----------------------------
bool cChesser::bResetOnceBit(cChessPiece &bit)  //清掉一颗下的子
{
	bit.ResetDisplaySta(bit);  //
	COORD xyt={0,0};//{bit.m_virX ,bit.m_virY};

	VirtualToPhyBit(bit.m_virX,bit.m_virY ,xyt);//将棋子对象的标号x，y  变换为 物理的坐标
	cBoaOfCher.putOneBoardBit(xyt);

	return 0;

}
//=============================
//禁手case
void cChesser::ForbiddenCase(int forbOption)
{
	if(ThreeThrForb == forbOption)
	{
		FirAlert(AlertXY ,"该黑棋--三三禁手,请重下一黑棋!"); 
	}
	else if(FourFouForb == forbOption)
	{
		FirAlert(AlertXY ,"该黑棋--四四禁手,请重下一黑棋!"); 
	}
	else if(FourThrThrForb == forbOption)
	{
		FirAlert(AlertXY ,"该黑棋--四三三禁手,请重下一黑棋!"); 
	}	
	else if(FourFouThrForb == forbOption)
	{
		FirAlert(AlertXY ,"该黑棋--四四三禁手,请重下一黑棋!"); 
	}
	else if(LongForb == forbOption)
	{
		FirAlert(AlertXY ,"该黑棋--长连禁手,请重下一黑棋!"); 
	}//FourThrForb
	else if(FourThrForb == forbOption)
	{
		FirAlert(AlertXY ,"该黑棋--四三禁手,请重下一黑棋!"); 
	}
	else if(FourFouThrThrForb == forbOption)
	{
		FirAlert(AlertXY ,"该黑棋--四四三三禁手,请重下一黑棋!"); 
	}

}

//---------------------------由该棋手操作两方棋子的状态------
int cChesser::iChesserOperating(int hmOrhh,  //0--人机    1--人人
								int fOrb ,		// 1--先手  2--后手  仅限单人模式有效
								COORD &tempPoint)  // 传回下的最近的一个子   tempPoint即最新下的子
{
	//------没人赢 start--------------------------------------------------------------
	if(NoneWin == m_iWinState)  // 没人赢状态----------
	{
		if(1==hmOrhh)//人机模式
		{
			if(1==fOrb) //人先手 ======================================start====
			{
					if( 0 == (iGetReadyChessCnt()%2))
					{//人下一子
							if(bPlayOnceChess(0, tempPoint))
							{
								FirAlert(AlertXY ,"下了一黑棋，请下一白棋"); 
							}
							while(!iGameIsWinCheck(cChPiece[tempPoint.X][tempPoint.Y],
										  0,							//谁走的棋，即先后手， 0-黑/1-白
										  m_iForbiddenSta,				//禁手状态	
										  m_lastGameSta,   //记录本次下棋返回的棋局
										  m_iWinState))	 //---check win statue？
							{	//禁手未通过		ThreeThrForb,FourFouForb,FourThrThrForb,FourFouThrForb,	LongForb
								ForbiddenCase(m_iForbiddenSta);	
								//清掉该位下的棋子，重下
								bResetOnceBit(cChPiece[tempPoint.X][tempPoint.Y]);  //清掉一颗下的子

								if(bPlayOnceChess(0, tempPoint))
								{
									FirAlert(AlertXY ,"下了一黑棋,请下白棋!"); 
								}
							}
					}else
					{//机器下一子
						if(MachGiveOnceStep(tempPoint ,1))
						{
							FirAlert(AlertXY ,"机器下了一白棋,请下一黑棋"); 
						}
						iGameIsWinCheck(cChPiece[tempPoint.X][tempPoint.Y],
							  1,							//谁走的棋，即先后手， 0-黑/1-白
							  m_iForbiddenSta,				//禁手状态	
							  m_lastGameSta,   //记录本次下棋返回的棋局
							  m_iWinState);
					}
				
			} //===//人先手模式 end================================================
			else if(2==fOrb)	//人后手=================================start===
			{// void ForbiddenCase(int forbOption);
					if( 0 == (iGetReadyChessCnt()%2))
					{//机器下一子
						if(MachGiveOnceStep(tempPoint ,0))
						{
							FirAlert(AlertXY ,"机器下了一黑棋,请下一白棋"); 
						}
						while(!iGameIsWinCheck(cChPiece[tempPoint.X][tempPoint.Y],
										  0,							//谁走的棋，即先后手， 0-黑/1-白
										  m_iForbiddenSta,				//禁手状态	
										  m_lastGameSta,   //记录本次下棋返回的棋局
										  m_iWinState))  //---check win statue？
						{	//禁手未通过		ThreeThrForb,FourFouForb,FourThrThrForb,FourFouThrForb,	LongForb
							ForbiddenCase(m_iForbiddenSta);	
							//清掉该位下的棋子，重下
							bResetOnceBit(cChPiece[tempPoint.X][tempPoint.Y]);  //清掉一颗下的子

							if(MachGiveOnceStep(tempPoint ,0))
							{
								FirAlert(AlertXY ,"机器下了一黑棋,请下一白棋"); 
							}
						}

					}else
					{//人下一子  // 后手行棋，不需考虑禁手， 只要考虑赢状态
							if(bPlayOnceChess(1, tempPoint))   //返回虚拟位置xy
							{
								FirAlert(AlertXY ,"下了一白棋，请下一黑棋"); 
							}
							iGameIsWinCheck(cChPiece[tempPoint.X][tempPoint.Y],
											  1,							//谁走的棋，即先后手， 0-黑/1-白
											  m_iForbiddenSta,				//禁手状态	
											  m_lastGameSta,   //记录本次下棋返回的棋局
											  m_iWinState);


					}
			} //===================人后手=================================end===

		}
		else if(2==hmOrhh) //双人模式 
		{
			if( 0 == (iGetReadyChessCnt()%2))
			{
				if(bPlayOnceChess(0, tempPoint))
				{
					FirAlert(AlertXY ,"下了一黑棋，请下一白棋"); 
				}
				while(!iGameIsWinCheck(cChPiece[tempPoint.X][tempPoint.Y],
										  0,							//谁走的棋，即先后手， 0-黑/1-白
										  m_iForbiddenSta,				//禁手状态	
										  m_lastGameSta,   //记录本次下棋返回的棋局
										  m_iWinState))  //---check win statue？
				{	//禁手未通过		ThreeThrForb,FourFouForb,FourThrThrForb,FourFouThrForb,	LongForb
					ForbiddenCase(m_iForbiddenSta);
					//清掉该位下的棋子，重下
					bResetOnceBit(cChPiece[tempPoint.X][tempPoint.Y]);  //清掉一颗下的子

					if(bPlayOnceChess(0, tempPoint))
					{
						FirAlert(AlertXY ,"下了一黑棋，请下一白棋"); 
					}
				}
			}

			else // 白棋下子，不需考虑禁手， 只要考虑赢状态
			{
				if(bPlayOnceChess(1, tempPoint))   //返回虚拟位置xy
				{
					FirAlert(AlertXY ,"下了一白棋，请下一黑棋"); 
				}
				iGameIsWinCheck(cChPiece[tempPoint.X][tempPoint.Y],
							  1,							//谁走的棋，即先后手， 0-黑/1-白
							  m_iForbiddenSta,				//禁手状态	
							  m_lastGameSta,   //记录本次下棋返回的棋局
							  m_iWinState);
			}
		}

	}
	//------没人赢 end--------------------------------------------------------------
//m_bHumAndMachMode;	//0-人机模式；1-人人模式	int  m_bMachIsFront;	//0-机先人后  1-人先机后
	//------------- 有人赢了-------------------------------------------------------
	else if(BlackPlayerWin == m_iWinState)  //BlackPlayerWin, WhitePlayerWin,
	{//黑棋赢
		int tempEnd = EndOnceGameOption(AlertXY , BlackPlayerWin ,m_bHumAndMachMode ,m_bMachIsFront);
		//int tempEnd = EndOnceGameOption(AlertXY, BlackPlayerWin);

		if(EndCaseIsEnd ==tempEnd)  //结束一局，显示框，继续下一局，还是退出;
		{
			MakeEndGame();
		}
		else if(EndCaseIsRestart ==tempEnd)
		{
	//		goto  myrestart;
		}
	}
	else if(WhitePlayerWin == m_iWinState) //BlackPlayerWin, WhitePlayerWin,   //EndCaseIsEnd=1,	EndCaseIsRestart
	{//白棋赢
		int tempEnd = EndOnceGameOption(AlertXY , WhitePlayerWin ,m_bHumAndMachMode ,m_bMachIsFront);
	//	int tempEnd = EndOnceGameOption( AlertXY,WhitePlayerWin);  //结束一局，显示框，继续下一局，还是退出;
		if(EndCaseIsEnd ==tempEnd)  //结束一局，显示框，继续下一局，还是退出;
		{
			MakeEndGame();
		}
		else if(EndCaseIsRestart ==tempEnd)
		{
		//	goto  myrestart;
		}
	}
	else
	{
		
	}
//-------
		return 0;
}


//enum GameSta  //棋局状态
//{
//	FreedomOfFour = 1,
//		SigleFour,
//		FreedomOfThree,
//		SigleThree,
//		FreedomOfTwo,
//		SigleTwo,
//		FreedomOfOne,
//		SigleOne
//};

// 对谁下的一子判断
// whobit  0  - 下的黑棋   1- 下的白棋    foebidden only for black    
// bit  虚拟棋子位  eg， cChPiece[0][0]
//---------判断输赢，包括禁手  返回有谁win 状态   0，无win   1- 黑win   2- 白win ，3-禁手，重下子 (重修)
//禁手无累积效应，仅当次有效
//int cChesser::iGameIsWinCheck(cChessPiece bit,
bool cChesser::iGameIsWinCheck(cChessPiece &bit,
							  bool whoBit,      //谁走的棋，即先后手， 0-黑/ 1-白  
							  int &forbiddenSta,   //禁手状态	 jian  enum
							  int &gameSta,  //返回给下一步棋子   当步下子后的棋局
							  int &winSta)		// 修改 传回winsta ，而不是return，考虑内部禁手   见enum
{
	int virt_x=0,virt_y=0;
	bool bIfxOutside = 0,bIfyOutside = 0;	//出界标志位
	forbiddenSta= 0;  //将禁手标志清零，防止误判，禁手标志从1开始
	winSta = NoneWin;
	//        N
	//      W   E
	//        S
	int bit_NS_rowNum = 0;		// 默认0子，改用 do- while  
	int bit_NW_rowNum = 0, bit_WE_rowNum = 0, bit_WS_rowNum = 0;  //该行的同色棋子个数
	int NS_lastNoneNum = 0;  //同行棋子 尾  空棋位个数
	int NW_lastNoneNum = 0,WE_lastNoneNum = 0,WS_lastNoneNum = 0;

	// 空棋位   一边-1； 两边-2    无空边 -0；
	int NSLiveCnt =0;
	int NWLiveCnt =0, WELiveCnt =0, WSLiveCnt =0;

	int NS_OneGapBit = 0;  //跳子有同色棋
	int NW_OneGapBit = 0,WE_OneGapBit = 0,WS_OneGapBit = 0;
	int NS_GameSta =0;  // 棋局状态 ：eg ，活四， 活三 。。
	int NW_GameSta =0 ,WE_GameSta =0 ,WS_GameSta =0;

	int virt_xtemp= bit.m_virX;
	int virt_ytemp= bit.m_virY;

	virt_x = virt_xtemp;  //保存以备用
	virt_y = virt_ytemp;

	//forbidden  cnt 
	int ForbiFourCnt=0;
	int ForbiThreeCnt=0;
	
	// up 
//	if( !((virt_ytemp -1) <0) ){ // 上行未出界
//		if (cChPiece[virt_xtemp][virt_ytemp -1].m_bBitDisplayState)// 此位已下子
//		{
//			if(cChPiece[virt_xtemp][virt_ytemp -1].m_bBitWOrBState == whoBit)   //m_bBitWOrBState  0-hei  1 bai
//			bit_RowNum +=1;
//		}
//	}else{  //上行出界，反向必不出界
//		if(cChPiece[virt_xtemp][virt_ytemp +1].m_bBitDisplayState)  //bool m_bBitWOrBState;	 //棋位黑/白状态 0-黑；1-白
//	}

//--start NS----------------------------------------------------------------------------------------------
	virt_xtemp = virt_x; 
	virt_ytemp = virt_y;
	do  //up&&down
	{ //up
		bit_NS_rowNum +=1;
		virt_ytemp -=1;
		if(virt_ytemp<0)	
		{//碰界退出
			bIfyOutside = 1;
			break; 
		}
	}while(cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)));  //有子 并等于所下颜色的子， +1
//	if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)||
//		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit))//只有当反色或者无子的时候才会到这里（除了边界））

	if(!bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit， 未出界，考虑活棋 
	{//考虑有几个空白棋位  ,暂时只考虑3位
		NS_lastNoneNum +=1;
		NSLiveCnt +=1;
		virt_ytemp -=1;  // see next  bit if none 
		if(virt_ytemp>=0)   //note：一个空棋位之后，可能还会出项一个自己的同色棋!!
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
			{
				NS_lastNoneNum +=1;
				virt_ytemp -=1;  // see next  bit if none 
				if(virt_ytemp>=0)   //note：一个空棋位之后，可能还会出项一个自己的同色棋!!
				{
					if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
					{
						NS_lastNoneNum +=1;
					}
				}
			}
			else    //跳一格后有子?
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //跳子同色
				{
					NS_OneGapBit = 1;   //前半部分有一子跳子棋
				}
			}
		}
	}
	
	virt_xtemp = virt_x; 
	virt_ytemp = virt_y;
	bIfyOutside = 0;  //清边界
	virt_ytemp +=1;  //移位

	//up&&down
	//------down // 反向不能够 先+1，  用while 
	while(cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)))
	{  //有子 并等于所下颜色的子， +1
		//只有当反色或者无子的时候才会退出while循环（除了边界））
		bit_NS_rowNum +=1;
		virt_ytemp +=1;
		if(virt_ytemp>14)	
		{//碰界退出
			bIfyOutside = 1;
			break; 
		}
	}

	//--start--考虑棋子尾 空白位问题
	if(!bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit， 未出界，考虑活棋 
	{//考虑有几个空白棋位  ,暂时只考虑3位
		NS_lastNoneNum +=1;
		NSLiveCnt +=1;
		virt_ytemp +=1;  // see next  bit if none 
		if(virt_ytemp<15)
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
			{
				NS_lastNoneNum +=1;
				if(virt_ytemp<15)
				{
					if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
					{
						NS_lastNoneNum +=1;	
					}
				}
			}
			else    //跳一格后有子
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //跳子同色
				{
					NS_OneGapBit += 1;   //后半部分有一子跳子棋
				}
			}
		}
	}
	//--end--考虑棋子尾 空白位问题

	//-------check-start---
	if(bit_NS_rowNum>5) // check the bit number in a row;  
	{
		if(!whoBit) // 黑棋长连禁手
		{
			forbiddenSta = LongForb;
			return false;
		}else 
		{
			winSta = WhitePlayerWin;
		}
	}else if(5 == bit_NS_rowNum )
	{
		if(!whoBit) //black bit
		{
			if(!forbiddenSta)  // note : 在黑棋取胜之前还要加入禁手判断！！待加--------（2014-12-7） 
			{
				winSta = BlackPlayerWin;
			}
		}else  //white is win 
		{
			winSta = WhitePlayerWin;
		}

	}else if(4 == bit_NS_rowNum)
	{
		if((NSLiveCnt ==2) &&(NS_lastNoneNum >=2)) //在 连棋4个，两边jun live ,总共空棋位大于2，时 可以为 活四
		{//live 4
			NS_GameSta = FreedomOfFour;
			ForbiFourCnt +=1;
		}
		else if((NSLiveCnt ==1) &&(NS_lastNoneNum >=1))
		{// single 4
			NS_GameSta = SigleFour;
		}
	}else if(3 == bit_NS_rowNum )
	{
		if((NSLiveCnt ==2) && (NS_lastNoneNum >=3))  //在 连棋3个，两边总共空棋位大于等于4，时 可以为 活三     空空×××空空
		{//live 3
			NS_GameSta = FreedomOfThree;
			ForbiThreeCnt +=1;
		}else if((NSLiveCnt ==1) && (NS_lastNoneNum >=3))  //     空空×××空空
		{//live 3
			NS_GameSta = SigleThree;
		}
	}else if(2 == bit_NS_rowNum )
	{
		if((NSLiveCnt ==2) && (NS_lastNoneNum >=4))  //在 连棋2个，两边总共空棋位大于等于4，时 可以为 活2     空空×××空空
		{//live 3
			NS_GameSta = FreedomOfTwo;
		}else if((NSLiveCnt ==1) && (NS_lastNoneNum >=4))  //     空空×××空空
		{//live 3
			NS_GameSta = SigleTwo;
		}else if((NSLiveCnt ==2) && (NS_OneGapBit>=1))
		{//live 4
			NS_GameSta = SigleFour;
		}
	}



	//------end check-------

//--end NS----------------------------------------------------------------------------------------


//--start NW&&SE----------------------------------------------------------------------------------
	virt_xtemp = virt_x; 
	virt_ytemp = virt_y;
	do  //NW&&SE
	{ //NW
		bit_NW_rowNum +=1;
		virt_ytemp -=1;
		virt_xtemp -=1;
		if(virt_ytemp<0)	
		{//碰界退出
			bIfyOutside = 1;
			break; 
		}
		if(virt_xtemp<0)	
		{//碰界退出
			bIfxOutside = 1;
			break; 
		}
	}while(cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)));  //有子 并等于所下颜色的子， +1

	if(!bIfxOutside && !bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit， 未出界，考虑活棋 
	{//考虑有几个空白棋位  ,暂时只考虑3位
		NW_lastNoneNum +=1;
		NWLiveCnt +=1;
		virt_ytemp -=1;  // see next  bit if none 
		virt_xtemp -=1; 
		if((virt_ytemp>=0) &&(virt_xtemp>=0))   //note：一个空棋位之后，可能还会出项一个自己的同色棋!!
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
			{
				NW_lastNoneNum +=1;
				virt_ytemp -=1;  // see next  bit if none 
				virt_xtemp -=1; 
				if((virt_ytemp>=0) &&(virt_xtemp>=0))   //note：一个空棋位之后，可能还会出项一个自己的同色棋!!
				{
					if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
					{
						NW_lastNoneNum +=1;
					}
				}
			}
			else    //跳一格后有子
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //跳子同色
				{
					NW_OneGapBit = 1;   //前半部分有一子跳子棋
				}
			}
		}
	}
	
	virt_xtemp = virt_x;   //复原值
	virt_ytemp = virt_y;
	bIfxOutside = 0;  //清边界
	bIfyOutside = 0;  //清边界
	virt_ytemp += 1;  //移位
	virt_xtemp += 1;  //移位

	////NW&&SE
	//------SE // 反向不能够 先+1，  用while 
	while(cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)))
	{  //有子 并等于所下颜色的子， +1
		//只有当反色或者无子的时候才会退出while循环（除了边界））
		bit_NW_rowNum +=1;
		virt_ytemp +=1;
		virt_xtemp +=1;
		if(virt_ytemp>14)	
		{//碰界退出
			bIfyOutside = 1;
			break; 
		}
		if(virt_xtemp>14)	
		{//碰界退出
			bIfxOutside = 1;
			break; 
		}
	}

	//--start--考虑棋子尾 空白位问题
	if(!bIfxOutside && !bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit， 未出界，考虑活棋 
	{//考虑有几个空白棋位  ,暂时只考虑两位
		NW_lastNoneNum +=1;
		NWLiveCnt +=1;
		virt_ytemp +=1;  // see next  bit if none 
		virt_xtemp +=1;  // see next  bit if none 
		if((virt_ytemp<15)&&(virt_xtemp<15))
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) 
			{
				NW_lastNoneNum +=1;
				virt_ytemp +=1;  // see next  bit if none 
				virt_xtemp +=1;  // see next  bit if none 
				if((virt_ytemp<15)&&(virt_xtemp<15))
				{
					if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) 
					{
						NW_lastNoneNum +=1;
					}
				}
			}
			else    //跳一格后有子
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //跳子同色
				{
					NW_OneGapBit += 1;   //后半部分有一子跳子棋
				}
			}
		}
				
	}
	//--end--考虑棋子尾 空白位问题

	//-------check-start---
if(bit_NW_rowNum>5) // check the bit number in a row;  
	{
		if(!whoBit) // 黑棋长连禁手
		{
			forbiddenSta = LongForb;
			return false;
		}else 
		{
			winSta = WhitePlayerWin;
		}
	}else if(5 == bit_NW_rowNum )
	{
		if(!whoBit) //black bit
		{
			if(!forbiddenSta)  // note : 在黑棋取胜之前还要加入禁手判断！！待加--------（2014-12-7） 
			{
				winSta = BlackPlayerWin;
			}
		}else  //white is win 
		{
			winSta = WhitePlayerWin;
		}

	}else if(4 == bit_NW_rowNum)
	{
		if((NWLiveCnt ==2) &&(NW_lastNoneNum >=2)) //在 连棋4个，两边jun live ,总共空棋位大于2，时 可以为 活四
		{//live 4
			NW_GameSta = FreedomOfFour;
			ForbiFourCnt +=1;
		}
		else if((NWLiveCnt ==1) &&(NW_lastNoneNum >=1))
		{// single 4
			NW_GameSta = SigleFour;
		}
	}else if(3 == bit_NW_rowNum )
	{
		if((NWLiveCnt ==2) && (NW_lastNoneNum >=3))  //在 连棋3个，两边总共空棋位大于等于4，时 可以为 活三     空空×××空空
		{//live 3
			NW_GameSta = FreedomOfThree;
			ForbiThreeCnt +=1;
		}else if((NWLiveCnt ==1) && (NW_lastNoneNum >=3))  //     空空×××空空
		{//live 3
			NW_GameSta = SigleThree;
		}
	}else if(2 == bit_NW_rowNum )
	{
		if((NWLiveCnt ==2) && (NW_lastNoneNum >=4))  //在 连棋2个，两边总共空棋位大于等于4，时 可以为 活2     空空×××空空
		{//live 3
			NW_GameSta = FreedomOfTwo;
		}else if((NWLiveCnt ==1) && (NW_lastNoneNum >=4))  //     空空×××空空
		{//live 3
			NW_GameSta = SigleTwo;
		}else if((NWLiveCnt ==2) && (NW_OneGapBit>=1))
		{//live 4
			NW_GameSta = SigleFour;
		}
	}
	// check  last none bit number
//	if(NS_lastNoneNum > 3)
//	{
//		
//	}

	//------end check-------

//--end NW&&SE-----------------------------------------------------------------------------------------------

//--start WE-----------------------------------------------------------------------------------------------
	virt_xtemp = virt_x; 
	virt_ytemp = virt_y;
	do  //WE
	{ //WE
		bit_WE_rowNum +=1;
	//	virt_ytemp -=1;
		virt_xtemp -=1;	//x-1, y 不变
	//	if(virt_ytemp<0)	
	//	{//碰界退出
	//		bIfyOutside = 1;
	//		break; 
	//	}
		if(virt_xtemp<0)	
		{//碰界退出
			bIfxOutside = 1;
			break; 
		}
	}while(cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)));  //有子 并等于所下颜色的子， +1

	if(!bIfxOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit， 未出界，考虑活棋 
	{//考虑有几个空白棋位  ,暂时只考虑两位
		WE_lastNoneNum +=1;
		WELiveCnt +=1;
	//	virt_ytemp -=1;  // see next  bit if none 
		virt_xtemp -=1; 
		if(virt_xtemp>=0)   //note：一个空棋位之后，可能还会出项一个自己的同色棋!!-------------------
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
			{
				WE_lastNoneNum +=1;
				virt_xtemp -=1; 
				if(virt_xtemp>=0)   //note：一个空棋位之后，可能还会出项一个自己的同色棋!!-------------------
				{
					if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
					{
						WE_lastNoneNum +=1;
					}
				}
			}
			else    //跳一格后有子
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //跳子同色
				{
					WE_OneGapBit = 1;   //前半部分有一子跳子棋
				}
			}
		}
	}
	
	virt_xtemp = virt_x;   //复原值
	virt_ytemp = virt_y;
	bIfxOutside = 0;  //清边界
	virt_xtemp += 1;  //移位

	////WE
	//------WE // 反向不能够 先+1，  用while 
	while(cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)))
	{  //有子 并等于所下颜色的子， +1
		//只有当反色或者无子的时候才会退出while循环（除了边界））
		bit_WE_rowNum +=1;
		virt_xtemp +=1;
		if(virt_xtemp>14)	
		{//碰界退出
			bIfxOutside = 1;
			break; 
		}
	}

	//--start--考虑棋子尾 空白位问题
	if(!bIfxOutside  && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit， 未出界，考虑活棋 
	{//考虑有几个空白棋位  ,暂时只考虑两位
		WE_lastNoneNum +=1;
		WELiveCnt +=1;
		virt_xtemp +=1;  // see next  bit if none 
		if(virt_xtemp<15)
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
			{
				WE_lastNoneNum +=1;
					virt_xtemp +=1;  // see next  bit if none 
				if(virt_xtemp<15)
				{
					if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
					{
						WE_lastNoneNum +=1;
					}
				}
			}
			else    //跳一格后有子
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //跳子同色
				{
					WE_OneGapBit += 1;   //后半部分有一子跳子棋
				}
			}
		}
				
	}
	//--end--考虑棋子尾 空白位问题

	//-------check-start---


if(bit_WE_rowNum>5) // check the bit number in a row;  
	{
		if(!whoBit) // 黑棋长连禁手
		{
			forbiddenSta = LongForb;
			return false;
		}else 
		{
			winSta = WhitePlayerWin;
		}
	}else if(5 == bit_WE_rowNum )
	{
		if(!whoBit) //black bit
		{
			if(!forbiddenSta)  // note : 在黑棋取胜之前还要加入禁手判断！！待加--------（2014-12-7） 
			{
				winSta = BlackPlayerWin;
			}
		}else  //white is win 
		{
			winSta = WhitePlayerWin;
		}

	}else if(4 == bit_WE_rowNum)
	{
		if((WELiveCnt ==2) &&(WE_lastNoneNum >=2)) //在 连棋4个，两边jun live ,总共空棋位大于2，时 可以为 活四
		{//live 4
			WE_GameSta = FreedomOfFour;
			ForbiFourCnt +=1;
		}
		else if((WELiveCnt ==1) &&(WE_lastNoneNum >=1))
		{// single 4
			WE_GameSta = SigleFour;
		}
	}else if(3 == bit_WE_rowNum )
	{
		if((WELiveCnt ==2) && (WE_lastNoneNum >=3))  //在 连棋3个，两边总共空棋位大于等于4，时 可以为 活三     空空×××空空
		{//live 3
			WE_GameSta = FreedomOfThree;
			ForbiThreeCnt +=1;
		}else if((WELiveCnt ==1) && (WE_lastNoneNum >=3))  //     空空×××空空
		{//live 3
			WE_GameSta = SigleThree;
		}
	}else if(2 == bit_WE_rowNum )
	{
		if((WELiveCnt ==2) && (WE_lastNoneNum >=4))  //在 连棋2个，两边总共空棋位大于等于4，时 可以为 活2     空空×××空空
		{//live 3
			WE_GameSta = FreedomOfTwo;
		}else if((WELiveCnt ==1) && (WE_lastNoneNum >=4))  //     空空×××空空
		{//live 3
			WE_GameSta = SigleTwo;
		}else if((WELiveCnt ==2) && (WE_OneGapBit>=1))
		{//live 4
			WE_GameSta = SigleFour;
		}
	}
	// check  last none bit number
//	if(NS_lastNoneNum > 3)
//	{
//		
//	}

	//------end check-------

//--end WE-------------------------------------------------------------------------------------------------------


//--start WS&&NE--------------------------------------------------------------------------------------------------
	virt_xtemp = virt_x; 
	virt_ytemp = virt_y;
	do  //Ws&&NE
	{ //Ws
		bit_WS_rowNum +=1;
		virt_ytemp +=1;
		virt_xtemp -=1;	//x-1, y 不变
		if(virt_ytemp>14)	
		{//碰界退出
			bIfyOutside = 1;
			break; 
		}
		if(virt_xtemp<0)	
		{//碰界退出
			bIfxOutside = 1;
			break; 
		}
	}while(cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)));  //有子 并等于所下颜色的子， +1

	if(!bIfxOutside && !bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit， 未出界，考虑活棋 
	{//考虑有几个空白棋位  ,暂时只考虑两位
		WS_lastNoneNum +=1;
		WSLiveCnt +=1;
		virt_ytemp +=1;  // see next  bit if none 
		virt_xtemp -=1; 
		if((virt_xtemp>=0)&&(virt_ytemp<15))   //note：一个空棋位之后，可能还会出项一个自己的同色棋!!-------------------
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
			{
				WS_lastNoneNum +=1;
					virt_ytemp +=1;  // see next  bit if none 
				virt_xtemp -=1; 
				if((virt_xtemp>=0)&&(virt_ytemp<15))   //note：一个空棋位之后，可能还会出项一个自己的同色棋!!-------------------
				{
					if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
					{
						WS_lastNoneNum +=1;
					}
				}
			}
			else    //跳一格后有子
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //跳子同色
				{
					WS_OneGapBit = 1;   //前半部分有一子跳子棋
				}
			}
		}
	}
	
	virt_xtemp = virt_x;   //复原值
	virt_ytemp = virt_y;
	bIfxOutside = 0;  //清边界
	bIfyOutside = 0;  //清边界
	virt_xtemp += 1;  //移位
	virt_ytemp -= 1;  //移位

	////Ws&&NE
	//------NE // 反向不能够 先+1，  用while 
	while(cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)))
	{  //有子 并等于所下颜色的子， +1
		//只有当反色或者无子的时候才会退出while循环（除了边界））
		bit_WS_rowNum +=1;
		virt_xtemp +=1;
		virt_ytemp -= 1;  
		if(virt_xtemp>14)	
		{//碰界退出
			bIfxOutside = 1;
			break; 
		}
		if(virt_ytemp<0)	
		{//碰界退出
			bIfyOutside = 1;
			break; 
		}
	}

	//--start--考虑棋子尾 空白位问题
	if(!bIfxOutside  && !bIfyOutside  &&  !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit， 未出界，考虑活棋 
	{//考虑有几个空白棋位  ,暂时只考虑两位
		WS_lastNoneNum +=1;
		WSLiveCnt +=1;
		virt_xtemp +=1;  // see next  bit if none 
		virt_ytemp -=1;  // see next  bit if none 
		if((virt_xtemp<15)&&(virt_ytemp>0))
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
			{
				WS_lastNoneNum +=1;
				virt_xtemp +=1;  // see next  bit if none 
				virt_ytemp -=1;  // see next  bit if none 
				if((virt_xtemp<15)&&(virt_ytemp>0))
				{
					if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
					{
						WS_lastNoneNum +=1;
					}
				}
			}
			else    //跳一格后有子
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //跳子同色
				{
					WS_OneGapBit += 1;   //后半部分有一子跳子棋
				}
			}
		}
				
	}
	//--end--考虑棋子尾 空白位问题

	//-------check-start---

if(bit_WS_rowNum>5) // check the bit number in a row;  
	{
		if(!whoBit) // 黑棋长连禁手
		{
			forbiddenSta = LongForb;
			return false;
		}else 
		{
			winSta = WhitePlayerWin;
		}
	}else if(5 == bit_WS_rowNum )
	{
		if(!whoBit) //black bit
		{
			if(!forbiddenSta)  // note : 在黑棋取胜之前还要加入禁手判断！！待加--------（2014-12-7） 
			{
				winSta = BlackPlayerWin;
			}
		}else  //white is win 
		{
			winSta = WhitePlayerWin;
		}

	}else if(4 == bit_WS_rowNum)
	{
		if((WSLiveCnt ==2) &&(WS_lastNoneNum >=2)) //在 连棋4个，两边jun live ,总共空棋位大于2，时 可以为 活四
		{//live 4
			WS_GameSta = FreedomOfFour;
			ForbiFourCnt +=1;
		}
		else if((WSLiveCnt ==1) &&(WS_lastNoneNum >=1))//////////////////////////////////////////
		{// single 4
			WS_GameSta = SigleFour;
		}
	}else if(3 == bit_WS_rowNum )
	{
		if((WSLiveCnt ==2) && (WS_lastNoneNum >=3))  //在 连棋3个，两边总共空棋位大于等于4，时 可以为 活三     空空×××空空
		{//live 3
			WS_GameSta = FreedomOfThree;
			ForbiThreeCnt +=1;
		}else if((WSLiveCnt ==1) && (WS_lastNoneNum >=3))  //     空空×××空空
		{//live 3
			WS_GameSta = SigleThree;
		}
	}else if(2 == bit_WS_rowNum )
	{
		if((WSLiveCnt ==2) && (WS_lastNoneNum >=4))  //在 连棋2个，两边总共空棋位大于等于4，时 可以为 活2     空空×××空空
		{//live 3
			WS_GameSta = FreedomOfTwo;
		}else if((WSLiveCnt ==1) && (WS_lastNoneNum >=4))  //     空空×××空空
		{//live 3
			WS_GameSta = SigleTwo;
		}else if((WSLiveCnt ==2) && (WS_OneGapBit>=1))
		{//live 4
			WS_GameSta = SigleFour;
		}
	}


	// check  last none bit number
//	if(NS_lastNoneNum > 3)
//	{
//		
//	}

	//------end check-------

//--end WS&&NE----------------------------------------------------------------------------------
//	ThreeThrForb = 1,		FourFouForb,		FourThrThrForb,		FourFouThrForb,	FourThrForb,	LongForb 
	//===========foebidden check===========================================================================
	if(!whoBit)
	{
		if(!ForbiThreeCnt)  //ForbiFourCnt
		{
			if(ForbiFourCnt>=2){
				forbiddenSta = FourFouForb;
				return false;
			}
		}
		else if(1==ForbiThreeCnt)  //ForbiFourCnt
		{// have 3
			if(1==ForbiFourCnt){
				forbiddenSta = FourThrForb;
				return false;
			}
			else if(ForbiFourCnt >=2){
				forbiddenSta =FourFouThrForb ;
				return false;
			}
		}else if(2==ForbiThreeCnt)
		{// two 3
			if(!ForbiFourCnt){
				forbiddenSta = ThreeThrForb;
				return false;
			}
			else if(1==ForbiFourCnt){ 
				forbiddenSta = FourThrThrForb;
				return false;
			}
			else if(ForbiFourCnt >=2){
				forbiddenSta =FourFouThrThrForb;
				return false;
			}
		}
	}
//=====================================================================================================

//	if(winSta) // 已经有某一方胜出
//	{
		if(BlackPlayerWin == winSta ) {
			FirAlert(AlertXY ,"黑棋胜"); 
		}
		else if(WhitePlayerWin ==  winSta){
			FirAlert(AlertXY ,"白棋胜"); 
		}//  NS_GameSta =0;  // 棋局状态 ：eg ，活四， 活三  NW_GameSta =0 ,WE_GameSta =0 ,WS_GameSta =0;
		else //没有哪一方棋子胜出，返回当前重要的棋局 
		{
			gameSta =0;
			gameSta = ((NS_GameSta<<12) | (NW_GameSta<<8) | (WE_GameSta<<4) |(WS_GameSta));
		}
//	}
	return true;
}


void cChesser::MakeEndGame()//eng game
{
	cChPiece[0][0].setReadyAllCnt();
}


void cChesser::checkCaseOption(int &rad, 
							    COORD &bitt,
								bool whobtemp, 
								int &MachForbFlagTemp,
								int &MachWinstaTemp, 
								int &machGameStaTemp,
								scoreAndBit *scoreSt,
								int &cnt)
{
	COORD lastBitTemp ={0,0};
	lastBitTemp.X =bitt.X;
	lastBitTemp.Y =bitt.Y;
	
	scoreAndBit* p_st = scoreSt;
	bool whot =0;

	for(int radtemp = 0; radtemp < (rad -1); radtemp++)
	{
		int scorTempFA = 0;
		int scorTempBb = 0;
		//-2 列开始
		int tempx = 0,tempy=0;
		tempx =lastBitTemp.X - (radtemp +2) ;
		if(tempx >=0  ) //&& tempx <15
		{
			for(tempy =lastBitTemp.Y -(radtemp +2) ; tempy<lastBitTemp.Y +(radtemp +3) ;tempy++)
			{
				//bitY ++;
				if( tempy >=0 && tempy <15)
				{
						if( !bGetChessDisplaySta(cChPiece[tempx][tempy]))//  &&  bit.X!=tempx && bit.Y!=tempy )
						{
							//返回禁手，此棋位舍弃！！

							if(CheckGameSta(cChPiece[tempx][tempy],whobtemp,
								MachForbFlagTemp,MachWinstaTemp,machGameStaTemp,scorTempFA) )
							{
									
									if(whobtemp){	whot =0;}
									else {whot =1;}
									if(CheckGameSta(cChPiece[tempx][tempy],whot,
									MachForbFlagTemp,MachWinstaTemp,machGameStaTemp,scorTempBb))	//假如该处为反棋是否成重要棋子
									{//修改反的了
										if( machGameStaTemp> 2000 )
										scorTempBb  += machGameStaTemp;
									}					
									p_st->Score = scorTempFA + scorTempBb/2;
									p_st->X = 	tempx;	//记录棋子的虚拟坐标
									p_st->Y = 	tempy;
									p_st++;
									cnt++;    //直接放数组坐标自加  访问不 了  [0][0]
							}
						}
				}
			}
		}
		// +2 列
		tempx =lastBitTemp.X +(radtemp +2) ;
		if(tempx <15 ) // &&  tempx >=0 && 
		{
			for(tempy =lastBitTemp.Y -(radtemp +2) ; tempy<lastBitTemp.Y +(radtemp +3) ;tempy++)
			{
				//bitY ++;
				if( tempy >=0 && tempy <15) //tempx >=0 && tempx <15  &&
				{
						if( !bGetChessDisplaySta(cChPiece[tempx][tempy]))//  &&  bit.X!=tempx && bit.Y!=tempy )
						{
							//返回禁手，此棋位舍弃！！
							if(CheckGameSta(cChPiece[tempx][tempy],whobtemp,
								MachForbFlagTemp,MachWinstaTemp,machGameStaTemp,scorTempFA) )
							{	
							//	bool whotemp =0;	
									if(whobtemp){	whot =0;}
									else {whot =1;}
									if(CheckGameSta(cChPiece[tempx][tempy],whot,
									MachForbFlagTemp,MachWinstaTemp,machGameStaTemp,scorTempBb))	//假如该处为反棋是否成重要棋子
									{//修改反的了
										if( machGameStaTemp> 2000 )
										scorTempBb  += machGameStaTemp;
									}					
									p_st->Score = scorTempFA + scorTempBb/2;
									p_st->X = 	tempx;	//记录棋子的虚拟坐标
									p_st->Y = 	tempy;
									p_st++;
									cnt++;    //直接放数组坐标自加  访问不 了  [0][0]
							}
						}
				}
			}
		}
			
		tempy =lastBitTemp.Y -(radtemp +2) ;  //-2 que 行   剩余点
		if( tempy >=0 ) //&& tempy <15)
		{
			for(tempx =lastBitTemp.X -(radtemp +1) ; tempx<lastBitTemp.X +(radtemp +2) ;tempx++)
			{
				//bitY ++;
				if(tempx >=0 && tempx <15  )
				{
						if( !bGetChessDisplaySta(cChPiece[tempx][tempy]))//  &&  bit.X!=tempx && bit.Y!=tempy )
						{
							//返回禁手，此棋位舍弃！！
							if(CheckGameSta(cChPiece[tempx][tempy],whobtemp,
								MachForbFlagTemp,MachWinstaTemp,machGameStaTemp,scorTempFA) )
							{	
							//	bool whotemp =0;
									if(whobtemp){	whot =0;}
									else {whot =1;}
									if(CheckGameSta(cChPiece[tempx][tempy],whot,
									MachForbFlagTemp,MachWinstaTemp,machGameStaTemp,scorTempBb))	//假如该处为反棋是否成重要棋子
									{//修改反的了
										if( machGameStaTemp> 2000 )
										scorTempBb  += machGameStaTemp;
									}					
									p_st->Score = scorTempFA + scorTempBb/2;
									p_st->X = 	tempx;	//记录棋子的虚拟坐标
									p_st->Y = 	tempy;
									p_st++;
									cnt++;    //直接放数组坐标自加  访问不 了  [0][0]
							}
						}
				}
			}
		}

		tempy =lastBitTemp.Y +(radtemp +2) ;  //+2行  剩余点
		if( tempy <15) // && tempy >=0 &&
		{
			for(tempx =lastBitTemp.X -(radtemp +1) ; tempx<lastBitTemp.X +(radtemp +2) ;tempx++)
			{
				//bitY ++;
				if(tempx >=0 && tempx <15  ) //&& tempy >=0 && tempy <15
				{
						if( !bGetChessDisplaySta(cChPiece[tempx][tempy]) )// &&  bit.X!=tempx && bit.Y!=tempy )
						{
							if(CheckGameSta(cChPiece[tempx][tempy],whobtemp,
								MachForbFlagTemp,MachWinstaTemp,machGameStaTemp,scorTempFA) )
							{	
								if(whobtemp){	whot =0;}
									else {whot =1;}
									if(CheckGameSta(cChPiece[tempx][tempy],whot,
									MachForbFlagTemp,MachWinstaTemp,machGameStaTemp,scorTempBb))	//假如该处为反棋是否成重要棋子
									{//修改反的了
										if( machGameStaTemp> 2000 )
										scorTempBb  += machGameStaTemp;
									}					
									p_st->Score = scorTempFA + scorTempBb/2;
									p_st->X = 	tempx;	//记录棋子的虚拟坐标
									p_st->Y = 	tempy;
									p_st++;
									cnt++;    //直接放数组坐标自加  访问不 了  [0][0]
							}
							//返回禁手，此棋位舍弃！！
						//	if(CheckGameSta(cChPiece[tempx][tempy],whobtemp,
						//		MachForbFlagTemp,MachWinstaTemp,machGameStaTemp,p_st->Score))
						//	{
						//			p_st->X = 	tempx;	//记录棋子的虚拟坐标
						//			p_st->Y = 	tempy;
						//			p_st++;
						//			cnt++;    //直接放数组坐标自加  访问不 了  [0][0]
						//	}
						}
				}
			}
		}
	}
}
		
//======================================================
//  bool whoBit,      //谁走的棋，即先后手， 0-黑/ 1-白  
//  int &forbiddenSta,   //禁手状态	 jian  enum
//  int &gameSta,  //返回给下一步棋子   当步下子后的棋局
//  int &winSta)   //赢状态
//======================================================
//iGameIsWinCheck(cChessPiece &bit, bool whoBit,  int &forbiddenSta,   	  int &gameSta,  int &winSta);

//check   bool whob 传 本次下棋方
bool cChesser::MachGiveOnceStep(COORD &bit ,bool whob) //传进去的是上一步，对方所下子的虚拟位置， 返回次步所下子
{
static	COORD lastBitTemp={0,0};

	lastBitTemp.X= bit.X;
	lastBitTemp.Y= bit.Y;  // copy is  so  fault!!!!!!!

	if(!iGetReadyChessCnt())
	{//先行第一步
			bit.X=7;
			bit.Y=7;

			COORD OnceBitTemp = {16,9};  //真实物理地址
			if(!bGetChessDisplaySta(cChPiece[7][7]))//此处还未有棋子
			{
				cChPiece[7][7].SetDisplaySta(cChPiece[7][7]); //标注已下子
				PutOneBit(0 , OnceBitTemp); // 0  黑棋； 1  白棋
				cChPiece[7][7].SetWOrBSta(cChPiece[7][7], 0); //
			}
			return 1;	
	}
	else if( whob && (1==iGetReadyChessCnt()))  //ji hou xing  di yi bu 
	{//后行第一步VirtualToPhyBit(int &virX,int &virY ,COORD &physical)//将棋子对象的标号x，y  变换为 物理的坐标
	//	COORD bitTwo ={0,0};
		COORD bitTempT={0,0};  //物理地址
	int	 virtX =bit.X;
	int	 virtY =bit.Y;
	//		bitTwo.Y =bit.Y;
			if(++ virtX <15)
			{
				VirtualToPhyBit(virtX , virtY ,bitTempT);
			}
			else if((virtX-2) >0)  //若上一步不行，次步加两步
			{
				virtX = virtX-2;
				VirtualToPhyBit(virtX , virtY  ,bitTempT);
			}else if(virtY<15)
			{
				VirtualToPhyBit(virtX , virtY,bitTempT);
			}
			else if((virtY-2) >0)  //若上一步不行，次步加两步
			{
				virtY = virtY-2;
				VirtualToPhyBit(virtX , virtY ,bitTempT);
			}else 
			{
				int tttw = 0;
				do
				{
				 tttw = rand();
				}
				while( virtY==tttw );
				virtY += tttw%2;  //产生一个不同的y
				VirtualToPhyBit(virtX , virtY ,bitTempT);
			}
//PhyToVirtualBit(COORD &physical, int &virX,int &virY)//将物理的坐标 变换为棋子对象的标号x，y
		//	COORD OnceBitTemp = {0,0};  //真实物理地址

			if(!bGetChessDisplaySta(cChPiece[virtX][virtY]))//此处还未有棋子
			{
				cChPiece[virtX][virtY].SetDisplaySta(cChPiece[virtX][virtY]); //标注已下子
				PutOneBit(1 , bitTempT); // 0  黑棋； 1  白棋
				cChPiece[virtX][virtY].SetWOrBSta(cChPiece[virtX][virtY], 1); //
			}
			return 1;	
	
	}
	else
	{

//========================
// 两种机器下棋搜索范围    
#ifdef  RadiusOptionTwo
		static int conRadiusNum = 2;
		 scoreAndBit scoretemp[25]={ {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
							{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
							{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
							{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
							{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
							};
#endif
#ifdef  RadiusOptionThree

		static int conRadiusNum = 3;
			scoreAndBit scoretemp[49]={{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},{0,0,0}, {0,0,0}, 
				{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},{0,0,0}, {0,0,0}, 
				{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},{0,0,0}, {0,0,0}, 
				{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},{0,0,0}, {0,0,0}, 
				{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},{0,0,0}, {0,0,0}, 
				{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},{0,0,0}, {0,0,0}, 
				{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},{0,0,0}, {0,0,0}, 
				};
#endif

#ifdef  RadiusOptionFour

		static int conRadiusNum = 4;
			scoreAndBit scoretemp[81]={{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, 
				{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, 
				{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, 
				{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, 
				{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, 
				{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, 
				{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, 
				{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, 
				{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, 
				};
#endif
#ifdef  RadiusOptionFive

		static int conRadiusNum = 5;
			scoreAndBit scoretemp[121]={
				{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
				{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
				{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
				{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
				{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
				{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
				{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
				{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
				{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
				{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
				{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},{0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0}, {0,0,0},
				};
#endif


		 int Scorcnt =0;
	//	Scorcnt =0;    //下次禁手先用
	//	int bitX =0, bitY =0;
		int tempx=0;
		int tempy=0;

		int MachForbFlag = 0;
		int MachWinsta = NoneWin;
		int machGameSta = 0;

		for(tempx =lastBitTemp.X -1 ; tempx<lastBitTemp.X +2 ;tempx++)
		{
			//bitX ++;
			for(tempy =lastBitTemp.Y -1 ; tempy<lastBitTemp.Y +2 ;tempy++)
			{
				//bitY ++;
				if((tempx >=0) & (tempx <15)  && (tempy >=0) & (tempy <15))
				{
						if( !bGetChessDisplaySta(cChPiece[tempx][tempy]) ) //&&  ((bit.X==tempx) &( bit.X==tempy)) )
						{
							if((bit.X==tempx) &&( bit.Y==tempy))	break;
							//scoretemp[Scorcnt].orderCnt = Scorcnt;
						//	CheckGameSta(cChPiece[bit.X][bit.X],whob,MachForbFlag,MachWinsta,machGameSta,scoretemp[Scorcnt].Score);
						//	MarkbitScoreer(conRadiusOption,whob, cChPiece[bit.X][bit.X] ,scoretemp[Scorcnt].Score);
							//返回禁手，此棋位舍弃！！
							int scorTempFA = 0;
							int scorTempBb = 0;
							if(CheckGameSta(cChPiece[tempx][tempy],whob,
								MachForbFlag,MachWinsta,machGameSta,scorTempFA) )
							{
									bool whotemp =0;
									if(whob){	whotemp =0;}
									else {whotemp =1;}
									if(CheckGameSta(cChPiece[tempx][tempy],whotemp,
									MachForbFlag,MachWinsta,machGameSta,scorTempBb))	//假如该处为反棋是否成重要棋子
									{//修改反的了
										if( machGameSta> 2000 )
										scorTempBb  += machGameSta;
									}							
									scoretemp[Scorcnt].Score = scorTempFA + scorTempBb/2;
									scoretemp[Scorcnt].X = 	tempx;	//记录棋子的虚拟坐标
									scoretemp[Scorcnt].Y = 	tempy;
									Scorcnt++;    //直接放数组坐标自加  访问不 了  [0][0]
									//scoretemp[Scorcnt].flag = 1;
									//scoretemp[Scorcnt].orderCnt = Scorcnt++;  //默认分数顺序
							}
						}
				}
			}
		}

	checkCaseOption(conRadiusNum, bit, whob, 
								MachForbFlag,
								MachWinsta, 
								machGameSta,
								&scoretemp[Scorcnt],
								Scorcnt);

/*
	//-2 列
		tempx =lastBitTemp.X -2 ;
		if(tempx >=0  ) //&& tempx <15
		{
			for(tempy =lastBitTemp.Y -2 ; tempy<lastBitTemp.Y +3 ;tempy++)
			{
				//bitY ++;
				if( tempy >=0 && tempy <15)
				{
						if( !bGetChessDisplaySta(cChPiece[tempx][tempy]))//  &&  bit.X!=tempx && bit.Y!=tempy )
						{
						//	scoretemp[Scorcnt].orderCnt = Scorcnt;
						//	MarkbitScoreer(conRadiusOption,whob, cChPiece[bit.X][bit.X] ,scoretemp[Scorcnt].Score);
							//返回禁手，此棋位舍弃！！
							if(CheckGameSta(cChPiece[tempx][tempy],whob,
								MachForbFlag,MachWinsta,machGameSta,scoretemp[Scorcnt].Score))
							{
									scoretemp[Scorcnt].X = 	tempx;	//记录棋子的虚拟坐标
									scoretemp[Scorcnt].Y = 	tempy;
									Scorcnt++;    //直接放数组坐标自加  访问不 了  [0][0]
									//scoretemp[Scorcnt].flag = 1;
									//scoretemp[Scorcnt].orderCnt = Scorcnt++;  //默认分数顺序
							}
						}
				}
			}
		}
		// +2 列
		tempx =lastBitTemp.X +2 ;
		if(tempx <15 ) // &&  tempx >=0 && 
		{
			for(tempy =lastBitTemp.Y -2 ; tempy<lastBitTemp.Y +3 ;tempy++)
			{
				//bitY ++;
				if( tempy >=0 && tempy <15) //tempx >=0 && tempx <15  &&
				{
						if( !bGetChessDisplaySta(cChPiece[tempx][tempy]))//  &&  bit.X!=tempx && bit.Y!=tempy )
						{
							//scoretemp[Scorcnt].orderCnt = Scorcnt;
							//MarkbitScoreer(conRadiusOption,whob, cChPiece[bit.X][bit.X] ,scoretemp[Scorcnt].Score);
							//返回禁手，此棋位舍弃！！
							if(CheckGameSta(cChPiece[tempx][tempy],whob,
								MachForbFlag,MachWinsta,machGameSta,scoretemp[Scorcnt].Score))
							{
									scoretemp[Scorcnt].X = 	tempx;	//记录棋子的虚拟坐标
									scoretemp[Scorcnt].Y = 	tempy;
									Scorcnt++;    //直接放数组坐标自加  访问不 了  [0][0]
									//scoretemp[Scorcnt].flag = 1;
									//scoretemp[Scorcnt].orderCnt = Scorcnt++;  //默认分数顺序
							}
						}
				}
			}
		}
			
		tempy =lastBitTemp.Y -2 ;  //-2 que 行
		if( tempy >=0 ) //&& tempy <15)
		{
			for(tempx =lastBitTemp.X -1 ; tempx<lastBitTemp.X +2 ;tempx++)
			{
				//bitY ++;
				if(tempx >=0 && tempx <15  )
				{
						if( !bGetChessDisplaySta(cChPiece[tempx][tempy]))//  &&  bit.X!=tempx && bit.Y!=tempy )
						{
							//scoretemp[Scorcnt].orderCnt = Scorcnt;
							//MarkbitScoreer(conRadiusOption,whob, cChPiece[bit.X][bit.X] ,scoretemp[Scorcnt].Score);
							//返回禁手，此棋位舍弃！！
							if(CheckGameSta(cChPiece[tempx][tempy],whob,
								MachForbFlag,MachWinsta,machGameSta,scoretemp[Scorcnt].Score))
							{
									scoretemp[Scorcnt].X = 	tempx;	//记录棋子的虚拟坐标
									scoretemp[Scorcnt].Y = 	tempy;
									Scorcnt++;    //直接放数组坐标自加  访问不 了  [0][0]
									//scoretemp[Scorcnt].flag = 1;
									//scoretemp[Scorcnt].orderCnt = Scorcnt++;  //默认分数顺序
							}
						}
				}
			}
		}

		tempy =lastBitTemp.Y +2 ;  //+2行
		if( tempy <15) // && tempy >=0 &&
		{
			for(tempx =lastBitTemp.X -1 ; tempx<lastBitTemp.X +2 ;tempx++)
			{
				//bitY ++;
				if(tempx >=0 && tempx <15  ) //&& tempy >=0 && tempy <15
				{
						if( !bGetChessDisplaySta(cChPiece[tempx][tempy]) )// &&  bit.X!=tempx && bit.Y!=tempy )
						{
							//scoretemp[Scorcnt].orderCnt = Scorcnt;
						//	MarkbitScoreer(conRadiusOption,whob, cChPiece[bit.X][bit.X] ,scoretemp[Scorcnt].Score);
							//返回禁手，此棋位舍弃！！
							if(CheckGameSta(cChPiece[tempx][tempy],whob,
								MachForbFlag,MachWinsta,machGameSta,scoretemp[Scorcnt].Score))
							{
									scoretemp[Scorcnt].X = 	tempx;	//记录棋子的虚拟坐标
									scoretemp[Scorcnt].Y = 	tempy;
									Scorcnt++;    //直接放数组坐标自加  访问不 了  [0][0]
									//scoretemp[Scorcnt].flag = 1;
									//scoretemp[Scorcnt].orderCnt = Scorcnt++;  //默认分数顺序
							}
						}
				}
			}
		}
		
#ifdef  RadiusOptionFour

	//-3 列
		tempx =lastBitTemp.X -3 ;
		if(tempx >=0  ) //&& tempx <15
		{
			for(tempy =lastBitTemp.Y -3 ; tempy<lastBitTemp.Y +4 ;tempy++)
			{
				//bitY ++;
				if( tempy >=0 && tempy <15)
				{
						if( !bGetChessDisplaySta(cChPiece[tempx][tempy]))//  &&  bit.X!=tempx && bit.Y!=tempy )
						{
							//返回禁手，此棋位舍弃！！
							if(CheckGameSta(cChPiece[tempx][tempy],whob,
								MachForbFlag,MachWinsta,machGameSta,scoretemp[Scorcnt].Score))
							{
									scoretemp[Scorcnt].X = 	tempx;	//记录棋子的虚拟坐标
									scoretemp[Scorcnt].Y = 	tempy;
									Scorcnt++;    //直接放数组坐标自加  访问不 了  [0][0]
							}
						}
				}
			}
		}
		// +3 列
		tempx =lastBitTemp.X +3 ;
		if(tempx <15 ) // &&  tempx >=0 && 
		{
			for(tempy =lastBitTemp.Y -3 ; tempy<lastBitTemp.Y +4 ;tempy++)
			{
				//bitY ++;
				if( tempy >=0 && tempy <15) //tempx >=0 && tempx <15  &&
				{
						if( !bGetChessDisplaySta(cChPiece[tempx][tempy]))//  &&  bit.X!=tempx && bit.Y!=tempy )
						{
							//返回禁手，此棋位舍弃！！
							if(CheckGameSta(cChPiece[tempx][tempy],whob,
								MachForbFlag,MachWinsta,machGameSta,scoretemp[Scorcnt].Score))
							{
									scoretemp[Scorcnt].X = 	tempx;	//记录棋子的虚拟坐标
									scoretemp[Scorcnt].Y = 	tempy;
									Scorcnt++;    //直接放数组坐标自加  访问不 了  [0][0]
							}
						}
				}
			}
		}
			
		tempy =lastBitTemp.Y -3 ;  //-3 que 行   剩余点
		if( tempy >=0 ) //&& tempy <15)
		{
			for(tempx =lastBitTemp.X -2 ; tempx<lastBitTemp.X +3 ;tempx++)
			{
				//bitY ++;
				if(tempx >=0 && tempx <15  )
				{
						if( !bGetChessDisplaySta(cChPiece[tempx][tempy]))//  &&  bit.X!=tempx && bit.Y!=tempy )
						{
							//scoretemp[Scorcnt].orderCnt = Scorcnt;
							//MarkbitScoreer(conRadiusOption,whob, cChPiece[bit.X][bit.X] ,scoretemp[Scorcnt].Score);
							//返回禁手，此棋位舍弃！！
							if(CheckGameSta(cChPiece[tempx][tempy],whob,
								MachForbFlag,MachWinsta,machGameSta,scoretemp[Scorcnt].Score))
							{
									scoretemp[Scorcnt].X = 	tempx;	//记录棋子的虚拟坐标
									scoretemp[Scorcnt].Y = 	tempy;
									Scorcnt++;    //直接放数组坐标自加  访问不 了  [0][0]
									//scoretemp[Scorcnt].flag = 1;
									//scoretemp[Scorcnt].orderCnt = Scorcnt++;  //默认分数顺序
							}
						}
				}
			}
		}

		tempy =lastBitTemp.Y +3 ;  //+3行  剩余点
		if( tempy <15) // && tempy >=0 &&
		{
			for(tempx =lastBitTemp.X -2 ; tempx<lastBitTemp.X +3 ;tempx++)
			{
				//bitY ++;
				if(tempx >=0 && tempx <15  ) //&& tempy >=0 && tempy <15
				{
						if( !bGetChessDisplaySta(cChPiece[tempx][tempy]) )// &&  bit.X!=tempx && bit.Y!=tempy )
						{
							//scoretemp[Scorcnt].orderCnt = Scorcnt;
						//	MarkbitScoreer(conRadiusOption,whob, cChPiece[bit.X][bit.X] ,scoretemp[Scorcnt].Score);
							//返回禁手，此棋位舍弃！！
							if(CheckGameSta(cChPiece[tempx][tempy],whob,
								MachForbFlag,MachWinsta,machGameSta,scoretemp[Scorcnt].Score))
							{
									scoretemp[Scorcnt].X = 	tempx;	//记录棋子的虚拟坐标
									scoretemp[Scorcnt].Y = 	tempy;
									Scorcnt++;    //直接放数组坐标自加  访问不 了  [0][0]
									//scoretemp[Scorcnt].flag = 1;
									//scoretemp[Scorcnt].orderCnt = Scorcnt++;  //默认分数顺序
							}
						}
				}
			}
		}
		
#endif
*/
		int sortd = Scorcnt /2;
		cChPiece[0][0].shellSort(scoretemp ,sortd ,Scorcnt);

		bit.X =scoretemp[Scorcnt-1].X;
		bit.Y =scoretemp[Scorcnt-1].Y;

		COORD phyTemp={0,0};  //物理地址  下子
		VirtualToPhyBit(scoretemp[Scorcnt-1].X, scoretemp[Scorcnt-1].Y , phyTemp);
	//--------------------------------------------
		if(!bGetChessDisplaySta(cChPiece[bit.X][bit.Y]))//此处还未有棋子
		{
			cChPiece[bit.X][bit.Y].SetDisplaySta(cChPiece[bit.X][bit.Y]); //标注已下子

			if(!whob){
				PutOneBit(0 , phyTemp); // 0  黑棋； 1  白棋
				cChPiece[bit.X][bit.Y].SetWOrBSta(cChPiece[bit.X][bit.Y], 0); //
			}
			else{
				PutOneBit(1 , phyTemp); // 0  黑棋； 1  白棋
				cChPiece[bit.X][bit.Y].SetWOrBSta(cChPiece[bit.X][bit.Y], 1);
			}
		}
	}
	return true;
}



//int radii,cChessPiece &bAi ,cChessPiece &nextBit,int &retScore
void cChesser::MarkbitScoreer(int radii ,  //评分半径
							  bool whoBit,
							cChessPiece &bAi ,  //上次下棋点
						//	cChessPiece &nextBit, //下次最优下棋点
							int &retScore)   //下完上次棋得到的分
{
	int raditemp=0;  //搜索半径temp

	int retS = 0;
	int retPlus = 0;
	int ret = 0;  // ret  = retS- retPlus ;
	int virt_x=0,virt_y=0;   //保存传入位置
	bool bIfxOutside = 0,bIfyOutside = 0;	//出界标志位
//	forbiddenSta= 0;  //将禁手标志清零，防止误判，禁手标志从1开始
//	winSta = NoneWin;
	//        N
	//      W   E
	//        S
	int bit_NS_rowNum = 0;		// 默认0子，改用 do- while  
	int bit_NW_rowNum = 0, bit_WE_rowNum = 0, bit_WS_rowNum = 0;  //该行的同色棋子个数
	int NS_lastNoneNum = 0;  //同行棋子 尾  空棋位个数
	int NW_lastNoneNum = 0,WE_lastNoneNum = 0,WS_lastNoneNum = 0;
	int NS_OneGapBit = 0;  //跳子有同色棋
	int NW_OneGapBit = 0,WE_OneGapBit = 0,WS_OneGapBit = 0;
	int NS_GameSta =0;  // 棋局状态 ：eg ，活四， 活三 。。
	int NW_GameSta =0 ,WE_GameSta =0 ,WS_GameSta =0;

	bool NS_lastNoneFlagFore = 0, NS_lastNoneFlagBlack =0;  //前后有空棋标志位
	bool NW_lastNoneFlagFore = 0, NW_lastNoneFlagBlack =0;  //前后有空棋标志位
	bool WE_lastNoneFlagFore = 0, WE_lastNoneFlagBlack =0;  //前后有空棋标志位
	bool WS_lastNoneFlagFore = 0, WS_lastNoneFlagBlack =0;  //前后有空棋标志位

	int virt_xtemp= bAi.m_virX;
	int virt_ytemp= bAi.m_virY;

	virt_x = virt_xtemp;  //保存以备用
	virt_y = virt_ytemp;
	
//--start NS----------------------------------------------------------------------------------------------
//	int retS = 0;
//	int retPlus = 0;

	virt_xtemp = virt_x; 
	virt_ytemp = virt_y;
	raditemp=0;  //搜索半径temp

	do  //up&&down
	{ //up
		raditemp +=1;
		bit_NS_rowNum +=1;
		virt_ytemp -=1;
		if(virt_ytemp<0)	
		{//碰界退出
			bIfyOutside = 1;
			break; 
		}
	}while((raditemp <radii) && cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)));  //有子 并等于所下颜色的子， +1

	if((raditemp <radii) && !bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit， 未出界，考虑活棋 
	{//考虑有几个空白棋位  ,暂时只考虑两位
		raditemp +=1;
		NS_lastNoneNum +=1;  
		NS_lastNoneFlagFore = 1;
		virt_ytemp -=1;  // see next  bit if none 
		if((raditemp <radii) &&virt_ytemp>=0)   //note：一个空棋位之后，可能还会出项一个自己的同色棋!!
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  NS_lastNoneNum +=1;
			else    //跳一格后有子
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //跳子同色
				{
					NS_OneGapBit = 1;   //前半部分有一子跳子棋
				}
			}
		}
	}
	
	virt_xtemp = virt_x; 
	virt_ytemp = virt_y;
	bIfyOutside = 0;  //清边界
	virt_ytemp +=1;  //移位
	raditemp =0;

	//up&&down
	//------down // 反向不能够 先+1，  用while 
	while((raditemp <radii) && 
		cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)))
	{  //有子 并等于所下颜色的子， +1
		//只有当反色或者无子的时候才会退出while循环（除了边界））
		raditemp +=1;
		bit_NS_rowNum +=1;
		virt_ytemp +=1;
		if(virt_ytemp>14)	
		{//碰界退出
			bIfyOutside = 1;
			break; 
		}
	}

	//--start--考虑棋子尾 空白位问题
	if((raditemp <radii) && 
		!bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit， 未出界，考虑活棋 
	{//考虑有几个空白棋位  ,暂时只考虑两位
		raditemp +=1;
		NS_lastNoneNum +=1;
		NS_lastNoneFlagBlack =1;
		virt_ytemp +=1;  // see next  bit if none 
		if((raditemp <radii) &&
			virt_ytemp<15)
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  NS_lastNoneNum +=1;
			else    //跳一格后有子
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //跳子同色
				{
					NS_OneGapBit += 1;   //后半部分有一子跳子棋
				}
			}
		}
				
	}
	//--end--考虑棋子尾 空白位问题

	//-------check-start---
	if(bit_NS_rowNum>=5) // check the bit number in a row;  
	{
		retS +=fiveScore;
	}else if(4 == bit_NS_rowNum  )
	{
		if(NS_lastNoneFlagBlack & NS_lastNoneFlagFore)
		{//live 4
			retS +=liveFour;
		}else if((NS_lastNoneFlagBlack & !NS_lastNoneFlagFore) 
			||(!NS_lastNoneFlagBlack & NS_lastNoneFlagFore))
		{//sigle 4
			retS +=sigleFour;
		}

	}else if(3 == bit_NS_rowNum)
	{
		if(NS_lastNoneFlagBlack & NS_lastNoneFlagFore)
		{//live 3
			retS +=liveThree;
		}else if( ((NS_lastNoneFlagBlack & !NS_lastNoneFlagFore ) 
			||(!NS_lastNoneFlagBlack & NS_lastNoneFlagFore))&& NS_OneGapBit)   //三只，跳一位还有  单4
		{//sigle 4
			retS +=sigleFour;
		}
		else if(((NS_lastNoneFlagBlack & !NS_lastNoneFlagFore ) 
			||(!NS_lastNoneFlagBlack & NS_lastNoneFlagFore))&& !NS_OneGapBit && (NS_lastNoneNum>=2))
		{//s3
			retS +=sigleThree;
		}
//		if(NS_lastNoneNum >=2) //在 连棋4个，两边总共空棋位大于2，时 可以为 活四
//		{
//			NS_GameSta = FreedomOfFour;
//		}
	}else if(2 == bit_NS_rowNum)
	{
		if((NS_lastNoneNum >=4)&& (NS_lastNoneFlagBlack & NS_lastNoneFlagFore))  //在 连棋2个，两边总共空棋位大于等于4，时 可以为 活2     空空××空空
		{//liv2
			retS +=liveTwo;
		}
		else if((NS_lastNoneNum >=4)&& ((!NS_lastNoneFlagBlack & NS_lastNoneFlagFore) || (NS_lastNoneFlagBlack & !NS_lastNoneFlagFore)))  //
		{//s2
			retS +=sigleTwo;
		}
	}else if(1 == bit_NS_rowNum)
	{
		if((NS_lastNoneNum >=4)&& (NS_lastNoneFlagBlack & NS_lastNoneFlagFore))  //在 连棋2个，两边总共空棋位大于等于4，时 可以为 活2     空空××空空
		{//liv1
			retS +=liveOne;
		}
		else if((NS_lastNoneNum >=4)&& 
			((!NS_lastNoneFlagBlack & NS_lastNoneFlagFore) || (NS_lastNoneFlagBlack & !NS_lastNoneFlagFore)))  //
		{//s2
			retS +=sigleOne;
		}
	}

	// check  plus  bit Score



	//------end check-------

//--end NS----------------------------------------------------------------------------------------

//=================================

//--start NW&&SE----------------------------------------------------------------------------------
	virt_xtemp = virt_x; 
	virt_ytemp = virt_y;
	raditemp=0;  //搜索半径temp

	do  //NW&&SE
	{ //NW
		raditemp +=1;
		bit_NW_rowNum +=1;
		virt_ytemp -=1;
		virt_xtemp -=1;
		if(virt_ytemp<0)	
		{//碰界退出
			bIfyOutside = 1;
			break; 
		}
		if(virt_xtemp<0)	
		{//碰界退出
			bIfxOutside = 1;
			break; 
		}
	}while((raditemp <radii) &&cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)));  //有子 并等于所下颜色的子， +1

	if((raditemp <radii) && !bIfxOutside && !bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit， 未出界，考虑活棋 
	{//考虑有几个空白棋位  ,暂时只考虑两位
		raditemp +=1;
		NW_lastNoneNum +=1;
		virt_ytemp -=1;  // see next  bit if none 
		virt_xtemp -=1; 
		if((raditemp <radii) &&(virt_ytemp>=0) &&(virt_xtemp>=0))   //note：一个空棋位之后，可能还会出项一个自己的同色棋!!
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  NW_lastNoneNum +=1;
			else    //跳一格后有子
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //跳子同色
				{
					NW_OneGapBit = 1;   //前半部分有一子跳子棋
				}
			}
		}
	}
	
	virt_xtemp = virt_x;   //复原值
	virt_ytemp = virt_y;
	bIfxOutside = 0;  //清边界
	bIfyOutside = 0;  //清边界
	virt_ytemp += 1;  //移位
	virt_xtemp += 1;  //移位

	raditemp =0;

	////NW&&SE
	//------SE // 反向不能够 先+1，  用while 
	while((raditemp <radii) && 
		cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)))
	{  //有子 并等于所下颜色的子， +1
		//只有当反色或者无子的时候才会退出while循环（除了边界））
		raditemp +=1;
		bit_NW_rowNum +=1;
		virt_ytemp +=1;
		virt_xtemp +=1;
		if(virt_ytemp>14)	
		{//碰界退出
			bIfyOutside = 1;
			break; 
		}
		if(virt_xtemp>14)	
		{//碰界退出
			bIfxOutside = 1;
			break; 
		}
	}

	//--start--考虑棋子尾 空白位问题
	if((raditemp <radii) && 
		!bIfxOutside && !bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit， 未出界，考虑活棋 
	{//考虑有几个空白棋位  ,暂时只考虑两位
		raditemp +=1;
		NW_lastNoneNum +=1;
		virt_ytemp +=1;  // see next  bit if none 
		virt_xtemp +=1;  // see next  bit if none 
		if((raditemp <radii) && (virt_ytemp<15)&&(virt_xtemp<15))
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  NW_lastNoneNum +=1;
			else    //跳一格后有子
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //跳子同色
				{
					NW_OneGapBit += 1;   //后半部分有一子跳子棋
				}
			}
		}
				
	}
	//--end--考虑棋子尾 空白位问题

	//-------check-start---
	if(bit_NW_rowNum>=5) // check the bit number in a row;  
	{
		retS +=fiveScore;
	}else if(4 == bit_NW_rowNum  )
	{
		if(NW_lastNoneFlagBlack & NW_lastNoneFlagFore)
		{//live 4
			retS +=liveFour;
		}else if((NW_lastNoneFlagBlack & !NW_lastNoneFlagFore) 
			||(!NW_lastNoneFlagBlack & NW_lastNoneFlagFore))
		{//sigle 4
			retS +=sigleFour;
		}

	}else if(3 == bit_NW_rowNum)
	{
		if(NW_lastNoneFlagBlack & NW_lastNoneFlagFore)
		{//live 3
			retS +=liveThree;
		}else if( ((NW_lastNoneFlagBlack & !NW_lastNoneFlagFore ) 
			||(!NW_lastNoneFlagBlack & NW_lastNoneFlagFore))&& NW_OneGapBit)   //三只，跳一位还有  单4
		{//sigle 4
			retS +=sigleFour;
		}
		else if(((NW_lastNoneFlagBlack & !NW_lastNoneFlagFore ) 
			||(!NW_lastNoneFlagBlack & NW_lastNoneFlagFore))&& !NW_OneGapBit && (NW_lastNoneNum>=2))
		{//s3
			retS +=sigleThree;
		}
//		if(NS_lastNoneNum >=2) //在 连棋4个，两边总共空棋位大于2，时 可以为 活四
//		{
//			NS_GameSta = FreedomOfFour;
//		}
	}else if(2 == bit_NW_rowNum)
	{
		if((NW_lastNoneNum >=4)&& (NW_lastNoneFlagBlack & NW_lastNoneFlagFore))  //在 连棋2个，两边总共空棋位大于等于4，时 可以为 活2     空空××空空
		{//liv2
			retS +=liveTwo;
		}
		else if((NW_lastNoneNum >=4)&& 
			((!NW_lastNoneFlagBlack & NW_lastNoneFlagFore) || (NW_lastNoneFlagBlack & !NW_lastNoneFlagFore)))  //
		{//s2
			retS +=sigleTwo;
		}
	}else if(1 == bit_NW_rowNum)
	{
		if((NW_lastNoneNum >=4)&& (NW_lastNoneFlagBlack & NW_lastNoneFlagFore))  //在 连棋2个，两边总共空棋位大于等于4，时 可以为 活2     空空××空空
		{//liv1
			retS +=liveOne;
		}
		else if((NW_lastNoneNum >=4)&& 
			((!NW_lastNoneFlagBlack & NW_lastNoneFlagFore) || (NW_lastNoneFlagBlack & !NW_lastNoneFlagFore)))  //
		{//s2
			retS +=sigleOne;
		}
	}
	//------end check-------

//--end NW&&SE-----------------------------------------------------------------------------------------------

//--start WE-----------------------------------------------------------------------------------------------
	virt_xtemp = virt_x; 
	virt_ytemp = virt_y;
	raditemp=0; 
	do  //WE
	{ //WE
		raditemp +=1;
		bit_WE_rowNum +=1;
	//	virt_ytemp -=1;
		virt_xtemp -=1;	//x-1, y 不变
	//	if(virt_ytemp<0)	
	//	{//碰界退出
	//		bIfyOutside = 1;
	//		break; 
	//	}
		if(virt_xtemp<0)	
		{//碰界退出
			bIfxOutside = 1;
			break; 
		}
	}while((raditemp <radii) && 
		cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)));  //有子 并等于所下颜色的子， +1

	if((raditemp <radii) && 
		!bIfxOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit， 未出界，考虑活棋 
	{//考虑有几个空白棋位  ,暂时只考虑两位
		raditemp +=1;
		WE_lastNoneNum +=1;
	//	virt_ytemp -=1;  // see next  bit if none 
		virt_xtemp -=1; 
		if((raditemp <radii) &&virt_xtemp>=0)   //note：一个空棋位之后，可能还会出项一个自己的同色棋!!-------------------
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  WE_lastNoneNum +=1;
			else    //跳一格后有子
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //跳子同色
				{
					WE_OneGapBit = 1;   //前半部分有一子跳子棋
				}
			}
		}
	}
	
	virt_xtemp = virt_x;   //复原值
	virt_ytemp = virt_y;
	bIfxOutside = 0;  //清边界
	virt_xtemp += 1;  //移位
		raditemp =0;

	////WE
	//------WE // 反向不能够 先+1，  用while 
	while((raditemp <radii) && 
		cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)))
	{  //有子 并等于所下颜色的子， +1
		//只有当反色或者无子的时候才会退出while循环（除了边界））
		raditemp +=1;
		bit_WE_rowNum +=1;
		virt_xtemp +=1;
		if(virt_xtemp>14)	
		{//碰界退出
			bIfxOutside = 1;
			break; 
		}
	}

	//--start--考虑棋子尾 空白位问题
	if((raditemp <radii) && 
		!bIfxOutside  && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit， 未出界，考虑活棋 
	{//考虑有几个空白棋位  ,暂时只考虑两位
		raditemp +=1;
		WE_lastNoneNum +=1;
		virt_xtemp +=1;  // see next  bit if none 
		if((raditemp <radii) &&
			virt_xtemp<15)
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  WE_lastNoneNum +=1;
			else    //跳一格后有子
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //跳子同色
				{
					WE_OneGapBit += 1;   //后半部分有一子跳子棋
				}
			}
		}
				
	}
	//--end--考虑棋子尾 空白位问题

	//-------check-start---

	if(bit_WE_rowNum>=5) // check the bit number in a row;  
	{
		retS +=fiveScore;
	}else if(4 == bit_WE_rowNum  )
	{
		if(WE_lastNoneFlagBlack & WE_lastNoneFlagFore)
		{//live 4
			retS +=liveFour;
		}else if((WE_lastNoneFlagBlack & !WE_lastNoneFlagFore) 
			||(!WE_lastNoneFlagBlack & WE_lastNoneFlagFore))
		{//sigle 4
			retS +=sigleFour;
		}

	}else if(3 == bit_WE_rowNum)
	{
		if(WE_lastNoneFlagBlack & WE_lastNoneFlagFore)
		{//live 3
			retS +=liveThree;
		}else if( ((WE_lastNoneFlagBlack & !WE_lastNoneFlagFore ) 
			||(!WE_lastNoneFlagBlack & WE_lastNoneFlagFore))&& WE_OneGapBit)   //三只，跳一位还有  单4
		{//sigle 4
			retS +=sigleFour;
		}
		else if(((WE_lastNoneFlagBlack & !WE_lastNoneFlagFore ) 
			||(!WE_lastNoneFlagBlack & WE_lastNoneFlagFore))&& !WE_OneGapBit && (WE_lastNoneNum>=2))
		{//s3
			retS +=sigleThree;
		}
//		if(NS_lastNoneNum >=2) //在 连棋4个，两边总共空棋位大于2，时 可以为 活四
//		{
//			NS_GameSta = FreedomOfFour;
//		}
	}else if(2 == bit_WE_rowNum)
	{
		if((WE_lastNoneNum >=4)&& (WE_lastNoneFlagBlack & WE_lastNoneFlagFore))  //在 连棋2个，两边总共空棋位大于等于4，时 可以为 活2     空空××空空
		{//liv2
			retS +=liveTwo;
		}
		else if((WE_lastNoneNum >=4)&& 
			((!WE_lastNoneFlagBlack & WE_lastNoneFlagFore) || (WE_lastNoneFlagBlack & !WE_lastNoneFlagFore)))  //
		{//s2
			retS +=sigleTwo;
		}
	}else if(1 == bit_WE_rowNum)
	{
		if((WE_lastNoneNum >=4)&& (WE_lastNoneFlagBlack & WE_lastNoneFlagFore))  //在 连棋2个，两边总共空棋位大于等于4，时 可以为 活2     空空××空空
		{//liv1
			retS +=liveOne;
		}
		else if((WE_lastNoneNum >=4)&& 
			((!WE_lastNoneFlagBlack & WE_lastNoneFlagFore) || (WE_lastNoneFlagBlack & !WE_lastNoneFlagFore)))  //
		{//s2
			retS +=sigleOne;
		}
	}

	//------end check-------

//--end WE-------------------------------------------------------------------------------------------------------


//--start WS&&NE--------------------------------------------------------------------------------------------------
	virt_xtemp = virt_x; 
	virt_ytemp = virt_y;
	raditemp=0;  
	do  //Ws&&NE
	{ //Ws
		raditemp +=1;
		bit_WS_rowNum +=1;
		virt_ytemp +=1;
		virt_xtemp -=1;	//x-1, y 不变
		if(virt_ytemp>14)	
		{//碰界退出
			bIfyOutside = 1;
			break; 
		}
		if(virt_xtemp<0)	
		{//碰界退出
			bIfxOutside = 1;
			break; 
		}
	}while((raditemp <radii) && 
		cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)));  //有子 并等于所下颜色的子， +1

	if((raditemp <radii) && 
		!bIfxOutside && !bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit， 未出界，考虑活棋 
	{//考虑有几个空白棋位  ,暂时只考虑两位
		raditemp +=1;
		WS_lastNoneNum +=1;
		virt_ytemp +=1;  // see next  bit if none 
		virt_xtemp -=1; 
		if((raditemp <radii) &&
			(virt_xtemp>=0)&&(virt_ytemp<15))   //note：一个空棋位之后，可能还会出项一个自己的同色棋!!-------------------
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  WS_lastNoneNum +=1;
			else    //跳一格后有子
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //跳子同色
				{
					WS_OneGapBit = 1;   //前半部分有一子跳子棋
				}
			}
		}
	}
	
	virt_xtemp = virt_x;   //复原值
	virt_ytemp = virt_y;
	bIfxOutside = 0;  //清边界
	bIfyOutside = 0;  //清边界
	virt_xtemp += 1;  //移位
	virt_ytemp -= 1;  //移位
		raditemp =0;

	////Ws&&NE
	//------NE // 反向不能够 先+1，  用while 
	while((raditemp <radii) && 
		cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)))
	{  //有子 并等于所下颜色的子， +1
		//只有当反色或者无子的时候才会退出while循环（除了边界））
		raditemp +=1;

		bit_WS_rowNum +=1;

		virt_xtemp +=1;
		virt_ytemp -= 1;  
		if(virt_xtemp>14)	
		{//碰界退出
			bIfxOutside = 1;
			break; 
		}
		if(virt_ytemp<0)	
		{//碰界退出
			bIfyOutside = 1;
			break; 
		}
	}

	//--start--考虑棋子尾 空白位问题
	if((raditemp <radii) && 
		!bIfxOutside  && !bIfyOutside  &&  !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit， 未出界，考虑活棋 
	{//考虑有几个空白棋位  ,暂时只考虑两位
		raditemp +=1;
		WS_lastNoneNum +=1;
		virt_xtemp +=1;  // see next  bit if none 
		virt_ytemp -=1;  // see next  bit if none 
		if((raditemp <radii) &&
			(virt_xtemp<15)&&(virt_ytemp>0))
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  WS_lastNoneNum +=1;
			else    //跳一格后有子
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //跳子同色
				{
					WS_OneGapBit += 1;   //后半部分有一子跳子棋
				}
			}
		}
				
	}
	//--end--考虑棋子尾 空白位问题

	//-------check-start---

	if(bit_WS_rowNum>=5) // check the bit number in a row;  
	{
		retS +=fiveScore;
	}else if(4 == bit_WS_rowNum  )
	{
		if(WS_lastNoneFlagBlack & WS_lastNoneFlagFore)
		{//live 4
			retS +=liveFour;
		}else if((WS_lastNoneFlagBlack & !WS_lastNoneFlagFore) 
			||(!WS_lastNoneFlagBlack & WS_lastNoneFlagFore))
		{//sigle 4
			retS +=sigleFour;
		}

	}else if(3 == bit_WS_rowNum)
	{
		if(WS_lastNoneFlagBlack & WS_lastNoneFlagFore)
		{//live 3
			retS +=liveThree;
		}else if( ((WS_lastNoneFlagBlack & !WS_lastNoneFlagFore ) 
			||(!WS_lastNoneFlagBlack & WS_lastNoneFlagFore))&& WS_OneGapBit)   //三只，跳一位还有  单4
		{//sigle 4
			retS +=sigleFour;
		}
		else if(((WS_lastNoneFlagBlack & !WS_lastNoneFlagFore ) 
			||(!WS_lastNoneFlagBlack & WS_lastNoneFlagFore))&& !WS_OneGapBit && (WS_lastNoneNum>=2))
		{//s3
			retS +=sigleThree;
		}
//		if(NS_lastNoneNum >=2) //在 连棋4个，两边总共空棋位大于2，时 可以为 活四
//		{
//			NS_GameSta = FreedomOfFour;
//		}
	}else if(2 == bit_WS_rowNum)
	{
		if((WS_lastNoneNum >=4)&& (WS_lastNoneFlagBlack & WS_lastNoneFlagFore))  //在 连棋2个，两边总共空棋位大于等于4，时 可以为 活2     空空××空空
		{//liv2
			retS +=liveTwo;
		}
		else if((WS_lastNoneNum >=4)&& 
			((!WS_lastNoneFlagBlack & WS_lastNoneFlagFore) || (WS_lastNoneFlagBlack & !WS_lastNoneFlagFore)))  //
		{//s2
			retS +=sigleTwo;
		}
	}else if(1 == bit_WS_rowNum)
	{
		if((WS_lastNoneNum >=4)&& (WS_lastNoneFlagBlack & WS_lastNoneFlagFore))  //在 连棋2个，两边总共空棋位大于等于4，时 可以为 活2     空空××空空
		{//liv1
			retS +=liveOne;
		}
		else if((WS_lastNoneNum >=4)&& 
			((!WS_lastNoneFlagBlack & WS_lastNoneFlagFore) || (WS_lastNoneFlagBlack & !WS_lastNoneFlagFore)))  //
		{//s2
			retS +=sigleOne;
		}
	}
	//------end check-------

//=================================================================================================
//retPlus Parts
//=================================================================================================

bIfxOutside = 0;bIfyOutside = 0;	//
//	forbiddenSta= 0;  
//	winSta = NoneWin;
	//        N
	//      W   E
	//        S
	 bit_NS_rowNum = 0;		// - do- while  
	 bit_NW_rowNum = 0; bit_WE_rowNum = 0; bit_WS_rowNum = 0;  //-
	 NS_lastNoneNum = 0;  //-
	 NW_lastNoneNum = 0;WE_lastNoneNum = 0;WS_lastNoneNum = 0;
	 NS_OneGapBit = 0;  //-
	 NW_OneGapBit = 0;WE_OneGapBit = 0;WS_OneGapBit = 0;
	 NS_GameSta =0;  // -
	 NW_GameSta =0 ;WE_GameSta =0 ;WS_GameSta =0;

	 NS_lastNoneFlagFore = 0; NS_lastNoneFlagBlack =0;  //-
	 NW_lastNoneFlagFore = 0; NW_lastNoneFlagBlack =0;  //-
	 WE_lastNoneFlagFore = 0; WE_lastNoneFlagBlack =0;  //-
	 WS_lastNoneFlagFore = 0; WS_lastNoneFlagBlack =0;  //-

	//int virt_xtemp= bAi.m_virX;
	//int virt_ytemp= bAi.m_virY;

	//virt_x = virt_xtemp;  //-
	//virt_y = virt_ytemp;
	
//--start NS----------------------------------------------------------------------------------------------
//	int retPlus = 0;
//	int retPlus = 0;

	virt_xtemp = virt_x; 
	virt_ytemp = virt_y;
	raditemp=0;  //????temp

	do  //up&&down
	{ //up
		raditemp +=1;
		bit_NS_rowNum +=1;
		virt_ytemp -=1;
		if(virt_ytemp<0)	
		{//????
			bIfyOutside = 1;
			break; 
		}
	}while((raditemp <radii) && cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit)));  // oppositely colour

	if((raditemp <radii) && !bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit, 
	{//
		raditemp +=1;
		NS_lastNoneNum +=1;  
		NS_lastNoneFlagFore = 1;
		virt_ytemp -=1;  // see next  bit if none 
		if((raditemp <radii) &&virt_ytemp>=0)   //note:
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  NS_lastNoneNum +=1;
			else    //??????
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit))  //
				{
					NS_OneGapBit = 1;   //
				}
			}
		}
	}
	
	virt_xtemp = virt_x; 
	virt_ytemp = virt_y;
	bIfyOutside = 0;  //
	virt_ytemp +=1;  //
	raditemp =0;

	//up&&down
	//------down // +1,  while 
	while((raditemp <radii) && 
		cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit)))
	{  // +1
		//while
		raditemp +=1;
		bit_NS_rowNum +=1;
		virt_ytemp +=1;
		if(virt_ytemp>14)	
		{//
			bIfyOutside = 1;
			break; 
		}
	}

	//--start--
	if((raditemp <radii) && 
		!bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit
	{//
		raditemp +=1;
		NS_lastNoneNum +=1;
		NS_lastNoneFlagBlack =1;
		virt_ytemp +=1;  // see next  bit if none 
		if((raditemp <radii) &&
			virt_ytemp<15)
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  NS_lastNoneNum +=1;
			else    //??????
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit))  //
				{
					NS_OneGapBit += 1;   //
				}
			}
		}
				
	}
	//--end--

	//-------check-start---
	if(bit_NS_rowNum>=5) // check the bit number in a row;  
	{
		retPlus +=fiveScore;
	}else if(4 == bit_NS_rowNum  )
	{
		if(NS_lastNoneFlagBlack & NS_lastNoneFlagFore)
		{//live 4
			retPlus +=liveFour;
		}else if((NS_lastNoneFlagBlack & !NS_lastNoneFlagFore) 
			||(!NS_lastNoneFlagBlack & NS_lastNoneFlagFore))
		{//sigle 4
			retPlus +=sigleFour;
		}

	}else if(3 == bit_NS_rowNum)
	{
		if(NS_lastNoneFlagBlack & NS_lastNoneFlagFore)
		{//live 3
			retPlus +=liveThree;
		}else if( ((NS_lastNoneFlagBlack & !NS_lastNoneFlagFore ) 
			||(!NS_lastNoneFlagBlack & NS_lastNoneFlagFore))&& NS_OneGapBit)   //--
		{//sigle 4
			retPlus +=sigleFour;
		}
		else if(((NS_lastNoneFlagBlack & !NS_lastNoneFlagFore ) 
			||(!NS_lastNoneFlagBlack & NS_lastNoneFlagFore))&& !NS_OneGapBit && (NS_lastNoneNum>=2))
		{//s3
			retPlus +=sigleThree;
		}
	}
	else if(2 == bit_NS_rowNum)
	{
		if((NS_lastNoneNum >=4)&& (NS_lastNoneFlagBlack & NS_lastNoneFlagFore))  //
		{//liv2
			retPlus +=liveTwo;
		}
		else if((NS_lastNoneNum >=4)&& ((!NS_lastNoneFlagBlack & NS_lastNoneFlagFore) || (NS_lastNoneFlagBlack & !NS_lastNoneFlagFore)))  //
		{//s2
			retPlus +=sigleTwo;
		}
	}else if(1 == bit_NS_rowNum)
	{
		if((NS_lastNoneNum >=4)&& (NS_lastNoneFlagBlack & NS_lastNoneFlagFore))  //
		{//liv1
			retPlus +=liveOne;
		}
		else if((NS_lastNoneNum >=4)&& 
			((!NS_lastNoneFlagBlack & NS_lastNoneFlagFore) || (NS_lastNoneFlagBlack & !NS_lastNoneFlagFore)))  //
		{//s2
			retPlus +=sigleOne;
		}
	}

	// check  plus  bit Score



	//------end check-------

//--end NS----------------------------------------------------------------------------------------

//=================================

//--start NW&&SE----------------------------------------------------------------------------------
	virt_xtemp = virt_x; 
	virt_ytemp = virt_y;
	raditemp=0;  //temp

	do  //NW&&SE
	{ //NW
		raditemp +=1;
		bit_NW_rowNum +=1;
		virt_ytemp -=1;
		virt_xtemp -=1;
		if(virt_ytemp<0)	
		{//
			bIfyOutside = 1;
			break; 
		}
		if(virt_xtemp<0)	
		{//????
			bIfxOutside = 1;
			break; 
		}
	}while((raditemp <radii) &&cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit)));  //

	if((raditemp <radii) && !bIfxOutside && !bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit, ???,???? 
	{//
		raditemp +=1;
		NW_lastNoneNum +=1;
		virt_ytemp -=1;  // see next  bit if none 
		virt_xtemp -=1; 
		if((raditemp <radii) &&(virt_ytemp>=0) &&(virt_xtemp>=0))   //note:-
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  NW_lastNoneNum +=1;
			else    //??????
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit))  //
				{
					NW_OneGapBit = 1;   //
				}
			}
		}
	}
	
	virt_xtemp = virt_x;   
	virt_ytemp = virt_y;
	bIfxOutside = 0;  //
	bIfyOutside = 0;  //
	virt_ytemp += 1;  
	virt_xtemp += 1;  

	raditemp =0;

	////NW&&SE
	//------SE // while 
	while((raditemp <radii) && 
		cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState &  whoBit)))
	{  //		
		raditemp +=1;
		bit_NW_rowNum +=1;
		virt_ytemp +=1;
		virt_xtemp +=1;
		if(virt_ytemp>14)	
		{//
			bIfyOutside = 1;
			break; 
		}
		if(virt_xtemp>14)	
		{//
			bIfxOutside = 1;
			break; 
		}
	}

	//--start--
	if((raditemp <radii) && 
		!bIfxOutside && !bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit, ???,???? 
	{//
		raditemp +=1;
		NW_lastNoneNum +=1;
		virt_ytemp +=1;  // see next  bit if none 
		virt_xtemp +=1;  // see next  bit if none 
		if((raditemp <radii) && (virt_ytemp<15)&&(virt_xtemp<15))
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  NW_lastNoneNum +=1;
			else    //
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit))  //
				{
					NW_OneGapBit += 1;   //
				}
			}
		}
				
	}
	//--end--------------------------------------------

	//-------check-start---
	if(bit_NW_rowNum>=5) // check the bit number in a row;  
	{
		retPlus +=fiveScore;
	}else if(4 == bit_NW_rowNum  )
	{
		if(NW_lastNoneFlagBlack & NW_lastNoneFlagFore)
		{//live 4
			retPlus +=liveFour;
		}else if((NW_lastNoneFlagBlack & !NW_lastNoneFlagFore) 
			||(!NW_lastNoneFlagBlack & NW_lastNoneFlagFore))
		{//sigle 4
			retPlus +=sigleFour;
		}

	}else if(3 == bit_NW_rowNum)
	{
		if(NW_lastNoneFlagBlack & NW_lastNoneFlagFore)
		{//live 3
			retPlus +=liveThree;
		}else if( ((NW_lastNoneFlagBlack & !NW_lastNoneFlagFore ) 
			||(!NW_lastNoneFlagBlack & NW_lastNoneFlagFore))&& NW_OneGapBit)   //
		{//sigle 4
			retPlus +=sigleFour;
		}
		else if(((NW_lastNoneFlagBlack & !NW_lastNoneFlagFore ) 
			||(!NW_lastNoneFlagBlack & NW_lastNoneFlagFore))&& !NW_OneGapBit && (NW_lastNoneNum>=2))
		{//s3
			retPlus +=sigleThree;
		}
	}
	else if(2 == bit_NW_rowNum)
	{
		if((NW_lastNoneNum >=4)&& (NW_lastNoneFlagBlack & NW_lastNoneFlagFore))  //
		{//liv2
			retPlus +=liveTwo;
		}
		else if((NW_lastNoneNum >=4)&& 
			((!NW_lastNoneFlagBlack & NW_lastNoneFlagFore) || (NW_lastNoneFlagBlack & !NW_lastNoneFlagFore)))  //
		{//s2
			retPlus +=sigleTwo;
		}
	}else if(1 == bit_NW_rowNum)
	{
		if((NW_lastNoneNum >=4)&& (NW_lastNoneFlagBlack & NW_lastNoneFlagFore))  // 
		{//liv1
			retPlus +=liveOne;
		}
		else if((NW_lastNoneNum >=4)&& 
			((!NW_lastNoneFlagBlack & NW_lastNoneFlagFore) || (NW_lastNoneFlagBlack & !NW_lastNoneFlagFore)))  //
		{//s2
			retPlus +=sigleOne;
		}
	}
	//------end check-------

//--end NW&&SE-----------------------------------------------------------------------------------------------

//--start WE-----------------------------------------------------------------------------------------------
	virt_xtemp = virt_x; 
	virt_ytemp = virt_y;
	raditemp=0; 
	do  //WE
	{ //WE
		raditemp +=1;
		bit_WE_rowNum +=1;
	//	virt_ytemp -=1;
		virt_xtemp -=1;	//x-1, y 
 
		if(virt_xtemp<0)	
		{//????
			bIfxOutside = 1;
			break; 
		}
	}while((raditemp <radii) && 
		cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit)));  //

	if((raditemp <radii) && 
		!bIfxOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit, 
	{// 
		raditemp +=1;
		WE_lastNoneNum +=1;
	//	virt_ytemp -=1;  // see next  bit if none 
		virt_xtemp -=1; 
		if((raditemp <radii) &&virt_xtemp>=0)   //note: ------------------
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  WE_lastNoneNum +=1;
			else    //
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState &  whoBit))  // 
				{
					WE_OneGapBit = 1;   // 
				}
			}
		}
	}
	
	virt_xtemp = virt_x;   // 
	virt_ytemp = virt_y;
	bIfxOutside = 0;  // 
	virt_xtemp += 1;  // 
		raditemp =0;

	////WE
	//------WE //  while 
	while((raditemp <radii) && 
		cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit)))
	{  
		raditemp +=1;
		bit_WE_rowNum +=1;
		virt_xtemp +=1;
		if(virt_xtemp>14)	
		{//????
			bIfxOutside = 1;
			break; 
		}
	}

	//--start--
	if((raditemp <radii) && 
		!bIfxOutside  && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit, ???,???? 
	{// 
		raditemp +=1;
		WE_lastNoneNum +=1;
		virt_xtemp +=1;  // see next  bit if none 
		if((raditemp <radii) &&
			virt_xtemp<15)
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  WE_lastNoneNum +=1;
			else    //??????
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit))  //
				{
					WE_OneGapBit += 1;   //
				}
			}
		}
				
	}
	//--end--????? ?????

	//-------check-start---

	if(bit_WE_rowNum>=5) // check the bit number in a row;  
	{
		retPlus +=fiveScore;
	}else if(4 == bit_WE_rowNum  )
	{
		if(WE_lastNoneFlagBlack & WE_lastNoneFlagFore)
		{//live 4
			retPlus +=liveFour;
		}else if((WE_lastNoneFlagBlack & !WE_lastNoneFlagFore) 
			||(!WE_lastNoneFlagBlack & WE_lastNoneFlagFore))
		{//sigle 4
			retPlus +=sigleFour;
		}

	}else if(3 == bit_WE_rowNum)
	{
		if(WE_lastNoneFlagBlack & WE_lastNoneFlagFore)
		{//live 3
			retPlus +=liveThree;
		}else if( ((WE_lastNoneFlagBlack & !WE_lastNoneFlagFore ) 
			||(!WE_lastNoneFlagBlack & WE_lastNoneFlagFore))&& WE_OneGapBit)   //??,?????  ?4
		{//sigle 4
			retPlus +=sigleFour;
		}
		else if(((WE_lastNoneFlagBlack & !WE_lastNoneFlagFore ) 
			||(!WE_lastNoneFlagBlack & WE_lastNoneFlagFore))&& !WE_OneGapBit && (WE_lastNoneNum>=2))
		{//s3
			retPlus +=sigleThree;
		}
	}else if(2 == bit_WE_rowNum)
	{
		if((WE_lastNoneNum >=4)&& (WE_lastNoneFlagBlack & WE_lastNoneFlagFore))  //
		{//liv2
			retPlus +=liveTwo;
		}
		else if((WE_lastNoneNum >=4)&& 
			((!WE_lastNoneFlagBlack & WE_lastNoneFlagFore) || (WE_lastNoneFlagBlack & !WE_lastNoneFlagFore)))  //
		{//s2
			retPlus +=sigleTwo;
		}
	}else if(1 == bit_WE_rowNum)
	{
		if((WE_lastNoneNum >=4)&& (WE_lastNoneFlagBlack & WE_lastNoneFlagFore))  //
		{//liv1
			retPlus +=liveOne;
		}
		else if((WE_lastNoneNum >=4)&& 
			((!WE_lastNoneFlagBlack & WE_lastNoneFlagFore) || (WE_lastNoneFlagBlack & !WE_lastNoneFlagFore)))  //
		{//s2
			retPlus +=sigleOne;
		}
	}

	//------end check-------

//--end WE-------------------------------------------------------------------------------------------------------


//--start WS&&NE--------------------------------------------------------------------------------------------------
	virt_xtemp = virt_x; 
	virt_ytemp = virt_y;
	raditemp=0;  
	do  //Ws&&NE
	{ //Ws
		raditemp +=1;
		bit_WS_rowNum +=1;
		virt_ytemp +=1;
		virt_xtemp -=1;	//x-1, y 
		if(virt_ytemp>14)	
		{//
			bIfyOutside = 1;
			break; 
		}
		if(virt_xtemp<0)	
		{//
			bIfxOutside = 1;
			break; 
		}
	}while((raditemp <radii) && 
		cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit)));  

	if((raditemp <radii) && 
		!bIfxOutside && !bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit, 
	{//
		raditemp +=1;
		WS_lastNoneNum +=1;
		virt_ytemp +=1;  // see next  bit if none 
		virt_xtemp -=1; 
		if((raditemp <radii) &&
			(virt_xtemp>=0)&&(virt_ytemp<15))   //note------------------
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  WS_lastNoneNum +=1;
			else    //??????
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit))  
				{
					WS_OneGapBit = 1;   
				}
			}
		}
	}
	
	virt_xtemp = virt_x;   
	virt_ytemp = virt_y;
	bIfxOutside = 0;  //
	bIfyOutside = 0;  
	virt_xtemp += 1;  
	virt_ytemp -= 1;  
		raditemp =0;

	////Ws&&NE
	//------NE // while 
	while((raditemp <radii) && 
		cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit)))
	{  //
		raditemp +=1;

		bit_WS_rowNum +=1;

		virt_xtemp +=1;
		virt_ytemp -= 1;  
		if(virt_xtemp>14)	
		{//
			bIfxOutside = 1;
			break; 
		}
		if(virt_ytemp<0)	
		{//
			bIfyOutside = 1;
			break; 
		}
	}

	//--start--
	if((raditemp <radii) && 
		!bIfxOutside  && !bIfyOutside  &&  !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit, 
	{//
		raditemp +=1;
		WS_lastNoneNum +=1;
		virt_xtemp +=1;  // see next  bit if none 
		virt_ytemp -=1;  // see next  bit if none 
		if((raditemp <radii) &&
			(virt_xtemp<15)&&(virt_ytemp>0))
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  WS_lastNoneNum +=1;
			else    //??????
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit))  
				{
					WS_OneGapBit += 1;   //
				}
			}
		}
				
	}
	//--end--

	//-------check-start---

	if(bit_WS_rowNum>=5) // check the bit number in a row;  
	{
		retPlus +=fiveScore;
	}else if(4 == bit_WS_rowNum  )
	{
		if(WS_lastNoneFlagBlack & WS_lastNoneFlagFore)
		{//live 4
			retPlus +=liveFour;
		}else if((WS_lastNoneFlagBlack & !WS_lastNoneFlagFore) 
			||(!WS_lastNoneFlagBlack & WS_lastNoneFlagFore))
		{//sigle 4
			retPlus +=sigleFour;
		}

	}else if(3 == bit_WS_rowNum)
	{
		if(WS_lastNoneFlagBlack & WS_lastNoneFlagFore)
		{//live 3
			retPlus +=liveThree;
		}else if( ((WS_lastNoneFlagBlack & !WS_lastNoneFlagFore ) 
			||(!WS_lastNoneFlagBlack & WS_lastNoneFlagFore))&& WS_OneGapBit)   //
		{//sigle 4
			retPlus +=sigleFour;
		}
		else if(((WS_lastNoneFlagBlack & !WS_lastNoneFlagFore ) 
			||(!WS_lastNoneFlagBlack & WS_lastNoneFlagFore))&& !WS_OneGapBit && (WS_lastNoneNum>=2))
		{//s3
			retPlus +=sigleThree;
		}
	}
	else if(2 == bit_WS_rowNum)
	{
		if((WS_lastNoneNum >=4)&& (WS_lastNoneFlagBlack & WS_lastNoneFlagFore))  //
		{//liv2
			retPlus +=liveTwo;
		}
		else if((WS_lastNoneNum >=4)&& 
			((!WS_lastNoneFlagBlack & WS_lastNoneFlagFore) || (WS_lastNoneFlagBlack & !WS_lastNoneFlagFore)))  //
		{//s2
			retPlus +=sigleTwo;
		}
	}else if(1 == bit_WS_rowNum)
	{
		if((WS_lastNoneNum >=4)&& (WS_lastNoneFlagBlack & WS_lastNoneFlagFore))  //
		{//liv1
			retPlus +=liveOne;
		}
		else if((WS_lastNoneNum >=4)&& 
			((!WS_lastNoneFlagBlack & WS_lastNoneFlagFore) || (WS_lastNoneFlagBlack & !WS_lastNoneFlagFore)))  //
		{//s2
			retPlus +=sigleOne;
		}
	}



//================================================================================================
	retScore = retS - retPlus;

	//return true;
}


// 对将要下的一子判断
// whobit  0  - 下的黑棋   1- 下的白棋    foebidden only for black    
// bit  虚拟棋子位  eg， cChPiece[0][0]
//---------判断输赢，包括禁手  返回有谁win 状态 winSta   0，无win   1- 黑win   2- 白win ，3-禁手，重下子 (重修)
//禁手无累积效应，仅当次有效   forbiddenSta 禁手状态
//返回棋子评价量 retScore
//中途在检测到禁手时，返回失败
//int &gameSta,  //返回给下一步棋子   当步下子后的棋局
//非赢状态下比较分数， 赢状态直接下该子
bool cChesser::CheckGameSta(cChessPiece &bit,bool whoBit,int &forbiddenSta,int &winSta,int &gameSta,int &retScore)
{

	int virt_x=0,virt_y=0;
	bool bIfxOutside = 0,bIfyOutside = 0;	//出界标志位
	forbiddenSta= 0;  //将禁手标志清零，防止误判，禁手标志从1开始
	winSta = NoneWin;
	retScore = 0;
	//        N
	//      W   E
	//        S
	int bit_NS_rowNum = 0;		// 默认0子，改用 do- while  
	int bit_NW_rowNum = 0, bit_WE_rowNum = 0, bit_WS_rowNum = 0;  //该行的同色棋子个数
	int NS_lastNoneNum = 0;  //同行棋子 尾  空棋位个数
	int NW_lastNoneNum = 0,WE_lastNoneNum = 0,WS_lastNoneNum = 0;

	// 空棋位   一边-1； 两边-2    无空边 -0；
	int NSLiveCnt =0;
	int NWLiveCnt =0, WELiveCnt =0, WSLiveCnt =0;

	int NS_OneGapBit = 0;  //跳子有同色棋
	int NW_OneGapBit = 0,WE_OneGapBit = 0,WS_OneGapBit = 0;
	int NS_GameSta =0;  // 棋局状态 ：eg ，活四， 活三 。。
	int NW_GameSta =0 ,WE_GameSta =0 ,WS_GameSta =0;

	int virt_xtemp= bit.m_virX;
	int virt_ytemp= bit.m_virY;

	virt_x = virt_xtemp;  //保存以备用
	virt_y = virt_ytemp;

	//forbidden  cnt 
	int ForbiFourCnt=0;
	int ForbiThreeCnt=0;
	
	// up 
//	if( !((virt_ytemp -1) <0) ){ // 上行未出界
//		if (cChPiece[virt_xtemp][virt_ytemp -1].m_bBitDisplayState)// 此位已下子
//		{
//			if(cChPiece[virt_xtemp][virt_ytemp -1].m_bBitWOrBState == whoBit)   //m_bBitWOrBState  0-hei  1 bai
//			bit_RowNum +=1;
//		}
//	}else{  //上行出界，反向必不出界
//		if(cChPiece[virt_xtemp][virt_ytemp +1].m_bBitDisplayState)  //bool m_bBitWOrBState;	 //棋位黑/白状态 0-黑；1-白
//	}

//--start NS----------------------------------------------------------------------------------------------
	virt_xtemp = virt_x; 
	virt_ytemp = virt_y;
	do  //up&&down
	{ //up
		bit_NS_rowNum +=1;
		virt_ytemp -=1;
		if(virt_ytemp<0)	
		{//碰界退出
			bIfyOutside = 1;
			break; 
		}
	}while(cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)));  //有子 并等于所下颜色的子， +1
//	if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)||
//		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit))//只有当反色或者无子的时候才会到这里（除了边界））

	if(!bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit， 未出界，考虑活棋 
	{//考虑有几个空白棋位  ,暂时只考虑3位
		NS_lastNoneNum +=1;
		NSLiveCnt +=1;
		virt_ytemp -=1;  // see next  bit if none 
		if(virt_ytemp>=0)   //note：一个空棋位之后，可能还会出项一个自己的同色棋!!
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
			{
				NS_lastNoneNum +=1;
				virt_ytemp -=1;  // see next  bit if none 
				if(virt_ytemp>=0)   //note：一个空棋位之后，可能还会出项一个自己的同色棋!!
				{
					if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
					{
						NS_lastNoneNum +=1;
					}
				}
			}
			else    //跳一格后有子?
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //跳子同色
				{
					NS_OneGapBit = 1;   //前半部分有一子跳子棋
				}
			}
		}
	}
	
	virt_xtemp = virt_x; 
	virt_ytemp = virt_y;
	bIfyOutside = 0;  //清边界
	virt_ytemp +=1;  //移位

	//up&&down
	//------down // 反向不能够 先+1，  用while 
	while(cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)))
	{  //有子 并等于所下颜色的子， +1
		//只有当反色或者无子的时候才会退出while循环（除了边界））
		bit_NS_rowNum +=1;
		virt_ytemp +=1;
		if(virt_ytemp>14)	
		{//碰界退出
			bIfyOutside = 1;
			break; 
		}
	}

	//--start--考虑棋子尾 空白位问题
	if(!bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit， 未出界，考虑活棋 
	{//考虑有几个空白棋位  ,暂时只考虑3位
		NS_lastNoneNum +=1;
		NSLiveCnt +=1;
		virt_ytemp +=1;  // see next  bit if none 
		if(virt_ytemp<15)
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
			{
				NS_lastNoneNum +=1;
				if(virt_ytemp<15)
				{
					if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
					{
						NS_lastNoneNum +=1;	
					}
				}
			}
			else    //跳一格后有子
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //跳子同色
				{
					NS_OneGapBit += 1;   //后半部分有一子跳子棋
				}
			}
		}
	}
	//--end--考虑棋子尾 空白位问题

	//-------check-start---
	if(bit_NS_rowNum>5) // check the bit number in a row;  
	{
		if(!whoBit) // 黑棋长连禁手
		{
			forbiddenSta = LongForb;
			return false;
		}else 
		{
			winSta = WhitePlayerWin;
		}
	}else if(5 == bit_NS_rowNum )
	{
		if(!whoBit) //black bit
		{
			if(!forbiddenSta)  // note : 在黑棋取胜之前还要加入禁手判断！！待加--------（2014-12-7） 
			{
				winSta = BlackPlayerWin;
			}
		}else  //white is win 
		{
			winSta = WhitePlayerWin;
		}

	}else if(4 == bit_NS_rowNum)
	{
		if((NSLiveCnt ==2) &&(NS_lastNoneNum >=2)) //在 连棋4个，两边jun live ,总共空棋位大于2，时 可以为 活四
		{//live 4
			NS_GameSta = FreedomOfFour;
			ForbiFourCnt +=1;
		}
		else if((NSLiveCnt ==1) &&(NS_lastNoneNum >=1))
		{// single 4
			NS_GameSta = SigleFour;
		}
	}else if(3 == bit_NS_rowNum )
	{
		if((NSLiveCnt ==2) && (NS_lastNoneNum >=3))  //在 连棋3个，两边总共空棋位大于等于4，时 可以为 活三     空空×××空空
		{//live 3
			NS_GameSta = FreedomOfThree;
			ForbiThreeCnt +=1;
		}else if((NSLiveCnt ==1) && (NS_lastNoneNum >=3))  //     空空×××空空
		{//live 3
			NS_GameSta = SigleThree;
		}
	}else if(2 == bit_NS_rowNum )
	{
		if((NSLiveCnt ==2) && (NS_lastNoneNum >=4))  //在 连棋2个，两边总共空棋位大于等于4，时 可以为 活2     空空×××空空
		{//live 3
			NS_GameSta = FreedomOfTwo;
		}else if((NSLiveCnt ==1) && (NS_lastNoneNum >=4))  //     空空×××空空
		{//live 3
			NS_GameSta = SigleTwo;
		}else if((NSLiveCnt ==2) && (NS_OneGapBit>=1))
		{//live 4
			NS_GameSta = SigleFour;
		}
	}
	else if(1 == bit_NS_rowNum )
	{
		if((NSLiveCnt ==2) && (NS_lastNoneNum >=4))
		{//live 1
			NS_GameSta = FreedomOfOne;
		}else if((NSLiveCnt ==1) && (NS_lastNoneNum >=4))
		{//s1
			NS_GameSta = SigleOne;
		}else
			NS_GameSta = HaveOne;
	}

	//------end check-------

//--end NS----------------------------------------------------------------------------------------


//--start NW&&SE----------------------------------------------------------------------------------
	virt_xtemp = virt_x; 
	virt_ytemp = virt_y;
	do  //NW&&SE
	{ //NW
		bit_NW_rowNum +=1;
		virt_ytemp -=1;
		virt_xtemp -=1;
		if(virt_ytemp<0)	
		{//碰界退出
			bIfyOutside = 1;
			break; 
		}
		if(virt_xtemp<0)	
		{//碰界退出
			bIfxOutside = 1;
			break; 
		}
	}while(cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)));  //有子 并等于所下颜色的子， +1

	if(!bIfxOutside && !bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit， 未出界，考虑活棋 
	{//考虑有几个空白棋位  ,暂时只考虑3位
		NW_lastNoneNum +=1;
		NWLiveCnt +=1;
		virt_ytemp -=1;  // see next  bit if none 
		virt_xtemp -=1; 
		if((virt_ytemp>=0) &&(virt_xtemp>=0))   //note：一个空棋位之后，可能还会出项一个自己的同色棋!!
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
			{
				NW_lastNoneNum +=1;
				virt_ytemp -=1;  // see next  bit if none 
				virt_xtemp -=1; 
				if((virt_ytemp>=0) &&(virt_xtemp>=0))   //note：一个空棋位之后，可能还会出项一个自己的同色棋!!
				{
					if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
					{
						NW_lastNoneNum +=1;
					}
				}
			}
			else    //跳一格后有子
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //跳子同色
				{
					NW_OneGapBit = 1;   //前半部分有一子跳子棋
				}
			}
		}
	}
	
	virt_xtemp = virt_x;   //复原值
	virt_ytemp = virt_y;
	bIfxOutside = 0;  //清边界
	bIfyOutside = 0;  //清边界
	virt_ytemp += 1;  //移位
	virt_xtemp += 1;  //移位

	////NW&&SE
	//------SE // 反向不能够 先+1，  用while 
	while(cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)))
	{  //有子 并等于所下颜色的子， +1
		//只有当反色或者无子的时候才会退出while循环（除了边界））
		bit_NW_rowNum +=1;
		virt_ytemp +=1;
		virt_xtemp +=1;
		if(virt_ytemp>14)	
		{//碰界退出
			bIfyOutside = 1;
			break; 
		}
		if(virt_xtemp>14)	
		{//碰界退出
			bIfxOutside = 1;
			break; 
		}
	}

	//--start--考虑棋子尾 空白位问题
	if(!bIfxOutside && !bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit， 未出界，考虑活棋 
	{//考虑有几个空白棋位  ,暂时只考虑两位
		NW_lastNoneNum +=1;
		NWLiveCnt +=1;
		virt_ytemp +=1;  // see next  bit if none 
		virt_xtemp +=1;  // see next  bit if none 
		if((virt_ytemp<15)&&(virt_xtemp<15))
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) 
			{
				NW_lastNoneNum +=1;
				virt_ytemp +=1;  // see next  bit if none 
				virt_xtemp +=1;  // see next  bit if none 
				if((virt_ytemp<15)&&(virt_xtemp<15))
				{
					if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) 
					{
						NW_lastNoneNum +=1;
					}
				}
			}
			else    //跳一格后有子
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //跳子同色
				{
					NW_OneGapBit += 1;   //后半部分有一子跳子棋
				}
			}
		}
				
	}
	//--end--考虑棋子尾 空白位问题

	//-------check-start---
if(bit_NW_rowNum>5) // check the bit number in a row;  
	{
		if(!whoBit) // 黑棋长连禁手
		{
			forbiddenSta = LongForb;
			return false;
		}else 
		{
			winSta = WhitePlayerWin;
		}
	}else if(5 == bit_NW_rowNum )
	{
		if(!whoBit) //black bit
		{
			if(!forbiddenSta)  // note : 在黑棋取胜之前还要加入禁手判断！！待加--------（2014-12-7） 
			{
				winSta = BlackPlayerWin;
			}
		}else  //white is win 
		{
			winSta = WhitePlayerWin;
		}

	}else if(4 == bit_NW_rowNum)
	{
		if((NWLiveCnt ==2) &&(NW_lastNoneNum >=2)) //在 连棋4个，两边jun live ,总共空棋位大于2，时 可以为 活四
		{//live 4
			NW_GameSta = FreedomOfFour;
			ForbiFourCnt +=1;
		}
		else if((NWLiveCnt ==1) &&(NW_lastNoneNum >=1))
		{// single 4
			NW_GameSta = SigleFour;
		}
	}else if(3 == bit_NW_rowNum )
	{
		if((NWLiveCnt ==2) && (NW_lastNoneNum >=3))  //在 连棋3个，两边总共空棋位大于等于4，时 可以为 活三     空空×××空空
		{//live 3
			NW_GameSta = FreedomOfThree;
			ForbiThreeCnt +=1;
		}else if((NWLiveCnt ==1) && (NW_lastNoneNum >=3))  //     空空×××空空
		{//live 3
			NW_GameSta = SigleThree;
		}
	}else if(2 == bit_NW_rowNum )
	{
		if((NWLiveCnt ==2) && (NW_lastNoneNum >=4))  //在 连棋2个，两边总共空棋位大于等于4，时 可以为 活2     空空×××空空
		{//live 3
			NW_GameSta = FreedomOfTwo;
		}else if((NWLiveCnt ==1) && (NW_lastNoneNum >=4))  //     空空×××空空
		{//live 3
			NW_GameSta = SigleTwo;
		}else if((NWLiveCnt ==2) && (NW_OneGapBit>=1))
		{//live 4
			NW_GameSta = SigleFour;
		}
	}else if(1 == bit_NW_rowNum )
	{
		if((NWLiveCnt ==2) && (NW_lastNoneNum >=4))
		{//live 1
			NW_GameSta = FreedomOfOne;
		}else if((NWLiveCnt ==1) && (NW_lastNoneNum >=4))
		{//s1
			NW_GameSta = SigleOne;
		}else 
			NW_GameSta=HaveOne;
	}
	// check  last none bit number
//	if(NS_lastNoneNum > 3)
//	{
//		
//	}

	//------end check-------

//--end NW&&SE-----------------------------------------------------------------------------------------------

//--start WE-----------------------------------------------------------------------------------------------
	virt_xtemp = virt_x; 
	virt_ytemp = virt_y;
	do  //WE
	{ //WE
		bit_WE_rowNum +=1;
	//	virt_ytemp -=1;
		virt_xtemp -=1;	//x-1, y 不变
	//	if(virt_ytemp<0)	
	//	{//碰界退出
	//		bIfyOutside = 1;
	//		break; 
	//	}
		if(virt_xtemp<0)	
		{//碰界退出
			bIfxOutside = 1;
			break; 
		}
	}while(cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)));  //有子 并等于所下颜色的子， +1

	if(!bIfxOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit， 未出界，考虑活棋 
	{//考虑有几个空白棋位  ,暂时只考虑两位
		WE_lastNoneNum +=1;
		WELiveCnt +=1;
	//	virt_ytemp -=1;  // see next  bit if none 
		virt_xtemp -=1; 
		if(virt_xtemp>=0)   //note：一个空棋位之后，可能还会出项一个自己的同色棋!!-------------------
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
			{
				WE_lastNoneNum +=1;
				virt_xtemp -=1; 
				if(virt_xtemp>=0)   //note：一个空棋位之后，可能还会出项一个自己的同色棋!!-------------------
				{
					if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
					{
						WE_lastNoneNum +=1;
					}
				}
			}
			else    //跳一格后有子
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //跳子同色
				{
					WE_OneGapBit = 1;   //前半部分有一子跳子棋
				}
			}
		}
	}
	
	virt_xtemp = virt_x;   //复原值
	virt_ytemp = virt_y;
	bIfxOutside = 0;  //清边界
	virt_xtemp += 1;  //移位

	////WE
	//------WE // 反向不能够 先+1，  用while 
	while(cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)))
	{  //有子 并等于所下颜色的子， +1
		//只有当反色或者无子的时候才会退出while循环（除了边界））
		bit_WE_rowNum +=1;
		virt_xtemp +=1;
		if(virt_xtemp>14)	
		{//碰界退出
			bIfxOutside = 1;
			break; 
		}
	}

	//--start--考虑棋子尾 空白位问题
	if(!bIfxOutside  && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit， 未出界，考虑活棋 
	{//考虑有几个空白棋位  ,暂时只考虑两位
		WE_lastNoneNum +=1;
		WELiveCnt +=1;
		virt_xtemp +=1;  // see next  bit if none 
		if(virt_xtemp<15)
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
			{
				WE_lastNoneNum +=1;
					virt_xtemp +=1;  // see next  bit if none 
				if(virt_xtemp<15)
				{
					if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
					{
						WE_lastNoneNum +=1;
					}
				}
			}
			else    //跳一格后有子
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //跳子同色
				{
					WE_OneGapBit += 1;   //后半部分有一子跳子棋
				}
			}
		}
				
	}
	//--end--考虑棋子尾 空白位问题

	//-------check-start---


if(bit_WE_rowNum>5) // check the bit number in a row;  
	{
		if(!whoBit) // 黑棋长连禁手
		{
			forbiddenSta = LongForb;
			return false;
		}else 
		{
			winSta = WhitePlayerWin;
		}
	}else if(5 == bit_WE_rowNum )
	{
		if(!whoBit) //black bit
		{
			if(!forbiddenSta)  // note : 在黑棋取胜之前还要加入禁手判断！！待加--------（2014-12-7） 
			{
				winSta = BlackPlayerWin;
			}
		}else  //white is win 
		{
			winSta = WhitePlayerWin;
		}

	}else if(4 == bit_WE_rowNum)
	{
		if((WELiveCnt ==2) &&(WE_lastNoneNum >=2)) //在 连棋4个，两边jun live ,总共空棋位大于2，时 可以为 活四
		{//live 4
			WE_GameSta = FreedomOfFour;
			ForbiFourCnt +=1;
		}
		else if((WELiveCnt ==1) &&(WE_lastNoneNum >=1))
		{// single 4
			WE_GameSta = SigleFour;
		}
	}else if(3 == bit_WE_rowNum )
	{
		if((WELiveCnt ==2) && (WE_lastNoneNum >=3))  //在 连棋3个，两边总共空棋位大于等于4，时 可以为 活三     空空×××空空
		{//live 3
			WE_GameSta = FreedomOfThree;
			ForbiThreeCnt +=1;
		}else if((WELiveCnt ==1) && (WE_lastNoneNum >=3))  //     空空×××空空
		{//live 3
			WE_GameSta = SigleThree;
		}
	}else if(2 == bit_WE_rowNum )
	{
		if((WELiveCnt ==2) && (WE_lastNoneNum >=4))  //在 连棋2个，两边总共空棋位大于等于4，时 可以为 活2     空空×××空空
		{//live 3
			WE_GameSta = FreedomOfTwo;
		}else if((WELiveCnt ==1) && (WE_lastNoneNum >=4))  //     空空×××空空
		{//live 3
			WE_GameSta = SigleTwo;
		}else if((WELiveCnt ==2) && (WE_OneGapBit>=1))
		{//live 4
			WE_GameSta = SigleFour;
		}
	}else if(1 == bit_WE_rowNum )
	{
		if((WELiveCnt ==2) && (WE_lastNoneNum >=4))
		{//live 1
			WE_GameSta = FreedomOfOne;
		}else if((WELiveCnt ==1) && (WE_lastNoneNum >=4))
		{//s1
			WE_GameSta = SigleOne;
		}else 
			WE_GameSta=HaveOne;
	}
	// check  last none bit number
//	if(NS_lastNoneNum > 3)
//	{
//		
//	}

	//------end check-------

//--end WE-------------------------------------------------------------------------------------------------------


//--start WS&&NE--------------------------------------------------------------------------------------------------
	virt_xtemp = virt_x; 
	virt_ytemp = virt_y;
	do  //Ws&&NE
	{ //Ws
		bit_WS_rowNum +=1;
		virt_ytemp +=1;
		virt_xtemp -=1;	//x-1, y 不变
		if(virt_ytemp>14)	
		{//碰界退出
			bIfyOutside = 1;
			break; 
		}
		if(virt_xtemp<0)	
		{//碰界退出
			bIfxOutside = 1;
			break; 
		}
	}while(cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)));  //有子 并等于所下颜色的子， +1

	if(!bIfxOutside && !bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit， 未出界，考虑活棋 
	{//考虑有几个空白棋位  ,暂时只考虑两位
		WS_lastNoneNum +=1;
		WSLiveCnt +=1;
		virt_ytemp +=1;  // see next  bit if none 
		virt_xtemp -=1; 
		if((virt_xtemp>=0)&&(virt_ytemp<15))   //note：一个空棋位之后，可能还会出项一个自己的同色棋!!-------------------
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
			{
				WS_lastNoneNum +=1;
					virt_ytemp +=1;  // see next  bit if none 
				virt_xtemp -=1; 
				if((virt_xtemp>=0)&&(virt_ytemp<15))   //note：一个空棋位之后，可能还会出项一个自己的同色棋!!-------------------
				{
					if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
					{
						WS_lastNoneNum +=1;
					}
				}
			}
			else    //跳一格后有子
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //跳子同色
				{
					WS_OneGapBit = 1;   //前半部分有一子跳子棋
				}
			}
		}
	}
	
	virt_xtemp = virt_x;   //复原值
	virt_ytemp = virt_y;
	bIfxOutside = 0;  //清边界
	bIfyOutside = 0;  //清边界
	virt_xtemp += 1;  //移位
	virt_ytemp -= 1;  //移位

	////Ws&&NE
	//------NE // 反向不能够 先+1，  用while 
	while(cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)))
	{  //有子 并等于所下颜色的子， +1
		//只有当反色或者无子的时候才会退出while循环（除了边界））
		bit_WS_rowNum +=1;
		virt_xtemp +=1;
		virt_ytemp -= 1;  
		if(virt_xtemp>14)	
		{//碰界退出
			bIfxOutside = 1;
			break; 
		}
		if(virt_ytemp<0)	
		{//碰界退出
			bIfyOutside = 1;
			break; 
		}
	}

	//--start--考虑棋子尾 空白位问题
	if(!bIfxOutside  && !bIfyOutside  &&  !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit， 未出界，考虑活棋 
	{//考虑有几个空白棋位  ,暂时只考虑两位
		WS_lastNoneNum +=1;
		WSLiveCnt +=1;
		virt_xtemp +=1;  // see next  bit if none 
		virt_ytemp -=1;  // see next  bit if none 
		if((virt_xtemp<15)&&(virt_ytemp>0))
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
			{
				WS_lastNoneNum +=1;
				virt_xtemp +=1;  // see next  bit if none 
				virt_ytemp -=1;  // see next  bit if none 
				if((virt_xtemp<15)&&(virt_ytemp>0))
				{
					if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
					{
						WS_lastNoneNum +=1;
					}
				}
			}
			else    //跳一格后有子
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //跳子同色
				{
					WS_OneGapBit += 1;   //后半部分有一子跳子棋
				}
			}
		}
				
	}
	//--end--考虑棋子尾 空白位问题

	//-------check-start---

if(bit_WS_rowNum>5) // check the bit number in a row;  
	{
		if(!whoBit) // 黑棋长连禁手
		{
			forbiddenSta = LongForb;
			return false;
		}else 
		{
			winSta = WhitePlayerWin;
		}
	}else if(5 == bit_WS_rowNum )
	{
		if(!whoBit) //black bit
		{
			if(!forbiddenSta)  // note : 在黑棋取胜之前还要加入禁手判断！！待加--------（2014-12-7） 
			{
				winSta = BlackPlayerWin;
			}
		}else  //white is win 
		{
			winSta = WhitePlayerWin;
		}

	}else if(4 == bit_WS_rowNum)
	{
		if((WSLiveCnt ==2) &&(WS_lastNoneNum >=2)) //在 连棋4个，两边jun live ,总共空棋位大于2，时 可以为 活四
		{//live 4
			WS_GameSta = FreedomOfFour;
			ForbiFourCnt +=1;
		}
		else if((WSLiveCnt ==1) &&(WS_lastNoneNum >=1))//////////////////////////////////////////
		{// single 4
			WS_GameSta = SigleFour;
		}
	}else if(3 == bit_WS_rowNum )
	{
		if((WSLiveCnt ==2) && (WS_lastNoneNum >=3))  //在 连棋3个，两边总共空棋位大于等于4，时 可以为 活三     空空×××空空
		{//live 3
			WS_GameSta = FreedomOfThree;
			ForbiThreeCnt +=1;
		}else if((WSLiveCnt ==1) && (WS_lastNoneNum >=3))  //     空空×××空空
		{//live 3
			WS_GameSta = SigleThree;
		}
	}else if(2 == bit_WS_rowNum )
	{
		if((WSLiveCnt ==2) && (WS_lastNoneNum >=4))  //在 连棋2个，两边总共空棋位大于等于4，时 可以为 活2     空空×××空空
		{//live 3
			WS_GameSta = FreedomOfTwo;
		}else if((WSLiveCnt ==1) && (WS_lastNoneNum >=4))  //     空空×××空空
		{//live 3
			WS_GameSta = SigleTwo;
		}else if((WSLiveCnt ==2) && (WS_OneGapBit>=1))
		{//live 4
			WS_GameSta = SigleFour;
		}
	}else if(1 == bit_WS_rowNum )
	{
		if((WSLiveCnt ==2) && (WS_lastNoneNum >=4))
		{//live 1
			WS_GameSta = FreedomOfOne;
		}else if((WSLiveCnt ==1) && (WS_lastNoneNum >=4))
		{//s1
			WS_GameSta = SigleOne;
		}else 
			WS_GameSta=HaveOne;
	}


	// check  last none bit number
//	if(NS_lastNoneNum > 3)
//	{
//		
//	}

	//------end check-------

//--end WS&&NE----------------------------------------------------------------------------------
//	ThreeThrForb = 1,		FourFouForb,		FourThrThrForb,		FourFouThrForb,	FourThrForb,	LongForb 
	//===========foebidden check===========================================================================
	if(!whoBit)
	{
		if(!ForbiThreeCnt)  //ForbiFourCnt
		{
			if(ForbiFourCnt>=2){
				forbiddenSta = FourFouForb;
				return false;
			}
		}
		else if(1==ForbiThreeCnt)  //ForbiFourCnt
		{// have 3
			if(1==ForbiFourCnt){
				forbiddenSta = FourThrForb;
				return false;
			}
			else if(ForbiFourCnt >=2){
				forbiddenSta =FourFouThrForb ;
				return false;
			}
		}else if(2==ForbiThreeCnt)
		{// two 3
			if(!ForbiFourCnt){
				forbiddenSta = ThreeThrForb;
				return false;
			}
			else if(1==ForbiFourCnt){ 
				forbiddenSta = FourThrThrForb;
				return false;
			}
			else if(ForbiFourCnt >=2){
				forbiddenSta =FourFouThrThrForb;
				return false;
			}
		}
	}
//=====================================================================================================

//	if(winSta) // 已经有某一方胜出
		int StaOfWin = 0;
		if(BlackPlayerWin == winSta ) {
			if(!whoBit)   
			{
				StaOfWin  = fiveScore;
			}
		}
		else if(WhitePlayerWin ==  winSta){
			if(whoBit)
			{   
				StaOfWin  = fiveScore;
			}
		}//  NS_GameSta =0;  // 棋局状态 ：eg ，活四， 活三  NW_GameSta =0 ,WE_GameSta =0 ,WS_GameSta =0;
		else //没有哪一方棋子胜出，返回当前重要的棋局 
		{//记录棋局
			gameSta =0;

			gameSta = NS_GameSta; // max
			if(gameSta < NW_GameSta)  gameSta = NS_GameSta;
			if(gameSta < WE_GameSta)  gameSta = WE_GameSta;
			if(gameSta < WS_GameSta)  gameSta = WS_GameSta;

		}

//=========score====================
	retScore =NS_GameSta + NW_GameSta + WE_GameSta + WS_GameSta + StaOfWin;

//	}
	return true;

}