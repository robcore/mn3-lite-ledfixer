#!/bin/bash

echo '/*' > curvegenheader.h
echo '*		index : 0 ~ 255' >> curvegenheader.h
echo '*		350 is max CANDELA' >> curvegenheader.h
echo '*		(350*((index/255)^1.65))*4194304' >> curvegenheader.h
echo '*/' >> curvegenheader.h
echo '' >> curvegenheader.h
echo 'static int curve_1p65_350[] = {' >> curvegenheader.h

candela_func65() {
	local bracket="$(qalc -t $1/255)"
	local exponent="$(qalc -t $bracket^1.65)"
	local multone="$(qalc -t 350*$exponent)"
	local multtwo="$(qalc -t $multone*4194304)"
	printf "%.0f" "$multtwo" >> curvegenheader.h
	echo ' ,' >> curvegenheader.h
}

END=255
for ((i=0;i<=END;i++)); do
    candela_func65 $i
done
echo '};' >> curvegenheader.h
#endofseq

echo '/*' >> curvegenheader.h
echo '*		index : 0 ~ 255' >> curvegenheader.h
echo '*		350 is max CANDELA' >> curvegenheader.h
echo '*		(350*((index/255)^1.6))*4194304' >> curvegenheader.h
echo '*/' >> curvegenheader.h
echo '' >> curvegenheader.h
echo 'static int curve_1p6_350[] = {' >> curvegenheader.h

candela_func6() {
	local bracket="$(qalc -t $1/255)"
	local exponent="$(qalc -t $bracket^1.6)"
	local multone="$(qalc -t 350*$exponent)"
	local multtwo="$(qalc -t $multone*4194304)"
	printf "%.0f" "$multtwo" >> curvegenheader.h
	echo ' ,' >> curvegenheader.h
}

END=255
for ((i=0;i<=END;i++)); do
    candela_func6 $i
done
echo '};' >> curvegenheader.h
