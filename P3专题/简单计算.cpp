#include <stdio.h>
#include "string.h"

char op;

int addup();
int plus();
int brackets();

int main(){
	int sum=0;
	op=getchar();
	sum=addup();
	printf("%d",sum);
} 

int addup(){
	int sum=0;
	sum=plus();
	while(op=='+'||op=='-'){
		switch(op){
			case '+': op=getchar(); sum+=plus(); break;
			case '-': op=getchar(); sum-=plus(); break; 
		}	
	}
	return sum;	
} 

int plus(){
	int sum=0;
	sum=brackets();
	while(op=='*'||op=='/'||op=='%'){
		switch(op){
			case '*': op=getchar(); sum*=brackets(); break;
			case '/': op=getchar(); sum/=brackets(); break;
			case '%': op=getchar(); sum%=brackets(); break;
		}	
	}
	return sum;
}

int brackets(){
	int sum=0;
	if(op=='('){
		op=getchar();
		sum=addup();
		if(op==')') op=getchar();
	}
	else if((op>='0'&&op<='9')||op=='-'){
		if(op=='-'){
			op=getchar();
			while(op>='0'&&op<='9'){
				sum=sum*10+op-'0';
				op=getchar();
			}
			sum=-1*sum;
		}else{
			while(op>='0'&&op<='9'){
				sum=sum*10+op-'0';
				op=getchar();
			}
		}
	}
	return sum;
}
