//
//  main.cpp
//  CPU Simulator
//
//  Created by Qinyang Li on 21/10/2018.
//  Copyright © 2018 Qinyang Li. All rights reserved.
//

#include <iostream>
#include <fstream>
#include <string>
#include "func.hpp"
#define LENTH 0x1000000
using namespace std;

int main(int argc ,char *argv[]){
    memory* mem = new memory;
    reg r;
    unsigned int address=0x10000000;
    ifstream file;
    file.open(argv[1],ifstream::binary);
    if(!file.is_open()){
        cerr << "error, can't open input file" << endl;
        exit(-21);
    }
    file.read(reinterpret_cast<char*>(ins), sizeof(char)*LENTH);
    //cout<<bitset<32>(word(&ins[0]))<<endl;
    file.close();
    while (address!=0) {
        do_op(ins, r,mem, address);
    }
    //cout<<r.read(9)<<endl;  //测试输出
    int exitcode= extract(r.read(2), 7, 0);
    return exitcode;
}
