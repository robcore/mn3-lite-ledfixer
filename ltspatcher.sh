#!/bin/bash

PATCHFILE="/root/mn3lite/lts-patchlist.txt"

reversepause() {

	printf "%s\n" "ltspatcher : $1"
	printf "%s\n" "Patch can be reversed! Probably already applied!"
	pause

}

failpause() {

	printf "%s\n" "ltspatcher : $1"
	pause

}

pcheckrs() {

	if patch -p1 -R --dry-run < "$1"
	then
		reversepause "$1 failed"
	elif patch -p1 --dry-run < "$1"
	then
		patch -p1 < "$1"
		echo "$1 Applied Cleanly."
	else
		failpause "$1 Does not apply cleanly"
	fi

}

while IFS= read -r PATCHLINE
do
	if [ "$PATCHLINE" = "/root/linux-stable/patches/0820-Linux-3.4.11.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/1038-Linux-3.4.12.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/1091-Linux-3.4.13.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/1212-Linux-3.4.14.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/1275-Linux-3.4.15.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/1318-Linux-3.4.16.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/1373-Linux-3.4.17.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/1386-Linux-3.4.18.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/1446-Linux-3.4.19.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/1617-Linux-3.4.20.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/1674-Linux-3.4.21.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/1676-Linux-3.4.22.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/1696-Linux-3.4.23.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/1725-Linux-3.4.24.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/1806-Linux-3.4.25.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/1978-Linux-3.4.26.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/2000-Linux-3.4.27.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/2023-Linux-3.4.28.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/2057-Linux-3.4.29.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/2084-Linux-3.4.30.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/2121-Linux-3.4.31.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/2130-Linux-3.4.32.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/2218-Linux-3.4.34.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/2265-Linux-3.4.35.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/2306-Linux-3.4.36.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/2355-Linux-3.4.37.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/2428-Linux-3.4.38.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/2498-Linux-3.4.39.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/2528-Linux-3.4.40.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/2547-Linux-3.4.41.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/2574-Linux-3.4.42.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/2609-Linux-3.4.43.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/2672-Linux-3.4.44.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/2699-Linux-3.4.45.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/2750-Linux-3.4.46.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/2756-Linux-3.4.47.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/2801-Linux-3.4.48.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/2834-Linux-3.4.49.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/2861-Linux-3.4.50.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/2889-Linux-3.4.51.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/2902-Linux-3.4.52.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/2914-Linux-3.4.53.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/2939-Linux-3.4.54.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/2999-Linux-3.4.55.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/3039-Linux-3.4.56.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/3065-Linux-3.4.57.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/3083-Linux-3.4.58.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/3117-Linux-3.4.59.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/3131-Linux-3.4.60.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/3146-Linux-3.4.61.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/3170-Linux-3.4.62.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/3211-Linux-3.4.63.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/3234-Linux-3.4.64.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/3250-Linux-3.4.65.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/3297-Linux-3.4.66.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/3309-Linux-3.4.67.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/3342-Linux-3.4.68.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/3369-Linux-3.4.69.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/3381-Linux-3.4.70.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/3421-Linux-3.4.71.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/3482-Linux-3.4.72.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/3515-Linux-3.4.73.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/3542-Linux-3.4.74.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/3575-Linux-3.4.75.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/3618-Linux-3.4.76.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/3646-Linux-3.4.77.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/3656-Linux-3.4.78.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/3693-Linux-3.4.79.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/3724-Linux-3.4.80.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/3749-Linux-3.4.81.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/3775-Linux-3.4.82.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/3873-Linux-3.4.83.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/3909-Linux-3.4.84.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/3923-Linux-3.4.85.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/3930-Linux-3.4.86.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/4065-Linux-3.4.87.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/4093-Linux-3.4.88.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/4137-Linux-3.4.89.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/4160-Linux-3.4.90.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/4170-Linux-3.4.91.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/4391-Linux-3.4.92.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/4470-Linux-3.4.93.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/4479-Linux-3.4.94.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/4506-Linux-3.4.95.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/4550-Linux-3.4.96.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/4570-Linux-3.4.97.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/4617-Linux-3.4.98.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/4634-Linux-3.4.99.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/4658-Linux-3.4.100.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/4669-Linux-3.4.101.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/4689-Linux-3.4.102.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/4713-Linux-3.4.103.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/4759-Linux-3.4.104.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/4851-Linux-3.4.105.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/5033-Linux-3.4.106.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/5210-Linux-3.4.107.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/5384-Linux-3.4.108.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/5530-Linux-3.4.109.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/5597-Linux-3.4.110.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/5704-Linux-3.4.111.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/5797-Linux-3.4.112.patch" ] || \
	   [ "$PATCHLINE" = "/root/linux-stable/patches/5929-Linux-3.4.113.patch" ]
	then
		echo "$PATCHLINE reached"
		pause
	else
		pcheckrs "$PATCHLINE"
	fi

done < "$PATCHFILE"
