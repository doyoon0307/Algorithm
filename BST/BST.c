#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef struct _BSTNode {
	int key;
	struct _BSTNode *leftchild;
	struct _BSTNode *rightchild;
	struct _BSTNode *parent;
} BSTNode;

BSTNode *Create(int key) {
	BSTNode *temp = (BSTNode *)malloc(sizeof(BSTNode));
	temp->key = key;
	temp->leftchild = temp->rightchild = NULL;
	temp->parent = NULL;
	return temp;
}
BSTNode *Search(BSTNode *node, int key) {
	if (node == NULL) {
		printf("key %d is not in BST.\n", key);
		return node;
	}
	if (node->key == key) {
		printf("key %d is in BST.\n", key);
		return node;
	}
	else if (node->key > key) {
		printf("visit %d\n", node->key);
		return Search(node->leftchild, key);
	}
	else {
		printf("visit %d\n", node->key);
		return Search(node->rightchild, key);
	}
}
BSTNode *Insert(BSTNode *node, int key) {
	if (node == NULL) return Create(key);
	if (key < node->key) {
		BSTNode *lchild = Insert(node->leftchild, key);
		node->leftchild = lchild;
		lchild->parent = node;
	}
	else if (key > node->key) {
		BSTNode *rchild = Insert(node->rightchild, key);
		node->rightchild = rchild;
		rchild->parent = node;
	}
	else
		printf("key %d is already in BST.\n", key);
	return node;
}
BSTNode *Delete(BSTNode *node, int key) {
	if (node == NULL) {
		printf("key %d is not in BST.\n", key);
		return NULL;
	}
	if (key < node->key)
		node->leftchild = Delete(node->leftchild, key);
	else if (key > node->key)
		node->rightchild = Delete(node->rightchild, key);
	else {
		BSTNode *cur = node;
		// Case 1 : No child node 
		if (node->leftchild == NULL && node->rightchild == NULL) {
			node = NULL;
			free(cur);
		}
		// Case 2 : One child node
		else if (node->leftchild == NULL || node->rightchild == NULL) {
			if (node->leftchild != NULL) {
				node = node->leftchild;
				node->parent = cur->parent;
				free(cur);
			}
			else {
				node = node->rightchild;
				node->parent = cur->parent;
				free(cur);
			}
		}
		// Case 3 : Two child nodes
		else {
			cur = cur->rightchild;
			while (cur->leftchild != NULL)
				cur = cur->leftchild;
			node->key = cur->key;
			node->rightchild = Delete(node->rightchild, cur->key);
		}
	}
	return node;
}
int Nodes(BSTNode *node) {
	int l = 0, r = 0;
	if (node->leftchild != NULL)
		l = Nodes(node->leftchild);
	if (node->rightchild != NULL)
		r = Nodes(node->rightchild);
	return 1 + r + l;
}
int *Inorder(BSTNode *root, int num) {
	BSTNode *cur, *pre;
	int *arr = (int *)malloc(sizeof(int)*num);
	int i = 0;
	if (root == NULL) return;
	cur = root;
	while (cur != NULL) {
		if (cur->leftchild == NULL) {
			arr[i] = cur->key;
			i++;
			cur = cur->rightchild;
		}
		else {
			pre = cur->leftchild;
			while (pre->rightchild != NULL && pre->rightchild != cur)
				pre = pre->rightchild;
			if (pre->rightchild == NULL) {
				pre->rightchild = cur;
				cur = cur->leftchild;
			}
			else {
				pre->rightchild = NULL;
				arr[i] = cur->key;
				i++;
				cur = cur->rightchild;
			}
		}
	}
	return arr;
}
int Nearest_neighbor(BSTNode *root, int key) {
	int num = Nodes(root);
	int nearestvalue = 0;
	int temp = 0, index = 0;
	int *inorder = (int *)malloc(sizeof(int)*num);
	inorder = Inorder(root, num);
	for (int i = 0; i < num; i++) {
		if (inorder[i] == key) {
			index = i;
			temp = 1;
			break;
		}
	}
	if (temp == 1) {
		if (index == 0)
			nearestvalue = inorder[1] - inorder[0];
		else if (index == num - 1)
			nearestvalue = inorder[num - 1] - inorder[num - 2];
		else {
			if (inorder[index] - inorder[index - 1] < inorder[index + 1] - inorder[index])
				nearestvalue = inorder[index] - inorder[index - 1];
			else
				nearestvalue = inorder[index + 1] - inorder[index];
		}
	}
	else if (temp == 0) {
		for (int i = num - 1; i >= 0; i--) {
			if (key > inorder[i]) {
				index = i;
				break;
			}
		}
		if (key - inorder[index] < inorder[index + 1] - key)
			nearestvalue = key - inorder[index];
		else
			nearestvalue = inorder[index + 1] - key;
	}
	return nearestvalue;
}
int height(BSTNode *node) {
	int r = 0, l = 0;
	if (node->rightchild != NULL)
		r = height(node->rightchild);
	if (node->leftchild != NULL)
		l = height(node->leftchild);
	return 1 + max(r, l);
}
void printLevel(BSTNode *root, int level) {
	if (root == NULL)
		return;
	if (level == 1) 
		printf("%d ", root->key);
	else if (level > 1) {
		printLevel(root->leftchild, level - 1);
		printLevel(root->rightchild, level - 1);
	}
}
void Printarray(BSTNode *root) {
	int h = height(root);
	for (int i = 1; i <= h; i++) {
		printLevel(root, i);
		printf("\n");
	}
}
void Printtree(BSTNode *root, int space) {
	if (root != NULL) {
		if (root->rightchild)
			Printtree(root->rightchild, space + 4);
		if (space) {
			for (int i = 0; i < space; i++)
				printf(" ");
		}
		if (root->rightchild) {
			printf("/\n");
			for (int i = 0; i < space; i++)
				printf(" ");
		}
		printf("%d \n", root->key);
		if (root->leftchild) {
			for (int i = 0; i < space; i++)
				printf(" ");
			printf("\\\n");
			Printtree(root->leftchild, space + 4);
		}
	}
}
int main() {
	int arr[20];
	int i, j;
	srand(time(NULL));
	for (i = 0; i < 20; i++) {
		arr[i] = rand() % 50;
		for (j = 0; j < i; j++) {
			if (arr[i] == arr[j])
				i--;
		}
	}
	printf("The inserted keys are\n");
	for (i = 0; i < 20; i++)
		printf("%d ", arr[i]);
	printf("\n");
	//problem 2
	BSTNode *root = Create(arr[0]);
	for (i = 1; i < 20; i++)
		Insert(root, arr[i]);
	printf("BST Tree is \n");
	Printtree(root, 0);
	printf("Level order is \n");
	Printarray(root);
	//problem 3
	printf("\nSearch 15\n");
	Search(root, 15);
	printf("\nSearch 8\n");
	Search(root, 8);
	printf("\nSearch 18\n");
	Search(root, 18);
	//problem 4
	printf("\nThe nearest neighbor value of 17 is %d\n", Nearest_neighbor(root, 17));
	printf("The nearest neighbor value of 3 is %d\n", Nearest_neighbor(root, 3));
	printf("The nearest neighbor value of 8 is %d\n", Nearest_neighbor(root, 8));
	//problem 5
	printf("\nInsert 5\n"), Insert(root, 5), /*Printtree(root, 0),*/ Printarray(root);
	printf("\nInsert 7\n"), Insert(root, 7), /*Printtree(root, 0),*/ Printarray(root);
	printf("\nInsert 17\n"), Insert(root, 17), /*Printtree(root, 0),*/ Printarray(root);
	printf("\nInsert 51\n"), Insert(root, 51), /*Printtree(root, 0),*/ Printarray(root);
	//problem 6
	printf("\nDelete 17\n"), Delete(root, 17), /*Printtree(root, 0),*/ Printarray(root);
	printf("\nDelete 5\n"), Delete(root, 5), /*Printtree(root, 0),*/ Printarray(root);
	printf("\nDelete 51\n"), Delete(root, 51), /*Printtree(root, 0),*/ Printarray(root);
	printf("\nDelete 17\n"), Delete(root, 17), /*Printtree(root, 0),*/ Printarray(root);
}