package dev.profsucrose.lox;

// throw exception for returns to unwind JVM callstack
public class Return extends RuntimeException {
    final Object value;

    Return(Object value) {
        super(null, null, false, false);
        this.value = value;
    }
}
