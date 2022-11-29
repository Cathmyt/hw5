

#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool schedule_helper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<int>& day_vec,
    int current,
    int row,
    int col
);

// Add your implementation of schedule() and other helper functions here

bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){
        return false;
    }
    sched.clear();
    // Add your code below
    vector<Worker_T> temp = vector<Worker_T>(dailyNeed, 0);
    for (int i=0; i<(int)avail.size(); i++) {
        sched.push_back(temp);
    }
    vector<int> day_vec = vector<int>(avail[0].size(), 0);
    int row = -1;
    int col = avail[0].size()+1;
		int current = 0;
    return schedule_helper(avail, dailyNeed, maxShifts, sched, day_vec, current, row, col);
}

//helper function
bool schedule_helper(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched,
    vector<int>& day_vec,
    int current,
    int row,
    int col
)
{
  //todo
  if (row == (int)avail.size()) {
    return true;
  }
  else if (col >= (int)dailyNeed) {
    row ++;
    col = 0;
    current = 0;
    return schedule_helper(avail, dailyNeed, maxShifts, sched, day_vec, current, row, col);
  }
  else if (current >= (int)avail[0].size()) {
    return false;
  }
  else {
    if ((int)maxShifts > day_vec[current]) {
			if (avail[row][current]!=0) {
				sched[row][col] = current;
				day_vec[current] ++;
        if (schedule_helper(avail, dailyNeed, maxShifts, sched, day_vec, current+1, row, col+1)) {
          return true;
        }
				else {
					sched[row][col] = -1;
					day_vec[current] --;
				}
			}
    }
		current ++;
		return schedule_helper(avail, dailyNeed, maxShifts, sched, day_vec, current, row, col);
  }
  
}



