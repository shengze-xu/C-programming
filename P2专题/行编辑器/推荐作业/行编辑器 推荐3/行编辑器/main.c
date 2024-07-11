#include "acllib.h"
#include <stdio.h>
#include "function.h"

int Setup(){
	initWindow("行编辑器",0,0,600,600);
	initConsole();
	printf("本产品包含功能：左右方向键、回退和删除键、ins切换插入和覆盖状态、鼠标点击控制光标位置\n不支持输入中文，输入结束请按回车\n");
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
