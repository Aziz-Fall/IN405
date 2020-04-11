import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseEvent;
import java.awt.event.MouseListener;
import java.nio.channels.Pipe;

public class Button extends JButton implements MouseListener {
    private Station mStation;
    private JLabel  mLabel;
    public Button(Point p, Station station){
        mStation = station;
        mLabel   = new JLabel();
        this.setBounds((int)p.getX(), (int)p.getY(), 8, 8);
        this.addMouseListener(this);
        this.setText(Integer.toString(mStation.getNumberStation()));
    }

    @Override
    public void mouseClicked(MouseEvent mouseEvent) {
        this.setBackground(Color.GREEN);
        this.setSize(new Dimension(15, 15));
        System.out.println("On: " + mStation.getNameStation());
    }

    @Override
    public void mousePressed(MouseEvent mouseEvent) {

    }

    @Override
    public void mouseReleased(MouseEvent mouseEvent) {

    }

    @Override
    public void mouseEntered(MouseEvent mouseEvent) {
        setToolTipText(this.mStation.getNameStation());
    }

    @Override
    public void mouseExited(MouseEvent mouseEvent) {

    }

    public Station getStation() {
        return mStation;
    }
}
