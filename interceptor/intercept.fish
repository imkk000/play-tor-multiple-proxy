#!/usr/bin/env fish

# set proxychains configuration
set -lx PROXYCHAINS_CONF_FILE ../proxychains.conf

# intercept my hook function
# then chain to proxychains
set -lx LD_PRELOAD ./intercept.so:/usr/lib/libproxychains4.so

# execute command from args
$argv
