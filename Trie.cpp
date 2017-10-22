#include "Trie.h"


typedef std::map<unsigned, Node*>* MapPointer;
typedef std::map<unsigned, Node*>::iterator ChildrenIterator;


bool Trie::prepareDictionary(std::string path) {
	std::fstream file;

	file.open(path.c_str(), std::ios::in | std::ios::out);
	if (!file.is_open())
		return false;

	std::string line;
	for (std::streampos pos;; pos = file.tellg()) { //na pocz¹tku ka¿dej linijki zapamiêtujemy pozycjê w pliku
		if (!std::getline(file, line))
			break;
		this->insert(line);
	}
	file.close();
	return true;
}


std::string Trie::wordToDigits(std::string word) {
	std::stringstream ss;
	char ch;
	for (unsigned i = 0; i < word.length(); i++) {
		ch = word[i];
		if (ch >= 'a' && ch <= 'c')
			ss << 2;
		else if (ch >= 'd' && ch <= 'f')
			ss << 3;
		else if (ch >= 'g' && ch <= 'i')
			ss << 4;
		else if (ch >= 'j' && ch <= 'l')
			ss << 5;
		else if (ch >= 'm' && ch <= 'o')
			ss << 6;
		else if (ch >= 'p' && ch <= 's')
			ss << 7;
		else if (ch >= 't' && ch <= 'v')
			ss << 8;
		else if (ch >= 'w' && ch <= 'z')
			ss << 9;
	}
	return ss.str();
}

void Trie::insert(std::string word) {
	std::map<unsigned, Node*> *currentNodeChildren = &head.children;
	std::map<unsigned, Node*>::iterator childIterator;

	std::transform(word.begin(), word.end(), word.begin(), ::tolower); //Konwertowanie liter na ma³e
	std::string digits(wordToDigits(word));

	unsigned currDigit;
	bool wordExists = true; //zmienna pomocnicza; zakladamy na poczatku, ze slowo istnieje w drzewie

	for (unsigned i = 0; i < digits.length(); i++) {
		currDigit = digits[i] - '0'; //konwertujemy char ze stringa do liczby dodatniej
	    //sprawdzamy czy wœród dzieci Node'a istnieje szukany Node
		if (wordExists && (childIterator = currentNodeChildren->find(currDigit)) != currentNodeChildren->end()) {
			currentNodeChildren = &childIterator->second->children;

			//je¿eli jesteœmy na ostatniej iteracji pêtli oraz s³owo nie istnieje w zbiorze danego Node'a to dodajemy je
			if (i == digits.length() - 1 && childIterator->second->words.find(word) == childIterator->second->words.end())
				childIterator->second->words.insert(word);
			continue;
		}
		//ta czêœæ kodu zostanie wykonana w przypadku, jeœli nie znaleziono szukanego node'a
		wordExists = false;  //je¿eli jeden z wêz³ów nie istnieje, to znaczy, ¿e kolejne te¿ nie bêd¹ istnia³y
		Node* tNode = new Node; 
		if (i == digits.length() - 1) //je¿eli wêze³, który nie istnieje jest wêz³em ostatnim, to chcemy, aby zawiera³ s³owo
			tNode->words.insert(std::move(word));
		currentNodeChildren->insert(std::pair<unsigned, Node*>(currDigit, tNode));
		currentNodeChildren = &tNode->children;
	}
} 

void Trie::showStartingWith(std::string digits) {
	MapPointer currentNodeChildren = &head.children;
	ChildrenIterator childIterator;

	unsigned currDigit;
	for (unsigned i = 0; i < digits.length(); i++) {
		currDigit = digits[i] - '0';
		if((childIterator = currentNodeChildren->find(currDigit)) == currentNodeChildren->end()){
			std::cout << "Brak podpowiedzi!" << std::endl;
			return;
		}
		currentNodeChildren = &childIterator->second->children;
	}

	std::function<void(MapPointer, ChildrenIterator)> showWords;
	showWords = [&](MapPointer mp, ChildrenIterator ci)->void {
		for (auto const& x : ci->second->words)
			std::cout << std::setw(10) << x ;
		MapPointer t_mp; //temporary
		for (ChildrenIterator x = mp->begin(); x != mp->end(); x++) {
			t_mp = &x->second->children;
			showWords(t_mp, x);
		}
	};

	showWords(currentNodeChildren, childIterator);
}
