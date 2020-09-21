#!/bin/bash
cd /home/enselme/git/kernels/staging
make menuconfig && time make -j2 && sudo time make modules_install && sudo time make install && reboot