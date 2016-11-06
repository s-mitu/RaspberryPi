## FreeBSD で RaspberryPi

鈴木光宏(@s_mitu)

---

## 自己紹介
## <img width="100" src="images/icon.png"/>

* 鈴木光宏(@s_mitu) 
 * なんちゃって組み込み系(i386系 CPU でFreeBSD/Linux 入れて動く機械を作る)
 * 最近は arm 系も(Linuxですが)
 * 電子工作は初心者に毛が生えなかった感じ
 * ネコとマヌルネコとダム画像ばかり流れてくる twitter アカウント @s_mitu

---

## RaspberryPi で FreeBSD

* 対応ボード
 * Raspberry Pi A/B (GPIO / I2C / Audio /Camera(要細工))
 * Raspberry Pi Zero (GPIO / I2C/Camera は動かない)
 * Raspberry Pi 2 (V1.2 は動かないかも) (GPIO / I2C / Audio / Camera)
 * Raspberry Pi 3 (GPIO) arm64 として動きます。
 

---
## RaspberryPi を FreeBSD を動かすメリット
 * 現時点あまりない
 * RaspberryPi の様々な機能を楽に動かすなら Raspbian でいい。
 * X 使わないとかなら、容量を食わない。
 * FreeBSD に慣れた人が GPIOや I2Cで遊べる。
 * 別のOSでRaspberryPiを動かしてみたい。
 * 徳を積んで来世デーモンに生まれ変わりたい人。
 * 色々な人が遊び倒していくうちに新たな可能性が見えてくるかも。

---
## 情報源

 * https://wiki.freebsd.org/FreeBSD/arm/Raspberry%20Pi (古い情報も)
 * https://raspbsd.org (イメージ)
 * freebsd-arm ML (https://lists.freebsd.org/pipermail/freebsd-arm/)


---
### インストール手順
 * イメージをダウンロード
 * dd でSDに書き込み
 * SD挿して起動

---
## イメージ
 * RaspBSD (http://www.raspbsd.org/raspberrypi.html)
  * Pi Zero は Raspberry Pi (A & B)を使う。

---
## SD書き込み
 * ダウンロードしてきたイメージをSDにdd
  * # zcat FreeBSD-armv6-12.0-RPI2-307523.img.gz | dd of=/dev/da0 bs=2m
 * でかい容量でも起動時に領域がリサイズされて全体が使えるようになる。
  * 初回起動時はこの処理でちょっと時間がかかる

---
## SD挿して起動
 * User: root パスワードなし 
 * User: raspberry  raspberry
 * 有線LANはDHCPなら挿してれば使える(ue0)

---
## 実演
 
---
## 以上です
