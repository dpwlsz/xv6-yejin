#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {
 if(argc<2){
  printf(2, "Usage: %s arg1\n", argv[0]);
  exit();
 }

 hello(argv[1]);
 exit();
}
