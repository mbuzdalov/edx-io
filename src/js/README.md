# I/O for JavaScript

This library provides a set of methods for efficient reading and writing necessary types of data:

## Opening and closing

* `new EdxIo()` -- opens the files `input.txt` for reading and `output.txt` for writing, prepares the rest of the library to work.
* `.close(): Promise<void>` -- flushes the streams and closes the files. Should be always called at the end and returned from main function.

## High-level input

* `.nextInt(): number` -- reads an `int`.
* `.nextFloat(): number` -- reads a `float`.
* `.nextToken(): string` -- reads a non-whitespace token and returns it.
* `.nextChar(): number` -- reads a non-whitespace char and returns it's code.

## High-level output

* `.write(content: any) void` -- calls `.toString()` method on given content and writes result to output.
* `.writeLn(content: any): void` -- calls `.toString()` method on given content and writes result with newline to output.

## Working with arrays

It's recommended to avoid working with number arrays of fixed length using the usual JavaScript `Array`. It's better to use `TypedArray` instead. For example if you're working with integer numbers, write `const numbers = new Int32Array(arrayLength)` instead of `const numbers = []`. It can speed up your code in several times.

## Example solution of the A+B problem

```
const EdxIo = require("./EdxIo");

const main = () => {
    const io = new EdxIo();
    io.writeLn(io.nextInt() + io.nextInt());
    return io.close();
}

main().catch(console.error)
```