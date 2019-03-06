#include "types.h"
#include "stat.h"
#include "user.h"
#define MSGSIZE 8


int main(void)
{
	printf(1,"%s\n","IPC Test case");

	int cid = fork();
	if(cid==0){
		// This is child
		char *msg = (char *)malloc(MSGSIZE);
		char *msg2 = (char *)malloc(MSGSIZE);
		int stat=-1;
		while(stat==-1){
			stat = recv(msg);
		}
		printf(1,"2 CHILD: msg recv is: %s \n", msg );
		int stat2=-1;
		while(stat2==-1){
			stat2 = recv(msg2);
		}
		printf(1,"2 CHILD: msg2 recv is: %s \n", msg2 );

		exit();
	}else{
		// This is parent
		char *msg_child = (char *)malloc(MSGSIZE);
		char *msg_child2 = (char *)malloc(MSGSIZE);

		msg_child = "P";
		msg_child2 = "H";
		send(getpid(),cid,msg_child);
		send(getpid(),cid,msg_child2);

		printf(1,"1 PARENT: msg sent is: %s \n", msg_child );
		printf(1,"1 PARENT: msg2 sent is: %s \n", msg_child2 );

		free(msg_child);
	}

	exit();
}
