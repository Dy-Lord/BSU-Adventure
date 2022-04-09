//UNCOMMIT TO DEBUG MESSAGES

using System;
using System.Collections.Generic;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Drawing;

namespace OS3
{
    class ThreadsConveyor
    {
        Form1 form;

        private static object locker = new object();
        static AutoResetEvent waitOutputHandler = new AutoResetEvent(false);

        private string inputPath;
        private string outputPath;
        private string outputNamePath;

        private const int LEFT_BOUND = 1;
        private const int RIGHT_BOUND = 5;
        private const int MAX_VALUE = 10000;

        private Thread CheckTestThread;
        private Thread SolveTaskThread;
        private Thread CheckTaskThread;

        private Queue<Box> Boxes = new Queue<Box>();

        private bool SolveThread = true;
        private bool SkipCheck = false;
        private bool StopSolveThread = false;
        private bool working = true;
        private bool FileCreated = false;

        private int TCount;

        public ThreadsConveyor(string inputFile, string outputFile, Form1 form)
        {
            this.inputPath = inputFile;
            this.outputPath = outputFile;
            this.outputNamePath = outputFile.Split('.')[0] + ".VER";
            this.form = form;

            CheckTestThread = new Thread(CheckTest);
            CheckTestThread.Start();

            SolveTaskThread = new Thread(SolveTask);
            SolveTaskThread.Start();

            CheckTaskThread = new Thread(CheckTask);
            CheckTaskThread.Start();
        }

        public bool isWorking()
        {
            return working;
        }
        public void stopSolveThread()
        {
            StopSolveThread = true;
        }

        public void resumeSolveThread()
        {
            StopSolveThread = false;
        }

        private void sendTextToRichTextBox(string text)
        {
            form.Invoke(form.TextDelegate, new Object[] { text });
        }

        private void isWrongTest(string error)
        {
            Invents.setEvent(form, Invents.Events.Bunner);
            Invents.setEvent(form, Invents.Events.Error);
            sendTextToRichTextBox($"\t {error}\n");
            SkipCheck = true;
            SolveThread = false;
            FileCreated = true;
        }
        private void CheckTest()
        {
            int TestsCount = 0;
            //sendTextToRichTextBox("--- Check tests thread started! ---" + '\n');
            using (StreamReader stream = new StreamReader(inputPath))
            {
                int count = int.Parse(stream.ReadLine());
                TCount = count;

                if (count < LEFT_BOUND || count > RIGHT_BOUND)
                {
                    isWrongTest("Tests count out of bound!");
                    return;
                }

                while (count != 0)
                {
                    Box box = new Box();
                    List<int> values = new List<int>();

                    char[] separators = new char[] { ' ' };
                    string[] panels = stream.ReadLine().Split(separators, StringSplitOptions.RemoveEmptyEntries);

                    foreach (string pen in panels)
                        values.Add(int.Parse(pen));

                    if (values.Count != 12)
                    {
                        try
                        {
                            Monitor.Enter(locker);
                            Invents.setEvent(form, Invents.Events.Bunner);
                            Invents.setEvent(form, Invents.Events.Error);
                            sendTextToRichTextBox($"\t Test #{TestsCount} wrong count of values!\n");
                        }
                        finally
                        {
                            Monitor.Exit(locker);
                        }
                    }
                    else
                        for (int i = 0; i < values.Count; i += 2)
                        {
                            if (values[i] > MAX_VALUE || values[i + 1] > MAX_VALUE)
                            {
                                try
                                {
                                    Monitor.Enter(locker);
                                    Invents.setEvent(form, Invents.Events.Bunner);
                                    Invents.setEvent(form, Invents.Events.Error);
                                    sendTextToRichTextBox($"\t Test #{TestsCount} values out of bound!\n");
                                }
                                finally
                                {
                                    Monitor.Exit(locker);
                                }
                                break;
                            }
                            else
                                box.setPanel(values[i], values[i + 1]);
                        }

                    try
                    {
                        Monitor.Enter(locker);
                        Invents.setEvent(form, Invents.Events.Bunner);
                        Invents.setEvent(form, Invents.Events.Get);

                        sendTextToRichTextBox($"\t Test #{TestsCount}\n");
                        TestsCount++;
                        Boxes.Enqueue(box);
                    }
                    finally
                    {
                        Monitor.Exit(locker);
                    }

                    count--;
                }

                SolveThread = false;
            }
        }

