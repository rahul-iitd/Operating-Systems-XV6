#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "date.h"

int
main(int argc, char *argv[]){

  void *msg=argv[1];
  recv(msg);
  exit();
}
