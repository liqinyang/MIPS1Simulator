//
//  mem.cpp
//  CPU Simulator
//
//  Created by Qinyang Li on 29/10/2018.
//  Copyright © 2018 Qinyang Li. All rights reserved.
//
#include <iostream>
#include "mem.hpp"
#include "func.hpp"
using namespace std;
int memory::read(int address){                               //读内存
    if (address%4!=0) {
        exit(-11);
    }
    if ((address>=0x20000000)&&(address<=0x23FFFFFC)) {
        int dataadd=address-0x20000000;
        return wordsigned(&data[dataadd]);
    }
    if ((address>=0x10000000)&&(address<=0x10FFFFFC)) {
        int dataadd=address-0x10000000;
        return word(&ins[dataadd]);
    }
    else{
        if (address==0x30000000) {
            //cerr<<"请输入"<<endl;
            int c= getchar();
            if (c==EOF) {
                return -1;
            }
            return c;
        }
        else{
            exit(-11);                          //非法内存地址 不4？
        }
    }
}
void memory::write(int address, int datain){                 //写内存
    if (address%4!=0) {
        exit(-11);
    }
    if ((address>=0x20000000)&&(address<=0x23FFFFFC)) {
        int dataadd=address-0x20000000;
        data[dataadd]= (datain & 0xFF000000)>>24;
        data[dataadd+1]= (datain & 0x00FF0000)>>16;
        data[dataadd+2]= (datain & 0x0000FF00)>>8;
        data[dataadd+3]= (datain & 0x000000FF);
    }
    else{
        if (address==0x30000004) {
            if (datain==-1) {
                putchar(datain);
                //exit(-21);
            }
            else{
                putchar(datain);
            }
        }
        else{
            exit(-11);                            //非法内存地址
        }
    }
}
unsigned int memory::read_half(int address){                               //读内存
    if (address%2!=0) {
        exit(-11);
    }
    if ((address>=0x20000000)&&(address<=0x23FFFFFE)) {
        int dataadd=address-0x20000000;
        char *a=&data[dataadd];
        unsigned int i;
        i=((*a)<<8)&0xFF00;
        a++;
        i=i|((*a)&0xFF);
        return i;
    }
    if ((address>=0x10000000)&&(address<=0x10FFFFFE)) {
        int dataadd=address-0x10000000;
        unsigned char *a=&ins[dataadd];
        unsigned int i;
        i=((*a)<<8)&0xFF00;
        a++;
        i=i|((*a)&0xFF);
        return i;
    }
    else{
        if ((address==0x30000000)||(address==0x30000002)) {
            //cerr<<"请输入"<<endl;              //half&byte读写IO未完成！
            int c= getchar();
            if (c==EOF) {
                return 0xFFFF;
            }
            if (address==0x30000002) {
                return c;
            }
            else{
                return 0;
            }
        }
        else{
            exit(-11);                          //非法内存地址 
        }
    }
}
void memory::write_half(int address, int datain){                 //写内存
    if (address%2!=0) {
        exit(-11);
    }
    if ((address>=0x20000000)&&(address<=0x23FFFFFE)) {
        int dataadd=address-0x20000000;
        data[dataadd]= (datain & 0x0000FF00)>>8;
        data[dataadd+1]= (datain & 0x000000FF);
    }
    else{
        switch (address) {
            case 0x30000006:
                if (datain==-1) {
                    putchar(datain);
                    //exit(-21);
                }
                else{
                    putchar(datain);
                }
                break;
            case 0x30000004:
                putchar(0);
                break;
            default:
                exit(-11);                                    //非法内存地址
                break;
        }
    }
}
unsigned int memory::read_byte(int address){                               //读内存
    if ((address>=0x20000000)&&(address<=0x23FFFFFF)) {
        int dataadd=address-0x20000000;
        char *a=&data[dataadd];
        unsigned int i;
        i=(*a)&0xFF;
        return i;
    }
    if ((address>=0x10000000)&&(address<=0x10FFFFFF)) {
        int dataadd=address-0x10000000;
        unsigned char *a=&ins[dataadd];
        unsigned int i;
        i=(*a)&0xFF;
        return i;
    }
    else{
        if ((address>=0x30000000)&&(address<=0x30000003)) {
            //cerr<<"请输入"<<endl;
            int c= getchar();
            if (c==EOF) {
                return 0xFF;
            }
            if (address==0x30000003) {
                return c;
            }
            else{
                return 0;
            }
        }
        else{
            exit(-11);                          //非法内存地址
        }
    }
}
void memory::write_byte(int address, int datain){                 //写内存
    if ((address>=0x20000000)&&(address<=0x23FFFFFF)) {
        int dataadd=address-0x20000000;
        data[dataadd]= (datain & 0x000000FF);
    }
    else{
        switch (address) {
            case 0x30000007:
                if (datain==-1) {
                    putchar(datain);
                    //exit(-21);
                }
                else{
                    putchar(datain);
                }
                break;
            case 0x30000004:case 0x30000005:case 0x30000006:
                putchar(0);
                break;
            default:
                exit(-11);                                    //非法内存地址
                break;
        }
    }
}
