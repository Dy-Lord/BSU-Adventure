namespace CodeConverter
{
    partial class Form1
    {
        /// <summary>
        /// Обязательная переменная конструктора.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Освободить все используемые ресурсы.
        /// </summary>
        /// <param name="disposing">истинно, если управляемый ресурс должен быть удален; иначе ложно.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Код, автоматически созданный конструктором форм Windows

        /// <summary>
        /// Требуемый метод для поддержки конструктора — не изменяйте 
        /// содержимое этого метода с помощью редактора кода.
        /// </summary>
        private void InitializeComponent()
        {
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.exitToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.aboutToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openFileDialog1 = new System.Windows.Forms.OpenFileDialog();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.windows = new System.Windows.Forms.RadioButton();
            this.utf = new System.Windows.Forms.RadioButton();
            this.koi = new System.Windows.Forms.RadioButton();
            this.ibm = new System.Windows.Forms.RadioButton();
            this.button1 = new System.Windows.Forms.Button();
            this.saveFileDialog1 = new System.Windows.Forms.SaveFileDialog();
            this.flowLayoutPanel1 = new System.Windows.Forms.FlowLayoutPanel();
            this.label1 = new System.Windows.Forms.Label();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.oldwin = new System.Windows.Forms.RadioButton();
            this.oldutf = new System.Windows.Forms.RadioButton();
            this.oldkoi = new System.Windows.Forms.RadioButton();
            this.oldibm = new System.Windows.Forms.RadioButton();
            this.menuStrip1.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.flowLayoutPanel1.SuspendLayout();
            this.groupBox2.SuspendLayout();
            this.SuspendLayout();
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.aboutToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Size = new System.Drawing.Size(194, 24);
            this.menuStrip1.TabIndex = 1;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.openToolStripMenuItem,
            this.exitToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(37, 20);
            this.fileToolStripMenuItem.Text = "File";
            // 
            // openToolStripMenuItem
            // 
            this.openToolStripMenuItem.Name = "openToolStripMenuItem";
            this.openToolStripMenuItem.Size = new System.Drawing.Size(103, 22);
            this.openToolStripMenuItem.Text = "Open";
            this.openToolStripMenuItem.Click += new System.EventHandler(this.OpenToolStripMenuItem_Click);
            // 
            // exitToolStripMenuItem
            // 
            this.exitToolStripMenuItem.Name = "exitToolStripMenuItem";
            this.exitToolStripMenuItem.Size = new System.Drawing.Size(103, 22);
            this.exitToolStripMenuItem.Text = "Exit";
            this.exitToolStripMenuItem.Click += new System.EventHandler(this.ExitToolStripMenuItem_Click);
            // 
            // aboutToolStripMenuItem
            // 
            this.aboutToolStripMenuItem.Name = "aboutToolStripMenuItem";
            this.aboutToolStripMenuItem.Size = new System.Drawing.Size(58, 20);
            this.aboutToolStripMenuItem.Text = "About..";
            this.aboutToolStripMenuItem.Click += new System.EventHandler(this.AboutToolStripMenuItem_Click);
            // 
            // openFileDialog1
            // 
            this.openFileDialog1.Filter = "Text files|*.txt";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.windows);
            this.groupBox1.Controls.Add(this.utf);
            this.groupBox1.Controls.Add(this.koi);
            this.groupBox1.Controls.Add(this.ibm);
            this.groupBox1.Location = new System.Drawing.Point(3, 143);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(182, 121);
            this.groupBox1.TabIndex = 6;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Choose new code";
            // 
            // windows
            // 
            this.windows.AutoSize = true;
            this.windows.Location = new System.Drawing.Point(6, 90);
            this.windows.Name = "windows";
            this.windows.Size = new System.Drawing.Size(93, 17);
            this.windows.TabIndex = 3;
            this.windows.TabStop = true;
            this.windows.Text = "windows-1251";
            this.windows.UseVisualStyleBackColor = true;
            this.windows.CheckedChanged += new System.EventHandler(this.windowscode);
            // 
            // utf
            // 
            this.utf.AutoSize = true;
            this.utf.Location = new System.Drawing.Point(6, 67);
            this.utf.Name = "utf";
            this.utf.Size = new System.Drawing.Size(46, 17);
            this.utf.TabIndex = 2;
            this.utf.TabStop = true;
            this.utf.Text = "utf-8";
            this.utf.UseVisualStyleBackColor = true;
            this.utf.CheckedChanged += new System.EventHandler(this.Utf_CheckedChanged);
            // 
            // koi
            // 
            this.koi.AutoSize = true;
            this.koi.Location = new System.Drawing.Point(6, 44);
            this.koi.Name = "koi";
            this.koi.Size = new System.Drawing.Size(51, 17);
            this.koi.TabIndex = 1;
            this.koi.TabStop = true;
            this.koi.Text = "koi8-r";
            this.koi.UseVisualStyleBackColor = true;
            this.koi.CheckedChanged += new System.EventHandler(this.Koi_CheckedChanged);
            // 
            // ibm
            // 
            this.ibm.AutoSize = true;
            this.ibm.Location = new System.Drawing.Point(6, 21);
            this.ibm.Name = "ibm";
            this.ibm.Size = new System.Drawing.Size(65, 17);
            this.ibm.TabIndex = 0;
            this.ibm.TabStop = true;
            this.ibm.Text = " ibm-866";
            this.ibm.UseVisualStyleBackColor = true;
            this.ibm.CheckedChanged += new System.EventHandler(this.Ibm_CheckedChanged);
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(3, 270);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(188, 28);
            this.button1.TabIndex = 7;
            this.button1.Text = "Save as..";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.Button1_Click);
            // 
            // saveFileDialog1
            // 
            this.saveFileDialog1.Filter = "Text files|*.txt";
            // 
            // flowLayoutPanel1
            // 
            this.flowLayoutPanel1.AutoSize = true;
            this.flowLayoutPanel1.Controls.Add(this.label1);
            this.flowLayoutPanel1.Controls.Add(this.groupBox2);
            this.flowLayoutPanel1.Controls.Add(this.groupBox1);
            this.flowLayoutPanel1.Controls.Add(this.button1);
            this.flowLayoutPanel1.FlowDirection = System.Windows.Forms.FlowDirection.TopDown;
            this.flowLayoutPanel1.Location = new System.Drawing.Point(0, 24);
            this.flowLayoutPanel1.Name = "flowLayoutPanel1";
            this.flowLayoutPanel1.Size = new System.Drawing.Size(194, 301);
            this.flowLayoutPanel1.TabIndex = 8;
            this.flowLayoutPanel1.Visible = false;
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(3, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(0, 13);
            this.label1.TabIndex = 8;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.oldwin);
            this.groupBox2.Controls.Add(this.oldutf);
            this.groupBox2.Controls.Add(this.oldkoi);
            this.groupBox2.Controls.Add(this.oldibm);
            this.groupBox2.Location = new System.Drawing.Point(3, 16);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(182, 121);
            this.groupBox2.TabIndex = 7;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "File code";
            // 
            // oldwin
            // 
            this.oldwin.AutoSize = true;
            this.oldwin.Location = new System.Drawing.Point(6, 90);
            this.oldwin.Name = "oldwin";
            this.oldwin.Size = new System.Drawing.Size(93, 17);
            this.oldwin.TabIndex = 3;
            this.oldwin.TabStop = true;
            this.oldwin.Text = "windows-1251";
            this.oldwin.UseVisualStyleBackColor = true;
            this.oldwin.CheckedChanged += new System.EventHandler(this.Oldwin_CheckedChanged);
            // 
            // oldutf
            // 
            this.oldutf.AutoSize = true;
            this.oldutf.Location = new System.Drawing.Point(6, 67);
            this.oldutf.Name = "oldutf";
            this.oldutf.Size = new System.Drawing.Size(46, 17);
            this.oldutf.TabIndex = 2;
            this.oldutf.TabStop = true;
            this.oldutf.Text = "utf-8";
            this.oldutf.UseVisualStyleBackColor = true;
            this.oldutf.CheckedChanged += new System.EventHandler(this.Oldutf_CheckedChanged);
            // 
            // oldkoi
            // 
            this.oldkoi.AutoSize = true;
            this.oldkoi.Location = new System.Drawing.Point(6, 44);
            this.oldkoi.Name = "oldkoi";
            this.oldkoi.Size = new System.Drawing.Size(51, 17);
            this.oldkoi.TabIndex = 1;
            this.oldkoi.TabStop = true;
            this.oldkoi.Text = "koi8-r";
            this.oldkoi.UseVisualStyleBackColor = true;
            this.oldkoi.CheckedChanged += new System.EventHandler(this.Oldkoi_CheckedChanged);
            // 
            // oldibm
            // 
            this.oldibm.AutoSize = true;
            this.oldibm.Location = new System.Drawing.Point(6, 21);
            this.oldibm.Name = "oldibm";
            this.oldibm.Size = new System.Drawing.Size(65, 17);
            this.oldibm.TabIndex = 0;
            this.oldibm.TabStop = true;
            this.oldibm.Text = " ibm-866";
            this.oldibm.UseVisualStyleBackColor = true;
            this.oldibm.CheckedChanged += new System.EventHandler(this.Oldibm_CheckedChanged);
            // 
            // Form1
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.AutoSize = true;
            this.ClientSize = new System.Drawing.Size(194, 325);
            this.Controls.Add(this.flowLayoutPanel1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Name = "Form1";
            this.StartPosition = System.Windows.Forms.FormStartPosition.CenterScreen;
            this.Text = "Code Converter";
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.flowLayoutPanel1.ResumeLayout(false);
            this.flowLayoutPanel1.PerformLayout();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem aboutToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem exitToolStripMenuItem;
        private System.Windows.Forms.OpenFileDialog openFileDialog1;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.RadioButton windows;
        private System.Windows.Forms.RadioButton utf;
        private System.Windows.Forms.RadioButton koi;
        private System.Windows.Forms.RadioButton ibm;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.SaveFileDialog saveFileDialog1;
        private System.Windows.Forms.FlowLayoutPanel flowLayoutPanel1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.RadioButton oldwin;
        private System.Windows.Forms.RadioButton oldutf;
        private System.Windows.Forms.RadioButton oldkoi;
        private System.Windows.Forms.RadioButton oldibm;
    }
}

