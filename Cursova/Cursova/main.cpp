#include <string>
#include <iostream>

using namespace std;


struct Word
{
	char ch;

	Word* nextChar;
};

struct Sentence
{
	Word* word;

	Sentence* nextWord;
};

bool CreateSentenceFromInput(Sentence* Head, string _sentence)
{
	if (_sentence.empty() == true)
	{
		return false;
	}

	Sentence* sentence = Head;
	
	Word* wordHead = new Word();

	Word* p = wordHead;

	for (int i = 0; i < _sentence.length(); ++i)
	{
		if (_sentence.at(i) == ' ')
		{
			if (!wordHead->ch) //Removing white space in front of the sentence
			{
				continue;
			}

			p->nextChar = NULL;
			sentence->word = wordHead;

			Sentence* s = new Sentence();

			sentence->nextWord = s;

			sentence = sentence->nextWord;

			Word* w = new Word();
			
			wordHead = w;

			p = wordHead;
			continue;
		}

		p->ch = _sentence.at(i);

		if (i == _sentence.length() - 1)
		{
			p->nextChar = NULL;
			sentence->word = wordHead;
			sentence->nextWord = NULL;

			return true;
		}


		if (_sentence.at(i + 1) == ' ')
		{			
			continue;
		}

		Word* w = new Word;

		p->nextChar = w;

		p = p->nextChar;
	}
}

bool CompàreWord(Word* Head, string _word)
{
	if (!Head)
	{
		return false;
	}

	Word* word = Head;
	int i = 0;

	while (word)
	{
		if (word->ch != _word.at(i))
		{
			return false;
		}

		word = word->nextChar;
		++i;
	}

	return true;
}

bool DeleteWordInSentenceByString(Sentence* &Head, string _word)
{
	Sentence* sentence = Head;
	
	Sentence* lastWord = NULL;

	while (sentence)
	{
		if (CompàreWord(sentence->word, _word))
		{
			if (!lastWord)
			{
				if (Head->nextWord)
				{
					Head = Head->nextWord;
					return true;
				}

				Head = NULL;
				return true;
			}

			lastWord->nextWord = sentence->nextWord;
			return true;
		}

		lastWord = sentence;
		sentence = sentence->nextWord;
	}

	return false;
}

bool DeleteWordInSentenceByInt(Sentence*& Head, int wordNum)
{
	Sentence* sentence = Head;

	Sentence* lastWord = NULL;

	int br = 1;

	while (sentence)
	{
		if (br == wordNum)
		{
			if (!lastWord)
			{
				if (Head->nextWord)
				{
					Head = Head->nextWord;
					return true;
				}

				Head = NULL;
				return true;
			}

			lastWord->nextWord = sentence->nextWord;
			return true;
		}

		lastWord = sentence;
		sentence = sentence->nextWord;
		++br;
	}

	return false;
}

void ReadSentence(Sentence* Head)
{
	Sentence* sentence = Head;
	Word* word = new Word();

	string finalSentence;

	while (sentence)
	{
		word = sentence->word;
		while (word)
		{
			finalSentence += word->ch;

			word = word->nextChar;
		}

		if (sentence->nextWord)
		{
			finalSentence += ' ';
		}

		sentence = sentence->nextWord;
		
	}

	cout << finalSentence << endl;
}

Word* CreateWordFormString(string input)
{
	Word* wordHead = new Word();
	Word* p = wordHead;

	for (int i = 0; i < input.length(); i++)
	{
		p->ch = input.at(i);

		if (i == input.length() - 1)
		{
			break;
		}

		Word* w = new Word();
		w->nextChar = NULL;

		p->nextChar = w;
		p = w;
	}

	return wordHead;
}

bool EditWordInSentenceByString(Sentence*& Head, string newWord, string oldWord)
{
	Sentence* sentence = Head;

	while (sentence)
	{
		if (CompàreWord(sentence->word, oldWord))
		{
			remove(newWord.begin(), newWord.end(), ' ');

			sentence->word->ch = NULL;
			sentence->word->nextChar = NULL;

			sentence->word = CreateWordFormString(newWord);

			return true;
		}
		sentence = sentence->nextWord;
	}

	return false;
}

bool EditWordInSentenceByInt(Sentence*& Head, string newWord, int oldWordNum)
{
	Sentence* sentence = Head;

	int br = 1;

	while (sentence)
	{
		if (br == oldWordNum)
		{
			remove(newWord.begin(), newWord.end(), ' ');

			sentence->word->ch = NULL;
			sentence->word->nextChar = NULL;

			sentence->word = CreateWordFormString(newWord);

			return true;
		}

		sentence = sentence->nextWord;
		++br;
	}

	return false;
}

