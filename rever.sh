#!/bin/bash

while read -r REVCOM
do
    if [ ! -f "$REVCOM" ]
    then
        echo "$REVCOM does not exist, exiting!"
        exit 1
    fi

    echo "Reverting $REVCOM"
    if ! patch -p1 -R < "$REVCOM"
    then
        echo "Patch Reversion Failed! Exiting!"
        echo "Last patch reverted was $REVCOM"
        exit 1
    fi
done < "/root/mn3-lite-ledfixer/revcommits"
