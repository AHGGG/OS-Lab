#!/bin/bash


clear

file_size='0'	
temp='0'	

echo -n "Input your filename:"
read filename

if [ -e $filename ]
then	
	echo "File [ $filename ] exists"
	ls -l $filename
else	
	echo "Can't find the file [ $filename ] "
	exit 0
fi

test_time=0		
change_time=0	

while [ $test_time -lt 10 ] && [ $change_time -lt 2 ]
do
	echo "test file's status ... "
	temp=`ls -l "$filename" |cut -d ' ' -f 5`

    if [ $temp == $file_size ]
    then       
        echo "file_size = [ $file_size ] "
		((test_time=test_time+1))
    else
        file_size="$temp"       
        echo "file [ $filename ] size changed"
        echo "file_size = [ $file_size ] "
		((change_time=change_time+1))
        ((test_time=0))
    fi
	sleep 5
done

if [ $change_time -ge 2 ]
then
	echo "Change number exceed 2, test end!"	
else
	echo "test number exceed 10!"
fi

