#include"../CodeHead/BTreeHead.h"
#include<stdio.h>
#include<stdlib.h>
/*
Time:2019/11/26 19:50
函数作用：在B树中查找关键字为k的结点
包含的函数：SearchBTree,SearchKey,其中SearchKey用了二分查找
*/
Status SearchBTree(BTree root, KeyType k, result &re){

	BTree cp = root;
	BTree before = NULL;
	if (root == NULL){
		re.tag = 0;
		re.pt = NULL;
		re.i = -1;
		return ERROR;
	}
	else{
		int resultKey = 1;
		while (cp != NULL){
			resultKey = searchKey(cp, k);
			if (resultKey <= cp->keynum && cp->key[resultKey] == k){

				re.i = resultKey;
				re.pt = cp;
				re.tag = 1;

				return SUCCESS;
			}
			else{
				before = cp;
				//具体看B树解析中的图片，找不到时会返回resultKey右边的位置，所以要减掉1.
				cp = cp->ptr[resultKey - 1];
			}
		}
		//找不到时候的操作。
		re.tag = 0;
		re.pt = before;
		re.i = resultKey;
		return ERROR;
	}
}

//二分查找，提高查找的效率。
int searchKey(BTree node, KeyType k){
	/*
	int i = 1;
	for (i = 1; i <= node->keynum && k > node->key[i]; i++);
	return i;*/

	if (node == NULL)return ERROR;
	int left = 1;
	int right = node->keynum;

	while (left <= right)  //循环条件，适时而变
	{
		int middle = left + ((right - left) >> 1);  //防止溢出，移位也更高效。同时，每次循环都需要更新。
		if (node->key[middle] > k)
			right = middle - 1;  //right赋值，适时而变
		else if (node->key[middle] < k)
			left = middle + 1;
		else
			return middle;
	}
	return left;//跳出循环说明找不到该元素，则此时left>right,且此时的left在k值应该在的地方的后一个。

}

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
Status InsertBTree(BTree &root, KeyType k){
	if (root == NULL){
		if (NewBroot(root, NULL, NULL, k) == SUCCESS){
			return SUCCESS;
		}
	}
	else{
		result re;
		if (SUCCESS == SearchBTree(root, k, re)){
			return ERROR;
		}
		//node位置的地方，在B树中关键字的个数要小于等于m-1，当等于m-1要再插入元素时，就得分割结点
		BTree node = re.pt;//返回结点要插入的层
		int KeySite = re.i;//结点的位置
		BTree SpiltRight = NULL;//分割后的右节点
		KeyType midKey;//分割后该层的中间关键字

		while (node != NULL){
			if (InsertNode(node, KeySite, k, SpiltRight) == ERROR){
				return ERROR;
			}
			//小于m即最大是m-1，当等于m时，说明超出了
			if (node->keynum < m){
				return SUCCESS;
			}
			else{
				midKey = node->key[(m + 1) / 2];
				SpiltRight = NULL;
				if (SpiltToTwo(node, SpiltRight) == ERROR){
					return ERROR;
				}
				else{
					//分割后node的中间关键字要插入到他的父亲节点中去
					if (node->parent == NULL){
						if (NewBroot(root, node, SpiltRight, midKey) == SUCCESS){
							return SUCCESS;
						}
					}
					else{
						node = node->parent;
						KeySite = searchKey(node, midKey);
						k = midKey;
					}
				}

			}
		}

	}
	return ERROR;
}
//root是某层，KeySite是要插入的地方,k是要插入的关键字，node是keySite对应的ptr
Status InsertNode(BTree &root, int KeySite, KeyType k, BTree &node){
	if (root == NULL)return ERROR;
	int keyNum = root->keynum;
	for (int i = keyNum; i >= KeySite; i--){
		root->key[i + 1] = root->key[i];
		root->ptr[i + 1] = root->ptr[i];
	}
	root->key[KeySite] = k;
	root->ptr[KeySite] = node;
	if (node != NULL){
		node->parent = root;
	}
	root->keynum++;
	return SUCCESS;
}
//分割成两个节点，一半留在root，一半在SpiltRight
Status SpiltToTwo(BTree &root, BTree &SpiltRight){
	int mid = (m + 1) / 2;

	SpiltRight = (BTree)malloc(sizeof(BTNode));

	if (SpiltRight == NULL)return ERROR;

	SpiltRight->parent = NULL;
	SpiltRight->keynum = 0;

	for (int i = 0; i <= m; i++){
		SpiltRight->ptr[i] = NULL;
	}
	//key的0位置是不存值的
	SpiltRight->ptr[0] = root->ptr[mid];

	for (int i = mid + 1; i <= root->keynum; i++){
		SpiltRight->key[i - mid] = root->key[i];
		SpiltRight->ptr[i - mid] = root->ptr[i];
		SpiltRight->keynum++;
	}
	root->keynum = mid - 1;
	SpiltRight->parent = root->parent;
	//修改孩子的父亲
	for (int i = 0; i <= SpiltRight->keynum; i++){
		if (SpiltRight->ptr[i] != NULL){
			SpiltRight->ptr[i]->parent = SpiltRight;
		}
	}
	return SUCCESS;
}

