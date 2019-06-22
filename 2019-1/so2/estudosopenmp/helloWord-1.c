/* 
    export OMP_NUM_THREADS=12
    gcc -fopenmp helloWord-1.c
    ./a.out
*/



#include <omp.h>
#include <stdio.h>

int main(int *argc, char *argv[]){
  #pragma omp parallel
  {
    printf("Hello World\n");
  }
  return 0;
}