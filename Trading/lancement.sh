#!/bin/bash
make
gnome-terminal -e "bash -c 'echo \"Serveur Quote\";./Serveur 20001; bash'"
gnome-terminal -e "bash -c 'echo \"Serveur Order\";./Serveur 20002; bash'"
sleep 1;
gnome-terminal -e "bash -c 'echo \"Client\";./Client localhost; bash'"
