#!/bin/bash
../../gitinspector/gitinspector.py -l -r -T --exclude="doc/*" --exclude="data/*" --exclude="include/*" --exclude=".cpp$" --exclude=".hpp$" --exclude=".py$" --exclude=".js$"
