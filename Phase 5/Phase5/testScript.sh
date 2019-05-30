#!/bin/sh

arg1=$1
arg2=$2

#compile program
javac src/BackEnd.java src/AccountTransaction.java src/TicketTransaction.java

#run program
java src/BackEnd.class
