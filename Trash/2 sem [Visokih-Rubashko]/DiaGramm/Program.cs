using System;
using System.Collections.Generic;
using System.Linq;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.Drawing;

namespace DiaGramm
{
    static class Program
    {
        [STAThread]
        static void Main()
        {
            try
            {
                Application.EnableVisualStyles();
                Application.Run(new AppWindow("DiaGram", 600, 1000));
            }
            catch (Exception e)
            {
                MessageBox.Show("Error: " + e.Message, "DiaGram", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
    }

    class AppWindow : Form
    {
        DATA exsp = new DATA();
        Random Rand;
        Bitmap Bmp;
        Graphics graf;
       
        private class DATA
        {
            public string Title { get; set; } = null;
            public Dictionary<string, int> one;
        }

        private void AppWindow_FormClosing(Object sender, FormClosingEventArgs e)
        {
            if (MessageBox.Show("Are you sure to exit?", Text, MessageBoxButtons.YesNo, MessageBoxIcon.Question) != DialogResult.Yes)       
                e.Cancel = true;
        }
        

        public AppWindow(string title, int width, int height)
        {
            Rand = new Random();
            Bmp = new Bitmap(width, height);
            graf = Graphics.FromImage(Bmp);
            

            FormClosing += AppWindow_FormClosing;
            

            Text = title;
            if (width > 0) Width = width;
            if (height > 0) Height = height;

            MinimumSize = new Size(Width, Height);
            MaximumSize = MinimumSize;

            Paint += AppWindow_Paint;
            CenterToScreen();
            BuildControls();
        }

        private void AppWindow_Paint(object sender, PaintEventArgs el)
        {
            graf.Flush();
            el.Graphics.DrawImage(Bmp, 0, 0, Bmp.Width, Bmp.Height);
        }
        private void BuildControls()
        {
            BuildToolTip();        
            BuildMenu();         
            BuildStatusLine();                
        }
       
        private StatusStrip statusStrip;
        private ToolStripStatusLabel toolStripStatusLabel;
        private void BuildStatusLine()
        {   
            statusStrip = new StatusStrip();
            toolStripStatusLabel = new ToolStripStatusLabel();
          
            statusStrip.SuspendLayout();
            SuspendLayout();

            statusStrip.Items.AddRange(new ToolStripItem[] { toolStripStatusLabel });
            statusStrip.Location = new Point(0, 248);
            statusStrip.Name = "statusStrip";
            statusStrip.Size = new Size(292, 30);
            statusStrip.TabIndex = 0;
            statusStrip.Text = "statusStrip";

            toolStripStatusLabel.BorderSides = 0;
            toolStripStatusLabel.BorderStyle = Border3DStyle.Flat;
            toolStripStatusLabel.IsLink = false;
            toolStripStatusLabel.Name = "toolStripStatusLabel";
            toolStripStatusLabel.Size = new Size(246, 28);

            toolStripStatusLabel.Spring = true;
           
            toolStripStatusLabel.Text = "";
            toolStripStatusLabel.Alignment = ToolStripItemAlignment.Left;
            toolStripStatusLabel.TextAlign = ContentAlignment.TopLeft;

            Controls.Add(statusStrip);
         
            statusStrip.ResumeLayout(false);
            statusStrip.PerformLayout();

            ResumeLayout(false);
            PerformLayout();
        }

        private MenuStrip mnuMain = new MenuStrip();

        private ToolStripMenuItem mnuFile = new ToolStripMenuItem();
        private ToolStripMenuItem mnuFileOpenFile = new ToolStripMenuItem();
        private ToolStripMenuItem mnuFileExit = new ToolStripMenuItem();

        private ToolStripMenuItem mnuView = new ToolStripMenuItem();
        private ToolStripMenuItem mnuColors = new ToolStripMenuItem();

        private ToolStripMenuItem mnuHelp = new ToolStripMenuItem();
        private ToolStripMenuItem mnuHelpAbout = new ToolStripMenuItem();

        private void BuildMenu()
        {
            mnuFile.Text = "&File";
            mnuMain.Items.Add(mnuFile);

            mnuView.Text = "&View";
            mnuMain.Items.Add(mnuView);

            mnuHelp.Text = "&Help";
            mnuMain.Items.Add(mnuHelp);
            
            mnuFileOpenFile.Text = "&Open";
            mnuFile.DropDownItems.Add(mnuFileOpenFile);
            mnuFileOpenFile.Click += (o, s) => OnFileOpen();
            mnuFileOpenFile.MouseEnter += (o, s) => toolStripStatusLabel.Text = "Open an existing file";
            mnuFileOpenFile.MouseLeave += (o, s) => toolStripStatusLabel.Text = "";

            mnuFile.DropDownItems.Add(new ToolStripSeparator());
          
            mnuFileExit.Text = "E&xit";
            mnuFile.DropDownItems.Add(mnuFileExit);
            mnuFileExit.Click += (o, s) => Application.Exit();
            mnuFileExit.MouseEnter += (o, s) => toolStripStatusLabel.Text = "Exit application...";
            mnuFileExit.MouseLeave += (o, s) => toolStripStatusLabel.Text = "";

            mnuColors.Text = "Change color";
            mnuView.DropDownItems.Add(mnuColors);     
            mnuColors.Click += (o, s) => SelectColors();
            mnuColors.MouseEnter += (o, s) => toolStripStatusLabel.Text = "Change color";
            mnuColors.MouseLeave += (o, s) => toolStripStatusLabel.Text = "";

            mnuHelpAbout.Text = "&About...";
            mnuHelp.DropDownItems.Add(mnuHelpAbout);

            mnuHelpAbout.Click += (o, s) => OnHelpAbout();
            mnuHelpAbout.MouseEnter += (o, s) => toolStripStatusLabel.Text = "Show information about " + " the programm...";
            mnuHelpAbout.MouseLeave += (o, s) => toolStripStatusLabel.Text = "";
          
            Controls.Add(mnuMain);
            MainMenuStrip = mnuMain;
           
        }
      
     
        ToolTip toolTip = new ToolTip();

        private void BuildToolTip()
        {
            toolTip.AutoPopDelay = 5000;
            toolTip.InitialDelay = 1000;
            toolTip.ReshowDelay = 500;
            toolTip.ShowAlways = true;
        }

        private void OnFileOpen()
        {
            try
            {
                using (OpenFileDialog openFileDialog = new OpenFileDialog())
                {
                    openFileDialog.InitialDirectory = Environment.GetFolderPath(Environment.SpecialFolder.Personal);
                    openFileDialog.Filter = "Text file (*.txt) |*.txt|All files (*.*) |*.*";
                    openFileDialog.FilterIndex = 0;
                    openFileDialog.DefaultExt = "txt";
                    openFileDialog.FileName = "*.txt";
                    openFileDialog.RestoreDirectory = true;
                    openFileDialog.Multiselect = false;

                    if (openFileDialog.ShowDialog() == DialogResult.OK)
                    {
                        StreamReader input = new StreamReader(openFileDialog.FileName, System.Text.Encoding.UTF8);

                        int count = 0;

                        while (input.ReadLine() != null)
                            count++;

                        input.Close();
                        input = new StreamReader(openFileDialog.FileName, System.Text.Encoding.UTF8);

                        if (count == 1 || count == 0)
                            throw new ArgumentException();

                        count--;

                        exsp = new DATA();
                        exsp.one = new Dictionary<string, int>(count);

                        if ((exsp.Title = input.ReadLine()) == null)
                            throw new ArgumentException();

                        string str;

                        while ((str = input.ReadLine()) != null)
                        {
                            string key = string.Empty, val = string.Empty;
                            int i = 0;
                            for (; i < str.Length; i++)
                                if (str[i] != ' ')
                                    val += str[i];
                                else
                                    break;
                            for (i++; i < str.Length; i++)
                                key += str[i];

                            if (Int32.Parse(val) != 0)
                                exsp.one.Add(key, Int32.Parse(val));
                            else
                                throw new ArgumentException();
                        }

                        DrowDiagram(exsp);

                        input.Close();
                    }
                }
            }
            catch (Exception e)
            {
                MessageBox.Show("Error: " + e.Message, "DiaGram", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void SelectColors()
        {
            try
            {
                if (exsp.Title == null)
                    throw new ArgumentNullException();
                else
                    DrowDiagram(exsp);
            }
            catch (Exception e)
            {
                MessageBox.Show("Error: " + e.Message, "DiaGram", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }
        private void OnHelpAbout()
        {
            MessageBox.Show("Задача:\n" +
"Постройте диаграмму опроса в сети, " +
"отображающую процентное соотношение " +
"проголосовавших.\n" +
"Входные данные хранятся в текстовом файле.\n" +
"Первая строка файла содержит наименование " +
"опроса.\nКаждая последующая строка файла " +
"содержит количество проголосовавших, затем, через" +
"пробел и до конца строки текст, соответствующий " +
"опции опроса. " +
"Для выбора файла входных данных " +
"использовать стандартный диалог.\n" + "\n" + "Разработчик:\n" + "Возовиков Никита Александрович\n" + "БГУ ФПМИ 1 курс 10 группа  \n", "About...", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }


        private void DrowDiagram(DATA P)
        {

            Point point = new Point(ClientSize.Width/16, 40);
            Brush br=new SolidBrush(Color.FromArgb(0,0,0));
            Font font = new Font(FontFamily.GenericSerif, 20, FontStyle.Regular, GraphicsUnit.Point);
            Pen pen = new Pen(Color.FromArgb(0, 0, 0),2f);

            graf.DrawString(P.Title, font, br, point, StringFormat.GenericDefault);

            float perval = 0;

            foreach (int el in P.one.Values)
                perval += el;
           

            float tempaim = 0;

            int Count = P.one.Count;
            List<string> list=new List<string>(Count);
            foreach (string el in P.one.Keys)
                list.Add(el);

            int g = 2;
          
            float x = 584 / 8;
            float y = 584 / 8;

            float x1 = 6 * 584 / 8;
            float y1 = 6 * 584 / 8;

            foreach (int el in P.one.Values)
            {
                float aim = el * 100 / perval * 3.6f;
                
                Brush brr = new SolidBrush(Color.FromArgb(Rand.Next(0, 0xFF), Rand.Next(0, 0xFF), Rand.Next(0, 0xFF)));

                if (g - 2 != Count)
                {
                    graf.DrawPie(pen, x, y, x1, y1, tempaim, aim);
                    graf.FillPie(brr, x, y, x1, y1, tempaim, aim);
                }
                else
                {
                    graf.DrawPie(pen, x, y, x1, y1, 0, -aim);
                    graf.FillPie(brr, x, y, x1, y1, 0, -aim);
                }

                graf.DrawRectangle(pen, ClientSize.Width / 16 - 20, ClientSize.Height / 2 + g * 30 + 8, 15, 15);
                graf.FillRectangle(brr, ClientSize.Width / 16 - 20, ClientSize.Height / 2 + g * 30 + 8, 15, 15);
                graf.DrawString(list[g - 2] + '(' + Math.Round(aim / 3.6f,2) + '%' + ')', font, br, ClientSize.Width / 16, ClientSize.Height / 2 + g * 30, StringFormat.GenericDefault);

                brr.Dispose();
                tempaim += aim;
                
                g++;
            }

            Refresh();
        }
    }

}
