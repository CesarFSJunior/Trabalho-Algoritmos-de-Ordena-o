#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

int compare(int a, int b) {
        if (a > b){
            return 1;
        }else{
            return 0;
        }
    }

void bubbleSort(int array[], int size, int *iterator) {
    for (int i = 0; i < size; i++) {
            for (int j = 0; j < size - 1 - i; j++) {
            *iterator = *iterator + 1;
            if (compare(array[j], array[j + 1]) == 1) {

                 int temp = array[j];
                 array[j] = array[j+1];
                 array[j + 1] = temp;

            }

        }

    }
}

void merge(int left[], int leftLenght, int right[], int rightLenght, int *it) {

    int i=0;
    int j=0;
    int result[leftLenght + rightLenght];
    int counter = 0;

    while (i < leftLenght && j < rightLenght) {
        if(compare(left[i], right[j]) == 0) {
            result[counter] = left[i];
            counter ++;
            i++;
        } else {
            result[counter] = right[j];
            counter ++;
            j++;
        }
        (*it)++;
    }

    if (i < leftLenght) {
        for(int k = 0; k < leftLenght - i; k++) {
            result[counter] = left[i + k];
            counter ++;
        }
    } else {
        for(int k = 0; k < rightLenght - j; k++) {
            result[counter] = right[j + k];
            counter ++;
        }
    }

    for(int i = 0; i < counter; i++) {
        if (i < leftLenght) {
            left[i] = result[i];
        } else {
            right[i-leftLenght] = result[i];
        }
    }
}

void mergeSort(int* arr, int size, int *it) {

    if (size > 1){

        int leftSize = size / 2;
        int rightSize = size - leftSize;

        int *left = &arr[0];
        mergeSort(left, leftSize, it);

        int *right = &arr[leftSize];
        mergeSort(right, rightSize, it);


        merge(left, leftSize, right, rightSize, it);

    }
}

void heapify(int arr[], int index, int size, int *it) {

    int element = index;
    int left = (2 * index) + 1;
    int right = (2 * index) + 2;
    *it = *it + 2;

    if ( left < size && compare(arr[element], arr[left]) == 0) {

        element = left;

    }
    if ( right < size && compare(arr[element], arr[right]) == 0) {

        element = right;

    }
    if ( index != element ) {
        int temp = arr[index];
        arr[index] = arr[element];
        arr[element] = temp;
        heapify(arr, element, size, it);
    }
}

void buildMaxHeap(int array[], int size, int *it) {
    for(int i = size / 2; i >= 0; i = i - 1) {
        heapify(array, i, size, it);
    }
}

void heapSort(int arr[], int size, int *it) {
    int arrSize = size;
    buildMaxHeap(arr, size, it);
    while(arrSize > 1) {
        int temp = arr[0];
        arr[0] = arr[arrSize-1];
        arr[arrSize-1] = temp;

        arrSize = arrSize - 1;
        heapify(arr, 0, arrSize, it);
    }
}

void mix(int arrAsc[], int arrDesc[], int arrRand[], int arrConc[], int arrConv[], int size) {

    for (int i = 0; i < size; i++) {
        arrAsc[i] = i;
        arrDesc[i] = size - 1 - i;
        arrRand[i] = (rand() % size) + 1;
        if (size % 2 == 0) {
            if (i < size / 2 ) {
            arrConc[i] = i;
            arrConv[i] = size - i;
            } else {
                arrConc[i] = size - i -1 ;
                arrConv[i] = i + 1 ;
            }
        } else {
            if (i <= size / 2 ) {
            arrConc[i] = i;
            arrConv[i] = size - i;
            } else {
                arrConc[i] = size - i - 1;
                arrConv[i] = i + 1;
            }
        }
    }
}

void printArr(int arr[], int n) {
    for(int i = 0; i < n; i++) {
        printf("%d,", arr[i]);
    }
}


