arg=$2
arg+='q;'
arg+=$1
arg+=','
arg+=$2
arg+='p'
echo $arg
sed -n $arg /media/lfdorelli/Data1/Mestrado/Twitter/resources/tweets  > tmp
