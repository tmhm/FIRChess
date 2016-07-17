#include "stdafx.h"
#include <windows.h>
//#include <stdio.h>
#include "cBaseAI.h"
#include "cChesser.h"
//#include <iostream.h>
#include "cChessBoard.h"
#include "stdlib.h"

extern   myrestart; 
 	//static	COORD m_iMostValBit_Vir ;   //����Ҫ����
//	static	COORD m_iSeconedValBit_Vir;   //�ڶ���Ҫ����

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

	m_iWinState = NoneWin;	//�Ƿ�Ӯ״̬
	m_iForbiddenSta =0;	//����״̬
//	m_iMostValBit_Vir  ={0,0};   //����Ҫ����
//	m_iSeconedValBit_Vir ={0,0};   //�ڶ���Ҫ����
	m_bHumAndMachMode = 0;	//0-�˻�ģʽ��1-����ģʽ
	m_bMachIsFront=0;	//0-�����˺�  1-���Ȼ���

}

cChesser::~cChesser()
{
 
}
//--------------------------�任---------------------------------------------------------------------
void cChesser::PhyToVirtualBit(COORD &physical, int &virX,int &virY)//����������� �任Ϊ���Ӷ���ı��x��y
{
	virX = (physical.X-2)/2;
	virY = physical.Y-2;
} 

void cChesser::VirtualToPhyBit(int &virX,int &virY ,COORD &physical)//�����Ӷ���ı��x��y  �任Ϊ ���������
{
	physical.X=virX*2+2;
	physical.Y=virY+2;
}
//-----------------------------------------------------------------------------------------------
bool cChesser::bPlayOnceChess(bool    playsta, //���������Ⱥ��֣�  ����--0�� ����--1  
				   COORD  &ret)  //�ش������ӵ��������꣬����������
{
	COORD	Getpostemp={0,0};
	int		virBit_x=0,virBit_y=0;
	
	cBoaOfCher.keyRecTrack(Getpostemp);  //��������λ��
	PhyToVirtualBit(Getpostemp, virBit_x, virBit_y);	//

	if(!bGetChessDisplaySta(cChPiece[virBit_x][virBit_y]))//�˴���δ������
	{
		cChPiece[virBit_x][virBit_y].SetDisplaySta(cChPiece[virBit_x][virBit_y]); //��ע������

		if(!playsta){
			PutOneBit(0 , Getpostemp); // 0  ���壻 1  ����
			cChPiece[virBit_x][virBit_y].SetWOrBSta(cChPiece[virBit_x][virBit_y], playsta); //
		}
		else{
			PutOneBit(1 , Getpostemp); // 0  ���壻 1  ����
			cChPiece[virBit_x][virBit_y].SetWOrBSta(cChPiece[virBit_x][virBit_y], playsta);
		}
		ret.X = virBit_x;
		ret.Y = virBit_y;
		return true;
	}
	else
		return false;
}

//-------------------------��ʾ״̬---------------------------------------
//�������������� �ͻṹ����󣡣�
bool cChesser:: bGetChessDisplaySta(cChessPiece &bit)//��ȡһ�����ӵ���ʾ״̬����
{
	return bit.m_bBitDisplayState;
}

//-------------------------------���ӷ�������-------------------------
int cChesser::bGetChessScore(cChessPiece &bit)//��ȡһ�����ӵķ�������
{
	return bit.m_iBitscore;
}

int cChesser::iGetReadyChessCnt()//��ȡ������������
{
//	int temp=0;
//	temp =cChPiece[0][0].iretReadyChessCnt();
//	return temp;
	return cChPiece[0][0].iretReadyChessCnt();
}

void cChesser::setGameModeFBOrS(int front ,int sigleOrdoub)
{
	m_bMachIsFront  = front;
	m_bHumAndMachMode = sigleOrdoub;	//0-�˻�ģʽ��1-����ģʽ
//	
}

//----------------------------
bool cChesser::bResetOnceBit(cChessPiece &bit)  //���һ���µ���
{
	bit.ResetDisplaySta(bit);  //
	COORD xyt={0,0};//{bit.m_virX ,bit.m_virY};

	VirtualToPhyBit(bit.m_virX,bit.m_virY ,xyt);//�����Ӷ���ı��x��y  �任Ϊ ���������
	cBoaOfCher.putOneBoardBit(xyt);

	return 0;

}
//=============================
//����case
void cChesser::ForbiddenCase(int forbOption)
{
	if(ThreeThrForb == forbOption)
	{
		FirAlert(AlertXY ,"�ú���--��������,������һ����!"); 
	}
	else if(FourFouForb == forbOption)
	{
		FirAlert(AlertXY ,"�ú���--���Ľ���,������һ����!"); 
	}
	else if(FourThrThrForb == forbOption)
	{
		FirAlert(AlertXY ,"�ú���--����������,������һ����!"); 
	}	
	else if(FourFouThrForb == forbOption)
	{
		FirAlert(AlertXY ,"�ú���--����������,������һ����!"); 
	}
	else if(LongForb == forbOption)
	{
		FirAlert(AlertXY ,"�ú���--��������,������һ����!"); 
	}//FourThrForb
	else if(FourThrForb == forbOption)
	{
		FirAlert(AlertXY ,"�ú���--��������,������һ����!"); 
	}
	else if(FourFouThrThrForb == forbOption)
	{
		FirAlert(AlertXY ,"�ú���--������������,������һ����!"); 
	}

}

