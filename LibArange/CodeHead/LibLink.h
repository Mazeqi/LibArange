#pragma once //�������ֻ����һ��
#ifndef LIB_H_INCLUDED //���ڶ���ͷ�ļ�
#define LIB_H_INCLUDED
#include"./BTreeHead.h"


typedef struct Brrower{
	int BrrowerId;
	int ReturnTime;
	int tag;//��������Ƿ�ע����0Ϊע�� 1Ϊδע��
}Brrower;

typedef struct LibBook{
	int BookId;//���
	char BookName[50];//����
	char BookAuthor[50]; //����
	int NowSum;//�ִ���
	int AllSum;//�ܿ����
	int BorrowSum;//������
	Brrower Member[50];//���ĸ������Ա��Ϣ
	struct LibBook *next;
}LibNode,*LibList;



Status InsertStorage(BTree &T, LibList &L); //�ɱ����
void InsertList(LibList &L, LibList Node);


Status ClearStorage(BTree &T, LibList &L); //���ĳ����Ŀ��
Status DeleteList(LibList &L, KeyType k);

Status BorrowBook(BTree &T, LibList &L); //����,�Ǽǽ����ߵ�ͼ��֤�ź͹黹����
Status ReturnBook(BTree &T, LibList &L); //�黹ͼ�飬ע���Խ����ߵĵǼǣ��ı�����ִ���

void SearchBook(BTree T, LibList L);

//������������Ϣ
void printAllBook(LibList L, BTree T);

#endif // LIB_H_INCLUDED
