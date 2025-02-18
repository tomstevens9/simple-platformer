#!/bin/bash
fd --extension c --extension h --type f . 'src/' \
            --exec-batch clang-tidy -p build
