package MainPCG;

import java.math.BigDecimal;
import java.util.Random;
import java.util.Scanner;

public class Gauss {

	static int IterCount = 0;// йнкхвеярбн оепеярюмнбнй ярпнй
	static int Precision = 17;
	static int MatPrecision = 17;

	public static double MaxNormNevSolve(double[][] array, int size, double ApproxValues[], double[] f) {// мюунфдемхе
																											// люйяхлсл-мнплш
																											// мебъгйх
		double Norm[] = VectorMatMult(array, ApproxValues, size);
		Norm = DiffVec(Norm, f, size);
		double result = FindMax(Norm, size);

		return Math.abs(result);
	}

	public static double MaxNormPogrSolve(double[] EcxactValues, double[] ApproxValues, int size) {// мюунфдемхе
																									// люйяхлсл-мнплш
																									// онцпеьмнярх
		double Norm[] = DiffVec(EcxactValues, ApproxValues, size);
		double result = FindMax(Norm, size);

		return Math.abs(result);
	}

	public static double FindMax(double a[], int size) {// люйяхлсл мнплю
		double Max = Math.abs(a[0]);
		int j = 0;
		for (int i = 0; i < size; i++)
			if (Math.abs(a[i]) > Max) {
				Max = Math.abs(a[i]);
				j = i;
			}

		return a[j];
	}

	public static double[] DiffVec(double One[], double Two[], int size) {// пюгмнярэ бейрнпнб
		double NewVec[] = new double[size];

		for (int i = 0; i < size; i++)
			NewVec[i] = One[i] - Two[i];

		return NewVec;
	}

	public static double[][] InverseMatSolve(double arrayI[][], int size) {// мюунфдемхе напюрмни
																			// люрпхжш

		double NewMat[][] = new double[size][size * 2];

		for (int i = 0; i < size; i++)
			for (int j = 0; j < size * 2; j++)
				if (j < size)
					NewMat[i][j] = arrayI[i][j];
				else {
					if (i + size == j)
						NewMat[i][j] = 1;
					else
						NewMat[i][j] = 0;
				}

		for (int i = 0; i < size; i++)
			ZeroDown(NewMat, size, i, size);

		// ViewMat(NewMat, size, size);

		for (int i = size - 1; i >= 0; i--)
			ZeroUp(NewMat, size, i, size);

		// ViewMat(NewMat, size, size);

		for (int i = 0; i < size; i++) {
			double coof = NewMat[i][i];
			if (coof == 0) {
				System.out.println("Unable to complete task due to division by zero!");
			}
			for (int j = 0; j < size * 2; j++)
				NewMat[i][j] /= coof;
		}

		// ViewMat(NewMat, size, size);

		double Mat[][] = new double[size][size];

		for (int i = 0; i < size; i++)
			for (int j = size; j < size * 2; j++)
				Mat[i][j - size] = NewMat[i][j];

		return Mat;
	}

	public static void PrintVec(double array[], int size, int Prec) {// бшбнд бейрнпю я гюдюммни рнвмнярэч
		for (int i = 0; i < size; i++) {
			System.out.print(BigDecimal.valueOf(array[i]).setScale(Prec, BigDecimal.ROUND_HALF_UP));
			System.out.print('\n');
		}
	}

	public static double[][] MatMultiplication(double Mat[][], double InverseMat[][], int size) {// опнхгбедемхе
																									// напюрмни
																									// люрпхжш мю
																									// хяундмсч

		double CheckMat[][] = new double[size][size];

		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				CheckMat[i][j] = 0;

		for (int i = 0; i < size; ++i)
			for (int j = 0; j < size; ++j)
				for (int k = 0; k < size; ++k)
					CheckMat[i][j] += Mat[i][k] * InverseMat[k][j];

		return CheckMat;

	}

	public static double[] VectorMatMult(double arrayE[][], double ExactValue[], int size) {// слмнфемхе люрпхжш мю
																							// бейрнп
		double VectorF[] = new double[size];

		for (int i = 0; i < size; i++)
			for (int j = 0; j < size; j++)
				VectorF[i] += arrayE[i][j] * ExactValue[j];

		return VectorF;
	}

	public static double[] ApproxSolve(double arrayS[][], int size) {// мюунфдемхе опхакхф╗ммнцн пеьемхъ

		double Solve[] = new double[size];

		for (int i = 0; i < size; i++)
			Solve[i] = 1;

		for (int l = size - 1; l >= 0; l--) {
			double temp = arrayS[l][size];
			for (int k = size - 1; k >= 0; k--) {
				if (k != l)
					temp -= arrayS[l][k] * Solve[k];
			}
			if (arrayS[l][l] == 0) {
				System.out.println("Unable to complete task due to division by zero!");
			}
			Solve[l] = temp / arrayS[l][l];

		}

		return Solve;
	}

	public static double DetA(double arrayD[][], int size) {// мюунфдемхе нопедекхрекъ люрпхжш

		double DetSum = 1;
		for (int i = 0; i < size; i++)
			DetSum *= arrayD[i][i];

		DetSum *= Math.pow(-1, IterCount);

		return DetSum;
	}

	public static void ViewMat(double arrayV[][], int size, int dop, int MatPrec) {// бшбнд люрпхжш

		System.out.println();

		for (int i = 0; i < size; i++) {
			for (int j = 0; j < size + dop; j++) {
				if (j != size) {
					System.out.print(BigDecimal.valueOf(arrayV[i][j]).setScale(MatPrec, BigDecimal.ROUND_HALF_UP));
					System.out.print('\t');
				} else
					System.out.print("| " + BigDecimal.valueOf(arrayV[i][j]).setScale(MatPrec, BigDecimal.ROUND_HALF_UP)
							+ "    ");
			}
			System.out.println();
		}
	}