        private void SolveTask()
        {
            FileInfo fileInf = new FileInfo(outputNamePath);
            if (fileInf.Exists)           
                fileInf.Delete();
            
            int TestsCount = 0;
            //sendTextToRichTextBox("--- Solve thread started! ---" + '\n');
            while (SolveThread || Boxes.Count != 0)
            {
                //Thread.Sleep(5000);
                if (StopSolveThread)
                {
                    Invents.setEvent(form, Invents.Events.Bunner);
                    Invents.setEvent(form, Invents.Events.Info);
                    sendTextToRichTextBox("\t Solve thread stoped!\n");
                    while (true)
                    {
                        if (!StopSolveThread)
                        {
                            Invents.setEvent(form, Invents.Events.Bunner);
                            Invents.setEvent(form, Invents.Events.Info);
                            sendTextToRichTextBox("\t Solve thread resume!\n");
                            break;
                        }
                    }
                }

                try
                {
                    Monitor.Enter(locker);

                    if (Boxes.Count != 0)
                    {
                        using (StreamWriter stream = new StreamWriter(outputNamePath, true, Encoding.Default))
                        {
                            FileCreated = true;
                            if (Boxes.Dequeue().isBox())
                                stream.WriteLine("YES");
                            else
                                stream.WriteLine("NO");
                        }
                        Invents.setEvent(form, Invents.Events.Bunner);
                        Invents.setEvent(form, Invents.Events.Solve);
                        sendTextToRichTextBox($"\t Task #{TestsCount}\n");
                        TestsCount++;
                    }
                }
                finally
                {
                    Monitor.Exit(locker);
                }
                Thread.Sleep(1);
            }

            waitOutputHandler.Set();
        }

        private void CheckTask()
        {
            //sendTextToRichTextBox('\n' + "--- Check tasks thread started! ---" + '\n');
            int TestsCount = 1;
            while (!FileCreated)
            { 
            }
            if (!SkipCheck)
            {
                using (StreamReader stream_out = new StreamReader(outputPath))
                {
                    while (SolveThread || TCount + 1 != TestsCount)
                    {
                        try
                        {
                            Monitor.Enter(locker);
                            using (StreamReader stream = new StreamReader(outputNamePath))
                            {
                                string solveOut = null;
                                for (int i = 0; i < TestsCount; i++)
                                    solveOut = stream.ReadLine();

                                if (solveOut != null)
                                {
                                    Invents.setEvent(form, Invents.Events.Bunner);
                                    Invents.setEvent(form, Invents.Events.Check);
                                    if (solveOut == stream_out.ReadLine())
                                    {
                                        sendTextToRichTextBox($"\tTest #{TestsCount - 1}\t");
                                        Invents.setEvent(form, Invents.Events.Ok);
                                        sendTextToRichTextBox("\n");
                                    }
                                    else
                                    {       
                                        sendTextToRichTextBox($"\tTest #{TestsCount - 1}\t");
                                        Invents.setEvent(form, Invents.Events.Error);
                                        sendTextToRichTextBox("\n");
                                    }
                                    TestsCount++;
                                }

                            }
                        }
                        finally
                        {
                            Monitor.Exit(locker);
                        }
                    }
                }
                waitOutputHandler.WaitOne();

                using (StreamReader stream = new StreamReader(outputNamePath))
                {
                    using (StreamReader stream_out = new StreamReader(outputPath))
                    {
                        Invents.setEvent(form, Invents.Events.Bunner);
                        Invents.setEvent(form, Invents.Events.Check);
                        Invents.setEvent(form, Invents.Events.Info);
                        sendTextToRichTextBox('\n' + "\n[Solve]\t\t[Reference]" + "\n\n");
                        string solveOut;
                        string finalOut;
                        while ((solveOut = stream.ReadLine()) != null && (finalOut = stream_out.ReadLine()) != null)
                        {
                            sendTextToRichTextBox($"\"{solveOut}\"\t\t\"{finalOut}\"\n");
                        }
                    }
                }
            }
            working = false;
        }

    }
}
