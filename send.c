#include "types.h"
#include "stat.h"
#include "user.h"
#include "fcntl.h"
#include "date.h"

int
main(int argc, char *argv[]){

  int sender_pid=atoi(argv[1]);
  int rec_pid=atoi(argv[2]);
  void *msg=argv[3];
  send(sender_pid,rec_pid,msg);
  exit();
}
