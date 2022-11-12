#!/bin/sh

mkdir -p etrobocon2022/logfiles
oldName="logfile.txt"
newName=`date +"%m%d-%H:%M.txt"`

mv -f $oldName etrobocon2022/logfiles/$newName
