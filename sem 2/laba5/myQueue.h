#pragma once

struct person
{
	char name[256];
	char pass[256];
};

struct tree
{
	int key;
	tree* left;
	tree* right;
	person info;
};

struct node
{
	tree* ver;
	node* next;
	node* prev;
};

struct myQueue
{
	node* begin;
	node* end;
};

void create(myQueue& q, tree* ver);

void pushEnd(myQueue& q, tree* ver);

void delBeg(myQueue& q);

void del(myQueue& q);
