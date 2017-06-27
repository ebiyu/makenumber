//
//  calculate.h
//  makenumber
//
//  Created by 海老原祐輔 on 2017/06/26.
//  Copyright © 2017年 海老原祐輔. All rights reserved.
//

#ifndef calculate_h
#define calculate_h

#include "frac.h"

enum op{
    plus,minus,times,divide,
};

class calculate{
    int count; //the number of numbers
    
    //internal use
    frac* iNum;
    op* iOperators;
    int* iCalcOrder;
    
    void calcIt(int iCount,int calcIndex); //Internal use
    
public:
    //constructor
    calculate(int count);
    
    //destructor
    ~calculate();
    
    //external use
    frac* num;
    op* operators;
    int* calcOrder;
    
    
    frac eval(frac* num,op* operators,int* calcOrder); //Evaluate solution
};


#endif /* calculate_h */
