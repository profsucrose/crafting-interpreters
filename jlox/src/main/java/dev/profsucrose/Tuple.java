package dev.profsucrose;

public class Tuple<T, Y> {
    private T first;
    private Y second;

    Tuple(T first, Y second) {
        this.first = first;
        this.second = second;
    }

    public T getFirst() {
        return this.first;
    }

    public Y getSecond() {
        return this.second;
    }

    public void setFirst(T first) {
        this.first = first;
    }

    public void setSecond(Y second) {
        this.second = second;
    }

}
