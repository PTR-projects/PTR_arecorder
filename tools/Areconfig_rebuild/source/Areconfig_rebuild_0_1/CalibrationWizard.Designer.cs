
namespace Areconfig_rebuild_0_1
{
    partial class CalibrationWizard
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(CalibrationWizard));
            this.CalWizard_Tabs = new System.Windows.Forms.TabControl();
            this.Info = new System.Windows.Forms.TabPage();
            this.acc_Xp = new System.Windows.Forms.TabPage();
            this.acc_Xn = new System.Windows.Forms.TabPage();
            this.acc_Yp = new System.Windows.Forms.TabPage();
            this.acc_Yn = new System.Windows.Forms.TabPage();
            this.acc_Zp = new System.Windows.Forms.TabPage();
            this.acc_Zn = new System.Windows.Forms.TabPage();
            this.Summary = new System.Windows.Forms.TabPage();
            this.button_SaveCalib = new System.Windows.Forms.Button();
            this.button_Cancel = new System.Windows.Forms.Button();
            this.button_prevStep = new System.Windows.Forms.Button();
            this.button_nextStep = new System.Windows.Forms.Button();
            this.button_CalNow = new System.Windows.Forms.Button();
            this.timer1 = new System.Windows.Forms.Timer(this.components);
            this.textBox_accXn = new System.Windows.Forms.TextBox();
            this.textBox_accXp = new System.Windows.Forms.TextBox();
            this.label_accX = new System.Windows.Forms.Label();
            this.label_accY = new System.Windows.Forms.Label();
            this.textBox_accYp = new System.Windows.Forms.TextBox();
            this.textBox_accYn = new System.Windows.Forms.TextBox();
            this.label_accZ = new System.Windows.Forms.Label();
            this.textBox_accZp = new System.Windows.Forms.TextBox();
            this.textBox_accZn = new System.Windows.Forms.TextBox();
            this.label_Hacc = new System.Windows.Forms.Label();
            this.textBox_HaccXp = new System.Windows.Forms.TextBox();
            this.textBox_HaccXn = new System.Windows.Forms.TextBox();
            this.progressBar = new System.Windows.Forms.ProgressBar();
            this.numericUpDown1 = new System.Windows.Forms.NumericUpDown();
            this.picture_accXp = new System.Windows.Forms.PictureBox();
            this.picture_accXn = new System.Windows.Forms.PictureBox();
            this.picture_accYp = new System.Windows.Forms.PictureBox();
            this.picture_accYn = new System.Windows.Forms.PictureBox();
            this.picture_accZp = new System.Windows.Forms.PictureBox();
            this.picture_accZn = new System.Windows.Forms.PictureBox();
            this.CalWizard_Tabs.SuspendLayout();
            this.acc_Xp.SuspendLayout();
            this.acc_Xn.SuspendLayout();
            this.acc_Yp.SuspendLayout();
            this.acc_Yn.SuspendLayout();
            this.acc_Zp.SuspendLayout();
            this.acc_Zn.SuspendLayout();
            this.Summary.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picture_accXp)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picture_accXn)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picture_accYp)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picture_accYn)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picture_accZp)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.picture_accZn)).BeginInit();
            this.SuspendLayout();
            // 
            // CalWizard_Tabs
            // 
            this.CalWizard_Tabs.Controls.Add(this.Info);
            this.CalWizard_Tabs.Controls.Add(this.acc_Xp);
            this.CalWizard_Tabs.Controls.Add(this.acc_Xn);
            this.CalWizard_Tabs.Controls.Add(this.acc_Yp);
            this.CalWizard_Tabs.Controls.Add(this.acc_Yn);
            this.CalWizard_Tabs.Controls.Add(this.acc_Zp);
            this.CalWizard_Tabs.Controls.Add(this.acc_Zn);
            this.CalWizard_Tabs.Controls.Add(this.Summary);
            this.CalWizard_Tabs.Location = new System.Drawing.Point(0, 0);
            this.CalWizard_Tabs.Name = "CalWizard_Tabs";
            this.CalWizard_Tabs.SelectedIndex = 0;
            this.CalWizard_Tabs.Size = new System.Drawing.Size(577, 349);
            this.CalWizard_Tabs.TabIndex = 0;
            this.CalWizard_Tabs.SelectedIndexChanged += new System.EventHandler(this.CalWizard_Tabs_SelectedIndexChanged);
            // 
            // Info
            // 
            this.Info.Location = new System.Drawing.Point(4, 22);
            this.Info.Name = "Info";
            this.Info.Padding = new System.Windows.Forms.Padding(3, 3, 3, 3);
            this.Info.Size = new System.Drawing.Size(569, 323);
            this.Info.TabIndex = 0;
            this.Info.Text = "Info";
            this.Info.UseVisualStyleBackColor = true;
            // 
            // acc_Xp
            // 
            this.acc_Xp.Controls.Add(this.picture_accXp);
            this.acc_Xp.Location = new System.Drawing.Point(4, 22);
            this.acc_Xp.Name = "acc_Xp";
            this.acc_Xp.Padding = new System.Windows.Forms.Padding(3, 3, 3, 3);
            this.acc_Xp.Size = new System.Drawing.Size(569, 323);
            this.acc_Xp.TabIndex = 1;
            this.acc_Xp.Text = "Acc X+";
            this.acc_Xp.UseVisualStyleBackColor = true;
            // 
            // acc_Xn
            // 
            this.acc_Xn.Controls.Add(this.picture_accXn);
            this.acc_Xn.Location = new System.Drawing.Point(4, 22);
            this.acc_Xn.Name = "acc_Xn";
            this.acc_Xn.Padding = new System.Windows.Forms.Padding(3, 3, 3, 3);
            this.acc_Xn.Size = new System.Drawing.Size(569, 323);
            this.acc_Xn.TabIndex = 2;
            this.acc_Xn.Text = "Acc X-";
            this.acc_Xn.UseVisualStyleBackColor = true;
            // 
            // acc_Yp
            // 
            this.acc_Yp.Controls.Add(this.picture_accYp);
            this.acc_Yp.Location = new System.Drawing.Point(4, 22);
            this.acc_Yp.Name = "acc_Yp";
            this.acc_Yp.Padding = new System.Windows.Forms.Padding(3, 3, 3, 3);
            this.acc_Yp.Size = new System.Drawing.Size(569, 323);
            this.acc_Yp.TabIndex = 3;
            this.acc_Yp.Text = "Acc Y+";
            this.acc_Yp.UseVisualStyleBackColor = true;
            // 
            // acc_Yn
            // 
            this.acc_Yn.Controls.Add(this.picture_accYn);
            this.acc_Yn.Location = new System.Drawing.Point(4, 22);
            this.acc_Yn.Name = "acc_Yn";
            this.acc_Yn.Padding = new System.Windows.Forms.Padding(3, 3, 3, 3);
            this.acc_Yn.Size = new System.Drawing.Size(569, 323);
            this.acc_Yn.TabIndex = 4;
            this.acc_Yn.Text = "Acc Y-";
            this.acc_Yn.UseVisualStyleBackColor = true;
            // 
            // acc_Zp
            // 
            this.acc_Zp.Controls.Add(this.picture_accZp);
            this.acc_Zp.Location = new System.Drawing.Point(4, 22);
            this.acc_Zp.Name = "acc_Zp";
            this.acc_Zp.Padding = new System.Windows.Forms.Padding(3, 3, 3, 3);
            this.acc_Zp.Size = new System.Drawing.Size(569, 323);
            this.acc_Zp.TabIndex = 5;
            this.acc_Zp.Text = "Acc Z+";
            this.acc_Zp.UseVisualStyleBackColor = true;
            // 
            // acc_Zn
            // 
            this.acc_Zn.Controls.Add(this.picture_accZn);
            this.acc_Zn.Location = new System.Drawing.Point(4, 22);
            this.acc_Zn.Name = "acc_Zn";
            this.acc_Zn.Padding = new System.Windows.Forms.Padding(3, 3, 3, 3);
            this.acc_Zn.Size = new System.Drawing.Size(569, 323);
            this.acc_Zn.TabIndex = 6;
            this.acc_Zn.Text = "Acc Z-";
            this.acc_Zn.UseVisualStyleBackColor = true;
            // 
            // Summary
            // 
            this.Summary.Controls.Add(this.button_SaveCalib);
            this.Summary.Location = new System.Drawing.Point(4, 22);
            this.Summary.Name = "Summary";
            this.Summary.Padding = new System.Windows.Forms.Padding(3, 3, 3, 3);
            this.Summary.Size = new System.Drawing.Size(569, 323);
            this.Summary.TabIndex = 7;
            this.Summary.Text = "Summary";
            this.Summary.UseVisualStyleBackColor = true;
            // 
            // button_SaveCalib
            // 
            this.button_SaveCalib.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.button_SaveCalib.Location = new System.Drawing.Point(192, 192);
            this.button_SaveCalib.Name = "button_SaveCalib";
            this.button_SaveCalib.Size = new System.Drawing.Size(137, 63);
            this.button_SaveCalib.TabIndex = 4;
            this.button_SaveCalib.Text = "Save and Exit";
            this.button_SaveCalib.UseVisualStyleBackColor = true;
            this.button_SaveCalib.Click += new System.EventHandler(this.button_SaveCalib_Click);
            // 
            // button_Cancel
            // 
            this.button_Cancel.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.button_Cancel.Location = new System.Drawing.Point(613, 360);
            this.button_Cancel.Name = "button_Cancel";
            this.button_Cancel.Size = new System.Drawing.Size(137, 63);
            this.button_Cancel.TabIndex = 1;
            this.button_Cancel.Text = "Cancel";
            this.button_Cancel.UseVisualStyleBackColor = true;
            this.button_Cancel.Click += new System.EventHandler(this.button_Cancel_Click);
            // 
            // button_prevStep
            // 
            this.button_prevStep.Enabled = false;
            this.button_prevStep.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.button_prevStep.Location = new System.Drawing.Point(613, 240);
            this.button_prevStep.Name = "button_prevStep";
            this.button_prevStep.Size = new System.Drawing.Size(137, 63);
            this.button_prevStep.TabIndex = 2;
            this.button_prevStep.Text = "Previous step";
            this.button_prevStep.UseVisualStyleBackColor = true;
            this.button_prevStep.Click += new System.EventHandler(this.button_prevStep_Click);
            // 
            // button_nextStep
            // 
            this.button_nextStep.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.button_nextStep.Location = new System.Drawing.Point(613, 155);
            this.button_nextStep.Name = "button_nextStep";
            this.button_nextStep.Size = new System.Drawing.Size(137, 63);
            this.button_nextStep.TabIndex = 3;
            this.button_nextStep.Text = "Next step";
            this.button_nextStep.UseVisualStyleBackColor = true;
            this.button_nextStep.Click += new System.EventHandler(this.button_nextStep_Click);
            // 
            // button_CalNow
            // 
            this.button_CalNow.Enabled = false;
            this.button_CalNow.Font = new System.Drawing.Font("Microsoft Sans Serif", 11.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.button_CalNow.Location = new System.Drawing.Point(613, 32);
            this.button_CalNow.Name = "button_CalNow";
            this.button_CalNow.Size = new System.Drawing.Size(137, 63);
            this.button_CalNow.TabIndex = 4;
            this.button_CalNow.Text = "Calibrate Now!";
            this.button_CalNow.UseVisualStyleBackColor = true;
            this.button_CalNow.Click += new System.EventHandler(this.button_CalNow_Click);
            // 
            // timer1
            // 
            this.timer1.Enabled = true;
            this.timer1.Interval = 10;
            this.timer1.Tick += new System.EventHandler(this.timer1_Tick);
            // 
            // textBox_accXn
            // 
            this.textBox_accXn.Enabled = false;
            this.textBox_accXn.HideSelection = false;
            this.textBox_accXn.Location = new System.Drawing.Point(13, 418);
            this.textBox_accXn.Name = "textBox_accXn";
            this.textBox_accXn.Size = new System.Drawing.Size(72, 20);
            this.textBox_accXn.TabIndex = 5;
            // 
            // textBox_accXp
            // 
            this.textBox_accXp.Enabled = false;
            this.textBox_accXp.HideSelection = false;
            this.textBox_accXp.Location = new System.Drawing.Point(13, 392);
            this.textBox_accXp.Name = "textBox_accXp";
            this.textBox_accXp.Size = new System.Drawing.Size(72, 20);
            this.textBox_accXp.TabIndex = 6;
            // 
            // label_accX
            // 
            this.label_accX.AutoSize = true;
            this.label_accX.Location = new System.Drawing.Point(13, 373);
            this.label_accX.Name = "label_accX";
            this.label_accX.Size = new System.Drawing.Size(33, 13);
            this.label_accX.TabIndex = 7;
            this.label_accX.Text = "AccX";
            // 
            // label_accY
            // 
            this.label_accY.AutoSize = true;
            this.label_accY.Location = new System.Drawing.Point(101, 373);
            this.label_accY.Name = "label_accY";
            this.label_accY.Size = new System.Drawing.Size(33, 13);
            this.label_accY.TabIndex = 10;
            this.label_accY.Text = "AccY";
            // 
            // textBox_accYp
            // 
            this.textBox_accYp.Enabled = false;
            this.textBox_accYp.HideSelection = false;
            this.textBox_accYp.Location = new System.Drawing.Point(101, 392);
            this.textBox_accYp.Name = "textBox_accYp";
            this.textBox_accYp.Size = new System.Drawing.Size(72, 20);
            this.textBox_accYp.TabIndex = 9;
            // 
            // textBox_accYn
            // 
            this.textBox_accYn.Enabled = false;
            this.textBox_accYn.HideSelection = false;
            this.textBox_accYn.Location = new System.Drawing.Point(101, 418);
            this.textBox_accYn.Name = "textBox_accYn";
            this.textBox_accYn.Size = new System.Drawing.Size(72, 20);
            this.textBox_accYn.TabIndex = 8;
            // 
            // label_accZ
            // 
            this.label_accZ.AutoSize = true;
            this.label_accZ.Location = new System.Drawing.Point(194, 373);
            this.label_accZ.Name = "label_accZ";
            this.label_accZ.Size = new System.Drawing.Size(33, 13);
            this.label_accZ.TabIndex = 13;
            this.label_accZ.Text = "AccZ";
            // 
            // textBox_accZp
            // 
            this.textBox_accZp.Enabled = false;
            this.textBox_accZp.HideSelection = false;
            this.textBox_accZp.Location = new System.Drawing.Point(194, 392);
            this.textBox_accZp.Name = "textBox_accZp";
            this.textBox_accZp.Size = new System.Drawing.Size(72, 20);
            this.textBox_accZp.TabIndex = 12;
            // 
            // textBox_accZn
            // 
            this.textBox_accZn.Enabled = false;
            this.textBox_accZn.HideSelection = false;
            this.textBox_accZn.Location = new System.Drawing.Point(194, 418);
            this.textBox_accZn.Name = "textBox_accZn";
            this.textBox_accZn.Size = new System.Drawing.Size(72, 20);
            this.textBox_accZn.TabIndex = 11;
            // 
            // label_Hacc
            // 
            this.label_Hacc.AutoSize = true;
            this.label_Hacc.Location = new System.Drawing.Point(285, 373);
            this.label_Hacc.Name = "label_Hacc";
            this.label_Hacc.Size = new System.Drawing.Size(33, 13);
            this.label_Hacc.TabIndex = 16;
            this.label_Hacc.Text = "Hacc";
            // 
            // textBox_HaccXp
            // 
            this.textBox_HaccXp.Enabled = false;
            this.textBox_HaccXp.HideSelection = false;
            this.textBox_HaccXp.Location = new System.Drawing.Point(285, 392);
            this.textBox_HaccXp.Name = "textBox_HaccXp";
            this.textBox_HaccXp.Size = new System.Drawing.Size(72, 20);
            this.textBox_HaccXp.TabIndex = 15;
            // 
            // textBox_HaccXn
            // 
            this.textBox_HaccXn.Enabled = false;
            this.textBox_HaccXn.HideSelection = false;
            this.textBox_HaccXn.Location = new System.Drawing.Point(285, 418);
            this.textBox_HaccXn.Name = "textBox_HaccXn";
            this.textBox_HaccXn.Size = new System.Drawing.Size(72, 20);
            this.textBox_HaccXn.TabIndex = 14;
            // 
            // progressBar
            // 
            this.progressBar.Location = new System.Drawing.Point(613, 101);
            this.progressBar.MarqueeAnimationSpeed = 1;
            this.progressBar.Name = "progressBar";
            this.progressBar.Size = new System.Drawing.Size(137, 23);
            this.progressBar.TabIndex = 17;
            // 
            // numericUpDown1
            // 
            this.numericUpDown1.Location = new System.Drawing.Point(416, 373);
            this.numericUpDown1.Name = "numericUpDown1";
            this.numericUpDown1.Size = new System.Drawing.Size(120, 20);
            this.numericUpDown1.TabIndex = 18;
            // 
            // picture_accXp
            // 
            this.picture_accXp.Image = ((System.Drawing.Image)(resources.GetObject("picture_accXp.Image")));
            this.picture_accXp.InitialImage = null;
            this.picture_accXp.Location = new System.Drawing.Point(20, 11);
            this.picture_accXp.Margin = new System.Windows.Forms.Padding(2);
            this.picture_accXp.Name = "picture_accXp";
            this.picture_accXp.Size = new System.Drawing.Size(150, 300);
            this.picture_accXp.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picture_accXp.TabIndex = 0;
            this.picture_accXp.TabStop = false;
            // 
            // picture_accXn
            // 
            this.picture_accXn.Image = ((System.Drawing.Image)(resources.GetObject("picture_accXn.Image")));
            this.picture_accXn.InitialImage = null;
            this.picture_accXn.Location = new System.Drawing.Point(20, 11);
            this.picture_accXn.Margin = new System.Windows.Forms.Padding(2);
            this.picture_accXn.Name = "picture_accXn";
            this.picture_accXn.Size = new System.Drawing.Size(150, 300);
            this.picture_accXn.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picture_accXn.TabIndex = 1;
            this.picture_accXn.TabStop = false;
            // 
            // picture_accYp
            // 
            this.picture_accYp.Image = ((System.Drawing.Image)(resources.GetObject("picture_accYp.Image")));
            this.picture_accYp.InitialImage = null;
            this.picture_accYp.Location = new System.Drawing.Point(28, 94);
            this.picture_accYp.Margin = new System.Windows.Forms.Padding(2);
            this.picture_accYp.Name = "picture_accYp";
            this.picture_accYp.Size = new System.Drawing.Size(300, 150);
            this.picture_accYp.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picture_accYp.TabIndex = 2;
            this.picture_accYp.TabStop = false;
            // 
            // picture_accYn
            // 
            this.picture_accYn.Image = ((System.Drawing.Image)(resources.GetObject("picture_accYn.Image")));
            this.picture_accYn.InitialImage = null;
            this.picture_accYn.Location = new System.Drawing.Point(28, 94);
            this.picture_accYn.Margin = new System.Windows.Forms.Padding(2);
            this.picture_accYn.Name = "picture_accYn";
            this.picture_accYn.Size = new System.Drawing.Size(300, 150);
            this.picture_accYn.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picture_accYn.TabIndex = 2;
            this.picture_accYn.TabStop = false;
            // 
            // picture_accZp
            // 
            this.picture_accZp.Image = ((System.Drawing.Image)(resources.GetObject("picture_accZp.Image")));
            this.picture_accZp.InitialImage = null;
            this.picture_accZp.Location = new System.Drawing.Point(28, 94);
            this.picture_accZp.Margin = new System.Windows.Forms.Padding(2);
            this.picture_accZp.Name = "picture_accZp";
            this.picture_accZp.Size = new System.Drawing.Size(300, 150);
            this.picture_accZp.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picture_accZp.TabIndex = 2;
            this.picture_accZp.TabStop = false;
            // 
            // picture_accZn
            // 
            this.picture_accZn.Image = ((System.Drawing.Image)(resources.GetObject("picture_accZn.Image")));
            this.picture_accZn.InitialImage = null;
            this.picture_accZn.Location = new System.Drawing.Point(28, 94);
            this.picture_accZn.Margin = new System.Windows.Forms.Padding(2);
            this.picture_accZn.Name = "picture_accZn";
            this.picture_accZn.Size = new System.Drawing.Size(300, 150);
            this.picture_accZn.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.picture_accZn.TabIndex = 2;
            this.picture_accZn.TabStop = false;
            // 
            // CalibrationWizard
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(this.numericUpDown1);
            this.Controls.Add(this.progressBar);
            this.Controls.Add(this.label_Hacc);
            this.Controls.Add(this.textBox_HaccXp);
            this.Controls.Add(this.textBox_HaccXn);
            this.Controls.Add(this.label_accZ);
            this.Controls.Add(this.textBox_accZp);
            this.Controls.Add(this.textBox_accZn);
            this.Controls.Add(this.label_accY);
            this.Controls.Add(this.textBox_accYp);
            this.Controls.Add(this.textBox_accYn);
            this.Controls.Add(this.label_accX);
            this.Controls.Add(this.textBox_accXp);
            this.Controls.Add(this.textBox_accXn);
            this.Controls.Add(this.button_CalNow);
            this.Controls.Add(this.button_nextStep);
            this.Controls.Add(this.button_prevStep);
            this.Controls.Add(this.button_Cancel);
            this.Controls.Add(this.CalWizard_Tabs);
            this.Name = "CalibrationWizard";
            this.Text = "Calibration Wizard";
            this.CalWizard_Tabs.ResumeLayout(false);
            this.acc_Xp.ResumeLayout(false);
            this.acc_Xn.ResumeLayout(false);
            this.acc_Yp.ResumeLayout(false);
            this.acc_Yn.ResumeLayout(false);
            this.acc_Zp.ResumeLayout(false);
            this.acc_Zn.ResumeLayout(false);
            this.Summary.ResumeLayout(false);
            ((System.ComponentModel.ISupportInitialize)(this.numericUpDown1)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picture_accXp)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picture_accXn)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picture_accYp)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picture_accYn)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picture_accZp)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.picture_accZn)).EndInit();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TabControl CalWizard_Tabs;
        private System.Windows.Forms.TabPage Info;
        private System.Windows.Forms.TabPage acc_Xp;
        private System.Windows.Forms.TabPage acc_Xn;
        private System.Windows.Forms.TabPage acc_Yp;
        private System.Windows.Forms.TabPage acc_Yn;
        private System.Windows.Forms.TabPage acc_Zp;
        private System.Windows.Forms.TabPage acc_Zn;
        private System.Windows.Forms.TabPage Summary;
        private System.Windows.Forms.Button button_Cancel;
        private System.Windows.Forms.Button button_prevStep;
        private System.Windows.Forms.Button button_nextStep;
        private System.Windows.Forms.Button button_CalNow;
        private System.Windows.Forms.Timer timer1;
        private System.Windows.Forms.TextBox textBox_accXn;
        private System.Windows.Forms.TextBox textBox_accXp;
        private System.Windows.Forms.Label label_accX;
        private System.Windows.Forms.Label label_accY;
        private System.Windows.Forms.TextBox textBox_accYp;
        private System.Windows.Forms.TextBox textBox_accYn;
        private System.Windows.Forms.Label label_accZ;
        private System.Windows.Forms.TextBox textBox_accZp;
        private System.Windows.Forms.TextBox textBox_accZn;
        private System.Windows.Forms.Label label_Hacc;
        private System.Windows.Forms.TextBox textBox_HaccXp;
        private System.Windows.Forms.TextBox textBox_HaccXn;
        private System.Windows.Forms.ProgressBar progressBar;
        private System.Windows.Forms.Button button_SaveCalib;
        private System.Windows.Forms.NumericUpDown numericUpDown1;
        private System.Windows.Forms.PictureBox picture_accXp;
        private System.Windows.Forms.PictureBox picture_accXn;
        private System.Windows.Forms.PictureBox picture_accYp;
        private System.Windows.Forms.PictureBox picture_accYn;
        private System.Windows.Forms.PictureBox picture_accZp;
        private System.Windows.Forms.PictureBox picture_accZn;
    }
}