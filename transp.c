#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
//#include <time.h>
void transp(int N, int block){
    float *matrix= malloc(N*N * sizeof(float));
    float *out = malloc(N*N * sizeof(float));
    struct timeval start;
    struct timeval end;
    float timesum =0;
    int t=0;

    for(t=0; t<49; t++){
        for(int i=0; i<N*N; i++){
            matrix[i] = (float)rand()/RAND_MAX*100;
            //printf("%f\n", matrix[i]);
        }
        //printf("test");
        gettimeofday(&start,NULL);
        for(int i =0; i<N; i+= block){
            for(int j=0; j<N; j+= block){
                for(int x=i; x<block+i; x++){
                    for(int y=j; y< block+j; y++){
                        out[y*N+x]=matrix[x*N+y];                
                    }
                }
            }
        }
        gettimeofday(&end,NULL);
 
        /*printf("\n");
        for(int i=0; i<N*N; i++){
        printf("%f\n", out[i]);
        }*/
        //time_t seconds = start.tv_sec;
        //time_t eseconds = end.tv_sec;
        //float seconds = start.tv_sec;
        //float endseconds =end.tv_sec;
        timesum += (float)(end.tv_sec - start.tv_sec) + (float)(end.tv_usec- start.tv_usec)/1000000.0;
    }
    printf("Average runtime: %.3f\n",timesum/(t+1));

}
int main(int argc,char **argv){
	if (argc != 3){
		fprintf(stderr, "Wrong number of command-line arguments\n");
		//usage(argv[0]);
		return -1;
	}
    int N= atoi(argv[1]);
    int block = atoi(argv[2]);
    transp(N,block);
    return 0;
}