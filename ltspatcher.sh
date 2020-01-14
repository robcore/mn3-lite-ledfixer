#!/bin/bash

if [ "$1" = "debug" ]
then
	DODEBUG="YES"
else
	DODEBUG="NO"
fi

PATCHFILE="/root/mn3lite/ltspatchlistforscript.txt"

#oldpause() {
#
#	printf "%s\r" "                                   "; \
#	printf "%s\n" " "
#	printf "%s" "Press [Enter] key to continue..."
#	read -p $*
#}

animatepausedbg() {

while :
do
	printf "%s\r" "----------SHELL-IS-PAUSED----------"; \
	sleep 0.1; \
	printf "%s\r" "--------- SHELL IS PAUSED ---------"; \
	sleep 0.1; \
	printf "%s\r" "--------  SHELL IS PAUSED  --------"; \
	sleep 0.1; \
	printf "%s\r" "-------   SHELL IS PAUSED   -------"; \
	sleep 0.1; \
	printf "%s\r" "------    SHELL IS PAUSED    ------"; \
	sleep 0.1; \
	printf "%s\r" "-----     SHELL IS PAUSED     -----"; \
	sleep 0.1; \
	printf "%s\r" "----      SHELL IS PAUSED      ----"; \
	sleep 0.1; \
	printf "%s\r" "---       SHELL IS PAUSED       ---"; \
	sleep 0.1; \
	printf "%s\r" "--        SHELL IS PAUSED        --"; \
	sleep 0.1; \
	printf "%s\r" "-         SHELL IS PAUSED         -"; \
	sleep 0.1; \
	printf "%s\r" "          SHELL IS PAUSED          "; \
	sleep 0.1; \
	printf "%s\r" "-         SHELL IS PAUSED         -"; \
	sleep 0.1; \
	printf "%s\r" "--        SHELL IS PAUSED        --"; \
	sleep 0.1; \
	printf "%s\r" "---       SHELL IS PAUSED       ---"; \
	sleep 0.1; \
	printf "%s\r" "----      SHELL IS PAUSED      ----"; \
	sleep 0.1; \
	printf "%s\r" "-----     SHELL IS PAUSED     -----"; \
	sleep 0.1; \
	printf "%s\r" "------    SHELL IS PAUSED    ------"; \
	sleep 0.1; \
	printf "%s\r" "-------   SHELL IS PAUSED   -------"; \
	sleep 0.1; \
	printf "%s\r" "--------  SHELL IS PAUSED  --------"; \
	sleep 0.1; \
	printf "%s\r" "--------- SHELL IS PAUSED ---------"; \
	sleep 0.1; \
done

}

animatepause() {

	printf "%s\r" "----------SHELL-IS-PAUSED----------"; \
	sleep 0.1; \
	printf "%s\r" "--------- SHELL IS PAUSED ---------"; \
	sleep 0.1; \
	printf "%s\r" "--------  SHELL IS PAUSED  --------"; \
	sleep 0.1; \
	printf "%s\r" "-------   SHELL IS PAUSED   -------"; \
	sleep 0.1; \
	printf "%s\r" "------    SHELL IS PAUSED    ------"; \
	sleep 0.1; \
	printf "%s\r" "-----     SHELL IS PAUSED     -----"; \
	sleep 0.1; \
	printf "%s\r" "----      SHELL IS PAUSED      ----"; \
	sleep 0.1; \
	printf "%s\r" "---       SHELL IS PAUSED       ---"; \
	sleep 0.1; \
	printf "%s\r" "--        SHELL IS PAUSED        --"; \
	sleep 0.1; \
	printf "%s\r" "-         SHELL IS PAUSED         -"; \
	sleep 0.1; \
	printf "%s\r" "          SHELL IS PAUSED          "; \
	sleep 0.1; \
	printf "%s\r" "-         SHELL IS PAUSED         -"; \
	sleep 0.1; \
	printf "%s\r" "--        SHELL IS PAUSED        --"; \
	sleep 0.1; \
	printf "%s\r" "---       SHELL IS PAUSED       ---"; \
	sleep 0.1; \
	printf "%s\r" "----      SHELL IS PAUSED      ----"; \
	sleep 0.1; \
	printf "%s\r" "-----     SHELL IS PAUSED     -----"; \
	sleep 0.1; \
	printf "%s\r" "------    SHELL IS PAUSED    ------"; \
	sleep 0.1; \
	printf "%s\r" "-------   SHELL IS PAUSED   -------"; \
	sleep 0.1; \
	printf "%s\r" "--------  SHELL IS PAUSED  --------"; \
	sleep 0.1; \
	printf "%s\r" "--------- SHELL IS PAUSED ---------"; \
	sleep 0.1; \

}