//---------------------------�ɸ����ֲ����������ӵ�״̬------
int cChesser::iChesserOperating(int hmOrhh,  //0--�˻�    1--����
								int fOrb ,		// 1--����  2--����  ���޵���ģʽ��Ч
								COORD &tempPoint)  // �����µ������һ����   tempPoint�������µ���
{
	//------û��Ӯ start--------------------------------------------------------------
	if(NoneWin == m_iWinState)  // û��Ӯ״̬----------
	{
		if(1==hmOrhh)//�˻�ģʽ
		{
			if(1==fOrb) //������ ======================================start====
			{
					if( 0 == (iGetReadyChessCnt()%2))
					{//����һ��
							if(bPlayOnceChess(0, tempPoint))
							{
								FirAlert(AlertXY ,"����һ���壬����һ����"); 
							}
							while(!iGameIsWinCheck(cChPiece[tempPoint.X][tempPoint.Y],
										  0,							//˭�ߵ��壬���Ⱥ��֣� 0-��/1-��
										  m_iForbiddenSta,				//����״̬	
										  m_lastGameSta,   //��¼�������巵�ص����
										  m_iWinState))	 //---check win statue��
							{	//����δͨ��		ThreeThrForb,FourFouForb,FourThrThrForb,FourFouThrForb,	LongForb
								ForbiddenCase(m_iForbiddenSta);	
								//�����λ�µ����ӣ�����
								bResetOnceBit(cChPiece[tempPoint.X][tempPoint.Y]);  //���һ���µ���

								if(bPlayOnceChess(0, tempPoint))
								{
									FirAlert(AlertXY ,"����һ����,���°���!"); 
								}
							}
					}else
					{//������һ��
						if(MachGiveOnceStep(tempPoint ,1))
						{
							FirAlert(AlertXY ,"��������һ����,����һ����"); 
						}
						iGameIsWinCheck(cChPiece[tempPoint.X][tempPoint.Y],
							  1,							//˭�ߵ��壬���Ⱥ��֣� 0-��/1-��
							  m_iForbiddenSta,				//����״̬	
							  m_lastGameSta,   //��¼�������巵�ص����
							  m_iWinState);
					}
				
			} //===//������ģʽ end================================================
			else if(2==fOrb)	//�˺���=================================start===
			{// void ForbiddenCase(int forbOption);
					if( 0 == (iGetReadyChessCnt()%2))
					{//������һ��
						if(MachGiveOnceStep(tempPoint ,0))
						{
							FirAlert(AlertXY ,"��������һ����,����һ����"); 
						}
						while(!iGameIsWinCheck(cChPiece[tempPoint.X][tempPoint.Y],
										  0,							//˭�ߵ��壬���Ⱥ��֣� 0-��/1-��
										  m_iForbiddenSta,				//����״̬	
										  m_lastGameSta,   //��¼�������巵�ص����
										  m_iWinState))  //---check win statue��
						{	//����δͨ��		ThreeThrForb,FourFouForb,FourThrThrForb,FourFouThrForb,	LongForb
							ForbiddenCase(m_iForbiddenSta);	
							//�����λ�µ����ӣ�����
							bResetOnceBit(cChPiece[tempPoint.X][tempPoint.Y]);  //���һ���µ���

							if(MachGiveOnceStep(tempPoint ,0))
							{
								FirAlert(AlertXY ,"��������һ����,����һ����"); 
							}
						}

					}else
					{//����һ��  // �������壬���迼�ǽ��֣� ֻҪ����Ӯ״̬
							if(bPlayOnceChess(1, tempPoint))   //��������λ��xy
							{
								FirAlert(AlertXY ,"����һ���壬����һ����"); 
							}
							iGameIsWinCheck(cChPiece[tempPoint.X][tempPoint.Y],
											  1,							//˭�ߵ��壬���Ⱥ��֣� 0-��/1-��
											  m_iForbiddenSta,				//����״̬	
											  m_lastGameSta,   //��¼�������巵�ص����
											  m_iWinState);


					}
			} //===================�˺���=================================end===

		}
		else if(2==hmOrhh) //˫��ģʽ 
		{
			if( 0 == (iGetReadyChessCnt()%2))
			{
				if(bPlayOnceChess(0, tempPoint))
				{
					FirAlert(AlertXY ,"����һ���壬����һ����"); 
				}
				while(!iGameIsWinCheck(cChPiece[tempPoint.X][tempPoint.Y],
										  0,							//˭�ߵ��壬���Ⱥ��֣� 0-��/1-��
										  m_iForbiddenSta,				//����״̬	
										  m_lastGameSta,   //��¼�������巵�ص����
										  m_iWinState))  //---check win statue��
				{	//����δͨ��		ThreeThrForb,FourFouForb,FourThrThrForb,FourFouThrForb,	LongForb
					ForbiddenCase(m_iForbiddenSta);
					//�����λ�µ����ӣ�����
					bResetOnceBit(cChPiece[tempPoint.X][tempPoint.Y]);  //���һ���µ���

					if(bPlayOnceChess(0, tempPoint))
					{
						FirAlert(AlertXY ,"����һ���壬����һ����"); 
					}
				}
			}

			else // �������ӣ����迼�ǽ��֣� ֻҪ����Ӯ״̬
			{
				if(bPlayOnceChess(1, tempPoint))   //��������λ��xy
				{
					FirAlert(AlertXY ,"����һ���壬����һ����"); 
				}
				iGameIsWinCheck(cChPiece[tempPoint.X][tempPoint.Y],
							  1,							//˭�ߵ��壬���Ⱥ��֣� 0-��/1-��
							  m_iForbiddenSta,				//����״̬	
							  m_lastGameSta,   //��¼�������巵�ص����
							  m_iWinState);
			}
		}

	}
	//------û��Ӯ end--------------------------------------------------------------
//m_bHumAndMachMode;	//0-�˻�ģʽ��1-����ģʽ	int  m_bMachIsFront;	//0-�����˺�  1-���Ȼ���
	//------------- ����Ӯ��-------------------------------------------------------
	else if(BlackPlayerWin == m_iWinState)  //BlackPlayerWin, WhitePlayerWin,
	{//����Ӯ
		int tempEnd = EndOnceGameOption(AlertXY , BlackPlayerWin ,m_bHumAndMachMode ,m_bMachIsFront);
		//int tempEnd = EndOnceGameOption(AlertXY, BlackPlayerWin);

		if(EndCaseIsEnd ==tempEnd)  //����һ�֣���ʾ�򣬼�����һ�֣������˳�;
		{
			MakeEndGame();
		}
		else if(EndCaseIsRestart ==tempEnd)
		{
	//		goto  myrestart;
		}
	}
	else if(WhitePlayerWin == m_iWinState) //BlackPlayerWin, WhitePlayerWin,   //EndCaseIsEnd=1,	EndCaseIsRestart
	{//����Ӯ
		int tempEnd = EndOnceGameOption(AlertXY , WhitePlayerWin ,m_bHumAndMachMode ,m_bMachIsFront);
	//	int tempEnd = EndOnceGameOption( AlertXY,WhitePlayerWin);  //����һ�֣���ʾ�򣬼�����һ�֣������˳�;
		if(EndCaseIsEnd ==tempEnd)  //����һ�֣���ʾ�򣬼�����һ�֣������˳�;
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


//enum GameSta  //���״̬
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

// ��˭�µ�һ���ж�
// whobit  0  - �µĺ���   1- �µİ���    foebidden only for black    
// bit  ��������λ  eg�� cChPiece[0][0]
//---------�ж���Ӯ����������  ������˭win ״̬   0����win   1- ��win   2- ��win ��3-���֣������� (����)
//�������ۻ�ЧӦ����������Ч
//int cChesser::iGameIsWinCheck(cChessPiece bit,
bool cChesser::iGameIsWinCheck(cChessPiece &bit,
							  bool whoBit,      //˭�ߵ��壬���Ⱥ��֣� 0-��/ 1-��  
							  int &forbiddenSta,   //����״̬	 jian  enum
							  int &gameSta,  //���ظ���һ������   �������Ӻ�����
							  int &winSta)		// �޸� ����winsta ��������return�������ڲ�����   ��enum
{
	int virt_x=0,virt_y=0;
	bool bIfxOutside = 0,bIfyOutside = 0;	//�����־λ
	forbiddenSta= 0;  //�����ֱ�־���㣬��ֹ���У����ֱ�־��1��ʼ
	winSta = NoneWin;
	//        N
	//      W   E
	//        S
	int bit_NS_rowNum = 0;		// Ĭ��0�ӣ����� do- while  
	int bit_NW_rowNum = 0, bit_WE_rowNum = 0, bit_WS_rowNum = 0;  //���е�ͬɫ���Ӹ���
	int NS_lastNoneNum = 0;  //ͬ������ β  ����λ����
	int NW_lastNoneNum = 0,WE_lastNoneNum = 0,WS_lastNoneNum = 0;

	// ����λ   һ��-1�� ����-2    �޿ձ� -0��
	int NSLiveCnt =0;
	int NWLiveCnt =0, WELiveCnt =0, WSLiveCnt =0;

	int NS_OneGapBit = 0;  //������ͬɫ��
	int NW_OneGapBit = 0,WE_OneGapBit = 0,WS_OneGapBit = 0;
	int NS_GameSta =0;  // ���״̬ ��eg �����ģ� ���� ����
	int NW_GameSta =0 ,WE_GameSta =0 ,WS_GameSta =0;

	int virt_xtemp= bit.m_virX;
	int virt_ytemp= bit.m_virY;

	virt_x = virt_xtemp;  //�����Ա���
	virt_y = virt_ytemp;

	//forbidden  cnt 
	int ForbiFourCnt=0;
	int ForbiThreeCnt=0;
	
	// up 
//	if( !((virt_ytemp -1) <0) ){ // ����δ����
//		if (cChPiece[virt_xtemp][virt_ytemp -1].m_bBitDisplayState)// ��λ������
//		{
//			if(cChPiece[virt_xtemp][virt_ytemp -1].m_bBitWOrBState == whoBit)   //m_bBitWOrBState  0-hei  1 bai
//			bit_RowNum +=1;
//		}
//	}else{  //���г��磬����ز�����
//		if(cChPiece[virt_xtemp][virt_ytemp +1].m_bBitDisplayState)  //bool m_bBitWOrBState;	 //��λ��/��״̬ 0-�ڣ�1-��
//	}

//--start NS----------------------------------------------------------------------------------------------
	virt_xtemp = virt_x; 
	virt_ytemp = virt_y;
	do  //up&&down
	{ //up
		bit_NS_rowNum +=1;
		virt_ytemp -=1;
		if(virt_ytemp<0)	
		{//�����˳�
			bIfyOutside = 1;
			break; 
		}
	}while(cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)));  //���� ������������ɫ���ӣ� +1
//	if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)||
//		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit))//ֻ�е���ɫ�������ӵ�ʱ��Żᵽ������˱߽磩��

	if(!bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit�� δ���磬���ǻ��� 
	{//�����м����հ���λ  ,��ʱֻ����3λ
		NS_lastNoneNum +=1;
		NSLiveCnt +=1;
		virt_ytemp -=1;  // see next  bit if none 
		if(virt_ytemp>=0)   //note��һ������λ֮�󣬿��ܻ������һ���Լ���ͬɫ��!!
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
			{
				NS_lastNoneNum +=1;
				virt_ytemp -=1;  // see next  bit if none 
				if(virt_ytemp>=0)   //note��һ������λ֮�󣬿��ܻ������һ���Լ���ͬɫ��!!
				{
					if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
					{
						NS_lastNoneNum +=1;
					}
				}
			}
			else    //��һ�������?
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //����ͬɫ
				{
					NS_OneGapBit = 1;   //ǰ�벿����һ��������
				}
			}
		}
	}
	
	virt_xtemp = virt_x; 
	virt_ytemp = virt_y;
	bIfyOutside = 0;  //��߽�
	virt_ytemp +=1;  //��λ

	//up&&down
	//------down // �����ܹ� ��+1��  ��while 
	while(cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)))
	{  //���� ������������ɫ���ӣ� +1
		//ֻ�е���ɫ�������ӵ�ʱ��Ż��˳�whileѭ�������˱߽磩��
		bit_NS_rowNum +=1;
		virt_ytemp +=1;
		if(virt_ytemp>14)	
		{//�����˳�
			bIfyOutside = 1;
			break; 
		}
	}

	//--start--��������β �հ�λ����
	if(!bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit�� δ���磬���ǻ��� 
	{//�����м����հ���λ  ,��ʱֻ����3λ
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
			else    //��һ�������
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //����ͬɫ
				{
					NS_OneGapBit += 1;   //��벿����һ��������
				}
			}
		}
	}
	//--end--��������β �հ�λ����

	//-------check-start---
	if(bit_NS_rowNum>5) // check the bit number in a row;  
	{
		if(!whoBit) // ���峤������
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
			if(!forbiddenSta)  // note : �ں���ȡʤ֮ǰ��Ҫ��������жϣ�������--------��2014-12-7�� 
			{
				winSta = BlackPlayerWin;
			}
		}else  //white is win 
		{
			winSta = WhitePlayerWin;
		}

	}else if(4 == bit_NS_rowNum)
	{
		if((NSLiveCnt ==2) &&(NS_lastNoneNum >=2)) //�� ����4��������jun live ,�ܹ�����λ����2��ʱ ����Ϊ ����
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
		if((NSLiveCnt ==2) && (NS_lastNoneNum >=3))  //�� ����3���������ܹ�����λ���ڵ���4��ʱ ����Ϊ ����     �տա������տ�
		{//live 3
			NS_GameSta = FreedomOfThree;
			ForbiThreeCnt +=1;
		}else if((NSLiveCnt ==1) && (NS_lastNoneNum >=3))  //     �տա������տ�
		{//live 3
			NS_GameSta = SigleThree;
		}
	}else if(2 == bit_NS_rowNum )
	{
		if((NSLiveCnt ==2) && (NS_lastNoneNum >=4))  //�� ����2���������ܹ�����λ���ڵ���4��ʱ ����Ϊ ��2     �տա������տ�
		{//live 3
			NS_GameSta = FreedomOfTwo;
		}else if((NSLiveCnt ==1) && (NS_lastNoneNum >=4))  //     �տա������տ�
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
		{//�����˳�
			bIfyOutside = 1;
			break; 
		}
		if(virt_xtemp<0)	
		{//�����˳�
			bIfxOutside = 1;
			break; 
		}
	}while(cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)));  //���� ������������ɫ���ӣ� +1

	if(!bIfxOutside && !bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit�� δ���磬���ǻ��� 
	{//�����м����հ���λ  ,��ʱֻ����3λ
		NW_lastNoneNum +=1;
		NWLiveCnt +=1;
		virt_ytemp -=1;  // see next  bit if none 
		virt_xtemp -=1; 
		if((virt_ytemp>=0) &&(virt_xtemp>=0))   //note��һ������λ֮�󣬿��ܻ������һ���Լ���ͬɫ��!!
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
			{
				NW_lastNoneNum +=1;
				virt_ytemp -=1;  // see next  bit if none 
				virt_xtemp -=1; 
				if((virt_ytemp>=0) &&(virt_xtemp>=0))   //note��һ������λ֮�󣬿��ܻ������һ���Լ���ͬɫ��!!
				{
					if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
					{
						NW_lastNoneNum +=1;
					}
				}
			}
			else    //��һ�������
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //����ͬɫ
				{
					NW_OneGapBit = 1;   //ǰ�벿����һ��������
				}
			}
		}
	}
	
	virt_xtemp = virt_x;   //��ԭֵ
	virt_ytemp = virt_y;
	bIfxOutside = 0;  //��߽�
	bIfyOutside = 0;  //��߽�
	virt_ytemp += 1;  //��λ
	virt_xtemp += 1;  //��λ

	////NW&&SE
	//------SE // �����ܹ� ��+1��  ��while 
	while(cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)))
	{  //���� ������������ɫ���ӣ� +1
		//ֻ�е���ɫ�������ӵ�ʱ��Ż��˳�whileѭ�������˱߽磩��
		bit_NW_rowNum +=1;
		virt_ytemp +=1;
		virt_xtemp +=1;
		if(virt_ytemp>14)	
		{//�����˳�
			bIfyOutside = 1;
			break; 
		}
		if(virt_xtemp>14)	
		{//�����˳�
			bIfxOutside = 1;
			break; 
		}
	}

	//--start--��������β �հ�λ����
	if(!bIfxOutside && !bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit�� δ���磬���ǻ��� 
	{//�����м����հ���λ  ,��ʱֻ������λ
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
			else    //��һ�������
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //����ͬɫ
				{
					NW_OneGapBit += 1;   //��벿����һ��������
				}
			}
		}
				
	}
	//--end--��������β �հ�λ����

	//-------check-start---
