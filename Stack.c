//头文件部分
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//结构体声明部分
typedef struct {
	int *data;					//保存的数据
	int StackLength;			//栈的长度
	int StackSize;				//栈的大小
}Stack;
Stack S;

//全局变量定义


//状态常量定义
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define TRUE 1
#define FALSE 0	
#define BACK 0
#define STACK_INIT_SIZE 5
#define STACKINCREMENT 10

//函数定义部分
int InitStack(Stack *S);				//建栈
int Pop(Stack *S);				//弹出栈顶元素
	/*
		1.先弹队尾元素
		2.删除空间
		3.StackLength--
		4.position--
	*/
int Push(Stack *S, int i, int newdata);						//压入元素
	/*
		1.创建空间
		2.写入数据
		3.StackLength++
		4.position++
	*/
void Input();							//初始化以及输入一体函数
void Output();							//输出站内所有元素

//函数实现部分

/*InitStack开始*/
int InitStack(Stack *S) {
	//分配内存空间
	S->data = (int*)malloc(STACK_INIT_SIZE*sizeof(int));
	S->StackLength = (int*)malloc(STACK_INIT_SIZE*sizeof(int));
	S->StackSize = (int*)malloc(STACK_INIT_SIZE*sizeof(int));
	//出错处理
	if (!S->data)					//data出错
		exit(OVERFLOW);

	if (!S->StackLength)			//StackLength出错
		exit(OVERFLOW);
	if (!S->StackSize)				//StackSize出错
		exit(OVERFLOW);
	//初始化
	S->StackLength = 0;
	S->StackSize = STACK_INIT_SIZE;
	//结尾
	return OK;
}
/*InitStack结束*/

/*Pop开始*/
/*与顺序表一样，i必须指定为队伍最有一个元素*/
int Pop(Stack *S) {
	//声明部分
	int data = 0;					//存放data数据的临时变量
	int *p_data_1;					//删除data用的指针1
	int *p_data_2;					//删除data用的指针2
	int i = 0;						//弹出队尾元素的位置
	//给i赋值
	i = S->StackLength-1;
	//输出要被弹出的元素
	printf("被弹出的栈顶元素是：%d\n", S->data[i]);

	//删除data
	i++;
	p_data_1 = &(S->data[i - 1]);
	data = *p_data_1;
	p_data_2 = S->data + S->StackLength + 1;
	for (++p_data_1;p_data_1 <= p_data_2;++p_data_1) {
		*(p_data_1 - 1) = *p_data_1;
	}
	
	//总长-1
	--S->StackLength;

	//结束
	return OK;
}
/*Pop结束*/

/*Push开始*/
/*与顺序表一样，i必须指定为队伍最后一个元素*/
int Push(Stack *S, int newdata) {
	//声明部分
	int *newbase_1;					//给position增加空间
	int *p_data_1;					//插入data用的指针1
	int *p_data_2;					//插入data用的指针2
	int i = 0;						//插入位置

	//分配空间
	if (S->StackLength >= S->StackSize) {
		//给data增加空间
		newbase_1 = (int*)realloc(S->data, (S->StackSize + STACKINCREMENT)*sizeof(int));
		if (!newbase_1) {
			printf("无法为data增加空间。\n");
			return ERROR;
		}

		S->data = newbase_1;
	}
	//在表尾插入数据
	//指定插入位置在队尾
	i = S->StackLength+1;
	//压入data
	p_data_2 = &(S->data[i - 1]);
	for (p_data_1 = &(S->data[S->StackLength - 1]);p_data_1 >= p_data_2;--p_data_1) {
		*(p_data_1 + 1) = *p_data_1;
	}
	*p_data_2 = newdata;

	//增加StackLength
	++S->StackLength;

	//结尾
	return OK;
}
/*Push结束*/

/*Input开始*/
void Input() {
	if (InitStack(&S) != 1) {
		printf("程序出错\n");
	}
	else {
		int StackIntputCheck = 0;		//栈长度输入合法性判断标志
		int StackInputLength = 0;		//第一次输入长度
		int i = 0;						//循环计数变量

		//输入栈的初始长度，并作合法性判断
		do {
			printf("请输入栈的初始长度：\n");
			scanf_s("%d", &StackInputLength);
			if (StackInputLength <= 0) {
				printf("栈的初始长度必须为非负数\n");
				StackIntputCheck = 0;
			}
			else {
				printf("输入的初始长度为：%d\n", StackInputLength);
				StackIntputCheck = 1;
			}
		} while (StackIntputCheck != 1);
		//输入栈的各个元素
		printf("请输入栈的各个元素：\n");
		for (i = 0;i < StackInputLength;i++) {
			printf("请输入栈的第%d个元素：", i + 1);
			scanf_s("%d", &S.data[i]);	//输入data
		}
		S.StackLength = i;
	}

	//输出栈内各个元素
	Output();
	
	//结束
	return OK;
}
/*Input结束*/

/*Output开始*/
void Output() {
	int i = 0;					//循环计数变量
	printf("栈中所有元素为：\n");
	for (i = 0;i < S.StackLength;i++) {
		printf("栈中从上往下数第%d个元素是：%d\n", i + 1, S.data[S.StackLength - i - 1]);
	}
	return OK;
}
/*Output结束*/

/*主函数开始*/
int main() {
	int MainMenuChoice = 0;					//主菜单选择
	int MainMenuChoiceCheck = 0;			//主菜单选择判断
	int MainMenuRestart = 0;				//主菜单循环

	do {
		//主菜单
		printf("栈的基本操作演示程序：\n");
		printf("1->创建栈\n");
		printf("2->压入元素\n");
		printf("3->弹出栈顶元素\n");
		printf("0->退出程序\n");

		//输入选择及其判断
		printf("请输入选择：\n");
		do {
			scanf_s("%d", &MainMenuChoice);
			if (MainMenuChoice != 0 && MainMenuChoice != 1 && MainMenuChoice != 2 && MainMenuChoice != 3) {
				printf("输入了错误的选项，请重新输入\n");
				MainMenuChoiceCheck = 0;
			}
			else {
				printf("输入的选项为：%d\n", MainMenuChoice);
				MainMenuChoiceCheck = 1;
			}
		} while (MainMenuChoiceCheck != 1);

		//开关语句
		switch (MainMenuChoice) {
		case 1: {
			Input();
			MainMenuRestart = 1;
			break;
		}
		case 2: {
			int newdata = 0;					//需要压入栈顶的元素
			//压栈操作
			printf("请输入需要压入栈顶的元素：\n");
			scanf_s("%d", &newdata);
			Push(&S, newdata);
			Output();
			MainMenuRestart = 1;
			break;
		}
		case 3: {
			Pop(&S);
			Output();
			MainMenuRestart = 1;
			break;
		}
		case 0: {
			MainMenuRestart = 0;
			break;
		}
		}
	} while (MainMenuRestart != 0);
	return 0;
}
/*主函数结束*/