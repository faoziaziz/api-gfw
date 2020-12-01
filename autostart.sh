#!/bin/bash script untuk restart aplikasi
date 
var=$(ps axu | grep -v grep | grep "api-gfw-client prasimax pmx123") 
if [ ! -z "$var" ];
                then echo "found";
        else
                /opt/gfw/bin/api-gfw-client prasimax pmx123
fi
