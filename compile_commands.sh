#!/bin/bash

set -e

bazel run --config=clang //:refresh_compile_commands && \
    python3 bazel/cc_modify.py compile_commands.json
