#!/bin/bash
# echo 当前进程运行的ID：$$, 传递到脚本的参数个数：$#
# if [ $# -eq 1 ]
# then
#     if [ -e "$1" ]
#     then
#         echo 要检测的文件名:$1
#     else
#         echo 要检测的文件不存在
#         exit 0
#     fi
# else
#     echo 请传入检测的文件名
#     exit 0
# fi

# loop=0
# size=`ls -l | grep $1 | awk  '{print $5}'`
# # who -a | cut -c1-11 打印1-11
# # -c-2 打印前两个字节
# echo 初始文件大小:$size

# changetime=0

# while(( $loop<=3 ))
# do
#     #=前后不能有空格
#     sizeNow=`ls -l | grep $1 | awk  '{print $5}'`
#     iseq=`expr $sizeNow == $size`
#     if [ $iseq == 1 ]
#     then
#         echo 第 $loop 次检测，文件\"$1\"的大小：$sizeNow, 未发生变化
#     else
#         let "changetime++"
#         echo 第 $loop 次检测，文件\"$1\"的大小：$sizeNow, 第$changetime次被改变, from $size to $sizeNow

#         if [ $changetime == 2 ]
#         then
#             echo 检测到第2次改变, 1s后清屏退出
#             sleep 2s
#             clear
#             exit 0
#         fi
#     fi
    
#     sleep 5s
#     let "loop++"
# done

# #!/bin/bash
# # clear
# count=$#
# user=$1
# # check_user()
# # {
# #   name=`who | grep $1`
# #   if [ -n $name ]
# #   then
# #       return 1
# #   else 
# #       return 0
# #   fi
# # }
# if [ $count -eq 1 ]
# then
#     # show=`who | awk '{print $1}'`
#     # check_user $user
#     # if [ $? -eq 0 ]
#     test=`who | awk '{print $1}' |grep -x $1`
#     if [ $test ]
#     then 
#         echo "user $user is logon"
#         exit 1
#     else
#         #    check_user $user
#         #    a=$?
#         #    while [ $a -eq 1 ]
#         test=`who | awk '{print $1}' |grep -x $1`
#         while true
#         do
#             if [ $test ]
#             then
#                 echo "user $user is logon"
#                 exit 1
#             else
#                 sleep 2s
#                 echo  "waiting user $user"
#                 #    check_user $user
#                 #    a=$?
#                 test=`who | awk '{print $1}' |grep -x $1`
#             fi
#         done
#     fi
# else
# echo "usage:usr_monitor username"
# fi




#!/bin/bash
check()
{
    usr=`who | awk '{print $1}' | grep -x $1`
    if [ $usr ]
    then
        echo logon
        return 0
    else
        echo not logon
        return 1
    fi
}
clear
# echo "These users is log on: $name "
user=$1
# if [ $? -eq 0 ]
# then
#     echo "user $user is log on"
#     exit
# else
#     echo "user $user is not log on"
# fi
check $1 
if [ $? -eq 0 ]
then
    echo "$user is log on"
    exit
else
    echo "$user is not log on"
fi

while true
do
    sleep 5
    echo "Checking if user $user is log on..."
    # check
    
    check $1 
    if [ $? -eq 0 ]
    then
        echo "$user is log on"
        exit
    else
        echo "$user is not log on"
    fi
done

