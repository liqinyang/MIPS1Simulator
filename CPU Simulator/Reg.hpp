//
//  Reg.hpp
//  CPU Simulator
//
//  Created by Qinyang Li on 21/10/2018.
//  Copyright © 2018 Qinyang Li. All rights reserved.
//
#ifndef Reg_hpp
#define Reg_hpp
class reg{
public:
    int read(int num);
    void write(int num, int data);
	int readhl(bool hl);
	void writehl(bool hl, int data);
private:
    int regdata[32]={0};
	int hi = 0;
	int lo = 0;
};
#endif /* Reg_hpp */
