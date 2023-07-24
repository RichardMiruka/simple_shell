#!/bin/bash

# /proc/sys/kernel/pid_max
# Write a shell script that prints the maximum value a process ID can be.

# Read the maximum PID value from /proc/sys/kernel/pid_max
pid_max=$(cat /proc/sys/kernel/pid_max)

# Print the maximum PID value
echo "Maximum PID value: $pid_max"
