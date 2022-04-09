import java.awt.BasicStroke;
import java.awt.Shape;
import java.awt.Stroke;
import java.awt.geom.GeneralPath;
import java.awt.geom.PathIterator;

public class StrokeDG implements Stroke {

	private float amp;
	private float step;

	private BasicStroke stroke = new BasicStroke(1);

	public StrokeDG(float amp, float wave) {
		this.amp = amp;
		this.step = wave;
	}

	public Shape createStrokedShape(Shape shape) {

		GeneralPath newshape = new GeneralPath();

		PathIterator iter = shape.getPathIterator(null);
		float[] coords = new float[2];
		float moveX = 0, moveY = 0;
		float lastX = 0, lastY = 0;
		int type = 0, phase = 0;
		float next = 0;

		while (!iter.isDone()) {

			int t = iter.currentSegment(coords);

			switch (t) {
			case PathIterator.SEG_MOVETO:

				moveX = lastX = coords[0];
				moveY = lastY = coords[1];

				newshape.moveTo(moveX, moveY);
				next = step / 2;

				break;
			case PathIterator.SEG_CLOSE:

				coords[0] = moveX;
				coords[1] = moveY;

				break;
			case PathIterator.SEG_LINETO:

				float dx = coords[0] - lastX;
				float dy = coords[1] - lastY;
				float distance = (float) Math.sqrt(dx * dx + dy * dy);

				if (distance >= next) {
					float r = 1.f / distance;
					while (distance >= next) {
						float x = lastX + next * dx * r;
						float y = lastY + next * dy * r;

						if ((phase % 2) == 1)
							newshape.curveTo(newshape.getCurrentPoint().getX(), newshape.getCurrentPoint().getY(),
									x + amp * dy * r, y - amp * dx * r, x, y);
						else
							newshape.lineTo(x, y);

						next += step;
						phase++;
					}
				}

				next -= distance;
				lastX = coords[0];
				lastY = coords[1];

				if (type == PathIterator.SEG_CLOSE)
					newshape.closePath();
				break;
			}
			iter.next();
		}
		return stroke.createStrokedShape(newshape);
	}
}