#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>
#include<omp.h>


int flag;

// ===== Auxillary functions ======== //

static double get_wall_seconds() {
  struct timeval tv;
  gettimeofday(&tv,NULL);
  double seconds = tv.tv_sec + (double)tv.tv_usec/1000000;
  return seconds;
}

void printArray(int* arr, int N) {
  printf("{");
  for(int i = 0; i < N-1; i++) {
    printf("%d, ",arr[i]);
  }
  printf("%d}\n",arr[N-1]);
}

// Array where we store the random elements
void generateArray(int* arr, int N, int max) {
  srand(get_wall_seconds());
  for (int i = 0; i < N; i++) {
    arr[i] = rand() % max; // Genrate a int in [0,max]
  }
}

void swap(int *xp, int *yp) { 
    int temp = *xp; 
    *xp = *yp; 
    *yp = temp; 
} 



// ==== mergeSort functions ==== //

// Bubblesort, taken from https://www.geeksforgeeks.org/bubble-sort/
void bubbleSort(int* arr, const int n) { 
   int i, j; 
   for (i = 0; i < n-1; i++)       
       for (j = 0; j < n-i-1; j++)  
           if (arr[j] > arr[j+1]) 
              swap(&arr[j], &arr[j+1]); 
} 

void merge(int* __restrict list, int* __restrict l1, int* __restrict l2, const int n1, const int n2) {
  int i = 0; int i1 = 0; int i2 = 0;
  while(i1 < n1 && i2 < n2) {
    if(l1[i1] < l2[i2]) {
      list[i] = l1[i1];
      i1++;
    } else {
      list[i] = l2[i2];
      i2++;
    }
    i++;  
  }
  while(i1 < n1) {
    list[i] = l1[i1];
    i++;
    i1++;
  }
  while(i2 < n2) {
    list[i] = l2[i2];
    i++;
    i2++;
  }
}

void mergeSort(int* __restrict list, const int N,const  int threads) {
  if (N == 1) {
    return;
  }

  if (N < flag) { // When list size is below a given threshold use bubblesort to avoid overhead from function calls.
    bubbleSort(list,N);
    
  } else { 
    int n1 = N>>1;
    int n2 = N - n1;
    int* l1 = (int*)malloc(N*sizeof(int)); //Allocate memory once, access "l2" with &l1[n1].
    
    for (int i = 0; i < n1; i++) {
      l1[i] = list[i];
      l1[n1+i] = list[n1+i];
    }
    
    if (N % 2 != 0) { // If N is odd the second list will be one element longer.
      l1[N-1] = list[N-1];
    }
    
    if (threads > 1) { 
  #pragma omp parallel sections num_threads(threads)
  {
    #pragma omp section 
    {mergeSort(l1,n1,threads/2);}
    #pragma omp section
    {mergeSort(&l1[n1],n2,threads/2);}
  }
 
    } else {
      mergeSort(l1,n1,1);
      mergeSort(&l1[n1],n2,1);
    }
    merge(list,l1,&l1[n1],n1,n2);
    free(l1);
  }
}


// === Analysis functions === //

// count the number of times the digit check appears in the array list with size N.
int count(int* list, int N, int a) {
  int counter = 0;
  
  for (int i = 0; i < N; i++) {
    if (a == list[i]) {
      counter++;
    }
  }
  return counter;
}

int correctness(int a, int b, int check) {
  if (a == b) {
    //printf("Same number of %d before and after sort: %d\n",check,a);
    return 1;
  } else {
    printf("Not same number of %d before and after, before: %d , after %d\n",check,a,b);
    return 0;
  }
}

 void singleRun(const int N, const int max, const int threads) {
  int c1; int c2; int check = 32;
  double time;
  
  int* list = (int*)malloc(N*sizeof(int));
  generateArray(list,N,max);

  c1 = count(list,N,check);
  time = get_wall_seconds();
  mergeSort(list,N,threads);
  time = get_wall_seconds() - time;
  c2 = count(list,N,check);

  printf("%f\n",time);
  
  correctness(c1,c2,check);

  free(list);
}

 void benchmark(const int N,const int max,const int K, int threads) {
  double time;
  double timeSum = 0;
  int* list = (int*)malloc(N*sizeof(int));
  int c1; int c2; int check = 32;

  
  for (int i = 0; i < K; i++) {
    generateArray(list,N,max);
    
    c1 = count(list,N,check);
    time = get_wall_seconds();
    mergeSort(list,N,threads);
    time = get_wall_seconds() - time;
    c2 = count(list,N,check);
    
    correctness(c1,c2,check);
    timeSum += time;
  }
  printf("%f\n",timeSum);
  
  free(list);
}



// ===== main ====== //
int main(int argc, char* argv[] ) {
  const int N = atoi(argv[1]);
  flag = atoi(argv[2]);
  const int nThreads = atoi(argv[3]);

  const int max = 200;
  omp_set_nested(1);
  omp_set_num_threads(nThreads);
  
  
  singleRun(N,max,nThreads);
  //benchmark(N,max,1000,nThreads);

}
