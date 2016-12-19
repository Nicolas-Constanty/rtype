#!/usr/bin/env bash

set -e

if [ -z "$1" ]
  then
    echo "No controller name supplied"
    exit
fi

controllerName=$1;
controllerNameUPPER=${controllerName^^}

rootDir=$( dirname "${BASH_SOURCE[0]}" )

defaultDir="${rootDir}/Assets/defaults/Controller/"


cp ${defaultDir}*.cpp .
cp ${defaultDir}*.hpp .

rename "{{Controller}}" ${controllerName} ./*.cpp
rename "{{Controller}}" ${controllerName} ./*.hpp

sed -i 's/{{CONTROLLER}}/'"${controllerNameUPPER}"'/g' ./*.cpp
sed -i 's/{{Controller}}/'"${controllerName}"'/g' ./*.cpp
sed -i 's/{{CONTROLLER}}/'"${controllerNameUPPER}"'/g' ./*.hpp
sed -i 's/{{Controller}}/'"${controllerName}"'/g' ./*.hpp