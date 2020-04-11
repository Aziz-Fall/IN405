import java.util.ArrayList;

public class Graph {

    private final static int NB_STATIONS = 376;
    private ArrayList<Station> mStations;
    private Bow[][] mNetWork;

    public Graph(){
        mStations = new ArrayList<Station>(NB_STATIONS);
        mNetWork = initNetWork();
    }

    public Bow[][] initNetWork(){
        Bow[][] netWork = new Bow[NB_STATIONS][NB_STATIONS];
        for( int i = 0; i < NB_STATIONS; i++)
            for( int j = 0; j < NB_STATIONS; j++)
                netWork[i][j] = new Bow();

        return netWork;
    }


    public void setStations(ArrayList<Station> stations) {
        mStations = stations;
    }

    public void setNetWork(Bow[][] netWork) {
        mNetWork = netWork;
    }

    public static int getNbStations() {
        return NB_STATIONS;
    }

    public ArrayList<Station> getStations() {
        return mStations;
    }

    public Bow[][] getNetWork() {
        return mNetWork;
    }
}
