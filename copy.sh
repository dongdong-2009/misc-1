#!/bin/sh

mkdir -p common
cp -rf ../vdsdk/vd_demo_all/libini ./
cp -f ../vdsdk/vd_demo_all/common/convert.h 	./common/
cp -f ../vdsdk/vd_demo_all/common/convert.c 	./common/
cp -f ../vdsdk/vd_demo_all/common/HxConfig.cpp 	./common/
cp -f ../vdsdk/vd_demo_all/common/HxConfig.h 	./common/
cp -f ../vdsdk/vd_demo_all/common/Sql.h 	./common/
cp -f ../vdsdk/vd_demo_all/common/Sql.cpp 	./common/
cp -f ../vdsdk/vd_demo_all/common/utils.cpp 	./common/
cp -f ../vdsdk/vd_demo_all/common/utils.h 	./common/
cp -f ../vdsdk/vd_demo_all/common/type_def.h 	./common/
cp -f ../vdsdk/vd_demo_all/common/type_def.cpp 	./common/

