#include <stdio.h>
#include "acllib.h"
#include <string.h>
#include <winuser.h>
#define MAXN 100
typedef struct b{
    int width;
    int height;
    char str[MAXN][MAXN];
    int cursorStat;
    int cursorPos;
    int isInsert;
    int fontSize;
    int isCap;
    int endWelcome;
    int line;
    int totLine;
    int isCtrl;
    int isSaving;
    char saveStr[MAXN][MAXN];
    int saveLines;
    int saveLine;
    int saveCursorPos;
}Model;
Model model;
char numberMapSymbol[20] = {')', '!', '@', '#', '$', '%', '^', '&', '*', '('};
char keyMap1[20] = {';', '=', ',', '-', '.', '/', '`'};
char keyMapCap1[20] = {':', '+', '<', '_', '>', '?', '~'};
char keyMap2[20] = {'[', '\\', ']', '\''};
char keyMapCap2[20] = {'{', '|', '}', '\"'};
void showSaveScreen();
void initModel() {
    model.width = 1200;
    model.height = 700;
//    strcat(model.str, "test");
    model.cursorStat = 0;
    model.cursorPos = 1;
    model.isInsert = 0;
    model.fontSize = 80;
    model.isCap = 0;
    model.endWelcome = 0;
    model.line = 1;
    model.totLine = 1;
    model.isCtrl = 0;
    model.isSaving = 0;
}
void refresh() {
    if(!model.endWelcome) return;
    beginPaint();
    setBrushColor(WHITE);
    rectangle(0, 0, model.width, model.height);
    int currentX = 10;
    int currentY = 10;
    int i; 
    for(i = 1; i <= model.totLine; i++){
        setTextSize(model.fontSize);
        setTextFont("Consolas");
        paintText(currentX, currentY, model.str[i]);
        currentY += 100;
    }
    currentY = 10;
    currentX += (model.cursorPos - 1) * (model.fontSize - 10) * 0.55 - 5;
    currentY += 100 * (model.line - 1);
    if(model.cursorPos > 17) currentX -= 10;
    if(model.cursorStat == 1) {
        setBrushColor(BLACK);
        if(model.isInsert) {
            rectangle(currentX, currentY, currentX + (model.fontSize - 10) * 0.55 + 5, currentY + 80);
        }
        else {
            rectangle(currentX, currentY, currentX + 5, currentY + 80);
        }
    }
    endPaint();
}
void timer(int id) {
    model.cursorStat ^= 1;
    refresh();
}
void addChar(char ch) {
    char tempstr[MAXN];
    strcpy(tempstr, model.str[model.line]);
    int i;
	for (i = 0; i < model.cursorPos - 1; i++) {
        model.str[model.line][i] = tempstr[i];
    }
    model.str[model.line][model.cursorPos - 1] = ch;
	for (i = model.cursorPos - 1; i < strlen(tempstr); i++) {
        model.str[model.line][i + 1] = tempstr[i];
    }
    model.str[model.line][strlen(tempstr) + 1] = 0;
    model.cursorPos++;
}
void insChar(char ch) {
    char tempstr[MAXN];
    strcpy(tempstr, model.str[model.line]);
    int i;
	for (i = 0; i < model.cursorPos - 1; i++) {
        model.str[model.line][i] = tempstr[i];
    }
    model.str[model.line][model.cursorPos - 1] = ch;
    for (i = model.cursorPos; i < strlen(tempstr); i++) {
        model.str[model.line][i] = tempstr[i];
    }
    model.str[model.line][strlen(tempstr)] = 0;
    model.cursorPos++;
}
void processChar(char ch) {
    if(model.isInsert == 0) {
        addChar(ch);
    } else {
        insChar(ch);
    }
}
void keyListener(int key, int event) {
    if(event == KEY_DOWN) {
        model.endWelcome = 1;
        char ch;
        if(key >= 0x41 && key <= 0x5A) {
            if (model.isCap == 0) {
                ch = key - 0x41 + 'a';
            } else {
                ch = key - 0x41 + 'A';
            }
            if((ch == 's' || ch == 'S') && model.isCtrl) {
                showSaveScreen();
                return;
            }
            processChar(ch);
        } else if(key == 0xA0 || key == 0xA1 || key == 0x10) {
            model.isCap ^= 1;
//            printf("The shift is pressed");
        } else if(key == 0x14) { //Capslock button
            model.isCap ^= 1;
        } else if(key == 0x08) { //backspace button
            if(model.cursorPos > 1) {
                char tempstr[MAXN];
                strcpy(tempstr, model.str[model.line]);
                int i;
				for (i = 0; i < model.cursorPos - 2; i++) {
                    model.str[model.line][i] = tempstr[i];
                }
                for (i = model.cursorPos - 1; i < strlen(tempstr); i++) {
                    model.str[model.line][i - 1] = tempstr[i];
                }
                model.str[model.line][strlen(tempstr) - 1] = 0;
                model.cursorPos--;
            } else {
                if(model.line > 1) {
                    model.line--;
                    model.cursorPos = strlen(model.str[model.line]) + 1;
                    strcat(model.str[model.line], model.str[model.line+1]);
                    int i;
					for(i = model.line+1; i < model.totLine; i++) {
                        strcpy(model.str[i], model.str[i+1]);
                    }
                    model.totLine--;
                }
            }
        } else if(key == 0x2E) { //delete button
            if(model.cursorPos <= strlen(model.str[model.line])) {
                model.cursorPos++;
                char tempstr[MAXN];
                strcpy(tempstr, model.str[model.line]);
                int i;
				for (i = 0; i < model.cursorPos - 2; i++) {
                    model.str[model.line][i] = tempstr[i];
                }
                for (i = model.cursorPos - 1; i < strlen(tempstr); i++) {
                    model.str[model.line][i - 1] = tempstr[i];
                }
                model.str[model.line][strlen(tempstr) - 1] = 0;
                model.cursorPos--;
            } else {
                if(model.totLine > model.line) {
                    strcat(model.str[model.line], model.str[model.line+1]);
                    int i;
					for(i = model.line+1; i < model.totLine; i++) {
                        strcpy(model.str[i], model.str[i+1]);
                    }
                    model.totLine--;
                }
            }
        } else if(key == 0x25) { //Left arrow
            if(model.cursorPos > 1) {
                model.cursorPos--;
            } else {
                if(model.line > 1) {
                    model.line--;
                    model.cursorPos = strlen(model.str[model.line]) + 1;
                }
            }
        } else if(key == 0x27) { //Right arrow
            if(model.cursorPos < strlen(model.str[model.line]) + 1) {
                model.cursorPos++;
            } else {
                if(model.line < model.totLine) {
                    model.line++;
                    model.cursorPos = 1;
                }
            }
        } else if(key == 0x26) { //Up arrow
            if(model.line > 1) {
                model.line--;
                if(model.cursorPos > strlen(model.str[model.line]) + 1) {
                    model.cursorPos = strlen(model.str[model.line]) + 1;
                }
            }
        } else if(key == 0x28) { //Down arrow
            if(model.line < model.totLine) {
                model.line++;
                if(model.cursorPos > strlen(model.str[model.line]) + 1) {
                    model.cursorPos = strlen(model.str[model.line]) + 1;
                }
            }
        } else if(key == 0x2D) {
            model.isInsert ^= 1;
        } else if(key == 0x0D) { //Enter Button
            if(model.isSaving == 1) {
                FILE* fp = fopen(model.str[2], "w");
                int i;
				for(i = 1; i <= model.saveLines; i++) {
                    fprintf(fp, "%s", model.saveStr[i]);
                    fprintf(fp, "\n");
                }
                fclose(fp);
                model.isSaving = 0;
                for(i = 1; i <= model.saveLines; i++) {
                    strcpy(model.str[i], model.saveStr[i]);
                }
                model.totLine = model.saveLines;
                model.line = model.saveLine;
                model.cursorPos = model.saveCursorPos;
                refresh();
                return;
            }
            if(model.isCap == 0){
                int i;
				for(i = 1; i <= model.totLine; i++) {
                    printf("%s", model.str[i]);
                    puts("");
                }
                exit(0);
            } else {
                model.totLine++;
                int i;
				for(i = model.totLine; i >= model.line + 2; i--) {
                    strcpy(model.str[i], model.str[i-1]);
                }
                strcpy(model.str[model.line+1], model.str[model.line] + model.cursorPos - 1);
                model.str[model.line][model.cursorPos - 1] = 0;
                model.line++;
                model.cursorPos = 1;
            }
        } else if(key >= 0x30 && key <= 0x39) {
            if(!model.isCap) ch = key - 0x30 + '0';
            else ch = numberMapSymbol[key - 0x30];
            processChar(ch);
        } else if(key == 0x20) {
            ch = ' ';
            processChar(ch);
        } else if(key == 0x24) {
            model.cursorPos = 1;
        } else if(key == 0x23) {
            model.cursorPos = strlen(model.str[model.line])+1;
        } else if(key >= 0xBA && key <= 0xC0) {
            if(model.isCap == 0) ch = keyMap1[key - 0xBA];
            else ch = keyMapCap1[key - 0xBA];
            processChar(ch);
        } else if(key >= 0xDB && key <= 0xDE) {
            if(model.isCap == 0) ch = keyMap2[key - 0xDB];
            else ch = keyMapCap2[key - 0xDB];
            processChar(ch);
        } else if(key == VK_CONTROL) {
            model.isCtrl = 1;
        } else if(key == VK_TAB) {
            int i;
			for(i = 1; i <= 4; i++) processChar(' ');
        }
    } else if(event == KEY_UP) {
        if(key == 0xA0 || key == 0xA1 || key == 0x10) {
            model.isCap ^= 1;
//            printf("The shift is not pressed");
        } else if(key == VK_CONTROL) {
            model.isCtrl = 0;
        }
    }
    refresh();
}
void showWelcome() {
    beginPaint();
    setBrushColor(WHITE);
    rectangle(0, 0, model.width, model.height);
    setTextSize(40);
    setTextFont("Consolas");
    paintText(260, 200, "ACEIM - ACllib based Editor IMproved");
    paintText(20, 300, "Welcome! Before use, please switch your input mode to ENGLISH!");
    paintText(300, 400, "Press SPACE to enter the software");
    endPaint();
}
void showSaveScreen() {
    model.isSaving = 1;
    int i;
	for(i = 1; i <= model.totLine; i++) {
        strcpy(model.saveStr[i], model.str[i]);
    }
    model.saveLine = model.line;
    model.saveCursorPos = model.cursorPos;
    model.saveLines = model.totLine;
    model.totLine = 2;
    strcpy(model.str[1], "Save the file in:");
    model.str[2][0] = 0;
    model.line = 2;
    model.cursorPos = 1;
}
int Setup() {
    initModel();
    initWindow("ACEIM", 120, 20, model.width, model.height);
    initConsole();
    registerTimerEvent(timer);
    startTimer(0, 500);
    registerKeyboardEvent(keyListener);
    showWelcome();
}
