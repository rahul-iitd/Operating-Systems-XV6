#include "types.h"
#include "stat.h"
#include "user.h"

char* itoa(int num, int base)
{
		char* str=(char *)malloc(8);
    int i = 0;
    /* Handle 0 explicitely, otherwise empty string is printed for 0 */
    if (num == 0)
    {
        str[i++] = '0';
        str[i] = '\0';
        return str;
    }

    // Process individual digits
    while (num != 0)
    {
        int rem = num % base;
        str[i++] = (rem > 9)? (rem-10) + 'a' : rem + '0';
        num = num/base;
    }
    str[i] = '\0'; // Append string terminator
		char* ans=(char *)malloc(8);
		for (int a = 0; a < i; a++) {
			ans[a]=str[i-a-1];
		}
		ans[i]='\0';
    return ans;
}

int
main(int argc, char *argv[])
{
	if(argc< 2){
		printf(1,"Need type and input filename\n");
		exit();
	}
	char *filename;
	filename=argv[2];
	int type = atoi(argv[1]);
	printf(1,"Type is %d and filename is %s\n",type, filename);

	int tot_sum = 0;
	float variance = 0.0;

	int size=1000;
	short arr[size];
	char c;
	int fd = open(filename, 0);
	for(int i=0; i<size; i++){
		read(fd, &c, 1);
		arr[i]=c-'0';
		read(fd, &c, 1);
	}
  	close(fd);
  	// this is to supress warning
  	printf(1,"first elem %d\n", arr[0]);
		int pid=getpid();
  	//----FILL THE CODE HERE for unicast sum and multicast variance
		int cid;
		int i;
		for (i = 0; i < 8; i++) {
		cid = fork();
		if (cid==0) break;
	}
		if(cid==0){
			//
			char* msg_child= (char *)malloc(MSGSIZE);
			int sum_1=0;
			for (int a = 125*i; a < (i+1)*125; a++) {
				sum_1+=arr[a];
			}
			strcpy(msg_child,itoa(sum_1,10));
			// msg_child="533";
			send(cid,pid,msg_child);

			// printf(1,"1 PARENT: msg sent is: %s \n", msg_child);
			free(msg_child);

			exit();
		}
		else{

			char *msg = (char *)malloc(MSGSIZE);
			int stat=-1;
			for (int i = 0; i < 8; i++) {
			while(stat==-1){
				// printf(1,"Receive called\n");
				stat = recv(msg);
				sleep(1.1);
			}
			// printf(1,"2 CHILD: msg recv is: %s \n", msg );
			// int* s=(int*)msg;
			tot_sum+=atoi(msg);
			stat=-1;
		}
			// printf(1,"Total sum is: %d \n", tot_sum );
			// printf(1,"2 CHILD: msg recv is: %s \n", msg );

		}



  	//------------------

  	if(type==0){ //unicast sum
		printf(1,"Sum of array for file %s is %d\n", filename,tot_sum);
	}
	else{ //mulicast variance
		printf(1,"Variance of array for file %s is %d\n", filename,(int)variance);
	}
	exit();
}
