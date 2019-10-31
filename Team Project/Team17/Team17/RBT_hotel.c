#include "RBT_hotel.h"

void H_LeftRotate(struct HNode **T, struct HNode **x) {
	struct HNode *y = (*x)->right;
	(*x)->right = y->left;
	if (y->left != NULL)
		y->left->parent = *x;
	y->parent = (*x)->parent;
	if ((*x)->parent == NULL)
		*T = y;
	else if (*x == (*x)->parent->left)
		(*x)->parent->left = y;
	else
		(*x)->parent->right = y;
	y->left = *x;
	(*x)->parent = y;
}
void H_RightRotate(struct HNode **T, struct HNode **x) {
	struct HNode *y = (*x)->left;
	(*x)->left = y->right;
	if (y->right != NULL)
		y->right->parent = *x;
	y->parent = (*x)->parent;
	if ((*x)->parent == NULL)
		*T = y;
	else if ((*x) == (*x)->parent->left)
		(*x)->parent->left = y;
	else
		(*x)->parent->right = y;
	y->right = *x;
	(*x)->parent = y;
}
void H_RB_INSERT_fixup(struct HNode **T, struct HNode **z) {
	struct HNode *grandparent = NULL;
	struct HNode *parentpt = NULL;
	while (((*z) != *T) && ((*z)->color != H_BLACK) && ((*z)->parent->color == H_RED)) {
		parentpt = (*z)->parent;
		grandparent = (*z)->parent->parent;
		if (parentpt == grandparent->left) {
			struct HNode *uncle = grandparent->right;
			if (uncle != NULL && uncle->color == H_RED) {
				grandparent->color = H_RED;
				parentpt->color = H_BLACK;
				uncle->color = H_BLACK;
				*z = grandparent;
			}
			else {
				if ((*z) == parentpt->right) {
					H_LeftRotate(T, &parentpt);
					(*z) = parentpt;
					parentpt = (*z)->parent;
				}
				H_RightRotate(T, &grandparent);
				parentpt->color = H_BLACK;
				grandparent->color = H_RED;
				(*z) = parentpt;
			}
		}
		else {
			struct HNode *uncle = grandparent->left;
			if (uncle != NULL && uncle->color == H_RED) {
				grandparent->color = H_RED;
				parentpt->color = H_BLACK;
				uncle->color = H_BLACK;
				(*z) = grandparent;
			}
			else {
				if ((*z) == parentpt->left) {
					H_RightRotate(T, &parentpt);
					(*z) = parentpt;
					parentpt = (*z)->parent;
				}
				H_LeftRotate(T, &grandparent);
				parentpt->color = H_BLACK;
				grandparent->color = H_RED;
				(*z) = parentpt;
			}
		}
	}
	(*T)->color = H_BLACK;
}
struct HNode *H_RB_INSERT(struct HNode *T, int price, int id) {
	struct HNode *z = (struct HNode*)malloc(sizeof(struct HNode));
	z->id = id;
	z->price = price;
	z->left = NULL;
	z->right = NULL;
	z->parent = NULL;
	z->color = H_RED;

	struct HNode *y = NULL;
	struct HNode *x = T;

	while (x != NULL) {
		y = x;
		if (z->price < x->price)
			x = x->left;
		else
			x = x->right;
	}
	z->parent = y;
	if (y == NULL)
		T = z;

