#include <stdio.h>
#include <iostream>
#include <math.h>
using namespace std;
int prime[1000];//存储1000以内的素数
int mark[1000];
int size=0;
int a_count[1000];//计算素数prime[i]在a^k中总的因子数
int n_count[1000];//计算素数prime[i]在n中总的因子数
int n_1_count[1000];//计算素数prime[i]在n-1中总的因子数
void findPrime(){//找到1000以内所有的素数，筛法
	int i;
	for( i=0;i<1000;i++){
		mark[i]=false;
	}
	for(i=2;i<999;i++){
		if(mark[i]==false){
			prime[size++]=i;
			for(int j=i*i;j<1000;j+=i)
				mark[j]=true;
		}
		else
			continue;
	}
}
void divi(int n,int a,int k){//对n和a^k因式分解
	int i;
	for(i=0;i<1000;i++)
		a_count[i]=n_count[i]=n_1_count[i]=0;

	for(int j=n;j>1;j-=2){//对n!!因式分解
		int temp=j;
		for(i=0;i<size;i++){
			while(temp%prime[i]==0){
				n_count[i]++;
				temp/=prime[i];
			}
		}
	}

	for( j=n-1;j>1;j-=2){
		int temp=j;
		for(i=0;i<size;i++){
			while(temp%prime[i]==0){
				n_1_count[i]++;
				temp/=prime[i];
			}
		}
	}
//a^k
	for(i=0;i<size;i++){
		while(a%prime[i]==0){
			a_count[i]++;
			a/=prime[i];
		}
		a_count[i]*=k;
	}

}
bool isDiviable(){//判断是否符合题设条件
	int i;
	for(i=0;i<size;i++){
		if(a_count[i] && a_count[i]>n_count[i])
			return false;
	}
	int flag=0;
	for(i=0;i<size;i++){
		if(a_count[i] && a_count[i]>n_1_count[i])
			return true;
	}
	return false;
}
int main(){
	int k,a,i;
	scanf("%d%d",&k,&a);
	findPrime();

	for( i=2;i<1000;i++){
		divi(i,a,k);
		if(isDiviable()){
			printf("%d",i);
			return 0;
		}
	}
	printf("-1");
	return 0;
}