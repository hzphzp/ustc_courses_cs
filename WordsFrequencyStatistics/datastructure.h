#ifndef _DATASTRUCTURE_H
#define _DATASTRUCTURE_H
#define MAXINITLENGTH 3010349
#define PHRASELENGTH 16785407
//#define EMERGENCYLENGTH 10
//TODO: to think about whether add the safe operation
#include<iostream>
#include<string>
#include<math.h>
using namespace std;
#define LETTERH 64
#define LETTERL 96
#define NUMBER 48
#define DELIMITER 0
int WhatKindChar(char c)
{
    if( ((int)c>=65) && ((int)c<=90) )
        return LETTERH;
    if( ((int)c>=97) && ((int)c<=122) )
        return LETTERL;
    if( ((int)c>=48) && ((int)c<=57) )
        return NUMBER;
    else
        return DELIMITER;
}


class HashTable
{
public:
	int* WordFrequency;
	char(*WordTable)[200];
	int* Formar;
	int* Latter;
	int* PhraseFrequency;
	HashTable()
	{
		WordFrequency = new int[MAXINITLENGTH];
		WordTable = new char[MAXINITLENGTH][200];
		Formar = new int[PHRASELENGTH];
		Latter = new int[PHRASELENGTH];
		PhraseFrequency = new int[PHRASELENGTH];
		for (int i = 0; i < MAXINITLENGTH; i++)
		{
			WordFrequency[i] = 0;
		}
		for (int i = 0; i < PHRASELENGTH; i++)
		{
			PhraseFrequency[i] = 0;
		}
	}

