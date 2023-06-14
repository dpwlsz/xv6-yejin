#include "types.h"
#include "stat.h"
#include "user.h"
#include "thread.h"

int arr[100];

void function(void *arg1, void *arg2)
{
  // print arguments
  printf(1, "arg1 = %d, arg2 = %d\n", *((int *)arg1), *((int *)arg2));

  int num1 = *((int *)arg1);
  int num2 = *((int *)arg2);

  for(int i = 0; i < 5; i++)
  {
    arr[num1+i] =  num2;
  }

  exit();
}

int main(int argc, char *argv[]) 
{
  int tid[4];
  
  int arg1 = 0;
  int arg2 = 5;
  int arg3 = 10;
  int arg4 = 15;
  int arg5 = 20;
  int arg6 = 25;
  int arg7 = 30;
  int arg8 = 35;

  tid[0] = thread_create(&function, &arg1, &arg5);
  tid[1] = thread_create(&function, &arg2, &arg6);
  tid[2] = thread_create(&function, &arg3, &arg7);
  tid[3] = thread_create(&function, &arg4, &arg8);


  for(int i = 0; i < 2; i++)
  {
    thread_join(tid[i]);
  }
  
  for (int i = 0; i < 30; i++)
  {
    printf(1, "[%d] = %d\n", i, arr[i]);
  }

  exit();
}

// -4