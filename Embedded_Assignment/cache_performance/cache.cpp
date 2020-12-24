#include <stdio.h>
#include <stdlib.h>
#include <time.h>


// Define a square must be a multiple of 3
#define N_TILES 600
#define ITERATIONS 300

int *ptr = NULL;
int random_index[N_TILES*N_TILES] = {0};
int naive_index[N_TILES*N_TILES] = {0};
int optimized_index[N_TILES*N_TILES] = {0};


void print_table(int table[N_TILES*N_TILES]){
    int i,j;
    for(i = 0; i < N_TILES; i++){
        for(j = 0; j < N_TILES; j++){
            printf(" %d ", table[i*N_TILES + j]);
        }
        printf("\n");
    }
}

void print_table_bool(bool table[N_TILES*N_TILES]){
    int i,j;
    for(i = 0; i < N_TILES; i++){
        for(j = 0; j < N_TILES; j++){
            printf(" %d", *(table + *(ptr + i*N_TILES + j)));
        }
        printf("\n");
    }
}

void create_vehicle(bool table[N_TILES*N_TILES]){
    *(table + *(ptr + 2*N_TILES)) = true;
    *(table + *(ptr + 2*N_TILES + 1)) = true;
    *(table + *(ptr + 2*N_TILES + 2)) = true;
    *(table + *(ptr + 1*N_TILES + 2)) = true;
    *(table + *(ptr + 1)) = true;
}



void initialize_data() {
  int a, b;
  for (a = 0; a < N_TILES; a++) {
    for (b = 0; b < N_TILES; b++) {
      random_index[a*N_TILES + b] = a*N_TILES + b;
      naive_index[a*N_TILES + b] = a*N_TILES + b;
      optimized_index[a*N_TILES + b] = (a / 3) * (3 * N_TILES) + 9 * (b / 3) + 3*(a % 3) + (b % 3);
    }
  }

  for (int a = N_TILES*N_TILES - 1; a >= 0; --a){
      //generate a random number [0, n-1]
      b = rand() % (a+1);
      //swap the last element with element at random index
      int temp = *(random_index + a);
      random_index[a] = random_index[b];
      random_index[b] = temp;
  }
}

void update_table_naive(bool table[N_TILES][N_TILES]){
    int aux_table[N_TILES][N_TILES] = {0};
    int i, j;

    //Corner
    aux_table[0][0] = table[1][0] + table[1][1] + table[0][1];
    aux_table[N_TILES - 1][0] = table[N_TILES - 1][1] + table[N_TILES - 2][0] + table[N_TILES - 2][1];
    aux_table[0][N_TILES - 1] = table[0][N_TILES - 2] + table[1][N_TILES - 2] + table[1][N_TILES - 1];
    aux_table[N_TILES - 1][N_TILES - 1] = table[N_TILES - 1][N_TILES - 2] + table[N_TILES - 2][N_TILES - 2] + table[N_TILES - 2][N_TILES - 1];

    //Border except Corner
    for (i = 1; i < N_TILES - 1; i++) {
        aux_table[i][0] = table[i - 1][0] + table[i - 1][1] + table[i][1] + table[i + 1][1] + table[i + 1][0];
        aux_table[i][N_TILES - 1] = table[i - 1][N_TILES - 1] + table[i - 1][N_TILES - 2] + table[i][N_TILES - 2] + table[i + 1][N_TILES - 2] + table[i + 1][N_TILES - 1];
    }

    for (j = 1; j < N_TILES - 1; j++) {
        aux_table[0][j] = table[0][j - 1] + table[1][j - 1] + table[1][j] + table[1][j + 1] + table[0][j + 1];
        aux_table[N_TILES - 1][j] = table[N_TILES - 1][j - 1] + table[N_TILES - 2][j - 1] + table[N_TILES - 2][j] + table[N_TILES - 2][j + 1] + table[N_TILES - 1][j + 1];
    }

    //Interior
    for(i = 1; i < N_TILES - 1; i++){
        for(j = 1; j < N_TILES - 1; j++){
            aux_table[i][j] = table[i-1][j-1] + table[i-1][j] + table[i-1][j+1] + table[i][j+1] + table[i+1][j+1] + table[i+1][j] + table[i+1][j-1] + table[i][j-1];
        }
    }

    //Update table
    for(i = 0; i < N_TILES; i++){
        for(j = 0; j < N_TILES; j++){
            table[i][j] = ((table[i][j] == 1) && (aux_table[i][j] <= 3) && (aux_table[i][j] >= 2)) || ((table[i][j] == 0) && (aux_table[i][j] == 3));
        }
    }
}

