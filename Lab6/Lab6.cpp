// Lab6.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <string>
#include <unordered_map>
using namespace std;
class Tlumaczenie
{
public:
    string Eng;
    string Pol;
    Tlumaczenie(string Eng,string Pol) :Eng(Eng),Pol(Pol) {}};
class Node
{
public:
	unordered_map<char, Node*> children;
	Tlumaczenie* word;
	char letter;
	void addNode(string englishWord, string polishWord)
	{
		if (word == NULL) {
			word = new Tlumaczenie(englishWord, polishWord);
		}
		else {
			word->Eng = englishWord;
			word->Pol = polishWord;
		}
	}

	Node(char letter) : letter(letter), word(NULL) {

	};
	~Node() {
if (word != NULL) delete word;
	unordered_map<char, Node*>::iterator it = children.begin();
	while (it != children.end())
	{
		delete it->second;
		it++;
	}
	};
};


class Tree
{
private:
	Node* root;
	void printWords(Node* tmpNode) {
		if (tmpNode->word != NULL) {
			printf("%s\n", tmpNode->word->Pol.c_str()); //%s to string; c_str zamienia ze stringa na typ const char*
		}
		//unordered_map<char, unique_ptr<Node> >::iterator it = tmpNode->children.begin(); //inicjalizujemy iterator
		unordered_map<char, Node*>::iterator it = tmpNode->children.begin();
		while (it != tmpNode->children.end())
		{
			printWords(it->second); //drugi element z pary klucz - wartosc (second, czyli wartosc)
			it++;
		}
	}

public:
	Tree() {
		root = new Node('\0'); //'\0' przechowuje puste znaki
	}
	void addNewWord(string englishWord, string polishWord) {
		Node* node = root; //node jest root node'm
		for (int i = 0; i < englishWord.length(); i++) {
			char singleLetter = englishWord[i];
			int index = singleLetter - 'a';
			if (node->children.count(index) == 0) {
				node->children[index] = new Node(singleLetter); //make_unique dziala jak new; jest dla inteligentnych wskaŸników
			}
			node = node->children[index]; //get() pozwala przypisaæ zwykly wskaznik do uniq pointera
		}
		node->addNode(englishWord, polishWord);
	}
	void translate(string englishWord) {
		Node* node = root;
		for (int i = 0; i < englishWord.length(); i++) {
			char singleLetter = englishWord[i];
			int index = singleLetter - 'a';
			if (node->children.count(index) == 0) {
				printf("-\n");
				//cout << "-" << endl;
				return;
			}
			node = node->children[index];
		}
		if (node->word == NULL) {
			printf("-\n");
		}
		else {
			printf("%s\n", node->word->Pol.c_str());
			//cout << node->word->polishWord << endl;
		}
	}
	void findWords(string prefix) {
		Node* node = root;
		for (int i = 0; i < prefix.length(); i++) { //prefix - przedrostek
			char singleLetter = prefix[i];
			int index = singleLetter - 'a';
			if (node->children.count(index) == 0) {
				printf("-\n");
				return;
			}
			node = node->children[index];
		}
		printWords(node);
	}
	~Tree() {
		delete root;
	}
};


int main()
{
	Tree tree;
	char comand;
	string En, Pl;
	while (scanf("%s", &comand) != EOF)
	{
		if (comand == '+')
		{
			cin >> En;
			cin>> Pl;
			tree.addNewWord(En, Pl);
		}
		else if (comand == '?') {
			cin >> En;
			tree.translate(En);

		}
		else if (comand == '*') {
			cin >> En;
			tree.findWords(En);

		}
	}
}

