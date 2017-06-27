//
//  calculate.cpp
//  makenumber
//
//  Created by 海老原祐輔 on 2017/06/26.
//  Copyright © 2017年 海老原祐輔. All rights reserved.
//

#include <stdio.h>
#include "calculate.h"
#include <iostream>


//constructor
calculate::calculate(int count){
    this->count=count;
    num=new frac[count];
    operators=new op[count];
    calcOrder=new int[count];
}

//destructor
calculate::~calculate(){
    delete[] num;
    num=NULL;
    delete[] operators;
    operators=NULL;
    delete[] calcOrder;
    calcOrder=NULL;
}


void calculate::calcIt(int iCount,int calcIndex){
    if(iCount!=1){
        
        int place=iCalcOrder[calcIndex];
        
        //calculate
        switch (iOperators[place]) {
            case plus:
                iNum[place]=iNum[place]+iNum[place+1];
                break;
            case minus:
                iNum[place]=iNum[place]-iNum[place+1];
                break;
            case times:
                iNum[place]=iNum[place]*iNum[place+1];
                break;
            case divide:
                iNum[place]=iNum[place]/iNum[place+1];
                break;
        }
        
        //delete and move
        for(int i=0;i<iCount-1;i++){
            if(i>place){
                iNum[i]=iNum[i+1];
            }
            if(i>=place&&i<iCount-2){
                iOperators[i]=iOperators[i+1];
            }
//            if(iCalcOrder[i]>place&&i<iCount-2){
//                iCalcOrder[i]--;
//            }
        }
        for(int i=0;i<count-1;i++){
            if(iCalcOrder[i]>place){
                iCalcOrder[i]--;
            }
        }
        
        //recursinon
        calcIt(iCount-1,calcIndex+1);
    }
}

frac calculate::eval(frac *pNum, op *pOperators, int *pCalcOrder){
    
//    //check size
//    if(sizeof(num)/sizeof(frac)!=this->count){
//        throw std::range_error("Array Size Inappropriate");
//    }
//    if(sizeof(operators)/sizeof(op)!=this->count-1){
//        throw std::range_error("Array Size Inappropriate");
//    }
//    if(sizeof(calcOrder)/sizeof(int)!=this->count-1){
//        throw std::range_error("Array Size Inappropriate");
//    }
    
    //copy for external use
    memcpy(num, pNum, count*sizeof(frac));
    memcpy(operators,pOperators,count*sizeof(op));
    memcpy(calcOrder,pCalcOrder,count*sizeof(int));
    
    //copy for internal use
    iNum=new frac[count];
    iOperators=new op[count];
    iCalcOrder=new int[count];
    
    memcpy(iNum, pNum, count*sizeof(frac));
    memcpy(iOperators,pOperators,count*sizeof(op));
    memcpy(iCalcOrder,pCalcOrder,count*sizeof(int));
    
    //calculate
    calcIt(count,0);
    
    frac ret=iNum[0];
    
    //release memory
    delete[] iNum;
    iNum=NULL;
    delete[] iOperators;
    iOperators=NULL;
    delete[] iCalcOrder;
    iCalcOrder=NULL;
    
    return ret;
}