bool FindIfWordIsPresentInSentenceByString(Sentence* Head, string word)
{
	Sentence* sentence = Head;

	while (sentence)
	{
		if (CompàreWord(sentence->word, word))
		{
			return true;
		}

		sentence = sentence->nextWord;
	}

	return false;
}

bool FindIfWordIsPresentInSentenceByInt(Sentence* Head, int wordNum)
{
	Sentence* sentence = Head;

	int br = 1;

	while (sentence)
	{
		if (br == wordNum)
		{
			return true;
		}

		sentence = sentence->nextWord;
		++br;
	}

	return false;
}

bool AddWordBeforGivenWordByString(Sentence* &Head, string input, string newWord)
{
	Sentence* sentence = Head;
	Word* wordHead = new Word();
	Word* p = new Word();

	wordHead = CreateWordFormString(newWord);

	Sentence* s = new Sentence();
	s->word = wordHead;

	if (CompàreWord(sentence->word, input))
	{
		s->nextWord = Head;

		Head = s;

		return true;
	}

	while (sentence)
	{
		if (CompàreWord(sentence->nextWord->word, input))
		{			
			s->nextWord = sentence->nextWord;

			sentence->nextWord = s;

			return true;
		}

		sentence = sentence->nextWord;
	}

	return false;
}

bool AddWordAfterGivenWordByString(Sentence* &Head, string input, string newWord)
{
	Sentence* sentence = Head;
	Word* wordHead = new Word();
	Word* p = new Word();

	wordHead = CreateWordFormString(newWord);

	Sentence* s = new Sentence();
	s->word = wordHead;

	while (sentence)
	{
		if (CompàreWord(sentence->word, input))
		{
			s->nextWord = sentence->nextWord;

			sentence->nextWord = s;

			return true;
		}

		sentence = sentence->nextWord;
	}

	return false;
}

bool AddWordBeforGivenWordByInt(Sentence*& Head, int inputNum, string newWord)
{
	Sentence* sentence = Head;
	Sentence* lastWord = NULL;

	Word* wordHead = new Word();
	Word* p = new Word();

	wordHead = CreateWordFormString(newWord);

	Sentence* s = new Sentence();
	s->word = wordHead;

	int br = 1;

	if (br == inputNum)
	{
		s->nextWord = Head;

		Head = s;

		return true;
	}

	while (sentence)
	{
		if (br == inputNum)
		{
			lastWord->nextWord = s;

			s->nextWord = sentence;

			return true;
		}

		lastWord = sentence;
		sentence = sentence->nextWord;

		++br;
	}

	return false;
}

bool AddWordAfterGivenWordByInt(Sentence*& Head, int inputNum, string newWord)
{
	Sentence* sentence = Head;
	Word* wordHead = new Word();
	Word* p = new Word();

	wordHead = CreateWordFormString(newWord);

	Sentence* s = new Sentence();
	s->word = wordHead;

	int br = 1;

	while (sentence)
	{
		if (br == inputNum)
		{
			s->nextWord = sentence->nextWord;

			sentence->nextWord = s;

			return true;
		}

		sentence = sentence->nextWord;
		++br;
	}

	return false;
}

bool OptionOneDeleteWord(Sentence*& SentenceHead, string input, char ch)
{
	system("CLS");

	cout << "Sentence: ";

	ReadSentence(SentenceHead);

	cout << endl;
	cout << endl;

	cout << "How do you want to delete the word: " << endl;

	cout << endl;

	cout << "1 - By string" << endl;
	cout << "2 - By int" << endl;

	cout << endl;

	cout << "Choose command: ";

	cin >> ch;

	switch (ch)
	{
	case '1':

		cout << endl;
		cout << endl;

		cout << "Type the word that you want to delete: ";

		cin.ignore(); //ignoring parasite /n.

		cin >> input;

		cout << endl;

		if (DeleteWordInSentenceByString(SentenceHead, input))
		{
			cout << "Operation successful!" << endl;
		}
		else
		{
			cout << "Operation unsuccessful! There is no such word in this sentence!" << endl;
		}

		break;

	case '2':

		cout << endl;
		cout << endl;

		cout << "Type the number of the word that you want to delete: ";

		cin.ignore(); //ignoring parasite /n.

		cin >> input;

		cout << endl;

		if (DeleteWordInSentenceByInt(SentenceHead, stoi(input)))
		{
			cout << "Operation successful!" << endl;
		}
		else
		{
			cout << "Operation unsuccessful! There is no such word in this sentence!" << endl;
		}

		break;

	default:

		cout << endl;
		cout << endl;
		cout << "This command does not exist!" << endl;

		cin.ignore(); //ignoring parasite /n.

		break;
	}

	cout << endl;
	cout << endl;

	cout << "Do you want to continue with this sentence (Y/N): ";

	cin >> ch;

	if (ch == 'y' || ch == 'Y')
	{
		return true;
	}

	return false;

}

