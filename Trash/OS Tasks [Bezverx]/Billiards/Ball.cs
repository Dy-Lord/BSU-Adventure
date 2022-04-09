using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Billiards
{
    public class Ball
    {
        public Color color;
        public SolidBrush Brush { get; set; }
        public float velocityX { get; set; }
        public float velocityY { get; set; }
        public float force { get; set; }
        public float mass { get; set; }


        private int reverseX = 1;
        private int reverseY = 1;
        private float prop;

        public float currentX { set; get; }
        public float currentY { set; get; }
        public float radius { get; set; }

        public Ball(float startX, float startY, float radius,Color color, float startVelocityX, float startVelocityY, float force, float mass)
        {
            this.color = color;

            Brush = new SolidBrush(color);
            velocityX = startVelocityX;
            velocityY = startVelocityY;

            this.force = force;
            this.mass = mass;

            prop = startVelocityX / startVelocityY;

            currentX = startX;
            currentY = startY;

            this.radius = radius;
        }

        public void ballMove(float timeDiv, float height, float widght)
        {
            if (currentX >= widght - 15 - radius || currentX <= 15)
                reverseX = -reverseX;
            
            if (currentY >= height - 15 - radius || currentY <= 15)
                reverseY = -reverseY;

            velocityX -= (force / mass) * timeDiv * prop;
            velocityY -= (force / mass) * timeDiv;

            if (velocityX <= 0 || velocityY <=0)
                force = 0;

            currentX += reverseX * velocityX;
            currentY += reverseY * velocityY;
        }

    }
}
