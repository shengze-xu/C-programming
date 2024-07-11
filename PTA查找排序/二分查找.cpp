#include <stdio.h>

int main(){	
	int n,x,i,a[10]={0};
	scanf("%d %d",&n,&x);
	for(i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	for(i=1;i<n;i++){
		if(a[i]<=a[i-1]){
			printf("Invalid Value\n");
			break;
		}
	}
	if(i>=n){
		int left=0,right=n-1,middle;
		middle=(left+right)/2;
		printf("[%d,%d][%d]\n",left,right,middle);
		while(left<right){
			if(a[middle]==x){
				break;
			}
			else if(x<a[middle]){
				right=middle-1;
			} 
			else{
				left=middle+1;
			}
			middle=(left+right)/2;
			printf("[%d,%d][%d]\n",left,right,middle);
		}
		if(a[middle]!=x){
			printf("Not Found\n");
		}
		else{
			printf("%d",middle);
		}
	}
	
	return 0;
}
