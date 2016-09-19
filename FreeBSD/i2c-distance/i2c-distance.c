#include <sys/types.h>
#include <sys/ioctl.h>
#include <dev/iicbus/iic.h>
#include <libgpio.h>

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>

#define IICBUS	"/dev/iic1"
#define GPIODEV "/dev/gpioc0"

int main(int argc, char *argv[])
{
	int i;
	int fd;
	uint8_t cmdbuff[256] = {0};
	struct iic_msg write_cmd[2] = {
			{
				.slave = 0x40 << 1 | !IIC_M_RD,
				.flags = !IIC_M_RD,
				.len = 1,
				.buf = cmdbuff,
			},
			{
				.slave = 0x40 << 1 | IIC_M_RD,
				.flags = IIC_M_RD,
				.len = sizeof (cmdbuff),
				.buf = cmdbuff,
			}, 
	};
	struct iic_rdwr_data cmd = {
		.msgs =  write_cmd,
		.nmsgs = 2,
	};
	if ((fd = open(IICBUS, O_RDWR)) == -1) {
		fprintf(stderr, "%d Error %s\n", __LINE__, strerror(errno));
		return 1;
	}
	if (ioctl(fd, I2CRDWR, &cmd) == -1) {
		fprintf(stderr, "%d Error %s\n", __LINE__, strerror(errno));
	} else {
		if (cmdbuff[0x35] == 0x01 || cmdbuff[0x35] == 0x02) {
			int bitshift = 1 << cmdbuff[0x35];
			float distance = (((cmdbuff[0x5e] << 4) + cmdbuff[0x5f]) / 16.0f) / bitshift;
			printf("%g %02x %02x %02x \n", distance, cmdbuff[0x35], cmdbuff[0x5e], cmdbuff[0x5f]);
		} else {
			printf("%02x\n", cmdbuff[0x00]);
		}
	}
	close(fd);
	return 0;
}