if(bit_NW_rowNum>5) // check the bit number in a row;  
	{
		if(!whoBit) // ���峤������
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
			if(!forbiddenSta)  // note : �ں���ȡʤ֮ǰ��Ҫ��������жϣ�������--------��2014-12-7�� 
			{
				winSta = BlackPlayerWin;
			}
		}else  //white is win 
		{
			winSta = WhitePlayerWin;
		}

	}else if(4 == bit_NW_rowNum)
	{
		if((NWLiveCnt ==2) &&(NW_lastNoneNum >=2)) //�� ����4��������jun live ,�ܹ�����λ����2��ʱ ����Ϊ ����
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
		if((NWLiveCnt ==2) && (NW_lastNoneNum >=3))  //�� ����3���������ܹ�����λ���ڵ���4��ʱ ����Ϊ ����     �տա������տ�
		{//live 3
			NW_GameSta = FreedomOfThree;
			ForbiThreeCnt +=1;
		}else if((NWLiveCnt ==1) && (NW_lastNoneNum >=3))  //     �տա������տ�
		{//live 3
			NW_GameSta = SigleThree;
		}
	}else if(2 == bit_NW_rowNum )
	{
		if((NWLiveCnt ==2) && (NW_lastNoneNum >=4))  //�� ����2���������ܹ�����λ���ڵ���4��ʱ ����Ϊ ��2     �տա������տ�
		{//live 3
			NW_GameSta = FreedomOfTwo;
		}else if((NWLiveCnt ==1) && (NW_lastNoneNum >=4))  //     �տա������տ�
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
		virt_xtemp -=1;	//x-1, y ����
	//	if(virt_ytemp<0)	
	//	{//�����˳�
	//		bIfyOutside = 1;
	//		break; 
	//	}
		if(virt_xtemp<0)	
		{//�����˳�
			bIfxOutside = 1;
			break; 
		}
	}while(cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)));  //���� ������������ɫ���ӣ� +1

	if(!bIfxOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit�� δ���磬���ǻ��� 
	{//�����м����հ���λ  ,��ʱֻ������λ
		WE_lastNoneNum +=1;
		WELiveCnt +=1;
	//	virt_ytemp -=1;  // see next  bit if none 
		virt_xtemp -=1; 
		if(virt_xtemp>=0)   //note��һ������λ֮�󣬿��ܻ������һ���Լ���ͬɫ��!!-------------------
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
			{
				WE_lastNoneNum +=1;
				virt_xtemp -=1; 
				if(virt_xtemp>=0)   //note��һ������λ֮�󣬿��ܻ������һ���Լ���ͬɫ��!!-------------------
				{
					if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
					{
						WE_lastNoneNum +=1;
					}
				}
			}
			else    //��һ�������
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //����ͬɫ
				{
					WE_OneGapBit = 1;   //ǰ�벿����һ��������
				}
			}
		}
	}
	
	virt_xtemp = virt_x;   //��ԭֵ
	virt_ytemp = virt_y;
	bIfxOutside = 0;  //��߽�
	virt_xtemp += 1;  //��λ

	////WE
	//------WE // �����ܹ� ��+1��  ��while 
	while(cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)))
	{  //���� ������������ɫ���ӣ� +1
		//ֻ�е���ɫ�������ӵ�ʱ��Ż��˳�whileѭ�������˱߽磩��
		bit_WE_rowNum +=1;
		virt_xtemp +=1;
		if(virt_xtemp>14)	
		{//�����˳�
			bIfxOutside = 1;
			break; 
		}
	}

	//--start--��������β �հ�λ����
	if(!bIfxOutside  && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit�� δ���磬���ǻ��� 
	{//�����м����հ���λ  ,��ʱֻ������λ
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
			else    //��һ�������
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //����ͬɫ
				{
					WE_OneGapBit += 1;   //��벿����һ��������
				}
			}
		}
				
	}
	//--end--��������β �հ�λ����

	//-------check-start---


if(bit_WE_rowNum>5) // check the bit number in a row;  
	{
		if(!whoBit) // ���峤������
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
			if(!forbiddenSta)  // note : �ں���ȡʤ֮ǰ��Ҫ��������жϣ�������--------��2014-12-7�� 
			{
				winSta = BlackPlayerWin;
			}
		}else  //white is win 
		{
			winSta = WhitePlayerWin;
		}

	}else if(4 == bit_WE_rowNum)
	{
		if((WELiveCnt ==2) &&(WE_lastNoneNum >=2)) //�� ����4��������jun live ,�ܹ�����λ����2��ʱ ����Ϊ ����
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
		if((WELiveCnt ==2) && (WE_lastNoneNum >=3))  //�� ����3���������ܹ�����λ���ڵ���4��ʱ ����Ϊ ����     �տա������տ�
		{//live 3
			WE_GameSta = FreedomOfThree;
			ForbiThreeCnt +=1;
		}else if((WELiveCnt ==1) && (WE_lastNoneNum >=3))  //     �տա������տ�
		{//live 3
			WE_GameSta = SigleThree;
		}
	}else if(2 == bit_WE_rowNum )
	{
		if((WELiveCnt ==2) && (WE_lastNoneNum >=4))  //�� ����2���������ܹ�����λ���ڵ���4��ʱ ����Ϊ ��2     �տա������տ�
		{//live 3
			WE_GameSta = FreedomOfTwo;
		}else if((WELiveCnt ==1) && (WE_lastNoneNum >=4))  //     �տա������տ�
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
		virt_xtemp -=1;	//x-1, y ����
		if(virt_ytemp>14)	
		{//�����˳�
			bIfyOutside = 1;
			break; 
		}
		if(virt_xtemp<0)	
		{//�����˳�
			bIfxOutside = 1;
			break; 
		}
	}while(cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)));  //���� ������������ɫ���ӣ� +1

	if(!bIfxOutside && !bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit�� δ���磬���ǻ��� 
	{//�����м����հ���λ  ,��ʱֻ������λ
		WS_lastNoneNum +=1;
		WSLiveCnt +=1;
		virt_ytemp +=1;  // see next  bit if none 
		virt_xtemp -=1; 
		if((virt_xtemp>=0)&&(virt_ytemp<15))   //note��һ������λ֮�󣬿��ܻ������һ���Լ���ͬɫ��!!-------------------
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
			{
				WS_lastNoneNum +=1;
					virt_ytemp +=1;  // see next  bit if none 
				virt_xtemp -=1; 
				if((virt_xtemp>=0)&&(virt_ytemp<15))   //note��һ������λ֮�󣬿��ܻ������һ���Լ���ͬɫ��!!-------------------
				{
					if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
					{
						WS_lastNoneNum +=1;
					}
				}
			}
			else    //��һ�������
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //����ͬɫ
				{
					WS_OneGapBit = 1;   //ǰ�벿����һ��������
				}
			}
		}
	}
	
	virt_xtemp = virt_x;   //��ԭֵ
	virt_ytemp = virt_y;
	bIfxOutside = 0;  //��߽�
	bIfyOutside = 0;  //��߽�
	virt_xtemp += 1;  //��λ
	virt_ytemp -= 1;  //��λ

	////Ws&&NE
	//------NE // �����ܹ� ��+1��  ��while 
	while(cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)))
	{  //���� ������������ɫ���ӣ� +1
		//ֻ�е���ɫ�������ӵ�ʱ��Ż��˳�whileѭ�������˱߽磩��
		bit_WS_rowNum +=1;
		virt_xtemp +=1;
		virt_ytemp -= 1;  
		if(virt_xtemp>14)	
		{//�����˳�
			bIfxOutside = 1;
			break; 
		}
		if(virt_ytemp<0)	
		{//�����˳�
			bIfyOutside = 1;
			break; 
		}
	}

	//--start--��������β �հ�λ����
	if(!bIfxOutside  && !bIfyOutside  &&  !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit�� δ���磬���ǻ��� 
	{//�����м����հ���λ  ,��ʱֻ������λ
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
			else    //��һ�������
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //����ͬɫ
				{
					WS_OneGapBit += 1;   //��벿����һ��������
				}
			}
		}
				
	}
	//--end--��������β �հ�λ����

	//-------check-start---

