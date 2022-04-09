import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Font;
import java.awt.FontMetrics;
import java.awt.GradientPaint;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Rectangle;
import java.awt.Shape;
import java.awt.font.GlyphVector;
import java.awt.geom.AffineTransform;
import java.awt.geom.PathIterator;
import java.awt.geom.Point2D;
import java.awt.geom.Rectangle2D;

public class signShapes implements Shape {

	private Rectangle2D rect;
	private Color borderColor;

	signShapes(int x, int y, int width, int height, Color border) {
		this.rect = new Rectangle(x, y, width, height);
		this.borderColor = border;
	}

	public void paint(Graphics graphics) {

		Graphics2D graphics2D = (Graphics2D) graphics;

		graphics2D.setPaint(Color.DARK_GRAY);

		AffineTransform shadow = AffineTransform.getShearInstance(-1.0, 0);
		shadow.scale(1.0, 0.8);

		graphics2D.translate(150, 80);

		Shape shRect = shadow.createTransformedShape(new Rectangle((int) rect.getX(), (int) rect.getY(),
				(int) rect.getWidth(), (int) rect.getHeight() - 20));
		graphics2D.fill(shRect);

		graphics2D.translate(-150, -80);

		graphics2D.setPaint(Color.white);

		graphics2D.setPaint(new GradientPaint(70, 200, Color.DARK_GRAY, 70, 80, Color.white));
		graphics2D.fillRect((int) rect.getX(), (int) rect.getY(), (int) rect.getWidth(), (int) rect.getHeight());

		graphics2D.setColor(borderColor);
		graphics2D.draw(rect);

		Font font = new Font("SansSerif", Font.BOLD, 40);
		graphics.setFont(font);
		FontMetrics f = graphics.getFontMetrics(font);

		GlyphVector gv = font.createGlyphVector(graphics2D.getFontRenderContext(), "GO");
		Shape gShape = gv.getGlyphOutline(0);
		Shape oShape = gv.getGlyphOutline(1);

		int xTrans = (int) (rect.getX() + rect.getWidth() / 2) - f.charWidth('G');
		int yTrans = (int) (rect.getY() + rect.getHeight() / 2) + (int) f.getHeight() / 4;

		graphics2D.setStroke(new BasicStroke(1.0f));

		// gShadow

		graphics2D.translate(xTrans, yTrans);
		graphics2D.translate(6, 5);
		graphics2D.setPaint(Color.BLACK);
		graphics2D.fill(shadow.createTransformedShape(gShape));

		// gBorder

		graphics2D.translate(-6, -5);
		graphics2D.setPaint(borderColor);
		graphics2D.fill(gShape);
		graphics2D.draw(gShape);

		// oShadow

		graphics2D.translate(2, 0);
		graphics2D.translate(6, 5);
		graphics2D.setPaint(Color.BLACK);
		graphics2D.fill(shadow.createTransformedShape(oShape));

		// oBorder

		graphics2D.translate(-6, -5);
		graphics2D.setPaint(borderColor);
		graphics2D.fill(oShape);
		graphics2D.draw(oShape);
	}

	@Override
	public boolean contains(Point2D arg0) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean contains(Rectangle2D arg0) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean contains(double arg0, double arg1) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean contains(double arg0, double arg1, double arg2, double arg3) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public Rectangle getBounds() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public Rectangle2D getBounds2D() {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public PathIterator getPathIterator(AffineTransform arg0) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public PathIterator getPathIterator(AffineTransform arg0, double arg1) {
		// TODO Auto-generated method stub
		return null;
	}

	@Override
	public boolean intersects(Rectangle2D arg0) {
		// TODO Auto-generated method stub
		return false;
	}

	@Override
	public boolean intersects(double arg0, double arg1, double arg2, double arg3) {
		// TODO Auto-generated method stub
		return false;
	}

}