	else if (z->price < y->price)
		y->left = z;
	else
		y->right = z;
	H_RB_INSERT_fixup(&T, &z);
	return T;
}
struct HNode *H_Tree_minimum(struct HNode *node) {
	while (node->left != NULL)
		node = node->left;
	return node;
}
void H_RB_delete_fixup(struct HNode **T, struct HNode **x) {
	while ((*x) != *T && (*x)->color == H_BLACK) {
		if ((*x) == (*x)->parent->left) {
			struct HNode *w = (*x)->parent->right;
			if (w->color == H_RED) {
				w->color = H_BLACK;
				(*x)->parent->color = H_BLACK;
				H_LeftRotate(T, &((*x)->parent));
				w = (*x)->parent->right;
			}
			if (w->left->color == H_BLACK && w->right->color == H_BLACK) {
				w->color = H_RED;
				(*x) = (*x)->parent;
			}
			else {
				if (w->right->color == H_BLACK) {
					w->left->color = H_BLACK;
					w->color = H_RED;
					H_RightRotate(T, &w);
					w = (*x)->parent->right;
				}

				w->color = (*x)->parent->color;
				(*x)->parent->color = H_BLACK;
				w->right->color = H_BLACK;
				H_LeftRotate(T, &((*x)->parent));
				(*x) = *T;
			}
		}
		else {
			struct HNode *w = (*x)->parent->left;

			if (w->color == H_RED) {
				w->color = H_BLACK;
				(*x)->parent->color = H_BLACK;
				H_RightRotate(T, &((*x)->parent));
				w = (*x)->parent->left;
			}
			if (w->right->color == H_BLACK && w->left->color == H_BLACK) {
				w->color = H_RED;
				(*x) = (*x)->parent;
			}
			else {
				if (w->left->color == H_BLACK) {
					w->right->color = H_BLACK;
					w->color = H_RED;
					H_LeftRotate(T, &w);
					w = (*x)->parent->left;
				}
				w->color = (*x)->parent->color;
				(*x)->parent->color = H_BLACK;
				w->left->color = H_BLACK;
				H_RightRotate(T, &((*x)->parent));
				(*x) = *T;
			}
		}
	}
	(*x)->color = H_BLACK;
}
void H_RB_transplat(struct HNode **T, struct HNode **u, struct HNode **v) {
	if ((*u)->parent == NULL)
		*T = *v;
	else if ((*u) == (*u)->parent->left)
		(*u)->parent->left = *v;
	else
		(*u)->parent->right = *v;
	if ((*v) != NULL)
		(*v)->parent = (*u)->parent;
}
struct HNode *H_RB_DELETE(struct HNode *T, struct HNode *z) {
	struct HNode *y = z;
	enum type yoc;
	yoc = z->color;
	struct HNode *x;
	if (z->left == NULL) {
		x = z->right;
		H_RB_transplat(&T, &z, &(z->right));
	}
	else if (z->right == NULL) {
		x = z->left;
		H_RB_transplat(&T, &z, &(z->left));
	}
	else {
		y = H_Tree_minimum(z->right);
		yoc = y->color;
		x = y->right;

		if (y->parent == z)
			x->parent = y;

		else {
			H_RB_transplat(&T, &y, &(y->right));
			y->right = z->right;
			y->right->parent = y;
		}

		H_RB_transplat(&T, &z, &y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	if (yoc == H_BLACK)
		H_RB_delete_fixup(&T, &x);
	return T;
}
struct HNode *H_BST_search(struct HNode *root, int x) {
	if (root == NULL || root->price == x)
		return root;
	if (root->price > x)
		return  H_BST_search(root->left, x);
	else
		return H_BST_search(root->right, x);
}
int H_check(int *a, int value) {
	for (int i = 0; i < 20; i++) {
		if (a[i] == value)
			return 0;
	}
	return 1;
}
void H_PRINT_BST(struct HNode *t) {
	if (t == NULL)
		return;
	printf("Hotel[%d] - %d$ (%c) :", t->id, t->price, color(t->color));
	if (t->left != NULL)
		printf("LEFT [%d] (%c)", (t->left)->id, color((t->left)->color));
	if (t->right != NULL)
		printf("RIGHT [%d] (%c)", (t->right)->id, color((t->right)->color));
	printf("\n");
	if (t->left)
		H_PRINT_BST(t->left);
	if (t->right)
		H_PRINT_BST(t->right);
}
int H_height(struct HNode *Root) {
	int h = 0;
	if (Root != NULL) {
		if (Root == NULL)
			h = 1;
		else {
			int leftHeight = H_height(Root->left);
			int rightHeight = H_height(Root->right);
			h = MAX(leftHeight, rightHeight) + 1;
		}
	}
	return h;
}
struct HNode *findMaximum(struct HNode *root) {
	while (root->right)
		root = root->right;
	return root;
}
struct HNode *findPredecessor(struct HNode *root, struct HNode *prec, int key) {
	if (root == NULL)
		return;
	if (root->price == key) {
		if (root->left)
			prec = findMaximum(root->left);
	}
	else if (key < root->price) {
		findPredecessor(root->left, prec, key);
	}
	else {
		prec = root;
		findPredecessor(root->right, prec, key);
	}
	return prec;
}