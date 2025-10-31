@echo off
xmake f --vs=2022 -y 
xmake project -k vsxmake -y -m "debug, release" -a "x64" ./build