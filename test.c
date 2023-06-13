#include "types.h"
#include "stat.h"
#include "user.h"
#include "thread.h"

int arr[20];

void function(void *arg)
{
  int num = *((int *)arg);
  for(int i = 0; i < 5; i++)
  {
    arr[num + i] =  num;
  }

  exit();
}

int main(int argc, char *argv[]) 
{
  int tid[4];
  
  int arg0 = 0;
  int arg1 = 5;
  int arg2 = 10;
  int arg3 = 15;

  tid[0] = thread_create(&function, &arg0);
  tid[1] = thread_create(&function, &arg1);
  tid[2] = thread_create(&function, &arg2);
  tid[3] = thread_create(&function, &arg3);

  for(int i = 0; i < 4; i++)
  {
    thread_join(tid[i]);
  }
  
  for (int i = 0; i < 20; i++)
  {
    printf(1, "[%d] = %d\n", i, arr[i]);
  }

  exit();
}

// -4