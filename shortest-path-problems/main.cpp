#include "Graph.h"
#include "Timer.h"
#include <queue>
#include <limits>
#include <algorithm>

using namespace std;


int MAX = 9999;

vector<int> computeShortestPath(Graph g, int node){

  //####implement the Dijkstra’s Algorithm here
  vector<int> d(g.size(), MAX);
  d[node] = 0;

  priority_queue<pair<int,int>, vector<pair<int,int> >, greater<pair<int,int> >> q;
  q.push(pair<int, int>(0, node));

  int u;
  while(!q.empty()) {
    u = q.top().second;
    q.pop();
    for(int z = 0; z < g.size(); z++) {
      if(g.connected(z, u) && d[u] != MAX && d[u] + g.getEdgeWeight(z, u) < d[z]) {
        d[z] = d[u] + g.getEdgeWeight(z, u);
        q.push(pair<int, int>(d[z], z));
      }
    }
  }

  return d;
};

vector<vector<int> > computeAllPairsShortestPath(Graph g){
  //####compute all possible shortest paths by calling the Dijkstra's Algorithm on each pair of nodes
  vector<int> d;
  Matrix result(g.size(), vector<int>(g.size(), -1));

  for(int i = 0; i < g.size(); i++) {
    d = computeShortestPath(g, i);
    for(int j = 0; j < g.size(); j++) {
      result[i][j] = d[j];
    }
  }

  return result;
};

Matrix computeAllPairsShortestPathDynamicProgramming(Graph g){
  //####compute all possible shortest paths by implementing the dynamic programming approach
  Matrix d(g.size(), vector<int>(g.size(), 0));
  
  for(int i = 0; i < g.size(); i++) {
    for(int j = 0; j < g.size(); j++) {
      if(i == j) {
        d[i][j] = 0;
      }
      else if(g.connected(i, j)) {
        d[i][j] = g.getEdgeWeight(i, j);
      }
      else {
        d[i][j] = MAX;
      }
    }
  }

  for(int k = 0; k < g.size(); k++) {
    for(int i = 0; i < g.size(); i++) {
      for(int j = 0; j < g.size(); j++) {
        d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
      }
    }
  }

  return d;
};

bool compareResults(Graph g, Matrix a, Matrix b){

  for(int i=0; i<g.size(); i++){
    for(int j=0; j<g.size(); j++){
      if(a[i][j] != b[i][j]){
        return false;
      }
    }
  }

  return true;
}


int main(){

  //create graph as a random matrix
  // Graph g(1000, 40000);
  // cout << "Graph generated " << endl;

  // //compute shortest path
  // Timer time;
  // time.start();
  // Matrix a = computeAllPairsShortestPath(g);
  // time.stop();
  // cout << "Time with Dijkstra's algorithm = " << time.getElapsedTimeInSec() << endl;

  // //compute all possible shortest paths
  // time.start();
  // Matrix b = computeAllPairsShortestPathDynamicProgramming(g);
  // time.stop();
  // cout << "Time with Dynamic programming  = " << time.getElapsedTimeInSec() << endl;

  // //compute by dynamic programming approach
  // if(compareResults(g,a,b)){
  //   cout << "They are the same" << endl;
  // }
  // else{
  //   cout << "Different" << endl;
  // }

  Graph g(10,10);
  
  Matrix a = computeAllPairsShortestPath(g);
  Matrix b = computeAllPairsShortestPathDynamicProgramming(g);
  
  if(compareResults(g,a,b)){
    cout << "They are the same" << endl;
  }
  else{
    cout << "Different" << endl;
  }
};
