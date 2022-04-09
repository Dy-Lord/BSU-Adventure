using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Windows.Forms.DataVisualization.Charting;

namespace MHA1
{
    public partial class Form1 : Form
    {
        private double leftBound = -5;
        private double rightBound = -1;
        private double h = 0.25;

        private List<double> nodes = new List<double>();
        private List<double> nodes1 = new List<double>();

        public double fun(double x)
        {
            return Math.Exp(2 * x);
        }

        public double interpolFun(double x)
        {
            return summarize(x);
        }
        public double summarize(double x)
        {
            double summ = 0;

            for (int i = 0; i < nodes.Count; i++)
                summ += fun(nodes[i]) * multiplication(x, i, nodes.Count);

            return summ;
        }

        public double multiplication(double x, int i, int n)
        {
            double mult = 1.0;
            for (int j = 0; j < n; j++)
                if (i != j)
                    mult *= ((x - nodes[j]) / (nodes[i] - nodes[j]));
            return mult;
        }
        public void printFun(Series series, List<double> nodes, Func<double ,double> fun)
        {
            foreach(double el in nodes)
                series.Points.AddXY(el, fun(el));
        }

        public void nodesInit(List<double> nodes, double leftBound, double rightBound, double h)
        {
            for (double i = leftBound; i <= rightBound; i += h)
                nodes.Add(i);
        }

        public double mesureError()
        {
            double max = maxAbs(leftBound, rightBound, nodes.Count) * omega(leftBound+0.0013, nodes.Count) / factorial(nodes.Count);
            for (double i = leftBound + 0.001; i < rightBound; i += 0.0013)
                max = Math.Min(max, maxAbs(leftBound, rightBound, nodes.Count) * omega(i, nodes.Count) / factorial(nodes.Count));
            return Math.Abs(max);
        }

        public double maxAbs(double leftBound, double rightBound, int n)
        {
            double max = Math.Abs(derivateExp(n) * fun(leftBound));

            for (double i = leftBound; i <= rightBound; i += 0.0001)
                max = Math.Max(max, derivateExp(nodes.Count) * fun(i));
            return max;
        }

        public double derivateExp(int n)
        {
            return n * 2;
        }

        public double factorial(int n)
        {
            int mult = 1;
            for (int i = 1; i <= n; i++)
                mult *= i;
            return mult;
        }
        
        public double omega(double x,int n)
        {
            double mult = 1;
            for (int i = 0; i < n; i++)
                mult *= (x - nodes[i]);
            return Math.Abs(mult);
        }
        public Form1()
        {
            InitializeComponent();

            chart1.Series[0].Color = Color.Indigo;
            chart1.Series[0].BorderWidth = 2;
            chart1.Series[0].ChartType = SeriesChartType.Line;

            chart1.Series.Add(new Series("Polinom"));
            chart1.Series[1].Color = Color.LightGreen;
            chart1.Series[1].BorderWidth = 2;
            chart1.Series[1].ChartType = SeriesChartType.Line;

          
            nodesInit(nodes1, leftBound, rightBound, 0.001);
            nodesInit(nodes, leftBound, rightBound, h);

            printFun(chart1.Series[0], nodes1, fun);
            printFun(chart1.Series[1], nodes, interpolFun);

            chart1.Series.Add(new Series("Error: " + mesureError().ToString()));
            chart1.Series[2].Color = Color.Red;
        }

        private void chart1_Click(object sender, EventArgs e)
        {

        }
    }
}
