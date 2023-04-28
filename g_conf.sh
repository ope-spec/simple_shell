#!/bin/bash

max_pid=$((2 ** (8 * $(getconf LONG_BIT) - 1) - 1))
echo "Maximum process ID value: $max_pid"
