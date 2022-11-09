#!/bin/bash

while [ true ];do 
	espeak -v mb-de7 -s 10 "`gensent.sh | tee /dev/tty`"; 
	sleep $(( 10 + $RANDOM % 30 ));
done


