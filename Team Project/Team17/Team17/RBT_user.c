#include "RBT_user.h"

void U_LeftRotate(struct UNode **T, struct UNode **x) {
	struct UNode *y = (*x)->right;
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
void U_RightRotate(struct UNode **T, struct UNode **x) {
	struct UNode *y = (*x)->left;
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
void U_RB_INSERT_fixup(struct UNode **T, struct UNode **z) {
	struct UNode *grandparent = NULL;
	struct UNode *parentpt = NULL;
	while (((*z) != *T) && ((*z)->color != BLACK) && ((*z)->parent->color == RED)) {
		parentpt = (*z)->parent;
		grandparent = (*z)->parent->parent;
		if (parentpt == grandparent->left) {
			struct UNode *uncle = grandparent->right;
			if (uncle != NULL && uncle->color == RED) {
				grandparent->color = RED;
				parentpt->color = BLACK;
				uncle->color = BLACK;
				*z = grandparent;
			}
			else {
				if ((*z) == parentpt->right) {
					U_LeftRotate(T, &parentpt);
					(*z) = parentpt;
					parentpt = (*z)->parent;
				}
				U_RightRotate(T, &grandparent);
				parentpt->color = BLACK;
				grandparent->color = RED;
				(*z) = parentpt;
			}
		}
		else {
			struct UNode* uncle = grandparent->left;
			if (uncle != NULL && uncle->color == RED) {
				grandparent->color = RED;
				parentpt->color = BLACK;
				uncle->color = BLACK;
				(*z) = grandparent;
			}
			else {
				if ((*z) == parentpt->left) {
					U_RightRotate(T, &parentpt);
					(*z) = parentpt;
					parentpt = (*z)->parent;
				}
				U_LeftRotate(T, &grandparent);
				parentpt->color = BLACK;
				grandparent->color = RED;
				(*z) = parentpt;
			}
		}
	}
	(*T)->color = BLACK;
}
struct UNode *U_RB_INSERT(struct UNode *T, int id, Time starttime, Time endtime, Time restime, int budget, int stay_day, int fee) {//¹Ù²Ù±â
	struct UNode *z = (struct UNode*)malloc(sizeof(struct UNode));

	z->id = id;
	z->start_time = starttime;
	z->end_time = endtime;
	z->hotel_res_time = restime;
	z->budget = budget;
	z->stay_day = stay_day;
	z->fee = fee;
	z->left = NULL;
	z->right = NULL;
	z->parent = NULL;
	z->color = RED;

	struct UNode *y = NULL;
	struct UNode *x = T;

	while (x != NULL) {
		y = x;
		if (z->id < x->id)
			x = x->left;
		else
			x = x->right;
	}
	z->parent = y;
	if (y == NULL)
		T = z;

	else if (z->id < y->id)
		y->left = z;
	else
		y->right = z;
	U_RB_INSERT_fixup(&T, &z);
	return T;
}
struct UNode *U_Tree_minimum(struct UNode *node) {
	while (node->left != NULL)
		node = node->left;
	return node;
}
void U_RB_delete_fixup(struct UNode **T, struct UNode **x) {
	while ((*x) != *T && (*x)->color == BLACK) {
		if ((*x) == (*x)->parent->left) {
			struct UNode *w = (*x)->parent->right;
			if (w->color == RED) {
				w->color = BLACK;
				(*x)->parent->color = BLACK;
				U_LeftRotate(T, &((*x)->parent));
				w = (*x)->parent->right;
			}
			if (w->left->color == BLACK && w->right->color == BLACK) {
				w->color = RED;
				(*x) = (*x)->parent;
			}
			else {
				if (w->right->color == BLACK) {
					w->left->color = BLACK;
					w->color = RED;
					U_RightRotate(T, &w);
					w = (*x)->parent->right;
				}

				w->color = (*x)->parent->color;
				(*x)->parent->color = BLACK;
				w->right->color = BLACK;
				U_LeftRotate(T, &((*x)->parent));
				(*x) = *T;
			}
		}
		else {
			struct UNode *w = (*x)->parent->left;

			if (w->color == RED) {
				w->color = BLACK;
				(*x)->parent->color = BLACK;
				U_RightRotate(T, &((*x)->parent));
				w = (*x)->parent->left;
			}
			if (w->right->color == BLACK && w->left->color == BLACK) {
				w->color = RED;
				(*x) = (*x)->parent;
			}
			else {
				if (w->left->color == BLACK) {
					w->right->color = BLACK;
					w->color = RED;
					U_LeftRotate(T, &w);
					w = (*x)->parent->left;
				}
				w->color = (*x)->parent->color;
				(*x)->parent->color = BLACK;
				w->left->color = BLACK;
				U_RightRotate(T, &((*x)->parent));
				(*x) = *T;
			}
		}
	}
	(*x)->color = BLACK;
}
void U_RB_transplat(struct UNode **T, struct UNode **u, struct UNode **v) {
	if ((*u)->parent == NULL)
		*T = *v;
	else if ((*u) == (*u)->parent->left)
		(*u)->parent->left = *v;
	else
		(*u)->parent->right = *v;
	if ((*v) != NULL)
		(*v)->parent = (*u)->parent;
}
struct UNode *U_RB_DELETE(struct UNode *T, struct UNode *z) {
	struct UNode *y = z;
	enum type yoc;
	yoc = z->color;
	struct UNode *x;
	if (z->left == NULL) {
		x = z->right;
		U_RB_transplat(&T, &z, &(z->right));
	}
	else if (z->right == NULL) {
		x = z->left;
		U_RB_transplat(&T, &z, &(z->left));
	}
	else {
		y = U_Tree_minimum(z->right);
		yoc = y->color;
		x = y->right;

		if (y->parent == z)
			x->parent = y;

		else {
			U_RB_transplat(&T, &y, &(y->right));
			y->right = z->right;
			y->right->parent = y;
		}

		U_RB_transplat(&T, &z, &y);
		y->left = z->left;
		y->left->parent = y;
		y->color = z->color;
	}
	if (yoc == BLACK)
		U_RB_delete_fixup(&T, &x);
	return T;
}
int U_BST_search(struct UNode *root, int x) {
	int temp = 0;
	if (root == NULL) {
		temp = 1;
		return temp;
	}
	else if (root->id == x) {
		temp = 0;
		return temp;
	}
	else if (root->id > x)
		return  U_BST_search(root->left, x);
	else
		return U_BST_search(root->right, x);
}
int U_check(int *a, int value) {
	for (int i = 0; i < 20; i++) {
		if (a[i] == value)
			return 0;
	}
	return 1;
}
void U_PRINT_BST(struct UNode *t) {
	if (t == NULL)
		return;
	printf("user[%d](%c) :", t->id, color(t->color));
	if (t->left != NULL)
		printf("LEFT [%d] (%c)", (t->left)->id, color((t->left)->color));
	if (t->right != NULL)
		printf("RIGHT [%d] (%c)", (t->right)->id, color((t->right)->color));
	printf("\n");
	if (t->left)
		U_PRINT_BST(t->left);
	if (t->right)
		U_PRINT_BST(t->right);
}
int U_height(struct UNode *Root)
{
	int h = 0;
	if (Root != NULL) {
		if (Root == NULL)
			h = 1;
		else {
			int leftHeight = U_height(Root->left);
			int rightHeight = U_height(Root->right);
			h = MAX(leftHeight, rightHeight) + 1;
		}
	}
	return h;
}