bool OptionOneReadSentence(Sentence* SentenceHead, char ch)
{
	cout << endl;
	cout << endl;

	ReadSentence(SentenceHead);

	cout << endl;
	cout << endl;

	cout << "Do you want to continue with this sentence (Y/N): ";

	cin >> ch;

	if (ch == 'y' || ch == 'Y')
	{
		return true;
	}

	return false;
}

bool OptionOneEditWord(Sentence* SentenceHead, string input, char ch)
{
	string newWord;

	system("CLS");

	cout << "Sentence: ";

	ReadSentence(SentenceHead);

	cout << endl;
	cout << endl;

	cout << "How do you want to edit the word: " << endl;

	cout << endl;

	cout << "1 - By string" << endl;
	cout << "2 - By int" << endl;

	cout << endl;

	cout << "Choose command: ";

	cin >> ch;

	switch (ch)
	{
	case '1':

		cout << endl;
		cout << endl;

		cout << "Type the word that you want to edit: ";

		cin.ignore(); //ignoring parasite /n.

		cin >> input;

		cout << endl;

		if (!FindIfWordIsPresentInSentenceByString(SentenceHead, input))
		{
			cout << "Operation unsuccessful! There is no such word in this sentence!" << endl;

			break;
		}

		cout << "Type the new word: ";

		cin >> newWord;

		cout << endl;
		cout << endl;

		if (EditWordInSentenceByString(SentenceHead, newWord, input))
		{
			cout << "Operation successful!" << endl;
		}
		else
		{
			cout << "Operation unsuccessful!" << endl;
		}

		break;

	case '2':

		cout << endl;
		cout << endl;

		cout << "Type the number of the word that you want to edit: ";

		cin.ignore(); //ignoring parasite /n.

		cin >> input;

		cout << endl;

		if (!FindIfWordIsPresentInSentenceByInt(SentenceHead, stoi(input)))
		{
			cout << "Operation unsuccessful! There is no such word in this sentence!" << endl;

			break;
		}

		cout << "Type the new word: ";

		cin >> newWord;

		cout << endl;
		cout << endl;

		if (EditWordInSentenceByInt(SentenceHead, newWord, stoi(input)))
		{
			cout << "Operation successful!" << endl;
		}
		else
		{
			cout << "Operation unsuccessful!" << endl;
		}

		break;

	default:

		cout << endl;
		cout << endl;
		cout << "This command does not exist!" << endl;

		cin.ignore(); //ignoring parasite /n.

		break;
	}

	cout << endl;
	cout << endl;

	cout << "Do you want to continue with this sentence (Y/N): ";

	cin >> ch;

	if (ch == 'y' || ch == 'Y')
	{
		return true;
	}

	return false;
}

