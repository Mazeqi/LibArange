#include"../CodeHead/BTreeHead.h"
#include<stdio.h>
#include<stdlib.h>
/*
Time:2019/11/26 19:50
�������ã���B���в��ҹؼ���Ϊk�Ľ��
�����ĺ�����SearchBTree,SearchKey,����SearchKey���˶��ֲ���
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
				//���忴B�������е�ͼƬ���Ҳ���ʱ�᷵��resultKey�ұߵ�λ�ã�����Ҫ����1.
				cp = cp->ptr[resultKey - 1];
			}
		}
		//�Ҳ���ʱ��Ĳ�����
		re.tag = 0;
		re.pt = before;
		re.i = resultKey;
		return ERROR;
	}
}

//���ֲ��ң���߲��ҵ�Ч�ʡ�
int searchKey(BTree node, KeyType k){
	/*
	int i = 1;
	for (i = 1; i <= node->keynum && k > node->key[i]; i++);
	return i;*/

	if (node == NULL)return ERROR;
	int left = 1;
	int right = node->keynum;

	while (left <= right)  //ѭ����������ʱ����
	{
		int middle = left + ((right - left) >> 1);  //��ֹ�������λҲ����Ч��ͬʱ��ÿ��ѭ������Ҫ���¡�
		if (node->key[middle] > k)
			right = middle - 1;  //right��ֵ����ʱ����
		else if (node->key[middle] < k)
			left = middle + 1;
		else
			return middle;
	}
	return left;//����ѭ��˵���Ҳ�����Ԫ�أ����ʱleft>right,�Ҵ�ʱ��left��kֵӦ���ڵĵط��ĺ�һ����

}

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
		//nodeλ�õĵط�����B���йؼ��ֵĸ���ҪС�ڵ���m-1��������m-1Ҫ�ٲ���Ԫ��ʱ���͵÷ָ���
		BTree node = re.pt;//���ؽ��Ҫ����Ĳ�
		int KeySite = re.i;//����λ��
		BTree SpiltRight = NULL;//�ָ����ҽڵ�
		KeyType midKey;//�ָ��ò���м�ؼ���

		while (node != NULL){
			if (InsertNode(node, KeySite, k, SpiltRight) == ERROR){
				return ERROR;
			}
			//С��m�������m-1��������mʱ��˵��������
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
					//�ָ��node���м�ؼ���Ҫ���뵽���ĸ��׽ڵ���ȥ
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
//root��ĳ�㣬KeySite��Ҫ����ĵط�,k��Ҫ����Ĺؼ��֣�node��keySite��Ӧ��ptr
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
//�ָ�������ڵ㣬һ������root��һ����SpiltRight
Status SpiltToTwo(BTree &root, BTree &SpiltRight){
	int mid = (m + 1) / 2;

	SpiltRight = (BTree)malloc(sizeof(BTNode));

	if (SpiltRight == NULL)return ERROR;

	SpiltRight->parent = NULL;
	SpiltRight->keynum = 0;

	for (int i = 0; i <= m; i++){
		SpiltRight->ptr[i] = NULL;
	}
	//key��0λ���ǲ���ֵ��
	SpiltRight->ptr[0] = root->ptr[mid];

	for (int i = mid + 1; i <= root->keynum; i++){
		SpiltRight->key[i - mid] = root->key[i];
		SpiltRight->ptr[i - mid] = root->ptr[i];
		SpiltRight->keynum++;
	}
	root->keynum = mid - 1;
	SpiltRight->parent = root->parent;
	//�޸ĺ��ӵĸ���
	for (int i = 0; i <= SpiltRight->keynum; i++){
		if (SpiltRight->ptr[i] != NULL){
			SpiltRight->ptr[i]->parent = SpiltRight;
		}
	}
	return SUCCESS;
}

//����һ���¸�
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
�������ܣ�

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

Status  DeleteBTree(BTree &root, KeyType k){
	if (root == NULL)return ERROR;

	result re;
	if (SearchBTree(root, k, re) == ERROR){
		return ERROR;
	}
	else{
		BTree node = re.pt;
		int KeySite = re.i;

		BTree nodeLeft = NULL;//����
		BTree nodeRight = NULL;//�Һ���

		int KeySiteLeft;
		KeyType KeyLeft; //���ӵ����ҹؼ���
		KeyType KeyRight; //�Һ��ӵ�����ؼ���

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

			nodeLeft = node->ptr[KeySite - 1];//�õ�����

			KeySiteLeft = nodeLeft->keynum; //�������ұߵĺ��ӡ�

			while (nodeLeft->ptr[KeySiteLeft] != NULL){
				nodeLeft = nodeLeft->ptr[KeySiteLeft];
				KeySiteLeft = nodeLeft->keynum;
			}
			//�������ұߵĹؼ���
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

//����ĳ�ڵ�
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

		int Finished = 0;//�����ж��Ƿ�������ڽӽڵ㸻ԣ����µĵ�����
		//���node�����м䡣
		if (PtrSite >= 1 && PtrSite < Parent->keynum){
			if (Parent->ptr[PtrSiteRight]->keynum >(m + 1) / 2 - 1){
				//�������������

				ParentKey = Parent->key[PtrSiteRight];
				Parent->key[PtrSiteRight] = Parent->ptr[PtrSiteRight]->key[1];

				InsertNode(node, node->keynum + 1, ParentKey, Parent->ptr[PtrSiteRight]->ptr[0]);
				DeleteNode(Parent->ptr[PtrSiteRight], 0);
				Finished = 1;

			}
			else if (Parent->ptr[PtrSiteLeft]->keynum > (m + 1) / 2 - 1){

				//���ڽڵ��������ô�������ڵ����ұߵ�Ԫ��
				int RightFinal = Parent->ptr[PtrSiteLeft]->keynum;

				ParentKey = Parent->key[PtrSite];
				Parent->key[PtrSite] = Parent->ptr[PtrSiteLeft]->key[RightFinal];

				InsertNode(node, 1, ParentKey, node->ptr[0]);
				node->ptr[0] = Parent->ptr[PtrSiteLeft]->ptr[RightFinal];

				DeleteNode(Parent->ptr[PtrSiteLeft], RightFinal);

				Finished = 1;
			}
		}
		//���node���������
		else if (PtrSite == 0){
			if (Parent->ptr[PtrSiteRight]->keynum >(m + 1) / 2 - 1){
				//�������������

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

				//���ڽڵ��������ô�������ڵ����ұߵ�Ԫ��
				int RightFinal = Parent->ptr[PtrSiteLeft]->keynum;

				Parent->key[PtrSite] = Parent->ptr[PtrSiteLeft]->key[RightFinal];

				InsertNode(node, 1, ParentKey, node->ptr[0]);
				node->ptr[0] = Parent->ptr[PtrSiteLeft]->ptr[RightFinal];

				DeleteNode(Parent->ptr[PtrSiteLeft], RightFinal);
				Finished = 1;
			}
		}
		//Finished == 0˵��û����ɵ����������ڽڵ㶼����ԣ��
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

//�ϲ��������,ͳһ�������ұߺϲ������
Status Merge(BTree &Left, BTree &Right, BTree &Parent){
	//�õ����ڵ��key
	int ParentKeySite = 0;
	for (int i = 0; i <= Parent->keynum; i++){
		if (Parent->ptr[i] == Left){
			ParentKeySite = i;
			break;
		}
	}
	//��λ��key
	ParentKeySite += 1;
	KeyType ParentKey = Parent->key[ParentKeySite];

	//��ParentKey���뵽��ߣ����ҽ����ڵĵ�һ������ת�ƹ���
	InsertNode(Left, Left->keynum + 1, ParentKey, Right->ptr[0]);

	//���ұߵ����йؼ��ֲ��뵽���
	for (int i = 1; i <= Right->keynum; i++){
		InsertNode(Left, Left->keynum + 1, Right->key[i], Right->ptr[i]);
	}
	//�ͷŵ���Ҫ�Ľ��
	BTree freeNode = Parent->ptr[ParentKeySite];
	Parent->ptr[ParentKeySite] = NULL;

	DeleteNode(Parent, ParentKeySite);

	free(freeNode);
	freeNode = NULL;

	return SUCCESS;
}

//��Ҷ�Ӳ�ɾ��ĳ���ؼ��֡�
Status DeleteNode(BTree &node, int KeySite){
	if (node == NULL)return ERROR;
	for (int i = KeySite; i <= node->keynum; i++){
		node->key[i] = node->key[i + 1];
		node->ptr[i] = node->ptr[i + 1];
	}
	node->keynum--;
	return SUCCESS;
}

//������ӡB��
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
//����B��
void Destroy(BTree &T){
	if (T){
		for (int i = 0; i <= T->keynum; i++)
			Destroy(T->ptr[i]);
		free(T);
		T = NULL;
	}
}

//�����
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

//��Ҷ����
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

//�������
void AscOrderTraverse(BTree T){
	if (NULL == T)
		return;
	AscOrderTraverse(T->ptr[0]);
	for (int i = 1; i <= T->keynum; i++){
		printf("%d\t", T->key[i]);
		AscOrderTraverse(T->ptr[i]);
	}
}

//�������
void DesOrderTraverse(BTree T){
	if (NULL == T)
		return;
	for (int i = T->keynum; i>0; i--){
		DesOrderTraverse(T->ptr[i]);
		printf("%d\t", T->key[i]);
	}
	DesOrderTraverse(T->ptr[0]);
}