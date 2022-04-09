using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ShrinkingMappingGraf
{
    public partial class Form1 : Form
    {
        public static double g(double x)
        {
            return x + Math.Atan(x) + x / (1 + Math.Pow(x, 2)) - 3;
        }

        public static double f(double x)
        {
            return (3 - Math.Atan(x)) * (1 + Math.Pow(x, 2)) / (2 + Math.Pow(x, 2));
        }

        public static int apriorCount(double x)
        {
            return (int)Math.Round(Math.Log(precision * (1 - alpha) / Math.Abs(x - f(x)), alpha)) + 1;
        }

        public const double alpha = 0.161;
        public const double precision = 0.0001;

        public static double leftBound = -10;
        public static double rightBound = 10;
        public Form1()
        {
            InitializeComponent();

            int count = 0;
            double x = 0;

            while (Math.Abs(x - f(x)) > precision)
            {          
                x = f(x);
                count++;
            }

            richTextBox1.AppendText("Априорная оценка количества итераций:\t" + apriorCount(0) + '\n');
            richTextBox1.AppendText($"Последняя итерация №{count}:\t" + x +'\n');
            richTextBox1.AppendText($"{f(5)}");

            chart1.Series[0].Name = "g(x)";
            chart1.Series[0].Color = Color.Red;
            chart1.Series[0].ChartType = System.Windows.Forms.DataVisualization.Charting.SeriesChartType.Line;

            for (double i = leftBound; i <= rightBound; i++)
                chart1.Series[0].Points.AddXY(i, g(i));
        }
    }
}
