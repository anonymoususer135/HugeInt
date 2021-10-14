#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

#include "HugeInt.h"

using namespace std;

HugeInt::HugeInt() {
    //for the adding thing, it makes a new node when the result.numDigits == 0.
    //When declaring new HugeInt, (e.g. make HugeInt hugeinteger. It will internally call
    //HugeInt function and make a new node. )
    Node *node=new Node;
    node->digit=0;
    this->lsd=node;
    this->msd=node;
    //one node is one digit. if there is 123, then there is 3 nodes.
    //since there is 1 node, 1 number goes into the result, result's numDigit will increment by 1.
    node->next_greater=node;
    node->next_lesser=node;
    this->sign = PLUS;
    this->numDigits = 0;
}

HugeInt::~HugeInt() {
    delete this;
}

bool HugeInt::operator<(HugeInt second) {
    if (this->sign==PLUS && second.sign==MINUS)
        return false; //e.g. 1 and -9000. -9000 is smaller
    
    if (this->sign==MINUS && second.sign==PLUS)
        return true; //e.g. -105 and 93. -105 is smaller
    
    if (this->numDigits < second.numDigits && this->sign==PLUS)
        return true; 
    
    if (this->numDigits < second.numDigits && this->sign==MINUS)
        return false;
    
    if (this->numDigits > second.numDigits && this->sign==PLUS)
        return false;
    
    if (this->numDigits > second.numDigits && this->sign==MINUS)
        return true;
    
    
    Node* s = this->msd;
    Node* t = second.msd;
    for (int i = 0;i < this->numDigits;i++)
    {
        if (s->digit == t->digit)
        {
            s = s->next_lesser;
            t = t->next_lesser;
            continue;
        }
        if (s->digit > t->digit)
            if (this->sign==PLUS)
                return false;
            else
                return true;
        else
            if (this->sign==PLUS)
                return true;
            else
                return false;
    }
    return false;
}

bool HugeInt::operator==(HugeInt second) {
    if (this->sign != second.sign)
        return false;
    
    if (this->numDigits != second.numDigits)
        return false;
    Node* s = this->msd;
    Node* t = second.msd;
    for (int cnt = 0;cnt < this->numDigits; cnt++)
    {
        if (s->digit == t->digit)
        {
            s = s->next_lesser;
            t = t->next_lesser;
            continue;
        }
        else
            return false;
    }
    return true;
}


