#!/bin/sh

EXEC="./million"

$EXEC server lottery-test.cfg &

$EXEC client 2 0 10 11 10

if [ $? != 0 ]; then
    echo "<TEST> ERR: client without server doesnot get right return code"
    exit 1
fi