#!/bin/bash

function run_java_one() {
    mkdir classes
    javac $1.java -d classes
    echo "        $1.java"
    /usr/bin/time -f "          times:    %U/%S/%M" java -Xmx256M -cp classes $1 && \
        echo "          finished: OK" || echo "          finished: FAILED"
    echo -n "          check:    "
    ./check answer.txt output.txt
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
    C_FILES=
    for C_FILE in "${@}"; do
        C_FILES="$C_FILES $C_FILE.c"
    done
    gcc -O2 $C_FILES -lm -o $1.exe
    echo "        $1.c"
    /usr/bin/time -f "          times:    %U/%S/%M" ./$1.exe && \
        echo "          finished: OK" || echo "          finished: FAILED"
    echo -n "          check:    "
    ./check answer.txt output.txt
    rm $1.exe
}

function run_c() {
    echo "    C:"
    rm -rf edx-io.*
    cp -r ../../src/c/* .
    for t in Test*.c; do
        run_c_one "${t:0:${#t}-2}" "edx-io"
    done
    rm -rf edx-io.*
    run_c_one "Reference"
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

for TEST in 0{1,2,3,4,5,6}*; do
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
    rm -f check
    popd > /dev/null
done

rm -f */{input,output,answer}.txt
rm -f *.class
