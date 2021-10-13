#ifndef HUGEINT_H_
#define HUGEINT_H_

enum SignType {PLUS, MINUS};

class HugeInt{
private:
	struct Node
	{
		int digit; // SINGLE DIGIT ONLY ie: (0, 1, 2, 3, 4, 5, 6, 7, 8, 9)
		Node *next_greater; // Next More Significant Digit
		Node *next_lesser; // Next less Significant Digit		
	};				
	
	/*  Integer 345 is stored in List: lsd-> 3 -><- 4 -><- 5 <- msd
		Integer 123 is stored in List: lsd-> 1 -><- 2 -><- 3 <- msd
		To add: add the least significant digits, potentially 
		keeping track of a carry value. Then move to the next 
		left nodes in both HugeInts. Add these and the carry. 
		Create a new carry value. Continue until both HugeInt 
		lists are empty. If one list is empty, keep processing 
		the non-empty list.
	*/ 

	Node *lsd; 			//Least significant digit
	Node *msd; 			//Most significant digit
	SignType sign; 		//enum of the sign of the HugeInt
	int numDigits; 		//Number of digits in the HugeInt
	void makeEmpty(); 	//clear the linked list of digits
public:
	HugeInt();
	~HugeInt();
	bool operator<(const HugeInt &second) const;//compare for less than. return true/false
	bool operator==(const HugeInt &second) const;//compare for equal. return true/false
	HugeInt operator+(const HugeInt &second) const;//add
	HugeInt operator-(const HugeInt &second) const;//subtract
	HugeInt operator=(const HugeInt &second) const;//copy
	void insertDigit(int); //insert new integer digit. Insert each digit separately!!!!!!!
	void printDigits() const; //print the HugeInt from lsd to msd.
};

#endif