using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace HTMLmapCreator
{
    public partial class ObjectInfo : Form
    {
        public ObjectInfo()
        {
            InitializeComponent();
        }

        List<Form1.InfoStruct> one;
        ComboBox two;
        PictureBox three;
        Form1.InfoStruct temp;
        public ObjectInfo(List<Form1.InfoStruct> obj, ComboBox box,PictureBox pict)
        {
            InitializeComponent();

            one = obj;
            two = box;
            three = pict;

            temp = one[two.SelectedIndex];
            label1.Text = "URL-adress: " + temp.link + '\n' + '\n' + "Alternative inscription: " + temp.alt + '\n' + '\n' + "Coordinates: " + '\n' + "x1 = " + temp.area.Left + "    " + "y1 = " + temp.area.Top + '\n' + '\n' + "x2 = " + temp.area.Right + "    " + "y2 = " + temp.area.Bottom + '\n';        
        }

        private void Button1_Click(object sender, EventArgs e)
        {
            one.Remove(temp);
            two.Items.Remove(two.SelectedItem);
        
            three.Refresh();
            three.Invalidate();

            Close();
        }

        private void Button2_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
