#!/usr/bin/env bash

set -e

if [ -z "$1" ]
  then
    echo "No prefab name supplied"
    exit
fi

prefabName=$1;
prefabNameUPPER=${prefabName^^}

defaultDir="Assets/defaults/Prefab/"

#testDir="test/"

srcDir="${testDir}src/"
incDir="${testDir}include/"
prefabsDir="Prefabs/"

prefabSrcDir=${srcDir}${prefabsDir}${prefabName}
prefabIncDir=${incDir}${prefabsDir}${prefabName}

mkdir -p ${prefabSrcDir}
mkdir -p ${prefabIncDir}

cp ${defaultDir}*.cpp ${prefabSrcDir}${PrefabName}
cp ${defaultDir}*.hpp ${prefabIncDir}${PrefabName}

rename "{{Prefab}}" ${prefabName} ${prefabSrcDir}${PrefabName}/*.cpp
rename "{{Prefab}}" ${prefabName} ${prefabIncDir}${PrefabName}/*.hpp

sed -i 's/{{PREFAB}}/'"${prefabNameUPPER}"'/g' ${prefabSrcDir}${PrefabName}/*.cpp
sed -i 's/{{Prefab}}/'"${prefabName}"'/g' ${prefabSrcDir}${PrefabName}/*.cpp
sed -i 's/{{PREFAB}}/'"${prefabNameUPPER}"'/g' ${prefabIncDir}${PrefabName}/*.hpp
sed -i 's/{{Prefab}}/'"${prefabName}"'/g' ${prefabIncDir}${PrefabName}/*.hpp