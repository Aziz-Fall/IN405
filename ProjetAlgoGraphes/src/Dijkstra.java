import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;

public class Dijkstra {
    
    private int mNumberLineBegin;
    private int mNumberLineEnd;
    private int mDuration;
    private int[] mParent;
    private ArrayList<Station> mStationsPath;

    private final static int sINFINITY    = 8888;
    private final static int sNO_TERMINUS = 9999;
    private final static int sNO_PARENT   = -1;
    private final static int sNB_STATIONS = 376;
    private final static int sVISITED     = 1;

    public Dijkstra( int numberLineBegin, int numberLineEnd ){
        mNumberLineBegin = numberLineBegin;
        mNumberLineEnd   = numberLineEnd;
        mDuration        = 0;
        mParent          = new int[sNB_STATIONS];
        mStationsPath    = new ArrayList<Station>();
    }
    public Dijkstra(){
        mDuration        = 0;
        mParent          = new int[sNB_STATIONS];
        mStationsPath    = new ArrayList<Station>();
    }

    public void setNumberLineBegin(int numberLineBegin) {
        mNumberLineBegin = numberLineBegin;
    }

    public void setNumberLineEnd(int numberLineEnd) {
        mNumberLineEnd = numberLineEnd;
    }

    public ArrayList<Station> getStationsPath() {
        return mStationsPath;
    }

    public int getNumberLineBegin() {
        return mNumberLineBegin;
    }

    public int getNumberLineEnd() {
        return mNumberLineEnd;
    }

    public int getDuration() {
        return mDuration;
    }

    public int[] getParent() {
        return mParent;
    }

    public void setDuration(int duration) {
        mDuration = duration;
    }

    public void setParent(int[] parent) {
        mParent = parent;
    }

    public void setStationsPath(ArrayList<Station> stationsPath) {
        mStationsPath = stationsPath;
    }

    public void getShortestPath(Graph g, Dijkstra d){
        int[] parent = new int[sNB_STATIONS], dist = new int[sNB_STATIONS], stationVisited = new int[sNB_STATIONS];
        initializations(dist, parent, stationVisited, g, d.getNumberLineBegin());
        stationVisited[0] = sVISITED;

        while ( !allNodesAreVisited(stationVisited) )
        {
            int stationToTrait        = index_min(stationVisited, dist);
            stationVisited[stationToTrait] = sVISITED;
            for( int i = 0; i < sNB_STATIONS; i++ )
                update(dist, parent, stationToTrait, i, g);
        }

        d.setParent(parent);

    }

    private int index_min(int node_visited[], int dist[])
    {
        int min = sINFINITY, node = -1;
        for( int i = 0; i < sNB_STATIONS; i++)
        {
            if( node_visited[i] != sVISITED && dist[i] <= min )
            {
                min  = dist[i];
                node = i;
            }
        }
        return node;
    }

    private void initializations(int[] dist, int[] parent, int[] stationVisited, Graph g, int begin)
    {
        for( int i = 0; i < sNB_STATIONS; i++)
        {
            parent[i] = ( g.getNetWork()[begin][i].getWeight() == sINFINITY )? sNO_PARENT : begin;
            stationVisited[i] = 0;
            dist[i] = g.getNetWork()[begin][i].getWeight();
        }
        dist[begin]   = 0;
        parent[begin] = sNO_PARENT;
    }

    public void update(int dist[], int parent[], int t, int k, Graph g)
    {
        if( dist[k] > dist[t] + g.getNetWork()[t][k].getWeight() )
        {
            dist[k]   = dist[t] + g.getNetWork()[t][k].getWeight();
            parent[k] = t;
        }
    }

    private boolean allNodesAreVisited(int stationVisited[])
    {
        for( int i = 0; i < sNB_STATIONS; i++)
            if( stationVisited[i] != sVISITED )
                return false;
        return true;
    }

    public ArrayList<Station> getPath(Dijkstra d, Graph g){
        ArrayList<Station> buildPath = new ArrayList<Station>();
        int e = d.getNumberLineEnd();
        while(e != d.getNumberLineBegin())
        {
            d.getStationsPath().add(g.getStations().get(e));
            int tmp = e;
            e = d.getParent()[e];
            d.setDuration(d.getDuration() + g.getNetWork()[tmp][e].getWeight());
        }
        d.getStationsPath().add(g.getStations().get(e));
        //Inversion du liste de chemin.
        Collections.reverse(d.getStationsPath());

        //Écriture du chemin à parcourir.
        int p2 = 1, p1 = 0, tmp;

        buildPath.add(g.getStations().get(d.getNumberLineBegin()));

        System.out.println("- Vous êtes à " + g.getStations().get(d.getNumberLineBegin()).getNameStation());

        while (p2 < d.getStationsPath().size()) {
            if ((g.getNetWork()[p1][p2].getTerminus() != sNO_TERMINUS) && (d.getStationsPath().get(p1).getNumberStation() == d.getNumberLineBegin())) {
                tmp = p1 + 1;
                if (d.getStationsPath().get(p1).getNumberStation() == 30)
                    System.out.print("- Prenez la ligne 3bis ");
                else if (d.getStationsPath().get(p1).getNumberStation() == 70)
                    System.out.print("- Prenez la ligne 7bis ");
                else
                    System.out.print("- Prenez la ligne " + d.getStationsPath().get(p1).getNumberLine());
                int x = d.getStationsPath().get(p1).getNumberStation(), y = d.getStationsPath().get(tmp).getNumberStation();
                System.out.println(" direction " + g.getStations().get(g.getNetWork()[x][y].getTerminus()).getNameStation());
            }
            int x = d.getStationsPath().get(p1).getNumberStation(), y = d.getStationsPath().get(p2).getNumberStation();
            if (g.getNetWork()[x][y].getTerminus() == sNO_TERMINUS) {
                buildPath.add(g.getStations().get(x));
                System.out.print("- A " + g.getStations().get(x).getNameStation() + " prenez la ligne ");
                if (g.getStations().get(x).getNumberLine() == 30)
                    System.out.print("3bis ");
                else if (g.getStations().get(x).getNumberLine() == 70)
                    System.out.print("7bis ");
                else
                    System.out.print(g.getStations().get(x).getNumberLine());
                if (d.getStationsPath().get(p2).getNumberLine() != d.getNumberLineEnd()) {
                    tmp = p2 + 1;
                    int x1 = d.getStationsPath().get(p2).getNumberStation(), y1 = d.getStationsPath().get(tmp).getNumberStation();
                    System.out.println(" direction " + g.getStations().get(g.getNetWork()[x1][y1].getTerminus()).getNameStation());
                } else
                    System.out.println("");
            }
            ++p1; ++p2;
        }
        System.out.println("Vous devriez arriver à " + g.getStations().get(d.getNumberLineEnd()).getNameStation() + " dans " + getTime(d.getDuration()));

        buildPath.add(g.getStations().get(d.getNumberLineEnd()));

        return buildPath;
    }

    private String getTime(int times){
        int h = times / 3600, min = (times % 3600)/60;
        String s = "";
        s += ( h > 0 ) ? h +" H " + min +" min." : min + " min.";
        return s;
    }
}
