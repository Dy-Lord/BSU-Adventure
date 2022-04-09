package MainPRG;

import java.util.Random;
import java.util.Scanner;

import MainPCG.Gauss;

public class Progonka {

	public static double[] ProgonkaSolve(double[] a, double[] b, double[] c, double[] f) {// –≈ÿ≈Õ»≈ —»—“≈Ã€ Ã≈“ŒƒŒÃ
																							// œ–Œ√ŒÕ »
		double[] Solve = new double[f.length];

		double[] alfa = new double[f.length - 1];
		double[] betta = new double[f.length];

		alfa[0] = b[0] / c[0];
		betta[0] = f[0] / c[0];

		for (int i = 1; i < f.length; i++) {
			double temp = c[i] - a[i - 1] * alfa[i - 1];

			if (i != f.length - 1)
				alfa[i] = b[i] / temp;
			betta[i] = (f[i] + a[i - 1] * betta[i - 1]) / temp;
		}

		Solve[f.length - 1] = betta[f.length - 1];

		for (int i = f.length - 2; i >= 0; i--)
			Solve[i] = alfa[i] * Solve[i + 1] + betta[i];

		return Solve;
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		try {
			Scanner in = new Scanner(System.in);

			System.out.print("Enter the dimension of the matrix: ");

			int size = in.nextInt();
			if (size <= 1) {
				System.out.println("Invalid n value (require: n > 1)");
				in.close();
				return;
			}

			double Mat[][] = new double[size][size];// “–®’ƒ»¿√ŒÕ¿À‹Õ¿ﬂ Ã¿“–»÷¿
			double a[] = new double[size - 1];// ¬≈ “Œ– ¿
			double b[] = new double[size - 1];// ¬≈ “Œ– ¬
			double c[] = new double[size];// ¬≈ “Œ– —
			double yExact[] = new double[size];// “Œ◊Õ€≈ «Õ¿◊≈Õ»ﬂ –≈ÿ≈Õ»ﬂ Y
			double yApprox[] = new double[size];// œ–»¡À»∆®ÕÕ€≈ «Õ¿◊≈Õ»ﬂ –≈ÿ≈Õ»ﬂ Y
			double f[] = new double[size];// ¬≈ “Œ– F

			Random rnd = new Random();
			rnd.setSeed(System.currentTimeMillis());

			int left, right;
			System.out.println("Enter the range of filling the matrix [-|a + b|, |a + b|]: ");
			System.out.print("a = ");
			left = in.nextInt();

			System.out.print("b = ");
			right = in.nextInt();

			if (left > right) {
				System.out.println("Incorrect range!");
				in.close();
				return;
			}

			for (int i = 0; i < size - 1; i++) {
				a[i] = Math.round((rnd.nextDouble() + (left + rnd.nextInt(right - left))) * 100.00) / 100.00;
				b[i] = Math.round((rnd.nextDouble() + (left + rnd.nextInt(right - left))) * 100.00) / 100.00;
			}

			if (b[0] > 0)
				c[0] = b[0] + 1;
			else
				c[0] = b[0] - 1;

			if (a[size - 2] > 0)
				c[size - 1] = a[size - 2] + 1;
			else
				c[size - 1] = a[size - 2] - 1;

			for (int i = 1; i < size - 1; i++)
				if (rnd.nextInt() % 2 == 0)
					c[i] = -(Math.abs(a[i - 1]) + Math.abs(b[i]) + 1);
				else
					c[i] = Math.abs(a[i - 1]) + Math.abs(b[i]) + 1;

			for (int i = 0; i < size; i++)
				yExact[i] = Math.round((rnd.nextDouble() + (left + rnd.nextInt(right - left))) * 100.00) / 100.00;

			for (int i = 0; i < size; i++)
				for (int j = 0; j < size; j++)
					if (i == j) {
						Mat[i][j] = c[i];
						if (c[i] == 0.0) {
							in.close();
							throw new Exception("Zero coefficient (matrix element)!");
						}
					} else if (j == i - 1) {
						Mat[i][j] = -a[i - 1];
						if (a[i - 1] == 0.0) {
							in.close();
							throw new Exception("Zero coefficient (matrix element)!");
						}
					} else if (j == i + 1) {
						Mat[i][j] = -b[i];
						if (b[i] == 0.0) {
							in.close();
							throw new Exception("Zero coefficient (matrix element)!");
						}
					} else
						Mat[i][j] = 0;

			f = Gauss.VectorMatMult(Mat, yExact, size);// «¿ƒ¿Õ»≈ ¬≈ “Œ–¿ F

			System.out.println("Mat A: ");
			Gauss.ViewMat(Mat, size, 0, 2);
			System.out.println();

			System.out.println("Vector _a: ");
			Gauss.PrintVec(a, size - 1, 2);
			System.out.println();

			System.out.println("Vector c: ");
			Gauss.PrintVec(c, size, 2);
			System.out.println();

			System.out.println("Vector _b: ");
			Gauss.PrintVec(b, size - 1, 2);
			System.out.println();

			System.out.println("Vector y(Exact value): ");
			Gauss.PrintVec(yExact, size, 2);
			System.out.println();

			System.out.println("Vector f: ");
			Gauss.PrintVec(f, size, 17);
			System.out.println();

			yApprox = ProgonkaSolve(a, b, c, f);
			System.out.println("Vector y(Approx value): ");
			Gauss.PrintVec(yApprox, size, 17);
			System.out.println();

			System.out.println("\n\n Maximum residual rate: ");
			System.out.println(Gauss.MaxNormNevSolve(Mat, size, yApprox, f));// Õ¿’Œ∆ƒ≈Õ»≈ Ã¿ —»Ã”Ã-ÕŒ–Ã€ Õ≈¬ﬂ« »

			System.out.println("\n\n Maximum error rate: ");
			System.out.println(Gauss.MaxNormPogrSolve(yExact, yApprox, size));// Õ¿’Œ∆ƒ≈Õ»≈ Ã¿ —»Ã”Ã-ÕŒ–Ã€ œŒ√–≈ÿÕŒ—“»

			in.close();
			return;

		} catch (Exception e) {
			System.out.println(e.getMessage());
			return;
		}
	}
}
