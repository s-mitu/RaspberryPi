#include <sys/types.h>
#include <sys/ioctl.h>
#include <dev/iicbus/iic.h>

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#define IICBUS	"/dev/iic1"

int main(int argc, char *argv[])
{
	int i;
	int fd;
	uint8_t cmdbuff[12] = {0};
	struct iiccmd start_cmd = {.slave = 0x48};
	struct iic_msg write_cmd[1] = {
			{
				.slave = 0x48 << 1 | IIC_M_RD,
				.flags = IIC_M_RD,
				.len = sizeof (cmdbuff),
				.buf = cmdbuff,
			}, 
	};
	struct iic_rdwr_data cmd = {
		.msgs =  write_cmd,
		.nmsgs = 1,
	};
	if ((fd = open(IICBUS, O_RDWR)) == -1) {
		fprintf(stderr, "%d Error %s\n", __LINE__, strerror(errno));
		return 1;
	}
	if (ioctl(fd, I2CRDWR, &cmd) == -1) {
		fprintf(stderr, "%d Error %s\n", __LINE__, strerror(errno));
	} else {
		float temp = (((cmdbuff[0] << 8) | cmdbuff[1]) >> 3) / 16.0f;
		printf("%02x %02x %02x %02x Temp: %g \n", cmdbuff[0], cmdbuff[1], cmdbuff[2], cmdbuff[3], temp);
	}
	close(fd);
	return 0;
}
