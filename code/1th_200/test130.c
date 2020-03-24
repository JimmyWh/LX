/*
** 插入到一个有序的单链表,函数的参数是一个指向链表第一个节点的指针以及需要插入的值.
*/
#include <stdlib.h>
#include <stdio.h>
#include "sll_node.h"

#define FALSE 0
#define TRUE  1

int sll_insert(register Node **linkp,int new_value)
{
	register Node *current;
	register Node *new;


	/*
	** 寻找正确的插入位置,方法是按顺序访问链表，直到到达其值大于或者等于
	** 新插入值的节点
	*/
	while ((current = *linkp) != NULL && current->value < new_value)
		linkp = &current->link;
	
	/*
	** 为新节点分配内存,并把新值存储到新节点中,如果内存分配失败.
	** 函数返回FALSE.
	*/
	new = (Node *)malloc(sizeof(Node));
	if (new == NULL)
		return FALSE;
	new->value = new_value;

	/*
	**把新节点插入链表中,并返回TRUE.
	*/
	new->link = current;
	*linkp = new;
	return TRUE;
	
}

int main()
{
	int result = 0;
	char *root = NULL;
	result = sll_insert(&root, 12);

}