if(bit_WS_rowNum>5) // check the bit number in a row;  
	{
		if(!whoBit) // ���峤������
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
			if(!forbiddenSta)  // note : �ں���ȡʤ֮ǰ��Ҫ��������жϣ�������--------��2014-12-7�� 
			{
				winSta = BlackPlayerWin;
			}
		}else  //white is win 
		{
			winSta = WhitePlayerWin;
		}

	}else if(4 == bit_WS_rowNum)
	{
		if((WSLiveCnt ==2) &&(WS_lastNoneNum >=2)) //�� ����4��������jun live ,�ܹ�����λ����2��ʱ ����Ϊ ����
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
		if((WSLiveCnt ==2) && (WS_lastNoneNum >=3))  //�� ����3���������ܹ�����λ���ڵ���4��ʱ ����Ϊ ����     �տա������տ�
		{//live 3
			WS_GameSta = FreedomOfThree;
			ForbiThreeCnt +=1;
		}else if((WSLiveCnt ==1) && (WS_lastNoneNum >=3))  //     �տա������տ�
		{//live 3
			WS_GameSta = SigleThree;
		}
	}else if(2 == bit_WS_rowNum )
	{
		if((WSLiveCnt ==2) && (WS_lastNoneNum >=4))  //�� ����2���������ܹ�����λ���ڵ���4��ʱ ����Ϊ ��2     �տա������տ�
		{//live 3
			WS_GameSta = FreedomOfTwo;
		}else if((WSLiveCnt ==1) && (WS_lastNoneNum >=4))  //     �տա������տ�
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

//	if(winSta) // �Ѿ���ĳһ��ʤ��
//	{
		if(BlackPlayerWin == winSta ) {
			FirAlert(AlertXY ,"����ʤ"); 
		}
		else if(WhitePlayerWin ==  winSta){
			FirAlert(AlertXY ,"����ʤ"); 
		}//  NS_GameSta =0;  // ���״̬ ��eg �����ģ� ����  NW_GameSta =0 ,WE_GameSta =0 ,WS_GameSta =0;
		else //û����һ������ʤ�������ص�ǰ��Ҫ����� 
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
		//-2 �п�ʼ
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
							//���ؽ��֣�����λ��������

							if(CheckGameSta(cChPiece[tempx][tempy],whobtemp,
								MachForbFlagTemp,MachWinstaTemp,machGameStaTemp,scorTempFA) )
							{
									
									if(whobtemp){	whot =0;}
									else {whot =1;}
									if(CheckGameSta(cChPiece[tempx][tempy],whot,
									MachForbFlagTemp,MachWinstaTemp,machGameStaTemp,scorTempBb))	//����ô�Ϊ�����Ƿ����Ҫ����
									{//�޸ķ�����
										if( machGameStaTemp> 2000 )
										scorTempBb  += machGameStaTemp;
									}					
									p_st->Score = scorTempFA + scorTempBb/2;
									p_st->X = 	tempx;	//��¼���ӵ���������
									p_st->Y = 	tempy;
									p_st++;
									cnt++;    //ֱ�ӷ����������Լ�  ���ʲ� ��  [0][0]
							}
						}
				}
			}
		}
		// +2 ��
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
							//���ؽ��֣�����λ��������
							if(CheckGameSta(cChPiece[tempx][tempy],whobtemp,
								MachForbFlagTemp,MachWinstaTemp,machGameStaTemp,scorTempFA) )
							{	
							//	bool whotemp =0;	
									if(whobtemp){	whot =0;}
									else {whot =1;}
									if(CheckGameSta(cChPiece[tempx][tempy],whot,
									MachForbFlagTemp,MachWinstaTemp,machGameStaTemp,scorTempBb))	//����ô�Ϊ�����Ƿ����Ҫ����
									{//�޸ķ�����
										if( machGameStaTemp> 2000 )
										scorTempBb  += machGameStaTemp;
									}					
									p_st->Score = scorTempFA + scorTempBb/2;
									p_st->X = 	tempx;	//��¼���ӵ���������
									p_st->Y = 	tempy;
									p_st++;
									cnt++;    //ֱ�ӷ����������Լ�  ���ʲ� ��  [0][0]
							}
						}
				}
			}
		}
			
		tempy =lastBitTemp.Y -(radtemp +2) ;  //-2 que ��   ʣ���
		if( tempy >=0 ) //&& tempy <15)
		{
			for(tempx =lastBitTemp.X -(radtemp +1) ; tempx<lastBitTemp.X +(radtemp +2) ;tempx++)
			{
				//bitY ++;
				if(tempx >=0 && tempx <15  )
				{
						if( !bGetChessDisplaySta(cChPiece[tempx][tempy]))//  &&  bit.X!=tempx && bit.Y!=tempy )
						{
							//���ؽ��֣�����λ��������
							if(CheckGameSta(cChPiece[tempx][tempy],whobtemp,
								MachForbFlagTemp,MachWinstaTemp,machGameStaTemp,scorTempFA) )
							{	
							//	bool whotemp =0;
									if(whobtemp){	whot =0;}
									else {whot =1;}
									if(CheckGameSta(cChPiece[tempx][tempy],whot,
									MachForbFlagTemp,MachWinstaTemp,machGameStaTemp,scorTempBb))	//����ô�Ϊ�����Ƿ����Ҫ����
									{//�޸ķ�����
										if( machGameStaTemp> 2000 )
										scorTempBb  += machGameStaTemp;
									}					
									p_st->Score = scorTempFA + scorTempBb/2;
									p_st->X = 	tempx;	//��¼���ӵ���������
									p_st->Y = 	tempy;
									p_st++;
									cnt++;    //ֱ�ӷ����������Լ�  ���ʲ� ��  [0][0]
							}
						}
				}
			}
		}

		tempy =lastBitTemp.Y +(radtemp +2) ;  //+2��  ʣ���
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
									MachForbFlagTemp,MachWinstaTemp,machGameStaTemp,scorTempBb))	//����ô�Ϊ�����Ƿ����Ҫ����
									{//�޸ķ�����
										if( machGameStaTemp> 2000 )
										scorTempBb  += machGameStaTemp;
									}					
									p_st->Score = scorTempFA + scorTempBb/2;
									p_st->X = 	tempx;	//��¼���ӵ���������
									p_st->Y = 	tempy;
									p_st++;
									cnt++;    //ֱ�ӷ����������Լ�  ���ʲ� ��  [0][0]
							}
							//���ؽ��֣�����λ��������
						//	if(CheckGameSta(cChPiece[tempx][tempy],whobtemp,
						//		MachForbFlagTemp,MachWinstaTemp,machGameStaTemp,p_st->Score))
						//	{
						//			p_st->X = 	tempx;	//��¼���ӵ���������
						//			p_st->Y = 	tempy;
						//			p_st++;
						//			cnt++;    //ֱ�ӷ����������Լ�  ���ʲ� ��  [0][0]
						//	}
						}
				}
			}
		}
	}
}
		
//======================================================
//  bool whoBit,      //˭�ߵ��壬���Ⱥ��֣� 0-��/ 1-��  
//  int &forbiddenSta,   //����״̬	 jian  enum
//  int &gameSta,  //���ظ���һ������   �������Ӻ�����
//  int &winSta)   //Ӯ״̬
//======================================================
//iGameIsWinCheck(cChessPiece &bit, bool whoBit,  int &forbiddenSta,   	  int &gameSta,  int &winSta);

//check   bool whob �� �������巽
bool cChesser::MachGiveOnceStep(COORD &bit ,bool whob) //����ȥ������һ�����Է������ӵ�����λ�ã� ���شβ�������
{
static	COORD lastBitTemp={0,0};

	lastBitTemp.X= bit.X;
	lastBitTemp.Y= bit.Y;  // copy is  so  fault!!!!!!!

	if(!iGetReadyChessCnt())
	{//���е�һ��
			bit.X=7;
			bit.Y=7;

			COORD OnceBitTemp = {16,9};  //��ʵ�����ַ
			if(!bGetChessDisplaySta(cChPiece[7][7]))//�˴���δ������
			{
				cChPiece[7][7].SetDisplaySta(cChPiece[7][7]); //��ע������
				PutOneBit(0 , OnceBitTemp); // 0  ���壻 1  ����
				cChPiece[7][7].SetWOrBSta(cChPiece[7][7], 0); //
			}
			return 1;	
	}
	else if( whob && (1==iGetReadyChessCnt()))  //ji hou xing  di yi bu 
	{//���е�һ��VirtualToPhyBit(int &virX,int &virY ,COORD &physical)//�����Ӷ���ı��x��y  �任Ϊ ���������
	//	COORD bitTwo ={0,0};
		COORD bitTempT={0,0};  //�����ַ
	int	 virtX =bit.X;
	int	 virtY =bit.Y;
	//		bitTwo.Y =bit.Y;
			if(++ virtX <15)
			{
				VirtualToPhyBit(virtX , virtY ,bitTempT);
			}
			else if((virtX-2) >0)  //����һ�����У��β�������
			{
				virtX = virtX-2;
				VirtualToPhyBit(virtX , virtY  ,bitTempT);
			}else if(virtY<15)
			{
				VirtualToPhyBit(virtX , virtY,bitTempT);
			}
			else if((virtY-2) >0)  //����һ�����У��β�������
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
				virtY += tttw%2;  //����һ����ͬ��y
				VirtualToPhyBit(virtX , virtY ,bitTempT);
			}
//PhyToVirtualBit(COORD &physical, int &virX,int &virY)//����������� �任Ϊ���Ӷ���ı��x��y
		//	COORD OnceBitTemp = {0,0};  //��ʵ�����ַ

			if(!bGetChessDisplaySta(cChPiece[virtX][virtY]))//�˴���δ������
			{
				cChPiece[virtX][virtY].SetDisplaySta(cChPiece[virtX][virtY]); //��ע������
				PutOneBit(1 , bitTempT); // 0  ���壻 1  ����
				cChPiece[virtX][virtY].SetWOrBSta(cChPiece[virtX][virtY], 1); //
			}
			return 1;	
	
	}
	else
	{

//========================
// ���ֻ�������������Χ    
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
	//	Scorcnt =0;    //�´ν�������
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
							//���ؽ��֣�����λ��������
							int scorTempFA = 0;
							int scorTempBb = 0;
							if(CheckGameSta(cChPiece[tempx][tempy],whob,
								MachForbFlag,MachWinsta,machGameSta,scorTempFA) )
							{
									bool whotemp =0;
									if(whob){	whotemp =0;}
									else {whotemp =1;}
									if(CheckGameSta(cChPiece[tempx][tempy],whotemp,
									MachForbFlag,MachWinsta,machGameSta,scorTempBb))	//����ô�Ϊ�����Ƿ����Ҫ����
									{//�޸ķ�����
										if( machGameSta> 2000 )
										scorTempBb  += machGameSta;
									}							
									scoretemp[Scorcnt].Score = scorTempFA + scorTempBb/2;
									scoretemp[Scorcnt].X = 	tempx;	//��¼���ӵ���������
									scoretemp[Scorcnt].Y = 	tempy;
									Scorcnt++;    //ֱ�ӷ����������Լ�  ���ʲ� ��  [0][0]
									//scoretemp[Scorcnt].flag = 1;
									//scoretemp[Scorcnt].orderCnt = Scorcnt++;  //Ĭ�Ϸ���˳��
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
	//-2 ��
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
							//���ؽ��֣�����λ��������
							if(CheckGameSta(cChPiece[tempx][tempy],whob,
								MachForbFlag,MachWinsta,machGameSta,scoretemp[Scorcnt].Score))
							{
									scoretemp[Scorcnt].X = 	tempx;	//��¼���ӵ���������
									scoretemp[Scorcnt].Y = 	tempy;
									Scorcnt++;    //ֱ�ӷ����������Լ�  ���ʲ� ��  [0][0]
									//scoretemp[Scorcnt].flag = 1;
									//scoretemp[Scorcnt].orderCnt = Scorcnt++;  //Ĭ�Ϸ���˳��
							}
						}
				}
			}
		}
		// +2 ��
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
							//���ؽ��֣�����λ��������
							if(CheckGameSta(cChPiece[tempx][tempy],whob,
								MachForbFlag,MachWinsta,machGameSta,scoretemp[Scorcnt].Score))
							{
									scoretemp[Scorcnt].X = 	tempx;	//��¼���ӵ���������
									scoretemp[Scorcnt].Y = 	tempy;
									Scorcnt++;    //ֱ�ӷ����������Լ�  ���ʲ� ��  [0][0]
									//scoretemp[Scorcnt].flag = 1;
									//scoretemp[Scorcnt].orderCnt = Scorcnt++;  //Ĭ�Ϸ���˳��
							}
						}
				}
			}
		}
			
		tempy =lastBitTemp.Y -2 ;  //-2 que ��
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
							//���ؽ��֣�����λ��������
							if(CheckGameSta(cChPiece[tempx][tempy],whob,
								MachForbFlag,MachWinsta,machGameSta,scoretemp[Scorcnt].Score))
							{
									scoretemp[Scorcnt].X = 	tempx;	//��¼���ӵ���������
									scoretemp[Scorcnt].Y = 	tempy;
									Scorcnt++;    //ֱ�ӷ����������Լ�  ���ʲ� ��  [0][0]
									//scoretemp[Scorcnt].flag = 1;
									//scoretemp[Scorcnt].orderCnt = Scorcnt++;  //Ĭ�Ϸ���˳��
							}
						}
				}
			}
		}

		tempy =lastBitTemp.Y +2 ;  //+2��
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
							//���ؽ��֣�����λ��������
							if(CheckGameSta(cChPiece[tempx][tempy],whob,
								MachForbFlag,MachWinsta,machGameSta,scoretemp[Scorcnt].Score))
							{
									scoretemp[Scorcnt].X = 	tempx;	//��¼���ӵ���������
									scoretemp[Scorcnt].Y = 	tempy;
									Scorcnt++;    //ֱ�ӷ����������Լ�  ���ʲ� ��  [0][0]
									//scoretemp[Scorcnt].flag = 1;
									//scoretemp[Scorcnt].orderCnt = Scorcnt++;  //Ĭ�Ϸ���˳��
							}
						}
				}
			}
		}
		
