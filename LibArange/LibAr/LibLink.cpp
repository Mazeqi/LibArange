#include"../CodeHead/LibLink.h"
#include"../CodeHead/BTreeHead.h"
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include<string.h>
Status InsertStorage(BTree &T, LibList &L){

	int BookId;
	char BookName[50];
	char BookAuthor[50];
	int NowSum = 0;
	int AllSum = 0;
	int BorrowSum = 0;//借阅人数
	KeyType k;
	result re;

	do{
		printf("\t输入书号：");
		fflush(stdin);
		scanf("%d", &BookId);
	} while (getchar() != '\n');
	k = BookId;

	printf("\t输入书名：");
	fflush(stdin);
	scanf("%s", BookName);

	printf("\t输入书的作者：");
	fflush(stdin);
	scanf("%s", BookAuthor);

	do{
		printf("\t输入书的入库量：");
		fflush(stdin);
		scanf("%d", &AllSum);
		NowSum = AllSum;
	} while (getchar() != '\n');

	//存在该书
	if (SearchBTree(T, k, re) == SUCCESS){
		for (LibList Node = L; Node != NULL; Node = Node->next){
			if (Node->BookId == k){
				Node->AllSum += AllSum;
				Node->NowSum += AllSum;
				break;
			}
		}
	}
	else{
		//不存在该书
		//插入到内存
		LibList Node = NULL;
		Node = (LibList)malloc(sizeof(LibNode));
		if (Node == NULL)return ERROR;

		Node->next = NULL;
		Node->BookId = BookId;
		strncpy(Node->BookName, BookName, strlen(BookName)+1);
		strncpy(Node->BookAuthor, BookAuthor, strlen(BookAuthor)+1);
		Node->AllSum = Node->NowSum = AllSum;
		Node->BorrowSum = 0;

		for (int i = 0; i < 50; i++){
			Node->Member[i].tag = 0;
		}
		InsertList(L, Node);
		InsertBTree(T, BookId);
	}
	
	return SUCCESS;
}

//插入一个结点,使用头插入
void InsertList(LibList &L, LibList Node){
	if (L == NULL){
		L = Node;
	}
	else{
		Node->next = L;
		L = Node;
	}
}

//清除某种书的库存
Status ClearStorage(BTree &T, LibList &L){
	if (T == NULL || L == NULL)return ERROR;
	result re;
	KeyType k;
	int BookId;

	do{
		printf("\t请输入要删除的书号：");
		fflush(stdin);
		scanf("%d", &BookId);
	} while (getchar() != '\n');

	k = BookId;

	if (SearchBTree(T, k, re) == ERROR){
		printf("\t不存在该书\n");
		return ERROR;
	}
	else{
		DeleteBTree(T, k);
		DeleteList(L, k);
	}
}
Status DeleteList(LibList &L, KeyType k){
	if (L == NULL)return ERROR;

	LibList DelNode = L;
	LibList p = L;

	for (; DelNode != NULL; p = DelNode, DelNode = DelNode->next){
		if (DelNode->BookId == k){
			if (p == DelNode){
				DelNode = DelNode->next;
				free(p);
				p = NULL;
				L = DelNode;
				return SUCCESS;
			}
			else{
				p->next = DelNode->next;
				free(DelNode);
				DelNode = NULL;
				return SUCCESS;
			}
		}
	}
	
}

//借阅
Status BorrowBook(BTree &T, LibList &L){
	if (T == NULL || L == NULL)return ERROR;
	int BookId;
	int MemId;
	int ReturnTime;
	KeyType k;
	result re;
	do{
		printf("\t输入要借阅的书号：");
		fflush(stdin);
		scanf("%d", &BookId);
	} while (getchar() != '\n');

	k = BookId;

	if (SearchBTree(T, k, re) == ERROR){
		printf("\t不存在该书\n");
		return ERROR;
	}

	do{
		printf("\t输入借阅者的图书证号：");
		fflush(stdin);
		scanf("%d", &MemId);
	} while (getchar() != '\n');
	
	do{
		printf("\t输入归还的日期：  ");
		fflush(stdin);
		scanf("%d", &ReturnTime);
	} while (getchar() != '\n');

	for (LibList Node = L; Node != NULL; Node = Node->next){
		if (Node->BookId == BookId){
			for (int i = 0; i < Node->AllSum; i++){
				if (Node->Member[i].tag == 0){
					Node->Member[i].BrrowerId = MemId;
					Node->Member[i].ReturnTime = ReturnTime;
					Node->Member[i].tag = 1;
					Node->NowSum--;
					Node->BorrowSum++;
					break;
				}
			}
			break;
		}
	}
	return SUCCESS;

}

