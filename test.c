#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]) {
 if(argc<2){
  printf(2, "%s command has no argument\n", argv[0]);
  exit();
 }

 hello(argv[1]);
 exit();
}
