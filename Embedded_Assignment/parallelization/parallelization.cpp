#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <pthread.h>

#define NUM_THREADS 4
//#define N_TILES 5
#define ITERATIONS 200

const int N_TILES = 150;
static clock_t start;


void update_table(bool table[(N_TILES - 1) * 2][(N_TILES - 1) * 2]){
    int aux_table[(N_TILES - 1) * 2][(N_TILES - 1) * 2] = {0};
    int i, j;

    //Corner
    aux_table[0][0] = table[1][0] + table[1][1] + table[0][1];
    aux_table[(N_TILES - 1) * 2 - 1][0] = table[((N_TILES - 1) * 2) - 1][1] + table[((N_TILES - 1) * 2) - 2][0] + table[((N_TILES - 1) * 2) - 2][1];
    aux_table[0][((N_TILES - 1) * 2) - 1] = table[0][((N_TILES - 1) * 2) - 2] + table[1][((N_TILES - 1) * 2) - 2] + table[1][((N_TILES - 1) * 2) - 1];
    aux_table[((N_TILES - 1) * 2) - 1][((N_TILES - 1) * 2) - 1] = table[((N_TILES - 1) * 2) - 1][((N_TILES - 1) * 2) - 2] + table[((N_TILES - 1) * 2) - 2][((N_TILES - 1) * 2) - 2] + table[((N_TILES - 1) * 2) - 2][((N_TILES - 1) * 2) - 1];

    //Border except Corner
    for (i = 1; i < ((N_TILES - 1) * 2) - 1; i++) {
        aux_table[i][0] = table[i - 1][0] + table[i - 1][1] + table[i][1] + table[i + 1][1] + table[i + 1][0];
        aux_table[i][((N_TILES - 1) * 2) - 1] = table[i - 1][((N_TILES - 1) * 2) - 1] + table[i - 1][((N_TILES - 1) * 2) - 2] + table[i][((N_TILES - 1) * 2) - 2] + table[i + 1][((N_TILES - 1) * 2) - 2] + table[i + 1][((N_TILES - 1) * 2) - 1];
    }

    for (j = 1; j < ((N_TILES - 1) * 2) - 1; j++) {
        aux_table[0][j] = table[0][j - 1] + table[1][j - 1] + table[1][j] + table[1][j + 1] + table[0][j + 1];
        aux_table[((N_TILES - 1) * 2) - 1][j] = table[((N_TILES - 1) * 2) - 1][j - 1] + table[((N_TILES - 1) * 2) - 2][j - 1] + table[((N_TILES - 1) * 2) - 2][j] + table[((N_TILES - 1) * 2) - 2][j + 1] + table[((N_TILES - 1) * 2) - 1][j + 1];
    }

    //Interior
    for(i = 1; i < ((N_TILES - 1) * 2) - 1; i++){
        for(j = 1; j < ((N_TILES - 1) * 2) - 1; j++){
            aux_table[i][j] = table[i-1][j-1] + table[i-1][j] + table[i-1][j+1] + table[i][j+1] + table[i+1][j+1] + table[i+1][j] + table[i+1][j-1] + table[i][j-1];
        }
    }

    //Update table
    for(i = 0; i < ((N_TILES - 1) * 2); i++){
        for(j = 0; j < ((N_TILES - 1) * 2); j++){
            table[i][j] = ((table[i][j] == 1) && (aux_table[i][j] <= 3) && (aux_table[i][j] >= 2)) || ((table[i][j] == 0) && (aux_table[i][j] == 3));
        }
    }
}

void *update_table_functional_1(void *table_arg){
    int aux_table[N_TILES][N_TILES] = {0};
    int i, j;
    bool *table = NULL;
    table = (bool*) table_arg;
    //Corner
    aux_table[0][0] = *(table + N_TILES) + *(table + N_TILES + 1) + *(table + 1);

    //Border except Corner
    for (i = 1; i < N_TILES - 1; i++) {
      aux_table[i][0] = *(table + (i - 1) * N_TILES) + *(table + (i - 1) * N_TILES + 1) + *(table + i * N_TILES + 1) + *(table + (i + 1) * N_TILES + 1) + *(table + (i + 1) * N_TILES);
    }

    for (j = 1; j < N_TILES - 1; j++) {
        aux_table[0][j] = *(table + j - 1) + *(table + N_TILES + j - 1) + *(table + N_TILES + j) + *(table + N_TILES + j + 1) + *(table + j + 1);
    }

    //Interior
    for(i = 1; i < N_TILES - 1; i++){
        for(j = 1; j < N_TILES - 1; j++){
            aux_table[i][j] = *(table + (i - 1) * N_TILES + j - 1) + *(table + (i - 1) * N_TILES + j) + *(table + (i - 1) * N_TILES + j + 1) + *(table + i * N_TILES + j + 1) + *(table + (i + 1) * N_TILES + j + 1) + *(table + (i + 1) * N_TILES + j) + *(table + (i + 1) * N_TILES + j - 1) + *(table + i * N_TILES + j - 1);
        }
    }

    //Update table
    for(i = 0; i < N_TILES - 1; i++){
        for(j = 0; j < N_TILES - 1; j++){
            *(table + i * N_TILES + j) = ((*(table + i * N_TILES + j) == 1) && (aux_table[i][j] <= 3) && (aux_table[i][j] >= 2)) || ((*(table + i * N_TILES + j) == 0) && (aux_table[i][j] == 3));
        }
    }
    pthread_exit(NULL);

}