Status ReturnBook(BTree &T, LibList &L){
	if (T == NULL || L == NULL)return ERROR;
	int BookId;
	int MemId;
	do{
		printf("\t输入借阅的书号：");
		fflush(stdin);
		scanf("%d", &BookId);
	} while (getchar() != '\n');

	do{
		printf("\t输入借阅者的图书证号：");
		fflush(stdin);
		scanf("%d", &MemId);
	} while (getchar() != '\n');

	for (LibList Node = L; Node != NULL; Node = Node->next){
		if (Node->BookId == BookId){
			for (int i = 0; i < Node->AllSum; i++){
				if (MemId == Node->Member[i].BrrowerId){
					Node->Member[i].tag = 0;
					Node->BorrowSum--;
					Node->NowSum++;
					break;
				}
			}
			break;
		}
	}
	return SUCCESS;
}
void printAllBook(LibList L,BTree T){
	if (L == NULL)return;
	result re;
	for (LibList Node = L; Node != NULL; Node = Node->next){
		if (SearchBTree(T, Node->BookId, re) == SUCCESS){
			printf("\t书名：%s\n", Node->BookName);
			printf("\t作者：%s\n", Node->BookAuthor);
			printf("\t现存量：%d\n", Node->NowSum);
			printf("\t总库存量：%d\n", Node->AllSum);
			printf("\t借阅量：%d\n", Node->BorrowSum);
			int sum = Node->BorrowSum;
			if (Node->BorrowSum > 0){
				printf("\t--------------------------------\n");
				printf("\t借阅者信息：\n");
				printf("\t\t图书证号：");

				for (int i = 0; i < Node->AllSum && sum > 0; i++){
					if (Node->Member[i].tag == 1){
						printf("  %-8d", Node->Member[i].BrrowerId);
						sum--;
					}

				}
				printf("\n");
				printf("\t\t归还日期：");
				sum = Node->BorrowSum;
				for (int i = 0; i < Node->AllSum && sum > 0; i++){
					if (Node->Member[i].tag == 1){
						printf("  %d", Node->Member[i].ReturnTime);
						sum--;
					}

				}
				printf("\n");
				printf("\t--------------------------------\n");
			}
			else{
				printf("\t该书当前无人借阅\n");
			}
			printf("\n\n");
		}
	}
}

void SearchBook(BTree T, LibList L){
	if (T == NULL || L == NULL)return;
	int BookId;
	result re;
	do{
		printf("\t输入查询的书号：");
		fflush(stdin);
		scanf("%d", &BookId);
	} while (getchar() != '\n');

	if (SearchBTree(T, BookId, re) == ERROR){
		printf("\t 不存在该书\n");
		return;
	}
	else{
		for (LibList Node = L; Node != NULL; Node = Node->next){
			if (Node->BookId == BookId){
				printf("\t书名：%s\n",Node->BookName);
				printf("\t作者：%s\n", Node->BookAuthor);
				printf("\t现存量：%d\n", Node->NowSum);
				printf("\t总库存量：%d\n", Node->AllSum);
				printf("\t借阅量：%d\n", Node->BorrowSum);
				int sum = Node->BorrowSum;
				if (Node->BorrowSum > 0){
					printf("\t--------------------------------\n");
					printf("\t借阅者信息：\n");
					printf("\t\t图书证号：");

					for (int i = 0; i < Node->AllSum && sum > 0; i++){
						if (Node->Member[i].tag == 1){
							printf("  %-8d", Node->Member[i].BrrowerId);
							sum--;
						}

					}
					printf("\n");
					printf("\t\t归还日期：");
					sum = Node->BorrowSum;
					for (int i = 0; i < Node->AllSum && sum > 0; i++){
						if (Node->Member[i].tag == 1){
							printf("  %d", Node->Member[i].ReturnTime);
							sum--;
						}

					}
					printf("\n");
					printf("\t--------------------------------\n");
				}
				else{
					printf("\t该书当前无人借阅\n");
				}
				break;
			}
		}
	}
}

