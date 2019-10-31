# ifndef RBTUSER_H
# define RBTUSER_H

#include <stdio.h>
#include <stdlib.h>

enum type { RED, BLACK };
//typedef int bool;
#define true 1
#define false 0
#define color(a) (((a)==0)?(a = 'R'):(a ='B')) // used in print node color
#define MAX(a,b) (((a)>(b))?(a):(b)) //used in height func
typedef struct _time {
	int hour;
	int minute;
} Time;

struct UNode {
	int id;
	Time start_time;
	Time end_time;
	Time hotel_res_time;
	int budget; //총예산
	int stay_day; //일수
	int fee; //관광비

	struct UNode *left;
	struct UNode *right;
	struct UNode *parent;
	enum type color;
} UNode; //for RBT

void U_LeftRotate(struct UNode **T, struct UNode **x);

void U_RightRotate(struct UNode **T, struct UNode **x);

void U_RB_INSERT_fixup(struct UNode **T, struct UNode **z);

struct UNode *U_RB_INSERT(struct UNode *T, int id, Time starttime, Time endtime, Time restime, int budget, int stay_day, int fee);
//함수 바꾸기**
struct UNode *U_Tree_minimum(struct UNode *node);

void U_RB_delete_fixup(struct UNode **T, struct UNode **x);

void U_RB_transplat(struct UNode **T, struct UNode **u, struct UNode **v);

struct UNode *U_RB_DELETE(struct UNode *T, struct UNode *z);

int U_BST_search(struct UNode *root, int x);

int U_check(int *a, int value);

void U_PRINT_BST(struct UNode *t);

int U_height(struct UNode *Root);

#endif