	public static void ZeroDown(double arrayS[][], int size, int up, int dop) {// опхбедемхе люрпхжш й бепумеи
																				// рпесцнкэмни

		if (up + 1 == size)
			return;

		double coof = arrayS[up][up];
		if (coof == 0) {
			System.out.println("Unable to complete task due to division by zero!");
		}

		for (int i = up + 1; i < size; i++) {
			double first = arrayS[i][up];
			for (int j = up; j < size + dop; j++) {
				arrayS[i][j] -= arrayS[up][j] / coof * first;
			}
		}
	}

	public static void ZeroUp(double arrayS[][], int size, int down, int dop) {// опхбедемхе люрпхжш й мхфмеи
																				// рпесцнкэмни

		if (down - 1 == -1)
			return;

		double coof = arrayS[down][down];
		if (coof == 0) {
			System.out.println("Unable to complete task due to division by zero!");
		}

		for (int i = down - 1; i >= 0; i--) {
			double first = arrayS[i][down];
			for (int j = down; j < size + dop; j++) {
				arrayS[i][j] -= arrayS[down][j] / coof * first;
			}
		}
	}

	public static void StrSwitch(double arrayS[][], int size, int up, int maxstr) {// оепеярюмнбйю ярпнй
		if (up == maxstr)
			return;

		double temp[][] = new double[size][size + 1];

		for (int i = 0; i < size; i++)
			for (int j = 0; j < size + 1; j++)
				temp[i][j] = arrayS[i][j];

		for (int i = 0; i < size + 1; i++) {
			arrayS[up][i] = temp[maxstr][i];
			arrayS[maxstr][i] = temp[up][i];
		}

		IterCount++;
	}

	public static void CollSolve(double arrayI[][], int size) {// лернд цюсяяю я бшанпнл цкюбмнцн щкелемрю он ярнкажс

		for (int j = 0; j < size - 1; j++) {

			double max = arrayI[j][j];
			int maxstr = j;

			for (int i = j; i < size; i++) {
				if (Math.abs(arrayI[i][j]) >= max) {
					maxstr = i;
					max = Math.abs(arrayI[i][j]);
				}
			}

			StrSwitch(arrayI, size, j, maxstr);
			// ViewMat(arrayI, size, 1);
			ZeroDown(arrayI, size, j, 1);
			// ViewMat(arrayI, size, 1);

		}
	}

	public static void main(String[] args) {

		Scanner in = new Scanner(System.in);

		System.out.print("Enter the dimension of the matrix: ");

		int n = in.nextInt();
		if (n <= 1) {
			System.out.println("Invalid n value (require: n > 1)");
			in.close();
			return;
		}

		double[][] a = new double[n][n + 1]; // хяундмюъ люрпхжю
		double[][] InverseMat = new double[n][n]; // напюрмюъ люрпхжю
		double[][] OneMat = new double[n][n];
		double[] ExactValue = new double[n]; // рнвмне пеьемхе
		double[] ApproxValue = new double[n]; // опхакхф╗ммне пеьемхе
		double[] VectorF = new double[n]; // бейрнп F

		double DetSum;
		Random rnd = new Random();
		rnd.setSeed(System.currentTimeMillis());

		int left, right;
		System.out.println("Enter the range of filling the matrix [a, b]: ");
		System.out.print("a = ");
		left = in.nextInt();

		System.out.print("b = ");
		right = in.nextInt();

		if (left > right) {
			System.out.println("Incorrect range!");
			in.close();
			return;
		}

		System.out.println("Input Matrix A: ");

		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				a[i][j] = Math.round((rnd.nextDouble() + (left + rnd.nextInt(right - left))) * 100.00) / 100.00;
				InverseMat[i][j] = a[i][j];
				OneMat[i][j] = a[i][j];
				System.out.print(BigDecimal.valueOf(a[i][j]).setScale(2, BigDecimal.ROUND_HALF_UP));
				System.out.print('\t');
			}
			System.out.print('\n');
		}

		System.out.println("\n\nExacts Values X: ");
		for (int i = 0; i < n; i++)
			ExactValue[i] = Math.round((rnd.nextDouble() + (left + rnd.nextInt(right - left))) * 100.00) / 100.00;

		PrintVec(ExactValue, n, 2);

		System.out.println("\n\nVector F Values: ");
		VectorF = VectorMatMult(a, ExactValue, n);
		PrintVec(VectorF, n, Precision);

		for (int i = 0; i < n; i++)
			a[i][n] = VectorF[i];

		// ViewMat(a, n, 1);
		CollSolve(a, n);
		DetSum = DetA(a, n);

		if (DetSum == 0) {
			System.out.println("\n\nDetermenant Value = 0!");
			in.close();
			return;
		}

		System.out.println("\n\nDetermenant Value: ");
		System.out.print(BigDecimal.valueOf(DetSum).setScale(2, BigDecimal.ROUND_HALF_UP));

		System.out.println("\n\nApprox Values X: ");
		ApproxValue = ApproxSolve(a, n);
		PrintVec(ApproxValue, n, Precision);
		InverseMat = InverseMatSolve(InverseMat, n);

		System.out.println("\n\nInvesre Matrix: ");
		ViewMat(InverseMat, n, 0, MatPrecision);

		System.out.println("\n\n Maximum residual rate: ");
		System.out.println(MaxNormNevSolve(OneMat, n, ApproxValue, VectorF));

		System.out.println("\n\n Maximum error rate: ");
		System.out.println(MaxNormPogrSolve(ExactValue, ApproxValue, n));

		System.out.println("\n\n A*A^(-1): ");
		OneMat = MatMultiplication(OneMat, InverseMat, n);
		ViewMat(OneMat, n, 0, MatPrecision);

		in.close();
	}

}
