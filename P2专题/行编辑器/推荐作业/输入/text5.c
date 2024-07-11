#include "graphics.h"
#include "extgraph.h"
#include "genlib.h"
#include "simpio.h"
#include "random.h"
#include "strlib.h"
#include "conio.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <stddef.h>

#include <windows.h>
#include <olectl.h>
#include <mmsystem.h>
#include <wingdi.h>
#include <ole2.h>
#include <ocidl.h>
#include <winuser.h>
char str[1000]="";	
int s,x; 
int k=1;
void CharEventProcess(char c);
void KeyboardEventProcess(int key,int event);
void Main()
{
	InitGraphics();
	registerCharEvent(CharEventProcess);
	registerKeyboardEvent(KeyboardEventProcess);
} 
void KeyboardEventProcess(int key,int event)
{
	if(k)
	{
	switch (event) {
	 	case KEY_DOWN:
			switch (key) {
			    case VK_LEFT:
			    	if(x==0)break;
			    	x--;
			    	break;
			    case VK_RIGHT:
			    	if(x==s)break;
			    	x++;
			    	break;
			}
		case KEY_UP:
			 break;
	 }
	}
} 
void CharEventProcess(char c)
{
	int i;
	if(k)
	{
	switch(c)
	{
		case '\r':
			k--;
			InitConsole();
			printf("%s",str);
			break;
		case '\b':
			if(x==0)break;
			for(i=x-1;i<s;i++)str[i]=str[i+1];
			s--;
			x--;
			InitGraphics();
			MovePen(2.0,2.0);
			DrawTextString(str);
			break;
		default:
			for(i=s+1;i>x;i--)str[i]=str[i-1];
			str[x]=c;
			s++;
			x++;
			InitGraphics();
			MovePen(2.0,2.0);
			DrawTextString(str);
			break;
	}
	}
}

