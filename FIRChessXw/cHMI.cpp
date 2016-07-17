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

void cHMI::FirAlert(COORD xy ,char *ch)//���潻��
{
	COORD xyTemp=xy;
	
	SetConsoleCursorPosition(hOut, xyTemp); 
	xyTemp.Y +=1;
	printf("��������������������������������������");	SetConsoleCursorPosition(hOut, xyTemp); xyTemp.Y +=1;
	printf("��                                  ��");	SetConsoleCursorPosition(hOut, xyTemp); xyTemp.Y -=1;xyTemp.X +=2;
	printf("��������������������������������������"); SetConsoleCursorPosition(hOut, xyTemp); 
	printf(ch);

}


void cHMI::SelectOption(COORD xyBottom,  //ѡ������������		�������¼�ѡ��spaceȷ��
				   COORD xyTop, 
				   COORD &re)	//����ѡ�������
{
	SetSignOpt(100, 1);
	SetConsoleCursorPosition(hOut, xyBottom);

	DWORD			dwRes;
	WORD			dwState=0;
	INPUT_RECORD	keyRec;
	CONSOLE_SCREEN_BUFFER_INFO bInfo;
	COORD hmipos;

	bool keySpaceDoFlagTemp=0;  //δ����ȷ���ͷ����Ӽ�
	while(!keySpaceDoFlagTemp)  //û�а���һֱɨ��
	{
 		ReadConsoleInput(hIn, &keyRec, 1, &dwRes);

		if (keyRec.EventType == KEY_EVENT && keyRec.Event.KeyEvent.bKeyDown)
		{			// 
				GetConsoleScreenBufferInfo(hOut, &bInfo);
				hmipos = bInfo.dwCursorPosition;
				dwState = keyRec.Event.KeyEvent.wVirtualKeyCode;
				if(dwState == VK_UP){
					hmipos.Y -= 1;
					if(hmipos.Y<xyBottom.Y)	hmipos.Y +=(xyTop.Y  - xyBottom.Y +1) ;  //����ѭ��ѡ������Ч��
				}else if(dwState == VK_DOWN){	//
					hmipos.Y += 1;				
					if(hmipos.Y>xyTop.Y)	hmipos.Y -=(xyTop.Y  - xyBottom.Y +1);  //����ѭ��ѡ������Ч��
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
	printf("��   a.����ģʽ                   ��");	setPos(hOut, 40, 9);
	printf("��   b.����ģʽ                   ��");	setPos(hOut, 40, 10);
	printf("������������������������������������");	setPos(hOut, 40, 11);
}
void cHMI::showHMPlusSelectF() //������ʾ
{
	setPos(hOut, 40, 6);
	printf("��������ϷģʽΪ��                ��");	setPos(hOut, 40, 7);
	printf("��  1.����ģʽ                    ��");	setPos(hOut, 40, 8);  
	printf("��   a.����ģʽ                   ��");	setPos(hOut, 40, 9);
	printf("��Enjoy yourself!(��������& space)��");	setPos(hOut, 40, 10);
	printf("������������������������������������");	setPos(hOut, 40, 11);
}
void cHMI::showHMPlusSelectB() //������ʾ
{
	setPos(hOut, 40, 6);
	printf("��������ϷģʽΪ��                ��");	setPos(hOut, 40, 7);
	printf("��  1.����ģʽ                    ��");	setPos(hOut, 40, 8);  
	printf("��   b.����ģʽ                   ��");	setPos(hOut, 40, 9);
	printf("��Enjoy yourself!(��������& space)��");	setPos(hOut, 40, 10);
	printf("������������������������������������");	setPos(hOut, 40, 11);
}

//void cHMI::showHHPlus()
//{
//	setPos(hOut, 40, 8);
//	printf("��  a.����ģʽ                    ��");	setPos(hOut, 40, 9);
//	printf("��  b.����ģʽ                    ��");	setPos(hOut, 40, 10);
//	printf("������������������������������������");	setPos(hOut, 40, 11);
//}

void cHMI::showHHPlusSelect()  //������ʾ
{
	setPos(hOut, 40, 6);
	printf("��������ϷģʽΪ��                ��");	setPos(hOut, 40, 7);
	printf("��  2.˫��ģʽ                    ��");	setPos(hOut, 40, 8);  
	printf("��    Ĭ�Ϻ�������                ��");	setPos(hOut, 40, 9);
	printf("��Enjoy yourself!(��������& space)��");	setPos(hOut, 40, 10);
	printf("������������������������������������");	setPos(hOut, 40, 11);
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
		printf("������������������������������������");	setPos(hOut, 40, 3);
		printf("��NOTE:                           ��");	setPos(hOut, 40, 4);
		printf("����ʹ�÷����ѡ��space��ȷ���� ��");	setPos(hOut, 40, 5);
		printf("��                                ��");	setPos(hOut, 40, 6);
		printf("����Ϸģʽ��                      ��");	setPos(hOut, 40, 7);
		printf("��  1.����ģʽ                    ��");	setPos(hOut, 40, 8);   //(��)
		printf("��  2.˫��ģʽ                    ��");	setPos(hOut, 40, 9);
		printf("������������������������������������");	setPos(hOut, 40, 10);

		SelectOption(hmiposHMmode,hmiposHHmode,cReCur);
		if(cReCur.Y == hmiposHMmode.Y){
			m_iGameModeHMorHH=1;	//������Ϸ
			showHMPlus();
			SelectOption(hmiposHMplusDown,hmiposHHPlusUp,cReCur);
			if(cReCur.Y == hmiposHMplusFo.Y){//����ģʽ
				m_iGameModeForeorBlack =1;	
				showHMPlusSelectF();
			}
			else if(cReCur.Y == hmiposHHPlusBl.Y){//����ģʽ
					m_iGameModeForeorBlack =2;	
					showHMPlusSelectB(); 
			}

		}
		else if(cReCur.Y == hmiposHHmode.Y){
			m_iGameModeHMorHH=2;	//˫����Ϸ  ��Ĭ���Ⱥ��֣������ã�
			showHHPlusSelect();
		}
}

void cHMI::PutOneBit(bool flag,COORD SitePut)  // 0  ���壻 1  ����
{
			  SetConsoleCursorPosition(hOut, SitePut);
			  if(!flag){
				SetConsoleTextAttribute(hOut, 0x30|0);    //0x00  fore  black�� 0x30 over blue    ����
			  }else{
				SetConsoleTextAttribute(hOut, 0x30|0x0f);  //0x30 over  blue ; 0x0f fore  white   ����
			  }
			  printf("��");

}

void cHMI::setPos(HANDLE hCon, int x, int y)  // ����궨λ��λ�ã�x��y��
	{
		COORD pos = {x, y};
        SetConsoleCursorPosition(hCon, pos); 
	}

//sigNum��С  0��100   ��show   0������ʾ  1-show   
void cHMI::SetSignOpt(int sigNum, bool showSta)
{
	CONSOLE_CURSOR_INFO cINFO;    //  ���״̬
	GetConsoleCursorInfo(hOut ,&cINFO);

	cINFO.dwSize=sigNum;
	cINFO.bVisible=showSta;

	SetConsoleCursorInfo(hOut,&cINFO);  //  ���״̬	
}

void cHMI::DynamicShowHmi()
{
	
}


void cHMI::GetGameMode(int &hhOrhm, int &foreOrBl)// ������Ϸģʽ����
{
	 //��Ϸģʽ:	1-������Ϸ		2-˫����Ϸ������ǰ����
	hhOrhm   =  m_iGameModeHMorHH;	

	foreOrBl =  m_iGameModeForeorBlack;		//�Ⱥ���ѡ��   1-- �����֣�2--�˺���
}

//BlackPlayerWin, WhitePlayerWin,
int cHMI::EndOnceGameOption(COORD endxy , int whowin ,int hhorhn ,int forbOrBla)  //����һ�֣���ʾ�򣬼�����һ�֣������˳�
{

	COORD xyTemp=endxy;
	COORD endPosT={2,18};
	
	SetConsoleCursorPosition(hOut, xyTemp); 
	xyTemp.Y +=1;
	printf("��������������������������������������");	SetConsoleCursorPosition(hOut, xyTemp); xyTemp.Y +=1;
	printf("��                                  ��");	SetConsoleCursorPosition(hOut, xyTemp); xyTemp.Y -=1;xyTemp.X +=2;
	printf("��������������������������������������"); SetConsoleCursorPosition(hOut, xyTemp); 
	if(BlackPlayerWin ==whowin)
	{
	//	printf("������ʤ! Enter--������Esc--�˳�");
		if( 1 ==hhorhn )
		{//dan ren 
			if( 1 == forbOrBla) //ren zai qian 
			{
				printf("��Ӯ��!�밴Esc--�˳�,ллʹ��!");
			
			}else{
				printf("������!�밴Esc--�˳�,ллʹ��!");
			}
		}else
		{
			printf("�����ʤ!�밴Esc--�˳�,ллʹ��!");
		}
		
		SetConsoleCursorPosition(hOut, endPosT);
	}else if(WhitePlayerWin ==whowin)
	{
		if( 1 ==hhorhn )
		{//dan ren 
			if( 2 == forbOrBla) //ren zai qian 
			{
				printf("��Ӯ��!�밴Esc--�˳�,ллʹ��!");
			
			}else{
				printf("������!�밴Esc--�˳�,ллʹ��!");
			}
		}
		else{
		//	printf("������ʤ! Enter--������Esc--�˳�");
			printf("�����ʤ!�밴Esc--�˳�,ллʹ��!");
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

	bool keySpaceDoFlag=0;  //δ����ȷ���ͷ����Ӽ�

	while(!keySpaceDoFlag)  //û�а���һֱɨ��
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


