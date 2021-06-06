# 实验4

### 相关知识点

#### 2021-6-6
- $[]和$(()) 是一组 标识的是 算术运算 `+-*/` !!!!!!!
```BASH
i=1;variable=$((5-$i))
```

---

- 调用函数，拿到返回值$?只能拿到返回的数字，但是如果返回字符串，就不行
```BASH
funWithReturn
echo "return = $?"
```
- 必须将函数放在脚本开始部分，直至shell解释器首次发现它时，才可以使用。调用函数仅使用其函数名即可。

- 在函数体内部，通过 $n 的形式来获取参数的值，例如，$1表示第一个参数，$2表示第二个参数
```BASH
funWithParam(){
    echo "第一个参数为 $1 !"
    echo "第二个参数为 $2 !"
    echo "第十个参数为 $10 !"
    echo "第十个参数为 ${10} !"
    echo "第十一个参数为 ${11} !"
    echo "参数总数有 $# 个!"
    echo "作为一个字符串输出所有参数 $* !"
}

funWithParam 1 2 3 4 5 6 7 8 9 34 73
```
---

- cat -v or od -c:当用的是基于ascii的终端的时候，有些东西不能输出到终端上。所以用这两个命令可以尝试解决。It shows an ASCII ("printable") representat
ion of unprintable and non-ASCII characters

- 单引号里的任何字符都会原样输出，单引号字符串中的变量是无效的；双引号里可以有变量,双引号里可以出现转义字符

- 注释：
```BASH
:<<EOF
注释内容...
注释内容...
注释内容...
EOF
```

- ``号中的内容会被先执行：先sleep 2s, 再echo test
```BASH
 echo `sleep 2s ` test
```

- ( a=321; )括号里的东西被当做子shell来运行

- echo -e：激活转义字符，使用-e选项时，若字符串中出现\n \r等字符，则特别加以处理，而不会将它当成一般文字输出

- 获取字符串/数组的长度:`string="abcd";echo ${#string}` 输出 4

- 提取子字符串:`string="test123test";echo ${string:1:4}` 输出 est1

- 查找字符串:查找字符 i 或 o 的位置，第一个字母是1开始的(哪个字母先出现就计算哪个)：
```bash
string="test io xx";echo `expr index "$string" io`
```

- 获取数组中所有的元素:`echo ${array_name[@]}`

- $*和$@是不一样的，前者是将./xx.sh 1 2 3传的参数1 2 3当做一个参数传进去，而$@是 传 1 2 3:
```BASH
for i in "$*"; do
    echo $i
done

for i in "$@"; do
    echo $i
done
```

- 文件测试运算符：
[![2UW0ij.png](https://z3.ax1x.com/2021/06/06/2UW0ij.png)](https://imgtu.com/i/2UW0ij)

- until [ ! $a -lt 10 ]:当a≥10的时候，做xxx

- wc -l users:看文件users的行数

- command1 < infile > outfile：同时替换输入和输出，执行command1，从文件infile读取内容，然后将输出写入到outfile中。

- command > file 2>&1：2>&1表示修饰，将 stdout 和 stderr 合并后重定向到 file

- Shell 包含外部脚本
```BASH
. filename   # 点号(.)和文件名中间有一空格例如 . ./filename.sh

或

source filename
```

---

- cut命令：
- who -a | cut -c1-11 打印1-11
- -c-2 打印前两个字节
- -c5- 从第5个字符开始到结尾
- 从1开始的！


---
---
---
---

#### 错误记录：
- ./test2.sh: line 2: syntax error near unexpected token `echo'  
- ./test2.sh: line 2: `    echo $file'

解决：
```BASH
for file in `ls ~/Desktop/OS-Lab/4`
do
    echo $file;
done
```
----

- ./test.sh: line 10: read filename: command not found

解决：cat -v ./xx.sh
看是否有非法字符, 比如test.sh里面的read filename看着没问题，但是用上面的命令一看，里面有未知的字符。手打一遍就好。

---

- 如果一个分支里面，没有任何东西，那么就不要写

#### 