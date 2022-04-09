using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Billiards
{
    public partial class Form1 : Form
    {
        Random rnd;
        Graphics g;
        private bool isShow = true;
        private bool Pause = false;

        private Bitmap bitmap;
        private Pen pen = new Pen(Brushes.Green, 3f) { DashStyle = System.Drawing.Drawing2D.DashStyle.Dash };
        private Pen ballPen = new Pen(Brushes.Black, 2f);
        private Pen clearPen = new Pen(Brushes.White, 2f);
        private SolidBrush clearBrush = new SolidBrush(Color.White);

        private Thread[] Threads;

        private List<Ball> balls = new List<Ball>();
        private int BallRadius = 10;
        private int BallMass = 14;

        private List<Color> colors = new List<Color>() { Color.Red, Color.Black, Color.Blue, Color.Orange };

        private bool checkThreads()
        {
            if (Threads != null)
                foreach (Thread tr in Threads)
                    if (tr.IsAlive)
                        return false;
            return true;
        }

        private void PauseBalls()
        {
            Pause = true;
        }

        private void ResumeBalls()
        {
            Pause = false;
        }

        private void AbortThreads()
        {
            foreach (Thread tr in Threads)
                tr.Abort();
            Threads = null;
            balls.Clear();
        }

        private void drawBall(object objBall)
        {
            Ball ball = (Ball)objBall;
                  
            while (ball.force != 0)
            {
                if (!Pause)
                {
                    Thread.Sleep(1);
                    drawPictureBox(ball, true);
                    ball.ballMove(0.001f, pictureBox1.Height, pictureBox1.Width); 
                    drawPictureBox(ball);
                }
            }

        }

        private void drawPictureBox(Ball ball, bool clear = false)
        {
            this.Invoke((MethodInvoker)delegate
            {
                if (clear == false)
                {
                    g.DrawEllipse(ballPen, ball.currentX, ball.currentY, BallRadius, BallRadius);
                    g.FillEllipse(ball.Brush, ball.currentX, ball.currentY, BallRadius, BallRadius);
                }
                else
                {
                    g.DrawEllipse(clearPen, ball.currentX, ball.currentY, BallRadius, BallRadius);
                    g.FillEllipse(clearBrush, ball.currentX, ball.currentY, BallRadius, BallRadius);
                }

                pictureBox1.Image = bitmap;
            });
        }
        private void initBalls()
        {
            rnd = new Random();
            int count = rnd.Next(1, 15);
            Threads = new Thread[count];

            for (int i = 0; i < count; i++)
            {
                Ball ball = new Ball(rnd.Next(BallRadius + 10, bitmap.Width - 25 - BallRadius), rnd.Next(BallRadius + 10, bitmap.Height - 25 - BallRadius),
                    BallRadius, colors[rnd.Next(0, colors.Count)], (float)rnd.NextDouble() * 10, (float)rnd.NextDouble() * 10, 45f, BallMass);
                balls.Add(ball);
                Thread newThread = new Thread(new ParameterizedThreadStart(drawBall));
                Threads[i] = newThread;
                newThread.Start(ball);
            }
        }

        public Form1()
        {
            InitializeComponent();
            bitmap = new Bitmap(pictureBox1.Width, pictureBox1.Height);

            g = Graphics.FromImage(bitmap);
            g.Clear(Color.White);
            g.DrawRectangle(pen, 10, 10, pictureBox1.Width - 20, pictureBox1.Height - 20);
            pictureBox1.Image = bitmap;
            pictureBox1.Invalidate();
        }

        private void pictureBox1_Click(object sender, EventArgs e)
        {

        }

        private void StartButton_Click(object sender, EventArgs e)
        {
            StartButton.Enabled = false;
            ResetButton.Enabled = true;
            PauseButton.Enabled = true;

            timer1.Interval = 2;
            timer1.Enabled = true;
            timer1.Start();
            initBalls();
            isShow = true;
        }

        private void ResetButton_Click(object sender, EventArgs e)
        {
            ResetButton.Enabled = false;
            PauseButton.Enabled = false;
            ContinueButton.Enabled = false;

            bool trig = false;
            if (isShow == true)
                trig = true;

            isShow = false;
            AbortThreads();
            g.Clear(Color.White);

            if (trig)
                MessageBox.Show("All threads are stopped!", "Reset", MessageBoxButtons.OK);
            StartButton.Enabled = true; 
        }

        private void PauseButton_Click(object sender, EventArgs e)
        {
            PauseButton.Enabled = false;
            ResetButton.Enabled = false;
            ContinueButton.Enabled = true;
            PauseBalls();
        }

        private void ContinueButton_Click(object sender, EventArgs e)
        {
            ContinueButton.Enabled = false;
            ResetButton.Enabled = true;
            PauseButton.Enabled = true;
            ResumeBalls();
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            
        }

        private void timer1_Tick_1(object sender, EventArgs e)
        {
            g.DrawRectangle(pen, 10, 10, pictureBox1.Width - 20, pictureBox1.Height - 20);

            foreach (Ball el in balls)
                if (el.force == 0)
                    drawPictureBox(el);
                

            pictureBox1.Image = bitmap;

            if (checkThreads() && isShow)
            {
                isShow = false;
                MessageBox.Show("All threads are complete!", "Alert", MessageBoxButtons.OK);
            }
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (Threads != null)
                AbortThreads();
        }
    }
}
