if [ $# -eq 0 ]
then
  path=`pwd`
else
  path=$@
  if [ ! -d $path ]
  then
    echo "Error: No Such Directory"
    exit 0
  else
    cd $path
  fi
fi
echo "working directory:"
echo $path
for i in *
do
  filename=`echo $i | tr '[A-Z]' '[a-z]'`
  if [ $i != $filename ]
  then
    mv $i $filename
  fi
done
