using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.IO;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CryptoGraf
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }


        private void AboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Задача:\n" +
"Копирование с шифрованием бинарного входного файла в выбранный каталог " +
"(отличный от исходного) блоками по 512 байт фиксированным ключом длиной 128 байт.\n" +
"Ключ создать случайным образом и выводить в файл по команде пользователя.\n" +
"Для выбора файла входных данных " +
"использовать стандартный диалог.\n" + "\n" + "Разработчик:\n" + "Возовиков Никита Александрович\n" + "БГУ ФПМИ 1 курс 10 группа  \n", "About...", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        string inputname;
        string keyinput;

        enum Method { Encrypt=1,Decrypt=2,None=0};

        Method swi = 0;

        byte[] KEY = new byte[128];
        byte ProgramKEY = 228;
        byte[] BUF = new byte[512];
        private void OpenToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                inputname = openFileDialog1.FileName;
                flowLayoutPanel1.Visible = true;              
                label2.Visible = false;
                button2.Visible = false;
                label1.Text = "File directory:" + '\n' + inputname;
            }
        }

        private void ExitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show("Are you sure to exit?", Text, MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes)
            {
                
                Close();
            }
        }

        private void SaveFileDialog1_FileOk(object sender, CancelEventArgs e)
        {
          
        }

        private void Button1_Click(object sender, EventArgs e)
        {
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                if (swi == Method.Encrypt)
                {
                    var rand = new Random();
                    rand.NextBytes(KEY);
                    using (FileStream input = new FileStream(inputname, FileMode.Open, FileAccess.Read))
                    {
                        using (FileStream output = new FileStream(saveFileDialog1.FileName, FileMode.Create, FileAccess.Write))
                        {
                            int nread;
                            while ((nread = input.Read(BUF, 0, 512)) > 0)
                            {
                                int g = 0;
                                for (int i = 0; i < BUF.Length; i++)
                                {
                                    if (g < KEY.Length)
                                    {
                                        BUF[i] += KEY[g];
                                        BUF[i] -= ProgramKEY;
                                        g++;
                                    }
                                    else
                                        g = 0;
                                }
                                output.Write(BUF, 0, nread);
                            }
                        }
                    }

                    label2.Visible = true;
                    button2.Visible = true;
                    label2.Text = "Your unique key:\n";

                    foreach (byte el in KEY)
                        codelabel.Text += el;

                    button1.Enabled = false;
                }
                else
                    if (swi == Method.Decrypt)
                {
                    using (FileStream input = new FileStream(keyinput, FileMode.Open, FileAccess.Read))
                    {
                        input.Read(KEY, 0, 128);
                    }

                    using (FileStream input = new FileStream(inputname, FileMode.Open, FileAccess.Read))
                    {
                        using (FileStream output = new FileStream(saveFileDialog1.FileName, FileMode.Create, FileAccess.Write))
                        {
                            int nread;
                            while ((nread = input.Read(BUF, 0, 512)) > 0)
                            {
                                int g = 0;
                                for (int i = 0; i < BUF.Length; i++)
                                {
                                    if (g < KEY.Length)
                                    {
                                        BUF[i] += ProgramKEY;
                                        BUF[i] -= KEY[g];
                                        g++;
                                    }
                                    else
                                        g = 0;
                                }
                                output.Write(BUF, 0, nread);
                            }
                        }
                    }
                    keydirectory.Visible = false;
                    flowLayoutPanel1.Visible = false;
                }
                else
                {
                    MessageBox.Show("No method selected!", Text, MessageBoxButtons.OK, MessageBoxIcon.Warning);
                    return;
                }
            }
        }

        private void Button2_Click(object sender, EventArgs e)
        {
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                using (FileStream output = new FileStream(saveFileDialog1.FileName, FileMode.Create, FileAccess.Write))
                {
                    output.Write(KEY, 0, KEY.Length);
                }
            }           
            codelabel.Visible = false;
            flowLayoutPanel1.Visible = false;
        }

        private void Encrypt_CheckedChanged_1(object sender, EventArgs e)
        {
            swi = Method.Encrypt;
            openkey.Visible = false;
            button1.Enabled = true;
        }

        private void Decrypt_CheckedChanged_1(object sender, EventArgs e)
        {
            swi = Method.Decrypt;
            openkey.Visible = true;
            button1.Enabled = false;
        }

        private void Openkey_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                keyinput = openFileDialog1.FileName;
                keydirectory.Visible = true;
                keydirectory.Text = "File directory:" + '\n' + keyinput;
                button1.Enabled = true;
            }
        }
    }
}
