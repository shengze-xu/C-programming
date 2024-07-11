#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int Judge(int a[],int b[],int n);
void NextInsertSort(int a[],int pos,int n);
void Merge(int a[],int low,int high,int mid);
int  GetLen(int a[],int n);
void NextMergeSort(int a[],int low,int high, int len);
void prt(int a[],int n);

int main(){
	int n,i;
	int a[105],b[105];
	scanf("%d",&n);
	for(i=0;i<n;i++){
		scanf("%d",&a[i]);
	}
	for(i=0;i<n;i++){
		scanf("%d",&b[i]);
	}
	int pos=Judge(a,b,n);
	if(pos){
		printf("Insertion Sort\n");
		NextInsertSort(b,pos,n);
	}else{
		printf("Merge Sort\n");
		int len=2*GetLen(b,n);
		NextMergeSort(b,0,n-1,len);
	}
	prt(b,n);
	return 0;
}

void prt(int a[],int n){
	for(int i=0;i<n;i++){
		if(i==0) printf("%d",a[i]);
		else printf(" %d",a[i]);
	}
}

int Judge(int a[],int b[],int n){
	int pos=0,flag=0,i=0;
	for(i=0;i<n;i++){
		if(b[i]>=b[i-1]) flag=1;
		else{pos=i;break;}
	}
	if(flag){
		for(i=pos;i<n;i++){
			if(a[i]!=b[i]){pos=0;break;}
		}
	}else pos=0;
	return pos;
}

void NextInsertSort(int a[],int pos,int n){
	int i,tmp=a[pos];
    int index;
    for(i=0;i<pos; i++) {
        if(a[i]>tmp) {
            index=i;
            break;
        }
    }
    for(i=pos-1;i>=index;i--) {
        a[i+1]=a[i];
    }
    a[index]=tmp;
}

void Merge(int a[],int low,int high,int mid) {
    int *p=(int *)malloc((high-low+1)*sizeof(int));
	int i=low,j=mid+1,k=0;
	while(i<=mid&&j<=high){
		if(a[i]<a[j]){
			p[k++]=a[i++];
		}else{
			p[k++]=a[j++];
		}
	}
	while(i<=mid){
		p[k++]=a[i++];
	}
	while(j<=high){
		p[k++]=a[j++];
	}
	for(i=0;i<k;i++){
		a[low+i]=p[i];
	}
}

int GetLen(int a[],int n) {
    int i,j;
    for(j=2; j<=n; j*=2){
        for(i=j; i<n; i=i+2*j)
        {
            if(a[i-1]>a[i])
                break;
        }    
        if(i<n)
            break;
    }
    return j;
}
void NextMergeSort(int a[],int low,int high,int len) {
    int i;
    for(i=low; i<=high; i+=len) {
        int mid=(i+i+len-1)/2;
        if(i+len-1<=high) {
            Merge(a,i,i+len-1,mid);
        }
        else if(mid<high) {
            Merge(a,i,high,mid);
        }
    }
}
