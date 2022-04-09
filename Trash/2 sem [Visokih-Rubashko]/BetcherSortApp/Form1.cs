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

namespace BetcherSortApp
{
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
        }

        string inputname;

        private void OpenToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                inputname = openFileDialog1.FileName;
                flowLayoutPanel1.Visible = true;
                button2.Enabled = false;
                button1.Enabled = true;
                up.Checked = false;
                down.Checked = false;
                CHLZ = MTH.emty;

                var fi = new FileInfo(inputname);
                if (fi.Length == 0)
                    throw new FileLoadException();

                label1.Text = "File directory:" + '\n' + inputname;
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
"Сортировка исходного текстового файла способом Бетчера\n" +
"Для выбора файла входных данных " +
"использовать стандартный диалог.\n" + "\n" + "Разработчик:\n" + "Возовиков Никита Александрович\n" + "БГУ ФПМИ 1 курс 10 группа  \n", "About...", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }

        int[] array;
        private async void Button1_Click(object sender, EventArgs e)
        {
            if (CHLZ == MTH.emty)
            {
                MessageBox.Show("No sorting method selected!", "Warning!", MessageBoxButtons.OK, MessageBoxIcon.Warning);
                return;
            }

            progressBar1.Visible = true;
        
            StreamReader input = new StreamReader(inputname, System.Text.Encoding.UTF8);
                string str, val = string.Empty;
                int count = 0;
            progressBar1.PerformStep();

            while ((str = input.ReadLine()) != null)
                {
                str += ' ';
                    for (int i = 0; i < str.Length; i++)
                    {
                        if (str[i] != ' ')
                            continue;
                        else
                            count++;
                    }
                }
                input.Close();

            array = new int [count];
            progressBar1.PerformStep();
            using (input = new StreamReader(inputname, System.Text.Encoding.UTF8))
            {
                int len = 0;
                while ((str = input.ReadLine()) != null)
                {                
                    for (int i = 0; i < str.Length; i++)
                    {                       
                            if (str[i] != ' ')
                                val += str[i];
                            else
                            {
                                if (Int32.TryParse(val, out int res))
                                    array[len++] = Int32.Parse(val);
                                else
                                {
                                    MessageBox.Show("Invalid data!", "Error!", MessageBoxButtons.OK, MessageBoxIcon.Error);
                                    progressBar1.Visible = false;
                                    progressBar1.Value = 0;
                                    return;
                                }
                                val = string.Empty;
                            }
                        
                    }
                }
                
                progressBar1.PerformStep();

                await Task.Run(() => Sort.sort(array, CHLZ));
                progressBar1.PerformStep();

                MessageBox.Show("The data is sorted!", "Success!", MessageBoxButtons.OK, MessageBoxIcon.Information);

                progressBar1.Visible = false;
                progressBar1.Value = 0;
                button2.Enabled = true;
                button1.Enabled = false;
            }

        }
        
        private async void Button2_Click(object sender, EventArgs e)
        {
            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                using (StreamWriter output = new StreamWriter(saveFileDialog1.FileName))
                {
                    progressBar1.Visible = true;
                    progressBar1.Maximum = 2;
                    progressBar1.PerformStep();
                    await Task.Run(() => Re_Write(output));
                    progressBar1.PerformStep();
                }
                progressBar1.Value = 0;
                progressBar1.Maximum = 4;
                progressBar1.Visible = false;
                button2.Enabled = false;
                button1.Enabled = true;
                flowLayoutPanel1.Visible = false;
            }
        }

        private void Re_Write(StreamWriter output)
        {
            string str = string.Empty;
            for (int i = 0; i < array.Length; i++)
            {
                if ((str.Length + array[i].ToString().Length + 1) < 1024)
                {                   
                    str += array[i].ToString();
                    str += ' ';
                }
                else
                {
                    output.WriteLine(str);
                    str = string.Empty;
                }
            }
        }

        public enum MTH { up=1,down=0,emty=3};
        MTH CHLZ = MTH.emty;
        private void Up_CheckedChanged(object sender, EventArgs e)
        {
            CHLZ = MTH.up;
        }

        private void Down_CheckedChanged(object sender, EventArgs e)
        {
            CHLZ = MTH.down;
        }
    }
}
