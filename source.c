#include <stdio.h>
#include <math.h>
#define LEFT -1
#define RIGHT 1
#define MIDDLE 0

typedef struct Node {
	char name;
	int x = 0, y = 0, radis = 0, check = 0;
} Node;

Node node[6];

// counter clock wise algorithm
int direct(Node *a, Node *b, Node *c) {
	int ccw = (b->x - a->x) * (c->y - a->y) - (c->x - a->x) * (b->y - a->y);
	if( ccw > 0 )
		return RIGHT;
	else if( ccw < 0 )
		return LEFT;
	else if( ccw == 0 )
		return MIDDLE;
}

void init_radis(Node *a1, int i) {
	if( i > 4)
		return;
	
	double d_vector = atan2(a1[i + 1].y - a1[0].y, a1[i + 1].x - a1[0].x);
	int angle = (d_vector * 180) / M_PI;
	a1[i + 1].radis = angle;

	init_radis(a1, i + 1);
		
}

void sort(Node *a1, int i , int j) {
	if( i > 4)
		return;
		
	if( a1[j].radis < a1[i].radis ) {
		Node temp = a1[j];
		a1[j] =  a1[i];
		a1[i] = temp;
	} 
	
	sort(a1, i + 1, i + 2);
}

int main() {
	node[0].x = 0; node[0].y = 0; node[0].name = 'A';
	node[1].x = 3; node[1].y = 2; node[1].name = 'B';
	node[2].x = 2; node[2].y = 2; node[2].name = 'C';
	node[3].x = 5; node[3].y = 3; node[3].name = 'D';
	node[4].x = 2; node[4].y = 4; node[4].name = 'E';
	node[5].x = 4; node[5].y = 5; node[5].name = 'F';
	
	init_radis(node, 0); 
	sort(node, 1, 2);
	
	for(int i = 0; (i + 2) < 6 - 1; i++) {
		if( direct(&node[i], &node[i + 1], &node[i + 2]) == LEFT) {
			Node temp;
			node[i + 3] = node[i + 4];
			node[i + 4] = temp;
			node[i + 4].check = 1;
		}
		
	}
	
	for(int i = 0; i < 6; i++) {
		if( node[i].check != 1) 
		printf("%c -> ", node[i].name);
	}
	
}
