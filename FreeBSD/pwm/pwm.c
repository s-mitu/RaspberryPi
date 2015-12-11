#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <libgpio.h>
#include <sys/time.h>

#include <signal.h>

#define PWM_MIN	600
#define PWM_MAX	2360
#define PWM_NEUTRAL 1230
#define PWM_CYCLE	15 * 1000 

//int g_interval = PWM_NEUTRAL;
int g_interval = PWM_MIN;
//int g_interval = PWM_MAX;
int g_flag_high = 0;
gpio_handle_t g_gh;
gpio_pin_t g_pin = 0;

struct itimerval itimer;

/*
 * PWM 出力用アラームハンドラ
 */
void handler_pulse(int sig)
{
	if (g_flag_high) {
		/* High */
		itimer.it_value.tv_usec = g_interval;
		gpio_pin_high(g_gh, g_pin);
		g_flag_high = 0;
		
	} else {
		/* Low */
		itimer.it_value.tv_usec = PWM_CYCLE - g_interval;
		gpio_pin_low(g_gh, g_pin);
		g_flag_high = 1;
	}
	setitimer(ITIMER_REAL, &itimer, NULL);
}

int main(int argc, char *argv[])
{
	g_gh = gpio_open(0);

	struct sigaction act = {
		.sa_handler = handler_pulse,
		.sa_flags = SA_RESTART

	};
	int i = 0;

	if (argc < 2) {
		fprintf(stderr, "Few arguments\n");
		return 1;
	}
	if (argc >= 2) {
		if ((g_pin = strtol(argv[1], NULL, 0)) <= 0) {
			fprintf(stderr, "Invalid argument\n");
			return 1;
		}
	}
	if (argc == 3) {
		int angle;
		angle = strtol(argv[2], NULL, 0);
		if (angle >= 0) {
			g_interval = (int)(((PWM_MAX - PWM_NEUTRAL)/110.0) *angle + PWM_NEUTRAL);
		} else {
			g_interval = (int)(-((PWM_NEUTRAL - PWM_MIN)/70.0) *(-angle) + PWM_NEUTRAL);
		
		}
		printf("g_interval: %d\n", g_interval);
		
	} else if (argc == 2){
		g_interval = PWM_NEUTRAL;
	}
	sigemptyset(&act.sa_mask);

	if (sigaction(SIGALRM, &act, NULL) < 0) {
		fprintf(stderr, "Signal setting error\n");
		return 1;	
	}
	itimer.it_value.tv_usec = PWM_CYCLE - g_interval;
	
	setitimer(ITIMER_REAL, &itimer, NULL);
	gpio_pin_output(g_gh, g_pin);
	for (i = 0; i < 50; i++) {
		usleep(PWM_CYCLE);
	}
	
	gpio_close(g_gh);

	return 0;	
}
