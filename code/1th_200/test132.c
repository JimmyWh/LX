/*
** 把一个值插入到一个双链表，rootp是一个指向根节点的指针.
** value是欲插入的新值.
** 返回值:如果欲插入值原先已经存在于链表中，函数返回0
** 如果内存不足导致无法插入,函数返回-1;如果插入成功,函数返回1
*/

#include <stdlib.h>
#include <stdio.h>
#include "doubly_linked_list_node.h"

int dll_insert(Node *rootp,int value)
{
	Node *this;
	Node *next;
	Node *newnode;

	/*
	** 查看value是否已经存在于链表中，如果是就返回.
	** 否则为新值创建一个新节点("newnode"将指向它)
	** "this"将指向应该在新节点之前的那个节点,
	** "next"将指向应该在新节点之后的那个节点.
	*/

	for (this = rootp;(next = this->fwd) != NULL;this = next)
	{
		if (next->value == value)
			return 0;
		if (next->value > value)
			break;
	}

	newnode = (Node *)malloc(sizeof(Node));
	if (newnode == NULL)
		return -1;
	newnode->value = value;

	/*
	** 把新值添加到链表中.
	*/
	if (next != NULL)
	{
		/*
		** 情况1或者2:并非位于链表尾部.
		*/

		if (this != rootp) //情况1：并非位于链表起始位置.
		{
			newnode->fwd = next;
			this->fwd = newnode;
			newnode->bwd = this;
			next->bwd = newnode;
		}
		else    //情况2:位于链表的起始位置.
		{
			newnode->fwd = next;
			rootp->fwd = newnode;
			newnode->bwd = NULL;
			next->bwd = newnode;
		}
	}
	else
	{
		/*
		** 情况3或者情况4:位于链表的尾部
		*/

		if (this != rootp) //情况3:并非位于链表的起始位置.
		{
			newnode->fwd = NULL;
			this->fwd    = newnode;
			newnode->bwd = this;
			rootp->bwd = newnode;
		}
		else            //情况4:位于链表的起始位置.
		{
			newnode->fwd = NULL;
			rootp->fwd = newnode;
			newnode->bwd = NULL;
			rootp->bwd = newnode;
		}
	}
	return 1;
}