#ifdef  RadiusOptionFour

	//-3 ��
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
							//���ؽ��֣�����λ��������
							if(CheckGameSta(cChPiece[tempx][tempy],whob,
								MachForbFlag,MachWinsta,machGameSta,scoretemp[Scorcnt].Score))
							{
									scoretemp[Scorcnt].X = 	tempx;	//��¼���ӵ���������
									scoretemp[Scorcnt].Y = 	tempy;
									Scorcnt++;    //ֱ�ӷ����������Լ�  ���ʲ� ��  [0][0]
							}
						}
				}
			}
		}
		// +3 ��
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
							//���ؽ��֣�����λ��������
							if(CheckGameSta(cChPiece[tempx][tempy],whob,
								MachForbFlag,MachWinsta,machGameSta,scoretemp[Scorcnt].Score))
							{
									scoretemp[Scorcnt].X = 	tempx;	//��¼���ӵ���������
									scoretemp[Scorcnt].Y = 	tempy;
									Scorcnt++;    //ֱ�ӷ����������Լ�  ���ʲ� ��  [0][0]
							}
						}
				}
			}
		}
			
		tempy =lastBitTemp.Y -3 ;  //-3 que ��   ʣ���
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
							//���ؽ��֣�����λ��������
							if(CheckGameSta(cChPiece[tempx][tempy],whob,
								MachForbFlag,MachWinsta,machGameSta,scoretemp[Scorcnt].Score))
							{
									scoretemp[Scorcnt].X = 	tempx;	//��¼���ӵ���������
									scoretemp[Scorcnt].Y = 	tempy;
									Scorcnt++;    //ֱ�ӷ����������Լ�  ���ʲ� ��  [0][0]
									//scoretemp[Scorcnt].flag = 1;
									//scoretemp[Scorcnt].orderCnt = Scorcnt++;  //Ĭ�Ϸ���˳��
							}
						}
				}
			}
		}

		tempy =lastBitTemp.Y +3 ;  //+3��  ʣ���
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
							//���ؽ��֣�����λ��������
							if(CheckGameSta(cChPiece[tempx][tempy],whob,
								MachForbFlag,MachWinsta,machGameSta,scoretemp[Scorcnt].Score))
							{
									scoretemp[Scorcnt].X = 	tempx;	//��¼���ӵ���������
									scoretemp[Scorcnt].Y = 	tempy;
									Scorcnt++;    //ֱ�ӷ����������Լ�  ���ʲ� ��  [0][0]
									//scoretemp[Scorcnt].flag = 1;
									//scoretemp[Scorcnt].orderCnt = Scorcnt++;  //Ĭ�Ϸ���˳��
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

		COORD phyTemp={0,0};  //�����ַ  ����
		VirtualToPhyBit(scoretemp[Scorcnt-1].X, scoretemp[Scorcnt-1].Y , phyTemp);
	//--------------------------------------------
		if(!bGetChessDisplaySta(cChPiece[bit.X][bit.Y]))//�˴���δ������
		{
			cChPiece[bit.X][bit.Y].SetDisplaySta(cChPiece[bit.X][bit.Y]); //��ע������

			if(!whob){
				PutOneBit(0 , phyTemp); // 0  ���壻 1  ����
				cChPiece[bit.X][bit.Y].SetWOrBSta(cChPiece[bit.X][bit.Y], 0); //
			}
			else{
				PutOneBit(1 , phyTemp); // 0  ���壻 1  ����
				cChPiece[bit.X][bit.Y].SetWOrBSta(cChPiece[bit.X][bit.Y], 1);
			}
		}
	}
	return true;
}



//int radii,cChessPiece &bAi ,cChessPiece &nextBit,int &retScore
void cChesser::MarkbitScoreer(int radii ,  //���ְ뾶
							  bool whoBit,
							cChessPiece &bAi ,  //�ϴ������
						//	cChessPiece &nextBit, //�´����������
							int &retScore)   //�����ϴ���õ��ķ�
{
	int raditemp=0;  //�����뾶temp

	int retS = 0;
	int retPlus = 0;
	int ret = 0;  // ret  = retS- retPlus ;
	int virt_x=0,virt_y=0;   //���洫��λ��
	bool bIfxOutside = 0,bIfyOutside = 0;	//�����־λ
//	forbiddenSta= 0;  //�����ֱ�־���㣬��ֹ���У����ֱ�־��1��ʼ
//	winSta = NoneWin;
	//        N
	//      W   E
	//        S
	int bit_NS_rowNum = 0;		// Ĭ��0�ӣ����� do- while  
	int bit_NW_rowNum = 0, bit_WE_rowNum = 0, bit_WS_rowNum = 0;  //���е�ͬɫ���Ӹ���
	int NS_lastNoneNum = 0;  //ͬ������ β  ����λ����
	int NW_lastNoneNum = 0,WE_lastNoneNum = 0,WS_lastNoneNum = 0;
	int NS_OneGapBit = 0;  //������ͬɫ��
	int NW_OneGapBit = 0,WE_OneGapBit = 0,WS_OneGapBit = 0;
	int NS_GameSta =0;  // ���״̬ ��eg �����ģ� ���� ����
	int NW_GameSta =0 ,WE_GameSta =0 ,WS_GameSta =0;

	bool NS_lastNoneFlagFore = 0, NS_lastNoneFlagBlack =0;  //ǰ���п����־λ
	bool NW_lastNoneFlagFore = 0, NW_lastNoneFlagBlack =0;  //ǰ���п����־λ
	bool WE_lastNoneFlagFore = 0, WE_lastNoneFlagBlack =0;  //ǰ���п����־λ
	bool WS_lastNoneFlagFore = 0, WS_lastNoneFlagBlack =0;  //ǰ���п����־λ

	int virt_xtemp= bAi.m_virX;
	int virt_ytemp= bAi.m_virY;

	virt_x = virt_xtemp;  //�����Ա���
	virt_y = virt_ytemp;
	
//--start NS----------------------------------------------------------------------------------------------
//	int retS = 0;
//	int retPlus = 0;

	virt_xtemp = virt_x; 
	virt_ytemp = virt_y;
	raditemp=0;  //�����뾶temp

	do  //up&&down
	{ //up
		raditemp +=1;
		bit_NS_rowNum +=1;
		virt_ytemp -=1;
		if(virt_ytemp<0)	
		{//�����˳�
			bIfyOutside = 1;
			break; 
		}
	}while((raditemp <radii) && cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)));  //���� ������������ɫ���ӣ� +1

	if((raditemp <radii) && !bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit�� δ���磬���ǻ��� 
	{//�����м����հ���λ  ,��ʱֻ������λ
		raditemp +=1;
		NS_lastNoneNum +=1;  
		NS_lastNoneFlagFore = 1;
		virt_ytemp -=1;  // see next  bit if none 
		if((raditemp <radii) &&virt_ytemp>=0)   //note��һ������λ֮�󣬿��ܻ������һ���Լ���ͬɫ��!!
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  NS_lastNoneNum +=1;
			else    //��һ�������
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //����ͬɫ
				{
					NS_OneGapBit = 1;   //ǰ�벿����һ��������
				}
			}
		}
	}
	
	virt_xtemp = virt_x; 
	virt_ytemp = virt_y;
	bIfyOutside = 0;  //��߽�
	virt_ytemp +=1;  //��λ
	raditemp =0;

	//up&&down
	//------down // �����ܹ� ��+1��  ��while 
	while((raditemp <radii) && 
		cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)))
	{  //���� ������������ɫ���ӣ� +1
		//ֻ�е���ɫ�������ӵ�ʱ��Ż��˳�whileѭ�������˱߽磩��
		raditemp +=1;
		bit_NS_rowNum +=1;
		virt_ytemp +=1;
		if(virt_ytemp>14)	
		{//�����˳�
			bIfyOutside = 1;
			break; 
		}
	}

	//--start--��������β �հ�λ����
	if((raditemp <radii) && 
		!bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit�� δ���磬���ǻ��� 
	{//�����м����հ���λ  ,��ʱֻ������λ
		raditemp +=1;
		NS_lastNoneNum +=1;
		NS_lastNoneFlagBlack =1;
		virt_ytemp +=1;  // see next  bit if none 
		if((raditemp <radii) &&
			virt_ytemp<15)
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  NS_lastNoneNum +=1;
			else    //��һ�������
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //����ͬɫ
				{
					NS_OneGapBit += 1;   //��벿����һ��������
				}
			}
		}
				
	}
	//--end--��������β �հ�λ����

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
			||(!NS_lastNoneFlagBlack & NS_lastNoneFlagFore))&& NS_OneGapBit)   //��ֻ����һλ����  ��4
		{//sigle 4
			retS +=sigleFour;
		}
		else if(((NS_lastNoneFlagBlack & !NS_lastNoneFlagFore ) 
			||(!NS_lastNoneFlagBlack & NS_lastNoneFlagFore))&& !NS_OneGapBit && (NS_lastNoneNum>=2))
		{//s3
			retS +=sigleThree;
		}
