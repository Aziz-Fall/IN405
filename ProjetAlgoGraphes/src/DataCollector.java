import java.awt.*;
import java.io.*;
import java.util.ArrayList;

public class DataCollector {

    private static final char sSUMMIT           = 'V';
    private static final char sSTOPPED          = 'E';
    private static final String sSEPARATOR      = " ";
    private static final String CARRIAGE_RETURN = "\n";
    private final static int NB_STATIONS        = 376;

    public Graph recoverDataGraph(Graph g, String nameFile){
        try {
            File f                = new File(nameFile);
            BufferedReader buffer = new BufferedReader( new FileReader(f) );
            String readedLine     = "";
            readedLine = buffer.readLine();
            while( readedLine != null ){
                if( readedLine.charAt(0) == sSUMMIT ){
                    g.getStations().add( splitLine(readedLine) );
                }
                else if( readedLine.charAt(0) == sSTOPPED ) {
                    String[] s;
                    s          = readedLine.split(sSEPARATOR, 6);
                    int x      = Integer.parseInt(s[1]);
                    int y      = Integer.parseInt(s[2]);
                    int weight = Integer.parseInt(s[3]);
                    int dir1   = Integer.parseInt(s[4]);
                    int dir2   = Integer.parseInt(s[5]);

                    g.getNetWork()[x][y].setTerminus(dir1);
                    g.getNetWork()[x][y].setWeight(weight);

                    g.getNetWork()[y][x].setTerminus(dir2);
                    g.getNetWork()[y][x].setWeight(weight);
                }
                readedLine = buffer.readLine();
            }
        } catch (IOException e){
            e.printStackTrace();
        }
        return g;
    }

    public Station splitLine(String readedLine){
        String[] s;

        s = readedLine.split(sSEPARATOR, 6);

        int number = Integer.parseInt(s[1]);
        int line   = Integer.parseInt(s[2]);
        int     x  = Integer.parseInt(s[3]);
        int     y  = Integer.parseInt(s[4]);

        return new Station(s[5], line, number, new Point(x, y));
    }

    /*
    public static void main(String[] args) throws IOException {
        DataCollector dataCollector = new DataCollector();
        Graph g                     = new Graph();
        g                           = dataCollector.recoverDataGraph(g, "../metro_bis.txt");
        Dijkstra d = new Dijkstra(55, 112);
        d.getShortestPath(g, d);

       ArrayList<Station> path =  d.getPath(d, g);
        for (Station station:
             path) {
            System.out.println(station.toString());
        }
    }*/
}
