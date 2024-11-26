cc=gcc
cflags=-Iinclude
src1=source/ttyACM0_configuration.c
target=built/read_from_acm

$(target):$(src1)
	$(cc) $(cflags) $(src1)  -o $(target)
clean:
	rm -rf $(target) 
