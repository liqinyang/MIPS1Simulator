MIPS_CC = mips-linux-gnu-gcc
MIPS_OBJCOPY = mips-linux-gnu-objcopy
MIPS_OBJDUMP = mips-linux-gnu-objdump
MIPS_CPPFLAGS = -W -Wall -O3 -fno-builtin -march=mips1 -mfp32
MIPS_LDFLAGS = -nostdlib -Wl,-melf32btsmip -march=mips1 -nostartfiles -mno-check-zero-division -Wl,--gpsize=0 -static -Wl,-Bstatic -Wl,--build-id=none


simulator:
	mkdir -p ./bin
	g++ -std=c++11 -c ./CPU\ Simulator/*.cpp
	g++ -std=c++11 ./*.o -o ./bin/mips_simulator

.PHONY: testbench
testbench:
	mkdir -p ./bin
	cp -p -f ./Testbench/mips_testbench ./bin/



# Compile C file (.c) into MIPS object file (.o)
%.mips.o: %.c
	$(MIPS_CC) $(MIPS_CPPFLAGS) -c $< -o $@

	# Assemble MIPS assembly file (.s) into MIPS object file (.o)
%.mips.o: %.s
		$(MIPS_CC) $(MIPS_CPPFLAGS) -c $< -o $@

	# Link MIPS object file (.o), producing .elf, using memory locations specified in spec
%.mips.elf: %.mips.o
		$(MIPS_CC) $(MIPS_CPPFLAGS) $(MIPS_LDFLAGS) -T linker.ld $< -o $@

	# Extract binary instructions only from linked object file (.elf)
%.bin: %.mips.elf
		$(MIPS_OBJCOPY) -O binary --only-section=.text $< $@

	# Disassemble linked object file (.elf), pulling out instructions as MIPS assembly file (.s)
%.mips.s : %.mips.elf
		$(MIPS_OBJDUMP) -j .text -D $< > $@
