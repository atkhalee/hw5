 #ifndef RECCHECK
#include <set>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#endif

// add or remove necessary headers as you please
#include "schedwork.h"

using namespace std;

// a constant that can be used to indicate an INVALID 
// worker ID if that is useful to your implementation.
// Feel free to not use or delete.
static const Worker_T INVALID_ID = (unsigned int)-1;


// Add prototypes for any helper functions here
bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t d,
    const size_t m,
    DailySchedule& sched,
    const size_t day,
    const size_t col,
		std::vector<size_t>& shift,
		unsigned int k
	);
//create helper fundtion to create a schedule
//void schedule_maker()
// Add your implementation of schedule() and other helper functions here
//need to implement is valid function to check
bool schedule(
    const AvailabilityMatrix& avail,
    const size_t dailyNeed,
    const size_t maxShifts,
    DailySchedule& sched
)
{
    if(avail.size() == 0U){//0U
        return false;
    }
    sched.clear();
    // Add your code below
    //the employee cannot work more than maxShifts
   
    //new
    //k is the number of workers
    // m = max shifts
    // d dailyneed
    //n is the nummber of days
		//checking how many rowsand columns are in avail
    //filing n by d board//fillingg the matrix with 0 to k-1 (id)
    //availabily work is n by k
    //worker is valid if available, assigned shift is <= m shifts, worker hasn't worked that day already
    
    //3 focus constraints --> if worker is available
    // three loops -->2 for setup, 1 for recursion
    //develop n by d matrix
    //setting up table

    unsigned int n =avail.size(); //number of days 
    unsigned int k = avail[0].size(); //number of workers
    unsigned int d = dailyNeed;
    unsigned int m = maxShifts;
    

/*
nothing
[]

[[] [] [] []]

sched = DailySchedule(size);
foreach day


[[-1 -1 -1]
[-1 -1 -1]
[-1 -1 -11]
]
*/
  sched = DailySchedule();
    for(unsigned int i =0; i < avail.size(); i++)
    {
      //temp vector that creates a rows
      sched.push_back(vector<Worker_T>());
			
      for(unsigned int j =0; j < d; j++)
      {
				//sched[i][j] = INVALID_ID;
				sched[i].push_back(INVALID_ID);
        
      }

    } 
   //vector that holds each worker, and their shfit amount --> starts at 0 and will increase when helper function is called
    std::vector<size_t> shift(k, 0);
    return scheduleHelper(avail, d, m, sched, 0, 0, shift, k);
    //base
    
    // for(unsignd int i = 0; i < sched.size())
    // {

    // }
    //base case
    // if(==avail.size())
    // {
    //   return true;
    // }
    // if(sched[n][d])
    // {
    //   return true;
    // }



}
bool scheduleHelper(
    const AvailabilityMatrix& avail,
    const size_t d,
    const size_t m,
    DailySchedule& sched,
    const size_t day,
    const size_t col,
    std::vector<size_t>& shift,
		unsigned int k
    )
{
  //if (day = avai.size())
  if(day == avail.size())
  {
    return true;
  }
  if(col == d)
  {
    return scheduleHelper(avail, d, m, sched, day+1, 0, shift, k);
  }
	for(unsigned int i =0; i < k; i++)
	{
		//shift.find(i);
		//if worker is not already assigned to day
		//size (vector of size daily need) content you want to filter
    auto x = std::find(sched[day].begin(), sched[day].end(), i);
		//std::<DailySchedule> mysched (sched[day], sched[day]+d)
		//std::<DailySchedule>::iterator it = find(mysched.begin() , mysched.end(), i);

		//= sched[day].find(i);
    //it!= mysched.end()
		if(x != sched[day].end())
		{
			continue; //continue to the next if statement
		}
    
		if(avail[day][i] != 0 && shift[i]< m)
		{
			//assign worker to schedule
			sched[day][col] = i;
			shift[i]++;
			bool result = scheduleHelper(avail, d, m, sched, day, col+1, shift, k);
			if(result == true)
			{
				return true;
			}
      shift[i]--;
      sched[day][col] = INVALID_ID;
			
		}
		// else
		// {
		// 	//backtrack
		// 	scheduleHelper(avail, d, m, sched, day, shift[k]+1, k);
		// }
	}
	return false;

}
// bool scheduleHelper(day, shift)
// {
//   //also need a data strucuture to keep in track of the. shift
//   // if day == n: return true
//   if(day)
//   // if shift == d: return helper(day+1, 0)

//   // loop over workers [0,k)
//     // if avail and less than max shifts and not already assigned to day
//       // assign worker to sched
//       //res = helper(day, shift+1)
//       //if res: return true
//       // backtrack
//   //return false

// }

