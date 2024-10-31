/**
 * @file anagram_dict.cpp
 * Implementation of the AnagramDict class.
 *
 * @author Matt Joras
 * @date Winter 2013
 */

#include "anagram_dict.h"

#include <algorithm> /* I wonder why this is included... */
#include <fstream>

using std::string;
using std::vector;
using std::ifstream;

/**
 * Constructs an AnagramDict from a filename with newline-separated
 * words.
 * @param filename The name of the word list file.
 */
AnagramDict::AnagramDict(const string& filename)
{
    /* Your code goes here! */
    ifstream wordsFile(filename);
    string word;
    if (wordsFile.is_open()) {
        while (getline(wordsFile, word)) { 
            std::string sorted = word;
            std::sort(sorted.begin(), sorted.end());
            if(dict.find(sorted) != dict.end()) {
                dict[sorted].push_back(word);
            } else {
                std::vector<std::string> s;
                s.push_back(word);
                dict[sorted] = s;
            }
        }
    }
}

/**
 * Constructs an AnagramDict from a vector of words.
 * @param words The vector of strings to be used as source words.
 */
AnagramDict::AnagramDict(const vector<string>& words)
{
    /* Your code goes here! */
    for(size_t i = 0; i < words.size(); i++) {
        std::string word = words[i];
        std::string sorted = word;
            std::sort(sorted.begin(), sorted.end());
            if(dict.find(sorted) != dict.end()) {
                dict[sorted].push_back(word);
            } else {
                std::vector<std::string> s;
                s.push_back(word);
                dict[sorted] = s;
            }
    }
}

/**
 * @param word The word to find anagrams of.
 * @return A vector of strings of anagrams of the given word. Empty
 * vector returned if no anagrams are found or the word is not in the
 * word list.
 */
vector<string> AnagramDict::get_anagrams(const string& word) const
{
    /* Your code goes here! */
    std::string sorted = word;
    std::sort(sorted.begin(), sorted.end());
    auto it = dict.find(sorted);

    if(it != dict.end()) {
        return dict.at(sorted);
    }

    return vector<string>();
}

/**
 * @return A vector of vectors of strings. Each inner vector contains
 * the "anagram siblings", i.e. words that are anagrams of one another.
 * NOTE: It is impossible to have one of these vectors have less than
 * two elements, i.e. words with no anagrams are ommitted.
 */
vector<vector<string>> AnagramDict::get_all_anagrams() const
{
    /* Your code goes here! */
    vector<vector<string>> all_anagrams;

    for(std::pair<std::string, std::vector<std::string>> p : dict) {
        if(p.second.size() >= 2) {
            all_anagrams.push_back(p.second);
        }
    }

    return all_anagrams;
}
