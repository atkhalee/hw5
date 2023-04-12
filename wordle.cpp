#ifndef RECCHECK
// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include <string>
#endif

#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here

void wordle_helper(std::string& in, std::string& floating, int count_index, std::set<string>& words, const std::set<std::string>& diction);
// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    //base case
    string inCopy = in;
		string floatingCopy = floating;
		std::set<std::string> words;
		wordle_helper(inCopy, floatingCopy, 0, words, dict);
    
    return words;

}

// Define any helper functions here
void wordle_helper(std::string& in, std::string& floating, int count_index, std::set<string>& words, const std::set<std::string>& diction)
{

//helper does some of the recursive work --> passes in the paramers to develop a set of possible list of words
// in = green letters, right spot, also the entire word with the dashes
//floating = yellow leters, need to index to find the right spot
//count_index = tracking the index of in
//words = new set of strings that are possible words
//dict = letters of the alphabet
    if(count_index == in.size())
    {
				//making sure all floatig characters are used and part of dict
        if(diction.find(in)!= diction.end() && floating.size() ==0)
				{
        	words.insert(in);
        	return;
				}
    }
		//case for the dashes
		else if(in[count_index] == '-')
		{
			//count checks how many are complete (no dahses)
			int count = 0;
			for(int i =count_index+1; i< in.length(); i++)
			{
				if(in[i] !='-')
				{
					count++;
				}
			}
				//checking number of spaces left
				int possibleLeft = in.length() - count_index;
				//letters that are already used
				std::set<char> used;
				for(int i =0; i <floating.size(); i++)
				{
					//floating has same letters used
					if(used.find(floating[i]) != used.end())
					{
						//next letter in the index
						continue;
					}
					in[count_index] = floating[i];
					string floating_temp = floating;
					//remove from floating as we do not want to use it again
					floating_temp.erase(i,1);
					wordle_helper(in, floating_temp, count_index+1, words, diction);
					//insert usee letters into the word set
					used.insert(floating[i]);
					//reset back to '-'
					in[count_index] = '-';
				}
				//checking if there are possibiliotes left even after useing up all the floating
				if(possibleLeft >  floating.size()+count)
				{
					for(char letter = 'a'; letter <= 'z'; letter++)
					{
						if(used.find(letter) != used.end())
						{
							continue;
							//next index
						}
						in[count_index] = letter;
						wordle_helper(in, floating, count_index+1, words, diction);
						in[count_index] = '-';
					}
				}
			}
			else
			{
				wordle_helper(in, floating, count_index+1, words, diction);
			
			}
			
}
