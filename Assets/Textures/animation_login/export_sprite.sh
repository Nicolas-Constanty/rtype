#!/usr/bin/env bash
echo "{
  \"mode\": \"LOOP\",
  \"framerate\": \"30\",
  \"sprites\": [" > animation_login.anim
for f in *.png; do
    echo "{
    \"texture\": \"animation_login/${f%.*}\",
    \"rect\": {
        \"x\": \"0\",
        \"y\": \"0\",
        \"width\": \"500\",
        \"heigth\": \"440\"
    }
}" > "${f%.*}.sprite"
echo "\"GUI/AnimLogin/${f%.*}\"," >> animation_login.anim
done

echo "]
}" >> animation_login.anim