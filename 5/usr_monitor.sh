#!/bin/bash
if [ $# -eq 1 ]
then
    echo You will monitor : $1
else
    echo Usage: usr_moniter username
    exit 0
fi

current_login=`who -u | awk '{print $1}'`
echo current login : $current_login

while(( 1 ))
do
    current_login=`who -u | awk '{print $1}'`
    tryfind=`who -u | awk '{print $1}' | grep -x $1`
    
    if [ $tryfind ]
    then
        echo \"$1\" is logon, 2s后退出
        sleep 2s
        exit 0
    else
        echo waiting user $1 ...
        sleep 5s
    fi
done

# 继续改进：检查用户输入的$1 是不是一个用户的名字，再来检查登录, 不然输入的不是用户名, 不久空等了吗