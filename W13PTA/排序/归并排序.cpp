#include<stdio.h>
#include<stdlib.h>

typedef  int  KeyType;
typedef  struct {                      
    KeyType *elem; /*elem[0]һ�����ڱ��򻺳���*/                       
    int Length;      
}SqList;

void  CreatSqList(SqList *L);/*�������н������ɲ���ʵ�֣�ϸ�ڲ���*/ 
void  MergeSort(SqList L,int low,int high);
void Merge(SqList L,int low,int m,int high); 

int main()
{
  	SqList L;
	int i;
	CreatSqList(&L);
	MergeSort(L,1,L.Length);
	for(i=1;i<=L.Length;i++){		
	    printf("%d ",L.elem[i]);
	}
	return 0;
}
void MergeSort(SqList L,int low,int high)  
{     
    /*�÷��η����ж�·�鲢����*/  
    int mid;  
    if(low<high)  /*���䳤�ȴ���1*/
    {      
        mid=(low+high)/2;               /*�ֽ�*/
        MergeSort(L,low,mid);           /*�ݹ�ض�low��mid�������� */ 
        MergeSort(L,mid+1,high);        /*�ݹ�ض�mid+1��high�������� */ 
        Merge(L,low,mid,high);          /*�鲢*/  
    }  
}

void Merge(SqList L,int low,int m,int high){
	KeyType *p=(KeyType *)malloc((high-low+1)*sizeof(KeyType));
	int i=low,j=m+1,k=0;
	while(i<=m&&j<=high){
		if(L.elem[i]<L.elem[j]){
			p[k++]=L.elem[i++];
		}else{
			p[k++]=L.elem[j++];
		}
	}
	while(i<=m){
		p[k++]=L.elem[i++];
	}
	while(j<=high){
		p[k++]=L.elem[j++];
	}
	for(i=0;i<k;i++){
		L.elem[low+i]=p[i];
	}
}

