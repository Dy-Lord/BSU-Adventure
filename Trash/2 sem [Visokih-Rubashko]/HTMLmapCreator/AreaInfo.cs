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
    public partial class AreaInfo : Form
    {
        public AreaInfo()
        {
            InitializeComponent();
        }

        public string href = string.Empty;
        public string alt = string.Empty;
        private void Button1_Click(object sender, EventArgs e)
        {
            href = LinkBox.Text;
            alt = AltBox.Text;
            Close();
        }
    }
}
