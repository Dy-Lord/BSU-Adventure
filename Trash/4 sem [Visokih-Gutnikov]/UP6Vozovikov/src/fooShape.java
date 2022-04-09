import java.awt.Rectangle;
import java.awt.Shape;
import java.awt.datatransfer.DataFlavor;
import java.awt.datatransfer.Transferable;
import java.awt.datatransfer.UnsupportedFlavorException;
import java.awt.geom.AffineTransform;
import java.awt.geom.PathIterator;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;
import java.io.Serializable;
import java.util.NoSuchElementException;
import java.util.StringTokenizer;

public class fooShape implements Shape, Transferable, Serializable, Cloneable {

    double centerX,centerY;

    private double startAngle = 0.01;
    private double endAngle = startAngle + 2 * Math.PI + 2 * 0.01;

    double maxX = 600;
    double maxY = 600;
    double minX = -600;
    double minY = -600;

    public fooShape() {
    }

    public double getCenterX() {
        return centerX;
    }

    public void setCenterX(double centerX) {
        this.centerX = centerX;
    }

    public double getCenterY() {
        return centerY;
    }

    public void setCenterY(double centerY) {
        this.centerY = centerY;
    }

    public void translate(double x,double y){
        this.centerX = x;
        this.centerY = y;
    }

    public Object clone() {
        try {
            fooShape s = (fooShape) super.clone(); // make a copy of all fields
            return s;
        } catch (CloneNotSupportedException e) {  // This should never happen
            return this;
        }
    }

    public static fooShape parse(String s) throws NumberFormatException {
        StringTokenizer st = new StringTokenizer(s);
        fooShape scribble = new fooShape();
        while (st.hasMoreTokens()) {
            String t = st.nextToken();
        }
        return scribble;
    }

    @Override
    public PathIterator getPathIterator(AffineTransform at, double flatness) {
        return new ShapeIterator(at);
    }

    @Override
    public Rectangle getBounds() {
        return new Rectangle((int) (minX - 0.5f), (int) (minY - 0.5f), (int) (maxX - minX + 0.5f),
                (int) (maxY - minY + 0.5f));
    }

    @Override
    public Rectangle2D getBounds2D() {
        return new Rectangle2D.Double(minX, minY, maxX - minX, maxY - minY);
    }

    @Override
    public boolean contains(double x, double y) {
        return false;
    }

    @Override
    public boolean contains(Point2D p) {
        return false;
    }

    @Override
    public boolean intersects(double x, double y, double w, double h) {
        return intersects(new Rectangle2D.Double(x, y, w, h));
    }

    @Override
    public boolean intersects(Rectangle2D r) {
        double t = startAngle;

        double x1, y1, x2, y2;

        x2 = 100 * Math.pow(Math.cos(t), 2)/Math.sin(t) + this.getCenterX();
        y2 = 100 * Math.cos(t) + this.getCenterY();

        while (t <= endAngle) {
            x1 = x2;
            y1 = y2;
            x2 = 100 * Math.pow(Math.cos(t), 2)/Math.sin(t) + this.getCenterX();
            y2 = 100 * Math.cos(t) + this.getCenterY();
            t += 0.0005;
            if (r.intersectsLine(x1, y1, x2, y2)) {
                return true;
            }
        }

        return false;
    }

    @Override
    public boolean contains(double x, double y, double w, double h) {
        return false;
    }

    @Override
    public boolean contains(Rectangle2D r) {
        return false;
    }

    @Override public PathIterator getPathIterator(AffineTransform at) {
        return new ShapeIterator(at);
    }

    public static DataFlavor scribbleDataFlavor = new DataFlavor(fooShape.class, "Scribble");

    public static DataFlavor[] supportedFlavors = { scribbleDataFlavor, DataFlavor.stringFlavor };

    public DataFlavor[] getTransferDataFlavors() {
        return (DataFlavor[]) supportedFlavors.clone();
    }

    public boolean isDataFlavorSupported(DataFlavor flavor) {
        return (flavor.equals(scribbleDataFlavor) || flavor.equals(DataFlavor.stringFlavor));
    }

    public Object getTransferData(DataFlavor flavor) throws UnsupportedFlavorException {
        if (flavor.equals(scribbleDataFlavor)) {
            return this;
        } else if (flavor.equals(DataFlavor.stringFlavor)) {
            return toString();
        } else {
            throw new UnsupportedFlavorException(flavor);
        }
    }

    class ShapeIterator implements PathIterator {
        AffineTransform at;

        double flatness = 0;
        double angle = startAngle;
        double step = 10;
        boolean done = false;


        public ShapeIterator(AffineTransform transform) {
            this.at = transform;
            this.flatness = 0;
        }
        @Override
        public int getWindingRule() {
            return WIND_NON_ZERO;
        }

        @Override
        public boolean isDone() {
            return done;
        }

        @Override
        public void next() {
            if (done)
                return;
            if (flatness == 0)
                step = 0.05;
            else
                step = flatness;
            angle += step;
            if (angle >= endAngle)
                done = true;
        }

        @Override
        public int currentSegment(float[] coords) {
            coords[0] = (float) (100 * Math.pow(Math.cos(angle), 2) / Math.sin(angle));
            coords[1] = -(float) (100 * Math.cos(angle));
            if (angle >= endAngle) done = true;
            if (angle == startAngle) return SEG_MOVETO;
            else return SEG_LINETO;
        }

        @Override
        public int currentSegment(double[] coords) {
            coords[0] = (float) (100 * Math.pow(Math.cos(angle), 2) / Math.sin(angle));
            coords[1] = -(float) (100 * Math.cos(angle));
            if (angle >= endAngle) done = true;
            if (angle == startAngle) return SEG_MOVETO;
            else return SEG_LINETO;
        }
    }
}
