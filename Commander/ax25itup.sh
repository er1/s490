echo You are $1
modprobe ax25
modprobe bpqether
ifconfig bpq0 hw ax25 $1 up
