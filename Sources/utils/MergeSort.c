#include "MergeSort.h"

Vector_t fromArrayToVector(JSONArray_t list)
{
	Vector_t Vlist = newVector();
	int i;
	for(i=0 ; i<JSONArray_size(list) ; i++)
	{
		addToVector(Vlist, JSONArray_get(list, i));
	}
	return Vlist;
}

JSONArray_t fromVectorToArray(Vector_t v)
{
	JSONArray_t a = JSONArray_new();
	int i = 0;
	while( i < sizeOfVector(v))
	{
		JSONArray_add(a, getFromVector(v, i));
		i++;
	}
	return a;
}

Vector_t merge_sort(Vector_t list)
{
	Vector_t a = newVectorFromVector(list);
	int size = sizeOfVector(a);
	printf("%d\n", size);
	if(size == 1)
	{
		return a;
	}
	else
	{
		//seconde moitié
		Vector_t l2 = splitVector(a, (int)(size/2));
		//premiere moitié
		Vector_t l1 = a;

		Vector_t a1 = merge_sort(l1);
		Vector_t a2 = merge_sort(l2);

		freeVector(l1);
		freeVector(l2);
		return merge(a1, a2);
	}
}
Vector_t merge(Vector_t list1, Vector_t list2)
{
	Vector_t sorted_vector = newVector();
	while((int)sizeOfVector(list1) > 0 && (int)sizeOfVector(list2) > 0)
	{
		printf("TEST\n");
		printf("list1 : %d\nlist2 : %d\n", (int)sizeOfVector(list1), (int)sizeOfVector(list2));
		double rate1 = JSONObject_intValueOf(getFromVector(list1, 0),autoString("Moyenne"));
		double rate2 = JSONObject_intValueOf(getFromVector(list2, 0),autoString("Moyenne"));
		if(rate1 > rate2)
		{
			addToVector(sorted_vector, getFromVector(list2, 0));
			eraseOnVector(list2, 0);
		}
		else
		{
			addToVector(sorted_vector, getFromVector(list1, 0));
			eraseOnVector(list1, 0);
		}
	}

	while(sizeOfVector(list1) > 0)
	{
		addToVector(sorted_vector, getFromVector(list1, 0));
		eraseOnVector(list1, 0);
	}

	while(sizeOfVector(list2) > 0)
	{
		addToVector(sorted_vector, getFromVector(list2, 0));
		eraseOnVector(list2, 0);
	}

	return sorted_vector;
}
