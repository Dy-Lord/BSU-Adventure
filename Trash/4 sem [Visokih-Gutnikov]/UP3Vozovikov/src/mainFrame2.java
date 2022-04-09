import java.awt.BasicStroke;
import java.awt.Color;
import java.awt.EventQueue;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.RenderingHints;
import java.awt.Shape;
import java.awt.event.ActionEvent;
import java.awt.image.BufferedImage;
import java.awt.print.PageFormat;
import java.awt.print.Printable;
import java.awt.print.PrinterException;
import java.awt.print.PrinterJob;
import java.io.BufferedReader;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;

import javax.print.attribute.HashPrintRequestAttributeSet;
import javax.print.attribute.PrintRequestAttributeSet;
import javax.print.attribute.standard.OrientationRequested;
import javax.print.attribute.standard.Sides;
import javax.swing.GroupLayout;
import javax.swing.JFrame;
import javax.swing.JMenu;
import javax.swing.JMenuBar;
import javax.swing.JMenuItem;
import javax.swing.JPanel;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;
import javax.swing.WindowConstants;

public class mainFrame2 extends JFrame implements Printable {

	private static final long serialVersionUID = 1L;
	public static final int CANVAS_WIDTH = 740;
	public static final int CANVAS_HEIGHT = 380;

	private int centerX = CANVAS_WIDTH / 2;
	private int centerY = CANVAS_HEIGHT / 3;
	private final int paramA = 100;

	private Shape plot = new fooShape(paramA, centerX, centerY);

	private mainFrame2() {

		initComponents();
		this.setTitle("Kappa");
		this.setSize(CANVAS_WIDTH, CANVAS_HEIGHT);

		textLines = initTextLines(new File("C:\\Users\\User01\\eclipse-workspace\\UP3Vozovikov\\src\\fooShape.java"));
	}

	private void initComponents() {

		JPanel jPanel1 = new JPanel() {
			private static final long serialVersionUID = 1L;

			@Override
			public void paintComponent(Graphics g) {

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
		};

		JMenuBar jMenuBar1 = new JMenuBar();
		JMenu jMenu2 = new JMenu();
		JMenuItem jMenuItem1 = new JMenuItem();

		setDefaultCloseOperation(WindowConstants.EXIT_ON_CLOSE);

		jPanel1.setBackground(Color.WHITE);

		GroupLayout jPanel1Layout = new GroupLayout(jPanel1);
		jPanel1.setLayout(jPanel1Layout);

		jPanel1Layout.setHorizontalGroup(
				jPanel1Layout.createParallelGroup(GroupLayout.Alignment.LEADING).addGap(0, 400, Short.MAX_VALUE));

		jPanel1Layout.setVerticalGroup(
				jPanel1Layout.createParallelGroup(GroupLayout.Alignment.LEADING).addGap(0, 279, Short.MAX_VALUE));

		jMenu2.setText("Report");
		jMenuItem1.setText("Print");

		jMenuItem1.addActionListener(this::jMenuItem1ActionPerformed);

		jMenu2.add(jMenuItem1);
		jMenuBar1.add(jMenu2);

		setJMenuBar(jMenuBar1);

		GroupLayout layout = new GroupLayout(getContentPane());
		getContentPane().setLayout(layout);

		layout.setHorizontalGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(jPanel1,
				GroupLayout.DEFAULT_SIZE, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE));

		layout.setVerticalGroup(layout.createParallelGroup(GroupLayout.Alignment.LEADING).addComponent(jPanel1,
				GroupLayout.DEFAULT_SIZE, GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE));

		pack();
	}

	private void jMenuItem1ActionPerformed(ActionEvent evt) {

		PrinterJob job = PrinterJob.getPrinterJob();
		PrintRequestAttributeSet printRequestAttributeSet = new HashPrintRequestAttributeSet();

		printRequestAttributeSet.add(Sides.DUPLEX);
		printRequestAttributeSet.add(OrientationRequested.LANDSCAPE);

		job.setPrintable(this);
		boolean ok = job.printDialog(printRequestAttributeSet);

		if (ok) {
			try {
				job.print(printRequestAttributeSet);
			} catch (PrinterException ex) {
				System.err.print(ex);
			}
		}

	}

	public static void main(String args[]) throws ClassNotFoundException, UnsupportedLookAndFeelException,
			InstantiationException, IllegalAccessException {

		UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
		EventQueue.invokeLater(() -> new mainFrame2().setVisible(true));
	}

	private String[] textLines;
	private int[] pageBreaks;
	private int lineHeight = 14;

	@Override
	public int print(Graphics graphics, PageFormat pageFormat, int pageIndex) throws PrinterException {

		Font font = new Font("Serif", Font.PLAIN, 14);

		graphics.setFont(font);

		if (pageIndex == 0) {

			BufferedImage bufferedImageAll = new BufferedImage(this.getWidth(), this.getHeight(),
					BufferedImage.TYPE_INT_RGB);

			Graphics2D graphics2DForImage = bufferedImageAll.createGraphics();
			this.printAll(graphics2DForImage);

			double scale = pageFormat.getWidth() / this.getWidth();

			int newWidth = (int) (pageFormat.getImageableWidth() * scale / 2.5);
			int newHeight = (int) (pageFormat.getImageableHeight() * scale / 2.5);

			graphics.drawString("Рисунок 1 - Кривая Каппа", newWidth + 30, newHeight + 150);

			Shape plot1 = new fooShape(paramA, (int) (pageFormat.getImageableWidth() / 2 + 70), 200);
			Graphics2D g2d = (Graphics2D) graphics;
			g2d.setRenderingHint(RenderingHints.KEY_ANTIALIASING, RenderingHints.VALUE_ANTIALIAS_ON);

			g2d.setStroke(new BasicStroke(2));

			g2d.setColor(Color.CYAN);
			g2d.setStroke(new StrokeDG(35, 15));

			g2d.draw(plot1);

			return PAGE_EXISTS;
		}

		if (pageBreaks == null) {

			int linesPerPage = (int) (pageFormat.getImageableHeight() / lineHeight);
			int numBreaks = (textLines.length - 1) / linesPerPage + 1;

			pageBreaks = new int[numBreaks];
			for (int b = 0; b < numBreaks; b++) {
				pageBreaks[b] = b * linesPerPage;
			}
		}

		if (pageIndex > pageBreaks.length) {
			return NO_SUCH_PAGE;
		}

		Graphics2D g2D = (Graphics2D) graphics;
		g2D.translate(pageFormat.getImageableX(), pageFormat.getImageableY());

		int y = 0;
		int start = pageBreaks[pageIndex - 1];
		int end = (pageIndex == pageBreaks.length) ? textLines.length : pageBreaks[pageIndex];

		for (int line = start; line < end; line++) {
			y += lineHeight;
			graphics.drawString(textLines[line], 0, y);
		}

		return PAGE_EXISTS;
	}

	private String[] initTextLines(File file) {

		ArrayList<String> result = new ArrayList<>();

		try (BufferedReader reader = new BufferedReader(new FileReader(file))) {

			String line;

			while ((line = reader.readLine()) != null) {
				result.add(line);
			}

		} catch (FileNotFoundException ex) {
			System.out.println("File not found");
			return null;
		} catch (IOException e) {
			System.err.println(e.getMessage());
		}

		return result.toArray(new String[result.size()]);
	}
}