#include <iostream>
#include <vector>
#include <limits>
#include <cstdlib>
#include <algorithm>

using namespace std;

/*
  Algorithm works like this:
  
  First place the listeners and towers in a sorted list.We assume listeners and towers are presorted. We use a merge similar to that in merge sort to combine them into one sorted array Identifiable by a char telling whether it is a Listener or a tower.

  <1-------4---------5----------8-----------11-------15----------20-->
   l       t         l          t           l        t            l
  Visit a Listeners, look to see what the closes tower near it is by checking to the left and right of the list. Update the smallest distance
  needed bassed on the closest tower found. Use max values case where a listener doesn't have a left or right tower

  

 */

auto mergeArrays(const std::vector<int> &l, const std::vector<int> &t) ->std::vector<pair<int,char>> {
  std::vector<pair<int,char>> merged;

    auto itl = l.begin();
    auto itt = t.begin();

    while(itl < l.end() && itt < t.end()){
      if((*itl) <= (*itt)){
	merged.push_back({(*itl),'l'});
	++itl;
      }else{
	merged.push_back({(*itt),'t'});
	++itt;
      }
      
    }
    
    while(itl < l.end()){
      merged.push_back({(*itl),'l'});
      ++itl;
    }
    while(itt < t.end()){
      merged.push_back({(*itt),'t'});
      ++itt;
    }
    return merged;
  
}


int main() {

  cout<<"Daily coding 314"<<endl;

  vector<int> listeners = {1,5,11,20};
  vector<int> towers = {4,8,15};

  // Assumes listeners and towers are pre sorted. need to run a sort on each if they are not.
  vector<pair<int,char>> minRangeList = mergeArrays(listeners,towers);

  int left = std::numeric_limits<int>::max();
  int right = std::numeric_limits<int>::max();
  int minRange = std::numeric_limits<int>::min();

 
  for(unsigned int i = 0; i < minRangeList.size(); ++i){
    if(minRangeList[i].second == 'l'){//We have a listener, lets calculate it's min distance to a tower
      for(int j  = i-1; j >0; --j){
	if(minRangeList[j].second == 't'){
	  //Found a tower, update left distance
	  left = minRangeList[i].first - minRangeList[j].first;
	  break;//Can leave after first tower
	}
      }

      for(unsigned int j = i+1; j < minRangeList.size(); ++j){
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
