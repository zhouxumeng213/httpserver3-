#!/bin/bash
ROOT_PATH=$(pwd)
LIB_PATH=${ROOT_PATH}/mysql_libs/lib
service iptables stop
service mysqld start
export LD_LIBRARY_PATH=${LIB_PATH}
env | grep LD_LIBRARY_PATH
./httpd 8080
