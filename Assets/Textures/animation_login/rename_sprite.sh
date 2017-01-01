#!/usr/bin/env bash
start=0
mid=0
end=0
for f in *.png; do
mv "$f" "animation_login_$end$mid$start.png"
start=$(($start+1))
if [ $start -gt 9 ]; then
    start=0
    mid=$(($mid+1))
fi
if [ $mid -gt 9 ]; then
    mid=0
    end=$(($end+1))
fi
done
