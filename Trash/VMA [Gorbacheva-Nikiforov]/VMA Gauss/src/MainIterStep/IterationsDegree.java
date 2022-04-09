package MainIterStep;

import java.util.Random;

import MainIter.Interations;
import MainPCG.Gauss;

public class IterationsDegree {

	static double MethodPresicion = Math.pow(10, -6);
	static int InterationCount = 0;
	static int K = 3;

	static double[] EigenVec_1;
	static double[] EigenVec_2;

	static int left = -3;
	static int right = 3;

	static public double[] DegreeMethod(double[][] Mat, double[] EigenVec, double Precision) { // яреоеммни лернд я
																								// оньюцнбни мнплхпнбйни
																								// бейрнпнб
		int size = EigenVec.length;

		double[] yVecPrev = VecOperDouble(EigenVec, Gauss.FindMax(EigenVec, size), true);
		double[] yVecNext = Interations.CloneVec(yVecPrev);

		double[] LamdaPrev = new double[size];
		double[] LamdaNext = new double[size];

		for (int i = 0; i < size; i++)
			LamdaNext[i] = 0;

		do {

			LamdaPrev = Interations.CloneVec(LamdaNext);

			yVecPrev = Interations.CloneVec(yVecNext);
			yVecNext = Gauss.VectorMatMult(Mat, yVecPrev, size);

			for (int i = 0; i < size; i++)
				LamdaNext[i] = yVecNext[i] / yVecPrev[i];

			yVecNext = VecOperDouble(yVecNext, Gauss.FindMax(yVecNext, size), true);

			InterationCount++;

		} while (Gauss.MaxNormPogrSolve(LamdaNext, LamdaPrev, LamdaNext.length) >= Precision);

		EigenVec_1 = Interations.CloneVec(yVecNext);

		return LamdaNext;

	}

	static public double ScalarMethod(double[][] Mat, double[] EigenVec, double Precision) { // лернд яйюкъпмшу
																								// опнхгбедемхи я
																								// оньюцнбни мнплхпнбйни
																								// бейрнпнб

		int size = EigenVec.length;

		double[] yVecPrev = VecOperDouble(EigenVec, Gauss.FindMax(EigenVec, size), true);
		double[] yVecNext = Interations.CloneVec(yVecPrev);

		double LamdaPrev = 0;
		double LamdaNext = 0;

		do {

			LamdaPrev = LamdaNext;

			yVecPrev = Interations.CloneVec(yVecNext);
			yVecNext = Gauss.VectorMatMult(Mat, yVecPrev, size);

			LamdaNext = VecScalarMult(yVecNext, yVecPrev) / VecScalarMult(yVecPrev, yVecPrev);

			yVecNext = VecOperDouble(yVecNext, Gauss.FindMax(yVecNext, size), true);

			InterationCount++;

		} while (Math.abs(LamdaNext - LamdaPrev) >= Precision);

		EigenVec_2 = Interations.CloneVec(yVecNext);

		return LamdaNext;

	}

	static public double VecScalarMult(double[] one, double[] two) { // яйюкъпмне опнхгбедемхе бейрнпнб

		double value = 0;

		for (int i = 0; i < one.length; i++)
			value += one[i] * two[i];

		return value;

	}

	static public double[] VecOperDouble(double[] Vec, double value, boolean div) { // слмнфемхе/декемхе бейрнпю мю
																					// гмювемхе

		double[] newVec = Interations.CloneVec(Vec);

		if (div == false)
			for (int i = 0; i < Vec.length; i++)
				newVec[i] *= value;
		else
			for (int i = 0; i < Vec.length; i++)
				newVec[i] /= value;

		return newVec;
	}

	static public double[][] MatrixAddition(double[][] one, double[][] two) { // ясллю люрпхж

		double[][] newMat = new double[one.length][one.length];

		for (int i = 0; i < one.length; i++)
			for (int j = 0; j < one.length; j++)
				newMat[i][j] = one[i][j] + two[i][j];

		return newMat;
	}

	static public double[][] MatMultDouble(double[][] array, double value) { // слмнфемхе люрпхжш мю гмювемхе

		double[][] newMat = CloneMat(array);

		for (int i = 0; i < array.length; i++)
			for (int j = 0; j < array.length; j++)
				newMat[i][j] *= value;

		return newMat;
	}