HugeInt HugeInt::operator+ (HugeInt second) {
    
    HugeInt result;
    short signCompareResult=0;
    
 
//signCompareResult: 1 when both PLUS; 2 when both MINUS; 3 when this->sign PLUS only
//4 when this->sign MINUS only
    
    
    if (this->sign==second.sign && this->sign==PLUS)
        signCompareResult=1;
    else if (this->sign==second.sign && this->sign==MINUS)
        signCompareResult=2;
    else if (this->sign==PLUS)
        signCompareResult=3;
    else
        signCompareResult=4;
    
    
//    switch (signCompareResult)
    if (signCompareResult==1 | signCompareResult==2 )
    {
    /*
    EXAMPLE: 
    12345 (l1's numDigit is 5)
    +3456 (m1's numDigit is 4)
    ------
    15801
    ____________EXAMPLE 2____________
    6789+12121 how to add?
    12121 (second. l1, because it's always pointing to long.)
    +6789 (this. m1, because it's always pointing to short.)
    ------

    the carry.
    Assume that l1 is larger than m1 in the absolute value. It starts with lsd and 
    moves on to the next digit, and this is numDigits of this, or the object itself than 
    second.
    longNumDigits are set to this. Short numDigits are set to the second. If this is less
    than second, then need to re-assign.
    */
            Node* l1 = this->lsd; 
            Node* m1 = second.lsd;
            int longNumDigits=this->numDigits;
            int shortNumDigits=second.numDigits;
    /* If the numDigits of this is smaller than the numDigits of second, then make l1
    points to second, m1 points to this second. 
    LongNumDigits are set to numDigits of second and shortNumDigits are set to numDigits
    of this.*/
    
            if (this->numDigits < second.numDigits)
            {
                l1 = second.lsd;
                m1 = this->lsd;
                longNumDigits=second.numDigits;
                shortNumDigits=this->numDigits;
            }
    /*l1 is with longNumDigits and m1 is with shortNumDigits.*/    
            int carry = 0; //carry is set 1 if 2 sum of 2 digits is >= 10
            for (int i = 0;i < longNumDigits;i++) //iterating throuugh longnumdigits
            {//every digits user adds, it makes a new node to add the sum in result of the addition
                if (i < shortNumDigits)
                {
                    /*
                    when a HugeInt is constructed, constructor would make one node and set the numDigits to zero.

                    HugeInt result contains the result of addition in its linked list.
                    If the result is zero, it means that the result was just created
                    with an empty node inside, simply store the result of addition of both lsd into the node. 
                    There is no need to create a new node.
                    */
                    if (l1->digit + m1->digit + carry <= 9)
                    {
                        if (result.numDigits==0) //declare result as part of it.
                        //result has been made with an empty node. ^
                        {
                            result.lsd->digit = l1->digit + m1->digit + carry;
                            result.numDigits++;
                        }
                        else
                        {
                            // If result.numDigits is not zero, it means there are already digits inside the HugeInt result. It stores the resulf of the addition and +carry. 
                            Node *newNode=new Node;
                            Node *workNode=result.msd;
                            newNode->digit=l1->digit + m1->digit + carry;
                            workNode->next_greater=newNode;
                            result.msd=newNode;
                            result.lsd->next_lesser=newNode;
                            newNode->next_greater=result.lsd;
                            newNode->next_lesser=workNode;
                            result.numDigits++;
                        }
                        carry=0;
                    }
                    else
                    {
                        if (result.numDigits==0)
                        {
                            result.lsd->digit = l1->digit + m1->digit + carry - 10;
                            result.numDigits++;
                        }
                        else
                        {
                            Node *newNode=new Node;
                            Node *workNode=result.msd;
                            newNode->digit=l1->digit + m1->digit + carry - 10;
                            workNode->next_greater=newNode;
                            result.msd=newNode;
                            result.lsd->next_lesser=newNode;
                            newNode->next_greater=result.lsd;
                            newNode->next_lesser=workNode;
                            result.numDigits++;
                        }
                        carry = 1;
                    }
                    l1 = l1->next_greater;
                    m1 = m1->next_greater;
                }
                else
                {
                    if (l1->digit + carry <= 9)
                    {
                        if (result.numDigits==0)
                        {
                            result.lsd->digit = l1->digit + carry;
                            result.numDigits++;
                        }
                        else
                        {
                            Node *newNode=new Node;
                            Node *workNode=result.msd;
                            newNode->digit=l1->digit + carry;
                            workNode->next_greater=newNode;
                            result.msd=newNode;
                            result.lsd->next_lesser=newNode;
                            newNode->next_greater=result.lsd;
                            newNode->next_lesser=workNode;
                            result.numDigits++;
                        }
                        carry=0;
                    }
                    else
                    {
                        if (result.numDigits==0)
                        {
                            result.lsd->digit = l1->digit + carry - 10;
                            result.numDigits++;
                        }
                        else
                        {
                            Node *newNode=new Node;
                            Node *workNode=result.msd;
                            newNode->digit=l1->digit + carry - 10;
                            workNode->next_greater=newNode;
                            result.msd=newNode;
                            result.lsd->next_lesser=newNode;
                            newNode->next_greater=result.lsd;
                            newNode->next_lesser=workNode;
                            result.numDigits++;
                        }
                        carry = 1;
                    }
                    l1 = l1->next_greater;
                }
            }
        
            if (carry==1) //If after msd, carry is 1, need to add one more digit, assign to 1
            {
                Node *newNode = new Node;
                newNode->digit=1;
                Node *workNode=result.msd;
                result.msd=newNode;
                result.lsd->next_lesser=newNode;
                workNode->next_greater=newNode;
                newNode->next_lesser=workNode;
                newNode->next_greater=result.lsd;
                result.numDigits++;
            }
         
            result.sign=this->sign;
    }
    else
    {
//this and second have different sign, minus really, not plus
//l1 always points to the longer number, m1 always points to shorter number
   
    Node* l1 = this->lsd;
    Node* m1 = second.lsd;
    int longNumDigits=this->numDigits;
    int shortNumDigits=second.numDigits;


    if (this->numDigits < second.numDigits)
    {
        l1 = second.lsd;
        m1 = this->lsd;
        longNumDigits=second.numDigits;
        shortNumDigits=this->numDigits;
    }

        
    if (*this < second)
    {
        result.sign=MINUS;
    }
    else
        result.sign=PLUS;
        
    int carry = 0;
//carry is set 1 if borrow from higher digit, for example, 21-15, need to borrow (2)1 can not substract (1)5, need to borrow from (2)
//from 2,
    for (int i = 0;i < longNumDigits;i++)
        {
            if (i < shortNumDigits)
            {
                if (l1->digit - m1->digit - carry >= 0) //No need to borrow
                {
                    if (result.numDigits==0)
                    {
                        result.lsd->digit = l1->digit - m1->digit - carry;
                        result.numDigits++;
                    }
                    else
                    {
                        Node *newNode=new Node;
                        Node *workNode=result.msd;
                        newNode->digit=l1->digit - m1->digit - carry;
                        workNode->next_greater=newNode;
                        result.msd=newNode;
                        result.lsd->next_lesser=newNode;
                        newNode->next_greater=result.lsd;
                        newNode->next_lesser=workNode;
                        result.numDigits++;
                    }
                    carry=0;
                }
                else
                { //Need to borrow
                    if (result.numDigits==0)
                    {
                        result.lsd->digit = l1->digit + 10 - m1->digit - carry;
                        result.numDigits++;
                    }
                    else
                    {
                        Node *newNode=new Node;
                        Node *workNode=result.msd;
                        newNode->digit=l1->digit + 10 - m1->digit - carry;;
                        workNode->next_greater=newNode;
                        result.msd=newNode;
                        result.lsd->next_lesser=newNode;
                        newNode->next_greater=result.lsd;
                        newNode->next_lesser=workNode;
                        result.numDigits++;
                    }
                    carry = 1;
                }
                l1 = l1->next_greater;
                m1 = m1->next_greater;
            }
            else
            {
                if (l1->digit - carry >=10) //No need to borrow
                {
                    if (result.numDigits==0)
                    {
                        result.lsd->digit = l1->digit - carry;
                        result.numDigits++;
                    }
                    else
                    {
                        Node *newNode=new Node;
                        Node *workNode=result.msd;
                        newNode->digit=l1->digit - carry;
                        workNode->next_greater=newNode;
                        result.msd=newNode;
                        result.lsd->next_lesser=newNode;
                        newNode->next_greater=result.lsd;
                        newNode->next_lesser=workNode;
                        result.numDigits++;
                    }
                    carry=0;
                }
                else
                {//Need to borrow
                    if (result.numDigits==0)
                    {
                        result.lsd->digit = l1->digit + 10 - carry;
                        result.numDigits++;
                    }
                    else
                    {
                        Node *newNode=new Node;
                        Node *workNode=result.msd;
                        newNode->digit=l1->digit + 10 - carry;
                        workNode->next_greater=newNode;
                        result.msd=newNode;
                        result.lsd->next_lesser=newNode;
                        newNode->next_greater=result.lsd;
                        newNode->next_lesser=workNode;
                        result.numDigits++;
                    }
                    carry = 1;
                }
                l1 = l1->next_greater;
            }
        }
    }
    return result;
}


