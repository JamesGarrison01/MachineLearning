/* Homework 1 Machine Learning
 * James Garrison
 * Question 1
 * a1.cpp
 */


#include <iostream>
#include <cstdlib>
#include <vector>
#include <set>
#include <math.h>
#include <time.h>
#include <algorithm>
#include <string>
#include <fstream>
#include <iterator>

using namespace std;

/* DataPoints::Class
 * Takes:
 * Name of the class::String
 * X cordinate of the datapoint::int
 * Y cordinate of the datapoint::int
 * id unique to the data point::int
 * number of the cluster that owns it::int
 *
 * Normal getters and setters
 * overright the < operator to allow assigning
 */
class dataPoints{
   private:
      string name;
      int x;
      int y;
      int idPoint;
      int cluster;


   public:
      dataPoints(){
         x = 0;
         y = 0;
         name = "";
         idPoint = 0;
         cluster = 0;
      }
      dataPoints(int idPoint, int x, int y, string name = ""){
         this->idPoint = idPoint;
         this->name = name;
         this->x = x;
         this->y = y;
         cluster = 0;
      }
      bool operator< (const dataPoints &right) const{
         return x < right.x;
      }
      int getID(){
         return idPoint;
      }
      string getName(){
         return name;
      }
      int getx(){
         return x;
      }
      int gety(){
         return y;
      }
      void setx(int x){
         this->x = x;
      }
      void sety(int y){
         this->y = y;
      }
      int getidPoint(){
         return idPoint;
      }
      int getCluster(){
         return cluster;
      }
      void setCluster(int cluster){
         this->cluster = cluster;
      }
};
/* Argmin
 * Takes:
 * x::set<dataPoints>
 * y::set<dataPoints>
 *
 *returns set<dataPoints>
 */
set<dataPoints> argMin(set<dataPoints> x, set<dataPoints> y);

/*CheckClusters
 * Takes: 
 * A which is the original dataset::set<dataPoints>
 * clusCent which is the current clusters center::set<dataPoints>
 *
 *Compares the datapoints to the centers and see if there needs to be a new center
 *returns the new centers to be checked if they changed
 */
set<dataPoints> checkClusters(set<dataPoints> A, set<dataPoints> clusCent);

/*checkChange
 * Takes:
 *clusCent which is the current clusters centers::set<dataPoints>
 *newCent which is the new clusters centers::set<dataPoints>
 *
 * Checks to see if the centers changed and returns a flag
 */
bool checkChange(set<dataPoints> clusCent, set<dataPoints> newCent);

/*printCluster
 * takes:
 * S which is the current dataset::set<dataPoints> 
 *
 * prints out the current dataset to screen
 */
void printCluster(set<dataPoints> S);



