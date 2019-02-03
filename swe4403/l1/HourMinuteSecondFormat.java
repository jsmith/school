import java.lang.Math;

class HourMinuteSecondFormat implements Format {
    public String format(long millis) {
        // Calculate seconds & cast to integer
        int seconds = (int) (millis / 1000);
        
        int minutes = seconds / 60;
        seconds = seconds % 60;
        
        int hours = minutes / 60;
        minutes = minutes % 60;

        // Make sure that hours < 24
        hours = hours % 24;

        return String.format("%d:%d:%d", hours, minutes, seconds);
    }
}