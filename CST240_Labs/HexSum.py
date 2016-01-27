#!/usr/bin/python
#@AUTHOR: Garrett Fleischer
#@ASSIGN: Lab 3
#@DATE: 01/21/16

import sys

def sum_hex(string, num):
    value = 0
    for c in range(num):
        value += int(string[c], 16)

    return value


def sum_file(file_string, num):
    most_sum = 0
    most_str = ""

    for i in range(len(file_string) - num + 1):
        cur_str = file_string[i:i+num]
        cur_sum = sum_hex(cur_str, num)
        
        if cur_sum > most_sum:
            most_str = cur_str
            most_sum = cur_sum

    return most_sum,most_str


#START HERE
if len(sys.argv) != 3:
    print "Wrong number of arguments!"
else:
    mfile = 0
    num = 0

    #Attempt to open file
    try:
        myFile = open(sys.argv[1], "r")
    except IOError:
        print "Specified file does not exist"
        exit()

    #Attempt to convert 2nd arg to int
    try:
        num = int(sys.argv[2])
    except ValueError:
        print "Second argument must be a number"
        exit()

    #Check if 2nd arg is less than 1
    if num < 1:
        print "Second argument must be greater than 0"
        exit()

    #Continue happily
    fileString = ''.join(myFile.read().split())
    myFile.close()
          
    maxNum,maxStr = sum_file(fileString, num)
    print maxNum,maxStr