void *update_table_functional_2(void *table_arg){
    int aux_table[N_TILES][N_TILES] = {0};
    int i, j;
    bool *table = NULL;
    table = (bool*) table_arg;
    //Corner
    aux_table[0][N_TILES - 1] = *(table + N_TILES - 2) + *(table + 2*N_TILES - 2) + *(table + 2*N_TILES - 1);

    //Border except Corner
    for (i = 1; i < N_TILES - 1; i++) {
        aux_table[i][N_TILES - 1] = *(table + (i - 1) * N_TILES + N_TILES - 1) + *(table + (i - 1) * N_TILES + N_TILES - 2) + *(table + i * N_TILES + N_TILES - 2) + *(table + (i + 1) * N_TILES + N_TILES - 2) + *(table + (i + 1) * N_TILES + N_TILES - 1);
    }

    for (j = 1; j < N_TILES - 1; j++) {
        aux_table[0][j] = *(table + j - 1) + *(table + N_TILES + j - 1) + *(table + N_TILES + j) + *(table + N_TILES + j + 1) + *(table + j + 1);
    }

    //Interior
    for(i = 1; i < N_TILES - 1; i++){
        for(j = 1; j < N_TILES - 1; j++){
            aux_table[i][j] = *(table + (i - 1) * N_TILES + j - 1) + *(table + (i - 1) * N_TILES + j) + *(table + (i - 1) * N_TILES + j + 1) + *(table + i * N_TILES + j + 1) + *(table + (i + 1) * N_TILES + j + 1) + *(table + (i + 1) * N_TILES + j) + *(table + (i + 1) * N_TILES + j - 1) + *(table + i * N_TILES + j - 1);
        }
    }

    //Update table
    for(i = 0; i < N_TILES - 1; i++){
        for(j = 0; j < N_TILES - 1; j++){
            *(table + i * N_TILES + j) = ((*(table + i * N_TILES + j) == 1) && (aux_table[i][j] <= 3) && (aux_table[i][j] >= 2)) || ((*(table + i * N_TILES + j) == 0) && (aux_table[i][j] == 3));
        }
    }
    pthread_exit(NULL);

}

void *update_table_functional_3(void *table_arg){
    int aux_table[N_TILES][N_TILES] = {0};
    int i, j;
    bool *table = NULL;
    table = (bool*) table_arg;
    //Corner
    aux_table[N_TILES - 1][0] = *(table + (N_TILES - 1) * N_TILES + 1) + *(table + (N_TILES - 2) * N_TILES) + *(table + (N_TILES - 2) * N_TILES + 1);


    //Border except Corner
    for (i = 1; i < N_TILES - 1; i++) {
      aux_table[i][0] = *(table + (i - 1) * N_TILES) + *(table + (i - 1) * N_TILES + 1) + *(table + i * N_TILES + 1) + *(table + (i + 1) * N_TILES + 1) + *(table + (i + 1) * N_TILES);
    }

    for (j = 1; j < N_TILES - 1; j++) {
        aux_table[N_TILES - 1][j] = *(table + (N_TILES - 1) * N_TILES + j - 1) + *(table + (N_TILES - 2) * N_TILES + j - 1) + *(table + (N_TILES - 2) * N_TILES + j) + *(table + (N_TILES - 2) * N_TILES + j + 1) + *(table + (N_TILES - 1) * N_TILES + j + 1);
    }

    //Interior
    for(i = 1; i < N_TILES - 1; i++){
        for(j = 1; j < N_TILES - 1; j++){
            aux_table[i][j] = *(table + (i - 1) * N_TILES + j - 1) + *(table + (i - 1) * N_TILES + j) + *(table + (i - 1) * N_TILES + j + 1) + *(table + i * N_TILES + j + 1) + *(table + (i + 1) * N_TILES + j + 1) + *(table + (i + 1) * N_TILES + j) + *(table + (i + 1) * N_TILES + j - 1) + *(table + i * N_TILES + j - 1);
        }
    }

    //Update table
    for(i = 0; i < N_TILES - 1; i++){
        for(j = 0; j < N_TILES - 1; j++){
            *(table + i * N_TILES + j) = ((*(table + i * N_TILES + j) == 1) && (aux_table[i][j] <= 3) && (aux_table[i][j] >= 2)) || ((*(table + i * N_TILES + j) == 0) && (aux_table[i][j] == 3));
        }
    }
    pthread_exit(NULL);

}

