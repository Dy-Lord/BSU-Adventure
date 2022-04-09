import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.GradientPaint;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.image.BufferedImage;
import java.awt.image.BufferedImageOp;
import java.awt.image.ByteLookupTable;
import java.awt.image.LookupOp;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

public class mainFrame extends JFrame {

	private static final long serialVersionUID = 1L;
	public static final int CANVAS_WIDTH = 740;
	public static final int CANVAS_HEIGHT = 380;

	private DrawCanvas canvas;

	private static int border = 8;

	private static int rectWight = 200;
	private static int rectHeight = 100;

	private static int xDiv = 100;
	private static int yDiv = 100;

	private static Color borderColor = Color.BLUE;

	static byte[] brightenTable = new byte[256];
	static {
		for (int i = 0; i < 256; i++)
			brightenTable[i] = (byte) (Math.sqrt(i / 255.0) * 255);
	}

	static BufferedImageOp filter = new LookupOp(new ByteLookupTable(0, brightenTable), null);

	public mainFrame() {
		canvas = new DrawCanvas();
		canvas.setPreferredSize(new Dimension(CANVAS_WIDTH, CANVAS_HEIGHT));

		Container cp = getContentPane();
		cp.add(canvas);

		setDefaultCloseOperation(EXIT_ON_CLOSE);
		pack();
		setTitle("Sign GO");
		setVisible(true);
	}

	private class DrawCanvas extends JPanel {

		private static final long serialVersionUID = 1L;

		@Override
		public void paintComponent(Graphics graphics) {
			super.paintComponent(graphics);

			Graphics2D g = (Graphics2D) graphics;

			setBackground(Color.WHITE);

			g.setPaint(new GradientPaint(70, 200, Color.LIGHT_GRAY, 70, 80, Color.white));
			g.fillRect(0, 0, CANVAS_WIDTH, CANVAS_HEIGHT);

			drawStrings(g, "Without filter", xDiv + rectWight / 14, 50);
			draw(g);

			g.translate(150, -163);

			BufferedImage bimage = new BufferedImage(CANVAS_WIDTH, CANVAS_HEIGHT, BufferedImage.TYPE_INT_ARGB);
			Graphics2D image = bimage.createGraphics();

			drawStrings(g, "With filter", xDiv + rectWight / 14, 50);
			draw(image);
			g.drawImage(filter.filter(bimage, null), 0, 0, null);

		}
	}

	public static void draw(Graphics2D g) {
		g.setStroke(new BasicStroke(border));
		g.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

		signShapes roadsign = new signShapes(xDiv, yDiv, rectWight, rectHeight, borderColor);
		roadsign.paint(g);
	}

	public static void drawStrings(Graphics2D g, String str, int x, int y) {
		g.setStroke(new BasicStroke(border));
		g.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

		Font font = new Font("Arial", Font.BOLD, 20);
		g.setFont(font);
		g.setColor(Color.BLACK);

		g.drawString(str, x, y);
	}

	public static void main(String[] args) {

		SwingUtilities.invokeLater(new Runnable() {
			@Override
			public void run() {
				new mainFrame();
			}
		});
	}
}