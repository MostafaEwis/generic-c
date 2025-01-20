#include <stdio.h>
#include <string.h>

int* binarySearch(int key, int* arr, int size){
	int min = 0 , max = size - 1;
	int middle = max / 2; 
	printf("%d\n", middle);
	while(min <= max){
		if(arr[middle] < key){
			min = middle + 1;
		}else if(arr[middle] > key){
			max = middle - 1;
		}else{
			return arr + middle;
		}
		middle = (max + min) / 2; 
		printf("%d\n", middle);
	}
	return NULL;

}
int cmp(void* po1, void* po2){
	int result;
	double d1 = *(double*)po1, d2 = *(double*)po2;

	if(d1 < d2) result = -1;
	else if(d1 > d2) result = 1;
	else result = 0;

	return result;
}
void* genericbinarysearch(void* key, void* arr, int size, int elemSize, int(*cmp)(void*, void*)){
	int min = 0;
	int max = size - 1;
	int middle = max / 2;
	printf("%d\n", middle);
	while(min <= max){
		//this would only work if the binary representations matches the int like style, floats and doubles wouldn't work
		//int result = memcmp((void*)((char*)arr + middle * elemSize), key, elemSize);
		int result = cmp((void*)((char*)arr + middle * elemSize), key);
		if(result < 0){
			min = middle + 1;
		}else if(result > 0){
			max = middle - 1;
		}else{
			return (void*)((char*)arr + middle * elemSize);
		}
		middle = (max + min) / 2;
		printf("%d\n", middle);
	}
	return NULL;

}

int main(){
	int iarr[] = {10, 20, 30, 50, 54, 55, 59, 60};	
	double arr[] = {0.1, 0.3, 0.4, 4.2, 5.3, 10.1, 11.9, 12.1};
	//float arr[] = {0.1, 0.3, 0.4, 4.2, 5.3, 10.1, 11.9, 12.1};
	double* fplace = genericbinarysearch(&arr[1], arr, 8, sizeof(double), cmp);
	printf("the element %f is at ", *fplace);
	printf("%p", fplace);
	return 0;
}
