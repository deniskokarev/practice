#!/usr/bin/bash
#
# Hackerrank https://www.hackerrank.com/challenges/lonely-integer-2
#
typeset -i SUM=0

read SZ
read LN
for I in $LN; do
	((SUM=SUM ^ I))
done
echo $SUM
