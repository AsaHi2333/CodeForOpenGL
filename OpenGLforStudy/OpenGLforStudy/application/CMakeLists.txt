#递归(包括本目录下和所有子目录下)将本文件夹下所有cpp放到FUNCS中
file(GLOB_RECURSE APPLICATION "./*.cpp")

#将FUNCS中所有cpp编译为funcs这个lib库
##库文件的存储目录从可执行程序的目录去找
add_library(application ${APPLICATION})



