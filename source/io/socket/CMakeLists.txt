zephyr_sources_ifdef(
  CONFIG_MODALITY_PROBE_IO_TRANSPORT_SOCKET
  modality_probe_io.c
  )

zephyr_include_directories_ifdef(
  CONFIG_MODALITY_PROBE_IO_TRANSPORT_SOCKET
  ./include
  )
