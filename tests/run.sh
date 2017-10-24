#!/bin/bash

if [[ "$1" == "clean" ]]; then
    rm -f */{input,output,answer}.txt
    rm -f *.class
    exit 0
fi

TIMEFORMAT="          time:     %U"

function print_io_sizes() {
    echo -n "          input:    "
    ls -la input.txt | awk '{ print $5 " bytes"}'
    echo -n "          output:   "
    ls -la output.txt | awk '{ print $5 " bytes"}'
}

function run_java_one() {
    mkdir classes
    javac $1.java -d classes
    echo "        $1.java"
    time java -Xmx256M -cp classes $1 && echo "          finished: OK" || echo "          finished: FAILED"
    echo -n "          check:    "
    ./check answer.txt output.txt
    print_io_sizes
    rm -rf output.txt classes
}

function run_java() {
    echo "    Java:"
    rm -rf mooc classes
    cp -r ../../src/jvm/mooc .
    for t in Test*.java; do
        run_java_one "${t:0:${#t}-5}"
    done
    rm -rf mooc
    run_java_one "Reference"
}

function run_c_one() {
    gcc -O3 "$@" -lm -o compiled_c.exe
    echo "        $1"
    time ./compiled_c.exe && echo "          finished: OK" || echo "          finished: FAILED"
    echo -n "          check:    "
    ./check answer.txt output.txt
    print_io_sizes
    rm compiled_c.exe
}

function run_c() {
    echo "    C:"
    rm -rf edx-io.*
    cp -r ../../src/c/edx-io.* .
    for t in Test*.c; do
        run_c_one "$t" "edx-io.c"
    done
    rm -rf edx-io.*
    run_c_one "Reference.c"
}

function run_cpp_one() {
    g++ -O3 "$@" -o compiled_cpp.exe
    echo "        $1"
    time ./compiled_cpp.exe && echo "          finished: OK" || echo "          finished: FAILED"
    echo -n "          check:    "
    ./check answer.txt output.txt
    print_io_sizes
    rm compiled_cpp.exe
}

function run_cpp() {
    echo "    C++:"
    rm -rf edx-io.*
    cp -r ../../src/c/edx-io.* .
    cp -r ../../src/c++/edx-io.* .
    for t in Test*.cpp; do
        run_cpp_one "$t" "edx-io.cpp" "edx-io.c"
    done
    rm -rf edx-io.*
    run_cpp_one "Reference.cpp"
}

function run_cpython_one() {
    echo "        $1"
    time python3 "$@" && echo "          finished: OK" || echo "          finished: FAILED"
    echo -n "          check:    "
    ./check answer.txt output.txt
    print_io_sizes
    rm -rf __pycache__
}

function run_cpython() {
    echo "    CPython:"
    rm -rf edx_io.*
    cp -r ../../src/python/* .
    for t in Test*.py; do
        run_cpython_one "$t" "edx_io.py"
    done
    rm -rf edx_io.*
    run_cpython_one "Reference.py"
}

function cat_simple_checker() {
cat <<SimpleChecker
#!/bin/bash
if cmp -s "\$1" "\$2"; then
    echo "OK"
else
    echo "FAILED"
fi
SimpleChecker
}

javac Generator.java
java Generator

if [[ "$1" == "" ]]; then
    MASK=0*
else
    MASK="$1"
fi

for TEST in $MASK; do
    pushd $TEST > /dev/null
    echo "Running test $TEST"
    if [[ -f check.c ]]; then
        gcc -O2 check.c -o check
    else
        cat_simple_checker > check
        chmod +x check
    fi
    run_java
    run_c
    run_cpp
    run_cpython
    rm -f check
    popd > /dev/null
done

rm -f */{output}.txt
rm -f *.class
