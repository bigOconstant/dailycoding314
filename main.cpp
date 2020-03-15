#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <algorithm>

using namespace std;

/*
  Algorithm works like this:
  
  First place the listeners and towers in a sorted list. Identifiable by a char telling wether it is a Listener or a tower.

  <1-------4---------5----------8-----------11-------15----------20-->
   l       t         l          t           l        t            l
  Visit a Listeners, look to see what the closes tower near it is by checking to the left and right of the list. Update the smallest distance
  needed bassed on the closest tower found. Use max values case where a listener doesn't have a left or right tower

  

 */


int main() {

  cout<<"Daily coding 314"<<endl;

  vector<int> listeners = {1,5,11,20};
  vector<int> towers = {4,8,15};
  
  vector<pair<int,char>> minRangeList;

 int left = std::numeric_limits<int>::max();
  int right = std::numeric_limits<int>::max();
  int minRange = std::numeric_limits<int>::min();
  
  for(auto it = listeners.begin(); it < listeners.end(); ++it) {
    minRangeList.push_back({(*it),'l'});
  }

  for(auto it = towers.begin(); it < towers.end(); ++it){
    minRangeList.push_back({(*it),'t'});
  }

  
  sort(minRangeList.begin(),minRangeList.end(),[]( const pair<int,char> &a,const  pair<int,char> &b){
	return a.first < b.first;
      });

  for(int i = 0; i < minRangeList.size(); ++i){
    if(minRangeList[i].second == 'l'){//We have a listener, lets calculate it's min distance to a tower
      for(int j  = i-1; j >0; --j){
	if(minRangeList[j].second == 't'){
	  //Found a tower, update left distance
	  left = minRangeList[i].first - minRangeList[j].first;
	  break;//Can leave after first tower
	}
      }

      for(int j = i+1; j < minRangeList.size(); ++j){
	if(left == 5){
	  cout<<"five still here"<<endl;
	}
	if(minRangeList[j].second == 't'){
	  //Found a tower, update right distance
	  right = minRangeList[j].first - minRangeList[i].first;

	  break;
	}
      }
      

      if(left == std::numeric_limits<int>::max()){
	
	if(right > minRange){
	  minRange = right;
	}
      }
      else if(right == std::numeric_limits<int>::max()){
	if(left > minRange){
	  minRange = left;
	}
      }

      else if(std::min(left,right) > minRange){
	minRange = std::min(left,right);
      }

      //Reset values to max for next iteration
      left = std::numeric_limits<int>::max();
      right = std::numeric_limits<int>::max();
      
    }
  }

  cout<<"Min Range:"<<minRange<<endl;
  
  
  return 0;
}
