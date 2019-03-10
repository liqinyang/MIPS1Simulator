//
//  Reg.cpp
//  CPU Simulator
//
//  Created by Qinyang Li on 21/10/2018.
//  Copyright © 2018 Qinyang Li. All rights reserved.
//

#include "Reg.hpp"
int reg::read(int num){
    if ((num>=0)&&(num<=31)) {
        if (num==0) {
            return 0;
        }
        else{
            return regdata[num];
        }
    }
    else{
        return -1;                                //非法寄存器error
    }
}
void reg::write(int num, int data){
    if ((num>=0)&&(num<=31)){
        if (num>0) {
            regdata[num]=data;
        }
    }
    else{
        return;                               //非法寄存器error
    }
}

int reg::readhl(bool hl) {
	if (hl == true) {
		return hi;
	}
	else {
		return lo;
	}
}

void reg::writehl(bool hl, int data) {
	if (hl == true) {
		hi = data;
	}
	else {
		lo = data;
	}
}
