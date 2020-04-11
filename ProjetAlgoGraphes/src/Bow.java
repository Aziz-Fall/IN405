public class Bow {
    private int mWeight;
    private int mTerminus;

    private final static int NOT_TERMINUS = 9999;
    private final static int NOT_BOW      = 8888;

    public Bow(){
        mWeight   = NOT_BOW;
        mTerminus = NOT_TERMINUS;
    }

    public int getWeight() {
        return mWeight;
    }

    public int getTerminus() {
        return mTerminus;
    }

    public void setWeight(int weight) {
        mWeight = weight;
    }

    public void setTerminus(int terminus) {
        mTerminus = terminus;
    }

    @Override
    public String toString() {
        return "Bow{" +
                "mWeight=" + mWeight +
                ", mTerminus=" + mTerminus +
                '}';
    }
}
