/*
 * genericHashTable.c
 *
 *  Created on: Nov 9, 2014
 *      Author:Netanel Gabay
 *      ID:303095228
 */
#include "GenericHashTable.h"

/**
 * this functions creates new Table and initialize all table properties
 *the table is an array of Object* which every cell is the the first element in the linked list
 *which corresponds to the matching index
 */
//-----^^^^^^^^^--------^^^^^^^$$$$$$$########@@@@@@@@!!!!!!!!!!!!!!!!!!!!!!!
Table* createTable(int size, int dType, int listLength){
	if(size<=0 ||listLength<=0){
		printf("illegal size\n");
		return NULL;
	}

	Table* newTable=(Table*)malloc(sizeof(Table));
	if(newTable==NULL)
		return NULL;
	newTable->arr=(Object**)calloc(size,sizeof(Object*));
	if(newTable->arr==NULL)
		return NULL;

	newTable->dataType=dType;
	newTable->tableOriginalSize=size;
	newTable->dimention=1;
	newTable->maxListLength=listLength;
	newTable->size=size;
	return newTable;
}






//-----^^^^^^^^^--------^^^^^^^$$$$$$$########@@@@@@@@!!!!!!!!!!!!!!!!!!!!!!!
// this function adds new element to the table
int add(Table* table, void* data){
	Object* newObj=createObject(data,table->dataType);
	if(newObj==NULL)
		return -1;
	int typeOfData=table->dataType;
	int index=0;
	Object* ptr=NULL;
	//getting the right index

	if(typeOfData==INT_TYPE)
		index=table->dimention*intHashFun( ((int*)data),table->tableOriginalSize);
	else
		index=table->dimention*strHashFun( ((char*)data) ,table->tableOriginalSize);

	ptr=table->arr[index];
	if(ptr==NULL){//if the first cell is empty
		table->arr[index]=newObj;
	}
	else{//if the first cell is'nt empty,therefore it will advance forward to the next element in the
		//linked list

		while(ptr->next!=NULL){
			//checking for collisions
			if(checkListLength(table->maxListLength,table->arr[index])==-1){//means that
				//the linked list in current index has reached it's max length
				//printf("illegal length on:%d\n",*((int*)newObj->data));
				index=correctTable(table,newObj,index);
				return index;
			}

			ptr=ptr->next;
		}


		ptr->next=newObj;
	}


	return index;
}







//-----^^^^^^^^^--------^^^^^^^$$$$$$$########@@@@@@@@!!!!!!!!!!!!!!!!!!!!!!!
//this function deals with length overflows
//there are 3 options to deals with length overflows:
//(1):the table d is 1 and in one of the cells there is linked list that has reached it's list therefore multiply
//(2):the table d>1(the table has been multiplied) and the new allocated cells for this index
//are occupied,therefore multiply
//(3):the table d>1 and the new allocated cells for this index are not occupied,therefore it will search for the
//nearest cell.
int correctTable(Table* table,Object* obj,int index){

	int nextFreeIndex= checkSpaceInNextIndex(table,index);

	if(table->dimention==1)
		return duplicate(table,obj,index);
	else if(nextFreeIndex==-1)
		return duplicate(table,obj,index);
	else{
		if(table->arr[nextFreeIndex]==NULL){
			table->arr[nextFreeIndex]=obj;
			return nextFreeIndex;
		}

		Object* ptr=NULL;
		ptr=table->arr[nextFreeIndex];
		while(ptr->next!=NULL){
			ptr=ptr->next;
		}
		ptr->next=obj;

	}
	return nextFreeIndex;

}






//-----^^^^^^^^^--------^^^^^^^$$$$$$$########@@@@@@@@!!!!!!!!!!!!!!!!!!!!!!!
//this function duplicates the table.
//the function doubles the size of the table
//and moving each entry to the index: index*2,and then adding the new object
int duplicate(Table* table,Object* obj,int index){

	table->arr=(Object**)realloc(table->arr,table->size*2*sizeof(Object*));
	//setting to NULL all the new cells
	int k=0;
	for(k=table->size;k<table->size*2;k++)
		table->arr[k]=NULL;


	table->size*=2;
	int i=(table->size/2)-1;
	Object* tmp=NULL;
	while(i>0){//iterating for the end to the start of arr and multiply each index by two.
		if(table->arr[i]!=NULL){
			tmp=table->arr[i];
			table->arr[i*2]=tmp;
			table->arr[i]=NULL;
		}
		i--;
	}
	//adding the new object after the multiplication
	int j=index*2;
	while(checkListLength(table->maxListLength,table->arr[j])==-1)
		j++;
	table->arr[j]=obj;
	table->dimention*=2;
	return j;
}








