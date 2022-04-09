using System;

namespace ShrinkingMappingGraf
{
    class Task2
    {
        private static double[,] matrix = { { -1.1, 0, 0.1 }, 
                                           { -0.1, 1.4, 0 }, 
                                           { -0.2, 0.4, 0.9 } };
        private static double[,] x = { { 0, 0, 0 } };
        private static double[,] y = { { 0, 1, -1 } };

        private const double precision = 0.001;
        public static double[,] transMat(double[,] matrix, double[,] y)
        { //ПРИВЕДЕНИЕ СИСТЕМЫ К СПЕЦИАЛЬНОМУ ВИДУ
            int rows = matrix.GetUpperBound(0) + 1;
            int columns = matrix.Length / rows;

            for (int i = 0; i < rows; i++)
                if (matrix[i, i] < 0)
                    matrix[i, i] += 1;
                else
                {
                    for (int j = 0; j < columns; j++)
                    {
                        matrix[i, j] *= -1;
                        y[0, j] *= -1;
                    }
                    matrix[i, i] += 1;
                }
                
            return matrix;
        }

        public static double[,] MatrixOperations(double[,] one, double[,] two, bool addition = true)
        { // СУММА/РАЗНОСТЬ МАТРИЦ
            int sign;
            if (addition == true)
                sign = 1;
            else
                sign = -1;

            int rows = one.GetUpperBound(0) + 1;
            int columns = one.Length / rows;

            double[,] newMat = new double[rows, columns];

            for (int i = 0; i < rows; i++)
                for (int j = 0; j < columns; j++)
                    newMat[i, j] = one[i, j] + sign * two[i, j];

            return newMat;
        }

        public static double[,] MatVecMultiplication(double[,] matrix, double[,] Vec)
        { // УМНОЖЕНИЕ МАТРИЦЫ НА ВЕКТОР
            int rows = matrix.GetUpperBound(0) + 1;
            int columns = matrix.Length / rows;

            double[,] newVec = new double[1, Vec.Length];
            for (int i = 0; i < Vec.Length; i++)
                newVec[0, i] = 0;

            for (int i = 0; i < rows; i++)
                for (int j = 0; j < columns; j++)
                    newVec[0, i] += matrix[i, j] * Vec[0, j];

            return newVec;
        }
        public static double matrixNorm(double[,] matrix)
        { //НОРМА МАТРИЦЫ
            int rows = matrix.GetUpperBound(0) + 1;
            int columns = matrix.Length / rows;
            double max = 0;

            for (int i = 0; i < rows; i++)
            {
                double temp = 0;
                for (int j = 0; j < columns; j++)
                    temp += Math.Abs(matrix[i, j]);
                if (temp > max)
                    max = temp;
            }

            return max;
        }

        public static int apriorCount(double alpha)
        {
            return (int)Math.Round(Math.Log(precision * (1 - alpha) / matrixNorm(MatrixOperations(x, y, false)), alpha)) + 1;
        }
        static void Main()
        {
            int count = 0;

            matrix = transMat(matrix, y);
            double alpha = matrixNorm(matrix);
            int apr = apriorCount(alpha);

            double[,] x0 = MatrixOperations(MatVecMultiplication(matrix, x), y);

            while (matrixNorm(MatrixOperations(x, x0, false)) > precision)
            {
                x0 = x;
                x = MatrixOperations(MatVecMultiplication(matrix, x), y);
                count++;
            }

            Console.WriteLine($"Коэффициент сжатия:\t{alpha}");
            Console.Write($"Последняя итерация №{count}:\t{{ ");

            foreach (double el in x)
                Console.Write(el.ToString() + ' ');
            Console.Write("}\n'");

            Console.WriteLine($"Априорная оценка количества итераций:\t{apr}\n");
        }
    }
}
