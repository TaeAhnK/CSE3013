if [ $# -eq 0 ]
then
  path=`pwd`
else
  path=$@
  if [ -d $path -a -w $path ]
  then
    cd $path
  else
    echo "Error: Cannot move to the Directory (No Directory or Permission Denied)"
    exit 0
  fi
fi
echo "working directory:"
echo $path
for i in *
do
  filename=`echo $i | tr '[a-zA-Z]' '[A-Za-z]'`
  mv $i $filename
done
