#include <stdio.h>
#include <math.h>
#include <string.h>
#include "acllib.h"
#include "function.h"
#include "callback.h"

#define width 1500
#define height 300
#define theight 60
#define twidth 30


int Setup(){
	initConsole();	
	initWindow("row_edit",DEFAULT,DEFAULT,width,height);
	
	beginPaint();
    registerCharEvent(CharListener);
	registerKeyboardEvent(KeyListener);
	registerMouseEvent(MouseListener);
	endPaint();
	
	return 0; 
}

