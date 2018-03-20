#include <stdio.h>
#include <string.h>
char str[1000];
#define ADD 0//定义下标
#define SUB 1
#define  MUL 2
#define DIV 3
#define NUM 4
#define LEFT 5
#define RIGHT 6
#define POW 7
#define EQU 8
#define VAR 9
//定义跟随矩阵，1表允许，0表不允许
int matrix[10][10]={
0,0,0,0,1,0,1,0,0,1,
1,0,0,0,1,0,1,0,1,1,
0,0,0,0,1,0,1,0,0,1,

//3
0,0,0,0,1,0,1,0,0,1,
1,1,1,1,1,1,0,1,1,0,
1,1,1,1,0,1,0,0,1,0,

//6
0,0,0,0,1,0,1,0,0,1,
0,0,0,0,0,0,0,0,0,1,
0,0,0,0,1,0,1,0,0,1,

//9
1,1,1,1,0,1,0,0,1,0
};
int indexs(char a){//返回字符在跟随矩阵中的下标
	switch(a){
	case '+':
		return 0;
	case '-':
		return 1;
	case '*':
		return 2;
	case '/':
		return 3;
	case '.':
		return 4;
	case  '(':
		return 5;
	case ')':
		return 6;
	case '^':
		return 7;
	case '=':
		return 8;
	case 'x':
		return 9;
	}
	return 4;
}

int main(){
	int i;
	scanf("%s",str);
	int len=strlen(str);
	int eqFlag=0;
	for(i=0;i<len;i++){//判断等号
		if(str[i]=='='){
			eqFlag=1;
			break;
		}
	}
	if(!eqFlag){
		puts("No");
		return 0;
	}
	//判断跟随矩阵
	for( i=0;i<len-1;i++){
		int a=indexs(str[i]);
		int b=indexs(str[i+1]);
		if(matrix[a][b])
			continue;
		else{
			puts("No");
			return 0;
		}
				
		}
		puts("Yes");
	return 0;
}