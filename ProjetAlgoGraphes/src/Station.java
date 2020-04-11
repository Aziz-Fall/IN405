import java.awt.Point;
import java.util.ArrayList;

public class Station {
    private String mNameStation;
    private int mNumberLine,
                mNumberStation;
    private Point mCoordinated;

    public Station(String nameStation, int numberLine, int numberStation, Point coordinated){
        mNameStation = nameStation;
        mNumberLine  = numberLine;
        mNumberStation = numberStation;
        mCoordinated   = coordinated.getLocation();
    }

    public String getNameStation() {
        return mNameStation;
    }

    public int getNumberLine() {
        return mNumberLine;
    }

    public int getNumberStation() {
        return mNumberStation;
    }

    public Point getCoordinated() {
        return mCoordinated;
    }

    @Override
    public String toString() {
        return "Station{" +
                "mNameStation='" + mNameStation + '\'' +
                ", mNumberLine=" + mNumberLine +
                ", mNumberStation=" + mNumberStation +
                ", mCoordinated{ x: " + mCoordinated.getX() + " y: " + mCoordinated.getY() +
                '}';
    }
}
