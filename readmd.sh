#!/bin/bash

count=0
while IFS= read -r MDLINE
do
	echo -n '[' >> newmdreadme
	echo -n "$count" >> newmdreadme
	echo -n ']' >> newmdreadme
	echo -n '  ' >> newmdreadme
	echo "$MDLINE" >> newmdreadme
	((count++))

done < mdreadme
echo "$count"
