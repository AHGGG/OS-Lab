#!/bin/bash
echo 当前进程运行的ID：$$, 传递到脚本的参数个数：$#
if [ $# -eq 1 ]
then
    if [ -f "$1" ]
    then
        echo 要检测的文件名:$1
    else
        echo 要检测的文件不存在
        exit 0
    fi
else
    echo 请传入检测的文件名
    exit 0
fi

loop=0
size=`ls -l | grep $1 | awk  '{print $5}'`
echo 初始文件大小:$size

changetime=0

while(( $loop<=3 ))
do
    #=前后不能有空格
    sizeNow=`ls -l | grep $1 | awk  '{print $5}'`
    iseq=`expr $sizeNow == $size`
    if [ $iseq == 1 ]
    then
        echo 第 $loop 次检测，文件\"$1\"的大小：$sizeNow, 未发生变化
    else
        let "changetime++"
        echo 第 $loop 次检测，文件\"$1\"的大小：$sizeNow, 第$changetime次被改变, from $size to $sizeNow

        if [ $changetime == 2 ]
        then
            echo 检测到第2次改变, 1s后清屏退出
            sleep 2s
            clear
            exit 0
        fi
    fi
    
    sleep 5s
    let "loop++"
done



