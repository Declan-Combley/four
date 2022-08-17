#!/bin/bash

set -xe

cc=clang
flags="-Wall -Wextra"

$cc main.c -o four $flags
