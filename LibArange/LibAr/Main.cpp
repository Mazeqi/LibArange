#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>
#include"../CodeHead/BTreeHead.h"
#include"../CodeHead/LibLink.h"
#include<string.h>

void Traverse(BTree T){
	printf("\n");
	printf("升序遍历结果 : ");
	AscOrderTraverse(T);
	printf("\n\n降序遍历结果 : ");
	DesOrderTraverse(T);
	printf("\n");
}
void DeteleTest(BTree &T){
	int k, num;
	printf("输入需要删除的数据量: ");
	fflush(stdin);
	scanf("%d", &num);
	Aoprint(T, 0);
	for (int i = 0; i<num && T != NULL; i++){
		fflush(stdin);
		printf("输入第%d个数: ", i + 1);
		scanf("%d", &k);
		if (DeleteBTree(T, k) == SUCCESS){
			printf("删除成功.\n");
			Aoprint(T, 0);
		}
		else
			printf("不存在该数, 删除失败\n");
	}
	if (T == NULL)   printf("树已为空.  ");
	printf("删除结束.\n");
}
void menu(){
	BTree T = NULL;
	LibList L = NULL;
	LibList Node = NULL;
	int test[18] = { 35, 16, 18, 70, 5, 50, 22, 60, 13, 17, 12, 45, 25, 42, 15, 90, 30, 7 };
	char BookName[18][10] = {"A\0","B\0","C\0","D\0","E\0","F\0","G\0","H\0","I\0","J\0","K\0","L\0","M\0","N\0","O\0","P\0","Q\0","R\0"};
	char AuthorName[18][10] = { "a\0", "b\0", "c\0", "d\0", "e\0", "f\0", "g\0", "h\0", "i\0", "j\0", "k\0", "l\0", "m\0", "n\0", "o\0", "p\0", "q\0", "r\0" };
	for (int i = 0; i < 18; i++){
		InsertBTree(T, test[i]);
	}
	for (int i = 0; i < 18; i++){

		Node = (LibList)malloc(sizeof(LibNode));
		Node->BookId = test[i];
		Node->next = NULL;
		strncpy(Node->BookName, BookName[i], strlen(BookName[i]) + 1);
		strncpy(Node->BookAuthor, AuthorName[i], strlen(AuthorName[i]) + 1);
		Node->AllSum = 5;
		Node->NowSum = 3;
		Node->BorrowSum = 2;

		for (int i = 0; i < 50; i++){
			Node->Member[i].tag = 0;
		}
		for (int i = 0; i < 2; i++){
			Node->Member[i].BrrowerId = i;
			Node->Member[i].ReturnTime = 20190101;
			Node->Member[i].tag = 1;
		}
		InsertList(L, Node);
		Node = NULL;
	}

	while (1){
		printf("\n\n\t-----------------------------\n");
		printf("\t    1. 采编入库\n");
		printf("\t    2. 清除库存\n");
		printf("\t    3. 借阅\n");
		printf("\t    4. 归还\n");
		printf("\t    5. 查询某书\n");
		printf("\t    6.查询所有书\n");
		printf("\t-----------------------------\n\n");

		printf("\t    7. 凹入表打印\n");
		printf("\t    8. 深度\n");
		printf("\t    9. 叶子数\n");
		printf("\t    10. 遍历\n");
		printf("\t    11. 在B树中删除结点\n");
		printf("\t    0. 退出程序\n");
		printf("\t-----------------------------\n");
		printf("\t请输入你的选择: ");

		int choose;
		fflush(stdin);
		scanf("%d", &choose);
		switch (choose){
		case 1:  InsertStorage(T, L); break;
		case 2:  ClearStorage(T, L); break;
		case 3:  BorrowBook(T, L); break;
		case 4:  ReturnBook(T, L); break;
		case 5:  SearchBook(T, L); break;
		case 6: printAllBook(L,T); break;
		case 7:  printf("\n"); Aoprint(T, 0); break;
		case 8:  printf("深度为: %d\n", Depth(T)); break;
		case 9:  printf("叶子数为: %d\n", Leaves(T)); break;
		case 10:  Traverse(T); break;
		case 11: DeteleTest(T); break;
		
		case 0:  exit(0); break;
		default:
			printf("输入错误! \n");
		}
		printf("操作结束 ,按任意键返回菜单. ");
		_getch();
		system("cls");
	}
}

int main(){
	menu();
	return 0;
}
