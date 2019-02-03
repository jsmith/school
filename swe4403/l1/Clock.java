import java.lang.System;

public abstract class Clock {
    long startMillis;
    Format format;

    Clock() {
        this.format = this.makeFormat();
        this.startMillis = System.currentTimeMillis();
    }

    public void reset() {
        this.startMillis = System.currentTimeMillis();
    }

    public String elapsedTime() {
        long elapsedMillis = System.currentTimeMillis() - this.startMillis;
        Object elapsedTime = this.format.format(elapsedMillis);
        return elapsedTime.toString();
    }

    abstract Format makeFormat();
}
