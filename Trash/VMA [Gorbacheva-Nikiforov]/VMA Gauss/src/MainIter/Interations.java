package MainIter;

import java.math.BigDecimal;
import java.util.Random;
import java.util.Scanner;

import MainPCG.Gauss;

public class Interations {

	static double MethodPresicion = Math.pow(10, -5);
	static int Precision = 17;
	static int InterationCount = 0;

	static int left = -1;
	static int right = 1;

	public static double[] RelaxSolution(double MatA[][], double VecF[], double Omega, double Presision) { // Ã≈“Œƒ
																											// –≈À¿ —¿÷»»

		int size = VecF.length;
		double[] startVec = new double[size];
		double[] prevVec = new double[size];
		double[] nextVec = new double[size];

		for (int i = 0; i < size; i++) {
			startVec[i] = (VecF[i] / MatA[i][i]) * Omega;
			nextVec[i] = startVec[i];
		}

		do {

			InterationCount++;
			prevVec = CloneVec(nextVec);

			for (int i = 0; i < size; i++) {

				nextVec[i] *= (1 - Omega);
				nextVec[i] += startVec[i];

				for (int j = 0; j < size; j++)
					if (i != j)
						nextVec[i] -= (MatA[i][j] / MatA[i][i]) * nextVec[j] * Omega;
			}

		} while ((Gauss.MaxNormPogrSolve(nextVec, prevVec, size) >= Presision) == true);

		return nextVec;

	}

	public static double[] SimpleSolution(double MatA[][], double VecF[], double Presision) { // Ã≈“Œƒ œ–Œ—“Œ… »“≈–¿÷»»

		int size = VecF.length;
		double[] startVec = new double[size];
		double[] prevVec = new double[size];
		double[] nextVec = new double[size];

		for (int i = 0; i < size; i++) {
			startVec[i] = VecF[i] / MatA[i][i];
			nextVec[i] = startVec[i];
		}

		do {

			InterationCount++;
			prevVec = CloneVec(nextVec);
			ZeroingVec(nextVec);

			for (int i = 0; i < size; i++) {
				nextVec[i] += startVec[i];
				for (int j = 0; j < size; j++)
					if (i != j)
						nextVec[i] -= (MatA[i][j] / MatA[i][i]) * prevVec[j];
			}

		} while ((Gauss.MaxNormPogrSolve(nextVec, prevVec, size) >= Presision) == true);

		return nextVec;

	}

	public static void ZeroingVec(double[] Vec) { // Œ¡Õ”À≈Õ»≈ ¬≈ “Œ–¿

		for (int i = 0; i < Vec.length; i++)
			Vec[i] = 0;
	}

	public static double[] CloneVec(double[] Vec) { //  Œœ»–Œ¬¿Õ»≈ ¬≈ “Œ–¿

		double[] newVec = new double[Vec.length];

		for (int i = 0; i < Vec.length; i++)
			newVec[i] = Vec[i];

		return newVec;
	}

	public static double[] MatVecMultiplication(double Mat[][], double Vec[]) { // ”ÃÕŒ∆≈Õ»≈ Ã¿“–»÷

		double newVec[] = new double[Vec.length];
		for (int i = 0; i < Vec.length; i++)
			newVec[i] = 0;

		for (int i = 0; i < Mat.length; i++)
			for (int j = 0; j < Mat.length; j++)
				newVec[i] += Mat[i][j] * Vec[j];

		return newVec;
	}

	public static double[][] MatTransponation(double[][] Mat) { // “–¿Õ—œŒÕ»–Œ¬¿Õ»≈ Ã¿“–»÷€

		double newMat[][] = new double[Mat.length][Mat.length];

		for (int i = 0; i < Mat.length; i++)
			for (int j = 0; j < Mat.length; j++)
				newMat[i][j] = Mat[j][i];

		return newMat;
	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Scanner in = new Scanner(System.in);

		System.out.print("Enter the dimension of the matrix: ");

		int n = in.nextInt();
		if (n <= 1) {
			System.out.println("Invalid n value (require: n > 1)");
			in.close();
			return;
		}

		double[][] MatA = new double[n][n]; // »—’ŒƒÕ¿ﬂ Ã¿“–»÷¿
		double[][] TransMat = new double[n][n]; // “–¿Õ—œŒÕ»–Œ¬¿ÕÕ¿ﬂ Ã¿“–»÷¿
		double[] ExactValue = new double[n]; // “Œ◊ÕŒ≈ –≈ÿ≈Õ»≈
		double[] ApproxValue = new double[n]; // œ–»¡À»∆®ÕÕŒ≈ –≈ÿ≈Õ»≈
		double[] VectorF = new double[n]; // ¬≈ “Œ– F

		Random rnd = new Random();
		rnd.setSeed(System.currentTimeMillis());

		System.out.println("Input Matrix A: ");

		for (int i = 0; i < n; i++)
			for (int j = 0; j < n; j++)
				MatA[i][j] = Math.round((rnd.nextDouble() + (left + rnd.nextInt(right - left))) * 100.00) / 100.00;

		for (int i = 0; i < n; i++) {
			MatA[i][i] = Math.abs(MatA[i][i]);
			for (int j = 0; j < n; j++)
				MatA[i][i] += Math.abs(MatA[i][j]);
		}

		TransMat = MatTransponation(MatA);

		Gauss.ViewMat(MatA, n, 0, 2);

		System.out.println("\n\nExacts Values X: ");
		for (int i = 0; i < n; i++)
			ExactValue[i] = Math.round((rnd.nextDouble() + (left + rnd.nextInt(right - left))) * 100.00) / 100.00;

		Gauss.PrintVec(ExactValue, n, 17);

		System.out.println("\n\nVector F Values: ");
		VectorF = Gauss.VectorMatMult(MatA, ExactValue, n);
		Gauss.PrintVec(VectorF, n, Precision);

		VectorF = MatVecMultiplication(TransMat, VectorF);
		MatA = Gauss.MatMultiplication(TransMat, MatA, n);

		Gauss.ViewMat(MatA, n, 0, 2);
		Gauss.PrintVec(VectorF, n, Precision);

		System.out.println("\n\nSimple iteration method:");

		ApproxValue = SimpleSolution(MatA, VectorF, MethodPresicion);

		System.out.println("\n\nApprox Values X: ");
		Gauss.PrintVec(ApproxValue, n, Precision);

		System.out.println("\n\n Maximum error rate: ");
		System.out.println(Gauss.MaxNormPogrSolve(ExactValue, ApproxValue, n));
		System.out.println(InterationCount);

		System.out.println("\n\nRelaxation method");

		for (double i = 0.1; i < 2; i += 0.1) {
			InterationCount = 0;
			double[] tempApprox = RelaxSolution(MatA, VectorF, i, MethodPresicion);
			System.out.println(BigDecimal.valueOf(i).setScale(2, BigDecimal.ROUND_HALF_UP) + "\t"
					+ (InterationCount + 1) + "\t" + Gauss.MaxNormPogrSolve(ExactValue, tempApprox, n));

		}

		Gauss.PrintVec(RelaxSolution(MatA, VectorF, 1.10, MethodPresicion), n, Precision);

		in.close();

	}

}