//		if(NS_lastNoneNum >=2) //�� ����4���������ܹ�����λ����2��ʱ ����Ϊ ����
//		{
//			NS_GameSta = FreedomOfFour;
//		}
	}else if(2 == bit_NS_rowNum)
	{
		if((NS_lastNoneNum >=4)&& (NS_lastNoneFlagBlack & NS_lastNoneFlagFore))  //�� ����2���������ܹ�����λ���ڵ���4��ʱ ����Ϊ ��2     �տա����տ�
		{//liv2
			retS +=liveTwo;
		}
		else if((NS_lastNoneNum >=4)&& ((!NS_lastNoneFlagBlack & NS_lastNoneFlagFore) || (NS_lastNoneFlagBlack & !NS_lastNoneFlagFore)))  //
		{//s2
			retS +=sigleTwo;
		}
	}else if(1 == bit_NS_rowNum)
	{
		if((NS_lastNoneNum >=4)&& (NS_lastNoneFlagBlack & NS_lastNoneFlagFore))  //�� ����2���������ܹ�����λ���ڵ���4��ʱ ����Ϊ ��2     �տա����տ�
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
	raditemp=0;  //�����뾶temp

	do  //NW&&SE
	{ //NW
		raditemp +=1;
		bit_NW_rowNum +=1;
		virt_ytemp -=1;
		virt_xtemp -=1;
		if(virt_ytemp<0)	
		{//�����˳�
			bIfyOutside = 1;
			break; 
		}
		if(virt_xtemp<0)	
		{//�����˳�
			bIfxOutside = 1;
			break; 
		}
	}while((raditemp <radii) &&cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)));  //���� ������������ɫ���ӣ� +1

	if((raditemp <radii) && !bIfxOutside && !bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit�� δ���磬���ǻ��� 
	{//�����м����հ���λ  ,��ʱֻ������λ
		raditemp +=1;
		NW_lastNoneNum +=1;
		virt_ytemp -=1;  // see next  bit if none 
		virt_xtemp -=1; 
		if((raditemp <radii) &&(virt_ytemp>=0) &&(virt_xtemp>=0))   //note��һ������λ֮�󣬿��ܻ������һ���Լ���ͬɫ��!!
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  NW_lastNoneNum +=1;
			else    //��һ�������
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //����ͬɫ
				{
					NW_OneGapBit = 1;   //ǰ�벿����һ��������
				}
			}
		}
	}
	
	virt_xtemp = virt_x;   //��ԭֵ
	virt_ytemp = virt_y;
	bIfxOutside = 0;  //��߽�
	bIfyOutside = 0;  //��߽�
	virt_ytemp += 1;  //��λ
	virt_xtemp += 1;  //��λ

	raditemp =0;

	////NW&&SE
	//------SE // �����ܹ� ��+1��  ��while 
	while((raditemp <radii) && 
		cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)))
	{  //���� ������������ɫ���ӣ� +1
		//ֻ�е���ɫ�������ӵ�ʱ��Ż��˳�whileѭ�������˱߽磩��
		raditemp +=1;
		bit_NW_rowNum +=1;
		virt_ytemp +=1;
		virt_xtemp +=1;
		if(virt_ytemp>14)	
		{//�����˳�
			bIfyOutside = 1;
			break; 
		}
		if(virt_xtemp>14)	
		{//�����˳�
			bIfxOutside = 1;
			break; 
		}
	}

	//--start--��������β �հ�λ����
	if((raditemp <radii) && 
		!bIfxOutside && !bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit�� δ���磬���ǻ��� 
	{//�����м����հ���λ  ,��ʱֻ������λ
		raditemp +=1;
		NW_lastNoneNum +=1;
		virt_ytemp +=1;  // see next  bit if none 
		virt_xtemp +=1;  // see next  bit if none 
		if((raditemp <radii) && (virt_ytemp<15)&&(virt_xtemp<15))
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  NW_lastNoneNum +=1;
			else    //��һ�������
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //����ͬɫ
				{
					NW_OneGapBit += 1;   //��벿����һ��������
				}
			}
		}
				
	}
	//--end--��������β �հ�λ����

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
			||(!NW_lastNoneFlagBlack & NW_lastNoneFlagFore))&& NW_OneGapBit)   //��ֻ����һλ����  ��4
		{//sigle 4
			retS +=sigleFour;
		}
		else if(((NW_lastNoneFlagBlack & !NW_lastNoneFlagFore ) 
			||(!NW_lastNoneFlagBlack & NW_lastNoneFlagFore))&& !NW_OneGapBit && (NW_lastNoneNum>=2))
		{//s3
			retS +=sigleThree;
		}
//		if(NS_lastNoneNum >=2) //�� ����4���������ܹ�����λ����2��ʱ ����Ϊ ����
//		{
//			NS_GameSta = FreedomOfFour;
//		}
	}else if(2 == bit_NW_rowNum)
	{
		if((NW_lastNoneNum >=4)&& (NW_lastNoneFlagBlack & NW_lastNoneFlagFore))  //�� ����2���������ܹ�����λ���ڵ���4��ʱ ����Ϊ ��2     �տա����տ�
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
		if((NW_lastNoneNum >=4)&& (NW_lastNoneFlagBlack & NW_lastNoneFlagFore))  //�� ����2���������ܹ�����λ���ڵ���4��ʱ ����Ϊ ��2     �տա����տ�
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
		virt_xtemp -=1;	//x-1, y ����
	//	if(virt_ytemp<0)	
	//	{//�����˳�
	//		bIfyOutside = 1;
	//		break; 
	//	}
		if(virt_xtemp<0)	
		{//�����˳�
			bIfxOutside = 1;
			break; 
		}
	}while((raditemp <radii) && 
		cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)));  //���� ������������ɫ���ӣ� +1

	if((raditemp <radii) && 
		!bIfxOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit�� δ���磬���ǻ��� 
	{//�����м����հ���λ  ,��ʱֻ������λ
		raditemp +=1;
		WE_lastNoneNum +=1;
	//	virt_ytemp -=1;  // see next  bit if none 
		virt_xtemp -=1; 
		if((raditemp <radii) &&virt_xtemp>=0)   //note��һ������λ֮�󣬿��ܻ������һ���Լ���ͬɫ��!!-------------------
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  WE_lastNoneNum +=1;
			else    //��һ�������
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //����ͬɫ
				{
					WE_OneGapBit = 1;   //ǰ�벿����һ��������
				}
			}
		}
	}
	
	virt_xtemp = virt_x;   //��ԭֵ
	virt_ytemp = virt_y;
	bIfxOutside = 0;  //��߽�
	virt_xtemp += 1;  //��λ
		raditemp =0;

	////WE
	//------WE // �����ܹ� ��+1��  ��while 
	while((raditemp <radii) && 
		cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)))
	{  //���� ������������ɫ���ӣ� +1
		//ֻ�е���ɫ�������ӵ�ʱ��Ż��˳�whileѭ�������˱߽磩��
		raditemp +=1;
		bit_WE_rowNum +=1;
		virt_xtemp +=1;
		if(virt_xtemp>14)	
		{//�����˳�
			bIfxOutside = 1;
			break; 
		}
	}

	//--start--��������β �հ�λ����
	if((raditemp <radii) && 
		!bIfxOutside  && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit�� δ���磬���ǻ��� 
	{//�����м����հ���λ  ,��ʱֻ������λ
		raditemp +=1;
		WE_lastNoneNum +=1;
		virt_xtemp +=1;  // see next  bit if none 
		if((raditemp <radii) &&
			virt_xtemp<15)
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  WE_lastNoneNum +=1;
			else    //��һ�������
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //����ͬɫ
				{
					WE_OneGapBit += 1;   //��벿����һ��������
				}
			}
		}
				
	}
	//--end--��������β �հ�λ����

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
			||(!WE_lastNoneFlagBlack & WE_lastNoneFlagFore))&& WE_OneGapBit)   //��ֻ����һλ����  ��4
		{//sigle 4
			retS +=sigleFour;
		}
		else if(((WE_lastNoneFlagBlack & !WE_lastNoneFlagFore ) 
			||(!WE_lastNoneFlagBlack & WE_lastNoneFlagFore))&& !WE_OneGapBit && (WE_lastNoneNum>=2))
		{//s3
			retS +=sigleThree;
		}
//		if(NS_lastNoneNum >=2) //�� ����4���������ܹ�����λ����2��ʱ ����Ϊ ����
//		{
//			NS_GameSta = FreedomOfFour;
//		}
	}else if(2 == bit_WE_rowNum)
	{
		if((WE_lastNoneNum >=4)&& (WE_lastNoneFlagBlack & WE_lastNoneFlagFore))  //�� ����2���������ܹ�����λ���ڵ���4��ʱ ����Ϊ ��2     �տա����տ�
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
		if((WE_lastNoneNum >=4)&& (WE_lastNoneFlagBlack & WE_lastNoneFlagFore))  //�� ����2���������ܹ�����λ���ڵ���4��ʱ ����Ϊ ��2     �տա����տ�
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
		virt_xtemp -=1;	//x-1, y ����
		if(virt_ytemp>14)	
		{//�����˳�
			bIfyOutside = 1;
			break; 
		}
		if(virt_xtemp<0)	
		{//�����˳�
			bIfxOutside = 1;
			break; 
		}
	}while((raditemp <radii) && 
		cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)));  //���� ������������ɫ���ӣ� +1

	if((raditemp <radii) && 
		!bIfxOutside && !bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit�� δ���磬���ǻ��� 
	{//�����м����հ���λ  ,��ʱֻ������λ
		raditemp +=1;
		WS_lastNoneNum +=1;
		virt_ytemp +=1;  // see next  bit if none 
		virt_xtemp -=1; 
		if((raditemp <radii) &&
			(virt_xtemp>=0)&&(virt_ytemp<15))   //note��һ������λ֮�󣬿��ܻ������һ���Լ���ͬɫ��!!-------------------
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  WS_lastNoneNum +=1;
			else    //��һ�������
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //����ͬɫ
				{
					WS_OneGapBit = 1;   //ǰ�벿����һ��������
				}
			}
		}
	}
	
	virt_xtemp = virt_x;   //��ԭֵ
	virt_ytemp = virt_y;
	bIfxOutside = 0;  //��߽�
	bIfyOutside = 0;  //��߽�
	virt_xtemp += 1;  //��λ
	virt_ytemp -= 1;  //��λ
		raditemp =0;

	////Ws&&NE
	//------NE // �����ܹ� ��+1��  ��while 
	while((raditemp <radii) && 
		cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)))
	{  //���� ������������ɫ���ӣ� +1
		//ֻ�е���ɫ�������ӵ�ʱ��Ż��˳�whileѭ�������˱߽磩��
		raditemp +=1;

		bit_WS_rowNum +=1;

		virt_xtemp +=1;
		virt_ytemp -= 1;  
		if(virt_xtemp>14)	
		{//�����˳�
			bIfxOutside = 1;
			break; 
		}
		if(virt_ytemp<0)	
		{//�����˳�
			bIfyOutside = 1;
			break; 
		}
	}

	//--start--��������β �հ�λ����
	if((raditemp <radii) && 
		!bIfxOutside  && !bIfyOutside  &&  !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit�� δ���磬���ǻ��� 
	{//�����м����հ���λ  ,��ʱֻ������λ
		raditemp +=1;
		WS_lastNoneNum +=1;
		virt_xtemp +=1;  // see next  bit if none 
		virt_ytemp -=1;  // see next  bit if none 
		if((raditemp <radii) &&
			(virt_xtemp<15)&&(virt_ytemp>0))
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  WS_lastNoneNum +=1;
			else    //��һ�������
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //����ͬɫ
				{
					WS_OneGapBit += 1;   //��벿����һ��������
				}
			}
		}
				
	}
	//--end--��������β �հ�λ����

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
			||(!WS_lastNoneFlagBlack & WS_lastNoneFlagFore))&& WS_OneGapBit)   //��ֻ����һλ����  ��4
		{//sigle 4
			retS +=sigleFour;
		}
		else if(((WS_lastNoneFlagBlack & !WS_lastNoneFlagFore ) 
			||(!WS_lastNoneFlagBlack & WS_lastNoneFlagFore))&& !WS_OneGapBit && (WS_lastNoneNum>=2))
		{//s3
			retS +=sigleThree;
		}
