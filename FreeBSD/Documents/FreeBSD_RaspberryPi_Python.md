# Python で GPIO 操作

鈴木光宏(@s_mitu)

---

## 自己紹介

* 鈴木光宏(@s_mitu)
 * なんちゃって組み込み系(i386系 CPU でFreeBSD/Linux 入れて動く機械を作る)
 * 最近は arm 系も(Linuxですが)
 * マヌルネコとダム画像ばかり流れてくる twitter アカウント @s_mitu

---

## Raspberry Pi といえば Python

* Pi = Python だとか
* Raspbian では GPIO など低レベルを叩けるライブラリが充実
* FreeBSD で使う分には関係ない。
* でも高級言語と充実したライブラリは魅力

---

## GPIO 操作用 Python + FreeBSD ライブラリ

* freebsd-gpio https://github.com/gonzoua/freebsd-gpio
 * 下の方がメンテがアクティブですよと勧められる
* fbsd_gpio_py https://github.com/evadot/fbsd_gpio_py
 * 今回はこちらを利用

--- 

