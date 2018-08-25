#ifndef _queue_hpp_
#define _queue_hpp_
#include "node.hpp"
#include <limits.h>
#include <stddef.h>

struct queue
{
	queue()
	{
		front = NULL;
		rear = NULL;
	}
	bool isEmpty() const
	{
		return (front == NULL);
	}
	void push(int value)
	{
		node *n = new node(value); //createNode(value);
		if (front == NULL)
			front = rear = n;
		else
		{
			rear->next = n;
			rear = n;
		}
	}
	int pop()
	{
		if (front == NULL) return INT_MIN;
		node *tmp = front;
		int res = front->value;
		front = front->next;
		delete tmp;
		return res;
	}
	~queue()
	{
		node *tmp;
		while (front != NULL)
		{
			tmp = front;
			front = front->next;
			delete tmp;
		}
	}
private:
	node *front;
	node *rear;
};
#endif
