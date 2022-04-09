using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace OS3
{
    class Test
    {
        public string InputFile { get; set; }
        public string OutPutFile { get; set; }

        public Test(string InputFile, string OutPutFile)
        {
            this.InputFile = InputFile;
            this.OutPutFile = OutPutFile;
        }
    }
}
