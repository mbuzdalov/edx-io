package mooc;

import java.io.*;
import java.nio.*;
import java.nio.channels.*;
import java.nio.file.*;
import java.util.*;

/**
 * This is a simple I/O library for JVM-based programming languages, such as Java, Scala and Kotlin,
 * intended to be used in edX-based courses on programming taught by ITMO University.
 *
 * @author Maxim Buzdalov
 */
public class EdxIO implements Closeable {
    /**
     * Creates a default instance of EdxIO
     * which reads input from "input.txt"
     * and writes output to "output.txt".
     *
     * @return the new EdxIO instance.
     */
    public static EdxIO create() {
        return new EdxIO("input.txt", "output.txt");
    }

    /**
     * This is an abstract class for an entry point intended to be used from Scala.
     *
     * It has an abstract method {#receive(EdxIO)} for doing the real work when the EdxIO instance is created,
     * and an implementation of public-static-void-main which creates an instance and delegates to {#receive(EdxIO)}.
     */
    public static abstract class Receiver {
        /**
         * This is an abstract method for doing the real work.
         *
         * @param io an instance of EdxIO for reading and writing.
         */
        protected abstract void receive(EdxIO io);

        /**
         * This is what will become the public-static-void-main
         * when this class is extended by a Scala object containing the solution.
         */
        public final void main(String[] args) {
            try (EdxIO io = EdxIO.create()) {
                receive(io);
            }
        }
    }

    /*-************************* Public high-level API for input *************************-*/

    /**
     * Reads from the input file and returns the next int.
     *
     * This will:
     * <ul>
     * <li>skip all whitespace until the next non-whitespace symbol;</li>
     * <li>remember the position of the first non-whitespace symbol;</li>
     * <li>try consuming as much non-whitespace symbols as needed to read an int;</li>
     * <li>if done successfully, returns an int, otherwise rewinds the stream
     *     to the remembered position and throws an exception.</li>
     * </ul>
     *
     * When the operation succeeds, the stream pointer for the input file points to the next
     * symbol after the last symbol of the consumed int value.
     *
     * When the operation fails, the stream pointer for the input file points to the first
     * non-whitespace symbol which started a sequence that could not be interpreted as an int.
     *
     * @return the int value which has just been read from the input file.
     */
    public int nextInt() {
        return nextIntImpl(false, 0);
    }

    /**
     * Reads from the input file and returns the next int.
     * On failure, returns the specified {@code valueOnFail}.
     *
     * This will:
     * <ul>
     * <li>skip all whitespace until the next non-whitespace symbol;</li>
     * <li>remember the position of the first non-whitespace symbol;</li>
     * <li>try consuming as much non-whitespace symbols as needed to read an int;</li>
     * <li>if done successfully, returns an int, otherwise rewinds the stream
     *     to the remembered position and returns the specified {@code valueOnFail}.</li>
     * </ul>
     *
     * When the operation succeeds, the stream pointer for the input file points to the next
     * symbol after the last symbol of the consumed int value.
     *
     * When the operation fails, the stream pointer for the input file points to the first
     * non-whitespace symbol which started a sequence that could not be interpreted as an int.
     *
     * @param valueOnFail the value to return on failure.
     * @return the int value which has just been read from the input file, or {@code valueOnFail} on fail.
     */
    public int nextIntOr(int valueOnFail) {
        return nextIntImpl(true, valueOnFail);
    }

    /*-************************* Public low-level API for input *************************-*/

    /**
     * Returns the symbol which is pointed by the stream pointer for the input file.
     * If the file has been entirely read, returns the value 0xFF, which is the same as -1.
     *
     * @return the current symbol, or -1 of EOF is reached.
     */
    public byte currentSymbol() {
        return inputPosition < inputCapacity ? inputBuffer.get(inputPosition) : (byte)-1;
    }

    /**
     * Skips all whitespace symbols in the input file,
     * such that the subsequent call to {#currentSymbol} returns a non-whitespace symbol.
     */
    public void skipWhiteSpace() {
        while (inputPosition < inputCapacity && inputBuffer.get(inputPosition) <= 32) {
            ++inputPosition;
        }
    }

