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
    public partial class ColorDLG : Form
    {
        Pen Select1;
        Pen Error;
           
        public ColorDLG(Pen select1,Pen error)
        {
            InitializeComponent();

            Select1 = select1;
            Error = error;         
        }


        private void Button1_Click(object sender, EventArgs e)
        {
            if(colorDialog1.ShowDialog()==DialogResult.OK)
            {
                Select1.Color = colorDialog1.Color;
            }

        }

        private void Button2_Click(object sender, EventArgs e)
        {
            if (colorDialog1.ShowDialog() == DialogResult.OK)
            {
                Error.Color = colorDialog1.Color;
            }
        }
     
        private void Button4_Click(object sender, EventArgs e)
        {
            Close();
        }
    }
}