//		if(NS_lastNoneNum >=2) //�� ����4���������ܹ�����λ����2��ʱ ����Ϊ ����
//		{
//			NS_GameSta = FreedomOfFour;
//		}
	}else if(2 == bit_WS_rowNum)
	{
		if((WS_lastNoneNum >=4)&& (WS_lastNoneFlagBlack & WS_lastNoneFlagFore))  //�� ����2���������ܹ�����λ���ڵ���4��ʱ ����Ϊ ��2     �տա����տ�
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
		if((WS_lastNoneNum >=4)&& (WS_lastNoneFlagBlack & WS_lastNoneFlagFore))  //�� ����2���������ܹ�����λ���ڵ���4��ʱ ����Ϊ ��2     �տա����տ�
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


// �Խ�Ҫ�µ�һ���ж�
// whobit  0  - �µĺ���   1- �µİ���    foebidden only for black    
// bit  ��������λ  eg�� cChPiece[0][0]
//---------�ж���Ӯ����������  ������˭win ״̬ winSta   0����win   1- ��win   2- ��win ��3-���֣������� (����)
//�������ۻ�ЧӦ����������Ч   forbiddenSta ����״̬
//�������������� retScore
//��;�ڼ�⵽����ʱ������ʧ��
//int &gameSta,  //���ظ���һ������   �������Ӻ�����
//��Ӯ״̬�±ȽϷ����� Ӯ״ֱ̬���¸���
bool cChesser::CheckGameSta(cChessPiece &bit,bool whoBit,int &forbiddenSta,int &winSta,int &gameSta,int &retScore)
{

	int virt_x=0,virt_y=0;
	bool bIfxOutside = 0,bIfyOutside = 0;	//�����־λ
	forbiddenSta= 0;  //�����ֱ�־���㣬��ֹ���У����ֱ�־��1��ʼ
	winSta = NoneWin;
	retScore = 0;
	//        N
	//      W   E
	//        S
	int bit_NS_rowNum = 0;		// Ĭ��0�ӣ����� do- while  
	int bit_NW_rowNum = 0, bit_WE_rowNum = 0, bit_WS_rowNum = 0;  //���е�ͬɫ���Ӹ���
	int NS_lastNoneNum = 0;  //ͬ������ β  ����λ����
	int NW_lastNoneNum = 0,WE_lastNoneNum = 0,WS_lastNoneNum = 0;

	// ����λ   һ��-1�� ����-2    �޿ձ� -0��
	int NSLiveCnt =0;
	int NWLiveCnt =0, WELiveCnt =0, WSLiveCnt =0;

	int NS_OneGapBit = 0;  //������ͬɫ��
	int NW_OneGapBit = 0,WE_OneGapBit = 0,WS_OneGapBit = 0;
	int NS_GameSta =0;  // ���״̬ ��eg �����ģ� ���� ����
	int NW_GameSta =0 ,WE_GameSta =0 ,WS_GameSta =0;

	int virt_xtemp= bit.m_virX;
	int virt_ytemp= bit.m_virY;

	virt_x = virt_xtemp;  //�����Ա���
	virt_y = virt_ytemp;

	//forbidden  cnt 
	int ForbiFourCnt=0;
	int ForbiThreeCnt=0;
	
	// up 
//	if( !((virt_ytemp -1) <0) ){ // ����δ����
//		if (cChPiece[virt_xtemp][virt_ytemp -1].m_bBitDisplayState)// ��λ������
//		{
//			if(cChPiece[virt_xtemp][virt_ytemp -1].m_bBitWOrBState == whoBit)   //m_bBitWOrBState  0-hei  1 bai
//			bit_RowNum +=1;
//		}
//	}else{  //���г��磬����ز�����
//		if(cChPiece[virt_xtemp][virt_ytemp +1].m_bBitDisplayState)  //bool m_bBitWOrBState;	 //��λ��/��״̬ 0-�ڣ�1-��
//	}

//--start NS----------------------------------------------------------------------------------------------
	virt_xtemp = virt_x; 
	virt_ytemp = virt_y;
	do  //up&&down
	{ //up
		bit_NS_rowNum +=1;
		virt_ytemp -=1;
		if(virt_ytemp<0)	
		{//�����˳�
			bIfyOutside = 1;
			break; 
		}
	}while(cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)));  //���� ������������ɫ���ӣ� +1
//	if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)||
//		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit))//ֻ�е���ɫ�������ӵ�ʱ��Żᵽ������˱߽磩��

	if(!bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit�� δ���磬���ǻ��� 
	{//�����м����հ���λ  ,��ʱֻ����3λ
		NS_lastNoneNum +=1;
		NSLiveCnt +=1;
		virt_ytemp -=1;  // see next  bit if none 
		if(virt_ytemp>=0)   //note��һ������λ֮�󣬿��ܻ������һ���Լ���ͬɫ��!!
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
			{
				NS_lastNoneNum +=1;
				virt_ytemp -=1;  // see next  bit if none 
				if(virt_ytemp>=0)   //note��һ������λ֮�󣬿��ܻ������һ���Լ���ͬɫ��!!
				{
					if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
					{
						NS_lastNoneNum +=1;
					}
				}
			}
			else    //��һ�������?
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //����ͬɫ
				{
					NS_OneGapBit = 1;   //ǰ�벿����һ��������
				}
			}
		}
	}
	
	virt_xtemp = virt_x; 
	virt_ytemp = virt_y;
	bIfyOutside = 0;  //��߽�
	virt_ytemp +=1;  //��λ

	//up&&down
	//------down // �����ܹ� ��+1��  ��while 
	while(cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)))
	{  //���� ������������ɫ���ӣ� +1
		//ֻ�е���ɫ�������ӵ�ʱ��Ż��˳�whileѭ�������˱߽磩��
		bit_NS_rowNum +=1;
		virt_ytemp +=1;
		if(virt_ytemp>14)	
		{//�����˳�
			bIfyOutside = 1;
			break; 
		}
	}

	//--start--��������β �հ�λ����
	if(!bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit�� δ���磬���ǻ��� 
	{//�����м����հ���λ  ,��ʱֻ����3λ
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
			else    //��һ�������
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //����ͬɫ
				{
					NS_OneGapBit += 1;   //��벿����һ��������
				}
			}
		}
	}
	//--end--��������β �հ�λ����

	//-------check-start---
	if(bit_NS_rowNum>5) // check the bit number in a row;  
	{
		if(!whoBit) // ���峤������
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
			if(!forbiddenSta)  // note : �ں���ȡʤ֮ǰ��Ҫ��������жϣ�������--------��2014-12-7�� 
			{
				winSta = BlackPlayerWin;
			}
		}else  //white is win 
		{
			winSta = WhitePlayerWin;
		}

	}else if(4 == bit_NS_rowNum)
	{
		if((NSLiveCnt ==2) &&(NS_lastNoneNum >=2)) //�� ����4��������jun live ,�ܹ�����λ����2��ʱ ����Ϊ ����
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
		if((NSLiveCnt ==2) && (NS_lastNoneNum >=3))  //�� ����3���������ܹ�����λ���ڵ���4��ʱ ����Ϊ ����     �տա������տ�
		{//live 3
			NS_GameSta = FreedomOfThree;
			ForbiThreeCnt +=1;
		}else if((NSLiveCnt ==1) && (NS_lastNoneNum >=3))  //     �տա������տ�
		{//live 3
			NS_GameSta = SigleThree;
		}
	}else if(2 == bit_NS_rowNum )
	{
		if((NSLiveCnt ==2) && (NS_lastNoneNum >=4))  //�� ����2���������ܹ�����λ���ڵ���4��ʱ ����Ϊ ��2     �տա������տ�
		{//live 3
			NS_GameSta = FreedomOfTwo;
		}else if((NSLiveCnt ==1) && (NS_lastNoneNum >=4))  //     �տա������տ�
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
		{//�����˳�
			bIfyOutside = 1;
			break; 
		}
		if(virt_xtemp<0)	
		{//�����˳�
			bIfxOutside = 1;
			break; 
		}
	}while(cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)));  //���� ������������ɫ���ӣ� +1

	if(!bIfxOutside && !bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit�� δ���磬���ǻ��� 
	{//�����м����հ���λ  ,��ʱֻ����3λ
		NW_lastNoneNum +=1;
		NWLiveCnt +=1;
		virt_ytemp -=1;  // see next  bit if none 
		virt_xtemp -=1; 
		if((virt_ytemp>=0) &&(virt_xtemp>=0))   //note��һ������λ֮�󣬿��ܻ������һ���Լ���ͬɫ��!!
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
			{
				NW_lastNoneNum +=1;
				virt_ytemp -=1;  // see next  bit if none 
				virt_xtemp -=1; 
				if((virt_ytemp>=0) &&(virt_xtemp>=0))   //note��һ������λ֮�󣬿��ܻ������һ���Լ���ͬɫ��!!
				{
					if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
					{
						NW_lastNoneNum +=1;
					}
				}
			}
			else    //��һ�������
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //����ͬɫ
				{
					NW_OneGapBit = 1;   //ǰ�벿����һ��������
				}
			}
		}
	}
	
	virt_xtemp = virt_x;   //��ԭֵ
	virt_ytemp = virt_y;
	bIfxOutside = 0;  //��߽�
	bIfyOutside = 0;  //��߽�
	virt_ytemp += 1;  //��λ
	virt_xtemp += 1;  //��λ

	////NW&&SE
	//------SE // �����ܹ� ��+1��  ��while 
	while(cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)))
	{  //���� ������������ɫ���ӣ� +1
		//ֻ�е���ɫ�������ӵ�ʱ��Ż��˳�whileѭ�������˱߽磩��
		bit_NW_rowNum +=1;
		virt_ytemp +=1;
		virt_xtemp +=1;
		if(virt_ytemp>14)	
		{//�����˳�
			bIfyOutside = 1;
			break; 
		}
		if(virt_xtemp>14)	
		{//�����˳�
			bIfxOutside = 1;
			break; 
		}
	}

	//--start--��������β �հ�λ����
	if(!bIfxOutside && !bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit�� δ���磬���ǻ��� 
	{//�����м����հ���λ  ,��ʱֻ������λ
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
			else    //��һ�������
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //����ͬɫ
				{
					NW_OneGapBit += 1;   //��벿����һ��������
				}
			}
		}
				
	}
	//--end--��������β �հ�λ����

	//-------check-start---
