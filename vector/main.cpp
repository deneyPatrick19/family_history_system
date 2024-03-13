#include <iostream>
#include "vector.h"

/* run this program using the console pauser or add your own getch, system("pause") or input loop */

int main(int argc, char** argv) {
	Vector* v=new_vector();
	T stud[3]={{"xia","082219"},{"chen","082220"},{"wu","082250"}};
	for(int i=0;i<3;i++)
	{
		vector_push_back(v,&stud[i]);
	}
	for(int i=0;i<3;i++)
	{
		printf("%s %s ",v->elements[i].name,v->elements[i].number);
	}
	student s={"li","082227"};
	Vector_insert(v,&s,2);
	printf("\n");
	for(int i=0;i<4;i++)
	{
		printf("%s %s ",v->elements[i].name,v->elements[i].number);
	}
	printf("\n");
	return 0;
}