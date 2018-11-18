#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
//#include <time.h>
void transpif(int N, int M, int block){
    float *matrix= malloc(N*M * sizeof(float));
    float *out = malloc(N*M * sizeof(float));
    struct timeval start;
    struct timeval end;
    float timesum =0;
    int t=0;

    for(t=0; t<49; t++){
        for(int i=0; i<N*M; i++){
            matrix[i] = (float)rand()/RAND_MAX*100;
            //printf("%f\n", matrix[i]);
        }
        //printf("test");
        gettimeofday(&start,NULL);
        for(int i =0; i<N; i+= block){
            for(int j=0; j<M; j+= block){
                if(i+block-1 >= N && j+block-1 >= M){
                    for(int x=i; x<N; x++){
                        for(int y=j; y<M; y++){
                            out[y*N+x]=matrix[x*M+y];                
                        }
                    }
                }
               else if(i+block-1 >= N){
                    for(int x=i; x<N; x++){
                        for(int y=j; y< block+j; y++){
                            out[y*N+x]=matrix[x*M+y];                
                        }
                    }
                }
               else if(j+block-1 >= M){
                    for(int x=i; x<block+i; x++){
                        for(int y=j; y<M; y++){
                            out[y*N+x]=matrix[x*M+y];                
                        }
                    }
                }
                else{
                    for(int x=i; x<block+i; x++){
                        for(int y=j; y< block+j; y++){
                            out[y*N+x]=matrix[x*M+y];                
                        }
                    }
                }
            }
        }
        gettimeofday(&end,NULL);
 
        /*printf("\n");
        for(int i=0; i<N*M; i++){
        printf("%f\n", out[i]);
        }*/
        timesum += (float)(end.tv_sec - start.tv_sec) + (float)(end.tv_usec- start.tv_usec)/1000000.0;
    }
    printf("Average runtime: %.3f\n",timesum/(t+1));

}
int main(int argc,char **argv){
	if (argc != 4){
		fprintf(stderr, "Wrong number of command-line arguments\n");
		//usage(argv[0]);
		return -1;
	}
    int N= atoi(argv[1]);
    int M = atoi(argv[2]);
    int block = atoi(argv[3]);
    transpif(N,M,block);
    return 0;
}