#include "test86.h"
#include <stdio.h>

/*
** ÿ����ַ���������֣��ֱ𱣴�����������Ķ�ӦԪ����.
*/

static char name[MAX_ADDRESSES][NAME_LENGTH];
static char address[MAX_ADDRESSES][ADDR_LENGTH];
static char phone[MAX_ADDRESSES][PHONE_LENGTH];

/*
** ��������������в���һ�����ֲ����ز��ҵ���λ�õ��±�
** �����������������в������ڣ���������-1
*/

static int find_entry(char const *name_to_find)
{
	int entry;

	for (entry =0; entry < MAX_ADDRESSES;entry += 1)
		if (strcmp(name_to_find,name[entry]) == 0)
			return entry;

		return -1;

}

/*
** ����һ�����֣����Ҳ����ض�Ӧ�ĵ�ַ.
** �������û���ҵ�����������һ��NULLָ��.
*/

char const *lookup_address(char const * name)
{
	int entry;
	entry = find_entry(name);
	if (entry == -1)
		return NULL;
	else
		return address[entry];

}

/*
** ����һ�����֣����Ҳ����ض�Ӧ�ĵ绰����.
** �������û���ҵ�����������һ��NULLָ��
*/

char const *lookup_phone(char const * name)
{
	int entry;

	entry = find_entry(name);
	if (entry == -1)
		return NULL;
	else
		return phone[entry];
}