//-----^^^^^^^^^--------^^^^^^^$$$$$$$########@@@@@@@@!!!!!!!!!!!!!!!!!!!!!!!
/**
 * This function creates an object and return the pointer to it or NULL if there is some error.
 */
//i allocate memory for data because i can get reference as an argument
//and then will be segmentation fault.
//for example:
//int x;
//add(table,&x);
Object* createObject(void* data,int dataType){
	Object* newObj=(Object*)malloc(sizeof(Object));
	if(newObj==NULL)
		return NULL;
	if(dataType==INT_TYPE){
		newObj->data=(int*)malloc(sizeof(int));//mallocing the data
		if(newObj->data==NULL)
			return NULL;
		*((int*)newObj->data)=*((int*)data);//setting the data
		//newObj->next=NULL;//setting the next to NULL
	}else{//string
		newObj->data=(char*)malloc(sizeof(char)*(strlen(data)+1));//mallocing the data
		if(newObj->data==NULL)
			return NULL;
		strcpy(newObj->data,data);//setting the data
		//newObj->next=NULL;//setting the next to NULL

	}
	newObj->next=NULL;
	return newObj;
}






//-----^^^^^^^^^--------^^^^^^^$$$$$$$########@@@@@@@@!!!!!!!!!!!!!!!!!!!!!!!
/**
 * check the equality of the data of two objects. The implementation is different depending the type of the data.
 * the function returns 0 if they are equal or some other value if they are not equal.
 */
int isEqual(int type, void* data1, void* data2){
	if(type==INT_TYPE){
		if(*((int*)data1)==*((int*)data2))
			return 0;
		else
			return -1;
	}
	else
		return strcmp(((char*)data1),((char*)data2));//if not equal returns <0 else return 0

	return -1;
}






//-----^^^^^^^^^--------^^^^^^^$$$$$$$########@@@@@@@@!!!!!!!!!!!!!!!!!!!!!!!
/**
 * returns the hash index of an integer, which is key mod origSize
 */
int intHashFun(int* key, int origSize){
	return (*key)  %  origSize;

}








//-----^^^^^^^^^--------^^^^^^^$$$$$$$########@@@@@@@@!!!!!!!!!!!!!!!!!!!!!!!
/**
 * returns the hash index of an string, which is m mod origSize, where m is the sum of the ascii value of all the
 * character in key.
 */
int strHashFun(char* key, int origSize){
	int sumOfHaskii=0;;
	int i=0;
	while(key[i]!='\0'){
		sumOfHaskii+=key[i];
		i++;
	}
	return sumOfHaskii%origSize;


}









//-----^^^^^^^^^--------^^^^^^^$$$$$$$########@@@@@@@@!!!!!!!!!!!!!!!!!!!!!!!
/**
 * The function print the table (the format is in the exe definition)
 */
void printTable(Table* table){
	int sizeOfTable=table->size;
	int i=0;
	Object* ptr;


	while(i<sizeOfTable){
		ptr=table->arr[i];
		printf("[%d]",i);
		printf("\t");
		while(ptr!=NULL){
			if(table->dataType==INT_TYPE&&ptr->data)
				printf("%d",*((int*)(ptr->data)));
			else
				printf("%s",((char*)(ptr->data)));
			printf("\t");
			if(ptr->next!=NULL)
				printf("-->");
			printf("\t");
			ptr=ptr->next;
		}
		printf("\n");
		i++;

	}

}








//-----^^^^^^^^^--------^^^^^^^$$$$$$$########@@@@@@@@!!!!!!!!!!!!!!!!!!!!!!!
/**
 * This function frees an object,  note the in the case of STR_TYPE, the data
 * of the object should also be freed.
 */
//note: when freeing a struct we need to free all it's dynamically allocated members and itself.
void freeObject(Object* obj, int type){
	free(obj->data);
	obj->data=NULL;
	//the reason i don't free the next is why:
	//suppose x->y->z then if i will do freeObject(x) then y will be freed(because y is the next of
	//x) but y members will not be freed only y as a pointer will be freed.
	//also i will y twice when freeTable will be called:once now and once when i
	//iterate on it .
	//free(obj->next);
	free(obj);


}







//-----^^^^^^^^^--------^^^^^^^$$$$$$$########@@@@@@@@!!!!!!!!!!!!!!!!!!!!!!!
/**
 * The function release all the allocated members of struct Table.
 */
