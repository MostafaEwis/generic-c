#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

typedef struct{
	size_t occupied;
	size_t size;
	size_t elemSize;
	void* arr;


} CVector;

void createCVector(CVector* vec, size_t elemSize){
	vec -> elemSize = elemSize;
	vec -> arr = malloc(elemSize * 4);
	vec -> size = 4;
	vec -> occupied = 0;
}

void growCVector(CVector* vec){
	void* ptr = realloc(vec -> arr, 2 * vec -> size * vec -> elemSize);
	vec -> size *= 2;
	vec->arr = ptr;
	assert(ptr != NULL);
}
void pushElement(CVector* vec, void* elem){
	printf("occupied: %d size: %d\r", vec->occupied, vec->size);
	if(vec -> occupied == vec -> size){
		growCVector(vec);
	}
	void* dest = (char*)(vec -> arr) + vec -> occupied * vec -> elemSize;
	memcpy(dest, elem, vec -> elemSize);
	vec -> occupied++;
}
void* popElement(CVector* vec){
	assert(vec -> occupied != 0);
	void* elem = (char*)(vec -> arr) + (vec -> occupied - 1) * vec -> elemSize;
	vec -> occupied--;
	return elem;
}
void freeCVector(CVector* vec, int(*freeElem)(void*)){
	if(freeElem != NULL){
		for(size_t i = 0; i < vec -> occupied; i++){
			freeElem((char*)(vec -> arr) + i * vec -> elemSize);
		}
	}
	printf("currently freeing the size of: %d", vec->elemSize);
	free(vec -> arr);
}
void* getElem(CVector* vec, int index){
	assert(index >= 0 && index < vec -> occupied);
	void* elem = (char*)(vec -> arr) + index * vec -> elemSize;
	return elem;
}
int main(){
	//double test
	CVector vec;
	createCVector(&vec, sizeof(double));
	for(int i = 0; i < 200000; i++){
		double elem = (double)i * 0.1;
		pushElement(&vec, &elem);

	}

	printf("\n");
	for(int i = 0; i < 200000; i++){
		printf("%f\r", *(double*)getElem(&vec, i));
	}
	freeCVector(&vec, NULL);
	//int test
	printf("\n");
	CVector intVec;
	createCVector(&intVec, sizeof(int));
	for(int i = 0; i < 100000; i++){
		int elem = i;
		pushElement(&intVec, &elem);

	}
	printf("\n");
	for(int i = 0; i < 100000; i++){
		printf("%i\r", *(int*)getElem(&intVec, i));
	}
	freeCVector(&intVec, NULL);
}
