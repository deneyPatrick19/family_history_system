#include <stdlib.h>
#include<stdbool.h>
#include "vector.h"

Vector *new_vector()
{
    Vector *newVector = (Vector*)malloc(sizeof(Vector));
    newVector->elements = (T*)calloc(initcpacity, sizeof(T));
    newVector->capacity = initcpacity;
    newVector->size = initSize;
    
    return newVector;
}

void vector_push_back(Vector *v, const T *t)
{
	if((v->size)+1 > (v->capacity))
	{
		T *formerV = v->elements;
		v->capacity = 2*v->capacity;
		v->elements = (T*)calloc(2*v->capacity, sizeof(T));
		for(int i=0;i<v->size;i++)
		{
			v->elements[i]= formerV[i];
		}
		free(formerV);
	}

	v->elements[v->size++] = *t;		

}

T vector_pop_back(Vector *v)
{
	T num=v->elements[v->size-1];
	v->size--;
    if((v->size)<(v->capacity)/4)
    {
    	T *formerV = v->elements;
    	v->capacity =v->capacity/2;
    	v->elements =(T*)calloc(v->capacity, sizeof(T));
    	for(int i=0;i<v->size;i++)
    	{
    		v->elements[i]= formerV[i];
		}
		free(formerV);
	}
	return num;
}

bool Vector_at(Vector *v, T *ret, int i)
{
	if(i<v->size&&i>=0)
	{
		*ret=v->elements[i];
		return true;
	}
	else
	{
		ret=NULL;
		return false;
	}
}

void Vector_insert(Vector *v, const T *t,int i)
{
	int m;
	if((v->size)+1 > (v->capacity))
	{
		T *formerV = v->elements;
		v->capacity = 2*v->capacity;
		v->elements = (T*)calloc(2*v->capacity, sizeof(T));
		for(int i=0;i<v->size;i++)
		{
			v->elements[i]= formerV[i];
		}
		free(formerV);
	}
	for(m=(v->size)-1;m>=i-1;m--)
	{
		v->elements[m+1]=v->elements[m];
	}
	v->elements[i-1] = *t;
	v->size++;
}
void Vector_delete(Vector *v, const T *t)
{
	int i,m;
	if((v->size)-1<(v->capacity)/4)
    {
    	T *formerV = v->elements;
    	v->capacity =v->capacity/2;
    	v->elements =(T*)calloc(v->capacity, sizeof(T));
    	for(int i=0;i<v->size;i++)
    	{
    		v->elements[i]= formerV[i];
		}
		free(formerV);
	}
	for(i=0;i<v->size;i++)
	{
		if(strcmp(v->elements[i].name,t->name)==0&&strcmp(v->elements[i].number,t->number)==0)
		{
			m=i;
			for(m=i;m<v->size;m++)
			{
				v->elements[m]=v->elements[m+1];
			}
		}
	}
	v->size--;
}
