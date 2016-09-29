## Python で GPIO 操作

鈴木光宏(@s_mitu)

---

## 自己紹介
## <img width="100" src="images/icon.png"/>

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
 * FreeBSD wiki (https://wiki.freebsd.org/FreeBSD/arm/Raspberry%20Pi) からリンク
 * Perl/Ruby/Python のライブラリ
 * Pythonライブラリは下の方がメンテがアクティブですよと勧められる
* fbsd_gpio_py https://github.com/evadot/fbsd_gpio_py
 * 今回はこちらを利用

---

## インストール
* まず cffi を pkg でインストール
 * pkg install py27-cffi
* setup.pyでインストール
 * README.rst では pip でインストールとなっているが途中でコケる
 * python setup.py build
 * python setup.py install

--- 
<img src="images/tank.jpg"/>
