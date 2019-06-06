/*
this function is for computer and statistic the words frequency in the file(transfered to
the memory buffer
and in this function we must free the memory of buffer to avoid the memory overflow
*/

#include"functions.h"
#include"datastructure.h"
#include<iostream>
#include<stdlib.h>
HashTable WordTable;//TODO
//HashTable PhraseTable(true);   //TODO
//TwoQueue PhraseQueue;   //TODO
long SumofChar = 0;
long SumofWord = 0;
long Sumofline = 0;
long SumofPhrase = 0;
int formarindex = -1;//coout for the phrase
using namespace std;
void statistics(char * buffer, long size)
{ 
	formarindex = -1;
	char sample[200] = { '\0' };//a sample word in the proceeding of finding words
	int samplelength = 0;
	int charkind;//a mark to show what kind of char it is
	//int c;//specially counting for char*
	for (int i = 0; i < size; i++)
	{
		//whole iterate to traverse the file
		charkind = WhatKindChar(*(buffer + i));//TODO:add accumulate SumChar and Sumofline in this function
		if ((int)*(buffer + i) >= 32 && (int)*(buffer + i) <= 126)
			SumofChar++;
		if (*(buffer + i) == '\n')
			Sumofline++;
		if ( samplelength < 4 && (charkind == LETTERH || charkind == LETTERL))
		{
			sample[samplelength] = *(buffer + i);
			samplelength++;
			sample[samplelength] = '\0';
			continue;
		}
		if ( samplelength >= 4 && (charkind != DELIMITER))
		{
			sample[samplelength] = *(buffer + i);
			samplelength++;
			sample[samplelength] = '\0';
			continue;
		}
		else
		{
			if (samplelength< 4)
			{
				sample[0] = '\0';
				samplelength = 0;
				continue;
			}
			else
			{//have found a word 
				//Low(sample);//TODO
				formarindex = WordTable.append(sample, formarindex);
				SumofWord++;
				SumofPhrase++; 
				sample[0] = '\0';
				samplelength = 0;
			}
		}
	}
	free(buffer);
}

void Low(char* sample)
{
    for(int i =0; sample[i] != '\0'; i++)
    {
        if(WhatKindChar(sample[i]) == LETTERH)
            sample[i] += ('a' - 'A');
    }
}


void outputresult()
{
	cout <<"word(same): "<< SumofWord << endl;
	cout << "word(diff): " << WordTable.getwordnumber() << endl;
	cout << "Phrase(same):" << SumofPhrase << endl;
	cout << "Pharse(diff): " << WordTable.getphrasenumber() << endl;
	cout << "chars: " << SumofChar << endl;
	cout << "lines: " << Sumofline << endl;
	cout << "10 most common words are :" << endl;
	WordTable.get10words();
	cout << "10 most common phrases are:" << endl;
	WordTable.get10phrases();
}
