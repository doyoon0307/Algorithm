# ifndef RBTHOTEL_H
# define RBTHOTEL_H

#include <stdio.h>
#include <stdlib.h>
enum H_type { H_RED, H_BLACK };
//typedef int bool;
#define true 1
#define false 0
#define color(a) (((a)==0)?(a = 'R'):(a ='B')) // used in print node color
#define MAX(a,b) (((a)>(b))?(a):(b)) //used in height func

struct HNode {
	int price;
	int id;
	struct HNode *left;
	struct HNode *right;
	struct HNode *parent;
	enum H_type color;
} HNode; // for RBT

void H_LeftRotate(struct HNode **T, struct HNode **x);

void H_RightRotate(struct HNode **T, struct HNode **x);

void H_RB_INSERT_fixup(struct HNode **T, struct HNode **z);

struct HNode *H_RB_INSERT(struct HNode *T, int price, int id);

struct HNode *H_Tree_minimum(struct HNode *node);

void H_RB_delete_fixup(struct HNode **T, struct HNode **x);

void H_RB_transplat(struct HNode **T, struct HNode **u, struct HNode **v);

struct HNode *H_RB_DELETE(struct HNode *T, struct HNode *z);

struct HNode *H_BST_search(struct HNode *root, int x);

int H_check(int *a, int value);

void H_PRINT_BST(struct HNode *t);

int H_height(struct HNode *Root);

struct HNode *findMaximum(struct HNode *root);

struct HNode *findPredecessor(struct HNode *root, struct HNode *prec, int key);

#endif