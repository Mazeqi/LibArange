//这里是BTree.h文件
#pragma once //这个代表只定义一次
#ifndef BTree_H_INCLUDED //用于定义头文件
#define BTree_H_INCLUDED
#define _CRT_SECURE_NO_WARNINGS
#define m 3
typedef int KeyType;


typedef enum Status {
	ERROR = 0, SUCCESS = 1
} Status;


typedef struct BTNode{
	int keynum;                  //结点当前的关键字个数
	KeyType key[m + 1];          //关键字数组，key[0]未用
	struct BTNode *parent;       //双亲结点指针
	struct BTNode *ptr[m + 1];   //孩子结点指针数组
	//Record *recptr[m + 1];     //记录指针向量，0号单元未用
}BTNode, *BTree;


typedef struct {
	BTree pt; //指向找到的节点
	int i;	  //1<=i<=m在节点中关键字的字序
	int tag;  //1:查找成功 0：查找失败
}result;

//查
/*
Time:2019/11/26 19:50
函数作用：在B树中查找关键字为k的结点
包含的函数：SearchBTree,SearchKey,其中SearchKey用了二分查找
*/
Status SearchBTree(BTree t, KeyType k, result &re);//寻找B树中关键字为k的节点
int searchKey(BTree node, KeyType k);//这里用的是二分查找

//增
/*
Time : 2019/11/28

函数：
1.InsertBTree(BTree &root,KeyType k):在B树中插入一个关键字k
2.InsertNode(BTree &root,int KeySite ,KeyType k, BTree &node):在B树某一层插入一个关键字，root是层，KeySite
是位置，K是关键字，node是root对应的孩子
3.SpiltToTwo(BTree &root, BTree &SpiltRight):分割结点,一半留在root，一半留在node，mid结点不放入。
4 NewBroot(BTree &root,BTree left, BTree right,KeyType k):生成一个新根

插入一个结点的流程：
1.判断根是否存在，不存在则生成新根
2.判断关键字是否存在，存在则返回ERROR
3.找到要插入的层，由于关键字中多留了一个m位置，虽然其最大的容量是m-1，所以当m位置也插入时，就进行分裂
4.分裂后进行根的处理，首先把mid位置的key插入到根中，接着判断根是否需要进行分裂，需要则进行循环，一直到不需要为止
*/
Status InsertBTree(BTree &root, KeyType k);//在B树中插入一个结点
Status SpiltToTwo(BTree &root, BTree &SpiltRight);//分割结点
Status NewBroot(BTree &root, BTree left, BTree right, KeyType k);//生成新的根
Status InsertNode(BTree &root, int KeySite, KeyType k, BTree &node);//在B树某一层插入一个关键字

//删
/*
Time:2019/11/30

删除步骤：
1.先查找是否存在该元素，如果存在，则将该元素在节点中删除，删除元素时，还得判断该元素是否有左右孩子
2.如果有左右孩子，则上移孩子节点中的某相近元素（"左孩子最右边的结点" 或者"右孩子最左边的结点"）
3.如果没有左右孩子结点，直接删除，然后移动。
4.删除元素，移动相应元素之后，如果某结点中元素数目（即关键字数）小于ceil（m/2）-1.则需要看其某个相
邻结点是否丰满（结点中元素个数大于ceil（m/2）-1）
5.如果丰满，则向父节点借一个元素来满足条件
6.如果其相邻兄弟节点都刚刚脱贫，即借了之后其节点数目小于ceil（m/2）-1，则该节点与其相邻的某一结点进
行合并成一个结点，以此来满足条件。
*/
Status  DeleteBTree(BTree &root, KeyType k);//删除一个关键字k
Status DeleteNode(BTree &node, int KeySite);
Status Restore(BTree &node);
Status Merge(BTree &Left, BTree &Right, BTree &Parent);

//打印

//凹入表打印B树
void Aoprint(BTree T, int depth);

//销毁B树
void Destroy(BTree &T);

//求深度
int Depth(BTree T);

//求叶子数
int Leaves(BTree T);

//升序遍历
void AscOrderTraverse(BTree T);

//降序遍历
void DesOrderTraverse(BTree T);
#endif // BTree_H_INCLUDED
