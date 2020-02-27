#!/bin/bash

if grub-file --is-x86-multiboot $1; then
	echo "[\033[0;32m🗸\033[0m] \"${1}\" is multiboot compliant"
else
	echo "[\033[0;31m✗\033[0m] \"${1}\" is NOT multiboot compliant"
fi
