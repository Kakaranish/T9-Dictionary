#include "Libs.h"
#include "Trie.h"

int main(int argc, char * argv[]) {
	/*
		2 -> abc
		3 -> def
		4 -> ghi
		5 -> jkl
		6 -> mno
		7 -> pqrs
		8 -> tuv
		9 -> wxyz
	*/
	Trie trie;
	if (trie.prepareDictionary("words10k.txt"))
		std::cout << "Poprawnie wczytano slownik!" << std::endl;

	std::string phrase;
	while (1) {
		char c = _getch();
		if (c >= '0' && c <= '9') {
			phrase += c;

			system("cls");
			std::cout << phrase << std::endl;

			trie.showStartingWith(phrase);
		}
		if (c == '\b' && phrase.length() > 0) {			
			phrase = phrase.substr(0, phrase.size() - 1);
			
			system("cls");
			std::cout << phrase << std::endl;
			
			if (phrase.size() >= 1) 
				trie.showStartingWith(phrase);
		}
		if (c == 27)
			return 0;
	}
	return 0;
}