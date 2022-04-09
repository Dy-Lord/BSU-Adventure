using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OS3
{
    class Box
    {
        private class Panel
        {
            public int minSide { get; set; }
            public int maxSide { get; set; }

            public Panel(int Higth, int Width)
            {
                if (Higth < Width)
                {
                    this.minSide = Higth;
                    this.maxSide = Width;
                }
                else
                {
                    this.minSide = Width;
                    this.maxSide = Higth;
                }
            }

            public bool EqualPanel(Panel panel)
            {
                if (minSide == panel.minSide && maxSide == panel.maxSide)
                    return true;
                else
                    return false;
            }
        }

        private List<Panel> Panels;
        public Box()
        {
            Panels = new List<Panel>();
        }

        public void setPanel(int Higth, int Width)
        {
            Panels.Add(new Panel(Higth, Width));
        }

        public int getPanelCount()
        {
            return Panels.Count;
        }

        public bool isBox()
        {
            if (getPanelCount() < 6)
                return false;

            List<Panel> pair1 = new List<Panel>();
            List<Panel> pair2 = new List<Panel>();
            List<Panel> pair3 = new List<Panel>();

            pair1.AddRange(Panels);
            pair2.Add(pair1[0]);
            pair1.Remove(pair1[0]);

            foreach(Panel pan in pair1)
                if (pair2[0].EqualPanel(pan))
                {
                    pair2.Add(pan);
                    pair1.Remove(pan);
                    break;
                }

            if (pair2.Count != 2)
                return false;

            pair3.Add(pair1[0]);
            pair1.Remove(pair1[0]);

            foreach (Panel pan in pair1)
                if (pair3[0].EqualPanel(pan))
                {
                    pair3.Add(pan);
                    pair1.Remove(pan);
                    break;
                }

            if (pair3.Count != 2)
                return false;

            if (!pair1[0].EqualPanel(pair1[1]))
                return false;

            if (pair2[0].minSide == pair3[0].minSide)
            {
                Panel temp = new Panel(pair2[0].maxSide, pair3[0].maxSide);
                if (temp.EqualPanel(pair1[0]))
                    return true;
            }

            if (pair2[0].minSide == pair1[0].minSide)
            {
                Panel temp = new Panel(pair2[0].maxSide, pair1[0].maxSide);
                if (temp.EqualPanel(pair3[0]))
                    return true;
            }

            if (pair2[0].minSide == pair3[0].maxSide)
            {
                Panel temp = new Panel(pair2[0].maxSide, pair3[0].minSide);
                if (temp.EqualPanel(pair1[0]))
                    return true;
            }

            if (pair2[0].minSide == pair1[0].maxSide)
            {
                Panel temp = new Panel(pair2[0].maxSide, pair1[0].minSide);
                if (temp.EqualPanel(pair3[0]))
                    return true;
            }

            return false;
        }
    }
}
