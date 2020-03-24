
/*
** ��һ���������в���һ��ָ��ֵ�ĺ��������Ĳ�����һ��ָ�������һ���ڵ��
** ָ��,һ��ָ��������Ҫ���ҵ�ֵ��ָ���һ������ָ�룬����ָ��ĺ������ڱȽ�
** �洢�������е����͵�ֵ.
*/

#include <stdio.h>
#include "node.h"

int compare_ints(void const *a,void const *b)
{
	if (*(int *)a == *(int *)b )
		return 0;
	else
		return 1;
}


Node *search_list(Node *node,void const *value,int (*compare)(void const *,void const *))
{
	while (node != NULL)
	{
		if (compare(&node->value,value) == 0)
			break;
		node = node->link;
	}
	return node;

}
