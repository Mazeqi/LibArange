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
//	printf("������Ҫ�����������: ");
//	fflush(stdin);
//	scanf("%d", &num);
//	for (int i = 0; i<num; i++){
//		fflush(stdin);
//		printf("�����%d����: ", i + 1);
//		scanf("%d", &k);
//		InsertBTree(T, k);
//	}
//	printf("�������.\n");
//}
//
//void DeteleTest(BTree &T){
//	int k, num;
//	printf("������Ҫɾ����������: ");
//	fflush(stdin);
//	scanf("%d", &num);
//	Aoprint(T, 0);
//	for (int i = 0; i<num && T != NULL; i++){
//		fflush(stdin);
//		printf("�����%d����: ", i + 1);
//		scanf("%d", &k);
//		if (DeleteBTree(T, k) == SUCCESS){
//			printf("ɾ���ɹ�.\n");
//			Aoprint(T, 0);
//		}
//		else
//			printf("�����ڸ���, ɾ��ʧ��\n");
//	}
//	if (T == NULL)   printf("����Ϊ��.  ");
//	printf("ɾ������.\n");
//}
//
//void Traverse(BTree T){
//	printf("\n");
//	printf("���������� : ");
//	AscOrderTraverse(T);
//	printf("\n\n���������� : ");
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
//		printf("\t    1. �������������\n");
//		printf("\t    2. ����\n");
//		printf("\t    3. ɾ��\n");
//		printf("\t    4. ����\n");
//		printf("\t    5. ������ӡ\n");
//		printf("\t    6. ���\n");
//		printf("\t    7. Ҷ����\n");
//		printf("\t    8. ����\n");
//		printf("\t    0. �˳�����\n");
//		printf("\t-----------------------------\n");
//		printf("\t���������ѡ��: ");
//
//		int choose;
//		fflush(stdin);
//		scanf("%d", &choose);
//		switch (choose){
//		case 1:  randInsert(T); break;
//		case 2:  InsertTest(T); break;
//		case 3:  DeteleTest(T); break;
//		case 4:  Destroy(T); printf("���ٽ���. \n"); break;
//		case 5:  printf("\n"); Aoprint(T, 0); break;
//		case 6:  printf("���Ϊ: %d\n", Depth(T)); break;
//		case 7:  printf("Ҷ����Ϊ: %d\n", Leaves(T)); break;
//		case 8:  Traverse(T); break;
//		case 0:  exit(0); break;
//		default:
//			printf("�������! \n");
//		}
//		printf("�������� ,����������ز˵�. ");
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
