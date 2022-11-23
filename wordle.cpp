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
    const std::string& in,
    std::string& floating,
    const std::set<std::string>& dict, 
    std::set<std::string>& potential_set,
    std::string str,
    int count);

// Definition of primary wordle function
std::set<std::string> wordle(
    const std::string& in,
    const std::string& floating,
    const std::set<std::string>& dict)
{
    // Add your code here
    std::set<std::string> potential_set;
    int dash = 0;//count for dash
    for (int i=0; i<(int)in.length(); i++){
      if (in[i] == '-') {
        dash++;
      }
    }
    std::string temp_floating = floating;
    wordle_helper(in, temp_floating, dict, potential_set, "", dash);
    return potential_set;
}

// Define any helper functions here
void wordle_helper(
    const std::string& in,
    std::string& floating,
    const std::set<std::string>& dict, 
    std::set<std::string>& potential_set,
    std::string str,
    int count)
{
  //TODO
  if (str.size() == in.size()) {//no next position
    if (floating.size() == 0) {
      if (dict.find(str) != dict.end()) {
        potential_set.insert(str);
      }
    }
  }
  else if (in[str.size()] != '-') {//next position is known
    char letter = in[str.size()];
    wordle_helper(in, floating, dict, potential_set, str+letter, count);
  }
  else {//next position == '-'
    std::string potential_str = "abcdefghijklmnopqrstuvwxyz";
    count -= 1;
    for (std::string::iterator it=floating.begin(); it!=floating.end(); ++it){
      char letter = *it;
      floating.erase(it);
      wordle_helper(in, floating, dict, potential_set, str+letter, count);
      floating.insert(it, letter);
      // if (potential_str.find(letter)!=potential_str.npos) {
      //   potential_str.erase(potential_str.begin()+potential_str.find(letter));
      // }
    }
    if (count >= int(floating.size())) {
      for (std::string::iterator it=potential_str.begin(); it!=potential_str.end(); ++it) {
        wordle_helper(in, floating, dict, potential_set, str+(*it), count);
      }
    }
  }
  return;
}

