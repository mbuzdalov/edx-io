#!/bin/bash

function run_java_one() {
    mkdir classes
    javac $1.java -d classes
    echo "        $1.java"
    /usr/bin/time -f "          times:    %U/%S/%M" java -Xmx256M -cp classes $1 && \
        echo "          finished: OK" || echo "          finished: FAILED"
    if cmp -s answer.txt output.txt; then
        echo "          check:    OK"
    else
        echo "          check:    FAILED"
    fi
    rm -rf output.txt classes
}

function run_java() {
    echo "    Java:"
    rm -rf mooc classes
    cp -r ../../src/jvm/mooc .
    run_java_one "Test"
    rm -rf mooc
    run_java_one "Reference"
}

javac Generator.java
java Generator

for TEST in 0*; do
    pushd $TEST > /dev/null
    echo "Running test $TEST"
    run_java
    popd > /dev/null
done

rm -f */{input,output,answer}.txt
rm -f *.class
