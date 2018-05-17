#!/bin/bash
valgrind --tool=memcheck --leak-check=full --num-callers=15 --suppressions=gtk.suppression "$1"
