#include<stdio.h>
#include<stdlib.h>
#include<sys/time.h>

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



// ==== mergeSort functions ==== // 

void merge(int* __restrict list, int* __restrict l1, int* __restrict l2, int n1, int n2) {
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

void mergeSort(int* __restrict list,int N) {
  if (N == 1) {
    return;
  }

  int n1 = N>>1;
  int n2 = N - n1;
  int* l1 = (int*)malloc(N*sizeof(int));
  int* l2 = &l1[n1];

  for (int i = 0; i < n1; i++) {
    l1[i] = list[i];
    l2[i] = list[n1+i];
  }

  if (n1 != n2) { // From splitting l2 will have one element more if uneven list size.
    l2[n2-1] = list[N-1];
  }
  
  mergeSort(l1,n1);
  mergeSort(l2,n2);
  merge(list,l1,l2,n1,n2);

  free(l1);
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

void singleRun(int N, int max) {
  int c1; int c2; int check = 32;
  double time;
  
  int* list = (int*)malloc(N*sizeof(int));
  generateArray(list,N,max);

  c1 = count(list,N,check);
  time = get_wall_seconds();
  mergeSort(list,N);
  time = get_wall_seconds() - time;
  c2 = count(list,N,check);

  printf("%f\n",time);
  
  correctness(c1,c2,check);

  free(list);
}

void benchmark(const int N,const int max,const int K) {
  double time;
  double timeSum = 0;
  int* list = (int*)malloc(N*sizeof(int));
  int c1; int c2; int check = 32;

  
  for (int i = 0; i < K; i++) {
    generateArray(list,N,max);
    
    c1 = count(list,N,check);
    time = get_wall_seconds();
    mergeSort(list,N);
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
  const int max = atoi(argv[2]);
  
  //singleRun(N,max);
  benchmark(N,max,1000);

}