int main(int argc, char **argv){
  //if no K is provided gives an error
  if(argc < 2){
     cout << "Error: no k provided\n";
     return 1;
  }
  int k = atoi(argv[1]); //sets k from terminal
  set<dataPoints> S;
  set<dataPoints> subS;
  set<dataPoints> A;
  set<dataPoints> clusCent;
  set<dataPoints> clusNew;
  int sSize = 0;
  int iRand = rand() % 10 + 0;
  int iRand2 = rand() % 10 + 0;

  //manually sets datapoints
  dataPoints A1(1, 2, 10, "A1");
  dataPoints A2(1, 2, 5, "A2");
  dataPoints A3(1, 8, 4, "A3");
  dataPoints A4(1, 5, 8, "A4");
  dataPoints A5(1, 7, 5, "A5");
  dataPoints A6(1, 6, 4, "A6");
  dataPoints A7(1, 1, 2, "A7");
  dataPoints A8(1, 4, 9, "A8");

  dataPoints R1(1, iRand, iRand2, "R1");

  iRand = rand() % 10 + 0;
  iRand2 = rand() % 10 + 0;
  dataPoints R2(1, iRand, iRand2, "R2");

  iRand = rand() % 10 + 0;
  iRand2 = rand() % 10 + 0;
  dataPoints R3(1, iRand, iRand2, "R3");
 
  sSize = S.size();
  subS = S;

//  int j = rand() % sSize;

  //inserts the datapoints into the data set
  S.insert(A1);
  S.insert(A2);
  S.insert(A3);
  S.insert(A4);
  S.insert(A5);
  S.insert(A6);
  S.insert(A7);
  S.insert(A8);

  
  set<dataPoints>::iterator it = S.find(A1);
  dataPoints b1 = *it;

  cout << clusCent.size() << endl;
  //round 1: sets the clusters manually
  cout << "\nRound1:\n";
      clusCent.insert(A1);
      clusCent.insert(A7);
      clusCent.insert(A8);

  cout << clusCent.size() << endl;
  //sets all of datapoints  to their respective centers
   S = argMin(S, clusCent);
   
   //assume flag is different
   bool flagChange = true;
   while(flagChange){
      clusNew = checkClusters(S, clusCent); //checks if clusters need to be moved
      flagChange = checkChange(clusCent, clusNew); //checks if  clusters moved
      if(flagChange){
         clusCent = clusNew; //if clusters moved replace old
         S = argMin(S, clusCent); //set datapoints to their respective clusters
        // printCluster(S); //print to check
      }
   }
   printCluster(S); //print to check

  //round 2: sets the clusters manually
  cout << "\nRound2:\n";
  dataPoints temp;
  for(set<dataPoints>::iterator itTemp = clusCent.begin(); itTemp != clusCent.end(); itTemp++){
      temp = *itTemp;
      clusCent.erase(temp);
  }  
      clusCent.insert(A2);
      clusCent.insert(A6);
      clusCent.insert(A8);

//   dataPoints temp;
//   for(set<dataPoints>::iterator itTemp = S.begin(); itTemp != S.end(); itTemp++){
//      temp = *itTemp;
//      temp.setCluster(0);
//   }
  //sets all of datapoints  to their respective centers
   S = argMin(S, clusCent);
   
   //assume flag is different
   flagChange = true;
   while(flagChange){
      clusNew = checkClusters(S, clusCent); //checks if clusters need to be moved
      flagChange = checkChange(clusCent, clusNew); //checks if  clusters moved
      if(flagChange){
         clusCent = clusNew; //if clusters moved replace old
         S = argMin(S, clusCent); //set datapoints to their respective clusters
         //printCluster(S); //print to check
      }
   }
   printCluster(S); //print to check

  cout << "\nRound3:\n";
  for(set<dataPoints>::iterator itTemp = clusCent.begin(); itTemp != clusCent.end(); itTemp++){
      temp = *itTemp;
      clusCent.erase(temp);
  }  
      clusCent.insert(A3);
      clusCent.insert(A5);
      clusCent.insert(A6);

  //sets all of datapoints  to their respective centers
   S = argMin(S, clusCent);
   
   //assume flag is different
   flagChange = true;
   while(flagChange){
      clusNew = checkClusters(S, clusCent); //checks if clusters need to be moved
      flagChange = checkChange(clusCent, clusNew); //checks if  clusters moved
      if(flagChange){
         clusCent = clusNew; //if clusters moved replace old
         S = argMin(S, clusCent); //set datapoints to their respective clusters
         //printCluster(S); //print to check
      }
   }
   printCluster(S); //print to check

  cout << "\nRound4:\n";
  for(set<dataPoints>::iterator itTemp = clusCent.begin(); itTemp != clusCent.end(); itTemp++){
      temp = *itTemp;
      clusCent.erase(temp);
  }  
      clusCent.insert(A2);
      clusCent.insert(A3);
      clusCent.insert(A7);
  
   //sets all of datapoints  to their respective centers
   S = argMin(S, clusCent);
   
   //assume flag is different
   flagChange = true;
   while(flagChange){
      clusNew = checkClusters(S, clusCent); //checks if clusters need to be moved
      flagChange = checkChange(clusCent, clusNew); //checks if  clusters moved
      if(flagChange){
         clusCent = clusNew; //if clusters moved replace old
         S = argMin(S, clusCent); //set datapoints to their respective clusters
         //printCluster(S); //print to check
      }
   }
   printCluster(S); //print to check
  
   cout << "\nRound5:\n";
  for(set<dataPoints>::iterator itTemp = clusCent.begin(); itTemp != clusCent.end(); itTemp++){
      temp = *itTemp;
      clusCent.erase(temp);
  }  
      clusCent.insert(R1);
      clusCent.insert(R2);
      clusCent.insert(R3);
  
   //sets all of datapoints  to their respective centers
   S = argMin(S, clusCent);
   
   //assume flag is different
   flagChange = true;
   while(flagChange){
      clusNew = checkClusters(S, clusCent); //checks if clusters need to be moved
      flagChange = checkChange(clusCent, clusNew); //checks if  clusters moved
      if(flagChange){
         clusCent = clusNew; //if clusters moved replace old
         S = argMin(S, clusCent); //set datapoints to their respective clusters
         //printCluster(S); //print to check
      }
   }
   printCluster(S); //print to check

   return 0;
}

