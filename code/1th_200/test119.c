#include <stdlib.h>
#include <stdio.h>
#include "inventor.h"

Invrec *create_subassy_record(int n_parts)
{
	Invrec *new_rec;

	/*
	** 试图为Invrec部分分配内存.
	*/

	new_rec = malloc(sizeof(Invrec));
	if (new_rec != NULL)
	{
		/*
		** 内存分配成功,现在存储SUBASSYINFO部分
		*/
		new_rec->info.subassy = malloc(sizeof(Subassyinfo));
		if (new_rec->info.subassy != NULL)
		{
			/*
			** 为零件获取一个足够大的数组.
			*/
			new_rec->info.subassy = malloc(n_parts * sizeof(struct SUBASSYPART));
			if (new_rec->info.subassy->part != NULL)
			{
				/*
				**获取内存，填充我们已知道的字段，然后返回.
				*/
				new_rec->type = SUBASSY;
				new_rec->info.subassy->n_parts = n_parts;
				return new_rec;
			}

			/*
			**内存已用完,释放我们原先分配的内存.
			*/
			free(new_rec->info.subassy);
		}
		free(new_rec);
	}
	return NULL;

}