//生成一个新根
Status NewBroot(BTree &root, BTree left, BTree right, KeyType k){

	root = (BTree)malloc(sizeof(BTNode));
	if (root == NULL){
		return ERROR;
	}
	else{
		for (int i = 0; i <= m; i++){
			root->ptr[i] = NULL;
		}

		root->keynum = 1;
		root->parent = NULL;
		root->ptr[0] = left;
		root->ptr[1] = right;
		root->key[1] = k;

		if (left != NULL){
			left->parent = root;
		}
		if (right != NULL){
			right->parent = root;
		}

		return SUCCESS;
	}
	return ERROR;
}

/*
Time:2019/11/28
函数功能：

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

Status  DeleteBTree(BTree &root, KeyType k){
	if (root == NULL)return ERROR;

	result re;
	if (SearchBTree(root, k, re) == ERROR){
		return ERROR;
	}
	else{
		BTree node = re.pt;
		int KeySite = re.i;

		BTree nodeLeft = NULL;//左孩子
		BTree nodeRight = NULL;//右孩子

		int KeySiteLeft;
		KeyType KeyLeft; //左孩子的最右关键字
		KeyType KeyRight; //右孩子的最左关键字

		if (node->ptr[KeySite] != NULL){

			nodeRight = node->ptr[KeySite];

			while (nodeRight->ptr[0] != NULL){
				nodeRight = nodeRight->ptr[0];
			}

			KeyRight = nodeRight->key[1];
			node->key[KeySite] = KeyRight;

			DeleteNode(nodeRight, 1);

			if (nodeRight->keynum < (m + 1) / 2 - 1){
				Restore(nodeRight);
			}
		}
		else if (node->ptr[KeySite - 1] != NULL){

			nodeLeft = node->ptr[KeySite - 1];//拿到左孩子

			KeySiteLeft = nodeLeft->keynum; //左孩子最右边的孩子。

			while (nodeLeft->ptr[KeySiteLeft] != NULL){
				nodeLeft = nodeLeft->ptr[KeySiteLeft];
				KeySiteLeft = nodeLeft->keynum;
			}
			//左孩子最右边的关键字
			KeyLeft = nodeLeft->key[KeySiteLeft];
			node->key[KeySite] = KeyLeft;
			DeleteNode(nodeLeft, KeySiteLeft);

			if (nodeLeft->keynum < (m + 1) / 2 - 1){
				Restore(nodeLeft);
			}

		}
		else if (node->ptr[KeySite - 1] == NULL && node->ptr[KeySite] == NULL){
			if (DeleteNode(node, KeySite) == ERROR)return ERROR;
			if (node->keynum < (m + 1) / 2 - 1){
				Restore(node);
			}
		}
		if (root->keynum == 0 && root->ptr[0] != NULL && root->ptr[0]->keynum != 0){
			BTree p = root;
			root = root->ptr[0];
			free(p);
			root->parent = NULL;
		}
		else if (root->keynum == 0 && root->ptr[0] == NULL){
			BTree p = root;
			free(p);
			root = NULL;
		}
		return SUCCESS;


	}
}

//调整某节点
Status Restore(BTree &node){
	BTree Parent = NULL;
	do{
		Parent = node->parent;

		if (node == NULL)return ERROR;
		if (Parent == NULL)return ERROR;

		int PtrSite = 0;
		for (int i = 0; i <= Parent->keynum; i++){
			if (node == Parent->ptr[i]){
				PtrSite = i;
				break;
			}
		}
		int PtrSiteRight = PtrSite + 1;
		int PtrSiteLeft = PtrSite - 1;
		KeyType ParentKey;

		int Finished = 0;//用于判断是否完成在邻接节点富裕情况下的调整。
		//如果node处在中间。
		if (PtrSite >= 1 && PtrSite < Parent->keynum){
			if (Parent->ptr[PtrSiteRight]->keynum >(m + 1) / 2 - 1){
				//如果右子树丰满

				ParentKey = Parent->key[PtrSiteRight];
				Parent->key[PtrSiteRight] = Parent->ptr[PtrSiteRight]->key[1];

				InsertNode(node, node->keynum + 1, ParentKey, Parent->ptr[PtrSiteRight]->ptr[0]);
				DeleteNode(Parent->ptr[PtrSiteRight], 0);
				Finished = 1;

			}
			else if (Parent->ptr[PtrSiteLeft]->keynum > (m + 1) / 2 - 1){

				//左邻节点丰满，那么就拿左邻的最右边的元素
				int RightFinal = Parent->ptr[PtrSiteLeft]->keynum;

				ParentKey = Parent->key[PtrSite];
				Parent->key[PtrSite] = Parent->ptr[PtrSiteLeft]->key[RightFinal];

				InsertNode(node, 1, ParentKey, node->ptr[0]);
				node->ptr[0] = Parent->ptr[PtrSiteLeft]->ptr[RightFinal];

				DeleteNode(Parent->ptr[PtrSiteLeft], RightFinal);

				Finished = 1;
			}
		}
		//如果node处在最左边
		else if (PtrSite == 0){
			if (Parent->ptr[PtrSiteRight]->keynum >(m + 1) / 2 - 1){
				//如果右子树丰满

				ParentKey = Parent->key[PtrSiteRight];
				Parent->key[PtrSiteRight] = Parent->ptr[PtrSiteRight]->key[1];

				InsertNode(node, node->keynum + 1, ParentKey, Parent->ptr[PtrSiteRight]->ptr[0]);
				DeleteNode(Parent->ptr[PtrSiteRight], 0);
				Finished = 1;
			}
		}
		else if (PtrSite == Parent->keynum){
			if (Parent->ptr[PtrSiteLeft]->keynum > (m + 1) / 2 - 1){

				ParentKey = Parent->key[PtrSite];

				//左邻节点丰满，那么就拿左邻的最右边的元素
				int RightFinal = Parent->ptr[PtrSiteLeft]->keynum;

				Parent->key[PtrSite] = Parent->ptr[PtrSiteLeft]->key[RightFinal];

				InsertNode(node, 1, ParentKey, node->ptr[0]);
				node->ptr[0] = Parent->ptr[PtrSiteLeft]->ptr[RightFinal];

				DeleteNode(Parent->ptr[PtrSiteLeft], RightFinal);
				Finished = 1;
			}
		}
		//Finished == 0说明没有完成调整，即相邻节点都不富裕。
		if (Finished == 0){
			if (PtrSite >= 1 && PtrSite <= Parent->keynum){
				Merge(Parent->ptr[PtrSiteLeft], node, Parent);
			}
			else if (PtrSite == 0){
				Merge(node, Parent->ptr[1], Parent);
			}
			else if (PtrSite == Parent->keynum){
				Merge(Parent->ptr[Parent->keynum - 1], node, Parent);
			}
		}
		if (Parent->keynum < (m + 1) / 2 - 1 && Parent->parent != NULL && Parent->parent->keynum != 0){
			node = Parent;
		}
	} while (Parent->keynum < (m + 1) / 2 - 1 && Parent->parent != NULL && Parent->parent->keynum != 0);
	return SUCCESS;

}

//合并两个结点,统一操作，右边合并到左边
Status Merge(BTree &Left, BTree &Right, BTree &Parent){
	//拿到父节点的key
	int ParentKeySite = 0;
	for (int i = 0; i <= Parent->keynum; i++){
		if (Parent->ptr[i] == Left){
			ParentKeySite = i;
			break;
		}
	}
	//定位到key
	ParentKeySite += 1;
	KeyType ParentKey = Parent->key[ParentKeySite];

	//将ParentKey插入到左边，并且将右邻的第一个孩子转移过来
	InsertNode(Left, Left->keynum + 1, ParentKey, Right->ptr[0]);

	//把右边的所有关键字插入到左边
	for (int i = 1; i <= Right->keynum; i++){
		InsertNode(Left, Left->keynum + 1, Right->key[i], Right->ptr[i]);
	}
	//释放掉不要的结点
	BTree freeNode = Parent->ptr[ParentKeySite];
	Parent->ptr[ParentKeySite] = NULL;

	DeleteNode(Parent, ParentKeySite);

	free(freeNode);
	freeNode = NULL;

	return SUCCESS;
}

//在叶子层删除某个关键字。
Status DeleteNode(BTree &node, int KeySite){
	if (node == NULL)return ERROR;
	for (int i = KeySite; i <= node->keynum; i++){
		node->key[i] = node->key[i + 1];
		node->ptr[i] = node->ptr[i + 1];
	}
	node->keynum--;
	return SUCCESS;
}

//凹入表打印B树
void Aoprint(BTree T, int depth){
	if (T == NULL)return;
	for (int i = T->keynum; i > 0; i--){
		Aoprint(T->ptr[i], depth + 1);
		for (int j = 0; j < depth; j++){
			printf("    ");
		}
		printf("%d\n", T->key[i]);
	}
	Aoprint(T->ptr[0], depth + 1);
}
//销毁B树
void Destroy(BTree &T){
	if (T){
		for (int i = 0; i <= T->keynum; i++)
			Destroy(T->ptr[i]);
		free(T);
		T = NULL;
	}
}

//求深度
int Depth(BTree T){
	if (NULL == T)
		return 0;
	int depth, max = 0;
	for (int i = 0; i <= T->keynum; i++){
		depth = Depth(T->ptr[i]);
		max = depth > max ? depth : max;
	}
	return max + 1;
}

//求叶子数
int Leaves(BTree T){
	if (NULL == T)
		return 0;
	int leaves = 0, isleave = 1;
	for (int i = 0; i <= T->keynum; i++){
		if (T->ptr[i] != NULL){
			leaves += Leaves(T->ptr[i]);
			isleave = 0;
		}
	}
	if (isleave)
		return 1;
	return leaves;
}

//升序遍历
void AscOrderTraverse(BTree T){
	if (NULL == T)
		return;
	AscOrderTraverse(T->ptr[0]);
	for (int i = 1; i <= T->keynum; i++){
		printf("%d\t", T->key[i]);
		AscOrderTraverse(T->ptr[i]);
	}
}

//降序遍历
void DesOrderTraverse(BTree T){
	if (NULL == T)
		return;
	for (int i = T->keynum; i>0; i--){
		DesOrderTraverse(T->ptr[i]);
		printf("%d\t", T->key[i]);
	}
	DesOrderTraverse(T->ptr[0]);
}