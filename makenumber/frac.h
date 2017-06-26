//
//  frac.h
//  makenumber
//
//  Created by 海老原祐輔 on 2017/06/26.
//  Copyright © 2017年 海老原祐輔. All rights reserved.
//

#ifndef frac_h
#define frac_h

class frac
{
    int denominator=1; //分母
    int numerator;//分子
    
    int gcd(int value1,int value2);
public:
    //constructor
    frac();
    frac(int value);
    frac(int numerator,int denominator);
    
    //destructor
    ~frac(){}
    
    //getter
    int getdenominator(){
        return denominator;
    }
    int getnumerator(){
        return numerator;
    }
    
    //setter
    void setdenominator(const int value);
    void setnumerator(int const value);
    void setfrac(int numerator,int denominator);
    void setint(int value);
    
    //reduction
    void reduction();
    
    //operater override
    frac operator+(const frac value);
    frac operator-(const frac value);
    frac operator*(const frac value);
    frac operator/(const frac value);
    
    bool operator=(const frac value);
    
    //output
    bool isint();
    int getint();
    float getfloat();
};

#endif /* frac_h */
