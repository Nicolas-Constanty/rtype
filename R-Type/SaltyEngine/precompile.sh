rm -rf GameObject.inl
for f in *.hpp; do
mkdir -p "compilation" && awk '!seen[$0]++' $f > "compilation/$f";
sed -n -e 's/^.*\(@Register<.*>\)/\1/p' "compilation/$f" | sed -e 's/.*<\(.*\)>/\1/' >> GameObject.inl;
grep -v "@Register" "compilation/$f" | grep -v "//" | grep -ve "/\*.*\*/" > "compilation/temp_$f" && mv "compilation/temp_$f" "compilation/$f";
done
cp GameObject.inl compilation/GameObject.inl
