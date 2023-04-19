/*Pointer

Syntax:

data_type *pointer_name;


*/
#include<stdio.h>

void swap(int *num1,int *num2){
	int temp=*num1;
	*num1=*num2;
	*num2=temp;
}

void main(){
	int a=5,b=10;
	swap(&a,&b);
	printf("a=%d\tb=%d",a,b);
	return;
}
