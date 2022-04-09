import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Container;
import java.awt.Dimension;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.Shape;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.SwingUtilities;

public class mainFrame extends JFrame {

	private static final long serialVersionUID = 1L;
	public static final int CANVAS_WIDTH = 740;
	public static final int CANVAS_HEIGHT = 380;

	private int centerX = CANVAS_WIDTH / 2;
	private int centerY = CANVAS_HEIGHT / 2;
	private final int paramA = 100;

	private Shape plot = new fooShape(paramA, centerX, centerY);

	private DrawCanvas canvas;

	public mainFrame() {
		canvas = new DrawCanvas();
		canvas.setPreferredSize(new Dimension(CANVAS_WIDTH, CANVAS_HEIGHT));

		Container cp = getContentPane();
		cp.add(canvas);

		setDefaultCloseOperation(EXIT_ON_CLOSE);
		pack();
		setTitle("Kappa");
		setVisible(true);
	}

	private class DrawCanvas extends JPanel {

		private static final long serialVersionUID = 1L;

		@Override
		public void paintComponent(Graphics g) {
			super.paintComponent(g);

			g.setColor(Color.white);
			g.fillRect(0, 0, getWidth(), getHeight());
			Graphics2D g2d = (Graphics2D) g;

			g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

			g2d.setStroke(new BasicStroke(2));
			g2d.setColor(Color.MAGENTA);

			g2d.setColor(Color.CYAN);
			g2d.setStroke(new StrokeDG(35, 15));
			g2d.draw(plot);
		}
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
