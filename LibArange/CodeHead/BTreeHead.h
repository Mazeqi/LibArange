//������BTree.h�ļ�
#pragma once //�������ֻ����һ��
#ifndef BTree_H_INCLUDED //���ڶ���ͷ�ļ�
#define BTree_H_INCLUDED
#define _CRT_SECURE_NO_WARNINGS
#define m 3
typedef int KeyType;


typedef enum Status {
	ERROR = 0, SUCCESS = 1
} Status;


typedef struct BTNode{
	int keynum;                  //��㵱ǰ�Ĺؼ��ָ���
	KeyType key[m + 1];          //�ؼ������飬key[0]δ��
	struct BTNode *parent;       //˫�׽��ָ��
	struct BTNode *ptr[m + 1];   //���ӽ��ָ������
	//Record *recptr[m + 1];     //��¼ָ��������0�ŵ�Ԫδ��
}BTNode, *BTree;


typedef struct {
	BTree pt; //ָ���ҵ��Ľڵ�
	int i;	  //1<=i<=m�ڽڵ��йؼ��ֵ�����
	int tag;  //1:���ҳɹ� 0������ʧ��
}result;

//��
/*
Time:2019/11/26 19:50
�������ã���B���в��ҹؼ���Ϊk�Ľ��
�����ĺ�����SearchBTree,SearchKey,����SearchKey���˶��ֲ���
*/
Status SearchBTree(BTree t, KeyType k, result &re);//Ѱ��B���йؼ���Ϊk�Ľڵ�
int searchKey(BTree node, KeyType k);//�����õ��Ƕ��ֲ���

//��
/*
Time : 2019/11/28

������
1.InsertBTree(BTree &root,KeyType k):��B���в���һ���ؼ���k
2.InsertNode(BTree &root,int KeySite ,KeyType k, BTree &node):��B��ĳһ�����һ���ؼ��֣�root�ǲ㣬KeySite
��λ�ã�K�ǹؼ��֣�node��root��Ӧ�ĺ���
3.SpiltToTwo(BTree &root, BTree &SpiltRight):�ָ���,һ������root��һ������node��mid��㲻���롣
4 NewBroot(BTree &root,BTree left, BTree right,KeyType k):����һ���¸�

����һ���������̣�
1.�жϸ��Ƿ���ڣ��������������¸�
2.�жϹؼ����Ƿ���ڣ������򷵻�ERROR
3.�ҵ�Ҫ����Ĳ㣬���ڹؼ����ж�����һ��mλ�ã���Ȼ������������m-1�����Ե�mλ��Ҳ����ʱ���ͽ��з���
4.���Ѻ���и��Ĵ������Ȱ�midλ�õ�key���뵽���У������жϸ��Ƿ���Ҫ���з��ѣ���Ҫ�����ѭ����һֱ������ҪΪֹ
*/
Status InsertBTree(BTree &root, KeyType k);//��B���в���һ�����
Status SpiltToTwo(BTree &root, BTree &SpiltRight);//�ָ���
Status NewBroot(BTree &root, BTree left, BTree right, KeyType k);//�����µĸ�
Status InsertNode(BTree &root, int KeySite, KeyType k, BTree &node);//��B��ĳһ�����һ���ؼ���

//ɾ
/*
Time:2019/11/30

ɾ�����裺
1.�Ȳ����Ƿ���ڸ�Ԫ�أ�������ڣ��򽫸�Ԫ���ڽڵ���ɾ����ɾ��Ԫ��ʱ�������жϸ�Ԫ���Ƿ������Һ���
2.��������Һ��ӣ������ƺ��ӽڵ��е�ĳ���Ԫ�أ�"�������ұߵĽ��" ����"�Һ�������ߵĽ��"��
3.���û�����Һ��ӽ�㣬ֱ��ɾ����Ȼ���ƶ���
4.ɾ��Ԫ�أ��ƶ���ӦԪ��֮�����ĳ�����Ԫ����Ŀ�����ؼ�������С��ceil��m/2��-1.����Ҫ����ĳ����
�ڽ���Ƿ�����������Ԫ�ظ�������ceil��m/2��-1��
5.������������򸸽ڵ��һ��Ԫ������������
6.����������ֵܽڵ㶼�ո���ƶ��������֮����ڵ���ĿС��ceil��m/2��-1����ýڵ��������ڵ�ĳһ����
�кϲ���һ����㣬�Դ�������������
*/
Status  DeleteBTree(BTree &root, KeyType k);//ɾ��һ���ؼ���k
Status DeleteNode(BTree &node, int KeySite);
Status Restore(BTree &node);
Status Merge(BTree &Left, BTree &Right, BTree &Parent);

//��ӡ

//������ӡB��
void Aoprint(BTree T, int depth);

//����B��
void Destroy(BTree &T);

//�����
int Depth(BTree T);

//��Ҷ����
int Leaves(BTree T);

//�������
void AscOrderTraverse(BTree T);

//�������
void DesOrderTraverse(BTree T);
#endif // BTree_H_INCLUDED
