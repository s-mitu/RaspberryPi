#include <sys/types.h>
#include <sys/ioctl.h>
#include <dev/iicbus/iic.h>

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <unistd.h>
#include <time.h>

#define IICBUS	"/dev/iic1"
#define READBUFFSIZE	(0x3f + 1)
#define BUFFSIZE (1 + READBUFFSIZE)

#define ACCEL_RES (3.91F * 0.001F)
#define G 			(9.8F)
#define ACCEL(buff)  (((int16_t)((*(buff + 1) << 8) | *(buff))) >> 6) 

static struct timespec prevTime = {0};
long diffTime()
{
	struct timespec now;
	long retval;
	clock_gettime(CLOCK_MONOTONIC, &now);
	if (prevTime.tv_sec == 0) {
		retval = 0;
	} else {
		retval = (now.tv_sec - prevTime.tv_sec) * 1000 + (now.tv_nsec - prevTime.tv_nsec) / (1000 * 1000);
	}
	prevTime.tv_sec = now.tv_sec;
	prevTime.tv_nsec = now.tv_nsec;
	return retval;
}
void check_sensor(int fd)
{
	int i;
	uint8_t cmdbuff[BUFFSIZE] = {0};
	struct iic_msg read_cmd[BUFFSIZE];
	struct iic_rdwr_data cmd = {
		.msgs =  read_cmd,
		.nmsgs = BUFFSIZE,
	};
	memset(read_cmd, sizeof (read_cmd), 0);
	read_cmd[0].slave = 0x18 << 1 | !IIC_M_RD;
	read_cmd[0].flags = !IIC_M_RD;
	read_cmd[0].len = 1;
	read_cmd[0].buf = cmdbuff;
	for (i = 0; i < READBUFFSIZE; i++)
	{
		read_cmd[i + 1].slave = 0x18 << 1 | IIC_M_RD;
		read_cmd[i + 1].flags = IIC_M_RD;
		read_cmd[i + 1].len = 1;
		read_cmd[i + 1].buf = cmdbuff + i;
	};
	if (ioctl(fd, I2CRDWR, &cmd) == -1) {
		fprintf(stderr, "%d Error %s\n", __LINE__, strerror(errno));
	} else {
		int i;
		int accelx, accely, accelz;
		float temp;
		accelx = ACCEL(cmdbuff + 2);
		accely = ACCEL(cmdbuff + 4);
		accelz = ACCEL(cmdbuff + 6);
		//temp = 24.0 + (cmdbuff[8] * 0.5);
		printf("%ld %d %d %d\r", diffTime(), accelx, accely, accelz);
		//printf("%g %g %g %g\r", accelx * ACCEL_RES * G, accely * ACCEL_RES * G, accelz * ACCEL_RES * G, temp);
#ifdef NOTDEF
		for (i = 0; i < sizeof (cmdbuff); i++) {
			printf("%02x ", cmdbuff[i]);
			if (((i +1) % 8) == 0) printf(" ");
			if (((i +1) % 16) == 0) printf("\n");
		}
#endif
		printf("\n");
		fflush(stdout);
	}
}
int main(int argc, char *argv[])
{
	int fd;
	if ((fd = open(IICBUS, O_RDWR)) == -1) {
		fprintf(stderr, "%d Error %s\n", __LINE__, strerror(errno));
		return 1;
	}
	while(1) {
		check_sensor(fd);
		usleep(1 * 1000);
	}
	close(fd);
	return 0;
}
