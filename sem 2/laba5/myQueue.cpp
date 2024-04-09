#include "myQueue.h"

void create(myQueue& q, tree* ver)
{
	q.begin = q.end = new node;
	q.begin->ver = ver;
	q.begin->next = q.begin->prev = nullptr;
}

void pushEnd(myQueue& q, tree* ver)
{
	node* newNode = new node;

	newNode->ver = ver;
	newNode->next = nullptr;
	newNode->prev = q.end;

	q.end->next = newNode;
	q.end = newNode;
}

void delBeg(myQueue& q)
{
	if (q.begin->next)
		q.begin->next->prev = nullptr;
	
	node* rem = q.begin;
	q.begin = q.begin->next;

	delete rem;
}

void del(myQueue& q)
{
	node* rem;
	node* cur = q.begin;

	while (cur)
	{
		rem = cur;
		cur = cur->next;
		delete rem;
	}

	q.begin = q.end = nullptr;
}