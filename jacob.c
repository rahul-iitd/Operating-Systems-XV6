//
// Created by rahul on 22/3/19.
//

#include "types.h"
#include "stat.h"
#include "user.h"




// #define E 0.00001
// #define T 100.0
// #define P 2
// #define L 300

float fabsm(float a){
    if(a<0)
        return -1*a;
    return a;
}
int main(int argc, char *argv[]){

char c;
int file = open("assig2a.inp", 0);
int iter=0;
int number[100];
while(1){
		read(file, &c, sizeof(char));
    if (c-'0'==-38) break;
    number[iter]=c-'0';
    iter++;
	}
  int N=0;
  int place=1;
for (int i = iter-1; i >= 0; i--) {
  N+=place*number[i];
  place*=10;
}
// int E1=0.0;
double p=0.1;
// int decimal =0;
// // while(1){
// //     one++;
// // 		read(file, &c, sizeof(char));
// //     // printf(1,"c is %c\n",c);
// //     if ((one==1) && (c-'0'==1)){E=1; break;}
// //     if (c-'0'==-38) break;
// //     if ((one>1) && (c-'0'!=-2)){
// //       // printf(1,"c is %c\n",c);
// //     E+=p*(c-'0');
// //     // printf(1,"c is %c\n",c);
// //
// //     p=p/10;
// //   }
// // }
// iter =0;
// int d_count=0;
// while(1){
// 		read(file, &c, sizeof(char));
//     if (c-'0'==-38) break;
//     if (c-'0'==-2) decimal=1;
//     if (c-'0'!=-2){
//     number[iter]=c-'0';
//     if (decimal==1) d_count++;
//     iter++;
//   }
// }
//    place=1;
// for (int i = iter-1; i >= 0; i--) {
//   E1+=place*number[i];
//   place*=10;
// }
//
// //float E=E1;
// printf(1,"E1 is %d\n",E1);
// float E = E1*1.0;
// for (int i = 0; i < d_count; i++) {
//   E=E*1.0/10;
// }
//float E=E1;

float E=0.0;
int b=0;
int d_count=0;
while(1){
  read(file, &c, sizeof(char));
  if (c-'0'==-2) b=1;
  if (c-'0'==-38) break;
  if (b==1 && c-'0'!=-2){
    d_count++;
  }
  if (c-'0'!=-2){
    E=E*10+(c-'0');
  }

}

for (int i = 0; i < d_count; i++) {
  E=E*1.0/10;
}

// printf(1,"E1 is %d\n",E*100000);

int T=0;
p=0.1;
iter=0;
while(1){
		read(file, &c, sizeof(char));
    if (c-'0'==-2) break;
    number[iter]=c-'0';

    iter++;
	}
  place=1;
for (int i = iter-1; i >= 0; i--) {
  T=place*number[i];
  place*=10;
}

double T2=0;

while(1){
  read(file, &c, sizeof(char));
  if (c-'0'==-38) break;
    T2+=p*(c-'0');
    p=p/10;
}


iter =0;
while(1){
		read(file, &c, sizeof(char));
    if (c-'0'==-38) break;
    number[iter]=c-'0';
    iter++;
	}
  int P=0;
   place=1;
for (int i = iter-1; i >= 0; i--) {
  P+=place*number[i];
  place*=10;
}


iter =0;
while(1){
		read(file, &c, sizeof(char));
    if (c-'0'==-38) break;
    number[iter]=c-'0';
    iter++;
	}
  int L=0;
   place=1;
for (int i = iter-1; i >= 0; i--) {
  L+=place*number[i];
  place*=10;
}

// printf(1,"P is %d\n", P);
// printf(1,"L is %d\n", L);
// printf(1,"N is %d\n", N);
// printf(1,"T is %d\n", T);
// printf(1,"E is %d\n", E*100000);










close(file);

    float diff;
    float mean;
    float u[N][N];
    float w[N][N];

    int count=0;
    mean = 0.0;
    for (int i = 0; i < N; i++){
        u[i][0] = u[i][N-1] = u[0][i] = T;
        u[N-1][i] = 0.0;
        mean += u[i][0] + u[i][N-1] + u[0][i] + u[N-1][i];
    }
    mean /= (4.0 * N);
    for (int i = 1; i < N-1; i++ ){
        for (int j= 1; j < N-1; j++) u[i][j] = mean;}


    int cid;
    int pi;
    int fd[P][2];
    for (int i = 0; i <P ; ++i) {
      int ret;
      ret=pipe(fd[i]);
      if(ret<0){
        printf(1,"%s\n","Error in creating in pipes" );
      }
    }
    for (;;) {
            // printf(1,"C is %d\n",count);
            int chunk_size=(N-2)/P;
            for (pi = 0; pi < P; pi++) {
                cid = fork();
                if (cid == 0) {
                  if (pi==0){
                    // printf(1,"Count child is %d\n",count);
                  }
                    // close(fd[pi][0]);
                    diff = 0.0;
                    if (pi != P - 1) {
                      // printf(1,"Count child is %d\n",count);
                        for (int i = 1 + chunk_size * pi; i <= chunk_size * (pi + 1); i++) {
                            for (int j = 1; j < N - 1; j++) {
                                w[i][j] = (u[i - 1][j] + u[i + 1][j] +
                                           u[i][j - 1] + u[i][j + 1]) / 4.0;
                                if (fabsm(w[i][j] - u[i][j]) > diff)
                                    diff = fabsm(w[i][j] - u[i][j]);
                            }
                        }

                        float w_child[chunk_size * (N - 2) + 1];

                        for (int i = 1 + chunk_size * pi; i <= chunk_size * (pi + 1); ++i) {
                            for (int j = 1; j < N - 1; ++j) {
                                w_child[(i-1 - chunk_size * pi) * (N - 2) + j-1] = w[i][j];
                            }
                        }
                        w_child[chunk_size * (N - 2)] = diff;
                        close(fd[pi][0]);
                        write(fd[pi][1], &w_child, sizeof(w_child));

                        // close(fd[pi][1]);
                        // printf(1,"Count child 1 is %d\n",count);
                    }
                    else {

                        for (int i = 1 + chunk_size * pi; i <= N - 2; i++) {
                            for (int j = 1; j < N - 1; j++) {
                                w[i][j] = (u[i - 1][j] + u[i + 1][j] +
                                           u[i][j - 1] + u[i][j + 1]) / 4.0;
                                if (fabsm(w[i][j] - u[i][j]) > diff)
                                    diff = fabsm(w[i][j] - u[i][j]);
                            }
                        }

                        float w_child[(N - 2 - chunk_size * pi) * (N - 2) + 1];
                        for (int i = 1 + chunk_size * pi; i <= N - 2; ++i) {
                            for (int j = 1; j < N - 1; ++j) {
                                w_child[(i-1 - chunk_size * pi) * (N - 2) + j-1] = w[i][j];
                            }
                        }

                        w_child[(N - 2 - chunk_size * pi) * (N - 2)] = diff;
                        close(fd[pi][0]);
                        write(fd[pi][1], &w_child, sizeof(w_child));

                        // close(fd[pi][1]);
                    }

                    exit();
                }
            }
                // printf(1,"Count is %d\n",count);
                    diff = 0;
                    for (int pid = 0; pid < P; ++pid) {
                        // close(fd[pid][1]);

                        if (pid != P - 1) {

                            float new_w[chunk_size * (N - 2)+1];
                            // close(fd[pid][1]);
                            read(fd[pid][0], &new_w, sizeof(new_w));
                            // close(fd[pid][0]);

                            for (int i = 1 + chunk_size * pid; i <= chunk_size * (pid + 1); ++i) {
                                for (int j = 1; j < N - 1; ++j) {
                                    u[i][j] = new_w[(i-1 - chunk_size * pid) * (N - 2) + j-1];
                                }
                            }


                            float diff_child;
                            diff_child = new_w[chunk_size * (N - 2)];
                            if (diff_child > diff) diff = diff_child;

                        } else {

                            float new_w[(N - 2 - chunk_size * pid) * (N - 2)+1];
                            // close(fd[pid][1]);
                            // printf(1,"Count is %d\n",count);
                            read(fd[pid][0], &new_w, sizeof(new_w));

                            // close(fd[pid][0]);
                            for (int i = 1 + chunk_size * pid; i <= N - 2; ++i) {
                                for (int j = 1; j < N - 1; ++j) {
                                    u[i][j] = new_w[(i-1 - chunk_size * pid) * (N - 2) + j-1];
                                }
                            }

                            float diff_child;
                            diff_child = new_w[(N - 2 - chunk_size * pid) * (N - 2)];
                            if (diff_child > diff) diff = diff_child;
                        }
                        // close(fd[pid][0]);
                        // close(fd[pid][1]);
                    }
                    // printf(1,"%d\n",count );
                    count++;

                    if (diff <= E || count > L) {
                        break;
                    }
                    for (int i = 0; i < P; i++) {
                      /* code */
                      wait();
                    }


}






    for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                printf(1,"%d ", ((int) u[i][j]));
            printf(1,"\n");
    }
    exit();
}
