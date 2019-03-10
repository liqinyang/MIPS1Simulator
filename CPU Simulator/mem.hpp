//
//  mem.hpp
//  CPU Simulator
//
//  Created by Qinyang Li on 29/10/2018.
//  Copyright © 2018 Qinyang Li. All rights reserved.
//

#ifndef mem_hpp
#define mem_hpp


class memory{
public:
    int read(int address);
    void write(int address, int datain);
    unsigned int read_half(int address);
    void write_half(int address, int datain);
    unsigned int read_byte(int address);
    void write_byte(int address, int datain);
private:
    char data[0x4000000]={0};
};


#endif /* mem_hpp */