if [ "DODEBUG" = "YES" ] || [ "$1" = "debug" ]
then
while IFS= read -r PATCHLINE
do
	if [ "$PATCHLINE" = "/root/linux-stable/patches/2428-Linux-3.4.38.patch" ] || \
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
		BCOUNT="$(echo $PATCHLINE | wc -c)"
		if [ "$BCOUNT" -eq 51 ]
		then
			echo "$(echo $PATCHLINE | cut --bytes=33-44) reached"
		elif [ "$BCOUNT" -eq 52 ]
			echo "$(echo $PATCHLINE | cut --bytes=33-45) reached"
		else
			echo "$PATCHLINE reached"
		fi
		animatepausedbg
	elif grep '/drivers/usb/' "$PATCHLINE"
	then
		echo "This would patch /drivers/usb/ ignoring!"
			animatepausedbg
	elif grep '/drivers/mmc/' "$PATCHLINE"
	then
		echo "This would patch /drivers/mmc/ ignoring!"
			animatepausedbg
	elif grep '/drivers/hid/' "$PATCHLINE"
	then
		echo "This would patch /drivers/hid/ ignoring!"
		animatepausedbg
	elif patch -p1 -R --dry-run < "$PATCHLINE" &> /dev/null
	then
		echo "$PATCHLINE was already applied! Doing Nothing!"
		echo ""
		animatepausedbg
	elif patch -p1 --dry-run < "$PATCHLINE" &> /dev/null
	then
		echo "Dry Run Succeeded!"
		echo "Applying $PATCHLINE"
		echo ""
		patch -p1 --dry-run < "$PATCHLINE"
	else
		printf "%s\n" "Dry run failed!"
		animatepausedbg
	fi
done < "$PATCHFILE"
else
while IFS= read -r PATCHLINE
do
	if [ "$PATCHLINE" = "/root/linux-stable/patches/2428-Linux-3.4.38.patch" ] || \
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
		BCOUNT="$(echo $PATCHLINE | wc -c)"
		if [ "$BCOUNT" -eq 51 ]
		then
			echo "$(echo $PATCHLINE | cut --bytes=33-44) reached"
		elif [ "$BCOUNT" -eq 52 ]
			echo "$(echo $PATCHLINE | cut --bytes=33-45) reached"
		else
			echo "$PATCHLINE reached"
		fi
		while :
		do
			animatepause
		done
	elif grep '/drivers/usb/' "$PATCHLINE"
	then
		echo "This would patch /drivers/usb/ ignoring!"
		while :
		do
			animatepause
		done
	elif grep '/drivers/mmc/' "$PATCHLINE"
	then
		echo "This would patch /drivers/mmc/ ignoring!"
		while :
		do
			animatepause
		done
	elif grep '/drivers/hid/' "$PATCHLINE"
	then
		echo "This would patch /drivers/hid/ ignoring!"
		while :
		do
			animatepause
		done
	elif patch -p1 -R --dry-run < "$PATCHLINE" &> /dev/null
	then
		echo "$PATCHLINE was already applied! Doing Nothing!"
		echo ""
		while :
		do
			animatepause
		done
	elif patch -p1 --dry-run < "$PATCHLINE" &> /dev/null
	then
		echo "Dry Run Succeeded!"
		echo "Applying $PATCHLINE"
		echo ""
		patch -p1 < "$PATCHLINE"
	else
		printf "%s\n" "Dry run failed!"
		while :
		do
			animatepause
		done
	fi
done < "$PATCHFILE"
fi
