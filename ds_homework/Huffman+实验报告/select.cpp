#include<iostream>
#include "coder.h"
using namespace std;
void select(Hufftree HT, int i, int &s1, int &s2){
	int value1=1000,value2=1000;
	s1=0,s2=0;
	for(int h=1;h<i;h++)
	{
		if(HT[h].parent==0)
		{
			if(HT[h].weight<value1)
			{
				value2=value1;
				s2=s1;
				value1=HT[h].weight;
				s1=h;
			}
			else if(HT[h].weight<value2)
			{
				value2=HT[h].weight;
				s2=h;
			}
		}
	}
}
