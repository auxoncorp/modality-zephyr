# Modality Zephyr RTOS tracing integration

[Zephyr](https://www.zephyrproject.org/) module to integrate with [Modality](https://docs.auxon.io/modality/)'s trace-based testing and analysis tools.

NOTE: Upstream support for external tracing modules has not yet landed; see the [Zephyr PR](https://github.com/zephyrproject-rtos/zephyr/pull/39552). In the meantime, use [Auxon's fork of Zephyr](https://github.com/auxoncorp/zephyr/tree/add-external-tracing-support-v2.6.0).

## Getting Started

For detailed steps, see [How to Instrument Your Zephyr System](https://docs.auxon.io/modality/setup/instrument/zephyr.html).

1. [Install Modality](https://docs.auxon.io/modality/setup/installation.html). The examples below assume that you extracted the [Modality tarball package](https://docs.auxon.io/modality/setup/installation.html#tarball) to `/usr/local/modality`.

2. Add the module in this repo to the `ZEPHYR_EXTRA_MODULES` CMake list.

    ```cmake
    list(APPEND ZEPHYR_EXTRA_MODULES /path/to/modality-zephyr)
    ```

3. Tell CMake where to find Modality and what [target triple](https://docs.auxon.io/modality/reference/zephyr-reference.html#modality-zephyr-supported-triples) you're building for. This step is only necessary when using the [Modality tarball package](https://docs.auxon.io/modality/setup/installation.html#tarball). If you're using the [Debian package](https://docs.auxon.io/modality/setup/installation.html#for-linux), Modality will be found automatically and when possible, your target triple will be inferred. 

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

4. Enable and configure tracing either in the Zephyr `menuconfig` or in a `prj.conf` file
    - Select "External tracing support" in Zephyr → Sub Systems and OS Services → Tracing Support → Tracing Format
    - Select "Modality probe tracing support" in Zephyr → Modules → ExternalTracing → Modality Probe Tracing
    - Further configuration of the Modality integration can be done under [Modality Probe Tracing](https://docs.auxon.io/modality/reference/zephyr-reference.html#zephyr-kconfig-options) once it's enabled.

5. Modality groups your system into one or more [components](https://docs.auxon.io/modality/reference/glossary.html#component). Run the [update-manifest.py](https://github.com/auxoncorp/modality-zephyr/blob/main/tools/update-manifest.py) script for each component. You'll need to re-run this script whenever you add a new thread to your Zephyr system. This script accepts the following options:
    - `--component` - Required. Path to the directory containing source files for this component.
    - `--component-name` - Optional. Name of component to be created. Defaults to `modality-component`.
    - `--thread-names` - Required. List of thread names to add as probes. You must provide the names of all threads in this component.

    ```bash
    ./tools/update-manifest.py \
        --component modality-component \
        --thread-names "consumer_thread" "producer_thread"
    ```

6. Create a [`Modality.toml`](https://docs.auxon.io/modality/reference/config/modality-configuration-file.html) configuration file.
    - The default `collector_connections` address in Zephyr is `udp://192.0.2.2:2718`; you can change this via `menuconfig`: Zephyr → Modules → ExternalTracing → Modality Probe Tracing → IO Transport Configuration; modify "Collector IP address" and "Collector UDP port number."
    - The `control_connections` IP address is [Zephyr's IPv4 address](https://docs.zephyrproject.org/latest/reference/kconfig/CONFIG_NET_CONFIG_MY_IPV4_ADDR.html), which defaults to `192.0.2.1`.
    - You can change Zephyr's IPv4 address via `menuconfig`: Zephyr → Sub Systems and OS Services → Networking → Link layer and IP networking support → Network Libraries → Set network settings for applications; modify "My IPv4 address"
    - The default `control_connections` UDP port in Zephyr is `34355`; you can change this via `menuconfig`: Zephyr → Modules → ExternalTracing → Modality Probe Tracing → IO Transport Configuration; modify "Control plane UDP port number."

    ```toml
    # Modality.toml
    modalityd = "http://localhost:14181/v1/"
    collector_connections = [
      "udp://192.0.2.2:2718"
    ]
    control_connections = [
      "udp://192.0.2.1:34355"
    ]
    ```

7. Create a [`SUT.toml`](https://docs.auxon.io/modality/reference/config/sut-definition-files.html) definition file, then call `modality sut create <directory containing SUT.toml>` to create it.
    ```toml
    # SUT.toml
    name = "example"
    tags = ["Zephyr"]
    component_paths = [
        "./modality-component",
    ]
    ```

    ```text
    $ modality sut create .
    $ modality sut list
    NAME      COMPONENTS    SESSIONS
    example   1             0
    ```


## Example

1. Get [Zephyr networking tools](https://github.com/zephyrproject-rtos/net-tools) and run the setup script in a separate terminal to proxy networking from qemu.

    ```bash
    ./net-setup.sh
    ```

2. Fetch the Zephyr workspace resources.

    ```bash
    cd example-workspace/
    west init -l modality-example
    west update
    source zephyr/zephyr-env.sh
    ```

3. Build the modality-zephyr example.

    ```bash
    cd modality-example/
    west build -b qemu_cortex_m3
    ```

4. Create the example SUT and open a [session](https://docs.auxon.io/modality/reference/glossary.html#session)

    ```bash
    ./sut-up.sh
    ```

5. Run the example

    ```bash
    west build -t run
    ```

    ```text
    trace: Initializing tracing
    *** Booting Zephyr OS build zephyr-v2.6.0-1-ge6858b1f2010  ***
    trace: Registering probe ID 63422 for thread 'consumer_thread'
    trace: Registering probe ID 45765 for thread 'producer_thread'
    Modality Zephyr Example
    Producer started
    trace: Allocated control plane message queue for thread 'producer_thread'
    Producing 0
    Consumer started
    Consuming 0
    trace: Tracing IO thread started
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
    Producing 6
    Consuming 6
    trace: Sent control message to thread 'producer_thread'
    trace: Thread producer_thread processed a control message
    Producing 7
    Consuming 7
    ```

6. View the trace log

    ```text
    $ modality log
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
    ╚═»╗  ║  modalityd interacted with PRODUCER_THREAD
    ║  ║  ║
    ║  *  ║  (45765:4:1:5, PRODUCING @ PRODUCER_THREAD, payload=1)
    ║  ║  ║
    ║  *  ║  (45765:4:1:6, THREAD_SLEEP @ PRODUCER_THREAD, payload=50)
    ║  ║  ║
    ║  *  ║  (45765:4:1:7, THREAD_SWITCHED_OUT @ PRODUCER_THREAD)
    .  .  .
    .  .  .
    .  .  .
    ```

## Updating Modality Component Manifests

Run the [tools/update-manifest.py](tools/update-manifest.py) script to
add the Zephyr tracing event and thread probe definitions to an existing Modality component. Probe IDs are generated from a hash of their associated thread name.

You may run [update-manifest.py](tools/update-manifest.py) to create a new Modality component.

**NOTE:** After adding or removing a thread from your Zephyr system, you must run [update-manifest.py](tools/update-manifest.py) for the relevant component.


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
