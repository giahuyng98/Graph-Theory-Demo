#ifndef  _node_hpp_
#define _node_hpp_

struct node
{
	int value;
	node *next;
	node(int v) : value(v), next(NULL){}
};
//node* createNode(int const &value)
//{
//	node *n = new node;
//	n->value = value;
//	return n;
//}
#endif
