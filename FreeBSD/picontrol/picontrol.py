#!/usr/local/bin/python2.7
# -*- coding: utf-8 -*-

from flask import Flask, jsonify
import subprocess
from time import sleep
from fbsd_gpio import GpioController, GPIO_VALUE_HIGH, GPIO_VALUE_LOW, GPIO_PIN_OUTPUT
import datetime

gpioc = GpioController(0)

pin1 = gpioc.pin(19)
pin2 = gpioc.pin(20)
pin3 = gpioc.pin(21)
pin4 = gpioc.pin(26)

led = gpioc.pin(5)
led2 = gpioc.pin(4)

pin1.output = True
pin2.output = True
led.output = True

# start distance subprocess
subprocess.Popen(['/usr/local/bin/distance_loop', '18'])

app = Flask(__name__)

@app.route("/")
def controllpage():
	try:
		return open("/usr/local/picontrol/picontrol.html", "r").read()
	except IOError:
		return "準備不足でした。"

@app.route("/wallpaler")
def wallpaper():
        try:
            return open("freebsd_wallpaper_by_nohup.jpg", "r").read()
	except IOError:
		return ""



#@app.route("/start")

# 前進
@app.route("/front")
def motorFront():
	pin1.high()
	pin2.low()
	pin3.high()
	pin4.low()
	led2.low()
	return "OK"

# 後進
@app.route("/back")
def motorBack():
	pin1.low()
	pin2.high()
	pin3.low()
	pin4.high()
	led2.low()
	return "OK"

# 超信地旋回R
@app.route("/pivotturn_r")
def motorPivotTurnR():
	pin1.low()
	pin2.high()
	pin3.high()
	pin4.low()
	led2.low()
	now = datetime.datetime.today().strftime("%Y-%m-%d %H:%M:%S")
	subprocess.Popen(["/usr/local/tankannounce/tankannounce.py", now + " 右回転中"])
	return "OK"

# 超信地旋回l
@app.route("/pivotturn_l")
def motorPivotTurnL():
	pin1.high()
	pin2.low()
	pin3.low()
	pin4.high()
	led2.low()
	now = datetime.datetime.today().strftime("%Y-%m-%d %H:%M:%S")
	subprocess.Popen(["/usr/local/tankannounce/tankannounce.py", now + " 左回転中"])
	return "OK"

# 
@app.route("/swing")
def motorSwing():
	for i in range(5):
		motorFront()
		sleep(1)
		motorBack()
		sleep(1)
		motorStop()
	return "OK"

# 停止
@app.route("/stop")
def motorStop():
	pin1.low()
	pin2.low()
	pin3.low()
	pin4.low()
	led.high()
	led2.high()
	now = datetime.datetime.today().strftime("%Y-%m-%d %H:%M:%S")
	subprocess.Popen(["/usr/local/tankannounce/tankannounce.py", now + " 停止"])
	return "OK"

# 距離取得
@app.route("/distance.json")
def distance():
	fdistance = open('/tmp/distance.txt', "r")
	ret = fdistance.read()
	fdistance.close()

	return jsonify(dist=ret)

led.high()
if __name__ == "__main__":
	app.run(host='0.0.0.0')
led.low()
subprocess.Popen.terminate()
