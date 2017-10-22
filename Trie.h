#pragma once
#include "Libs.h"

struct Node {
	std::map<unsigned, Node*> children;
	std::set<std::string> words;
};

class Trie {
protected:
	std::string wordToDigits(std::string word);
	Node head;
public:
	bool prepareDictionary(std::string path);
	void insert(std::string word);
	void showStartingWith(std::string digits);
};