void *update_table_functional_4(void *table_arg){
    int aux_table[N_TILES][N_TILES] = {0};
    int i, j;
    bool *table = NULL;
    table = (bool*) table_arg;
    //Corner
    aux_table[N_TILES - 1][N_TILES - 1] = *(table + N_TILES * N_TILES - 2) + *(table + (N_TILES - 2)*N_TILES + N_TILES - 2) + *(table + (N_TILES - 2)*N_TILES + N_TILES - 1);

    //Border except Corner
    for (i = 1; i < N_TILES - 1; i++) {
        aux_table[i][N_TILES - 1] = *(table + (i - 1) * N_TILES + N_TILES - 1) + *(table + (i - 1) * N_TILES + N_TILES - 2) + *(table + i * N_TILES + N_TILES - 2) + *(table + (i + 1) * N_TILES + N_TILES - 2) + *(table + (i + 1) * N_TILES + N_TILES - 1);
    }

    for (j = 1; j < N_TILES - 1; j++) {
        aux_table[N_TILES - 1][j] = *(table + (N_TILES - 1) * N_TILES + j - 1) + *(table + (N_TILES - 2) * N_TILES + j - 1) + *(table + (N_TILES - 2) * N_TILES + j) + *(table + (N_TILES - 2) * N_TILES + j + 1) + *(table + (N_TILES - 1) * N_TILES + j + 1);
    }

    //Interior
    for(i = 1; i < N_TILES - 1; i++){
        for(j = 1; j < N_TILES - 1; j++){
            aux_table[i][j] = *(table + (i - 1) * N_TILES + j - 1) + *(table + (i - 1) * N_TILES + j) + *(table + (i - 1) * N_TILES + j + 1) + *(table + i * N_TILES + j + 1) + *(table + (i + 1) * N_TILES + j + 1) + *(table + (i + 1) * N_TILES + j) + *(table + (i + 1) * N_TILES + j - 1) + *(table + i * N_TILES + j - 1);
        }
    }

    //Update table
    for(i = 0; i < N_TILES - 1; i++){
        for(j = 0; j < N_TILES - 1; j++){
            *(table + i * N_TILES + j) = ((*(table + i * N_TILES + j) == 1) && (aux_table[i][j] <= 3) && (aux_table[i][j] >= 2)) || ((*(table + i * N_TILES + j) == 0) && (aux_table[i][j] == 3));
        }
    }
    pthread_exit(NULL);

}

void start_clock() {
  start = clock();
}

float end_clock() {
  const clock_t end = clock();
  const float seconds = (float)(end - start) / CLOCKS_PER_SEC;
  printf("Runtime: %fs\n", seconds);
  return seconds;
}



void calcul(float *value_naive, float *value_threads, int n_interations) {
  pthread_t threads[NUM_THREADS];

  bool table[(N_TILES - 1) * 2][(N_TILES - 1) * 2] = {0};
  bool table_1[N_TILES*N_TILES] = {0};
  bool table_2[N_TILES*N_TILES] = {0};
  bool table_3[N_TILES*N_TILES] = {0};
  bool table_4[N_TILES*N_TILES] = {0};

  int i, j, rc;
  float result;
  void *status;



  start_clock();
  for (i = 0; i < n_interations; i++) {
    rc = pthread_create(&threads[0], NULL, update_table_functional_1, (void *) table_1); // Put index pointer dependant on j
    if (rc) {
     printf("Error:unable to create thread, %d", rc);
     exit(-1);
    }

    rc = pthread_create(&threads[1], NULL, update_table_functional_2, (void *) table_2); // Put index pointer dependant on j
    if (rc) {
     printf("Error:unable to create thread, %d", rc);
     exit(-1);
    }

    rc = pthread_create(&threads[2], NULL, update_table_functional_3, (void *) table_3); // Put index pointer dependant on j
    if (rc) {
     printf("Error:unable to create thread, %d", rc);
     exit(-1);
    }

    rc = pthread_create(&threads[3], NULL, update_table_functional_4, (void *) table_4); // Put index pointer dependant on j
    if (rc) {
     printf("Error:unable to create thread, %d", rc);
     exit(-1);
    }
    for (j = 0; j < NUM_THREADS; j++) {
        pthread_join(threads[j], &status);
    }
  }

  *value_threads = end_clock();
  //printf("Result in time %f", result);

  start_clock();
  for (i = 0; i < n_interations; i++) {
    update_table(table);
  }
  *value_naive = end_clock();

  //pthread_exit(NULL);

}

// Perform Scenario
void scenario() {
  FILE *pFile = fopen("gnuplot150.dat", "w");
  const int nPoints = 30;
  float result_naive, result_threads;
  float *presult_naive = &result_naive, *presult_threads = &result_threads;
  int i;

  for (i = 1; i <= nPoints; ++i) {
    calcul(presult_naive, presult_threads, 100*i);
    fprintf(pFile, "%d\t%f\t%f\n", 100*i, result_naive, result_threads);
    printf("Current state : %d / %d \n", i, nPoints);
  }
  fclose(pFile);
}

int main(void) {
    scenario();
}

