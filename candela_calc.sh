#!/bin/bash
echo "" >> curvegenheader.h
echo '/*' >> curvegenheader.h
echo '*		index : 0 ~ 255' >> curvegenheader.h
echo '*		350 is max CANDELA' >> curvegenheader.h
echo '*		(350*((index/255)^1.8))*4194304' >> curvegenheader.h
echo '*/' >> curvegenheader.h
echo '' >> curvegenheader.h
echo 'static int curve_1p8_350[] = {' >> curvegenheader.h

candela_func() {
	local bracket="$(qalc -t $1/255)"
	local exponent="$(qalc -t $bracket^1.8)"
	local multone="$(qalc -t 350*$exponent)"
	local multtwo="$(qalc -t $multone*4194304)"
	printf "%.0f" "$multtwo" >> curvegenheader.h
	echo ' ,' >> curvegenheader.h
}

END=255
for ((i=0;i<=END;i++)); do
    candela_func $i
done
echo '};' >> curvegenheader.h
#endofseq
