import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.Graphics2D;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.geom.AffineTransform;
import java.awt.geom.Ellipse2D;
import java.awt.geom.GeneralPath;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.Timer;

//example of arguments: 300 300 3 255 0 0 255 255 0 0 255 255

public class mainFrame {

	public static void main(String[] args) {

		if (args.length < 12)
			System.out.println(
					"Invalid count of arguments:\n" + "Example:\n" + "300 300 3 255 0 0 255 255 0 0 255 255\t\t"
							+ "x y wight(border) RGB(border color) RGB(cicle color) RGB(triangle color)");
		else {
			try {

				int x = Integer.parseInt(args[0]);
				int y = Integer.parseInt(args[1]);
				int wight = Integer.parseInt(args[2]);

				Color borderColor = new Color(Integer.parseInt(args[3]), Integer.parseInt(args[4]),
						Integer.parseInt(args[5]));
				Color circleColor = new Color(Integer.parseInt(args[6]), Integer.parseInt(args[7]),
						Integer.parseInt(args[8]));
				Color triangleColor = new Color(Integer.parseInt(args[9]), Integer.parseInt(args[10]),
						Integer.parseInt(args[11]));

				trigon shapes = new trigon();

				JFrame frame = new JFrame("Circle in triangle");
				final JPanel panel = new JPanel();

				frame.setPreferredSize(new Dimension(800, 800));
				frame.add(panel);
				frame.setVisible(true);
				frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
				frame.pack();

				Timer timer = new Timer(60, new ActionListener() {
					int count = 0;

					@Override
					public void actionPerformed(ActionEvent arg0) {
						Graphics2D gr = (Graphics2D) panel.getRootPane().getGraphics();
						panel.update(gr);

						GeneralPath triangle = new GeneralPath();
						GeneralPath circle = new GeneralPath();
						GeneralPath dote = new GeneralPath();

						triangle.append(shapes.getShape(0), true);
						circle.append(shapes.getShape(1), true);
						dote.append(new Ellipse2D.Double((double) x, (double) y, 10, 10), true);

						AffineTransform tranforms = AffineTransform.getRotateInstance(Math.PI / 30 * count, x, y);

						gr.setStroke(new BasicStroke(wight));

						gr.setColor(Color.BLACK);
						gr.fill(dote);

						gr.transform(tranforms);
						gr.setColor(triangleColor);
						gr.fill(triangle);

						gr.setColor(circleColor);
						gr.fill(circle);

						gr.setColor(borderColor);
						gr.draw(triangle);

						gr.draw(circle);

						count--;
					}
				});
				timer.start();

			} catch (Exception e) {
				System.err.println("Error:\nMessage:\t" + e.getMessage() + "\nStackTrace:\t" + e.getStackTrace());
			}
		}
	}
}