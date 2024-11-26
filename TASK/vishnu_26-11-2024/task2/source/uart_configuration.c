#include"header.h"
int main(int argc,char *argv[])
{
	if(argc<2)
	{
		perror("argc");
		return 1;
	}
    int serial_port= open(argv[1],O_RDWR);
    if (serial_port<0) {
        perror("serial_port");
        return 1;
    }
    struct termios tty;
    if (tcgetattr(serial_port,&tty) != 0) {
        printf("error %i %s\n", errno, strerror(errno));
        return 1;
    }
    tty.c_cflag|=(CREAD|CLOCAL);
    tty.c_cflag&=~(CRTSCTS|CSIZE|CSTOPB|PARENB);
    tty.c_cflag|=CS8;
    tty.c_oflag&=~(OPOST|ONLCR);
    tty.c_iflag&=~(IGNBRK|ISTRIP|BRKINT|INLCR|IXON|IXOFF|PARMRK|ICRNL|IXANY);
    tty.c_lflag&=~(ECHO|ECHOE|ECHONL|ISIG|ICANON);
    tty.c_cc[VMIN]= SERIAL_READ_MIN;
    tty.c_cc[VTIME]=SERIAL_READ_TIMEOUT;
    cfsetispeed(&tty, B115200);
    cfsetospeed(&tty, B115200);
    if (tcsetattr(serial_port, TCSANOW, &tty) != 0)
    {
        perror("tcsetattr");
        return 1;
    }
    while (1)
    {
	    char input_char=getchar();
	    if (write(serial_port, &input_char, sizeof(input_char))<0)
	    {
		    perror("Error writing  serial port");
            	    break;
	    }
	    char received_char;
	    int bytes_read=read(serial_port,&received_char,sizeof(received_char));
	    if (bytes_read< 0) {
		    perror("Error reading from serial port");
		    break;
	    }
	    else if (bytes_read==0) {
		    printf("No data received within the timeout.\n");
	    }
	    else {
		    printf("Received: %c\n",received_char);
	    }
    }
    close(serial_port);
}
