import java.awt.*;
import java.awt.event.*;
import javax.swing.*;
import java.awt.datatransfer.*;  
import java.awt.dnd.*;
import java.util.ArrayList;

public class mainFrame extends JComponent
        implements DragGestureListener,   
                   DragSourceListener,    
                   DropTargetListener,    
                   MouseListener,         
                   MouseMotionListener    
{
    static ArrayList<fooShape> fooArray = new ArrayList<fooShape>();
    fooShape beingDragged;
    DragSource dragSource;                  
    boolean dragMode;                      

    static final int LINEWIDTH = 12;
    static final StrokeDG linestyle = new StrokeDG(35,15);

    public mainFrame() {
        addMouseListener(this);
        addMouseMotionListener(this);

        dragSource = DragSource.getDefaultDragSource();
        dragSource.createDefaultDragGestureRecognizer(this, DnDConstants.ACTION_COPY_OR_MOVE,this);

        DropTarget dropTarget = new DropTarget(this, this);
        this.setDropTarget(dropTarget);  
    }


    public void paintComponent(Graphics g) {
        super.paintComponent(g);
        Graphics2D g2 = (Graphics2D) g;
        g2.setStroke(linestyle);
        g2.setColor(Color.BLACK);

        int numScribbles = fooArray.size();

        for (int i = 0; i < numScribbles; i++) {
        	fooShape s = fooArray.get(i);
            g2.translate(s.getCenterX(),s.getCenterY());
            g2.draw(s);
            g2.translate(-s.getCenterX(),-s.getCenterY());
        }
    }
    public void setDragMode(boolean dragMode) {
        this.dragMode = dragMode;
    }
    public void mousePressed(MouseEvent e) {}
    public void mouseReleased(MouseEvent e) {}
    public void mouseClicked(MouseEvent e) {}
    public void mouseEntered(MouseEvent e) {}
    public void mouseExited(MouseEvent e) {}
    public void mouseDragged(MouseEvent e) {}
    public void mouseMoved(MouseEvent e) {}

    public void dragGestureRecognized(DragGestureEvent e) {

        MouseEvent inputEvent = (MouseEvent) e.getTriggerEvent();

        int x = inputEvent.getX();
        int y = inputEvent.getY();

        Rectangle r = new Rectangle(x - LINEWIDTH, y - LINEWIDTH, LINEWIDTH * 2, LINEWIDTH * 2);
        int fooCount = fooArray.size();

        for (int i = 0; i < fooCount; i++) {
        	fooShape s = (fooShape) fooArray.get(i);

            if (s.intersects(r)) {
            	beingDragged = s;
                fooShape dragScribble = (fooShape) s.clone();
                dragScribble.translate(-x, -y);
                Cursor cursor;
                switch (e.getDragAction()) {
                    case DnDConstants.ACTION_COPY:
                        cursor = DragSource.DefaultCopyDrop;
                        break;
                    case DnDConstants.ACTION_MOVE:
                        cursor = DragSource.DefaultMoveDrop;
                        break;
                    default:
                        return;   
                }
                if (dragSource.isDragImageSupported()) {
                    Rectangle scribbleBox = dragScribble.getBounds();
                    Image dragImage = this.createImage(scribbleBox.width, scribbleBox.height);
                    Graphics2D g = (Graphics2D) dragImage.getGraphics();

                    g.setColor(new Color(0, 0, 0, 0));
                    g.fillRect(0, 0, scribbleBox.width, scribbleBox.height);
                    g.setColor(Color.black);
                    g.setStroke(linestyle);
                    g.translate(-scribbleBox.x, -scribbleBox.y);
                    g.draw(dragScribble);

                    Point hotspot = new Point(-scribbleBox.x, -scribbleBox.y);
                    e.startDrag(cursor, dragImage, hotspot, dragScribble, this);
                } else {
                    e.startDrag(cursor, dragScribble, this);
                }
                return;
            }
        }
    }
    public void dragDropEnd(DragSourceDropEvent e) {
        if (!e.getDropSuccess())
            return;

        int action = e.getDropAction();
        if (action == DnDConstants.ACTION_MOVE) {
            fooArray.remove(beingDragged);
            beingDragged = null;
            repaint();
        }
    }

    public void dragEnter(DragSourceDragEvent e) {}
    public void dragExit(DragSourceEvent e) {}
    public void dropActionChanged(DragSourceDragEvent e) {}
    public void dragOver(DragSourceDragEvent e) {}

    public void dragEnter(DropTargetDragEvent e) {
        if (e.isDataFlavorSupported(fooShape.scribbleDataFlavor) || e.isDataFlavorSupported(DataFlavor.stringFlavor)) {
            e.acceptDrag(DnDConstants.ACTION_COPY_OR_MOVE);
        }
    }

    public void dragExit(DropTargetEvent e) { }

    public void drop(DropTargetDropEvent e) {
        if (e.isDataFlavorSupported(fooShape.scribbleDataFlavor) ||
        		e.isDataFlavorSupported(DataFlavor.stringFlavor)) {
            e.acceptDrop(DnDConstants.ACTION_COPY_OR_MOVE);
        } else {
            e.rejectDrop();
            return;
        }
        Transferable t = e.getTransferable(); 
        fooShape droppedScribble;
        try {
            droppedScribble = (fooShape)
            		t.getTransferData(fooShape.scribbleDataFlavor);
        } catch (Exception ex) {  
            try {
                String s = (String) t.getTransferData(DataFlavor.stringFlavor);
                droppedScribble = fooShape.parse(s);
            } catch (Exception ex2) {
           
                e.dropComplete(false);
                return;
            }
        }
        Point p = e.getLocation();         
        droppedScribble.translate(p.getX(), p.getY());  
        fooArray.add(droppedScribble);
        repaint();
        e.dropComplete(true);                          
    }

    public void dragOver(DropTargetDragEvent e) {}
    public void dropActionChanged(DropTargetDragEvent e) {}

    public static void main(String[] args) {
        JFrame frame = new JFrame("Kappa");
        frame.addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent e) { System.exit(0); }
        });

        final mainFrame scribblePane = new mainFrame();

        frame.getContentPane().add(scribblePane, BorderLayout.CENTER);
        scribblePane.setDragMode(true);
        frame.setSize(600, 600);

        fooShape shape = new fooShape();
        shape.translate(300,300);
        fooArray.add(shape);

        scribblePane.repaint();
        frame.setVisible(true);
    }
}