	int getwordnumber()
	{
		int result = 0;
		for (int i = 0; (i < MAXINITLENGTH); i++)
		{
			if (WordFrequency[i] != 0)
				result++;
		}
		return result;
	}
	long getphrasenumber()
	{
		long result = 0;
		for (int i = 0; i < PHRASELENGTH; i++)
		{
			if (PhraseFrequency[i] != 0)
				result++;
		}
		return result;
	}
	void get10words()
	{
		int index[10] = { 0 };
		for (int m = 0; m < 10; m++)
		{
			int flag = 0;
			for (int i = 0; i < MAXINITLENGTH; i++)
			{
				for (int c = 0; c < m; c++)
				{
					if (i == index[c])
						i++;
				}
				if (WordFrequency[i] > WordFrequency[flag])
				{
					flag = i;
				}
			}
			index[m] = flag;
			cout << WordTable[flag] << ": " << WordFrequency[flag] << endl;
		}
	}
	void get10phrases()
	{
		int index[10] = { 0 };
		for (int m = 0; m < 10; m++)
		{
			int flag = 0;
			for (int i = 0; i < PHRASELENGTH; i++)
			{
				for (int c = 0; c < m; c++)
				{
					if (i == index[c])
						i++;
				}
				if (PhraseFrequency[i] > PhraseFrequency[flag])
				{
					flag = i;
				}
			}
			index[m] = flag;
			cout << WordTable[Formar[flag]] << " " << WordTable[Latter[flag]] << ": " << PhraseFrequency[flag] << endl;
		}
	}
	int append(char* sample, int formarindex) {
		char tochangestring[200];//wordcompare doesn't changed, use string like before
		unsigned int index = hash(sample);//TODO
		int c;//speciallly for the char*
		for (int i = 1; WordFrequency[index] != 0 && (wordcompare(WordTable[index], sample, tochangestring)) == false; i++)
		{
			index = (index + i * i) % MAXINITLENGTH;
		}
		if (WordFrequency[index] == 0)
		{
			WordFrequency[index]++;
			//wordcompare(sample, sample, tochangestring);
			for (c = 0; sample[c] != '\0'; c++)
			{
				WordTable[index][c] = sample[c];
			}
			WordTable[index][c] = '\0';
		}
		else if (strcmp(tochangestring, WordTable[index]) == 0)
		{
			WordFrequency[index]++;
		}
		else if (strcmp(tochangestring, WordTable[index]) != 0)
		{
			WordFrequency[index]++;
			//tochangestring = wordcompare(sample, sample);
			for (c = 0; tochangestring[c] != '\0'; c++)
			{
				WordTable[index][c] = tochangestring[c];
			}
			WordTable[index][c] = '\0';
		}
		if (formarindex == -1)
			return index;
		//the append the phrase
		unsigned int phraseindex = hash2(formarindex, index);//hash again
		for (int i = 0; ((PhraseFrequency[phraseindex] != 0) && ((formarindex != Formar[phraseindex]) || (index != Latter[phraseindex]))); i++)
		{
			phraseindex = (phraseindex + i * i) % PHRASELENGTH;
		}
		if (PhraseFrequency[phraseindex] == 0)
		{
			PhraseFrequency[phraseindex]++;
			Formar[phraseindex] = formarindex;
			Latter[phraseindex] = index;
		}
		else
		{
			PhraseFrequency[phraseindex]++;
		}
		return (int)index;
	}
	/*void append(char* a, char* b)
	{
		char tochangestringa[200];//wordcompare doesn't changed, use string like before
		char tochangestringb[200];
		int index = hash(a,b);//TODO
		int c;//speciallly for the char*
		for (int i = 1; ((Frequency[index] != 0) && (((wordcompare(WordTable1[index], a, tochangestringa)) == false) || ((wordcompare(WordTable2[index],b,tochangestringb)) == false))); i++)
		{//have confident when Frequence > 0 and one of the word is different from the original one
			index = (index + i * i) % MAXINITLENGTH;
		}
		if (Frequency[index] == 0)
		{
			Frequency[index]++;
			//wordcompare(sample, sample, tochangestring);
			for (c = 0; a[c] != '\0'; c++)
			{
				WordTable1[index][c] = a[c];
			}
			WordTable1[index][c] = '\0';
			for (c = 0; b[c] != '\0'; c++)
			{
				WordTable2[index][c] = b[c];
			}
			WordTable2[index][c] = '\0';
		}
		else
		{
			Frequency[index]++;
			for (c = 0; tochangestringa[c] != '\0'; c++)
				WordTable1[index][c] = tochangestringa[c];
			WordTable1[index][c] = '\0';
			for (c = 0; tochangestringb[c] != '\0'; c++)
				WordTable2[index][c] = tochangestringb[c];
			WordTable2[index][c] = '\0';
		}
	}*/
	int getwordfrequency(char* sample)
	{
		unsigned int index = hash(sample);
		char tochangestring[200];
		for (int i = 1; (WordFrequency[index] != 0) && (wordcompare(sample, WordTable[index], tochangestring) == false); i++)
		{
			index = (index + i * i) % MAXINITLENGTH;
		}
		return WordFrequency[index];
	}
	int getphrasefrequency(char* formar, char* latter)
	{
		int formarindex = hash(formar);
		char tochangestring[200];
		for (int i = 1; (WordFrequency[formarindex] != 0) && (wordcompare(formar, WordTable[formarindex], tochangestring) == false); i++)
		{
			formarindex = (formarindex + i * i) % MAXINITLENGTH;
		}
		int latterindex = hash(latter);
		for (int i = 1; (WordFrequency[latterindex] != 0) && (wordcompare(latter, WordTable[latterindex], tochangestring) == false); i++)
		{
			latterindex = (latterindex + i * i) % MAXINITLENGTH;
		}
		int phraseindex = hash2(formarindex, latterindex);//hash again
		for (int i = 0; ((PhraseFrequency[phraseindex] != 0) && ((formarindex != Formar[phraseindex]) || (latterindex != Latter[phraseindex]))); i++)
		{
			phraseindex = (phraseindex + i * i) % PHRASELENGTH;
		}
		return PhraseFrequency[phraseindex];
	}
	/*int getfrequency(char* a, char* b)
	{
		int index = hash(a, b);
		char tochangestringa[200];
		char tochangestringb[200];
		for (int i = 1; ((Frequency[index] != 0) && (((wordcompare(WordTable1[index], a, tochangestringa)) == false) || ((wordcompare(WordTable2[index], b, tochangestringb)) == false))); i++)
		{
			index = (index + i * i) % MAXINITLENGTH;
		}
	}*/
private:
	/*unsigned int hash(char* str)
	{
		unsigned int hash = 1315423911;
		unsigned int i = 0;
		for (i = 0; str[i] != '\0';i++)
		{
			hash ^= ((hash << 5) + ((int)(*str)-WhatKindChar(*str)) + (hash >> 2));
		}
		hash = hash % MAXINITLENGTH;
		return hash;
	}*/
	unsigned int hash(char* sample)
	{//TODO: to pay attention on the loop bound
		long long result = 0;
		unsigned int i, j, m;
		int samplelength;
		for (samplelength = 0; sample[samplelength] != '\0'; samplelength++);//get the length of sample
		for (j = samplelength - 1; (j > 0) && (WhatKindChar(sample[j]) == NUMBER); j--);
		for (m = 0; m <= j; m++)
		{
			result += (((int)sample[m] - WhatKindChar(sample[m]))) * (unsigned int)pow(13, m);
		}
		result = result % MAXINITLENGTH;
		return (int)result;

	}
	unsigned int hash2(int formarindex, unsigned int latterindex)
	{
		unsigned phraseindex = (unsigned int)formarindex * 7 + latterindex * 23;
		phraseindex = phraseindex & PHRASELENGTH;
		return (int)phraseindex;
	}
	/*int hash(char* a, char* b)
	{
		long long result = 0;
		int alen,blen;
		int aeffect, beffect;//to mark the last effective locate in the word
		int m;
		for (alen = 0; a[alen] != '\0'; alen++);//get the length of sample
		for (blen = 0; b[blen] != '\0'; blen++);
		for (aeffect = alen - 1; (aeffect > 0) && (WhatKindChar(a[aeffect]) == NUMBER); aeffect--);
		for (beffect = blen - 1; (beffect > 0) && (WhatKindChar(b[beffect]) == NUMBER); beffect--);
		for (m = 0; m <= aeffect; m++)
		{
			result += ((int)a[m] - WhatKindChar(a[m])) * 16 ^ m;
		}
		for (m = 0; m <= beffect; m++)
		{
			result += ((int)b[m] - WhatKindChar(b[m])) * 16 ^ m;
		}
		result = result % MAXINITLENGTH;
		return (int)result;
	}*/

