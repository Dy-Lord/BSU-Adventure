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

namespace HTMLmapCreator
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
"Создание HTML - карты.\nПрограмма предлагает выбрать файл изображения, отображает " +
"его в клиентской области окна.\nПользователь может определять непересекающиеся " +
"прямоугольные области на изображении, с каждой областью связывает название и URL-адрес.\nПосле нанесения разметки программа сохраняет разметку в текстовый файл в виде " +
"HTML - карты(тег<map>, оставшиеся неразмеченными части изображения помечать " +
"атрибутом nohref).\n" +
"Для выбора файла входных данных " +
"использовать стандартный диалог.\n" + "\n" + "Разработчик:\n" + "Возовиков Никита Александрович\n" + "БГУ ФПМИ 1 курс 10 группа  \n", "About...", MessageBoxButtons.OK, MessageBoxIcon.Information);
        }
      
        private void OpenImageToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (openFileDialog1.ShowDialog() == DialogResult.OK)
            {
                flowLayoutPanel1.Enabled = true;
                pictureBox1.Enabled = true;
                pictureBox1.Load(openFileDialog1.FileName);

                comboBox1.Items.Clear();
                one.Clear();
            }
        }

        private void ExitToolStripMenuItem_Click(object sender, EventArgs e)
        {
            if (MessageBox.Show("Are you sure to exit?", Text, MessageBoxButtons.YesNo, MessageBoxIcon.Question) == DialogResult.Yes)
                Close();
        }

        string name = string.Empty;
        string idmap = string.Empty;
        private void Button1_Click(object sender, EventArgs e)
        {
            name = NAME_TEXT.Text;
            idmap = ID_TEXT.Text;

            saveFileDialog1.FileName = name;

            if (saveFileDialog1.ShowDialog() == DialogResult.OK)
            {
                

                using (StreamWriter output = new StreamWriter(saveFileDialog1.FileName))
                {

                    output.WriteLine("<p><map id=" + '"' + idmap + '"' + " " + " name=" + '"' + name + '"' + ">");
                    foreach (InfoStruct el in one)
                        if (el.link != "NoHref")
                            output.WriteLine("  <area shape=" + '"' + "rect" + '"' + ' ' + "coords=" + '"' + el.area.Left + ',' + el.area.Top + ',' + el.area.Right + ',' + el.area.Bottom + '"' +
                                " " + "href=" + '"' + el.link + '"' + " " + "alt=" + '"' + el.alt + '"' + ">");
                        else
                            output.WriteLine("  <area shape=" + '"' + "rect" + '"' + ' ' + "coords=" + '"' + el.area.Left + ',' + el.area.Top + ',' + el.area.Right + ',' + el.area.Bottom + '"' +
                                " " + "nohref" + " " + "alt=" + '"' + el.alt + '"' + ">");
                    output.WriteLine("</map></p>");
                }

                MessageBox.Show("HTML Map Saved!", "Success", MessageBoxButtons.OK, MessageBoxIcon.Information);
            }
        }

        int count = 0;
        public struct InfoStruct
        {
            public Rectangle area;
            public string link;
            public string alt;
            public int ID;
            public InfoStruct(Rectangle one, string two, string three,int id)
            {
                area = one;
                link = two;
                alt = three;
                ID = id;
            }
        }

        List<InfoStruct> one = new List<InfoStruct>(1000);

        Pen selectpen = new Pen(Brushes.Black, 1f) { DashStyle = System.Drawing.Drawing2D.DashStyle.DashDot };
        Pen errorpen = new Pen(Brushes.Red, 1f) { DashStyle = System.Drawing.Drawing2D.DashStyle.DashDot };
        Brush brr = new SolidBrush(Color.Red);
        Font font = new Font(FontFamily.GenericSerif, 10, FontStyle.Regular, GraphicsUnit.Point);

        static Rectangle temprect;
        Point startpoint;
        
        private void PictureBox1_MouseDown(object sender, MouseEventArgs e)
        {
            pictureBox1.Paint += Selection_Paint;
            startpoint = e.Location;
        }
        private void PictureBox1_MouseMove(object sender, MouseEventArgs e)
        {
            if (e.Button == System.Windows.Forms.MouseButtons.Left)
                temprect = GetSelRectangle(startpoint, e.Location);             
            (sender as PictureBox).Refresh();
        }

        private void PictureBox1_MouseUp(object sender, MouseEventArgs e)
        {
            if (CrossRect(temprect) == false && (temprect.Width != 0 && temprect.Height !=0 )) 
            {
                pictureBox1.Paint -= Selection_Paint;              
                pictureBox1.Paint += PictureBox1_Paint;
               // (sender as PictureBox).Refresh();

                AreaInfo DLG = new AreaInfo();
                DLG.ShowDialog();
                InfoStruct temp = new InfoStruct(temprect, DLG.href, DLG.alt, ++count);
                one.Add(temp);

                comboBox1.Items.Add("Object №" + temp.ID.ToString());
            }
        }
        private void Selection_Paint(object sender, PaintEventArgs e)
        {
            if (CrossRect(temprect) == false)
                e.Graphics.DrawRectangle(selectpen, temprect);
            else
                e.Graphics.DrawRectangle(errorpen, temprect);
        }

        private void PictureBox1_Paint(object sender, PaintEventArgs e)
        {
            foreach (InfoStruct el in one)
            {
                e.Graphics.DrawString(el.ID.ToString(), font, brr, (el.area.Right - el.area.Width / 2), (el.area.Bottom - el.area.Height / 2));
                e.Graphics.DrawRectangle(selectpen, el.area);
            }
            
        }
        Rectangle GetSelRectangle(Point start_P, Point mouse_P)
        {
            Rectangle Rect = new Rectangle();
           
            int deltaX = mouse_P.X - start_P.X, deltaY = mouse_P.Y - start_P.Y;
            Size RectSize = new Size(Math.Abs(deltaX), Math.Abs(deltaY));


            if (deltaX >= 0 && deltaY >= 0)
                Rect = new Rectangle(start_P, RectSize);

            if (deltaX > 0 && deltaY < 0)
                Rect = new Rectangle(start_P.X, mouse_P.Y, RectSize.Width, RectSize.Height);

            if (deltaX < 0 && deltaY > 0)
                Rect = new Rectangle(mouse_P.X, start_P.Y, RectSize.Width, RectSize.Height);

            if (deltaX < 0 && deltaY < 0)
                Rect = new Rectangle(mouse_P, RectSize);

           
            if (Rect.Top < 0)
                Rect.Y = 0;

            if (Rect.Left < 0)
                Rect.X = 0;

            if (Rect.Bottom > pictureBox1.Image.Height || Rect.Right > pictureBox1.Image.Width) 
            {
                Size newSize;

                if (Rect.Right > pictureBox1.Image.Width)
                {
                    if (Rect.Bottom > pictureBox1.Image.Height)
                        newSize = new Size(pictureBox1.Width - Rect.Left - 1, pictureBox1.Height - Rect.Top - 1);
                    else
                        newSize = new Size(pictureBox1.Width - Rect.Left - 1, Rect.Height);
                }
                else
                    newSize = new Size(Rect.Width, pictureBox1.Height - Rect.Top - 1);
                                                 
                Rect = new Rectangle(Rect.Location, newSize);
            }

            return Rect;
        }

        private bool CrossRect(Rectangle rect)
        {
            foreach(InfoStruct el in one)
            {
                if (((rect.Left + rect.Width) >= el.area.Left) && ((rect.Top + rect.Height) >= el.area.Top) && (rect.Left <= el.area.Right && rect.Top <= el.area.Bottom))
                    return true;
            }
            return false;
        }

        private void ComboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            ObjectInfo two = new ObjectInfo(one, comboBox1, pictureBox1);
            two.Show();          
        }

        private void ColorsToolStripMenuItem_Click(object sender, EventArgs e)
        {
            ColorDLG clr = new ColorDLG(selectpen, errorpen);       
            clr.Show();
           
        }
    }

}

