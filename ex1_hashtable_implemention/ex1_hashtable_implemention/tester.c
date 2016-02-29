






#include "GenericHashTable.h"

int main(){

	Table* table;
	table=createTable(5,INT_TYPE,3);
	int i=0;
	int arr[40];

	arr[0]=5;
	arr[1]=6;
	arr[2]=7;
	arr[3]=8;
	arr[4]=9;
	arr[5]=10;
	arr[6]=15;
	arr[7]=20;
	arr[8]=11;
	arr[9]=16;
	arr[10]=21;
	arr[11]=26;
	arr[12]=25;
	arr[13]=30;
	arr[14]=14;
	arr[15]=19;
	arr[16]=24;
	arr[17]=29;
	arr[18]=34;
	arr[19]=35;
	arr[20]=40;
	arr[21]=45;
	arr[22]=50;
	arr[23]=55;
	arr[24]=60;
	arr[25]=31;
	arr[26]=36;
	arr[27]=41;
	arr[28]=46;
	arr[29]=51;
	arr[30]=56;
	arr[31]=61;
	arr[32]=39;
	arr[33]=44;
	arr[34]=49;
	arr[35]=54;
	arr[36]=59;
	arr[37]=64;
	arr[38]=69;
	arr[39]=12;

	for(i=0;i<40;i++){
		add(table,&arr[i]);
	}





	printTable(table);

	freeTable(table);
printf("%d",*(int*)table->arr[5]->data);




	return 0;
}



//	Object* obj=search(table,arr[17]);
//	printf("%d",*((int*)obj->data));


/*
 	void** arr[40];
	int i=0;
	for(i=0;i<40;i++)
		arr[i]=malloc(sizeof(char*));
 *arr[0]="a";
 *arr[1]="b";
 *arr[2]="c";
 *arr[3]="d";
 *arr[4]="e";
 *arr[5]="f";
//   *arr[0]="g";
 *arr[6]="k";
//   *arr[0]="i";
 *arr[7]="p";
//   *arr[0]="k";
//   *arr[0]="l";*/


/*	int i=0;
	int** arr[40];
	for(i=0;i<40;i++)
		arr[i]=malloc(sizeof(int*));


 *arr[0]=5;
 *arr[1]=6;
 *arr[2]=7;
 *arr[3]=8;
 *arr[4]=9;
 *arr[5]=10;
 *arr[6]=15;
 *arr[7]=20;
 *arr[8]=11;
 *arr[9]=16;
 *arr[10]=21;
 *arr[11]=26;
 *arr[12]=25;
//	*arr[13]=30;
//   *arr[14]=14;
//	*arr[15]=19;
//	*arr[16]=24;
//   *arr[17]=29;
//   *arr[18]=34;
//  *arr[19]=35;
//	*arr[20]=31;
//	*arr[21]=36;
//	*arr[22]=41;
//	*arr[23]=46;
//	*arr[24]=51;
//	*arr[25]=56;
//    *arr[26]=61;
//	*arr[27]=66;
//	*arr[28]=79;
 *
 */










/*
int* x=malloc(sizeof(int));
int* y=malloc(sizeof(int));
int* z=malloc(sizeof(int));
 *x=5;
 *y=6;
 *z=7;
Object* obj1=createObject(x,0);
Object* obj2=createObject(y,0);
Object* obj3=createObject(z,0);
obj1->data=x;
obj1->next=obj2;
obj2->data=y;
obj2->next=obj3;
obj3->data=z;
printf("%d\n",*((int*)obj1->data));
printf("%d\n",*((int*)obj2->data));
printf("%d\n",*((int*)obj3->data));
 *(int*)obj1->data=*(int*)obj2->data;
obj1->next=obj2->next;
freeObject(obj2,0);
printf("%d\n",*((int*)obj1->data));
printf("%d\n",*((int*)obj2->data));
printf("%d\n",*((int*)obj3->data));
printf("%d\n",*((int*)obj1->next->data));
 */








