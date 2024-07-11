#include <stdio.h>
void bubble (int a[ ], int n);
int main(void)
{    
  int n, a[10];
	int i;
	scanf("%d", &n);
	for (i=0; i<n;i++)
		scanf("%d",&a[i]);
	bubble(a,n);
	for (i=0; i<n; i++)
		printf("%d ",a[i]);
  printf("\n");
	return 0;
}

void bubble(int a[],int n){
	for(int i=n-1;i>0;i--){
		for(int j=0;j<i;j++){
			if (a[j]>a[j+1]){
				int t=a[j];
				a[j]=a[j+1];
				a[j+1]=t;
			}
        }
    }
} 
