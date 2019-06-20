/* Homework 1 Machine Learning
 * James Garrison
 * Question 2
 * a2.cpp
 */
#include <iostream>
#include <string>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <iomanip>
#include <fstream>
#include <algorithm>

using namespace std;

const int SIZE = 12;

struct Point{
  double x;
  double y;
};

struct Cluster{
  int i;
  int m;

};

struct Point dataPoints[SIZE] = {
  { .x = 2, .y = 2 },
  { .x = 3.01, .y = 2},
  { .x = 4.02, .y = 2},
  { .x = 5.03, .y = 2},
  { .x = 6.04, .y = 2},
  { .x = 7.05, .y = 2},
  { .x = 2, .y = 3.5},
  { .x = 3.01, .y = 3.5},
  { .x = 4.02, .y = 3.5},
  { .x = 5.03, .y = 3.5},
  { .x = 6.04, .y = 3.5},
  { .x = 7.05, .y = 3.5},
};

struct clusterContents{
  vector<Point> clusterPoints;
};

void argmax(int *index, double cluster[SIZE][SIZE], int *I);
void addClusters(struct clusterContents *P, int index, int index1);
double sim(Point o, Point p);
double simLinkage(int i, int m, int j, double cluster[SIZE][SIZE]);
double simComplete(int i, int m, int j, double cluster[SIZE][SIZE]);
void updateMatrix(int i, int m, int type, double cluster[SIZE][SIZE]);
void printResults(vector<Cluster>);

bool reSort(Cluster *a, Cluster *b){
    return a->m < b->m;
}

int main(){

  double clusterLink[SIZE][SIZE];
  double clusterComp[SIZE][SIZE];

  int index[2];
  int I[SIZE]; //keeps track of active clusters
  int I2[SIZE]; //keeps track of active clusters

  vector<Point> set (dataPoints, dataPoints + sizeof(dataPoints) / sizeof(Point) );
  vector<Cluster> resultsLinkage (999);
  vector<Cluster> resultsComplete (999);
  
  clusterContents P[SIZE]; 
  clusterContents P2[SIZE];

  for(int o = 0; o < SIZE; o++){
    P[o].clusterPoints.push_back(set[o]);
    P2[o].clusterPoints.push_back(set[o]);
    for (int p = 0; p < SIZE; p++){
      clusterLink[o][p] = sim(set[o],set[p]);
      clusterComp[o][p] = sim(set[o],set[p]);
    }
    I[o] = 1;
    I2[o] = 1;
  }

  cout << endl << "Running Single:";
  for(int k = 0; k < SIZE - 1; k++){
      double distance=0;
      int i, m;
      argmax(index, clusterLink, I);
      i = index[0];
      m = index[1];

      resultsLinkage[k].i = i;
      resultsLinkage[k].m = m;

      distance = clusterLink[i][m];
      addClusters(P, m, i);
      updateMatrix(i, m, 1, clusterLink);
      I[m] = 0;
  }
   printResults(resultsLinkage);
   
  cout << endl << "Running complete:";
   for(int k = 0; k < SIZE - 1; k++){
      double distance=0;
      int i, m;
      argmax(index, clusterComp, I2);
      i = index[0];
      m = index[1];

      resultsComplete[k].i = i;
      resultsComplete[k].m = m;

      distance = clusterComp[i][m];
      addClusters(P2, m, i);
      updateMatrix(i, m, 2, clusterComp);
      I2[m] = 0;
  }
   printResults(resultsComplete);


   return 0;
}

void argmax(int *index, double cluster[SIZE][SIZE], int *I){
  double min = 999;

  for(int o = 0; o < SIZE; o++){
    for (int p = 0; p < SIZE; p++){
      if(I[o] == 1 && I[p] == 1){
       if((min > cluster[o][p])){
         if (cluster[o][p] > 0){
          min = cluster[o][p];
          index[0] = o;
          index[1] = p;
          }
        }
      }
    }
  }
}

void updateMatrix(int i, int m, int option, double cluster[SIZE][SIZE]){
  double val;
  for(int j = 0; j < SIZE; j++){
    if(m != j && i != j){
      if(option == 1){
         val = simLinkage(i, m, j, cluster);
      }
      else if(option == 2){
         val = simComplete(i, m, j, cluster);
      }
      cluster[i][j] = val;
      cluster[j][i] = val;
    }
  }
}

double sim(Point o, Point p){
  double dx = o.x - p.x;
  double dy = o.y - p.y;
  double distance = sqrt((dx * dx) + (dy * dy));
  return distance;
}

double simLinkage(int i, int m, int j, double cluster[SIZE][SIZE]){
  double min = cluster[i][j];
  if(min > cluster[m][j]){
     min = cluster[m][j];
  }
  return min;
}

double simComplete(int i, int m, int j, double cluster[SIZE][SIZE]){
  double min = cluster[i][j];
  if(min < cluster[m][j]){
     min = cluster[m][j];
  }
  return min;
}

void addClusters(struct clusterContents *P, int index,int index1){
  for( int j = 0; j < P[index].clusterPoints.size(); j++){
    P[index1].clusterPoints.push_back(P[index].clusterPoints.at(j));
  }
}

void printResults(vector<Cluster> results){
  cout << endl << "Results:" << endl;
//  sort(results.begin(), results.end(), pred);
  for(int k = 0; k < SIZE - 1; k++){
    cout << "A" << results[k].m<<"'s cluster is: "<< results[k].i << endl;
  }
}
