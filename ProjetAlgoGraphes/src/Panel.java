import javax.imageio.ImageIO;
import javax.swing.JPanel;
import java.awt.*;
import java.io.File;
import java.io.IOException;

public class Panel extends JPanel {

    public Panel(){
        this.setLayout(null);
    }
    @Override
    public void paintComponent(Graphics g) {
        try{
            Image img = ImageIO.read(new File("../metro_bis.bmp"));
            g.drawImage(img, 0, 0, this);
        }catch (IOException e){
            e.printStackTrace();
        }
    }
}
