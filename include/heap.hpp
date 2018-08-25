#ifndef _heap_hpp_
#define _heap_hpp_
#include <stddef.h>

struct heap
{
	struct node
	{
		int value;
		node *left;
		node *right;
		node() : left(NULL), right(NULL) {}
	};
	
	
	heap() : root(NULL) {}
	void insert(int value)
	{
		
	}
	
private:
	node *root;
};

#endif