    /*-************************* Public high-level API for output *************************-*/

    /**
     * Prints a character to the output file.
     * A '\n' char is converted to the native newline byte sequence.
     *
     * @param the character to be printed.
     */
    public void print(char ch) {
        if (ch == '\n') {
            printNewLine();
        } else {
            write((byte) (ch));
        }
    }

    /**
     * Prints a character to the output file, and then puts a newline.
     *
     * @param the character to be printed.
     */
    public void println(char ch) {
        write((byte) (ch));
        printNewLine();
    }

    /**
     * Prints a String to the output file.
     * Every '\n' char is converted to the native newline byte sequence.
     *
     * @param the string to be printed.
     */
    public void print(String s) {
        for (int i = 0, iMax = s.length(); i < iMax; ++i) {
            print(s.charAt(i));
        }
    }

    /**
     * Prints a String to the output file, and then puts a newline.
     * Every '\n' char is converted to the native newline byte sequence.
     *
     * @param the string to be printed.
     */
    public void println(String s) {
        for (int i = 0, iMax = s.length(); i < iMax; ++i) {
            print(s.charAt(i));
        }
        printNewLine();
    }

    /**
     * Prints an int to the output file.
     *
     * @param the int to be printed.
     */
    public void print(int value) {
        if (value == Integer.MIN_VALUE) {
            print("-2147483648");
        } else {
            if (value < 0) {
                print('-');
                value = -value;
            }
            int pos = numberBuffer.length;
            while (value >= 65536) {
                int q = value / 100;
                // really: r = i - (q * 100);
                int r = value - ((q << 6) + (q << 5) + (q << 2));
                value = q;
                numberBuffer[--pos] = digitOnes[r];
                numberBuffer[--pos] = digitTens[r];
            }
            while (true) {
                int q = (value * 52429) >>> (16+3);
                int r = value - ((q << 3) + (q << 1));  // r = i-(q*10) ...
                numberBuffer[--pos] = digitOnes[r];
                value = q;
                if (value == 0) break;
            }
            write(numberBuffer, pos, numberBuffer.length - pos);
        }
    }

    /**
     * Prints an int to the output file, and then puts a newline.
     *
     * @param the int to be printed.
     */
    public void println(int value) {
        print(value);
        printNewLine();
    }

    /*-************************* Fields and initialization *************************-*/

    private FileInputStream inputStream;
    private FileChannel inputChannel;
    private MappedByteBuffer inputBuffer;
    private int inputPosition;
    private int inputCapacity;

    private byte[] outputBuffer;
    private int outputSize;
    private FileOutputStream outputStream;

    private final byte[] numberBuffer = new byte[32];
    private final byte[] lineSeparatorChars = System.lineSeparator().getBytes();

    private EdxIO(String inputFileName, String outputFileName) {
        try {
            File inputFile = new File(inputFileName);
            inputStream = new FileInputStream(inputFile);
            inputChannel = inputStream.getChannel();
            inputBuffer = inputChannel.map(FileChannel.MapMode.READ_ONLY, 0, inputFile.length());
            inputPosition = 0;
            inputCapacity = inputBuffer.capacity();

            outputStream = new FileOutputStream(outputFileName);
            outputBuffer = new byte[8192];
            outputSize = 0;
        } catch (IOException ex) {
            closeImpl();
            throw new UncheckedIOException(ex);
        }
    }

    /*-************************* Implementation of nextInt *************************-*/

