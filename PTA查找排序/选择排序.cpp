#include <stdio.h>

int main(){
	int n,i,a[10]={0};
	scanf("%d",&n);
	for(i=0;i<n;i++){
		scanf("%d",&a[i]);
	} 
	if(n==1) printf("%d",a[0]);
	int cnt=0,p,j,k;
	for(i=0;i<n-1;i++){
		for(j=i;j<n;j++){
			if(a[cnt]>a[j]){
				cnt=j;
			}
		}
		p=a[i];
		a[i]=a[cnt];
		a[cnt]=p;
		for(k=0;k<n;k++){
			if(k==0) printf("%d",a[k]);
			else printf(" %d",a[k]);
		}
		printf("\n");
		cnt=i+1;
	}
	return 0;
} 
