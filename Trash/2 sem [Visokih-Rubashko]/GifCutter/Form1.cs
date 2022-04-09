using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Drawing.Imaging;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace GifCutter
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        private static string Input;
        private static Image img;
        private void OpenToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                flowLayoutPanel1.Visible = true;
               
                Input = openFileDialog1.FileName;
                pictureBox1.Load(Input);
                img = Image.FromFile(Input);

                H_Num.Maximum = img.Width - 1;
                V_Num.Maximum = img.Height - 1;
            }
        }

        private void ExitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show("Are you sure to exit?", Text, MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes)
                Close();
        }

        private void AboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Задача:\n" +
"Разделение изображения на части.\nПрограмма предлагает выбрать файл изображения, " +
"отображает его в клиентской области окна и спрашивает пользователя на сколько частей "+
"нужно разделить изображение по горизонтали(H) и на сколько частей по вертикали(V).\n"+
"Полученные H * V изображений сохраняются в файлы типа GIF.\n"+
"Для выбора файла входных данных " +
"использовать стандартный диалог.\n" + "\n" + "Разработчик:\n" + "Возовиков Никита Александрович\n" + "БГУ ФПМИ 1 курс 10 группа  \n", "About...", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private async void Button1_Click(object sender, EventArgs e)
        {
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                menuStrip1.Enabled = false;
                flowLayoutPanel2.Enabled = false;

                progressBar1.Visible = true;
                progressBar1.Value = 0;


                int Hor_Val = (int)H_Num.Value;
                int Ver_Val = (int)V_Num.Value;


                progressBar1.Maximum = Hor_Val * Ver_Val;
                System.Windows.Forms.Control.CheckForIllegalCrossThreadCalls = false;
                await Task.Run(() => Cutter(Hor_Val, Ver_Val));


                MessageBox.Show("The picture was successfully cut!", "Success", MessageBoxButtons.OK, MessageBoxIcon.Information);

                menuStrip1.Enabled = true;
                flowLayoutPanel2.Enabled = true;
                progressBar1.Visible = false;
                flowLayoutPanel1.Visible = false;
            }
        }

        private void Cutter(int Hor_Val,int Ver_Val)
        {
            int count = 1;

            for (int i = 1; i <= Hor_Val; i++)
            {
                for (int j = 1; j <= Ver_Val; j++)
                {
                    Rectangle selection = new Rectangle(((img.Width) / Hor_Val) * (i - 1), ((img.Height) / Ver_Val) * (j - 1), ((img.Width) / Hor_Val), ((img.Height) / Ver_Val));
                    Bitmap bmp = img as Bitmap;
                    Bitmap cropBmp = bmp.Clone(selection, bmp.PixelFormat);

                    cropBmp.Save(saveFileDialog1.FileName + '_' + (count++).ToString() + ".gif", ImageFormat.Gif);
                    progressBar1.PerformStep();
                }
            }
        }

    }
}
