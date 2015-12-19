○はじめに

秋月電子の i2c キャラクター液晶をFreeBSDのRaspberryPiで表示
するシェルスクリプトです。

液晶
8x2 http://akizukidenshi.com/catalog/g/gK-06795/
16x2 http://akizukidenshi.com/catalog/g/gK-08896/ 

i2c のコマンドとして、
https://github.com/vzaigrin/newi2c
のnewi2c.cをコンパイルしたものを /usr/local/bin に入っている
ことを前提としています。

○使い方

i2c-lcd.sh [-bulk] [-w num]  format [arguments]

i2c-lcd.sh -c

オプション

        -w
                折り返しのための液晶の文字幅(default:8)

        -b
             	全画面クリアしてから書き込み   

        -u
                上の行のみクリアして書き込み

        -l
                下の行のみクリアして書き込み

        -c
				画面クリア

	format
				printf 文字列
	arguments
				printf 引数

	例:
		i2c-lcd.sh -w 16 "Now Temp : %d" 20
