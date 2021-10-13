#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

#include "HugeInt.h"

using namespace std;

int main()
{
	HugeInt hi1;
	HugeInt hi2;
	HugeInt hi3;
	
	srand((unsigned) time(0));
	int digit;
	
	for (int i = 0; i < 1000; i++){
		digit = (rand()%10); //random digit 0-9
		hi1.insertDigits(digit); //insert digit
		digit = (rand()%10); //random digit 0-9
		hi2.insertDigits(digit);
	}
	
	hi1 = hi1 + hi2;	//add HugeInts
	
	if (hi1 == hi2){
		cout << "Equal\n";
	}
	
	if (hi1 < hi2){
		cout << "hi1 is less than hi2\n";
	}else{
		cout << "hi1 is more than hi2\n";
	}
	
	cout << "HugeInt 1:\n";
	printDigits(hi1);

	cout << "HugeInt 2:\n";
	printDigits(hi2);
	
	return 0;
};