// For debugging
#include <iostream>
// For std::remove
#include <algorithm> 
#include <map>
#include <set>
#include "wordle.h"
#include "dict-eng.h"
using namespace std;


// Add prototypes of helper functions here
void wordle_helper(
    const std::string in,
    const std::string& floating,
    const std::set<std::string>& dict, 
    std::set<std::string>& potential_set);

void counting(std::string in, char c, int& count);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> potential_set;
    wordle_helper(in, floating, dict, potential_set);
    return potential_set;
}

// Define any helper functions here
void counting(std::string temp, char letter, int& count) {
	for (int i=0; i<(int)temp.length(); i++){
    if (temp[i] == letter) {
      count++;
    }
  }
}

void wordle_helper(
    std::string in,
    const std::string& floating,
    const std::set<std::string>& dict, 
    std::set<std::string>& potential_set)
{
  //TODO
  int dash = 0;//count for dash
	counting(in, '-', dash);
  if (dash == 0) {
    //all filled, check floating exist in in
    for (int i=0; i<(int)floating.length(); i++){
      int float_count = 0;
      int in_count = 0;
			char temp_letter = floating[i];
			counting(in, temp_letter, in_count);
      counting(floating, temp_letter, float_count);
      if (float_count > in_count) return;
    }
    std::set<std::string>::iterator it = dict.find(in);
    if(it != dict.end()) potential_set.insert(in);
  }
  else {
    //still have not sure char
    for (int i=0; i<(int)in.length(); i++) {
      if (in[i] == '-') {
        for (char letter = 'a'; letter <= 'z'; letter++) {
          in[i] = letter;
          wordle_helper(in, floating, dict, potential_set);
        }
      }
    }
  }
  return;
}