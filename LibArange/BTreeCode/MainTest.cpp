//#include"../CodeHead/BTreeHead.h"
//#define _CRT_SECURE_NO_WARNINGS
//#include<stdio.h>
//#include<stdlib.h>
//#include<time.h>
//#include<conio.h>
//void randInsert(BTree &T){
//	int k;
//	srand((unsigned int)(time(NULL)));
//	for (int i = 0; i < 25; i++){
//		k = rand() % 50000 + 1;
//		InsertBTree(T, k);
//	}
//}
//
//void InsertTest(BTree &T){
//	int k, num;
//	printf("输入需要插入的数据量: ");
//	fflush(stdin);
//	scanf("%d", &num);
//	for (int i = 0; i<num; i++){
//		fflush(stdin);
//		printf("输入第%d个数: ", i + 1);
//		scanf("%d", &k);
//		InsertBTree(T, k);
//	}
//	printf("插入结束.\n");
//}
//
//void DeteleTest(BTree &T){
//	int k, num;
//	printf("输入需要删除的数据量: ");
//	fflush(stdin);
//	scanf("%d", &num);
//	Aoprint(T, 0);
//	for (int i = 0; i<num && T != NULL; i++){
//		fflush(stdin);
//		printf("输入第%d个数: ", i + 1);
//		scanf("%d", &k);
//		if (DeleteBTree(T, k) == SUCCESS){
//			printf("删除成功.\n");
//			Aoprint(T, 0);
//		}
//		else
//			printf("不存在该数, 删除失败\n");
//	}
//	if (T == NULL)   printf("树已为空.  ");
//	printf("删除结束.\n");
//}
//
//void Traverse(BTree T){
//	printf("\n");
//	printf("升序遍历结果 : ");
//	AscOrderTraverse(T);
//	printf("\n\n降序遍历结果 : ");
//	DesOrderTraverse(T);
//	printf("\n");
//}
//
//void menu(){
//	BTree T = NULL;
//	int test[18] = { 35, 16, 18, 70, 5, 50, 22, 60, 13, 17, 12, 45, 25, 42, 15, 90, 30, 7 };
//	int test2[] = {20,30,50,52,60,68,70,72,71,100};
//	for (int i = 0; i < 10; i++){
//		InsertBTree(T, test2[i]);
//	}
//	while (1){
//		printf("\n\n\t-----------------------------\n");
//		printf("\t    1. 随机生成数插入\n");
//		printf("\t    2. 插入\n");
//		printf("\t    3. 删除\n");
//		printf("\t    4. 销毁\n");
//		printf("\t    5. 凹入表打印\n");
//		printf("\t    6. 深度\n");
//		printf("\t    7. 叶子数\n");
//		printf("\t    8. 遍历\n");
//		printf("\t    0. 退出程序\n");
//		printf("\t-----------------------------\n");
//		printf("\t请输入你的选择: ");
//
//		int choose;
//		fflush(stdin);
//		scanf("%d", &choose);
//		switch (choose){
//		case 1:  randInsert(T); break;
//		case 2:  InsertTest(T); break;
//		case 3:  DeteleTest(T); break;
//		case 4:  Destroy(T); printf("销毁结束. \n"); break;
//		case 5:  printf("\n"); Aoprint(T, 0); break;
//		case 6:  printf("深度为: %d\n", Depth(T)); break;
//		case 7:  printf("叶子数为: %d\n", Leaves(T)); break;
//		case 8:  Traverse(T); break;
//		case 0:  exit(0); break;
//		default:
//			printf("输入错误! \n");
//		}
//		printf("操作结束 ,按任意键返回菜单. ");
//		_getch();
//		system("cls");
//	}
//}
//
//int main(){
//	menu();
//	return 0;
//}
//
