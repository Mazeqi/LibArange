#pragma once //这个代表只定义一次
#ifndef LIB_H_INCLUDED //用于定义头文件
#define LIB_H_INCLUDED
#include"./BTreeHead.h"


typedef struct Brrower{
	int BrrowerId;
	int ReturnTime;
	int tag;//用来标记是否注销，0为注销 1为未注销
}Brrower;

typedef struct LibBook{
	int BookId;//书号
	char BookName[50];//书名
	char BookAuthor[50]; //作者
	int NowSum;//现存量
	int AllSum;//总库存量
	int BorrowSum;//借阅量
	Brrower Member[50];//借阅该书的人员信息
	struct LibBook *next;
}LibNode,*LibList;



Status InsertStorage(BTree &T, LibList &L); //采编入库
void InsertList(LibList &L, LibList Node);


Status ClearStorage(BTree &T, LibList &L); //清除某种书的库存
Status DeleteList(LibList &L, KeyType k);

Status BorrowBook(BTree &T, LibList &L); //借阅,登记借阅者的图书证号和归还日期
Status ReturnBook(BTree &T, LibList &L); //归还图书，注销对借阅者的登记，改变书的现存量

void SearchBook(BTree T, LibList L);

//输出所有书的信息
void printAllBook(LibList L, BTree T);

#endif // LIB_H_INCLUDED
