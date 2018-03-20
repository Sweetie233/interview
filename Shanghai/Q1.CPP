#include <stdio.h>
int data[1000000];
bool mark[100000];
int count=1;
bool flag=false;
void process(int deep,long int sum){
	if(deep==(count-1)){
		for(int i=1;i<count;i++){
			if(mark[i]==false){
				if(sum+data[i]==1){
					flag=true;
					return;
				}
				if(sum-data[i]==1){
					flag=true;
					return;
				}
				else
					return;
			}
		}
	}
	else{
		for(int i=1;i<count;i++){
			if(mark[i]==true)
				continue;
			mark[i]=true;
			process(deep+1,sum+data[i]);
			process(deep+1,sum-data[i]);
			mark[i]=false;
		}
	}
}

int main(){
	int temp;
	while(scanf("%d",&temp)!=EOF){
		data[count++]=temp;
		char a=getchar();
		if(a==' '&&a!='\n')
			continue;
		else 
			break;
	}
	for(int i=0;i<=count;i++){
		mark[i]=false;
	}
	process(1,0);
	if(flag)
		puts("Yes");
	else
		puts("No");
	return 0;

}