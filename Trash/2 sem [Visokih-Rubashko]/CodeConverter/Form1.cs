using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.IO;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace CodeConverter
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        string input;
        private void OpenToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK) 
            {                              
                input = openFileDialog1.FileName;                              
                flowLayoutPanel1.Visible = true;
                label1.Text = "File directory:" + '\n' + input;
            }
        }

        private void AboutToolStripMenuItem_Click(object sender, EventArgs e)
        {
            MessageBox.Show("Задача:\n" +
"Перекодировка текстового файла, пользователь выбирает несовпадающие кодировки "+
"входного и выходного файлов.\n" +
"Допустимые кодировки: koi8 - r, windows - 1251, utf - 8, ibm - 866\n" +
"Для выбора файла входных данных " +
"использовать стандартный диалог.\n" + "\n" + "Разработчик:\n" + "Возовиков Никита Александрович\n" + "БГУ ФПМИ 1 курс 10 группа  \n", "About...", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        private void Button1_Click(object sender, EventArgs e)
        {
            if (OldCode == 0)
            {
                MessageBox.Show("No input file encoding selected!", Text, MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            if (NewCode == 0)
            {
                MessageBox.Show("No output file encoding selected!", Text, MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            if (saveFileDialog1.ShowDialog()==DialogResult.OK)
            {
                
                    switch (NewCode)
                    {
                        case codes.ibm:
                        File.WriteAllText(saveFileDialog1.FileName, File.ReadAllText(input, Encoding.GetEncoding((Int32)OldCode)), Encoding.GetEncoding((Int32)NewCode));                    
                            break;
                        case codes.koi:
                        File.WriteAllText(saveFileDialog1.FileName, File.ReadAllText(input, Encoding.GetEncoding((Int32)OldCode)), Encoding.GetEncoding((Int32)NewCode));
                        break;
                        case codes.utf:
                        File.WriteAllText(saveFileDialog1.FileName, File.ReadAllText(input, Encoding.GetEncoding((Int32)OldCode)), Encoding.GetEncoding((Int32)NewCode));
                        break;
                        case codes.win:
                        File.WriteAllText(saveFileDialog1.FileName, File.ReadAllText(input, Encoding.GetEncoding((Int32)OldCode)), Encoding.GetEncoding((Int32)NewCode));
                        break;
                        default:
                            break;
                    }            
            }
            flowLayoutPanel1.Visible = false;
        }

        private void ExitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show("Are you sure to exit?", Text, MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes)
                Close();
        }

        enum codes { ibm=866,koi= 20866, utf=65001,win=1251,empty=0};
        codes NewCode = 0;
        codes OldCode = 0;
        private void Ibm_CheckedChanged(object sender, EventArgs e)
        {
            NewCode = codes.ibm;
        }
        private void Koi_CheckedChanged(object sender, EventArgs e)
        {
            NewCode = codes.koi;
        }
        private void Utf_CheckedChanged(object sender, EventArgs e)
        {
            NewCode = codes.utf;
        }
        private void windowscode(object sender, EventArgs e)
        {
            NewCode = codes.win;
        }


        private void Oldibm_CheckedChanged(object sender, EventArgs e)
        {
           OldCode = codes.ibm;
        }
        private void Oldkoi_CheckedChanged(object sender, EventArgs e)
        {
            OldCode = codes.koi;
        }
        private void Oldutf_CheckedChanged(object sender, EventArgs e)
        {
            OldCode = codes.utf;
        }
        private void Oldwin_CheckedChanged(object sender, EventArgs e)
        {
            OldCode = codes.win;
        }
    }
}
