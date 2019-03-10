#include <iostream>
#include "func.hpp"
#include "Reg.hpp"
#include "mem.hpp"
using namespace std;
unsigned char ins[LENTH]={0};
unsigned int word(unsigned char *a){
    unsigned int i;
    i= ((*a)<<24)&0xFF000000;
    a++;
    i=i|(((*a)<<16)&0xFF0000);
    a++;
    i=i|(((*a)<<8)&0xFF00);
    a++;
    i=i|((*a)&0xFF);
    return i;
}
int wordsigned(char *a){
    int i;
    i= ((*a)<<24)&0xFF000000;
    a++;
    i=i|(((*a)<<16)&0xFF0000);
    a++;
    i=i|(((*a)<<8)&0xFF00);
    a++;
    i=i|((*a)&0xFF);
    return i;
}
unsigned int extract(unsigned int ins,int a,int b){
    unsigned int tmp;
    tmp=ins<<(31-a);
    tmp=tmp>>(31-a+b);
    return tmp;
}

unsigned long int extract64(unsigned long int ins, int a, int b) {
	unsigned long int tmp;
	tmp = ins << (63 - a);
	tmp = tmp >> (63 - a + b);
	return tmp;
}

int signext(unsigned int imm){
    int test=imm>>15;
    if (test==1) {
        return imm-65536;
    }
    else{
        return imm;
    }
}
int signext8(unsigned int imm){
    int test=imm>>7;
    if (test==1) {
        return imm-256;
    }
    else{
        return imm;
    }
}
void do_op(unsigned char ins[],reg& r,memory* mem, unsigned int &address){
    if ((address<0x10000000)||(address>0x10FFFFFC)||(address%4!=0)){        //检查地址是否合法
        exit(-11);
    }
    unsigned int insaddr=address-0x10000000;
    unsigned int instrcution=word(&ins[insaddr]);
    unsigned int opcode=extract(instrcution, 31, 26);
    unsigned int rs=extract(instrcution, 25, 21);
    unsigned int rt=extract(instrcution, 20, 16);
    unsigned int rd=extract(instrcution, 15, 11);
    unsigned int shamt=extract(instrcution, 10, 6);
    unsigned int funct=extract(instrcution, 5, 0);
    unsigned int immediate=extract(instrcution, 15, 0);
    unsigned int jaddress=extract(instrcution, 25, 0);
    unsigned int jumpaddr=((extract(address+4, 31, 28)<<26)+jaddress)<<2;
    int tmprt,tmprs,temp,n;
    long int overflowtester_res,overflowtester_1,overflowtester_2, multmp,mula,mulb;
    unsigned int unsrt, unsrs,tmpaddress;
	unsigned long int unsmul,unmula,unmulb;
    switch (opcode) {
        case 0x0:
            switch (funct) {
                case 0x0:                           //SLL
                    if (rs!=0) {
                        exit(-12);
                    }
                    tmprt=r.read(rt)<<shamt;
                    r.write(rd, tmprt);
                    address+=0x4;
                    break;
                case 0x2:                           //SRL
                    if (rs!=0) {
                        exit(-12);
                    }
                    tmprt=r.read(rt);
                    unsmul=0xFFFFFFFF&tmprt;
                    unsmul=unsmul>>shamt;
                    r.write(rd, unsmul);
                    address+=0x4;
                    break;
				case 0x3:                           //SRA
                    if (rs!=0) {
                        exit(-12);
                    }
					tmprt = r.read(rt) >> shamt;
					r.write(rd, tmprt);
					address += 0x4;
					break;
				case 0x4:                           //SLLV
                    if (shamt!=0) {
                        exit(-12);
                    }
					tmprs = r.read(rs);
                    tmprs=extract(tmprs, 4, 0);
					tmprt = r.read(rt) << tmprs;
					r.write(rd, tmprt);
					address += 0x4;
					break;
				case 0x6:                           //SRLV
                    if (shamt!=0) {
                        exit(-12);
                    }
					tmprs = r.read(rs);
                    tmprs=extract(tmprs, 4, 0);
					tmprt = r.read(rt);
					unsmul = 0xFFFFFFFF & tmprt;
					unsmul = unsmul >> tmprs;
					r.write(rd, unsmul);
					address += 0x4;
					break;
				case 0x7:                           //SRAV
                    if (shamt!=0) {
                        exit(-12);
                    }
					tmprs = r.read(rs);
                    tmprs=extract(tmprs, 4, 0);
					tmprt = r.read(rt) >> tmprs;
					r.write(rd, tmprt);
					address += 0x4;
					break;
                case 0x8:                           //JR
                    if ((shamt!=0)||(rt!=0)||(rd!=0)) {
                        exit(-12);
                    }
                    tmpaddress=address+0x4;
                    do_op(ins, r, mem, tmpaddress);     //问题：slot是非法内存范围？
                    address=r.read(rs);
                    break;
				case 0x9:                           //JALR
                    if ((shamt!=0)||(rt!=0)) {
                        exit(-12);
                    }
					tmprs = r.read(rs);
					r.write(rd, address + 8);
					tmpaddress = address + 0x4;
					do_op(ins, r, mem, tmpaddress);
					address = tmprs;
					break;
				case 0x10:                          //MFHI
                    if ((shamt!=0)||(rt!=0)||(rs!=0)) {
                        exit(-12);
                    }
					tmprs = r.readhl(true);
					r.write(rd, tmprs);
					address += 0x4;
					break;
				case 0x11:                          //MTHI
                    if ((shamt!=0)||(rt!=0)||(rd!=0)) {
                        exit(-12);
                    }
					tmprs = r.read(rs);
					r.writehl(true, tmprs);
					address += 0x4;
					break;
				case 0x12:                          //MFLO
                    if ((shamt!=0)||(rt!=0)||(rs!=0)) {
                        exit(-12);
                    }
					tmprs = r.readhl(false);
					r.write(rd, tmprs);
					address += 0x4;
					break;
				case 0x13:                          //MTLO
                    if ((shamt!=0)||(rt!=0)||(rd!=0)) {
                        exit(-12);
                    }
					tmprs = r.read(rs);
					r.writehl(false, tmprs);
					address += 0x4;
					break;
				case 0x18:                          //MULT
                    if ((shamt!=0)||(rd!=0)) {
                        exit(-12);
                    }
					mula = r.read(rs);
					mulb = r.read(rt);
					multmp = mula*mulb;
					r.writehl(true, extract64(multmp, 63, 32));
					r.writehl(false, extract64(multmp, 31, 0));
					address += 0x4;
					break;
				case 0x19:                          //MULTU
                    if ((shamt!=0)||(rd!=0)) {
                        exit(-12);
                    }
					unmula = r.read(rs)&0xFFFFFFFF;
					unmulb = r.read(rt)&0xFFFFFFFF;
					unsmul = unmula * unmulb;
					r.writehl(true, extract64(unsmul, 63, 32));
					r.writehl(false, extract64(unsmul, 31, 0));
					address += 0x4;
					break;
				case 0x1a:                          //DIV
                    if ((shamt!=0)||(rd!=0)) {
                        exit(-12);
                    }
					tmprs = r.read(rs);
					tmprt = r.read(rt);
                    if (tmprt==0) {
                        tmprt=1;
                    }
					r.writehl(true, (tmprs%tmprt));
					r.writehl(false, (tmprs/tmprt));
					address += 0x4;
					break;
				case 0x1b:                          //DIVU
                    if ((shamt!=0)||(rd!=0)) {
                        exit(-12);
                    }
					unsrs = r.read(rs);
					unsrt = r.read(rt);
                    if (unsrt==0) {
                        unsrt=1;
                    }
					r.writehl(true, unsrs%unsrt);
					r.writehl(false, unsrs/unsrt);
					address += 0x4;
					break;
                case 0x20:                          //ADD Overflow?
                    if (shamt!=0) {
                        exit(-12);
                    }
                    tmprt = r.read(rt);
                    tmprs = r.read(rs);
                    tmprs = tmprs+tmprt;
                    overflowtester_1=r.read(rs);
                    overflowtester_2=r.read(rt);
                    overflowtester_res=overflowtester_1+overflowtester_2;
                    if (overflowtester_res!=tmprs) {
                        exit(-10);
                    }
                    r.write(rd, tmprs);
                    address += 0x4;
                    break;
                case 0x21:                          //ADDU
                    if (shamt!=0) {
                        exit(-12);
                    }
                    unsrt = r.read(rt);
                    unsrs = r.read(rs);
                    r.write(rd, (unsrt + unsrs));
                    address += 0x4;
                    break;
				case 0x22:                          //SUB   Overflow
                    if (shamt!=0) {
                        exit(-12);
                    }
					tmprt = r.read(rt);
					tmprs = r.read(rs);
                    tmprs = tmprs - tmprt;
                    overflowtester_1=r.read(rs);
                    overflowtester_2=r.read(rt);
                    overflowtester_res=overflowtester_1-overflowtester_2;
                    if (overflowtester_res!=tmprs) {
                        exit(-10);
                    }
					r.write(rd, tmprs);
					address += 0x4;
					break;
                case 0x23:                          //SUBU
                    if (shamt!=0) {
                        exit(-12);
                    }
                    unsrt = r.read(rt);
                    unsrs = r.read(rs);
                    r.write(rd, (unsrs - unsrt));
                    address += 0x4;
                    break;
                case 0x24:                          //AND
                    if (shamt!=0) {
                        exit(-12);
                    }
                    tmprt = r.read(rt);
                    tmprs = r.read(rs);
                    r.write(rd, (tmprt&tmprs));
                    address += 0x4;
                    break;
                case 0x25:                          //OR
                    if (shamt!=0) {
                        exit(-12);
                    }
                    tmprt = r.read(rt);
                    tmprs = r.read(rs);
                    r.write(rd, (tmprt | tmprs));
                    address += 0x4;
                    break;
				case 0x26:                          //XOR
                    if (shamt!=0) {
                        exit(-12);
                    }
					tmprt = r.read(rt);
					tmprs = r.read(rs);
					r.write(rd, (tmprt^tmprs));
					address += 0x4;
					break;
                case 0x2a:                          //SLT
                    if (shamt!=0) {
                        exit(-12);
                    }
                    tmprt = r.read(rt);
                    tmprs = r.read(rs);
                    if (tmprs < tmprt) {
                        r.write(rd, 1);
                    }
                    else {
                        r.write(rd, 0);
                    }
                    address += 0x4;
                    break;
                case 0x2b:                          //SLTU
                    if (shamt!=0) {
                        exit(-12);
                    }
                    unsrt = r.read(rt);
                    unsrs = r.read(rs);
                    if (unsrs < unsrt) {
                        r.write(rd, 1);
                    }
                    else {
                        r.write(rd, 0);
                    }
                    address += 0x4;
                    break;
                default:
                    exit(12);
                    break;
            }
            break;
		case 0x1:                                   
			switch (rt) {
			case 0x0:                              //BLTZ
				tmprs = r.read(rs);
				if (tmprs < 0) {
					immediate = signext(immediate) << 2;
					tmpaddress = address + 0x4;
					do_op(ins, r, mem, tmpaddress);
					address += 0x4 + immediate;
				}
				else {
					address += 0x4;
				}
				break;
			case 0x1:                              //BGEZ
				tmprs = r.read(rs);
				if (tmprs >= 0) {
					immediate = signext(immediate) << 2;
					tmpaddress = address + 0x4;
					do_op(ins, r, mem, tmpaddress);
					address += 0x4 + immediate;
				}
				else {
					address += 0x4;
				}
				break;
			case 0x10:                             //BLTZAL
				tmprs = r.read(rs);
                r.write(31, (address + 8));
				if (tmprs < 0) {
					immediate = signext(immediate) << 2;
					tmpaddress = address + 0x4;
					do_op(ins, r, mem, tmpaddress);
					address += 0x4 + immediate;
				}
				else {
					address += 0x4;
				}
				break;
			case 0x11:                             //BGEZAL
				tmprs = r.read(rs);
                r.write(31, (address + 8));
				if (tmprs >= 0) {
					immediate = signext(immediate) << 2;
					tmpaddress = address + 0x4;
					do_op(ins, r, mem, tmpaddress);
					address += 0x4 + immediate;
				}
				else {
					address += 0x4;
				}
				break;
            default:
                exit(-12);
                break;
			}
            break;
		case 0x2:                                   //J
			tmpaddress = address + 0x4;
			do_op(ins, r, mem, tmpaddress);
			address = jumpaddr;
			break;
		case 0x3:                                   //JAL
			tmpaddress = address + 0x4;
            r.write(31, (address + 8));
			do_op(ins, r, mem, tmpaddress);
			address = jumpaddr;
			break;
		case 0x4:                                   //BEQ
			tmprs = r.read(rs);
			tmprt = r.read(rt);
			if (tmprs == tmprt) {
				immediate = signext(immediate) << 2;
				tmpaddress = address + 0x4;
				do_op(ins, r, mem, tmpaddress);
				address += 0x4 + immediate;
			}
			else {
				address += 0x4;
			}
			break;
		case 0x5:                                   //BNE
			tmprs = r.read(rs);
			tmprt = r.read(rt);
			if (tmprs != tmprt) {
				immediate = signext(immediate) << 2;
				tmpaddress = address + 0x4;
				do_op(ins, r, mem, tmpaddress);
				address += 0x4 + immediate;
			}
			else {
				address += 0x4;
			}
			break;
		case 0x6:                                   //BLEZ
            if (rt!=0) {
                exit(-12);
            }
			tmprs = r.read(rs);
			if (tmprs <= 0) {
				immediate = signext(immediate) << 2;
				tmpaddress = address + 0x4;
				do_op(ins, r, mem, tmpaddress);
				address += 0x4 + immediate;
			}
			else {
				address += 0x4;
			}
			break;
		case 0x7:                                   //BGTZ
            if (rt!=0) {
                exit(-12);
            }
			tmprs = r.read(rs);
			if (tmprs > 0) {
				immediate = signext(immediate) << 2;
				tmpaddress = address + 0x4;
				do_op(ins, r, mem, tmpaddress);
				address += 0x4 + immediate;
			}
			else {
				address += 0x4;
			}
			break;
        case 0x8:                                   //ADDI Overflow?
            tmprs=r.read(rs)+signext(immediate);
            overflowtester_1=r.read(rs);
            overflowtester_2=signext(immediate);
            overflowtester_res=overflowtester_1+overflowtester_2;
            if (overflowtester_res!=tmprs) {
                exit(-10);
            }
            r.write(rt, tmprs);
            address+=0x4;
            break;
        case 0x9:                                   //ADDIU
            unsrs = r.read(rs) + signext(immediate);
            r.write(rt, unsrs);
            address += 0x4;
            break;
		case 0xa:                                   //SLTI
			tmprs = r.read(rs);
			if (tmprs < signext(immediate)) {
				r.write(rt, 1);
			}
			else {
				r.write(rt, 0);
			}
			address += 0x4;
			break;
		case 0xb:                                   //SLTIU
			unsrs = r.read(rs);
            unsrt = signext(immediate);
			if (unsrs < unsrt) {
				r.write(rt, 1);
			}
			else {
				r.write(rt, 0);
			}
			address += 0x4;
			break;
        case 0xc:                                   //ANDI
            tmprs = r.read(rs)&immediate;
            r.write(rt, tmprs);
            address += 0x4;
            break;
		case 0xd:                                   //ORI
			tmprs = r.read(rs) | immediate;
			r.write(rt, tmprs);
			address += 0x4;
			break;
		case 0xe:                                   //XORI
			tmprs = r.read(rs) ^ immediate;
			r.write(rt, tmprs);
			address += 0x4;
			break;
		case 0xf:                                   //LUI
            if (rs!=0) {
                exit(-12);
            }
			tmprs = immediate << 16;
			r.write(rt, tmprs);
			address += 0x4;
			break;
		case 0x20:                                  //LB
			tmprs = r.read(rs) + signext(immediate);
			r.write(rt, signext8(mem->read_byte(tmprs)));
			address += 0x4;
			break;
		case 0x21:                                  //LH
			tmprs = r.read(rs) + signext(immediate);
			r.write(rt, signext(mem->read_half(tmprs)));
			address += 0x4;
			break;
		case 0x22:                                  //LWL
			tmprs = r.read(rs) + signext(immediate);
            n=4-tmprs%4;
            if (tmprs>0x25000000) {
                if (tmprs==0x30000000) {
                    temp=mem->read(tmprs);
                }
                else{
                    exit(-11);
                }
            }
            else{
                temp=0;
                for (int i=0; i<n; i++) {
                    temp = temp|((mem->read_byte(tmprs+i))<<(8*(n-1-i)));
                }
            }
			tmprt = r.read(rt);
            if (n==4) {
                r.write(rt, temp);
            }
            else{
                tmprt=extract(tmprt, 8*(4-n)-1, 0);
                tmprt = tmprt | (temp<<(8*(4-n)));
                r.write(rt, tmprt);
            }
			address += 0x4;
			break;
        case 0x23:                                  //LW
            tmprs=r.read(rs)+signext(immediate);
            r.write(rt, mem->read(tmprs));
            address+=0x4;
            break;
		case 0x24:                                  //LBU
			tmprs = r.read(rs) + signext(immediate);
			r.write(rt, mem->read_byte(tmprs));
			address += 0x4;
			break;
		case 0x25:                                  //LHU
			tmprs = r.read(rs) + signext(immediate);
			r.write(rt, mem->read_half(tmprs));
			address += 0x4;
			break;
		case 0x26:                                  //LWR
            tmprs = r.read(rs) + signext(immediate);
            n=tmprs%4+1;
            if (tmprs>0x25000000) {
                if (tmprs==0x30000003) {
                    temp=mem->read(0x30000000);
                }
                else{
                    exit(-11);
                }
            }
            else{
                temp=0;
                for (int i=0; i<n; i++) {
                    temp = temp|((mem->read_byte(tmprs-i))<<(8*i));
                }
            }
            tmprt = r.read(rt);
            if (n==4) {
                r.write(rt, temp);
            }
            else{
                tmprt=extract(tmprt, 31, 8*n);
                tmprt = tmprt<<(8*n) | temp;
                r.write(rt, tmprt);
            }
			address += 0x4;
			break;
		case 0x28:                                  //SB
			tmprs = r.read(rs) + signext(immediate);
			mem->write_byte(tmprs, r.read(rt));
			address += 0x4;
			break;
		case 0x29:                                  //SH
			tmprs = r.read(rs) + signext(immediate);
			mem->write_half(tmprs, r.read(rt));
			address += 0x4;
			break;
        case 0x2b:                                  //SW
            tmprs=r.read(rs)+signext(immediate);
            mem->write(tmprs, r.read(rt));
            address+=0x4;
            break;
        default:                                    //非法Opcode
            exit(-12);
            break;
        }
}