int main()
{

    FILE *arquivo = fopen("TestesDesempenhoAps.csv", "a");
    srand(time(NULL));
    int n = 100000;

    for (int i = 0; i < 9041; i++){

    //printf("Numero de valores: \n");
    //scanf("%d", &n);

    int * arrAsc;
    int * arrDesc;
    int * arrRand;
    int * arrConc;
    int * arrConv;

    int iteratorAsc = 0;
    int iteratorDesc = 0;
    int iteratorRand = 0;
    int iteratorConc = 0;
    int iteratorConv = 0;

    arrAsc = (int *) malloc(n * sizeof(int));
    arrDesc = (int *) malloc(n * sizeof(int));
    arrRand = (int *) malloc(n * sizeof(int));
    arrConc = (int *) malloc(n * sizeof(int));
    arrConv = (int *) malloc(n * sizeof(int));

    clock_t start, end;
    double elapsed_time;

    //printf("\n\nMixing:\n");

    mix(arrAsc, arrDesc, arrRand, arrConc, arrConv, n);

    /*printf("\n\nArrASC: \n", n);
    printArr(arrAsc, n);

    printf("\n\nArrDesc: \n");
    printArr(arrDesc, n);

    printf("\n\nArrRand: \n");
    printArr(arrRand, n);

    printf("\n\nArrConc: \n");
    printArr(arrConc, n);

    printf("\n\nArrConv: \n");
    printArr(arrConv, n);


    printf("\n\n\nBubble Sort:");*/
    start = clock();
        bubbleSort(arrAsc, n, &iteratorAsc);
    end = clock();
    elapsed_time = (double)(end - start) / CLOCKS_PER_SEC * 1000;
    fprintf(arquivo, "\nbubbleSort,Asc,%d,%d,%.2f",n, iteratorAsc, elapsed_time);

    start = clock();
        bubbleSort(arrDesc, n, &iteratorDesc);
    end = clock();
    elapsed_time = (double)(end - start) / CLOCKS_PER_SEC * 1000;
    fprintf(arquivo, "\nbubbleSort,Desc,%d,%d,%.2f",n, iteratorDesc, elapsed_time);

    start = clock();
        bubbleSort(arrRand, n, &iteratorRand);
    end = clock();
    elapsed_time = (double)(end - start) / CLOCKS_PER_SEC * 1000;
    fprintf(arquivo, "\nbubbleSort,Rand,%d,%d,%.2f",n, iteratorRand, elapsed_time);

    start = clock();
        bubbleSort(arrConc, n, &iteratorConc);
    end = clock();
    elapsed_time = (double)(end - start) / CLOCKS_PER_SEC * 1000;
    fprintf(arquivo, "\nbubbleSort,Conc,%d,%d,%.2f",n, iteratorConc, elapsed_time);

    start = clock();
        bubbleSort(arrConv, n, &iteratorConv);
    end = clock();
    elapsed_time = (double)(end - start) / CLOCKS_PER_SEC * 1000;
    fprintf(arquivo, "\nbubbleSort,Conv,%d,%d,%.2f",n, iteratorConv, elapsed_time);

    /*printf("\n\nArrASC: \n", n);
    printArr(arrAsc, n);
    printf("\n%d\n", iteratorAsc);

    printf("\n\nArrDesc: \n");
    printArr(arrDesc, n);
    printf("\n%d\n", iteratorDesc);

    printf("\n\nArrRand: \n");
    printArr(arrRand, n);
    printf("\n%d\n", iteratorRand);

    printf("\n\nArrConc: \n");
    printArr(arrConc, n);
    printf("\n%d\n", iteratorConc);

    printf("\n\nArrConv: \n");
    printArr(arrConv, n);
    printf("\n%d\n", iteratorConv);


    printf("\n\nMixing:\n");*/

    //mix(arrAsc, arrDesc, arrRand, arrConc, arrConv, n);

    iteratorAsc = 0;
    iteratorDesc = 0;
    iteratorRand = 0;

    /*printf("\n\nArrASC: \n", n);
    printArr(arrAsc, n);

    printf("\n\nArrDesc: \n");
    printArr(arrDesc, n);

    printf("\n\nArrRand: \n");
    printArr(arrRand, n);

    printf("\n\nArrConc: \n");
    printArr(arrConc, n);

    printf("\n\nArrConv: \n");
    printArr(arrConv, n);



    printf("\n\n\Merge Sort:");*/
    /*start = clock();
        mergeSort(arrAsc, n, &iteratorAsc);
    end = clock();
    elapsed_time = (double)(end - start) / CLOCKS_PER_SEC * 1000;
    fprintf(arquivo, "\nmergeSort,Asc,%d,%d,%.2f",n, iteratorAsc, elapsed_time);

    start = clock();
        mergeSort(arrDesc, n, &iteratorDesc);
    end = clock();
    elapsed_time = (double)(end - start) / CLOCKS_PER_SEC * 1000;
    fprintf(arquivo, "\nmergeSort,Desc,%d,%d,%.2f",n, iteratorDesc, elapsed_time);

    start = clock();
        mergeSort(arrRand, n, &iteratorRand);
    end = clock();
    elapsed_time = (double)(end - start) / CLOCKS_PER_SEC * 1000;
    fprintf(arquivo, "\nmergeSort,Rand,%d,%d,%.2f",n, iteratorRand, elapsed_time);

    start = clock();
        mergeSort(arrConc, n, &iteratorConc);
    end = clock();
    elapsed_time = (double)(end - start) / CLOCKS_PER_SEC * 1000;
    fprintf(arquivo, "\nmergeSort,Conc,%d,%d,%.2f",n, iteratorConc, elapsed_time);

    start = clock();
        mergeSort(arrConv, n, &iteratorConv);
    end = clock();
    elapsed_time = (double)(end - start) / CLOCKS_PER_SEC * 1000;
    fprintf(arquivo, "\nmergeSort,Conv,%d,%d,%.2f",n, iteratorConv, elapsed_time);*/


   /*printf("\n\nArrASC: \n", n);
    printArr(arrAsc, n);
    printf("\n%d\n", iteratorAsc);

    printf("\n\nArrDesc: \n");
    printArr(arrDesc, n);
    printf("\n%d\n", iteratorDesc);

    printf("\n\nArrRand: \n");
    printArr(arrRand, n);
    printf("\n%d\n", iteratorRand);

    printf("\n\nArrConc: \n");
    printArr(arrConc, n);
    printf("\n%d\n", iteratorConc);

    printf("\n\nArrConv: \n");
    printArr(arrConv, n);
    printf("\n%d\n", iteratorConv);


    printf("\n\nMixing:\n");*/

    //mix(arrAsc, arrDesc, arrRand, arrConc, arrConv, n);

    iteratorAsc = 0;
    iteratorDesc = 0;
    iteratorRand = 0;

    /*printf("\n\nArrASC: \n", n);
    printArr(arrAsc, n);

    printf("\n\nArrDesc: \n");
    printArr(arrDesc, n);

    printf("\n\nArrRand: \n");
    printArr(arrRand, n);

    printf("\n\nArrConc: \n");
    printArr(arrConc, n);

    printf("\n\nArrConv: \n");
    printArr(arrConv, n);


    printf("\n\n\Heap Sort:");*/
    /*start = clock();
        heapSort(arrAsc, n, &iteratorAsc);
    end = clock();
    elapsed_time = (double)(end - start) / CLOCKS_PER_SEC * 1000;
    fprintf(arquivo, "\nheapSort,Asc,%d,%d,%.2f",n, iteratorAsc, elapsed_time);

    start = clock();
        heapSort(arrDesc, n, &iteratorDesc);
    end = clock();
    elapsed_time = (double)(end - start) / CLOCKS_PER_SEC * 1000;
    fprintf(arquivo, "\nheapSort,Desc,%d,%d,%.2f",n, iteratorDesc, elapsed_time);

    start = clock();
        heapSort(arrRand, n, &iteratorRand);
    end = clock();
    elapsed_time = (double)(end - start) / CLOCKS_PER_SEC * 1000;
    fprintf(arquivo, "\nheapSort,Rand,%d,%d,%.2f",n, iteratorRand, elapsed_time);

    start = clock();
        heapSort(arrConc, n, &iteratorConc);
    end = clock();
    elapsed_time = (double)(end - start) / CLOCKS_PER_SEC * 1000;
    fprintf(arquivo, "\nheapSort,Conc,%d,%d,%.2f",n, iteratorConc, elapsed_time);

    start = clock();
        heapSort(arrConv, n, &iteratorConv);
    end = clock();
    elapsed_time = (double)(end - start) / CLOCKS_PER_SEC * 1000;
    fprintf(arquivo, "\nheapSort,Conv,%d,%d,%.2f",n, iteratorConv, elapsed_time);*/


    /*printf("\n\nArrASC: \n", n);
    printArr(arrAsc, n);
    printf("\n%d\n", iteratorAsc);

    printf("\n\nArrDesc: \n");
    printArr(arrDesc, n);
    printf("\n%d\n", iteratorDesc);

    printf("\n\nArrRand: \n");
    printArr(arrRand, n);
    printf("\n%d\n", iteratorRand);

    printf("\n\nArrConc: \n");
    printArr(arrConc, n);
    printf("\n%d\n", iteratorConc);

    printf("\n\nArrConv: \n");
    printArr(arrConv, n);
    printf("\n%d\n", iteratorConv);*/

    free(arrAsc);
    free(arrDesc);
    free(arrRand);
    free(arrConc);
    free(arrConv);

    //printf("\n\n");
    }
    return 0;
}
