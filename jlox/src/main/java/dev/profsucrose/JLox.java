package dev.profsucrose;

public class JLox {
    public static void main(String[] args) {
        final Tuple<Integer, String> tuple = new Tuple<>(1, "Hello World");
        System.out.printf("(%s %s)", tuple.getFirst(), tuple.getSecond());
    }
}