//note: when freeing a struct we need to free all it's dynamically allocated members and itself.
//the freeing process works in this pattern: we iterate on every cell and on each cell we iterate on it's
//linked list.
//for example:if the linked list is:x->y->z
//tmp=x;
//ptr=y;
//free(x);
//tmp=y;
//ptr=z;
//free(y)...and again
void freeTable(Table* table){
	Object* ptr;
	Object* temp;
	int i=0;
	while(i<table->size){
		ptr=table->arr[i];
		while(ptr!=NULL){
			temp=ptr;
			ptr=ptr->next;
			freeObject(temp,table->dataType);
		}
		i++;
	}
	free(table->arr);
	free(table);

}






//-----^^^^^^^^^--------^^^^^^^$$$$$$$########@@@@@@@@!!!!!!!!!!!!!!!!!!!!!!!
/**
 * The function search for an object that its data is equal to data and returns a pointer to that object.
 * If there is no such object or in a case of an error, NULL is returned.
 */
//this function iterate only on all the cells which are allocated to that key.
//searching for that object.
Object* search(Table* table, void* data){

	Object* ptr;
	int indexInList=1;
	int i=0;
	int index=0;
	if(table->dataType==INT_TYPE)
		index=table->dimention*intHashFun( ((int*)data),table->tableOriginalSize);
	else
		index=table->dimention*strHashFun( ((char*)data) ,table->tableOriginalSize);
	i=index;
	//the cells that the desired object can located are index,index+1..,index+d
	while(i<index+table->dimention){
		ptr=table->arr[i];
		while(ptr!=NULL){
			if(isEqual(table->dataType,data,ptr->data)==0){
				printf("%d",i);
				printf("\t");
				printf("%d",indexInList);
				return ptr;
			}
			ptr=ptr->next;
			indexInList++;
		}
		i++;
		indexInList=1;
	}

	return NULL;
}






//-----^^^^^^^^^--------^^^^^^^$$$$$$$########@@@@@@@@!!!!!!!!!!!!!!!!!!!!!!!
//this function gets an object which is the first element of the list end checks whether
//the list has reached the max list length
//if yes: it returns -1 else return 0
int checkListLength(int listLengthLimit,Object* obj){

	int count=0;
	Object* ptr=NULL;
	ptr=obj;
	while(ptr!=NULL){

		ptr=ptr->next;
		count++;
	}

	if(count>=listLengthLimit)
		return -1;
	else
		return 0;
}







//-----^^^^^^^^^--------^^^^^^^$$$$$$$########@@@@@@@@!!!!!!!!!!!!!!!!!!!!!!!
//this function checks whether there are free cell in the allocated cells for this key
//if do it returns the index else it returns -1;

int checkSpaceInNextIndex(Table* table,int index){

	int i=index+1;
	int d=table->dimention;

	while(i%d!=0){
		if(checkListLength(table->maxListLength,table->arr[i])==0)
			return i;

		i++;
	}


	return -1;
}





//-----^^^^^^^^^--------^^^^^^^$$$$$$$########@@@@@@@@!!!!!!!!!!!!!!!!!!!!!!!
/**
 * The function removes the Object which its data equals to data, if there are more than one, it removes the first one.
 * On success, the function returns the array index of the removed data, otherwise, it returns -1.
 * -1 is also returned in the case where there is no such object.
 */
//the function finds the index which the object should be located
//then it search it on linked list which locates at this index and remove it.
int removeObj(Table* table, void* data){

	Object* tmp;
	Object* ptr;
	int i=0;
	int index=0;
	//	if((*(int*)data)==54)
	//		printf("dsds");


	//getting the right index
	if(table->dataType==INT_TYPE)
		index=table->dimention*intHashFun( ((int*)data),table->tableOriginalSize);
	else
		index=table->dimention*strHashFun( ((char*)data) ,table->tableOriginalSize);



	//iterating on all the cells allocated for that index
	i=index;
	int end=index+table->dimention;

	while(i<end){
		ptr=table->arr[i];
		//if the data locates at the head of the list
		if(ptr!=NULL&&isEqual(table->dataType,ptr->data,data)==0){
			table->arr[i]=ptr->next;
			freeObject(ptr,table->dataType);

			return i;
		}
		//if the data locates future in the list
		while(ptr!=NULL){
			if(isEqual(table->dataType,ptr->data,data)==0){
				tmp->next=ptr->next;
				freeObject(ptr,table->dataType);
				return i;
			}
			tmp=ptr;
			ptr=ptr->next;
		}


		i++;
	}


	return -1;
}


