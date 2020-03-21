#!/bin/bash

candela_func() {
	local bracket="$(qalc -t $1/255)"
	local exponent="$(qalc -t $bracket^1.6)"
	local multone="$(qalc -t 300*$exponent)"
	local multtwo="$(qalc -t $multone*4194304)"
	printf "%.0f" "$multtwo"
	echo ' ,'
	#echo "$1 out of 255 = $multtwo"
}

END=255
for ((i=0;i<=END;i++)); do
    candela_func $i
done
