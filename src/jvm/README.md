# I/O for Java, Scala and Kotlin

This library provides a single class `EdxIO` located in package `mooc`, which supports the following methods:

## Opening and closing

* `static EdxIO create()` -- creates a new instance of the library, which opens the files `input.txt` for reading and `output.txt` for writing.
* `void close()` -- flushes the streams and closes the files. Should be always called at the end. Use the 
["try-with-resources"](https://docs.oracle.com/javase/tutorial/essential/exceptions/tryResourceClose.html) construction to achieve this in a convenient way.

## Opening and closing -- Scala specific

There is a static inner class called `Receiver` (the full name is `mooc.EdxIO.Receiver`), which is intended for Scala users to reduce the boilerplate. It has the following methods:

* `abstract void receive(EdxIO)` -- the method which you need to extend to perform the real work.
* `void main(String[])` -- the implementation of `public static void main`, which creates an instance of `EdxIO`, passes it to `receive`, and subsequently closes.

If you wish, you may extend `Receiver` by your `object`, which then inherits the `main` method and becomes an eligible entry point.

## High-level input

* `int nextInt()` -- reads an `int`.
* `long nextLong()` -- reads a `long`.
* `double nextDoublePrecise()` -- reads a `double` using `Double.parseDouble` internally, which guarantees that all standard representation of `double` can be read.
* `double nextDoubleFast()` -- reads a `double` in a less compliant way, but maybe three times faster.
* `String next()` -- reads a non-whitespace token and returns it as a `String`.

## Low-level input

* `byte currentSymbol()` -- returns the next symbol to be read, but does not read it. The value of `-1` indicates the end-of-file.
* `void skipWhiteSpace()` -- skips all whitespace symbols until the next non-whitespace symbol.
* `void skipNonWhiteSpace()` -- skips all non-whitespace symbols until the next whitespace symbol.

## High-level output

All methods return `this` for convenience of chaining calls.

* `EdxIO println()` -- prints a newline.
* `EdxIO print(char)` -- prints a character.
* `EdxIO println(char)` -- prints a character and then a newline.
* `EdxIO print(int)` -- prints an int.
* `EdxIO println(int)` -- prints an int and then a newline.
* `EdxIO print(long)` -- prints a long.
* `EdxIO println(long)` -- prints a long and then a newline.
* `EdxIO print(double)` -- prints a double.
* `EdxIO println(double)` -- prints a double and then a newline.
* `EdxIO print(CharSequence)` -- prints a `CharSequence` (of which `String` is an example).
* `EdxIO println(CharSequence)` -- prints a `CharSequence` and then a newline.

## Example solutions of the A+B problem

### Java

```
import mooc.*;

public class Solution {
    public static void main(String[] args) {
        try (EdxIO io = EdxIO.create()) {
            io.println(io.nextInt() + io.nextInt());
        }
    }
}
```

### Scala

```
import mooc._

object Solution extends EdxIO.Receiver {
  def receive(io: EdxIO) {
    io.println(io.nextInt() + io.nextInt())
  }
}
```

### Kotlin

```
import mooc.*

fun main(args:Array<String>) {
  EdxIO.create().use {
    io -> io.println(io.nextInt() + io.nextInt())
  }
}
```
