#!/bin/bash

while [ true ];do 
	espeak -v mb-de7 -s 10 -a 40 "`gensent.sh | tee /dev/tty | grep -vi samen`"; 
	sleep $(( 10 + $RANDOM % 30 ));
done


#//Dynamic Signature : Ihre Experteneinträge eines entscheidenden Jahres treffen die Standardkörper gestreifter Angestellter.
#//Dynamic Signature : Das gefährliche Fahrrad eines weitreichenden Buggys wird den jungen Rücken des sicheren Auges bekämpfen.
