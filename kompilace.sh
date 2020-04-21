#!/bin/bash  
# Skript pro testování stavu systému  
make
cc -g -Wall   -c -o gthr.o gthr.c
as -o gtswtch.o gtswtch.S
cc -g -Wall   -c -o main.o main.c
cc -o gttest gthr.o gtswtch.o main.o 


