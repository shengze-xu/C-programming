#include "acllib.h"
#include <stdio.h>
#include "function.h"

int Setup(){
	initWindow("�б༭��",0,0,600,600);
	initConsole();
	printf("����Ʒ�������ܣ����ҷ���������˺�ɾ������ins�л�����͸���״̬����������ƹ��λ��\n��֧���������ģ���������밴�س�\n");
	beginPaint();
	setTextColor(BLACK);
	setPenColor(WHITE);
	setBrushColor(WHITE);
	setTextSize(20);
	setCaretSize(2,20);
	setCaretPos(0,0);
	showCaret();
	registerCharEvent(CharListener);
    registerKeyboardEvent(KeyListener);
    registerMouseEvent(Mouselistener);
	
	
	
	
	endPaint();
	
	
	
	return 0;
} 