/*
	int* x=malloc(sizeof(int));
	int* y=malloc(sizeof(int));
	int* z=malloc(sizeof(int));
 *x=5;
 *y=6;
 *z=7;
	Object* obj1=malloc(sizeof(Object));
	Object* obj2=malloc(sizeof(Object));
	Object* obj3=malloc(sizeof(Object));
	obj1->data=x;
	obj1->next=obj2;
	obj2->data=y;
//	obj2->next=obj3;
//	obj3->data=z;
table->arr[1]->next=obj1;

	printTable(table);

	printf("%d\n",checkSpaceInNextIndex(table,4));
 */
/*
	int add(Table* table, void* data)
	{
		int index;
		Object* p;
		Object* ptr;
		Object* obj=createObject(data,table->dtype);

		if (table->dtype==INT_TYPE)
		{
			obj->data=(int*)malloc(sizeof(int));
 *(int*)obj->data=*(int*)data;
			index=intHashFun(data,table->size_arr);
        }
		if(table->arr[index]==NULL)
			{
			table->arr[index]=obj;
				return index;
			}
			else{
		    for(ptr=table->arr[index];ptr->next!=NULL;ptr=ptr->next);
			ptr->next=obj;
			}


	}

 */


/*

if(table->dimention==1){

}
	i=0;
	Object* ptr;
	Table* newTable=createTable(table->tableOriginalSize*2,table->dataType,table->maxListLength);
	newTable->dimention= table->dimention*2;
	newTable->size=newTable->tableOriginalSize/newTable->dimention;
	while(i<table->tableOriginalSize){
		ptr=table->arr[i];
		while(ptr!=NULL){
			add(newTable,ptr->data);
			ptr=ptr->next;
		}
		i++;
	}
	freeTable(table);
	table=newTable;
	printTable(table);






 */


/*
int* x=malloc(sizeof(int));
int* y=malloc(sizeof(int));
 *x=5;
 *y=6;
printf("%d\n",*x);
free(x);
printf("%d\n",*x);
x=y;
printf("%d\n",*x);
 */







/*
printf("%d\n",removeObj(t,&a));
printf("%d\n",removeObj(t,&b));
printf("%d\n",removeObj(t,&g));
 */

/*
char* x=malloc(5);
 i=0;
for(i=0;i<5;i++){
	x[i]='g';
}
printf("%s\n",x);
 */


/*
int* x=malloc(sizeof(int));
int* y=malloc(sizeof(int));
int* z=malloc(sizeof(int));
 *x=5;
 *y=6;
 *z=7;
Object* obj1=malloc(sizeof(Object));
Object* obj2=malloc(sizeof(Object));
Object* obj3=malloc(sizeof(Object));
obj1->data=x;
obj1->next=obj2;
obj2->data=y;
obj2->next=obj3;
obj3->data=z;
//this means obj1->obj2->obj3
printf("%d\n",*((int*)obj1->data));
printf("%d\n",*((int*)obj2->data));
printf("%d\n",*((int*)obj3->data));
freeObject(obj1,INT_TYPE);
printf("%d\n",*((int*)obj1->data));
printf("%d\n",*((int*)obj2->data));
printf("%d\n",*((int*)obj3->data));
 */


/*
int* x=malloc(sizeof(int));
 *x=5;
free(x);
x=&a;
printf("%d\n",*x);
 */





/*printf("\n");
if(search(t,&h)==NULL){
	printf("NULL\n");
}else{
printf("%d\n",*((int*)(search(t,&h)->data)));
}
 */

/*
//main to check isEqual func
int main(){

	//checking the str
	void* x;
	void* y;
	char* w=malloc(5*sizeof(char));
	char* z=malloc(5*sizeof(char));
	int i=0;
	for(i=0;i<4;i++){
		w[i]='t';
		z[i]='y';
	}
	w[4]='\0';
	z[4]='\0';
	prtArr(w,5);
	prtArr(z,5);
	x=w;
	y=z;
	prtArr((char*)x,5);
	prtArr((char*)y,5);
printf("%d\n",isEqual(STR_TYPE,x,y));


//checking the int

void* a;
void* b;
int c=5;
int d=6;

a=&c;
b=&d;
printf("%d\n",isEqual(INT_TYPE,a,b));






	return 0;

}
 */

