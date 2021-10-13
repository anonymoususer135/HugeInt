#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <ctime>

#include "HugeInt.h"

using namespace std;

HugeInt::HugeInt() {
    Node *node=new Node;
    node->digit=0;
    this->lsd=node;
    this->msd=node;
    node->next_greater=node;
    node->next_lesser=node;
    this->sign = PLUS;
    this->numDigits = 0;
}

HugeInt::~HugeInt() {
//    delete this;
}

bool HugeInt::operator<(HugeInt second) {
    if (this->sign==PLUS && second.sign==MINUS)
        return false;
    
    if (this->sign==MINUS && second.sign==PLUS)
        return true;
    
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
        
            int carry = 0; //carry is set 1 if 2 sum of 2 digits is >= 10
            for (int i = 0;i < longNumDigits;i++)
            {
                if (i < shortNumDigits)
                {
                    if (l1->digit + m1->digit + carry <= 9)
                    {
                        if (result.numDigits==0)
                        {
                            result.lsd->digit = l1->digit + m1->digit + carry;
                            result.numDigits++;
                        }
                        else
                        {
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
