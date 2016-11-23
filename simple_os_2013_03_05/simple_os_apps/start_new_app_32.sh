echo $1
mkdir ./$1
cd ./$1
ln -s ../hello_console/Makefile_32
ln -s ../hello_console/rules.mk
mkdir src
mkdir obj

