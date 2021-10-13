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
	
	for (int i = 0; i < 5; i++){
		digit = (rand()%10); //random digit 0-9
		hi1.insertDigit(digit); //insert digit
		digit = (rand()%10); //random digit 0-9
		hi2.insertDigit(digit);
	}
//    hi1.printDigits();
    
    cout << "Notice, all number are displayed reversely, i.e., from lsd to msd" << endl;
    cout << "For example, an integer 152, one hundred fifty two is displayed as 251, where 2 is least signigicant digit, 1 as most significant digit" << endl;
    cout << "hi1 = " ;
    hi1.printDigits();
    cout << "hi2 = ";
    hi2.printDigits();
    
    hi3=hi1 + hi2;	//add HugeInts
    
    cout << "hi1 + hi2 = " ;
    hi3.printDigits();
    
    hi3= hi1 - hi2;
    
    cout << "hi1 - hi2 = " ;
    
    if (hi1 < hi2)
        cout << "-";
    
    hi3.printDigits();
    
 
	
	if (hi1 == hi2){
		cout << "Equal\n";
	}
	
	if (hi1 < hi2){
		cout << "hi1 is less than hi2\n";
	}else{
		cout << "hi1 is more than hi2\n";
	}
	

    
	cout << "HugeInt 1:\n";
	hi1.printDigits();

	cout << "HugeInt 2:\n";
	hi2.printDigits();
	
	return 0;
};
