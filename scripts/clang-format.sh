#!/bin/bash

if [[ "$1" == "--fix" ]]; then
    # Run clang-format in-place reformatting.
    fd --extension c --extension h --type f . 'src/' \
       --exec-batch clang-format -i
else
    # Run clang-format in dry-run mode to check formatting.
    fd --extension c --extension h --type f . 'src/' \
       --exec-batch clang-format --dry-run -Werror
fi