	bool wordcompare(char* a, char* b, char *p)
	{/*
		this function is to compare a and b to see if they are the same wordorphrase of the
		if they are not the same , the function will return a empty string: std:string()/""
		if they are the same , the function will return a string to represent the one between them with higher rank in priority
	 */
		int c;//counte for char*
		int alen, blen;
		for (alen = 0; a[alen] != '\0'; alen++);
		for (blen = 0; b[blen] != '\0'; blen++);

		int wi, wj, wm;
		for (wi = alen - 1; (wi > 0) && (WhatKindChar(a[wi]) == NUMBER); wi--);
		for (wj = blen - 1; (wj > 0) && (WhatKindChar(b[wj]) == NUMBER); wj--);
		if (wi != wj)
			return false;//return a empty string ""
		else
		{
			for (wm = 0; (wm <= wi) && ((a[wm] - WhatKindChar(a[wm]))== (b[wm] - WhatKindChar(b[wm]))); wm++);//find the place starting to be different
			if (wm <= wi)
			{//is different in fommer part, return a empty string ""
				return false;
			}
			else
			{//is the same word
				if (strcmp(a, b) > 0)
				{
					for (c = 0; c < blen; c++)
						p[c] = b[c];
					p[c] = '\0';
				}
				else
				{
					for (c = 0; c < alen; c++)
						p[c] = a[c];
					p[c] = '\0';
				}
				return true;
			}
		}
	}
};

/*class TwoQueue
{
public:
	char item[2][200];
	void enqueue(char* sample)
	{
		int samplelength;
		int c;
		for (samplelength = 0; sample[samplelength] != '\0'; samplelength++);
		if (empty())
		{
			for (c = 0; c < samplelength; c++)
				item[0][c] = sample[c];
			item[0][c] = '\0';
		}
		else
		{
			for (c = 0; c < samplelength; c++)
				item[1][c] = sample[c];
			item[1][c] = '\0';
		}
	}
	void dequeue(char* p)
	{
		int c, len0, len1;
		for (len0 = 0; item[0][len0] != '\0'; len0++);
		for (len1 = 0; item[0][len1] != '\0'; len1++);
		for (c = 0; c < len0; c++)
			p[c] = item[0][c];
		p[c] = '\0';
		for (c = 0; c < len1; c++)
			item[0][c] = item[1][c];
		item[0][c] = '\0';
		item[1][0] = '\0';
	}
	bool empty()
	{
		return (item[0][0] == '\0');
	}
};*/

#endif