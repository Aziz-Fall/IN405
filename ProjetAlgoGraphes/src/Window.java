import javax.swing.JFrame;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class Window extends JFrame{

    private final static int sWIDTH       = 700;
    private final static int sHeight      = 700;
    private final static int sNB_STATIONS = 376;

    public Panel panel                    = new Panel();
    public Button[] mButtons              = new Button[sNB_STATIONS];
    private Graph mGraph                  = new Graph();
    private DataCollector mDataCollector  = new DataCollector();
    private int mNbClick;
    private Dijkstra mDijkstra;
    private ButtonListener[] mButtonListener;


    public Window(String name){
        mGraph = mDataCollector.recoverDataGraph(mGraph, "../metro_bis.txt");
        this.setName(name);
        this.setSize(new Dimension(sWIDTH, sHeight));
        this.setDefaultCloseOperation(Window.EXIT_ON_CLOSE);
        this.getContentPane().setLayout( new FlowLayout() );
        this.setLayout(null);
        mNbClick        = 0;
        mDijkstra       = new Dijkstra();
        mButtonListener = new ButtonListener[sNB_STATIONS];
        for( int i = 0; i < sNB_STATIONS; i++ ){
            mButtons[i] = new Button(mGraph.getStations().get(i).getCoordinated(), mGraph.getStations().get(i));
            panel.add(mButtons[i]);
            mButtons[i].addActionListener(new ButtonListener());
        }
        this.setContentPane(panel);
        this.setVisible(true);
    }



    public static void main(String[] args) {
        Window window = new Window("Métro Parisiens");
    }

    public void setNbClick(int nbClick) {
        mNbClick = nbClick;
    }



    class ButtonListener implements ActionListener{
        @Override
        public void actionPerformed(ActionEvent actionEvent) {
            if( mNbClick > 2 ){
                mNbClick = 0;
            }
            if( mNbClick == 1 ) {
                mDijkstra.setNumberLineBegin(Integer.parseInt(actionEvent.getActionCommand()));
                System.out.println(actionEvent.getActionCommand());
                ++mNbClick;
                System.out.println("Click: "+mNbClick);
            }
            if( mNbClick == 0 ) {
                mDijkstra.setNumberLineBegin(Integer.parseInt(actionEvent.getActionCommand()));
                System.out.println(actionEvent.getActionCommand());
                ++mNbClick;
                System.out.println("Click: "+mNbClick);
            }
        }
    }
}
