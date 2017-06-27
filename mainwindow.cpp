//
//  mainwindow.cpp
//  makenumber
//
//  Created by 海老原祐輔 on 2017/06/26.
//  Copyright © 2017年 海老原祐輔. All rights reserved.
//

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>
#include <algorithm>
#include "frac.h"
#include "calculate.h"
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    ui->pushButton->setEnabled(false);
    QApplication::processEvents(QEventLoop::ExcludeUserInputEvents);

    const int dig=4;
    int num[dig];
    int target;
    num[0]=ui->numBox1->text().toInt();
    num[1]=ui->numBox2->text().toInt();
    num[2]=ui->numBox3->text().toInt();
    num[3]=ui->numBox4->text().toInt();
    target=ui->targetBox->text().toInt();

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
                        QString result;
                        for(int j=0;j<dig-1;j++){
                            result+=QString().setNum(numbers[j].getint());
                            switch (operators[j]) {
                                case plus:
                                    result+="+";
                                    break;
                                case minus:
                                    result+="-";
                                    break;
                                case times:
                                    result+="*";
                                    break;
                                case divide:
                                    result+="/";
                            }
                        }
                        result+=QString().setNum(numbers[dig-1].getint());
                        result=result+"(order:";
                        for(int j=0;j<dig-2;j++){
                            result+=QString().setNum(calcOrders[j]);
                            result=result+"," ;
                        }
                        result+=QString().setNum(calcOrders[dig-2]);
                        result+=")";

                        ui->resultList->addItem(QString(result));
                    }
                }catch(const std::range_error e){

                }


            }
        }while(std::next_permutation(calcOrders, calcOrders+dig-1));


    }while(std::next_permutation(numIndex, numIndex+dig));

    ui->pushButton->setEnabled(true);
}