void update_table_functional(bool table[N_TILES*N_TILES]){
    int aux_table[N_TILES][N_TILES] = {0};
    int i, j;

    //Corner
    aux_table[0][0] = *(table + *(ptr + N_TILES)) + *(table + *(ptr + N_TILES + 1)) + *(table + *(ptr + 1));
    aux_table[N_TILES - 1][0] = *(table + *(ptr + (N_TILES - 1) * N_TILES + 1)) + *(table + *(ptr + (N_TILES - 2) * N_TILES)) + *(table + *(ptr + (N_TILES - 2) * N_TILES + 1));
    aux_table[0][N_TILES - 1] = *(table + *(ptr + N_TILES - 2)) + *(table + *(ptr + 2*N_TILES - 2)) + *(table + *(ptr + 2*N_TILES - 1));
    aux_table[N_TILES - 1][N_TILES - 1] = *(table + *(ptr + N_TILES * N_TILES - 2)) + *(table + *(ptr + (N_TILES - 2)*N_TILES + N_TILES - 2)) + *(table + *(ptr + (N_TILES - 2)*N_TILES + N_TILES - 1));

    //Border except Corner
    for (i = 1; i < N_TILES - 1; i++) {
      aux_table[i][0] = *(table + *(ptr + (i - 1) * N_TILES)) + *(table + *(ptr + (i - 1) * N_TILES + 1)) + *(table + *(ptr + i * N_TILES + 1)) + *(table + *(ptr + (i + 1) * N_TILES + 1)) + *(table + *(ptr + (i + 1) * N_TILES));
      aux_table[i][N_TILES - 1] = *(table + *(ptr + (i - 1) * N_TILES + N_TILES - 1)) + *(table + *(ptr + (i - 1) * N_TILES + N_TILES - 2)) + *(table + *(ptr + i * N_TILES + N_TILES - 2)) + *(table + *(ptr + (i + 1) * N_TILES + N_TILES - 2)) + *(table + *(ptr + (i + 1) * N_TILES + N_TILES - 1));
    }

    for (j = 1; j < N_TILES - 1; j++) {
        aux_table[0][j] = *(table + *(ptr + j - 1)) + *(table + *(ptr + N_TILES + j - 1)) + *(table + *(ptr + N_TILES + j)) + *(table + *(ptr + N_TILES + j + 1)) + *(table + *(ptr + j + 1));
        aux_table[N_TILES - 1][j] = *(table + *(ptr + (N_TILES - 1) * N_TILES + j - 1)) + *(table + *(ptr + (N_TILES - 2) * N_TILES + j - 1)) + *(table + *(ptr + (N_TILES - 2) * N_TILES + j)) + *(table + *(ptr + (N_TILES - 2) * N_TILES + j + 1)) + *(table + *(ptr + (N_TILES - 1) * N_TILES + j + 1));
    }

    //Interior
    for(i = 1; i < N_TILES - 1; i++){
        for(j = 1; j < N_TILES - 1; j++){
            aux_table[i][j] = *(table + *(ptr + (i - 1) * N_TILES + j - 1)) + *(table + *(ptr + (i - 1) * N_TILES + j)) + *(table + *(ptr + (i - 1) * N_TILES + j + 1)) + *(table + *(ptr + i * N_TILES + j + 1)) + *(table + *(ptr + (i + 1) * N_TILES + j + 1)) + *(table + *(ptr + (i + 1) * N_TILES + j)) + *(table + *(ptr + (i + 1) * N_TILES + j - 1)) + *(table + *(ptr + i * N_TILES + j - 1));
        }
    }

    //Update table
    for(i = 0; i < N_TILES; i++){
        for(j = 0; j < N_TILES; j++){
            *(table + *(ptr + i * N_TILES + j)) = ((*(table + *(ptr + i * N_TILES + j)) == 1) && (aux_table[i][j] <= 3) && (aux_table[i][j] >= 2)) || ((*(table + *(ptr + i * N_TILES + j)) == 0) && (aux_table[i][j] == 3));
        }
    }
}

static clock_t start;

void start_clock() {
  start = clock();
}

float end_clock() {
  const clock_t end = clock();
  const float seconds = (float)(end - start) / CLOCKS_PER_SEC;
  //printf("Runtime: %fs\n", seconds);
  return seconds;
}


/*
* Perform Calculation of N_iterations update of the frame
* given a choice of indexing through ptr. Return the time taken.
*/
float calculate(bool table[N_TILES*N_TILES], int N_iterations) {
    int n_iteration;

    start_clock();

    for (n_iteration = 0; n_iteration < N_iterations; n_iteration++) {
        update_table_functional(table);
    }

    return end_clock();
}



// Perform Scenario
void scenario(bool table[N_TILES*N_TILES]) {
  FILE *pFile = fopen("gnuplot.dat", "w");
  const int nPoints = 30;
  float result_random, result_naive, result_optimized;
  int i;
  for (i = 1; i <= nPoints; ++i) {
    ptr = random_index;
    result_random = calculate(table, 10*i);

    ptr = naive_index;
    result_naive = calculate(table, 10*i);

    ptr = optimized_index;
    result_optimized = calculate(table, 10*i);

    fprintf(pFile, "%d\t%f\t%f\t%f\n", 10*i, result_random, result_naive, result_optimized);
    printf("Current state : %d / %d \n", i, nPoints);
  }
  fclose(pFile);
}

int main(void) {
  bool table[N_TILES*N_TILES] = {0};

  initialize_data();

  scenario(table);

  return 0;
}
