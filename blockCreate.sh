#!/usr/bin/env bash

x=1400
y=300
i=1
name="BlockSimple"
prefabName="BlockSimple"

for (( c=1; c<=10; c++ ))
do
    echo -ne "\"$name"
    echo -ne "$i"
    echo -ne "\" : {\n\"prefabName\": \"$prefabName\",\n\"position\": {\n\"x\": \"$x\",\n\"y\": \"$y\"\n}\n},"
    x=$(($x+94))
    i=$(($i+1))
done