if(bit_NW_rowNum>5) // check the bit number in a row;  
	{
		if(!whoBit) // ���峤������
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
			if(!forbiddenSta)  // note : �ں���ȡʤ֮ǰ��Ҫ��������жϣ�������--------��2014-12-7�� 
			{
				winSta = BlackPlayerWin;
			}
		}else  //white is win 
		{
			winSta = WhitePlayerWin;
		}

	}else if(4 == bit_NW_rowNum)
	{
		if((NWLiveCnt ==2) &&(NW_lastNoneNum >=2)) //�� ����4��������jun live ,�ܹ�����λ����2��ʱ ����Ϊ ����
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
		if((NWLiveCnt ==2) && (NW_lastNoneNum >=3))  //�� ����3���������ܹ�����λ���ڵ���4��ʱ ����Ϊ ����     �տա������տ�
		{//live 3
			NW_GameSta = FreedomOfThree;
			ForbiThreeCnt +=1;
		}else if((NWLiveCnt ==1) && (NW_lastNoneNum >=3))  //     �տա������տ�
		{//live 3
			NW_GameSta = SigleThree;
		}
	}else if(2 == bit_NW_rowNum )
	{
		if((NWLiveCnt ==2) && (NW_lastNoneNum >=4))  //�� ����2���������ܹ�����λ���ڵ���4��ʱ ����Ϊ ��2     �տա������տ�
		{//live 3
			NW_GameSta = FreedomOfTwo;
		}else if((NWLiveCnt ==1) && (NW_lastNoneNum >=4))  //     �տա������տ�
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
		virt_xtemp -=1;	//x-1, y ����
	//	if(virt_ytemp<0)	
	//	{//�����˳�
	//		bIfyOutside = 1;
	//		break; 
	//	}
		if(virt_xtemp<0)	
		{//�����˳�
			bIfxOutside = 1;
			break; 
		}
	}while(cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)));  //���� ������������ɫ���ӣ� +1

	if(!bIfxOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit�� δ���磬���ǻ��� 
	{//�����м����հ���λ  ,��ʱֻ������λ
		WE_lastNoneNum +=1;
		WELiveCnt +=1;
	//	virt_ytemp -=1;  // see next  bit if none 
		virt_xtemp -=1; 
		if(virt_xtemp>=0)   //note��һ������λ֮�󣬿��ܻ������һ���Լ���ͬɫ��!!-------------------
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
			{
				WE_lastNoneNum +=1;
				virt_xtemp -=1; 
				if(virt_xtemp>=0)   //note��һ������λ֮�󣬿��ܻ������һ���Լ���ͬɫ��!!-------------------
				{
					if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
					{
						WE_lastNoneNum +=1;
					}
				}
			}
			else    //��һ�������
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //����ͬɫ
				{
					WE_OneGapBit = 1;   //ǰ�벿����һ��������
				}
			}
		}
	}
	
	virt_xtemp = virt_x;   //��ԭֵ
	virt_ytemp = virt_y;
	bIfxOutside = 0;  //��߽�
	virt_xtemp += 1;  //��λ

	////WE
	//------WE // �����ܹ� ��+1��  ��while 
	while(cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)))
	{  //���� ������������ɫ���ӣ� +1
		//ֻ�е���ɫ�������ӵ�ʱ��Ż��˳�whileѭ�������˱߽磩��
		bit_WE_rowNum +=1;
		virt_xtemp +=1;
		if(virt_xtemp>14)	
		{//�����˳�
			bIfxOutside = 1;
			break; 
		}
	}

	//--start--��������β �հ�λ����
	if(!bIfxOutside  && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit�� δ���磬���ǻ��� 
	{//�����м����հ���λ  ,��ʱֻ������λ
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
			else    //��һ�������
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //����ͬɫ
				{
					WE_OneGapBit += 1;   //��벿����һ��������
				}
			}
		}
				
	}
	//--end--��������β �հ�λ����

	//-------check-start---


if(bit_WE_rowNum>5) // check the bit number in a row;  
	{
		if(!whoBit) // ���峤������
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
			if(!forbiddenSta)  // note : �ں���ȡʤ֮ǰ��Ҫ��������жϣ�������--------��2014-12-7�� 
			{
				winSta = BlackPlayerWin;
			}
		}else  //white is win 
		{
			winSta = WhitePlayerWin;
		}

	}else if(4 == bit_WE_rowNum)
	{
		if((WELiveCnt ==2) &&(WE_lastNoneNum >=2)) //�� ����4��������jun live ,�ܹ�����λ����2��ʱ ����Ϊ ����
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
		if((WELiveCnt ==2) && (WE_lastNoneNum >=3))  //�� ����3���������ܹ�����λ���ڵ���4��ʱ ����Ϊ ����     �տա������տ�
		{//live 3
			WE_GameSta = FreedomOfThree;
			ForbiThreeCnt +=1;
		}else if((WELiveCnt ==1) && (WE_lastNoneNum >=3))  //     �տա������տ�
		{//live 3
			WE_GameSta = SigleThree;
		}
	}else if(2 == bit_WE_rowNum )
	{
		if((WELiveCnt ==2) && (WE_lastNoneNum >=4))  //�� ����2���������ܹ�����λ���ڵ���4��ʱ ����Ϊ ��2     �տա������տ�
		{//live 3
			WE_GameSta = FreedomOfTwo;
		}else if((WELiveCnt ==1) && (WE_lastNoneNum >=4))  //     �տա������տ�
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
		virt_xtemp -=1;	//x-1, y ����
		if(virt_ytemp>14)	
		{//�����˳�
			bIfyOutside = 1;
			break; 
		}
		if(virt_xtemp<0)	
		{//�����˳�
			bIfxOutside = 1;
			break; 
		}
	}while(cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)));  //���� ������������ɫ���ӣ� +1

	if(!bIfxOutside && !bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit�� δ���磬���ǻ��� 
	{//�����м����հ���λ  ,��ʱֻ������λ
		WS_lastNoneNum +=1;
		WSLiveCnt +=1;
		virt_ytemp +=1;  // see next  bit if none 
		virt_xtemp -=1; 
		if((virt_xtemp>=0)&&(virt_ytemp<15))   //note��һ������λ֮�󣬿��ܻ������һ���Լ���ͬɫ��!!-------------------
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
			{
				WS_lastNoneNum +=1;
					virt_ytemp +=1;  // see next  bit if none 
				virt_xtemp -=1; 
				if((virt_xtemp>=0)&&(virt_ytemp<15))   //note��һ������λ֮�󣬿��ܻ������һ���Լ���ͬɫ��!!-------------------
				{
					if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  
					{
						WS_lastNoneNum +=1;
					}
				}
			}
			else    //��һ�������
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //����ͬɫ
				{
					WS_OneGapBit = 1;   //ǰ�벿����һ��������
				}
			}
		}
	}
	
	virt_xtemp = virt_x;   //��ԭֵ
	virt_ytemp = virt_y;
	bIfxOutside = 0;  //��߽�
	bIfyOutside = 0;  //��߽�
	virt_xtemp += 1;  //��λ
	virt_ytemp -= 1;  //��λ

	////Ws&&NE
	//------NE // �����ܹ� ��+1��  ��while 
	while(cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)))
	{  //���� ������������ɫ���ӣ� +1
		//ֻ�е���ɫ�������ӵ�ʱ��Ż��˳�whileѭ�������˱߽磩��
		bit_WS_rowNum +=1;
		virt_xtemp +=1;
		virt_ytemp -= 1;  
		if(virt_xtemp>14)	
		{//�����˳�
			bIfxOutside = 1;
			break; 
		}
		if(virt_ytemp<0)	
		{//�����˳�
			bIfyOutside = 1;
			break; 
		}
	}

	//--start--��������β �հ�λ����
	if(!bIfxOutside  && !bIfyOutside  &&  !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit�� δ���磬���ǻ��� 
	{//�����м����հ���λ  ,��ʱֻ������λ
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
			else    //��һ�������
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit))  //����ͬɫ
				{
					WS_OneGapBit += 1;   //��벿����һ��������
				}
			}
		}
				
	}
	//--end--��������β �հ�λ����

	//-------check-start---

if(bit_WS_rowNum>5) // check the bit number in a row;  
	{
		if(!whoBit) // ���峤������
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
			if(!forbiddenSta)  // note : �ں���ȡʤ֮ǰ��Ҫ��������жϣ�������--------��2014-12-7�� 
			{
				winSta = BlackPlayerWin;
			}
		}else  //white is win 
		{
			winSta = WhitePlayerWin;
		}

	}else if(4 == bit_WS_rowNum)
	{
		if((WSLiveCnt ==2) &&(WS_lastNoneNum >=2)) //�� ����4��������jun live ,�ܹ�����λ����2��ʱ ����Ϊ ����
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
		if((WSLiveCnt ==2) && (WS_lastNoneNum >=3))  //�� ����3���������ܹ�����λ���ڵ���4��ʱ ����Ϊ ����     �տա������տ�
		{//live 3
			WS_GameSta = FreedomOfThree;
			ForbiThreeCnt +=1;
		}else if((WSLiveCnt ==1) && (WS_lastNoneNum >=3))  //     �տա������տ�
		{//live 3
			WS_GameSta = SigleThree;
		}
	}else if(2 == bit_WS_rowNum )
	{
		if((WSLiveCnt ==2) && (WS_lastNoneNum >=4))  //�� ����2���������ܹ�����λ���ڵ���4��ʱ ����Ϊ ��2     �տա������տ�
		{//live 3
			WS_GameSta = FreedomOfTwo;
		}else if((WSLiveCnt ==1) && (WS_lastNoneNum >=4))  //     �տա������տ�
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

//	if(winSta) // �Ѿ���ĳһ��ʤ��
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
		}//  NS_GameSta =0;  // ���״̬ ��eg �����ģ� ����  NW_GameSta =0 ,WE_GameSta =0 ,WS_GameSta =0;
		else //û����һ������ʤ�������ص�ǰ��Ҫ����� 
		{//��¼���
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