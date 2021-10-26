# Modality probe Zephyr RTOS tracing backend

NOTE: We're currently waiting on upstream support for external tracing modules to land,
see https://github.com/zephyrproject-rtos/zephyr/pull/39552.

In the meantime, our fork is available [here](https://github.com/auxoncorp/zephyr/tree/add-external-tracing-support-v2.6.0).

## Getting Started

1. Install Modality (the examples assume the tarball was extracted to `/usr/local/modality`)
2. Add the module in this repo to the `ZEPHYR_EXTRA_MODULES` CMake list
  ```cmake
  list(APPEND ZEPHYR_EXTRA_MODULES /path/to/modality-zephyr)
  ```
3. Tell CMake where to find Modality and what target triple your building for (Cortex-M3 in this example).
   This step is only necessary when using the tarball package. If you're using the debian package it
   will be found automatically and your target triple will be inferred (when possible).
  ```cmake
  set(
      MODALITY_PROBE_ROOT
      "/usr/local/modality"
      CACHE
      PATH
      "Modality tarball package installation directory")

  set(
      MODALITY_PROBE_TARGET_TRIPLE
      "thumbv7m-none-eabi"
      CACHE
      STRING
      "Target triple")

  list(APPEND CMAKE_MODULE_PATH "${MODALITY_PROBE_ROOT}/cmake")
  ```
4. Enable and configure tracing either in the `menuconfig` or in a `prj.conf` file
  * Select "External tracing support" in Zephyr → Sub Systems and OS Services → Tracing Support → Tracing Format
  * Select "Modality probe tracing support" in Zephyr → Modules → ExternalTracing → Modality Probe Tracing
  * Further configuration of the tracing implementation can be done once enabled

## Example

1. Get https://github.com/zephyrproject-rtos/net-tools and run the setup script in a separate terminal to proxy networking from qemu
```bash
./net-setup.sh
```
2. Fetch the Zephyr workspace resources
  ```bash
  cd example-workspace/
  west init -l modality-example
  west update
  source zephyr/zephyr-env.sh
  ```
3. Build the example
  ```bash
  cd modality-example/
  west build -b qemu_cortex_m3
  ```
4. Create the example SUT and open a session
  ```bash
  ./sut-up.sh
  ```
5. Run the example
  ```bash
  west build -t run
  ```
  ```text
  Initializing tracing
  *** Booting Zephyr OS build zephyr-v2.6.0-1-ge6858b1f2010  ***
  Registering probe ID 63422 for task 'consumer_thread'
  Registering probe ID 45765 for task 'producer_thread'
  Modality Zephyr Example
  Producer started
  Producing 0
  Consumer started
  Consuming 0
  Main loop
  Producing 1
  Consuming 1
  Main loop
  Producing 2
  Consuming 2
  Producing 3
  Consuming 3
  Main loop
  Producing 4
  Consuming 4
  Producing 5
  Consuming 5
  Main loop
  ```
6. View the trace log
  ```bash
  modality log
  ```
  ```text
  ║  *  ║  (45765:1:0:1, THREAD_CREATE @ PRODUCER_THREAD, payload=-1)
  ║  ║  ║
  ║  ║  *  (63422:1:0:1, THREAD_CREATE @ CONSUMER_THREAD, payload=-1)
  ║  ║  ║
  ║  *  ║  (45765:1:0:2, THREAD_SWITCHED_IN @ PRODUCER_THREAD, payload=-1)
  ║  ║  ║
  ║  *  ║  (45765:1:0:3, PRODUCING @ PRODUCER_THREAD, payload=0)
  ║  ║  ║
  ║  *  ║  (45765:1:0:4, THREAD_SLEEP @ PRODUCER_THREAD, payload=50)
  ║  ║  ║
  ║  *  ║  (45765:1:0:5, THREAD_SWITCHED_OUT @ PRODUCER_THREAD)
  ║  ║  ║
  ║  ╚═»╗  PRODUCER_THREAD interacted with CONSUMER_THREAD
  ║  ║  ║
  ║  ║  *  (63422:2:0:3, THREAD_SWITCHED_IN @ CONSUMER_THREAD, payload=-1)
  ║  ║  ║
  ║  ║  *  (63422:2:0:4, RX_MSG @ CONSUMER_THREAD, outcome=PASS)
  ║  ║  ║
  ║  ║  *  (63422:2:0:5, THREAD_SWITCHED_OUT @ CONSUMER_THREAD)
  ║  ║  ║
  ║  ╔«═╝  CONSUMER_THREAD interacted with PRODUCER_THREAD
  ║  ║  ║
  ║  *  ║  (45765:3:1:3, THREAD_SWITCHED_IN @ PRODUCER_THREAD, payload=-1)
  ║  ║  ║
  ║  *  ║  (45765:3:1:4, PRODUCING @ PRODUCER_THREAD, payload=1)
  ║  ║  ║
  ║  *  ║  (45765:3:1:5, THREAD_SLEEP @ PRODUCER_THREAD, payload=50)
  ║  ║  ║
  ║  *  ║  (45765:3:1:6, THREAD_SWITCHED_OUT @ PRODUCER_THREAD)
  ║  ║  ║
  ║  ╚═»╗  PRODUCER_THREAD interacted with CONSUMER_THREAD
  .  .  .
  .  .  .
  .  .  .
  ```

## Updating Modality Component Manifests

Run the [tools/update-manifest.py](tools/update-manifest.py) script to
add the Zephyr tracing event and thread probe definitions to a Modality component
or once initially to create a new Modality component.
Probe IDs are generated from a hash of their associated thread name.

```bash
./tools/update-manifest.py \
    --component modality-component \
    --thread-names "consumer_thread" "producer_thread"
```

## LICENSE

See [LICENSE](./LICENSE) for more details.

Copyright 2020 [Auxon Corporation](https://auxon.io)

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

[http://www.apache.org/licenses/LICENSE-2.0](http://www.apache.org/licenses/LICENSE-2.0)

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