	static public double[][] CloneMat(double[][] array) { // йнохпнбюмхе люрпхжш

		double[][] newMat = new double[array.length][array.length];

		for (int i = 0; i < array.length; i++)
			for (int j = 0; j < array.length; j++)
				newMat[i][j] = array[i][j];

		return newMat;

	}

	static public double[][] getMatrixB() {

		double[][] array = { { 1.342, 0.432, -0.599, 0.202, 0.603, -0.202 },
				{ 0.432, 1.342, 0.256, -0.599, 0.204, 0.304 }, { -0.599, 0.256, 1.342, 0.532, 0.101, 0.506 },
				{ 0.202, -0.599, 0.532, 1.342, 0.106, -0.311 }, { 0.603, 0.204, 0.101, 0.106, 1.342, 0.102 },
				{ -0.202, 0.304, 0.506, -0.311, 0.102, 1.342 } };

		return array;

	}

	static public double[][] getMatrixC() {

		double[][] array = { { 0.05, 0, 0, 0, 0, 0 }, { 0, 0.03, 0, 0, 0, 0 }, { 0, 0, 0.02, 0, 0, 0, },
				{ 0, 0, 0, 0.04, 0, 0 }, { 0, 0, 0, 0, 0.06, 0, }, { 0, 0, 0, 0, 0, 0.07 } };

		return array;

	}

	static public double[][] getMatrixA() {

		return MatrixAddition(getMatrixB(), MatMultDouble(getMatrixC(), K));

	}

	public static void main(String[] args) {
		// TODO Auto-generated method stub

		Random rnd = new Random();
		rnd.setSeed(System.currentTimeMillis());

		double[][] MatA = getMatrixA();

		EigenVec_1 = new double[MatA.length];
		EigenVec_2 = new double[MatA.length];

		double[] Lamda_1 = new double[MatA.length];
		double Lamda_2;

		for (int i = 0; i < EigenVec_1.length; i++)
			EigenVec_1[i] = Math.round((rnd.nextDouble() + (left + rnd.nextInt(right - left))) * 100.00) / 100.00;

		EigenVec_2 = Interations.CloneVec(EigenVec_1);

		Lamda_1 = DegreeMethod(MatA, EigenVec_1, MethodPresicion);

		Gauss.ViewMat(MatA, MatA.length, 0, 3);
		System.out.println();

		System.out.println("Vector y(0): ");
		Gauss.PrintVec(EigenVec_1, EigenVec_1.length, 2);
		System.out.println();

		System.out.println("Degree Method: ");
		System.out.println();

		System.out.println("Eigen Value: ");
		System.out.println(Gauss.FindMax(Lamda_1, Lamda_1.length));
		System.out.println();

		System.out.println("Eigen Vector: ");
		Gauss.PrintVec(EigenVec_1, EigenVec_1.length, 17);
		System.out.println();

		System.out.println("Vector R: ");
		Gauss.PrintVec(
				Gauss.DiffVec(Gauss.VectorMatMult(MatA, EigenVec_1, EigenVec_1.length),
						VecOperDouble(EigenVec_1, Gauss.FindMax(Lamda_1, Lamda_1.length), false), EigenVec_1.length),
				EigenVec_1.length, 17);

		System.out.println("Itarations: ");
		System.out.println(InterationCount);
		InterationCount = 0;

		System.out.println();
		System.out.println();

		Lamda_2 = ScalarMethod(MatA, EigenVec_2, MethodPresicion);

		System.out.println("Scalar Method: ");
		System.out.println();

		System.out.println("Eigen Value: ");
		System.out.println(Lamda_2);
		System.out.println();

		System.out.println("Eigen Vector: ");
		Gauss.PrintVec(EigenVec_2, EigenVec_2.length, 17);
		System.out.println();

		System.out.println("Vector R: ");
		Gauss.PrintVec(Gauss.DiffVec(Gauss.VectorMatMult(MatA, EigenVec_2, EigenVec_2.length),
				VecOperDouble(EigenVec_2, Lamda_2, false), EigenVec_2.length), EigenVec_2.length, 17);
		System.out.println();

		System.out.println("Itarations: ");
		System.out.println(InterationCount);
		InterationCount = 0;

	}

}
