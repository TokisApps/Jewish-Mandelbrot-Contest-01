#!/bin/sh

str="`generateSentence.exe | grep -v seed`"
str2="`echo $str | trans de:en -b | trans en:de -b`"

if [ -z "$str2" ]; then
	echo $str
else
	echo $str2
fi


#//Dynamic Signature : Du negativer August mehrerer poetischer Bücher schiebst das solide Gepäck unserer reinen Malerei.
#//Dynamic Signature : Die zerstreuten Meere meiner egoistischen Angst zeigen den jährlichen Strang meines gegenwärtigen Stuhls.