set<dataPoints> argMin(set<dataPoints> s, set<dataPoints> clusCent){
   dataPoints k, j, v;
   set<dataPoints> nSet;
   int x1, y1, x2, y2;
   int cluster = 0;
   int count = s.size();
   int centCount = clusCent.size();
   double distance = 0;
   double distanceOld = 999;
   set<dataPoints>::iterator it = s.begin();
   set<dataPoints>::iterator it2 = clusCent.begin();

   //iterates through datapoints (will check with each cluster)
   for(it = s.begin(); it != s.end(); ++it){
      distanceOld = 999;
      j = *it;
      x2 = j.getx(); //gets clusters x
      y2 = j.gety();//gets clusters y

      //iterates through cluster centers to compare datapoints find
      //which is the closest
      for(it2 = clusCent.begin(); it2 != clusCent.end(); ++it2){
         k = *it2;
         x1 = k.getx();//gets clusters x
         y1 = k.gety();//gets clusters y

         //performs distances formula
         int dx = x2 - x1;
         int dy = y2 - y2;
         distance = sqrt((dx * dx) + (dy * dy));

         //checks if the distance to center is lower than the current
         //no change if they are equal
         if(distance < distanceOld){
            distanceOld = distance;
            j.setCluster(cluster); //stores which cluster  belongs to
         }
         cluster++;
      }
      cluster = 0; //shows cluster number
      nSet.insert(j);
   }
   return nSet;
}

set<dataPoints> checkClusters(set<dataPoints> A, set<dataPoints> clusCent){
   set<dataPoints> newClus;
   set<dataPoints>::iterator it3 = clusCent.begin();
   set<dataPoints>::iterator it = A.begin();
   int j = 0;

   for(it3 = clusCent.begin(); it3 != clusCent.end(); ++it3){
      dataPoints b2 = *it3;
      double meanx = 0;
      double meany = 0;
      double count = 0;
      for(it = A.begin(); it != A.end(); ++it){
         dataPoints b1  = *it;
         if(b1.getCluster() == j){
            meanx = meanx + b1.getx();
            meany = meany + b1.gety();
            count++;
            }
      }
      if(meanx > 0){
         meanx = meanx/count;
         meany = meany/count;
         b2.setx(meanx);
         b2.sety(meany);
         newClus.insert(b2);
      }
      if(j > 3)
         break;
      j++;
   }
   return newClus;
}

bool checkChange(set<dataPoints> clusCent, set<dataPoints> newCent){
   set<dataPoints>::iterator it = clusCent.begin();
   set<dataPoints>::iterator it2 = newCent.begin();
   dataPoints b1, n2;
   bool flagChange = false;

  // for(it = clusCent.begin(); it != clusCent.end(); ++it){
      for(it2 = newCent.begin(); it2 != newCent.end(); ++it2){
         b1 = *it;
         n2 = *it2;
         if(b1.getx() != n2.getx()){
            b1.setx(n2.getx());
            flagChange = true;
         }
         if(b1.gety() != n2.gety()){
            b1.sety(n2.gety());
            flagChange = true;
         }
         it++;
      }
      
   //}
   return flagChange;
}


void printCluster(set<dataPoints> S){ 
   set<dataPoints>::iterator it = S.begin();
   dataPoints b1;

   for(it = S.begin(); it != S.end(); ++it){
      b1 = *it; 
      cout << b1.getName() << "'s cluster: " << b1.getCluster() << endl; 

   }
}
