#!/usr/bin/env bash

modality sut delete modapp --force
modality session delete ztest --force

set -e

modality sut create .
modality session open ztest modapp --force
modality session use ztest