HugeInt HugeInt::operator- (HugeInt second) {
    if (this->sign==PLUS && second.sign==PLUS)
        second.sign=MINUS;
    else if (this->sign==MINUS && second.sign==MINUS)
        second.sign=PLUS;
    else if (this->sign==PLUS && second.sign==MINUS)
        second.sign=PLUS;
    else
        second.sign=MINUS;
    HugeInt ret=operator+(second);
    return ret;
}

void HugeInt::insertDigit(int tobeInserted) {
    
    if (this->numDigits==0) //empty, with already one node allocated, just set the digit
    {
        this->lsd->digit=tobeInserted;
        this->numDigits++;
    }
    else
    {
    Node *newNode= new Node;
    newNode->digit=tobeInserted;
    Node *workNode;
    workNode=this->msd;
    this->msd=newNode;
    this->lsd->next_lesser=newNode;
    workNode->next_greater=newNode;
    newNode->next_lesser=workNode;
    newNode->next_greater=this->lsd;
    this->msd=newNode;
    this->numDigits++;
    }
}

void HugeInt::printDigits() const {
    Node *startDigit=this->lsd;
//    cout << this->lsd->digit;
//    cout <<this->lsd->next_greater->digit;
    for (int i = 0; i < this->numDigits; i++) {
        cout << startDigit->digit;
        startDigit=startDigit->next_greater;
    }
    cout << endl;
}

void HugeInt::makeEmpty()
{
    Node *startDigit=this->lsd;
    for (int i = 0; i < this->numDigits; i++) {
        startDigit->digit=NULL;
        startDigit=startDigit->next_greater;
    }
    cout << endl;
    
}
