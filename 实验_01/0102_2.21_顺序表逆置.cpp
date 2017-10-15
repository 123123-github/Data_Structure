#include "List_Sq.h"

void Reverse_Sq(SqList &L)
{
	if (L.length <= 0)
		return OK;

	int i, j, t;
	i = 1;
	j = L.length;

	while (i < j)
	{
		t = L.elem[i - 1];
		L.elem[i - 1] = L.elem[j - 1];
		L.elem[j - 1] = t;

		i++;
		j--;
	}
	return OK;
}