#include "matrixChain.h"

#include <random>
#include <vector>
#include <iostream>

using namespace std;

MatrixChain::MatrixChain(int* dimensions, int num){

  this->dimensions = dimensions;
  this->num = num;

  for(int i=0;i<num;i++){
    generate_matrix(dimensions[i],dimensions[i+1]);
  }
}

void MatrixChain::generate_matrix(int rows, int cols){
  srand(time(0));

  Matrix matrix(rows, vector<int>(cols,0));
  for (int j=0;j<rows;j++){//row
    for (int k=0;k<cols;k++){//
          matrix[j][k] = rand()%NUM+1;
      }
  }
  chain.push_back(matrix);
}

Matrix MatrixChain::multiply(Matrix a, Matrix b){
  int N = a.size();
  int K = a[0].size();
  int M = b[0].size();

  Matrix result(N, vector<int>(M, 0));
  int sum;

  for(int i = 0; i < N; i++) {
    for(int j = 0; j < M; j++) {
      sum = 0;
      for(int k = 0; k < K; k++) {
        sum += a[i][k] * b[k][j];
      }
      result[i][j] = sum;
    }
  }

  return result;
}

Matrix MatrixChain::dynamicChain(){
  //implement here the optimal approach using the dynamic programming algorithm
  Matrix N(num, vector<int>(num, -1));
  Matrix K(num, vector<int>(num, -1));

  for(int i = 0; i < num; i++) {
    N[i][i] = 0;
  }

  int j, temp;
  for(int b = 1; b < num; b++) {
    for(int i = 0; i < num - b; i++) {
      j = i + b;
      N[i][j] = INT_MAX;
      for(int k = i; k < j; k++) {
        temp = N[i][j];
        N[i][j] = min(N[i][j], N[i][k] + N[k+1][j] + dimensions[i]*dimensions[k+1]*dimensions[j+1]);
        if(N[i][j] < temp) {
          K[i][j] = k;
        }
      }
    }
  }

  Matrix M = chain[0];
  for(int i = 1; i < num; i++) {
    M = multiply(M, chain[i]);
  }

  cout << N[0][num - 1] << " " << K[0][num - 1] << "\n";
  return M;
}
