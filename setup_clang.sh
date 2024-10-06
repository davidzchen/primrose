#!/bin/bash -e

BAZELRC_FILE="${BAZELRC_FILE:-./clang.bazelrc}"

LLVM_PREFIX=$1

if [[ ! -e "${LLVM_PREFIX}/bin/llvm-config" ]]; then
  echo "Error: cannot find local llvm-config in ${LLVM_PREFIX}."
  exit 1
fi

PATH="$("${LLVM_PREFIX}"/bin/llvm-config --bindir):${PATH}"
export PATH

LLVM_VERSION="$(llvm-config --version)"
LLVM_LIBDIR="$(llvm-config --libdir)"
LLVM_TARGET="$(llvm-config --host-target)"

RT_LIBRARY_PATH="${LLVM_LIBDIR}/clang/${LLVM_VERSION}/lib/${LLVM_TARGET}"

echo "# Generated file, do not edit. If you want to disable clang, just delete this file.
# setup PATH
build:clang --action_env='PATH=${PATH}' --host_action_env='PATH=${PATH}'

# Use c++20 standard
build:clang --cxxopt='-std=c++20'

# Setup CC and CXX
build:clang --action_env=CC=clang --host_action_env=CC=clang
build:clang --action_env=CXX=clang++ --host_action_env=CXX=clang++

# Use libc++
build:clang --cxxopt='-stdlib=libc++'

# Optimization: operator new guarantees 8 byte alignment
# instead of 16
build:clang --cxxopt='-fnew-alignment=8'

# Disable rtti and exceptions(sorry)
build:clang --cxxopt='-fno-rtti'
build:clang --cxxopt='-fno-exceptions'

# Optimization: use sized deallocation for standard library containers
build:clang --cxxopt='-fsized-deallocation'

# Use llvm linker
build:clang --linkopt='-fuse-ld=lld'

# Link with libc++ instead of libstdc++
build:clang --linkopt='-stdlib=libc++'

# Use compiler-rt instead of gcc_s?
build:clang --linkopt='--rtlib=compiler-rt'

# To give -v to linker to see the exact flags used, uncomment these to debug linker issues
# build:clang --linkopt='-v'
" > "${BAZELRC_FILE}"
