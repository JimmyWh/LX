/*
** ���뵽һ������ĵ�����,�����Ĳ�����һ��ָ�������һ���ڵ��ָ���Լ���Ҫ�����ֵ.
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
	** Ѱ����ȷ�Ĳ���λ��,�����ǰ�˳���������ֱ��������ֵ���ڻ��ߵ���
	** �²���ֵ�Ľڵ�
	*/
	while ((current = *linkp) != NULL && current->value < new_value)
		linkp = &current->link;
	
	/*
	** Ϊ�½ڵ�����ڴ�,������ֵ�洢���½ڵ���,����ڴ����ʧ��.
	** ��������FALSE.
	*/
	new = (Node *)malloc(sizeof(Node));
	if (new == NULL)
		return FALSE;
	new->value = new_value;

	/*
	**���½ڵ����������,������TRUE.
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