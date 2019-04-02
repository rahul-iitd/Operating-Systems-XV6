//
// Created by rahul on 22/3/19.
//

//#include "types.h"
//#include "stat.h"
//#include "user.h"

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <time.h>








float fabsm(float a){
    if(a<0)
        return -1*a;
    return a;
}
int main(int argc, char *argv[]){
  clock_t t;
  t=clock();

     FILE* file = fopen("assig2a.inp", "r");
     int N = 0;
     fscanf(file,"%d",&N);
     float E = 0.0;
    fscanf(file,"%f",&E);
     float T = 0.0;
     fscanf(file,"%f",&T);
     int P = 0;
     fscanf(file,"%d",&P);
     int L = 0;
    fscanf(file,"%d",&L);

    // fclose(file);
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
//            int fd_diff[P][2];
    for (int i = 0; i <P ; ++i) {
        pipe(fd[i]);
    }
    for (;;) {

//            for (int i = 0; i <P ; ++i) {
//                pipe(fd_diff[i]);
//            }

            int chunk_size=(N-2)/P;

            for (pi = 0; pi < P; pi++) {
//                printf("child number : %d", pi);
                cid = fork();
                if (cid == 0) {

                    diff = 0.0;
                    if (pi != P - 1) {
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
//                        if (count==10) {
//                            for (int i = 0; i < chunk_size * (N - 2) + 1; ++i) {
//                                printf("%f ", w_child[i]);
//                            }
//                            printf("\n");
//                        }
//
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

//                        if (count==0) {
//                            for (int i = 0; i <(N - 2 - chunk_size * pi) * (N - 2) + 1; ++i) {
//                                printf("%f ", w_child[i]);
//                            }
//                            printf("\n");
//                        }
                    }
                    exit(1);
                }
            }
                    diff = 0;
                    for (int pid = 0; pid < P; ++pid) {

                        if (pid != P - 1) {
                            float new_w[chunk_size * (N - 2)+1];
                            read(fd[pid][0], &new_w, sizeof(new_w));

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
                            read(fd[pid][0], &new_w, sizeof(new_w));
//                            printf("%d\n",i);
                            for (int i = 1 + chunk_size * pid; i <= N - 2; ++i) {
                                for (int j = 1; j < N - 1; ++j) {
                                    u[i][j] = new_w[(i-1 - chunk_size * pid) * (N - 2) + j-1];
                                }
                            }

                            float diff_child;
                            diff_child = new_w[(N - 2 - chunk_size * pid) * (N - 2)];
                            if (diff_child > diff) diff = diff_child;
                        }
                    }

                    count++;
                    if (diff <= E || count > L) {
                        break;
                    }


}






    for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++)
                printf("%d ", ((int) u[i][j]));
            printf("\n");
    }
t=clock()-t;
double t2=((double)t)/CLOCKS_PER_SEC;
//printf("Time taken %f\n",t2 );

    exit(1);
}
