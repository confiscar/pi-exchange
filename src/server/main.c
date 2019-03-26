/*
 * main.c
 *
 *  Created on: 2018/11/29
 *      Author: Ke CHEN
 */
//#include "exchange.h"
//#include "notification.c"
#include <stdio.h>



// mainly for test the functions
// no need to look at this file

int main(){
    double price = 1.1;
    //convertToBuffer(price);
    char buf[1024];
    sprintf(buf, "price = %f", 1.1);
    printf("%s",buf);
}

