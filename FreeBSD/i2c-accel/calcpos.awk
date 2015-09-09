#! /usr/bin/awk -f 
BEGIN{
	dt=0.029;
	vx0=0; vy0=0; vz0=0;
	x0=0; y0=0; z0=0
	g = 9.8;
	r = 3.9
}
{
	ax = ($2 * r * g) / 1000 
	ay = ($3 * r * g) / 1000
    az = ($4 * r * g) / 1000 - 9.8;
	vx = vx0 + ax * dt; 
	vy = vy0 + ay * dt;
	vz = vz0 + az * dt;
	x = x0 + vx * dt;
    y = y0 + vy * dt;
	z = z0 + vz * dt;
	vx0 = vx; vy0 = vy; vz0 = vz;
    x0 = x; y0 = y; z0 = z;
	printf("%g %g %g %g %g %g %g %g %g\n", ax, ay, az, vx, vy, vz, x, y, z);
}
