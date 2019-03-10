//
//  func.h
//  CPU Simulator
//
//  Created by Qinyang Li on 29/10/2018.
//  Copyright © 2018 Qinyang Li. All rights reserved.
//

#ifndef func_hpp
#define func_hpp
#include "Reg.hpp"
#include "mem.hpp"
#define LENTH 0x1000000
extern unsigned char ins[LENTH];
unsigned int word(unsigned char *a);
int wordsigned(char *a);
unsigned int extract(unsigned int ins,int a,int b);
int signext(unsigned int imm);
int signext8(unsigned int imm);
void do_op(unsigned char ins[],reg& r,memory* mem, unsigned int &address);
unsigned long int extract64(unsigned long int ins, int a, int b);
#endif /* func_h */
