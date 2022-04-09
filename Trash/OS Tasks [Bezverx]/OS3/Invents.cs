using System;
using System.Collections.Generic;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OS3
{
    class Invents
    {
        private class TEvent
        {
            public string EventText { get; set; }
            public Color EventColor { get; set; }

            public TEvent(string EventText, Color EventColor)
            {
                this.EventText = EventText;
                this.EventColor = EventColor;
            }
        }

        public enum Events { Bunner, Run, Solve, Error, Check, Upload, Info, Get, Ok };

        private static TEvent BunnerEvent = new TEvent("[SYSTEM]", Color.Indigo);
        private static TEvent RunEvent = new TEvent("[RUN]", Color.Blue);
        private static TEvent SolveEvent = new TEvent("[SOLVE]", Color.Green);
        private static TEvent ErrorEvent = new TEvent("[ERROR]", Color.Red);
        private static TEvent CheckEvent = new TEvent("[CHECK]", Color.Brown);
        private static TEvent UploadEvent = new TEvent("[UPLOAD]", Color.Cyan);
        private static TEvent Infovent = new TEvent("[INFO]", Color.Orange);
        private static TEvent GetEvent = new TEvent("[GET]", Color.Violet);
        private static TEvent OkEvent = new TEvent("[OK]", Color.DarkGreen);


        public static void setEvent(Form1 Form, Events ev)
        {
            TEvent temp = BunnerEvent;

            switch (ev)
            {
                case Events.Bunner:
                    temp = BunnerEvent;
                    break;
                case Events.Run:
                    temp = RunEvent;
                    break;
                case Events.Solve:
                    temp = SolveEvent;
                    break;
                case Events.Error:
                    temp = ErrorEvent;
                    break;
                case Events.Check:
                    temp = CheckEvent;
                    break;
                case Events.Upload:
                    temp = UploadEvent;
                    break;
                case Events.Info:
                    temp = Infovent;
                    break;
                case Events.Get:
                    temp = GetEvent;
                    break;
                case Events.Ok:
                    temp = OkEvent;
                    break;
                default:
                    break;
            }
            Form.Invoke(Form.ColorTextDelegate, new Object[] { temp.EventText, temp.EventColor });
        }
    }
}
