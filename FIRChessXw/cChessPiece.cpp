#include "stdafx.h"
#include <windows.h>
//#include <stdio.h>
//#include <conio.h>
#include "cChessPiece.h"
//#include <iostream.h>

int cChessPiece::m_iChessReadyCnt=0;	//已下子个数记录，静态成员，初始化

cChessPiece::cChessPiece()
{
//	m_iChessBitScore=0;//[i][j]=0;

}

cChessPiece::~cChessPiece()
{
 
}


void cChessPiece::chessBitSetScore(int chessBit)  // 0  黑棋； 1  白棋
{

}


bool cChessPiece::MarkScore(int radii ,  //评分半径
							cBaseAI &bAi ,  //上次下棋点
							cBaseAI &nextBit, //下次最优下棋点
							int &retScore)   //下完上次棋得到的分
{
//	if(bAi.m_bBitDisplayState && !bAi.m_bBitWOrBState)  //显示的黑子
//	{		
//	}


//	return 0;
/*
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
	}while((raditemp <3) && cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState  && 
		((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & whoBit) || 
		(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState & !whoBit)));  //有子 并等于所下颜色的子， +1

	if((raditemp <3) && !bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit， 未出界，考虑活棋 
	{//考虑有几个空白棋位  ,暂时只考虑两位
		raditemp +=1;
		NS_lastNoneNum +=1;  
		NS_lastNoneFlagFore = 1;
		virt_ytemp -=1;  // see next  bit if none 
		if((raditemp <3) &&virt_ytemp>=0)   //note：一个空棋位之后，可能还会出项一个自己的同色棋!!
		{
			if(!cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState)  NS_lastNoneNum +=1;
			else    //跳一格后有子
			{
				if((cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState && whoBit) || 
					(!cChPiece[virt_xtemp][virt_ytemp].m_bBitWOrBState && !whoBit))  //跳子同色
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
	while((raditemp <3) && 
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
	if((raditemp <3) && 
		!bIfyOutside && !cChPiece[virt_xtemp][virt_ytemp].m_bBitDisplayState) //none bit， 未出界，考虑活棋 
	{//考虑有几个空白棋位  ,暂时只考虑两位
		raditemp +=1;
		NS_lastNoneNum +=1;
		NS_lastNoneFlagBlack =1;
		virt_ytemp +=1;  // see next  bit if none 
		if((raditemp <3) && virt_ytemp<15)
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

//只修改了上下方向！！仅同色分=================================

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

//--end WS&&NE----------------------------------------------------------------------------------

	if(winSta) // 已经有某一方胜出
	{
		if(BlackPlayerWin == winSta ) {
			FirAlert(AlertXY ,"黑棋胜"); 
		}
		else if(WhitePlayerWin ==  winSta){
			FirAlert(AlertXY ,"白棋胜"); 
		}
	}
	return true;

*/

	return true;
}

//--------------------显示状态------------------------------
bool cChessPiece::bGetDisplaySta(cChessPiece &bit)//获取一个棋子的显示状态属性
{
	return bit.m_bBitDisplayState;
}

void cChessPiece::SetDisplaySta(cChessPiece &bit)//设置一个棋子的显示状态属性
{
	bit.m_bBitDisplayState =1;
	m_iChessReadyCnt +=1;   //已下子个数  +1

}
void cChessPiece::ResetDisplaySta(cChessPiece &bit)//设置一个棋子的显示状态属性
{
	bit.m_bBitDisplayState =0;
	m_iChessReadyCnt -=1;   //已下子个数  -1

}

//--------------------黑白状态------------------------------
//棋位黑/白状态 0-黑；1-白
bool cChessPiece::bGetWOrBSta(cChessPiece &bit)//获取一个棋子的黑白状态属性
{
	return bit.m_bBitWOrBState;
}

void cChessPiece::SetWOrBSta(cChessPiece &bit , bool sta)//设置一个棋子的黑白状态属性
{
	//if(!sta)
	bit.m_bBitWOrBState = sta;
}
//-----------------------分数属性---------------------------
int cChessPiece::iGetScore(cChessPiece &bit)//获取一个棋子的分数属性
{
	return bit.m_iBitscore;
}

void cChessPiece::iSetScore(cChessPiece &bit, int score)//设置一个棋子的分数属性
{
	bit.m_iBitscore = score;
}
//------------------------------------------------------------------
int cChessPiece::iretReadyChessCnt()//获取已下棋子数量
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
	if(!state)//黑子
	{
		bAi.m_bBitWOrBState=0;		//黑子属性
		bAi.m_bBitDisplayState=1;	//mark showed
	}else
	{
		bAi.m_bBitWOrBState=1;		//白子属性
		bAi.m_bBitDisplayState=1;	//mark showed
	}
	


	return true;
//	return 1;

}


