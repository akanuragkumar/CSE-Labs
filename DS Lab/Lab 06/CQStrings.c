//
//  CircularQueue.c
//  Circular Queue of Strings.
//
//  Created by Avikant Saini on 9/06/15.
//  Copyright © 2015 avikantz. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 10
#define UNDERFLOW_CHAR '\0'

/// Boolean type, just for readability

typedef enum {
	NO = 0,
	YES = 1,
} BOOL;

typedef struct CircularQueue {
	char ** arr;
	int front;
	int rear;
} CQUEUE_t;

/// CQUEUE_t pointer type @line You might as well use CQUEUE_t *

typedef CQUEUE_t * CQUEUE_p_t;

// Queue methods

BOOL isFullQueue (CQUEUE_p_t queue) {
	if ((queue->rear + 1)%SIZE == queue->front)
		return YES;
	return NO;
}

BOOL isEmptyQueue (CQUEUE_t queue) {
	if (queue.front == -1)
		return YES;
	return NO;
}

void insert (CQUEUE_p_t queue, char * item) {
	if (isFullQueue(queue)) {
		printf("\nQueue Overflow!\n\n");
		return;
	}
	
	if (isEmptyQueue(*queue))
		queue->front = queue->rear = 0;
	else
		queue->rear = (queue->rear + 1)%SIZE;
	
	*(queue->arr + queue->rear) = item;
}

char * delete (CQUEUE_p_t queue) {
	if (isEmptyQueue(*queue)) {
		printf("\nQueue Underflow!\n\n");
		return UNDERFLOW_CHAR;
	}
	
	char * item = *(queue->arr + queue->front);
	
	if (queue->front == queue->rear)
		queue->front = queue->rear = -1;
	else
		queue->front = (queue->front + 1)%SIZE;
	
	return item;
}

void display (CQUEUE_t queue) {
	if (isEmptyQueue(queue))
		printf("\nEmpty Queue.\n");
	else {
		printf("\nCurrent Queue : ");
		int i;
		for (i = queue.front; i != queue.rear; i = (i+1)%SIZE)
			printf("\t%s", *(queue.arr + i));
		printf("\t%s\n", *(queue.arr + i));
	}
}


int main(int argc, const char * argv[]) {
	
	CQUEUE_p_t queue = (CQUEUE_p_t)calloc(SIZE, sizeof(CQUEUE_t));
	queue->arr = (char **)calloc(SIZE, sizeof(char *));
	queue->front = -1;
	queue->rear = -1;
	
	char choice;
	
	do {
		printf("\n\t1. Insert\n\t2. Delete\n\t3. Display Queue.\n\tQ. Quit\nEnter Choice : ");
		scanf(" %c", &choice);
		
		char * item = (char *)calloc(SIZE, sizeof(char));
		
		if (choice == '1') {
			printf("\tEnter item to be inserted: ");
			scanf("%s", item);
			insert(queue, item);
		}
		else if (choice == '2') {
			item = delete(queue);
			if (item != UNDERFLOW_CHAR)
				printf("\tDeleted item: %s\n", item);
		}
		
		display(*queue);
		
	} while (choice == '1' || choice == '2' || choice == '3');
	
	return 0;
}
