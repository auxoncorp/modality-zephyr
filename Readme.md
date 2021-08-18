# A modality demonstrator for Zephyr RTOS

## How to run
1. Put this code in a zephyr workspace directory. i.e. you should see
   'bootloader, 'modules', 'zephyr', etc. next to this.

2. Install the tarball build of modality into `/usr/local/modality`

3. Get https://github.com/zephyrproject-rtos/net-tools and run the
   setup script, to proxy networking from qemu:
```
./net-setup.sh
```

4. Build it
```
west build -b qemu_cortex_m3 --pristine
```

5. Set up modality
```
modality sut create .
modality sut use modapp
modality sut list
modality sut component list
```

4. Build it and run it
```
modality session open ztest modapp
modality session use ztest
modality status
west build -t run
```

