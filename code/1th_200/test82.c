

void clear_array(int array[],int n_elements)
{
	/*
	** 从数组最后一个元素开始，逐个清楚数组中的所有元素，注意前缀自增避免了越出数组边界的可能性
	*/

	while (n_elements > 0)
		array[--n_elements] = 0;

}

