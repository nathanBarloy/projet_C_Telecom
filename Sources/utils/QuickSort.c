#include "QuickSort.h"

Vector_t quick_sort(Vector_t list)
{
	Vector_t init = newVectorFromVector(list);
	int size = sizeOfVector(init);
	//printf("%d\n", size);
	if(size <= 1)
	{
		return init;
	}
	else
	{
		//centre
		Vector_t c = newVector();
		double center_value = JSONObject_doubleValueOf(getFromVector(init, 0), autoString("Moyenne"));
		addToVector(c, getFromVector(init, 0));
		eraseOnVector(c, 0);

		Vector_t g = newVector();
		Vector_t d = newVector();

		while(sizeOfVector(init) != 0)
		{
			double current_value = JSONObject_doubleValueOf(getFromVector(init, 0), autoString("Moyenne"));
			if(current_value > center_value)
			{
				addToVector(d, getFromVector(init, 0));
				eraseOnVector(init, 0);
			}
			else if(current_value < center_value)
			{
				addToVector(g, getFromVector(init, 0));
				eraseOnVector(init, 0);
			}
			else
			{
				addToVector(c, getFromVector(init, 0));
				eraseOnVector(init, 0);
			}
		}

		//recursivité sur les membres droit et gauche
		Vector_t newG = quick_sort(g);
		Vector_t newD = quick_sort(d);

		freeVector(d);
		freeVector(g);
		Vector_t r = merge_quick(newG, c, newD);
		freeVector(init);
		return r;
	}
}

Vector_t merge_quick(Vector_t g, Vector_t c, Vector_t d)
{
	Vector_t result = newVectorFromVector(g);
	appendVectorToVector(result, c);
	appendVectorToVector(result, d);
	return result;
}
