cc=gcc
cflags=-Iinclude
src1=source/uart_configuration.c
target1=built/usb_to_uart_serial
$(target1):$(src1)
	$(cc) $(cflags) $(src1)  -o $(target1)
clean:
	rm -rf $(target1)
