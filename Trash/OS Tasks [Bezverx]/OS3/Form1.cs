using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Threading;

namespace OS3
{
    public partial class Form1 : Form
    {
        private string FolderPath;
        List<Test> Tests = new List<Test>();

        public delegate void TextOut(string text);
        public delegate void ColorTextOut(string text, Color color);
        public TextOut TextDelegate;
        public ColorTextOut ColorTextDelegate;

        public delegate void Reset();
        public Reset ResetDelegate;

        private bool StopCurrentConv = false;
        private Thread mainThread;
        public Form1()
        {
            InitializeComponent();
            TextDelegate = new TextOut(TextBoxOut);
            ColorTextDelegate = new ColorTextOut(ColorTextBoxOut);
            ResetDelegate = new Reset(ResetButtons);
        }

        public void TextBoxOut(string text)
        {
            richTextBox1.AppendText(text);            
        }

        public void ColorTextBoxOut(string text, Color color)
        {
            richTextBox1.SelectionStart = richTextBox1.TextLength;
            richTextBox1.SelectionLength = 0;

            richTextBox1.SelectionColor = color;
            richTextBox1.AppendText(text);
            richTextBox1.SelectionColor = richTextBox1.ForeColor;
        }

        private void ResetButtons()
        {
            StartButton.Enabled = true;
            StopButton.Enabled = false;
            resumeButton.Enabled = false;
        }

        private void SplitFiles(string InputFile, List<string> Files)
        {
            string FileName = InputFile.Split('.')[0];

            foreach(string file in Files)
                if(file.Split('.')[1]=="OUT")
                    if (file.Split('.')[0] == FileName)
                    {
                        Tests.Add(new Test(InputFile, file));
                        break;
                    }
        }

        private bool CheckFiles(string FolderPath)
        {
            List<string> Files = new List<string>(Directory.GetFiles(FolderPath));
            Tests.Clear();

            foreach (string file in Files)
                if (file.Split('.')[1] == "IN")
                    SplitFiles(file, Files);


            foreach (Test ts in Tests)
            {
                Invents.setEvent(this, Invents.Events.Bunner);
                Invents.setEvent(this, Invents.Events.Upload);
                richTextBox1.AppendText($"\t\t{ts.InputFile.Substring(ts.InputFile.LastIndexOf('\\') + 1)}  and  {ts.OutPutFile.Substring(ts.OutPutFile.LastIndexOf('\\') + 1)}\n");
            }

            if (Tests.Count != 0)
                return true;

            return false; 
        }

        private void openToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (folderBrowserDialog1.ShowDialog() == DialogResult.OK)
            {
                StartButton.Enabled = true;
                FolderPath = folderBrowserDialog1.SelectedPath;
                TestDirectoryLabel.Text = FolderPath;

                if (CheckFiles(FolderPath))
                    StartButton.Enabled = true;
                else
                {
                    Invents.setEvent(this, Invents.Events.Bunner);
                    Invents.setEvent(this, Invents.Events.Info);
                    richTextBox1.AppendText("\t Tests files no found!\n");
                }
                
            }
        }

        private void checkConveyor()
        {
            foreach (Test ts in Tests)
            {
                this.Invoke(this.ColorTextDelegate, new Object[] { "\n###################################################\n",Color.Gray });
                Invents.setEvent(this, Invents.Events.Bunner);
                Invents.setEvent(this, Invents.Events.Run);
                this.Invoke(this.TextDelegate, new Object[] {$"\t Test {ts.InputFile.Substring(ts.InputFile.LastIndexOf('\\') + 1)} proccessing!\n" });
                
                ThreadsConveyor conv = new ThreadsConveyor(ts.InputFile, ts.OutPutFile, this);

                while (conv.isWorking())
                {
                    if (StopCurrentConv)
                        conv.stopSolveThread();
                    else
                        conv.resumeSolveThread();
                    Thread.Sleep(1);
                }
            }
            this.Invoke(this.ResetDelegate);
        }
        private void StartButton_Click(object sender, EventArgs e)
        {
            StartButton.Enabled = false;
            StopButton.Enabled = true;

            mainThread = new Thread(checkConveyor);
            mainThread.Start();
        }

        private void StopButton_Click(object sender, EventArgs e)
        {
            resumeButton.Enabled = true;
            StopButton.Enabled = false;

            StopCurrentConv = true;
        }

        private void resumeButton_Click(object sender, EventArgs e)
        {
            resumeButton.Enabled = false;
            StopButton.Enabled = true;
            StopCurrentConv = false;
        }
    }
}
