//
//  frac.cpp
//  makenumber
//
//  Created by 海老原祐輔 on 2017/06/26.
//  Copyright © 2017年 海老原祐輔. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include "frac.h"
#include <cstdlib>

//constructor
frac::frac(){
    setint(0);
}
frac::frac(int value){
    setint(value);
}
frac::frac(int numerator,int denominator){
    setnumerator(numerator);
    setdenominator(denominator);
}

//setter
void frac::setdenominator(const int value){
    if (value==0) {
        throw std::range_error("Divided by zero.");
    }else{
        this->denominator=value;
    }
}
void frac::setnumerator(const int value){
    this->numerator=value;
}
void frac::setfrac(int numerator, int denominator){
    setnumerator(numerator);
    setdenominator(denominator);
}
void frac::setint(int value) {
    setnumerator(value);
    setdenominator(1);
}

//reduction
int frac::gcd(int value1, int value2){
    value1 = std::abs(value1);
    value2 = std::abs(value2);
    
    //make value1>value2
    int tmp;
    if (value1 < value2){
        tmp=value1;
        value1=value2;
        value2=tmp;
    }
    
    while(value2 != 0){
        tmp = value2;
        value2  = value1 % value2;
        value1 = tmp;
    }
    return value1;
}

void frac::reduction(){
    int GCD=gcd(this->numerator, this->denominator);
    
    int  denominator=this->denominator/GCD;
    int numerator=this->numerator/GCD;
    
    
    //keep denominator plus
    if(denominator<0){
        denominator=-denominator;
        numerator=-numerator;
    }
    
    setdenominator(denominator);
    setnumerator(numerator);
}

//operatoe override
frac frac::operator+(const frac value){
    int lcm=value.denominator*this->denominator/gcd(value.denominator,this->denominator);
    int numerator=value.numerator*lcm/value.denominator+this->numerator*lcm/this->denominator;
    frac ret=frac(numerator,lcm);
    ret.reduction();
    return ret;
}

frac frac::operator-(const frac value){
    return operator+(frac(-value.numerator,value.denominator));
}

frac frac::operator*(const frac value){
    frac ret=frac(this->numerator*value.numerator,this->denominator*value.denominator);
    ret.reduction();
    return ret;
}

frac frac::operator/(const frac value){
    frac ret=frac(this->numerator*value.denominator,this->denominator*value.numerator);
    ret.reduction();
    return ret;
   
}


//output
bool frac::isint(){
    if (getnumerator()/getdenominator()==getint()) {
        return true;
    }else{
        return false;
    }
}
int frac::getint(){
    return (int)(getnumerator()/getdenominator());
}
float frac::getfloat(){
    return getnumerator()/getdenominator();
}
