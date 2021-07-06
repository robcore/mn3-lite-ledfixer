#!/bin/bash

candela_func_1p8() {
	local bracket="$(qalc -t $1/255)"
	local exponent="$(qalc -t $bracket^1.8)"
	local multone="$(qalc -t 300*$exponent)"
	local multtwo="$(qalc -t $multone*4194304)"
	printf "%.0f" "$multtwo" >> curvegenheader.h
	echo ' ,' >> curvegenheader.h
}

candela_func_1p8_350() {
	local bracket="$(qalc -t $1/255)"
	local exponent="$(qalc -t $bracket^1.8)"
	local multone="$(qalc -t 350*$exponent)"
	local multtwo="$(qalc -t $multone*4194304)"
	printf "%.0f" "$multtwo" >> curvegenheader.h
	echo ' ,' >> curvegenheader.h
}

candela_func_1p85() {
	local bracket="$(qalc -t $1/255)"
	local exponent="$(qalc -t $bracket^1.85)"
	local multone="$(qalc -t 300*$exponent)"
	local multtwo="$(qalc -t $multone*4194304)"
	printf "%.0f" "$multtwo" >> curvegenheader.h
	echo ' ,' >> curvegenheader.h
}

candela_func_1p85_350() {
	local bracket="$(qalc -t $1/255)"
	local exponent="$(qalc -t $bracket^1.85)"
	local multone="$(qalc -t 350*$exponent)"
	local multtwo="$(qalc -t $multone*4194304)"
	printf "%.0f" "$multtwo" >> curvegenheader.h
	echo ' ,' >> curvegenheader.h
}

END=255

rm curvegenheader.h &>/dev/null
touch curvegenheader.h

echo "1.8 300 candela table"
echo "" >> curvegenheader.h
echo '/*' >> curvegenheader.h
echo '*		index : 0 ~ 255' >> curvegenheader.h
echo '*		300 is max CANDELA' >> curvegenheader.h
echo '*		(300*((index/255)^1.8))*4194304' >> curvegenheader.h
echo '*/' >> curvegenheader.h
echo '' >> curvegenheader.h
echo 'static int curve_1p8[] = {' >> curvegenheader.h
for ((i=0;i<=END;i++)); do
	echo "Calculating $i/255"
    candela_func_1p8 $i
done
echo '};' >> curvegenheader.h
echo "1.8 350 candela table"
echo "" >> curvegenheader.h
echo '/*' >> curvegenheader.h
echo '*		index : 0 ~ 255' >> curvegenheader.h
echo '*		350 is max CANDELA' >> curvegenheader.h
echo '*		(350*((index/255)^1.8))*4194304' >> curvegenheader.h
echo '*/' >> curvegenheader.h
echo '' >> curvegenheader.h
echo 'static int curve_1p8_350[] = {' >> curvegenheader.h
for ((i=0;i<=END;i++)); do
	echo "Calculating $i/255"
    candela_func_1p8_350 $i
done
echo '};' >> curvegenheader.h

echo "1.85 300 candela table"
echo "" >> curvegenheader.h
echo '/*' >> curvegenheader.h
echo '*		index : 0 ~ 255' >> curvegenheader.h
echo '*		300 is max CANDELA' >> curvegenheader.h
echo '*		(300*((index/255)^1.85))*4194304' >> curvegenheader.h
echo '*/' >> curvegenheader.h
echo '' >> curvegenheader.h
echo 'static int curve_1p85[] = {' >> curvegenheader.h
for ((i=0;i<=END;i++)); do
	echo "Calculating $i/255"
    candela_func_1p85 $i
done
echo '};' >> curvegenheader.h
echo "1.85 350 candela table"
echo "" >> curvegenheader.h
echo '/*' >> curvegenheader.h
echo '*		index : 0 ~ 255' >> curvegenheader.h
echo '*		350 is max CANDELA' >> curvegenheader.h
echo '*		(350*((index/255)^1.85))*4194304' >> curvegenheader.h
echo '*/' >> curvegenheader.h
echo '' >> curvegenheader.h
echo 'static int curve_1p85_350[] = {' >> curvegenheader.h
for ((i=0;i<=END;i++)); do
	echo "Calculating $i/255"
    candela_func_1p85_350 $i
done
echo '};' >> curvegenheader.h