bool OptionOneAddWord(Sentence*& SentenceHead, string input, char ch)
{
	string newWord;

	system("CLS");

	cout << "Sentence: ";

	ReadSentence(SentenceHead);

	cout << endl;
	cout << endl;

	cout << "How do you want to add the word: " << endl;

	cout << endl;

	cout << "1 - By string" << endl;
	cout << "2 - By int" << endl;

	cout << endl;

	cout << "Choose command: ";

	cin >> ch;

	switch (ch)
	{
	case '1':

		cout << endl;
		cout << endl;

		cout << "Where do you want to add the word: " << endl;

		cout << endl;

		cout << "1 - Before given word" << endl;
		cout << "2 - After given word" << endl;

		cout << endl;

		cout << "Choose command: ";

		cin >> ch;

		cout << endl;
		cout << endl;

		switch (ch)
		{
		case '1':

			cout << "Type the word before which you want to add the new word: ";

			cin >> input;

			if (!FindIfWordIsPresentInSentenceByString(SentenceHead, input))
			{
				cout << "Operation unsuccessful! There is no such word in this sentence!" << endl;

				break;
			}

			cout << endl;

			cout << "Type the word that you want to add: ";

			cin >> newWord;

			cout << endl;
			cout << endl;

			if (AddWordBeforGivenWordByString(SentenceHead, input, newWord))
			{
				cout << "Operation successful!" << endl;
			}
			else
			{
				cout << "Operation unsuccessful!" << endl;
			}
			break;

		case '2':

			cout << "Type the word after which you want to add the new word: ";

			cin >> input;

			if (!FindIfWordIsPresentInSentenceByString(SentenceHead, input))
			{
				cout << "Operation unsuccessful! There is no such word in this sentence!" << endl;

				break;
			}

			cout << endl;

			cout << "Type the word that you want to add: ";

			cin >> newWord;

			cout << endl;
			cout << endl;

			if (AddWordAfterGivenWordByString(SentenceHead, input, newWord))
			{
				cout << "Operation successful!" << endl;
			}
			else
			{
				cout << "Operation unsuccessful!" << endl;
			}
			break;

		default:

			cout << endl;
			cout << endl;
			cout << "This command does not exist!" << endl;

			cin.ignore(); //ignoring parasite /n.

			break;
		}

		break;

	case '2':

		cout << endl;
		cout << endl;

		cout << "Where do you want to add the word: " << endl;

		cout << endl;

		cout << "1 - Before given word" << endl;
		cout << "2 - After given word" << endl;

		cout << endl;

		cout << "Choose command: ";

		cin >> ch;

		cout << endl;
		cout << endl;

		switch (ch)
		{
		case '1':

			cout << "Type the number of the word before which you want to add the new word: ";

			cin >> input;

			if (!FindIfWordIsPresentInSentenceByInt(SentenceHead, stoi(input)))
			{
				cout << "Operation unsuccessful! There is no such word in this sentence!" << endl;

				break;
			}

			cout << endl;

			cout << "Type the word that you want to add: ";

			cin >> newWord;

			cout << endl;
			cout << endl;

			if (AddWordBeforGivenWordByInt(SentenceHead, stoi(input), newWord))
			{
				cout << "Operation successful!" << endl;
			}
			else
			{
				cout << "Operation unsuccessful!" << endl;
			}
			break;

		case '2':

			cout << "Type the number of the word before which you want to add the new word: ";

			cin >> input;

			if (!FindIfWordIsPresentInSentenceByInt(SentenceHead, stoi(input)))
			{
				cout << "Operation unsuccessful! There is no such word in this sentence!" << endl;

				break;
			}

			cout << endl;

			cout << "Type the word that you want to add: ";

			cin >> newWord;

			cout << endl;
			cout << endl;

			if (AddWordAfterGivenWordByInt(SentenceHead, stoi(input), newWord))
			{
				cout << "Operation successful!" << endl;
			}
			else
			{
				cout << "Operation unsuccessful!" << endl;
			}
			break;

		default:

			cout << endl;
			cout << endl;
			cout << "This command does not exist!" << endl;

			cin.ignore(); //ignoring parasite /n.

			break;
		}

		break;
	}

	cout << endl;
	cout << endl;

	cout << "Do you want to continue with this sentence (Y/N): ";

	cin >> ch;

	if (ch == 'y' || ch == 'Y')
	{
		return true;
	}

	return false;
}

bool OptionOneSwitchLoop(Sentence*& SentenceHead, string input, char ch)
{
	system("CLS");

	cout << "1 - Delete word" << endl;
	cout << "2 - Read sentence" << endl;
	cout << "3 - Edit word" << endl;
	cout << "4 - Add word" << endl;
	cout << endl;

	cout << "Choose command: ";

	cin >> ch;

	switch (ch)
	{

	case '1':

		return OptionOneDeleteWord(SentenceHead, input, ch);

		break;

	case '2':

		return OptionOneReadSentence(SentenceHead, ch);

		break;

	case '3':

		return OptionOneEditWord(SentenceHead, input, ch);

		break;

	case '4':

		return OptionOneAddWord(SentenceHead, input, ch);

		break;
	default:

		cout << endl;
		cout << endl;
		cout << "This command does not exist!" << endl;

		cin.ignore(); //ignoring parasite /n.

		return true;
		break;
	}
}

void OptionOne()
{
	system("CLS");

	char ch;
	string input;

	Sentence* SentenceHead = new Sentence();

	cout << "Enter sentence: ";

	getline(cin, input);


	if (!CreateSentenceFromInput(SentenceHead, input))
	{
		cout << endl;
		cout << "The text cant be noting!" << endl;

		cin >> ch;
		return;
	}

	ch = 'y';

	while (true)
	{
		if (!OptionOneSwitchLoop(SentenceHead, input, ch))
		{
			break;
		}
	}
}

void main()
{
	char ch;

	while (true)
	{
		system("CLS");

		cout << "1 - Enter one whole sentence." << endl;

		cout << endl;

		cout << "Choose command: ";

		cin >> ch;

		switch (ch)
		{
		case '1':
			cin.ignore(); //ignoring parasite /n.
			OptionOne();
			break;

		default:

			cout << endl;
			cout << endl;
			cout << "This command does not exist!" << endl;

			cin >> ch;
			break;
		}
	}
}