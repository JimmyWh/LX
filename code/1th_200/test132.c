/*
** ��һ��ֵ���뵽һ��˫����rootp��һ��ָ����ڵ��ָ��.
** value�����������ֵ.
** ����ֵ:���������ֵԭ���Ѿ������������У���������0
** ����ڴ治�㵼���޷�����,��������-1;�������ɹ�,��������1
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
	** �鿴value�Ƿ��Ѿ������������У�����Ǿͷ���.
	** ����Ϊ��ֵ����һ���½ڵ�("newnode"��ָ����)
	** "this"��ָ��Ӧ�����½ڵ�֮ǰ���Ǹ��ڵ�,
	** "next"��ָ��Ӧ�����½ڵ�֮����Ǹ��ڵ�.
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
	** ����ֵ��ӵ�������.
	*/
	if (next != NULL)
	{
		/*
		** ���1����2:����λ������β��.
		*/

		if (this != rootp) //���1������λ��������ʼλ��.
		{
			newnode->fwd = next;
			this->fwd = newnode;
			newnode->bwd = this;
			next->bwd = newnode;
		}
		else    //���2:λ���������ʼλ��.
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
		** ���3�������4:λ�������β��
		*/

		if (this != rootp) //���3:����λ���������ʼλ��.
		{
			newnode->fwd = NULL;
			this->fwd    = newnode;
			newnode->bwd = this;
			rootp->bwd = newnode;
		}
		else            //���4:λ���������ʼλ��.
		{
			newnode->fwd = NULL;
			rootp->fwd = newnode;
			newnode->bwd = NULL;
			rootp->bwd = newnode;
		}
	}
	return 1;
}


