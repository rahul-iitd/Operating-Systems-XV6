#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "date.h"

int
main(int argc, char *argv[]){

  int a=atoi(argv[1]);
  int b=atoi(argv[2]);
  add(a,b);
  exit();
}
