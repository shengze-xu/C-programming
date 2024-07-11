/*this program is written by Zhao Hongjue, finished on 4/15/2020
Project 2: Row Edit 
teacher: Weng Kai    C program
remember to add acllib to this project.
*/

#include <stdio.h>
#include <stdlib.h>
#include "acllib.h"
#include "row.h"
#include "edit.h"

#define WinWidth 1200 
#define WinHeight 100
#define charsize 100
#define maxn 15
#define delta 51 

int i;//used to know where the caret is
List list={NULL,NULL};
int caretwid=3; 

void keyboard_listener(int key,int event); 
void char_listener(char key); 
void mouse_listener(int x,int y,int button,int event);
void time_listener(int timeID);

int Setup()
{
	initConsole();
	
	initWindow("row_edit",DEFAULT,DEFAULT,WinWidth,WinHeight);
	
	beginPaint();
	setTextSize(charsize);

	startTimer(0,500);
	registerKeyboardEvent(keyboard_listener);
	registerCharEvent(char_listener);
	registerMouseEvent(mouse_listener);
	registerTimerEvent(time_listener);
	endPaint();
	return 0;
 }
 
void keyboard_listener(int key,int event){
	if(event==0){
		switch(key){
			case 37: LEFT(&i);break;//left
			case 39: RIGHT(&list,&i);break;//right
			case 13: ENTER(&list,&i);break;//enter
			case 45: INSERT(&caretwid,i);break;//insert
			case 46: deletekey(&list,&i);break;//delete
			case 8: BACKSPACE(&list,&i);break;//backspace;
			case 35: END(&list,&i);break;//end
			case 36: HOME(&i);break;//home
		}
	}
	putCaret(i);	
} 

void char_listener(char key){
	if(key!=13&&key!=8){//is not backspace or enter
		if(caretwid==3)list_getin(&list,key,i);
		else{
			if(i==list_size(&list))list_getin(&list,key,i);
			else list_set(&list,i,key);
		}
		print(&list);
		i++; 
	}
	putCaret(i);	
}

void mouse_listener(int x,int y,int button,int event){
	if(button==1&&event==0){
		int cnt=list_size(&list), j;
		for(j=0;j<cnt;j++){
			if(x>=j*delta&&x<(j+1)*delta){
				i=j;
				break;
			}
		}
		if(x>=cnt*delta){
			i=cnt;
		}
	}
	putCaret(i);
}

void time_listener(int timeID){
	static flag=1;
	setCaretSize(caretwid,100);

	if(flag==1){
		showCaret();
		flag=0;
	}
	else{
		hideCaret();
		flag=1;
	}
}
