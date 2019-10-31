#include "RBT_user.h"
#include "RBT_hotel.h"
#include "graph.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
//typedef enum { false, true } bool;

#define CITY_NUM 100
#define PATH_NUM 300
#define HOTEL_NUM 100
#define USER_NUM 500
#define INF 100000

int checkday(int hour) {
	int day = hour / 24;
	return day;
}

int main() {
	srand(time(NULL));
	int i = 0, j = 0, k = 0;
	TRANSPORT a[CITY_NUM][CITY_NUM] = { 0 };
	char b[CITY_NUM][CITY_NUM] = { 0 };

	for (int i = 0; i < CITY_NUM; i++) {
		for (int j = 0; j < CITY_NUM; j++)
			a[i][j].length = INF;
	}
	while (k < PATH_NUM) {
		i = rand() % CITY_NUM, j = rand() % CITY_NUM;
		if (i != j && b[i][j] != '*' && b[j][i] != '*') {
			///transport 거리생성
			a[i][j].length = rand() % 101 + 50; //50 ~ 150
			a[i][j].fee = rand() % 91 + 10; //10 ~ 100
			a[i][j].path_id = k;
			a[j][i].length = a[i][j].length;
			a[j][i].fee = a[i][j].fee;
			a[j][i].path_id = a[i][j].path_id;
			b[i][j] = '*', b[j][i] = '*';
		}
		else if (b[i][j] == '*' && b[j][i] == '*')
			continue;
		else if (i == j)
			continue;
		k++;
	}

	/*for (int i = 0; i < CITY_NUM; i++) {
	   for (int j = 0; j < CITY_NUM; j++)
		  printf("%d\t ", a[i][j].length);
	   printf("\n");
	}
	printf("\n");*/

	//호텔생성(id, price)
	struct HNode* RBT_hotel[CITY_NUM] = { NULL };
	int hotelPrice;
	int id;
	int check_id[HOTEL_NUM + 1];
	for (i = 0; i < CITY_NUM; i++) {
		for (j = 0; j < HOTEL_NUM + 1; j++)
			check_id[j] = 0;
		for (j = 0; j < HOTEL_NUM; j++) {
			hotelPrice = rand() % 201 + 100; //100 ~ 300
			while (1) {
				id = rand() % HOTEL_NUM + 1;
				if (check_id[id] == 0) {
					check_id[id]++;
					break;
				}
			}
			RBT_hotel[i] = H_RB_INSERT(RBT_hotel[i], hotelPrice, id);
		}
	}

	//유저생성
	struct UNode *RBT_user = { NULL };
	//int check_user_id[USER_NUM + 1] = { 0 };

	Graph g;
	CreateGraph(&g, CITY_NUM);

	//도시 생성 및 연결 
	k = 0;
	for (i = 0; i < CITY_NUM; i++) {
		for (j = i + 1; j < CITY_NUM; j++) {
			if (a[i][j].length != INF && a[j][i].length != INF)
				AddEdge(&g, i, j, a[i][j].path_id, a[i][j].length, a[i][j].fee);
		}
	}

	//PrintGraph(&g);
	//printf("\n");

	for (i = 0; i < CITY_NUM; i++) {
		MakeHotelInfo(g.heads[i], RBT_hotel[i]);
		//printf("HOTEL_CITY[%d]\n", i);
		//H_PRINT_BST(g.heads[i]->hotel);
		//printf("\n");
	}

	//Yes or No 반복 해야 할 부분
	char answer = 'N';
	printf("Welcome to our Happy♡ Short-term travel agent!!! \n\n");
	printf("If you want to travel with our travel agent, press 'Y', or want to quit, press 'N' : ");
	scanf("%c", &answer);
	printf("\n");
	while (answer == 'Y') {
		int start_c, end_c;
		int user_id = 0, my_budget = 0, check_time = 0, hotel_budget = 0, move_budget = 0, total_budget = 0;
		int starthour, startminute = 0, daycount = 0;
		int res_day = 0, res_days = 0;
		int hotel_price;
		int cur_hour = 0, cur_minute = 0;

		//시간 - 거리 비례상수
		int pathtime = 2;

		Time starttime;
		Time endtime;
		Time hoteltime;

		printf("Enter your ID(0 ~ 499) : ");
		scanf("%d", &user_id);
		int searchflag = U_BST_search(RBT_user, user_id);
		while (searchflag == 0) { //1이면 id가 아직 존재하지 않음
			printf("That ID already exists! Try again!\n");
			printf("Enter your ID(0 ~ 499) : ");
			scanf("%d", &user_id);
			searchflag = U_BST_search(RBT_user, user_id);
		}

		printf("Enter your budget(in $) : "); //money that user has
		scanf("%d", &my_budget);
		printf("Enter your travel period(in days) : "); //tour period that user predicts
		scanf("%d", &check_time);
		printf("Enter a point of departure(0 ~ 99) : "); //start city
		scanf("%d", &start_c);
		printf("Enter your destination(0 ~ 99) : "); //end city
		scanf("%d", &end_c);
		printf("Enter your start time(0h ~ 23h) : "); //departure time that user wants
		scanf("%d", &starthour);
		printf("Enter your hotel budget(in $, $100 ~ $300) : "); //available money that user can spend in hotel reservation
		scanf("%d", &hotel_budget);

		//최적의 경로를 찾기 전에 BFS를 통해서 연결이 되어 있는지 아닌지 찾는다
		int connect = BFS(&g, start_c, end_c);
		if (connect == 0) {
			printf("City %d is not connected to city %d.\n", start_c, end_c);
			printf("Choose the another departure or destination, please.\n");
			printf("Do you want to reserve another tour? ('Y'(yes) or 'N'(no)) : ");
			scanf(" %c", &answer);
			if (answer == 'Y')
				continue;
			else if (answer == 'N')
				return 0;
		} //두 도시가 연결되어 있지 않을 때
		//다익스트라 알고리즘
		else if (connect == 1) {
			printf("City %d is connected to city %d.\n", start_c, end_c);
			int min, v, n, m;
			int visit[CITY_NUM] = { 0 };
			int dist[CITY_NUM];

			for (i = 0; i < CITY_NUM; i++)
				dist[i] = INF;

			dist[start_c] = 0;
			for (i = 0; i < CITY_NUM; i++) {
				min = INF;
				for (j = 0; j < CITY_NUM; j++) {
					if (visit[j] == 0 && min > dist[j]) {
						min = dist[j];
						v = j;
					}
				}
				visit[v] = 1;
				for (j = 0; j < CITY_NUM; j++) {
					if (dist[j] > dist[v] + a[v][j].length) {
						dist[j] = dist[v] + a[v][j].length;
						move_budget = a[v][j].fee;
					}
				}
			}
			starttime.hour = starthour;
			starttime.minute = startminute;

			cur_hour = starthour;
			cur_minute = dist[end_c] * pathtime;
			int moving_hour, moving_minute;
			if (cur_minute >= 60) {
				moving_hour = cur_minute / 60;
				moving_minute = cur_minute % 60;
			}
			cur_hour += moving_hour;
			cur_minute = moving_minute;

			int hotelhour, hotelminute;
			if (cur_hour >= 24) {
				daycount += checkday(cur_hour);
				cur_hour = cur_hour % 24;
			}
			res_day = daycount;
			hoteltime.hour = cur_hour;
			hoteltime.minute = cur_minute;

			cur_hour += g.heads[end_c]->path.length + 8;
			cur_minute += moving_minute;
			if (cur_minute >= 60) {
				cur_hour += (cur_minute) / 60;
				cur_minute = cur_minute % 60;
			}
			if (cur_hour >= 24) {
				daycount += checkday(cur_hour);
				cur_hour = cur_hour % 24;
			}
			res_days = daycount - res_day + 1;

			cur_hour += g.heads[end_c]->path.length + 8 * res_days + moving_hour;
			cur_minute += moving_minute;
			if (cur_minute >= 60) {
				cur_hour += (cur_minute) / 60;
				cur_minute = cur_minute % 60;
			}
			if (cur_hour >= 24) {
				daycount += checkday(cur_hour);
				cur_hour = cur_hour % 24;
			}
			endtime.hour = cur_hour;
			endtime.minute = cur_minute;

			struct HNode *prec = NULL;
			struct HNode *predecessor = findPredecessor(g.heads[end_c]->hotel, prec, hotel_budget);
			if (predecessor == NULL) {
				printf("All hotels are more expensive than reservation budget that you plan.\n");
				printf("You have to choose the other destionation city or you need to spend more budget in your hotel reservation.\n");
				printf("\nDo you want to reserve another tour? ('Y'(yes) or 'N'(no)) : ");
				scanf(" %c", &answer);
				if (answer == 'Y')
					continue;
				else if (answer == 'N')
					return;
			}
			else {
				hotel_price = predecessor->price;
				printf("mb - %d$, hp - %d$, mh - %dhour(s), rds - %dday(s)\n", move_budget, hotel_price, moving_hour, res_days);
				total_budget = (2 * move_budget) + (hotel_price * res_days);

				printf("\n< Your itinerary plan from %d-city to %d-city > will be \n\n", start_c, end_c);
				printf("--------------------------------------------------------------------\n");
				printf("You want to start a trip at %d : %d.\n", starttime.hour, starttime.minute);
				printf("Hotel reservation is available from <day %d, %d : %d.>\n", res_day, hoteltime.hour, hoteltime.minute);
				printf("Hotel price that is best suitable for you is %d$.\n", hotel_price);
				printf("Tour is scheduleded to finish at %d : %d after %d day(s).\n", endtime.hour, endtime.minute, daycount);
				printf("The estimated budget of your trip is %d$.\n", total_budget);
				printf("--------------------------------------------------------------------\n");

				//check
				if (total_budget > my_budget || daycount >= check_time) {
					if (total_budget > my_budget)
						printf("But you need %d$ more at least... :(\n", total_budget - my_budget);
					if (daycount >= check_time)
						printf("But you need %d day(s) more at least... :(\n", daycount - check_time);
				}
				else {
					RBT_user = U_RB_INSERT(RBT_user, user_id, starttime, endtime, hoteltime, total_budget, daycount, my_budget - total_budget);
					printf("Reservation complete! Have a good trip! :)\n");
				}
				printf("\nDo you want to reserve another tour? ('Y'(yes) or 'N'(no)) : ");
				scanf(" %c", &answer);
			}
		} //두 도시가 연결되어 있을 때
	} //가장 큰 while문, 계속 여행을 알아보고 싶을 때
	DestroyGraph(&g);
}