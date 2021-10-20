#!/usr/bin/env python3
#
# pip3 install crccheck pyclibrary

import os
import csv
import toml
import json
import pathlib
import sys
import argparse
import subprocess
from pyclibrary import CParser
from crccheck.crc import Crc16Ibm3740

# Most of the events have u32 payloads, this is a list of events that don't
EVENTS_WITHOUT_PAYLOADS = [
    'TRACE_EVENT_TASK_SWITCHED_OUT',
    'TRACE_EVENT_MUTEX_GIVE',
    'TRACE_EVENT_MUTEX_GIVE_BLOCKED',
    'TRACE_EVENT_MUTEX_GIVE_FAILED',
    'TRACE_EVENT_MUTEX_TAKE',
    'TRACE_EVENT_MUTEX_TAKE_BLOCKED',
    'TRACE_EVENT_MUTEX_TAKE_FAILED',
]

# Most of the events with payloads are u32, this is a list of of events that have signed payloads
EVENTS_WITH_SIGNED_PAYLOADS = [
    'TRACE_EVENT_TASK_SWITCHED_IN',
    'TRACE_EVENT_TASK_MSLEEP',
    'TRACE_EVENT_TASK_USLEEP',
]

def remove_prefix(text, prefix):
    return text[text.startswith(prefix) and len(prefix):]

def parse_zephyr_trace_event_definitions(header_file_path):
    events = []
    parser = CParser([header_file_path])
    ids = set()
    for item in parser.defs['values'].items():
        name = item[0]
        event_id = item[1]
        if name != 'TRACE_EVENT_ID_TOP' and name.startswith('TRACE_EVENT_'):
            if event_id in ids:
                sys.exit('Found duplicate event ID {} for event {}'.format(event_id, name))
            ids.add(event_id)
            canonical_name = remove_prefix(name, 'TRACE_EVENT_').upper()
            event_class = canonical_name.split('_')[0].lower()
            desc = 'Zephyr {}'.format(canonical_name.replace('_', ' ').lower())
            is_failure = 'FAILED' in canonical_name
            type_hint = ''
            if name in EVENTS_WITH_SIGNED_PAYLOADS:
                type_hint = 'I32'
            elif name not in EVENTS_WITHOUT_PAYLOADS:
                type_hint = 'U32'
            event = {
                'name': canonical_name,
                'class': event_class,
                'desc': desc,
                'type_hint': type_hint,
                'is_failure': is_failure,
                'id': str(event_id),
            }
            events.append(event)
    return events

def hash_task_name_to_probe_id(task_name):
    return Crc16Ibm3740.calc(str.encode(task_name))

parser = argparse.ArgumentParser(description='Updates Modality component manifest files to include Zephyr events and probes.')
parser.add_argument('-c', '--component', type=str, required=True, help='Path to component directory')
parser.add_argument('-n', '--component-name', type=str, required=False, default='modality-component',
        help='Modality component name')
parser.add_argument('-t', '--task-names', nargs='+', default=[], help='List of task names to add as probes')
args = parser.parse_args()

root_dir = pathlib.Path(__file__).parent.resolve().parent
trace_event_header_file = root_dir.joinpath('source/include/modality_probe_events.h')
trace_events = parse_zephyr_trace_event_definitions(trace_event_header_file)

cli_args = [
    'modality-probe',
    'manifest-gen',
    '--component-name',
    '{}'.format(args.component_name),
    '--output-path',
    '{}'.format(args.component),
]

for trace_event in trace_events:
    tags = 'Zephyr;' + trace_event['class']
    if trace_event['is_failure']:
        tags = 'FAILURE;{}'.format(tags)

    if 'ISR' in trace_event['name']:
        tags += ';ISR'

    ext_event = {
        'id': int(trace_event['id']),
        'name': trace_event['name'],
        'description': trace_event['desc'],
        'tags': tags,
        'type_hint': trace_event['type_hint'],
    }

    cli_args.append('--external-event')
    cli_args.append('{}'.format(json.dumps(ext_event)))

for task_name in args.task_names:
    probe_id = int(hash_task_name_to_probe_id(task_name))
    canonical_name = task_name.replace(' ', '_').replace('-', '_').upper()
    ext_probe = {
        'id': probe_id,
        'name': canonical_name,
        'description': "Zephyr task '{}'".format(task_name),
        'tags': 'Zephyr;task',
    }
    cli_args.append('--external-probe')
    cli_args.append('{}'.format(json.dumps(ext_probe)))

subprocess.run(cli_args)
