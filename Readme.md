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

4. Choose the board config and build
```
rm -rf build && west build -b qemu_cortex_m3 --pristine
```

5. Set up modality
```
./go-modality.sh
```

6. Build it and run it
```
west build -t run
```

7. Use your collected traces
```
modality log | less
(etc)
```

## Usage notes
### Reporting and Registration
The 'modality_comms' file has a thread that sends reports back to
modalityd. Each probe must be registered with the thread using the
`register_probe` function. For cooperative threads, no more steps are
needed.  Any tracing done in a pre-emptible thread or an ISR must
additionally be surrounded by a critical section using `irq_lock` /
`irq_unlock`.

`register_probe` also uses the thread 'custom data' pointer to store a
pointer back to the thread's registry entry. This allows trace-point
instrumentation to use the probe from the current thread.

### Trace point instrumentation
Zephyr uses a preprocessor-macro based tracing system. Here, we
provide a replacement `tracing.h` which logs modality messages for
some of the probes.

modality_tracing.c 

### Mutations
TODO
