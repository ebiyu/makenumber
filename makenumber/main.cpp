//
//  main.cpp
//  makenumber
//
//  Created by 海老原祐輔 on 2017/06/26.
//  Copyright © 2017年 海老原祐輔. All rights reserved.
//

#include <iostream>
#include <algorithm>
#include "frac.h"
#include "calculate.h"


int main(int argc, const char * argv[]) {
    //    calculate calc1(4);
    //    std::cout << calc1.eval((frac[]){frac(3),frac(8),frac(2),frac(2)}, (op[]){plus,minus,divide}, (int[]){0,2,1}).ToString();
    //    return 0;
    const int dig=4;
    int num[dig];
    int target;
    std::cin >> num[0];
    std::cin >> num[1];
    std::cin >> num[2];
    std::cin >> num[3];
    std::cin >> target;
    
    //number sort
    int numIndex[dig];
    for(int i=0;i<dig;i++){
        numIndex[i]=i;
    }
    do{
        frac numbers[dig];
        for(int i=0;i<dig;i++){
            numbers[i].setint(num[numIndex[i]]);
        }
        
        //calculateOrder sort
        int calcOrders[dig-1];
        for(int i=0;i<dig-1;i++){
            calcOrders[i]=i;
        }
        do{
            //operators select
            int pow=1;
            for(int i=0;i<dig-1;i++){
                pow*=4;
            }
            for(int i=0;i<pow;i++){
                int iNum=i;
                op operators[dig-1];
                for(int j=0;j<dig-1;j++){
                    switch (iNum%4) {
                        case 0:
                            operators[j]=plus;
                            break;
                        case 1:
                            operators[j]=minus;
                            break;
                        case 2:
                            operators[j]=times;
                            break;
                        case 3:
                            operators[j]=divide;
                            break;
                    }
                    iNum=iNum/4;
                }
                
                //calculate
                calculate calc1(dig);
                try{
                    frac result=calc1.eval(numbers, operators, calcOrders);
                    if(result.isint()&&result.getint()==target){
                        for(int j=0;j<dig-1;j++){
                            std::cout << numbers[j].getint();
                            switch (operators[j]) {
                                case plus:
                                    std::cout << "+";
                                    break;
                                case minus:
                                    std::cout << "-";
                                    break;
                                case times:
                                    std::cout << "*";
                                    break;
                                case divide:
                                    std::cout << "/";
                            }
                        }
                        std::cout << numbers[dig-1].getint();
                        std::cout << "(order:";
                        for(int j=0;j<dig-1;j++){
                            std::cout << calcOrders[j] << "," ;
                        }
                        std::cout << ")\n";
                    }
                }catch(const std::range_error e){
                    
                }
                
                
            }
        }while(std::next_permutation(calcOrders, calcOrders+dig-1));
        
        
    }while(std::next_permutation(numIndex, numIndex+dig));
    
    
    return 0;
}