    private int nextIntImpl(boolean hasValueOnFail, int valueOnFail) {
        skipWhiteSpace();
        int firstNonWhitespacePosition = inputPosition;
        boolean isNegative = false;
        if (currentSymbol() == '-') {
            isNegative = true;
            ++inputPosition;
        }
        boolean hasSymbols = false;
        int value = 0;
        while (true) {
            byte next = currentSymbol();
            if (next >= '0' && next <= '9') {
                hasSymbols = true;
                ++inputPosition;
                int add = next - '0';
                if (nextIntImplIsSafe(value, add, isNegative)) {
                    value = value * 10 + add;
                } else {
                    inputPosition = firstNonWhitespacePosition;
                    return nextIntImplThrow(hasValueOnFail, valueOnFail);
                }
            } else {
                // not a number anymore
                if (hasSymbols) {
                    return isNegative ? -value : value;
                } else {
                    inputPosition = firstNonWhitespacePosition;
                    return nextIntImplThrow(hasValueOnFail, valueOnFail);
                }
            }
        }
    }

    private boolean nextIntImplIsSafe(int value, int add, boolean isNegative) {
        if (value < 214748364) {
            return true;
        }
        if (value > 214748364) {
            return false;
        }
        return isNegative ? add <= 8 : add < 8;
    }

    private int nextIntImplThrow(boolean hasValueOnFail, int valueOnFail) {
        if (hasValueOnFail) {
            return valueOnFail;
        } else {
            throw new NumberFormatException();
        }
    }

    /*-************************* Implementation of print *************************-*/

    private void write(byte b) {
        outputBuffer[outputSize++] = b;
        if (outputSize == outputBuffer.length) {
            flush();
        }
    }

    private void printNewLine() {
        write(lineSeparatorChars, 0, lineSeparatorChars.length);
    }

    private void flush() {
        try {
            outputStream.write(outputBuffer, 0, outputSize);
            outputSize = 0;
        } catch (IOException ex) {
            throw new UncheckedIOException(ex);
        }
    }

    private void write(byte[] buffer, int offset, int length) {
        if (outputSize + length <= outputBuffer.length) {
            System.arraycopy(buffer, offset, outputBuffer, outputSize, length);
            outputSize += length;
        } else {
            flush();
            try {
                outputStream.write(buffer, offset, length);
            } catch (IOException ex) {
                throw new UncheckedIOException(ex);
            }
        }
    }

    private final static byte[] digitTens = {
        48, 48, 48, 48, 48, 48, 48, 48, 48, 48,
        49, 49, 49, 49, 49, 49, 49, 49, 49, 49,
        50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
        51, 51, 51, 51, 51, 51, 51, 51, 51, 51,
        52, 52, 52, 52, 52, 52, 52, 52, 52, 52,
        53, 53, 53, 53, 53, 53, 53, 53, 53, 53,
        54, 54, 54, 54, 54, 54, 54, 54, 54, 54,
        55, 55, 55, 55, 55, 55, 55, 55, 55, 55,
        56, 56, 56, 56, 56, 56, 56, 56, 56, 56,
        57, 57, 57, 57, 57, 57, 57, 57, 57, 57,
    };

    private final static byte[] digitOnes = {
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
        48, 49, 50, 51, 52, 53, 54, 55, 56, 57,
    } ;


    /*-************************* Closing *************************-*/

    @Override
    public void close() {
        IOException ex = closeImpl();
        if (ex != null) {
            throw new UncheckedIOException(ex);
        }
    }

    private IOException closeImpl() {
        IOException first = null;

        inputBuffer = null;
        if (inputChannel != null) {
            try {
                inputChannel.close();
            } catch (IOException ex) {
                if (first == null) {
                    first = ex;
                }
            }
            inputChannel = null;
        }
        if (inputStream != null) {
            try {
                inputStream.close();
            } catch (IOException ex) {
                if (first != null) {
                    first = ex;
                }
            }
        }

        if (outputSize > 0 && outputBuffer != null && outputStream != null) {
            try {
                outputStream.write(outputBuffer, 0, outputSize);
            } catch (IOException ex) {
                if (first != null) {
                    first = ex;
                }
            }
        }

        outputBuffer = null;
        outputSize = 0;
        if (outputStream != null) {
            try {
                outputStream.close();
            } catch (IOException ex) {
                if (first != null) {
                    first = ex;
                }
            }
        }

        return first;
    }
}
