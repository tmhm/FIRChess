#include "stdafx.h"
#include <windows.h>
//#include <stdio.h>
//#include <conio.h>
#include "cChessPiece.h"
//#include <iostream.h>

int cChessPiece::m_iChessReadyCnt=0;	//�����Ӹ�����¼����̬��Ա����ʼ��

cChessPiece::cChessPiece()
{
//	m_iChessBitScore=0;//[i][j]=0;

}

cChessPiece::~cChessPiece()
{
 
}


void cChessPiece::chessBitSetScore(int chessBit)  // 0  ���壻 1  ����
{

}


bool cChessPiece::MarkScore(int radii ,  //���ְ뾶
							cBaseAI &bAi ,  //�ϴ������
							cBaseAI &nextBit, //�´����������
							int &retScore)   //�����ϴ���õ��ķ�
{
//	if(bAi.m_bBitDisplayState && !bAi.m_bBitWOrBState)  //��ʾ�ĺ���
//	{		
//	}


//	return 0;
/*
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
	}while((raditemp <3) && cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)));  //���� ������������ɫ���ӣ� +1

	if((raditemp <3) && !bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit�� δ���磬���ǻ��� 
	{//�����м����հ���λ  ,��ʱֻ������λ
		raditemp +=1;
		NS_lastNoneNum +=1;  
		NS_lastNoneFlagFore = 1;
		virt_ytemp -=1;  // see next  bit if none 
		if((raditemp <3) &&virt_ytemp>=0)   //note��һ������λ֮�󣬿��ܻ������һ���Լ���ͬɫ��!!
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  NS_lastNoneNum +=1;
			else    //��һ�������
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState && whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState && !whoBit))  //����ͬɫ
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
	while((raditemp <3) && 
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
	if((raditemp <3) && 
		!bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit�� δ���磬���ǻ��� 
	{//�����м����հ���λ  ,��ʱֻ������λ
		raditemp +=1;
		NS_lastNoneNum +=1;
		NS_lastNoneFlagBlack =1;
		virt_ytemp +=1;  // see next  bit if none 
		if((raditemp <3) && virt_ytemp<15)
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

//ֻ�޸������·��򣡣���ͬɫ��=================================

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
		{//s
			retS +=sigleOne;

		}
	}

	//------end check-------

//=========end WE--------------------- -----------------------------------------

//--sta-r-t- W--S--&--&--NE-------------------------------------------------------------------------

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

//--end WS&&NE----------------------------------------------------------------------------------

	if(winSta) // �Ѿ���ĳһ��ʤ��
	{
		if(BlackPlayerWin == winSta ) {
			FirAlert(AlertXY ,"����ʤ"); 
		}
		else if(WhitePlayerWin ==  winSta){
			FirAlert(AlertXY ,"����ʤ"); 
		}
	}
	return true;

*/

	return true;
}

//--------------------��ʾ״̬------------------------------
bool cChessPiece::bGetDisplaySta(cChessPiece &bit)//��ȡһ�����ӵ���ʾ״̬����
{
	return bit.m_bBitDisplayState;
}

void cChessPiece::SetDisplaySta(cChessPiece &bit)//����һ�����ӵ���ʾ״̬����
{
	bit.m_bBitDisplayState =1;
	m_iChessReadyCnt +=1;   //�����Ӹ���  +1

}
void cChessPiece::ResetDisplaySta(cChessPiece &bit)//����һ�����ӵ���ʾ״̬����
{
	bit.m_bBitDisplayState =0;
	m_iChessReadyCnt -=1;   //�����Ӹ���  -1

}

//--------------------�ڰ�״̬------------------------------
//��λ��/��״̬ 0-�ڣ�1-��
bool cChessPiece::bGetWOrBSta(cChessPiece &bit)//��ȡһ�����ӵĺڰ�״̬����
{
	return bit.m_bBitWOrBState;
}

void cChessPiece::SetWOrBSta(cChessPiece &bit , bool sta)//����һ�����ӵĺڰ�״̬����
{
	//if(!sta)
	bit.m_bBitWOrBState = sta;
}
//-----------------------��������---------------------------
int cChessPiece::iGetScore(cChessPiece &bit)//��ȡһ�����ӵķ�������
{
	return bit.m_iBitscore;
}

void cChessPiece::iSetScore(cChessPiece &bit, int score)//����һ�����ӵķ�������
{
	bit.m_iBitscore = score;
}
//------------------------------------------------------------------
int cChessPiece::iretReadyChessCnt()//��ȡ������������
{
	return m_iChessReadyCnt;
}

void cChessPiece::setReadyAllCnt()
{
	m_iChessReadyCnt =256;
}

//-----------------------------------------------------------
//bool CallMoveToAnyBit(cBaseAI &bAi,bool state)
//{
//	bAi.MoveToAny
//}

bool cChessPiece::MoveToAnyBit(cBaseAI &bAi , bool state)
{
	if(!state)//����
	{
		bAi.m_bBitWOrBState=0;		//��������
		bAi.m_bBitDisplayState=1;	//mark showed
	}else
	{
		bAi.m_bBitWOrBState=1;		//��������
		bAi.m_bBitDisplayState=1;	//mark showed
	}
	


	return true;
//	return 1;

}


