#include <stdio.h>

int main(){
	int n,a[10]={0};
	scanf("%d",&n);
	for(int i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	if(n==1) printf("%d",a[0]);
	for(int i=n-1;i>0;i--){
		for(int j=0;j<i;j++){
			if(a[j]>a[j+1]){
				int temp=a[j];
				a[j]=a[j+1];
				a[j+1]=temp;
			}
		}
		for(int m=0;m<n;m++){
			if(m==0){
				printf("%d",a[m]);
			}
		    else{
				printf(" %d",a[m]);
			}

		}
		printf("\n");
	}
	return 0;
} 
