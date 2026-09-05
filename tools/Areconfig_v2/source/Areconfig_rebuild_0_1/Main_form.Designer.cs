
namespace Areconfig_rebuild_0_1
{
    partial class Main_form
    {
        /// <summary>
        /// Wymagana zmienna projektanta.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Wyczyść wszystkie używane zasoby.
        /// </summary>
        /// <param name="disposing">prawda, jeżeli zarządzane zasoby powinny zostać zlikwidowane; Fałsz w przeciwnym wypadku.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Kod generowany przez Projektanta formularzy systemu Windows

        /// <summary>
        /// Metoda wymagana do obsługi projektanta — nie należy modyfikować
        /// jej zawartości w edytorze kodu.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            System.Windows.Forms.Label label_Battery_V;
            System.Windows.Forms.Label label_Battery;
            System.Windows.Forms.Label label_Angle;
            System.Windows.Forms.Label label2;
            System.Windows.Forms.Label label_accX;
            System.Windows.Forms.Label label4;
            System.Windows.Forms.Label label5;
            System.Windows.Forms.Label label6;
            System.Windows.Forms.Label label7;
            System.Windows.Forms.Label label8;
            System.Windows.Forms.Label label9;
            System.Windows.Forms.Label label10;
            System.Windows.Forms.Label label11;
            System.Windows.Forms.Label label12;
            System.Windows.Forms.Label label13;
            System.Windows.Forms.Label label14;
            System.Windows.Forms.Label label_ConfigName;
            System.Windows.Forms.Label label_ConfigPhone;
            System.Windows.Forms.Label label_ConfigMainAltitude;
            System.Windows.Forms.Label label_ConfigLaunchpadLength;
            System.Windows.Forms.Label label_ConfigSecondStageDelay;
            System.Windows.Forms.Label label_ConfigDragFailureDetector;
            System.Windows.Forms.Label label_Config1;
            System.Windows.Forms.Label label_Config2;
            System.Windows.Forms.Label label_Config3;
            System.Windows.Forms.Label label_Config4;
            System.Windows.Forms.Label label_AdminSerialNumber;
            System.Windows.Forms.Label label_Admin_A0g;
            System.Windows.Forms.Label label_Admin_Y0g;
            System.Windows.Forms.Label label_Admin_Z0g;
            System.Windows.Forms.Label label_Admin_Ha0g;
            System.Windows.Forms.Label label_Admin_A1g;
            System.Windows.Forms.Label label_Admin_Ha1g;
            System.Windows.Forms.Label label_Admin_Toffset;
            System.Windows.Forms.Label label_LSB_aX_0g;
            System.Windows.Forms.Label label1;
            System.Windows.Forms.Label label3;
            System.Windows.Forms.Label label15;
            System.Windows.Forms.Label label16;
            System.Windows.Forms.Label label17;
            System.Windows.Forms.Label label18;
            System.Windows.Forms.Label label_Author;
            System.Windows.Forms.Label label_SpaceConfig;
            System.ComponentModel.ComponentResourceManager resources = new System.ComponentModel.ComponentResourceManager(typeof(Main_form));
            this.serialPort_USB = new System.IO.Ports.SerialPort(this.components);
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabPage_liveview = new System.Windows.Forms.TabPage();
            this.button_UnlockIgn = new System.Windows.Forms.Button();
            this.status_Ign_SecondStage = new System.Windows.Forms.Button();
            this.status_Ign_Main = new System.Windows.Forms.Button();
            this.status_Ign_Drag = new System.Windows.Forms.Button();
            this.button_Ign_All = new System.Windows.Forms.Button();
            this.button_Ign_SecondStage = new System.Windows.Forms.Button();
            this.button_Ign_Main = new System.Windows.Forms.Button();
            this.button_Ign_Drag = new System.Windows.Forms.Button();
            this.LiveView_OrientationIndicator = new System.Windows.Forms.PictureBox();
            this.liveView_Press = new System.Windows.Forms.TextBox();
            this.liveView_Temp = new System.Windows.Forms.TextBox();
            this.liveView_HAcc = new System.Windows.Forms.TextBox();
            this.liveView_AccZ = new System.Windows.Forms.TextBox();
            this.liveView_AccY = new System.Windows.Forms.TextBox();
            this.liveView_AccX = new System.Windows.Forms.TextBox();
            this.liveView_Angle = new System.Windows.Forms.TextBox();
            this.liveView_Battery = new System.Windows.Forms.TextBox();
            this.tabPage_config = new System.Windows.Forms.TabPage();
            this.numeric_Config4_DragFail = new System.Windows.Forms.NumericUpDown();
            this.numeric_Config3_DragFail = new System.Windows.Forms.NumericUpDown();
            this.numeric_Config2_DragFail = new System.Windows.Forms.NumericUpDown();
            this.numeric_Config1_DragFail = new System.Windows.Forms.NumericUpDown();
            this.numeric_Config4_SecondStageDelay = new System.Windows.Forms.NumericUpDown();
            this.numeric_Config4_LanuchpadLen = new System.Windows.Forms.NumericUpDown();
            this.numeric_Config4_MainParAlt = new System.Windows.Forms.NumericUpDown();
            this.numeric_Config3_SecondStageDelay = new System.Windows.Forms.NumericUpDown();
            this.numeric_Config3_LanuchpadLen = new System.Windows.Forms.NumericUpDown();
            this.numeric_Config3_MainParAlt = new System.Windows.Forms.NumericUpDown();
            this.numeric_Config2_SecondStageDelay = new System.Windows.Forms.NumericUpDown();
            this.numeric_Config2_LanuchpadLen = new System.Windows.Forms.NumericUpDown();
            this.numeric_Config2_MainParAlt = new System.Windows.Forms.NumericUpDown();
            this.numeric_Config1_SecondStageDelay = new System.Windows.Forms.NumericUpDown();
            this.numeric_Config1_LanuchpadLen = new System.Windows.Forms.NumericUpDown();
            this.numeric_Config1_MainParAlt = new System.Windows.Forms.NumericUpDown();
            this.text_ConfigPhone = new System.Windows.Forms.TextBox();
            this.text_ConfigName = new System.Windows.Forms.TextBox();
            this.button_ConfigRead = new System.Windows.Forms.Button();
            this.button_ConfigRestoreDefault = new System.Windows.Forms.Button();
            this.button_ConfigSave = new System.Windows.Forms.Button();
            this.tabPage_logger = new System.Windows.Forms.TabPage();
            this.tabPage_admin = new System.Windows.Forms.TabPage();
            this.button_CalibrationWizard = new System.Windows.Forms.Button();
            this.button_SerialNumber_Increase = new System.Windows.Forms.Button();
            this.numeric_Admin_Toffset = new System.Windows.Forms.NumericUpDown();
            this.numeric_Admin_Ha1g = new System.Windows.Forms.NumericUpDown();
            this.numeric_Admin_A1g = new System.Windows.Forms.NumericUpDown();
            this.numeric_Admin_Ha0g = new System.Windows.Forms.NumericUpDown();
            this.numeric_Admin_Z0g = new System.Windows.Forms.NumericUpDown();
            this.numeric_Admin_Y0g = new System.Windows.Forms.NumericUpDown();
            this.numeric_Admin_A0g = new System.Windows.Forms.NumericUpDown();
            this.numeric_AdminSerial = new System.Windows.Forms.NumericUpDown();
            this.button_AdminRead = new System.Windows.Forms.Button();
            this.button_AdminSave = new System.Windows.Forms.Button();
            this.Console = new System.Windows.Forms.GroupBox();
            this.Console_textbox = new System.Windows.Forms.TextBox();
            this.progressBar1 = new System.Windows.Forms.ProgressBar();
            this.button_USBconnect = new System.Windows.Forms.Button();
            this.statusStrip1 = new System.Windows.Forms.StatusStrip();
            this.status_SerialNumber = new System.Windows.Forms.ToolStripStatusLabel();
            this.button_USBrescan = new System.Windows.Forms.Button();
            this.Serial_COMlist = new System.Windows.Forms.ComboBox();
            this.status_USBcon = new System.Windows.Forms.Button();
            this.backgroundWorker1 = new System.ComponentModel.BackgroundWorker();
            label_Battery_V = new System.Windows.Forms.Label();
            label_Battery = new System.Windows.Forms.Label();
            label_Angle = new System.Windows.Forms.Label();
            label2 = new System.Windows.Forms.Label();
            label_accX = new System.Windows.Forms.Label();
            label4 = new System.Windows.Forms.Label();
            label5 = new System.Windows.Forms.Label();
            label6 = new System.Windows.Forms.Label();
            label7 = new System.Windows.Forms.Label();
            label8 = new System.Windows.Forms.Label();
            label9 = new System.Windows.Forms.Label();
            label10 = new System.Windows.Forms.Label();
            label11 = new System.Windows.Forms.Label();
            label12 = new System.Windows.Forms.Label();
            label13 = new System.Windows.Forms.Label();
            label14 = new System.Windows.Forms.Label();
            label_ConfigName = new System.Windows.Forms.Label();
            label_ConfigPhone = new System.Windows.Forms.Label();
            label_ConfigMainAltitude = new System.Windows.Forms.Label();
            label_ConfigLaunchpadLength = new System.Windows.Forms.Label();
            label_ConfigSecondStageDelay = new System.Windows.Forms.Label();
            label_ConfigDragFailureDetector = new System.Windows.Forms.Label();
            label_Config1 = new System.Windows.Forms.Label();
            label_Config2 = new System.Windows.Forms.Label();
            label_Config3 = new System.Windows.Forms.Label();
            label_Config4 = new System.Windows.Forms.Label();
            label_AdminSerialNumber = new System.Windows.Forms.Label();
            label_Admin_A0g = new System.Windows.Forms.Label();
            label_Admin_Y0g = new System.Windows.Forms.Label();
            label_Admin_Z0g = new System.Windows.Forms.Label();
            label_Admin_Ha0g = new System.Windows.Forms.Label();
            label_Admin_A1g = new System.Windows.Forms.Label();
            label_Admin_Ha1g = new System.Windows.Forms.Label();
            label_Admin_Toffset = new System.Windows.Forms.Label();
            label_LSB_aX_0g = new System.Windows.Forms.Label();
            label1 = new System.Windows.Forms.Label();
            label3 = new System.Windows.Forms.Label();
            label15 = new System.Windows.Forms.Label();
            label16 = new System.Windows.Forms.Label();
            label17 = new System.Windows.Forms.Label();
            label18 = new System.Windows.Forms.Label();
            label_Author = new System.Windows.Forms.Label();
            label_SpaceConfig = new System.Windows.Forms.Label();
            this.tabControl1.SuspendLayout();
            this.tabPage_liveview.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.LiveView_OrientationIndicator)).BeginInit();
            this.tabPage_config.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Config4_DragFail)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Config3_DragFail)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Config2_DragFail)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Config1_DragFail)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Config4_SecondStageDelay)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Config4_LanuchpadLen)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Config4_MainParAlt)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Config3_SecondStageDelay)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Config3_LanuchpadLen)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Config3_MainParAlt)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Config2_SecondStageDelay)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Config2_LanuchpadLen)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Config2_MainParAlt)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Config1_SecondStageDelay)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Config1_LanuchpadLen)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Config1_MainParAlt)).BeginInit();
            this.tabPage_admin.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Admin_Toffset)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Admin_Ha1g)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Admin_A1g)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Admin_Ha0g)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Admin_Z0g)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Admin_Y0g)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Admin_A0g)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_AdminSerial)).BeginInit();
            this.Console.SuspendLayout();
            this.statusStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // label_Battery_V
            // 
            label_Battery_V.AutoSize = true;
            label_Battery_V.Location = new System.Drawing.Point(201, 185);
            label_Battery_V.Name = "label_Battery_V";
            label_Battery_V.Size = new System.Drawing.Size(17, 17);
            label_Battery_V.TabIndex = 8;
            label_Battery_V.Text = "V";
            // 
            // label_Battery
            // 
            label_Battery.AutoSize = true;
            label_Battery.Location = new System.Drawing.Point(40, 182);
            label_Battery.Name = "label_Battery";
            label_Battery.Size = new System.Drawing.Size(53, 17);
            label_Battery.TabIndex = 9;
            label_Battery.Text = "Battery";
            // 
            // label_Angle
            // 
            label_Angle.AutoSize = true;
            label_Angle.Location = new System.Drawing.Point(45, 208);
            label_Angle.Name = "label_Angle";
            label_Angle.Size = new System.Drawing.Size(44, 17);
            label_Angle.TabIndex = 12;
            label_Angle.Text = "Angle";
            // 
            // label2
            // 
            label2.AutoSize = true;
            label2.Location = new System.Drawing.Point(201, 211);
            label2.Name = "label2";
            label2.Size = new System.Drawing.Size(53, 17);
            label2.TabIndex = 11;
            label2.Text = "degree";
            // 
            // label_accX
            // 
            label_accX.AutoSize = true;
            label_accX.Location = new System.Drawing.Point(45, 234);
            label_accX.Name = "label_accX";
            label_accX.Size = new System.Drawing.Size(44, 17);
            label_accX.TabIndex = 15;
            label_accX.Text = "Acc X";
            // 
            // label4
            // 
            label4.AutoSize = true;
            label4.Location = new System.Drawing.Point(201, 237);
            label4.Name = "label4";
            label4.Size = new System.Drawing.Size(16, 17);
            label4.TabIndex = 14;
            label4.Text = "g";
            // 
            // label5
            // 
            label5.AutoSize = true;
            label5.Location = new System.Drawing.Point(45, 260);
            label5.Name = "label5";
            label5.Size = new System.Drawing.Size(44, 17);
            label5.TabIndex = 18;
            label5.Text = "Acc Y";
            // 
            // label6
            // 
            label6.AutoSize = true;
            label6.Location = new System.Drawing.Point(201, 263);
            label6.Name = "label6";
            label6.Size = new System.Drawing.Size(16, 17);
            label6.TabIndex = 17;
            label6.Text = "g";
            // 
            // label7
            // 
            label7.AutoSize = true;
            label7.Location = new System.Drawing.Point(45, 286);
            label7.Name = "label7";
            label7.Size = new System.Drawing.Size(44, 17);
            label7.TabIndex = 21;
            label7.Text = "Acc Z";
            // 
            // label8
            // 
            label8.AutoSize = true;
            label8.Location = new System.Drawing.Point(201, 289);
            label8.Name = "label8";
            label8.Size = new System.Drawing.Size(16, 17);
            label8.TabIndex = 20;
            label8.Text = "g";
            // 
            // label9
            // 
            label9.AutoSize = true;
            label9.Location = new System.Drawing.Point(45, 312);
            label9.Name = "label9";
            label9.Size = new System.Drawing.Size(41, 17);
            label9.TabIndex = 24;
            label9.Text = "HAcc";
            // 
            // label10
            // 
            label10.AutoSize = true;
            label10.Location = new System.Drawing.Point(201, 315);
            label10.Name = "label10";
            label10.Size = new System.Drawing.Size(16, 17);
            label10.TabIndex = 23;
            label10.Text = "g";
            // 
            // label11
            // 
            label11.AutoSize = true;
            label11.Location = new System.Drawing.Point(45, 338);
            label11.Name = "label11";
            label11.Size = new System.Drawing.Size(44, 17);
            label11.TabIndex = 27;
            label11.Text = "Temp";
            // 
            // label12
            // 
            label12.AutoSize = true;
            label12.Location = new System.Drawing.Point(201, 341);
            label12.Name = "label12";
            label12.Size = new System.Drawing.Size(53, 17);
            label12.TabIndex = 26;
            label12.Text = "Celsius";
            // 
            // label13
            // 
            label13.AutoSize = true;
            label13.Location = new System.Drawing.Point(45, 364);
            label13.Name = "label13";
            label13.Size = new System.Drawing.Size(44, 17);
            label13.TabIndex = 30;
            label13.Text = "Press";
            // 
            // label14
            // 
            label14.AutoSize = true;
            label14.Location = new System.Drawing.Point(201, 367);
            label14.Name = "label14";
            label14.Size = new System.Drawing.Size(25, 17);
            label14.TabIndex = 29;
            label14.Text = "Pa";
            // 
            // label_ConfigName
            // 
            label_ConfigName.AutoSize = true;
            label_ConfigName.Location = new System.Drawing.Point(8, 24);
            label_ConfigName.Name = "label_ConfigName";
            label_ConfigName.Size = new System.Drawing.Size(45, 17);
            label_ConfigName.TabIndex = 10;
            label_ConfigName.Text = "Name";
            // 
            // label_ConfigPhone
            // 
            label_ConfigPhone.AutoSize = true;
            label_ConfigPhone.Location = new System.Drawing.Point(8, 52);
            label_ConfigPhone.Name = "label_ConfigPhone";
            label_ConfigPhone.Size = new System.Drawing.Size(49, 17);
            label_ConfigPhone.TabIndex = 11;
            label_ConfigPhone.Text = "Phone";
            // 
            // label_ConfigMainAltitude
            // 
            label_ConfigMainAltitude.AutoSize = true;
            label_ConfigMainAltitude.Location = new System.Drawing.Point(8, 168);
            label_ConfigMainAltitude.Name = "label_ConfigMainAltitude";
            label_ConfigMainAltitude.Size = new System.Drawing.Size(100, 17);
            label_ConfigMainAltitude.TabIndex = 12;
            label_ConfigMainAltitude.Text = "Main chute [m]";
            // 
            // label_ConfigLaunchpadLength
            // 
            label_ConfigLaunchpadLength.AutoSize = true;
            label_ConfigLaunchpadLength.Location = new System.Drawing.Point(8, 191);
            label_ConfigLaunchpadLength.Name = "label_ConfigLaunchpadLength";
            label_ConfigLaunchpadLength.Size = new System.Drawing.Size(150, 17);
            label_ConfigLaunchpadLength.TabIndex = 13;
            label_ConfigLaunchpadLength.Text = "Launchpad Length [m]";
            // 
            // label_ConfigSecondStageDelay
            // 
            label_ConfigSecondStageDelay.AutoSize = true;
            label_ConfigSecondStageDelay.Location = new System.Drawing.Point(8, 220);
            label_ConfigSecondStageDelay.Name = "label_ConfigSecondStageDelay";
            label_ConfigSecondStageDelay.Size = new System.Drawing.Size(156, 17);
            label_ConfigSecondStageDelay.TabIndex = 14;
            label_ConfigSecondStageDelay.Text = "Second Stage Delay [s]";
            // 
            // label_ConfigDragFailureDetector
            // 
            label_ConfigDragFailureDetector.AutoSize = true;
            label_ConfigDragFailureDetector.Location = new System.Drawing.Point(8, 249);
            label_ConfigDragFailureDetector.Name = "label_ConfigDragFailureDetector";
            label_ConfigDragFailureDetector.Size = new System.Drawing.Size(210, 17);
            label_ConfigDragFailureDetector.TabIndex = 15;
            label_ConfigDragFailureDetector.Text = "Drag Chute Failure Detect. [m/s]";
            // 
            // label_Config1
            // 
            label_Config1.AutoSize = true;
            label_Config1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            label_Config1.Location = new System.Drawing.Point(170, 140);
            label_Config1.Name = "label_Config1";
            label_Config1.Size = new System.Drawing.Size(68, 17);
            label_Config1.TabIndex = 32;
            label_Config1.Text = "Config 1";
            // 
            // label_Config2
            // 
            label_Config2.AutoSize = true;
            label_Config2.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            label_Config2.Location = new System.Drawing.Point(255, 140);
            label_Config2.Name = "label_Config2";
            label_Config2.Size = new System.Drawing.Size(68, 17);
            label_Config2.TabIndex = 33;
            label_Config2.Text = "Config 2";
            // 
            // label_Config3
            // 
            label_Config3.AutoSize = true;
            label_Config3.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            label_Config3.Location = new System.Drawing.Point(352, 140);
            label_Config3.Name = "label_Config3";
            label_Config3.Size = new System.Drawing.Size(68, 17);
            label_Config3.TabIndex = 34;
            label_Config3.Text = "Config 3";
            // 
            // label_Config4
            // 
            label_Config4.AutoSize = true;
            label_Config4.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            label_Config4.Location = new System.Drawing.Point(450, 140);
            label_Config4.Name = "label_Config4";
            label_Config4.Size = new System.Drawing.Size(68, 17);
            label_Config4.TabIndex = 35;
            label_Config4.Text = "Config 4";
            // 
            // label_AdminSerialNumber
            // 
            label_AdminSerialNumber.AutoSize = true;
            label_AdminSerialNumber.Location = new System.Drawing.Point(9, 22);
            label_AdminSerialNumber.Name = "label_AdminSerialNumber";
            label_AdminSerialNumber.Size = new System.Drawing.Size(98, 17);
            label_AdminSerialNumber.TabIndex = 14;
            label_AdminSerialNumber.Text = "Serial Number";
            // 
            // label_Admin_A0g
            // 
            label_Admin_A0g.AutoSize = true;
            label_Admin_A0g.Location = new System.Drawing.Point(9, 50);
            label_Admin_A0g.Name = "label_Admin_A0g";
            label_Admin_A0g.Size = new System.Drawing.Size(49, 17);
            label_Admin_A0g.TabIndex = 16;
            label_Admin_A0g.Text = "A_0_g";
            // 
            // label_Admin_Y0g
            // 
            label_Admin_Y0g.AutoSize = true;
            label_Admin_Y0g.Location = new System.Drawing.Point(9, 78);
            label_Admin_Y0g.Name = "label_Admin_Y0g";
            label_Admin_Y0g.Size = new System.Drawing.Size(49, 17);
            label_Admin_Y0g.TabIndex = 18;
            label_Admin_Y0g.Text = "Y_0_g";
            // 
            // label_Admin_Z0g
            // 
            label_Admin_Z0g.AutoSize = true;
            label_Admin_Z0g.Location = new System.Drawing.Point(9, 106);
            label_Admin_Z0g.Name = "label_Admin_Z0g";
            label_Admin_Z0g.Size = new System.Drawing.Size(49, 17);
            label_Admin_Z0g.TabIndex = 20;
            label_Admin_Z0g.Text = "Z_0_g";
            // 
            // label_Admin_Ha0g
            // 
            label_Admin_Ha0g.AutoSize = true;
            label_Admin_Ha0g.Location = new System.Drawing.Point(9, 133);
            label_Admin_Ha0g.Name = "label_Admin_Ha0g";
            label_Admin_Ha0g.Size = new System.Drawing.Size(58, 17);
            label_Admin_Ha0g.TabIndex = 22;
            label_Admin_Ha0g.Text = "Ha_0_g";
            // 
            // label_Admin_A1g
            // 
            label_Admin_A1g.AutoSize = true;
            label_Admin_A1g.Location = new System.Drawing.Point(9, 163);
            label_Admin_A1g.Name = "label_Admin_A1g";
            label_Admin_A1g.Size = new System.Drawing.Size(49, 17);
            label_Admin_A1g.TabIndex = 24;
            label_Admin_A1g.Text = "A_1_g";
            // 
            // label_Admin_Ha1g
            // 
            label_Admin_Ha1g.AutoSize = true;
            label_Admin_Ha1g.Location = new System.Drawing.Point(9, 191);
            label_Admin_Ha1g.Name = "label_Admin_Ha1g";
            label_Admin_Ha1g.Size = new System.Drawing.Size(58, 17);
            label_Admin_Ha1g.TabIndex = 26;
            label_Admin_Ha1g.Text = "Ha_1_g";
            // 
            // label_Admin_Toffset
            // 
            label_Admin_Toffset.AutoSize = true;
            label_Admin_Toffset.Location = new System.Drawing.Point(9, 219);
            label_Admin_Toffset.Name = "label_Admin_Toffset";
            label_Admin_Toffset.Size = new System.Drawing.Size(56, 17);
            label_Admin_Toffset.TabIndex = 16;
            label_Admin_Toffset.Text = "T offset";
            // 
            // label_LSB_aX_0g
            // 
            label_LSB_aX_0g.AutoSize = true;
            label_LSB_aX_0g.Location = new System.Drawing.Point(296, 219);
            label_LSB_aX_0g.Name = "label_LSB_aX_0g";
            label_LSB_aX_0g.Size = new System.Drawing.Size(34, 17);
            label_LSB_aX_0g.TabIndex = 85;
            label_LSB_aX_0g.Text = "LSB";
            // 
            // label1
            // 
            label1.AutoSize = true;
            label1.Location = new System.Drawing.Point(296, 192);
            label1.Name = "label1";
            label1.Size = new System.Drawing.Size(34, 17);
            label1.TabIndex = 86;
            label1.Text = "LSB";
            // 
            // label3
            // 
            label3.AutoSize = true;
            label3.Location = new System.Drawing.Point(296, 165);
            label3.Name = "label3";
            label3.Size = new System.Drawing.Size(34, 17);
            label3.TabIndex = 87;
            label3.Text = "LSB";
            // 
            // label15
            // 
            label15.AutoSize = true;
            label15.Location = new System.Drawing.Point(296, 135);
            label15.Name = "label15";
            label15.Size = new System.Drawing.Size(34, 17);
            label15.TabIndex = 88;
            label15.Text = "LSB";
            // 
            // label16
            // 
            label16.AutoSize = true;
            label16.Location = new System.Drawing.Point(296, 108);
            label16.Name = "label16";
            label16.Size = new System.Drawing.Size(34, 17);
            label16.TabIndex = 89;
            label16.Text = "LSB";
            // 
            // label17
            // 
            label17.AutoSize = true;
            label17.Location = new System.Drawing.Point(296, 80);
            label17.Name = "label17";
            label17.Size = new System.Drawing.Size(34, 17);
            label17.TabIndex = 90;
            label17.Text = "LSB";
            // 
            // label18
            // 
            label18.AutoSize = true;
            label18.Location = new System.Drawing.Point(296, 52);
            label18.Name = "label18";
            label18.Size = new System.Drawing.Size(34, 17);
            label18.TabIndex = 91;
            label18.Text = "LSB";
            // 
            // label_Author
            // 
            label_Author.AutoSize = true;
            label_Author.Location = new System.Drawing.Point(675, 73);
            label_Author.Name = "label_Author";
            label_Author.Size = new System.Drawing.Size(128, 17);
            label_Author.TabIndex = 13;
            label_Author.Text = "by bartekM @ PTR";
            // 
            // label_SpaceConfig
            // 
            label_SpaceConfig.AutoSize = true;
            label_SpaceConfig.Font = new System.Drawing.Font("Microsoft Sans Serif", 26.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            label_SpaceConfig.Location = new System.Drawing.Point(562, 27);
            label_SpaceConfig.Name = "label_SpaceConfig";
            label_SpaceConfig.Size = new System.Drawing.Size(283, 52);
            label_SpaceConfig.TabIndex = 12;
            label_SpaceConfig.Text = "SpaceConfig";
            // 
            // serialPort_USB
            // 
            this.serialPort_USB.BaudRate = 115200;
            this.serialPort_USB.DataReceived += new System.IO.Ports.SerialDataReceivedEventHandler(this.serialPort_USB_DataReceived);
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabPage_liveview);
            this.tabControl1.Controls.Add(this.tabPage_config);
            this.tabControl1.Controls.Add(this.tabPage_logger);
            this.tabControl1.Controls.Add(this.tabPage_admin);
            this.tabControl1.Location = new System.Drawing.Point(0, 2);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(544, 423);
            this.tabControl1.TabIndex = 1;
            // 
            // tabPage_liveview
            // 
            this.tabPage_liveview.Controls.Add(this.button_UnlockIgn);
            this.tabPage_liveview.Controls.Add(this.status_Ign_SecondStage);
            this.tabPage_liveview.Controls.Add(this.status_Ign_Main);
            this.tabPage_liveview.Controls.Add(this.status_Ign_Drag);
            this.tabPage_liveview.Controls.Add(this.button_Ign_All);
            this.tabPage_liveview.Controls.Add(this.button_Ign_SecondStage);
            this.tabPage_liveview.Controls.Add(this.button_Ign_Main);
            this.tabPage_liveview.Controls.Add(this.button_Ign_Drag);
            this.tabPage_liveview.Controls.Add(this.LiveView_OrientationIndicator);
            this.tabPage_liveview.Controls.Add(label13);
            this.tabPage_liveview.Controls.Add(label14);
            this.tabPage_liveview.Controls.Add(this.liveView_Press);
            this.tabPage_liveview.Controls.Add(label11);
            this.tabPage_liveview.Controls.Add(label12);
            this.tabPage_liveview.Controls.Add(this.liveView_Temp);
            this.tabPage_liveview.Controls.Add(label9);
            this.tabPage_liveview.Controls.Add(label10);
            this.tabPage_liveview.Controls.Add(this.liveView_HAcc);
            this.tabPage_liveview.Controls.Add(label7);
            this.tabPage_liveview.Controls.Add(label8);
            this.tabPage_liveview.Controls.Add(this.liveView_AccZ);
            this.tabPage_liveview.Controls.Add(label5);
            this.tabPage_liveview.Controls.Add(label6);
            this.tabPage_liveview.Controls.Add(this.liveView_AccY);
            this.tabPage_liveview.Controls.Add(label_accX);
            this.tabPage_liveview.Controls.Add(label4);
            this.tabPage_liveview.Controls.Add(this.liveView_AccX);
            this.tabPage_liveview.Controls.Add(label_Angle);
            this.tabPage_liveview.Controls.Add(label2);
            this.tabPage_liveview.Controls.Add(this.liveView_Angle);
            this.tabPage_liveview.Controls.Add(label_Battery);
            this.tabPage_liveview.Controls.Add(label_Battery_V);
            this.tabPage_liveview.Controls.Add(this.liveView_Battery);
            this.tabPage_liveview.Location = new System.Drawing.Point(4, 25);
            this.tabPage_liveview.Name = "tabPage_liveview";
            this.tabPage_liveview.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage_liveview.Size = new System.Drawing.Size(536, 394);
            this.tabPage_liveview.TabIndex = 1;
            this.tabPage_liveview.Text = "Live view";
            this.tabPage_liveview.UseVisualStyleBackColor = true;
            this.tabPage_liveview.Click += new System.EventHandler(this.tabPage_liveview_Click);
            // 
            // button_UnlockIgn
            // 
            this.button_UnlockIgn.Location = new System.Drawing.Point(8, 30);
            this.button_UnlockIgn.Name = "button_UnlockIgn";
            this.button_UnlockIgn.Size = new System.Drawing.Size(105, 95);
            this.button_UnlockIgn.TabIndex = 40;
            this.button_UnlockIgn.Text = "Unlock Igniters";
            this.button_UnlockIgn.UseVisualStyleBackColor = true;
            this.button_UnlockIgn.Click += new System.EventHandler(this.button_UnlockIgn_Click);
            // 
            // status_Ign_SecondStage
            // 
            this.status_Ign_SecondStage.BackColor = System.Drawing.Color.Yellow;
            this.status_Ign_SecondStage.Location = new System.Drawing.Point(119, 101);
            this.status_Ign_SecondStage.Name = "status_Ign_SecondStage";
            this.status_Ign_SecondStage.Size = new System.Drawing.Size(96, 23);
            this.status_Ign_SecondStage.TabIndex = 39;
            this.status_Ign_SecondStage.Text = "No Ign";
            this.status_Ign_SecondStage.UseVisualStyleBackColor = false;
            // 
            // status_Ign_Main
            // 
            this.status_Ign_Main.BackColor = System.Drawing.Color.Yellow;
            this.status_Ign_Main.Location = new System.Drawing.Point(119, 65);
            this.status_Ign_Main.Name = "status_Ign_Main";
            this.status_Ign_Main.Size = new System.Drawing.Size(96, 23);
            this.status_Ign_Main.TabIndex = 38;
            this.status_Ign_Main.Text = "No Ign";
            this.status_Ign_Main.UseVisualStyleBackColor = false;
            // 
            // status_Ign_Drag
            // 
            this.status_Ign_Drag.BackColor = System.Drawing.Color.Yellow;
            this.status_Ign_Drag.Location = new System.Drawing.Point(119, 30);
            this.status_Ign_Drag.Name = "status_Ign_Drag";
            this.status_Ign_Drag.Size = new System.Drawing.Size(96, 23);
            this.status_Ign_Drag.TabIndex = 37;
            this.status_Ign_Drag.Text = "No Ign";
            this.status_Ign_Drag.UseVisualStyleBackColor = false;
            // 
            // button_Ign_All
            // 
            this.button_Ign_All.Enabled = false;
            this.button_Ign_All.Location = new System.Drawing.Point(377, 29);
            this.button_Ign_All.Name = "button_Ign_All";
            this.button_Ign_All.Size = new System.Drawing.Size(137, 95);
            this.button_Ign_All.TabIndex = 36;
            this.button_Ign_All.Text = "Trigger ALL";
            this.button_Ign_All.UseVisualStyleBackColor = true;
            this.button_Ign_All.Click += new System.EventHandler(this.button_Ign_All_Click);
            // 
            // button_Ign_SecondStage
            // 
            this.button_Ign_SecondStage.Enabled = false;
            this.button_Ign_SecondStage.Location = new System.Drawing.Point(221, 101);
            this.button_Ign_SecondStage.Name = "button_Ign_SecondStage";
            this.button_Ign_SecondStage.Size = new System.Drawing.Size(132, 23);
            this.button_Ign_SecondStage.TabIndex = 35;
            this.button_Ign_SecondStage.Text = "Second stage";
            this.button_Ign_SecondStage.UseVisualStyleBackColor = true;
            this.button_Ign_SecondStage.Click += new System.EventHandler(this.button_Ign_SecondStage_Click);
            // 
            // button_Ign_Main
            // 
            this.button_Ign_Main.Enabled = false;
            this.button_Ign_Main.Location = new System.Drawing.Point(221, 65);
            this.button_Ign_Main.Name = "button_Ign_Main";
            this.button_Ign_Main.Size = new System.Drawing.Size(132, 23);
            this.button_Ign_Main.TabIndex = 34;
            this.button_Ign_Main.Text = "Mainchute";
            this.button_Ign_Main.UseVisualStyleBackColor = true;
            this.button_Ign_Main.Click += new System.EventHandler(this.button_Ign_Main_Click);
            // 
            // button_Ign_Drag
            // 
            this.button_Ign_Drag.Enabled = false;
            this.button_Ign_Drag.Location = new System.Drawing.Point(221, 29);
            this.button_Ign_Drag.Name = "button_Ign_Drag";
            this.button_Ign_Drag.Size = new System.Drawing.Size(132, 23);
            this.button_Ign_Drag.TabIndex = 33;
            this.button_Ign_Drag.Text = "Dragchute";
            this.button_Ign_Drag.UseVisualStyleBackColor = true;
            this.button_Ign_Drag.Click += new System.EventHandler(this.button_Ign_Drag_Click);
            // 
            // LiveView_OrientationIndicator
            // 
            this.LiveView_OrientationIndicator.Image = ((System.Drawing.Image)(resources.GetObject("LiveView_OrientationIndicator.Image")));
            this.LiveView_OrientationIndicator.Location = new System.Drawing.Point(306, 175);
            this.LiveView_OrientationIndicator.Name = "LiveView_OrientationIndicator";
            this.LiveView_OrientationIndicator.Size = new System.Drawing.Size(224, 209);
            this.LiveView_OrientationIndicator.SizeMode = System.Windows.Forms.PictureBoxSizeMode.Zoom;
            this.LiveView_OrientationIndicator.TabIndex = 32;
            this.LiveView_OrientationIndicator.TabStop = false;
            // 
            // liveView_Press
            // 
            this.liveView_Press.Location = new System.Drawing.Point(94, 361);
            this.liveView_Press.Name = "liveView_Press";
            this.liveView_Press.Size = new System.Drawing.Size(100, 22);
            this.liveView_Press.TabIndex = 28;
            // 
            // liveView_Temp
            // 
            this.liveView_Temp.Location = new System.Drawing.Point(94, 335);
            this.liveView_Temp.Name = "liveView_Temp";
            this.liveView_Temp.Size = new System.Drawing.Size(100, 22);
            this.liveView_Temp.TabIndex = 25;
            // 
            // liveView_HAcc
            // 
            this.liveView_HAcc.Location = new System.Drawing.Point(94, 309);
            this.liveView_HAcc.Name = "liveView_HAcc";
            this.liveView_HAcc.Size = new System.Drawing.Size(100, 22);
            this.liveView_HAcc.TabIndex = 22;
            // 
            // liveView_AccZ
            // 
            this.liveView_AccZ.Location = new System.Drawing.Point(94, 283);
            this.liveView_AccZ.Name = "liveView_AccZ";
            this.liveView_AccZ.Size = new System.Drawing.Size(100, 22);
            this.liveView_AccZ.TabIndex = 19;
            // 
            // liveView_AccY
            // 
            this.liveView_AccY.Location = new System.Drawing.Point(94, 257);
            this.liveView_AccY.Name = "liveView_AccY";
            this.liveView_AccY.Size = new System.Drawing.Size(100, 22);
            this.liveView_AccY.TabIndex = 16;
            // 
            // liveView_AccX
            // 
            this.liveView_AccX.Location = new System.Drawing.Point(94, 231);
            this.liveView_AccX.Name = "liveView_AccX";
            this.liveView_AccX.Size = new System.Drawing.Size(100, 22);
            this.liveView_AccX.TabIndex = 13;
            // 
            // liveView_Angle
            // 
            this.liveView_Angle.Location = new System.Drawing.Point(94, 205);
            this.liveView_Angle.Name = "liveView_Angle";
            this.liveView_Angle.Size = new System.Drawing.Size(100, 22);
            this.liveView_Angle.TabIndex = 10;
            // 
            // liveView_Battery
            // 
            this.liveView_Battery.Location = new System.Drawing.Point(94, 179);
            this.liveView_Battery.Name = "liveView_Battery";
            this.liveView_Battery.Size = new System.Drawing.Size(100, 22);
            this.liveView_Battery.TabIndex = 7;
            // 
            // tabPage_config
            // 
            this.tabPage_config.Controls.Add(this.numeric_Config4_DragFail);
            this.tabPage_config.Controls.Add(this.numeric_Config3_DragFail);
            this.tabPage_config.Controls.Add(this.numeric_Config2_DragFail);
            this.tabPage_config.Controls.Add(this.numeric_Config1_DragFail);
            this.tabPage_config.Controls.Add(this.numeric_Config4_SecondStageDelay);
            this.tabPage_config.Controls.Add(this.numeric_Config4_LanuchpadLen);
            this.tabPage_config.Controls.Add(this.numeric_Config4_MainParAlt);
            this.tabPage_config.Controls.Add(this.numeric_Config3_SecondStageDelay);
            this.tabPage_config.Controls.Add(this.numeric_Config3_LanuchpadLen);
            this.tabPage_config.Controls.Add(this.numeric_Config3_MainParAlt);
            this.tabPage_config.Controls.Add(this.numeric_Config2_SecondStageDelay);
            this.tabPage_config.Controls.Add(this.numeric_Config2_LanuchpadLen);
            this.tabPage_config.Controls.Add(this.numeric_Config2_MainParAlt);
            this.tabPage_config.Controls.Add(this.numeric_Config1_SecondStageDelay);
            this.tabPage_config.Controls.Add(this.numeric_Config1_LanuchpadLen);
            this.tabPage_config.Controls.Add(this.numeric_Config1_MainParAlt);
            this.tabPage_config.Controls.Add(label_Config4);
            this.tabPage_config.Controls.Add(label_Config3);
            this.tabPage_config.Controls.Add(label_Config2);
            this.tabPage_config.Controls.Add(label_Config1);
            this.tabPage_config.Controls.Add(label_ConfigDragFailureDetector);
            this.tabPage_config.Controls.Add(label_ConfigSecondStageDelay);
            this.tabPage_config.Controls.Add(label_ConfigLaunchpadLength);
            this.tabPage_config.Controls.Add(label_ConfigMainAltitude);
            this.tabPage_config.Controls.Add(label_ConfigPhone);
            this.tabPage_config.Controls.Add(label_ConfigName);
            this.tabPage_config.Controls.Add(this.text_ConfigPhone);
            this.tabPage_config.Controls.Add(this.text_ConfigName);
            this.tabPage_config.Controls.Add(this.button_ConfigRead);
            this.tabPage_config.Controls.Add(this.button_ConfigRestoreDefault);
            this.tabPage_config.Controls.Add(this.button_ConfigSave);
            this.tabPage_config.Location = new System.Drawing.Point(4, 25);
            this.tabPage_config.Name = "tabPage_config";
            this.tabPage_config.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage_config.Size = new System.Drawing.Size(536, 394);
            this.tabPage_config.TabIndex = 2;
            this.tabPage_config.Text = "Configuration";
            this.tabPage_config.UseVisualStyleBackColor = true;
            // 
            // numeric_Config4_DragFail
            // 
            this.numeric_Config4_DragFail.Location = new System.Drawing.Point(453, 247);
            this.numeric_Config4_DragFail.Name = "numeric_Config4_DragFail";
            this.numeric_Config4_DragFail.Size = new System.Drawing.Size(75, 22);
            this.numeric_Config4_DragFail.TabIndex = 86;
            this.numeric_Config4_DragFail.ThousandsSeparator = true;
            this.numeric_Config4_DragFail.ValueChanged += new System.EventHandler(this.numeric_Config4_DragFail_ValueChanged);
            // 
            // numeric_Config3_DragFail
            // 
            this.numeric_Config3_DragFail.Location = new System.Drawing.Point(359, 247);
            this.numeric_Config3_DragFail.Name = "numeric_Config3_DragFail";
            this.numeric_Config3_DragFail.Size = new System.Drawing.Size(76, 22);
            this.numeric_Config3_DragFail.TabIndex = 85;
            this.numeric_Config3_DragFail.ThousandsSeparator = true;
            this.numeric_Config3_DragFail.ValueChanged += new System.EventHandler(this.numeric_Config3_DragFail_ValueChanged);
            // 
            // numeric_Config2_DragFail
            // 
            this.numeric_Config2_DragFail.Location = new System.Drawing.Point(266, 247);
            this.numeric_Config2_DragFail.Name = "numeric_Config2_DragFail";
            this.numeric_Config2_DragFail.Size = new System.Drawing.Size(75, 22);
            this.numeric_Config2_DragFail.TabIndex = 84;
            this.numeric_Config2_DragFail.ThousandsSeparator = true;
            this.numeric_Config2_DragFail.ValueChanged += new System.EventHandler(this.numeric_Config2_DragFail_ValueChanged);
            // 
            // numeric_Config1_DragFail
            // 
            this.numeric_Config1_DragFail.Location = new System.Drawing.Point(173, 246);
            this.numeric_Config1_DragFail.Name = "numeric_Config1_DragFail";
            this.numeric_Config1_DragFail.Size = new System.Drawing.Size(75, 22);
            this.numeric_Config1_DragFail.TabIndex = 83;
            this.numeric_Config1_DragFail.ThousandsSeparator = true;
            this.numeric_Config1_DragFail.ValueChanged += new System.EventHandler(this.numeric_Config1_DragFail_ValueChanged);
            // 
            // numeric_Config4_SecondStageDelay
            // 
            this.numeric_Config4_SecondStageDelay.DecimalPlaces = 1;
            this.numeric_Config4_SecondStageDelay.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.numeric_Config4_SecondStageDelay.Location = new System.Drawing.Point(453, 219);
            this.numeric_Config4_SecondStageDelay.Maximum = new decimal(new int[] {
            600,
            0,
            0,
            0});
            this.numeric_Config4_SecondStageDelay.Name = "numeric_Config4_SecondStageDelay";
            this.numeric_Config4_SecondStageDelay.Size = new System.Drawing.Size(75, 22);
            this.numeric_Config4_SecondStageDelay.TabIndex = 82;
            this.numeric_Config4_SecondStageDelay.ThousandsSeparator = true;
            this.numeric_Config4_SecondStageDelay.ValueChanged += new System.EventHandler(this.numeric_Config4_SecondStageDelay_ValueChanged);
            // 
            // numeric_Config4_LanuchpadLen
            // 
            this.numeric_Config4_LanuchpadLen.DecimalPlaces = 1;
            this.numeric_Config4_LanuchpadLen.Location = new System.Drawing.Point(453, 193);
            this.numeric_Config4_LanuchpadLen.Maximum = new decimal(new int[] {
            20,
            0,
            0,
            0});
            this.numeric_Config4_LanuchpadLen.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numeric_Config4_LanuchpadLen.Name = "numeric_Config4_LanuchpadLen";
            this.numeric_Config4_LanuchpadLen.Size = new System.Drawing.Size(75, 22);
            this.numeric_Config4_LanuchpadLen.TabIndex = 81;
            this.numeric_Config4_LanuchpadLen.ThousandsSeparator = true;
            this.numeric_Config4_LanuchpadLen.Value = new decimal(new int[] {
            2,
            0,
            0,
            0});
            this.numeric_Config4_LanuchpadLen.ValueChanged += new System.EventHandler(this.numeric_Config4_LanuchpadLen_ValueChanged);
            // 
            // numeric_Config4_MainParAlt
            // 
            this.numeric_Config4_MainParAlt.Increment = new decimal(new int[] {
            50,
            0,
            0,
            0});
            this.numeric_Config4_MainParAlt.Location = new System.Drawing.Point(453, 166);
            this.numeric_Config4_MainParAlt.Maximum = new decimal(new int[] {
            100000,
            0,
            0,
            0});
            this.numeric_Config4_MainParAlt.Name = "numeric_Config4_MainParAlt";
            this.numeric_Config4_MainParAlt.Size = new System.Drawing.Size(75, 22);
            this.numeric_Config4_MainParAlt.TabIndex = 80;
            this.numeric_Config4_MainParAlt.ThousandsSeparator = true;
            this.numeric_Config4_MainParAlt.Value = new decimal(new int[] {
            200,
            0,
            0,
            0});
            this.numeric_Config4_MainParAlt.ValueChanged += new System.EventHandler(this.numeric_Config4_MainParAlt_ValueChanged);
            // 
            // numeric_Config3_SecondStageDelay
            // 
            this.numeric_Config3_SecondStageDelay.DecimalPlaces = 1;
            this.numeric_Config3_SecondStageDelay.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.numeric_Config3_SecondStageDelay.Location = new System.Drawing.Point(359, 219);
            this.numeric_Config3_SecondStageDelay.Maximum = new decimal(new int[] {
            600,
            0,
            0,
            0});
            this.numeric_Config3_SecondStageDelay.Name = "numeric_Config3_SecondStageDelay";
            this.numeric_Config3_SecondStageDelay.Size = new System.Drawing.Size(76, 22);
            this.numeric_Config3_SecondStageDelay.TabIndex = 78;
            this.numeric_Config3_SecondStageDelay.ThousandsSeparator = true;
            this.numeric_Config3_SecondStageDelay.ValueChanged += new System.EventHandler(this.numeric_Config3_SecondStageDelay_ValueChanged);
            // 
            // numeric_Config3_LanuchpadLen
            // 
            this.numeric_Config3_LanuchpadLen.DecimalPlaces = 1;
            this.numeric_Config3_LanuchpadLen.Location = new System.Drawing.Point(359, 193);
            this.numeric_Config3_LanuchpadLen.Maximum = new decimal(new int[] {
            20,
            0,
            0,
            0});
            this.numeric_Config3_LanuchpadLen.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numeric_Config3_LanuchpadLen.Name = "numeric_Config3_LanuchpadLen";
            this.numeric_Config3_LanuchpadLen.Size = new System.Drawing.Size(76, 22);
            this.numeric_Config3_LanuchpadLen.TabIndex = 77;
            this.numeric_Config3_LanuchpadLen.ThousandsSeparator = true;
            this.numeric_Config3_LanuchpadLen.Value = new decimal(new int[] {
            2,
            0,
            0,
            0});
            this.numeric_Config3_LanuchpadLen.ValueChanged += new System.EventHandler(this.numeric_Config3_LanuchpadLen_ValueChanged);
            // 
            // numeric_Config3_MainParAlt
            // 
            this.numeric_Config3_MainParAlt.Increment = new decimal(new int[] {
            50,
            0,
            0,
            0});
            this.numeric_Config3_MainParAlt.Location = new System.Drawing.Point(359, 166);
            this.numeric_Config3_MainParAlt.Maximum = new decimal(new int[] {
            100000,
            0,
            0,
            0});
            this.numeric_Config3_MainParAlt.Name = "numeric_Config3_MainParAlt";
            this.numeric_Config3_MainParAlt.Size = new System.Drawing.Size(76, 22);
            this.numeric_Config3_MainParAlt.TabIndex = 76;
            this.numeric_Config3_MainParAlt.ThousandsSeparator = true;
            this.numeric_Config3_MainParAlt.Value = new decimal(new int[] {
            200,
            0,
            0,
            0});
            this.numeric_Config3_MainParAlt.ValueChanged += new System.EventHandler(this.numeric_Config3_MainParAlt_ValueChanged);
            // 
            // numeric_Config2_SecondStageDelay
            // 
            this.numeric_Config2_SecondStageDelay.DecimalPlaces = 1;
            this.numeric_Config2_SecondStageDelay.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.numeric_Config2_SecondStageDelay.Location = new System.Drawing.Point(266, 219);
            this.numeric_Config2_SecondStageDelay.Maximum = new decimal(new int[] {
            600,
            0,
            0,
            0});
            this.numeric_Config2_SecondStageDelay.Name = "numeric_Config2_SecondStageDelay";
            this.numeric_Config2_SecondStageDelay.Size = new System.Drawing.Size(75, 22);
            this.numeric_Config2_SecondStageDelay.TabIndex = 74;
            this.numeric_Config2_SecondStageDelay.ThousandsSeparator = true;
            this.numeric_Config2_SecondStageDelay.ValueChanged += new System.EventHandler(this.numeric_Config2_SecondStageDelay_ValueChanged);
            // 
            // numeric_Config2_LanuchpadLen
            // 
            this.numeric_Config2_LanuchpadLen.DecimalPlaces = 1;
            this.numeric_Config2_LanuchpadLen.Location = new System.Drawing.Point(266, 193);
            this.numeric_Config2_LanuchpadLen.Maximum = new decimal(new int[] {
            20,
            0,
            0,
            0});
            this.numeric_Config2_LanuchpadLen.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numeric_Config2_LanuchpadLen.Name = "numeric_Config2_LanuchpadLen";
            this.numeric_Config2_LanuchpadLen.Size = new System.Drawing.Size(75, 22);
            this.numeric_Config2_LanuchpadLen.TabIndex = 73;
            this.numeric_Config2_LanuchpadLen.ThousandsSeparator = true;
            this.numeric_Config2_LanuchpadLen.Value = new decimal(new int[] {
            2,
            0,
            0,
            0});
            this.numeric_Config2_LanuchpadLen.ValueChanged += new System.EventHandler(this.numeric_Config2_LanuchpadLen_ValueChanged);
            // 
            // numeric_Config2_MainParAlt
            // 
            this.numeric_Config2_MainParAlt.Increment = new decimal(new int[] {
            50,
            0,
            0,
            0});
            this.numeric_Config2_MainParAlt.Location = new System.Drawing.Point(266, 166);
            this.numeric_Config2_MainParAlt.Maximum = new decimal(new int[] {
            100000,
            0,
            0,
            0});
            this.numeric_Config2_MainParAlt.Name = "numeric_Config2_MainParAlt";
            this.numeric_Config2_MainParAlt.Size = new System.Drawing.Size(75, 22);
            this.numeric_Config2_MainParAlt.TabIndex = 72;
            this.numeric_Config2_MainParAlt.ThousandsSeparator = true;
            this.numeric_Config2_MainParAlt.Value = new decimal(new int[] {
            200,
            0,
            0,
            0});
            this.numeric_Config2_MainParAlt.ValueChanged += new System.EventHandler(this.numeric_Config2_MainParAlt_ValueChanged);
            // 
            // numeric_Config1_SecondStageDelay
            // 
            this.numeric_Config1_SecondStageDelay.DecimalPlaces = 1;
            this.numeric_Config1_SecondStageDelay.Increment = new decimal(new int[] {
            1,
            0,
            0,
            65536});
            this.numeric_Config1_SecondStageDelay.Location = new System.Drawing.Point(173, 218);
            this.numeric_Config1_SecondStageDelay.Maximum = new decimal(new int[] {
            600,
            0,
            0,
            0});
            this.numeric_Config1_SecondStageDelay.Name = "numeric_Config1_SecondStageDelay";
            this.numeric_Config1_SecondStageDelay.Size = new System.Drawing.Size(75, 22);
            this.numeric_Config1_SecondStageDelay.TabIndex = 70;
            this.numeric_Config1_SecondStageDelay.ThousandsSeparator = true;
            this.numeric_Config1_SecondStageDelay.ValueChanged += new System.EventHandler(this.numeric_Config1_SecondStageDelay_ValueChanged);
            // 
            // numeric_Config1_LanuchpadLen
            // 
            this.numeric_Config1_LanuchpadLen.DecimalPlaces = 1;
            this.numeric_Config1_LanuchpadLen.Location = new System.Drawing.Point(173, 192);
            this.numeric_Config1_LanuchpadLen.Maximum = new decimal(new int[] {
            20,
            0,
            0,
            0});
            this.numeric_Config1_LanuchpadLen.Minimum = new decimal(new int[] {
            1,
            0,
            0,
            0});
            this.numeric_Config1_LanuchpadLen.Name = "numeric_Config1_LanuchpadLen";
            this.numeric_Config1_LanuchpadLen.Size = new System.Drawing.Size(75, 22);
            this.numeric_Config1_LanuchpadLen.TabIndex = 69;
            this.numeric_Config1_LanuchpadLen.ThousandsSeparator = true;
            this.numeric_Config1_LanuchpadLen.Value = new decimal(new int[] {
            2,
            0,
            0,
            0});
            this.numeric_Config1_LanuchpadLen.ValueChanged += new System.EventHandler(this.numeric_Config1_LanuchpadLen_ValueChanged);
            // 
            // numeric_Config1_MainParAlt
            // 
            this.numeric_Config1_MainParAlt.Increment = new decimal(new int[] {
            50,
            0,
            0,
            0});
            this.numeric_Config1_MainParAlt.Location = new System.Drawing.Point(173, 165);
            this.numeric_Config1_MainParAlt.Maximum = new decimal(new int[] {
            100000,
            0,
            0,
            0});
            this.numeric_Config1_MainParAlt.Name = "numeric_Config1_MainParAlt";
            this.numeric_Config1_MainParAlt.Size = new System.Drawing.Size(75, 22);
            this.numeric_Config1_MainParAlt.TabIndex = 68;
            this.numeric_Config1_MainParAlt.ThousandsSeparator = true;
            this.numeric_Config1_MainParAlt.Value = new decimal(new int[] {
            200,
            0,
            0,
            0});
            this.numeric_Config1_MainParAlt.ValueChanged += new System.EventHandler(this.numeric_Config1_MainParAlt_ValueChanged);
            // 
            // text_ConfigPhone
            // 
            this.text_ConfigPhone.Location = new System.Drawing.Point(72, 49);
            this.text_ConfigPhone.Name = "text_ConfigPhone";
            this.text_ConfigPhone.Size = new System.Drawing.Size(442, 22);
            this.text_ConfigPhone.TabIndex = 10;
            this.text_ConfigPhone.TextChanged += new System.EventHandler(this.text_ConfigPhone_TextChanged);
            // 
            // text_ConfigName
            // 
            this.text_ConfigName.Location = new System.Drawing.Point(72, 21);
            this.text_ConfigName.Name = "text_ConfigName";
            this.text_ConfigName.Size = new System.Drawing.Size(442, 22);
            this.text_ConfigName.TabIndex = 9;
            this.text_ConfigName.TextChanged += new System.EventHandler(this.text_ConfigName_TextChanged);
            // 
            // button_ConfigRead
            // 
            this.button_ConfigRead.Location = new System.Drawing.Point(199, 323);
            this.button_ConfigRead.Name = "button_ConfigRead";
            this.button_ConfigRead.Size = new System.Drawing.Size(133, 52);
            this.button_ConfigRead.TabIndex = 8;
            this.button_ConfigRead.Text = "Get from EEPROM";
            this.button_ConfigRead.UseVisualStyleBackColor = true;
            this.button_ConfigRead.Click += new System.EventHandler(this.button_ConfigRead_Click);
            // 
            // button_ConfigRestoreDefault
            // 
            this.button_ConfigRestoreDefault.Location = new System.Drawing.Point(8, 323);
            this.button_ConfigRestoreDefault.Name = "button_ConfigRestoreDefault";
            this.button_ConfigRestoreDefault.Size = new System.Drawing.Size(133, 52);
            this.button_ConfigRestoreDefault.TabIndex = 6;
            this.button_ConfigRestoreDefault.Text = "Restore Default";
            this.button_ConfigRestoreDefault.UseVisualStyleBackColor = true;
            this.button_ConfigRestoreDefault.Click += new System.EventHandler(this.button_ConfigRestoreDefault_Click);
            // 
            // button_ConfigSave
            // 
            this.button_ConfigSave.Location = new System.Drawing.Point(397, 323);
            this.button_ConfigSave.Name = "button_ConfigSave";
            this.button_ConfigSave.Size = new System.Drawing.Size(133, 52);
            this.button_ConfigSave.TabIndex = 5;
            this.button_ConfigSave.Text = "Save to EEPROM";
            this.button_ConfigSave.UseVisualStyleBackColor = true;
            this.button_ConfigSave.Click += new System.EventHandler(this.button_ConfigSave_Click);
            // 
            // tabPage_logger
            // 
            this.tabPage_logger.Location = new System.Drawing.Point(4, 25);
            this.tabPage_logger.Name = "tabPage_logger";
            this.tabPage_logger.Padding = new System.Windows.Forms.Padding(3);
            this.tabPage_logger.Size = new System.Drawing.Size(536, 394);
            this.tabPage_logger.TabIndex = 3;
            this.tabPage_logger.Text = "Logger";
            this.tabPage_logger.UseVisualStyleBackColor = true;
            // 
            // tabPage_admin
            // 
            this.tabPage_admin.Controls.Add(this.button_CalibrationWizard);
            this.tabPage_admin.Controls.Add(this.button_SerialNumber_Increase);
            this.tabPage_admin.Controls.Add(label18);
            this.tabPage_admin.Controls.Add(label17);
            this.tabPage_admin.Controls.Add(label16);
            this.tabPage_admin.Controls.Add(label15);
            this.tabPage_admin.Controls.Add(label3);
            this.tabPage_admin.Controls.Add(label1);
            this.tabPage_admin.Controls.Add(label_LSB_aX_0g);
            this.tabPage_admin.Controls.Add(this.numeric_Admin_Toffset);
            this.tabPage_admin.Controls.Add(this.numeric_Admin_Ha1g);
            this.tabPage_admin.Controls.Add(this.numeric_Admin_A1g);
            this.tabPage_admin.Controls.Add(this.numeric_Admin_Ha0g);
            this.tabPage_admin.Controls.Add(this.numeric_Admin_Z0g);
            this.tabPage_admin.Controls.Add(this.numeric_Admin_Y0g);
            this.tabPage_admin.Controls.Add(this.numeric_Admin_A0g);
            this.tabPage_admin.Controls.Add(this.numeric_AdminSerial);
            this.tabPage_admin.Controls.Add(label_Admin_Toffset);
            this.tabPage_admin.Controls.Add(label_Admin_Ha1g);
            this.tabPage_admin.Controls.Add(label_Admin_A1g);
            this.tabPage_admin.Controls.Add(label_Admin_Ha0g);
            this.tabPage_admin.Controls.Add(label_Admin_Z0g);
            this.tabPage_admin.Controls.Add(label_Admin_Y0g);
            this.tabPage_admin.Controls.Add(label_Admin_A0g);
            this.tabPage_admin.Controls.Add(label_AdminSerialNumber);
            this.tabPage_admin.Controls.Add(this.button_AdminRead);
            this.tabPage_admin.Controls.Add(this.button_AdminSave);
            this.tabPage_admin.Location = new System.Drawing.Point(4, 25);
            this.tabPage_admin.Name = "tabPage_admin";
            this.tabPage_admin.Size = new System.Drawing.Size(536, 394);
            this.tabPage_admin.TabIndex = 4;
            this.tabPage_admin.Text = "Admin";
            this.tabPage_admin.UseVisualStyleBackColor = true;
            // 
            // button_CalibrationWizard
            // 
            this.button_CalibrationWizard.Location = new System.Drawing.Point(351, 106);
            this.button_CalibrationWizard.Name = "button_CalibrationWizard";
            this.button_CalibrationWizard.Size = new System.Drawing.Size(133, 52);
            this.button_CalibrationWizard.TabIndex = 93;
            this.button_CalibrationWizard.Text = "Calibration wizard";
            this.button_CalibrationWizard.UseVisualStyleBackColor = true;
            this.button_CalibrationWizard.Click += new System.EventHandler(this.button_CalibrationWizard_Click);
            // 
            // button_SerialNumber_Increase
            // 
            this.button_SerialNumber_Increase.Location = new System.Drawing.Point(298, 19);
            this.button_SerialNumber_Increase.Name = "button_SerialNumber_Increase";
            this.button_SerialNumber_Increase.Size = new System.Drawing.Size(173, 23);
            this.button_SerialNumber_Increase.TabIndex = 92;
            this.button_SerialNumber_Increase.Text = "Increase";
            this.button_SerialNumber_Increase.UseVisualStyleBackColor = true;
            this.button_SerialNumber_Increase.Click += new System.EventHandler(this.button_SerialNumber_Increase_Click);
            // 
            // numeric_Admin_Toffset
            // 
            this.numeric_Admin_Toffset.Location = new System.Drawing.Point(113, 217);
            this.numeric_Admin_Toffset.Maximum = new decimal(new int[] {
            32767,
            0,
            0,
            0});
            this.numeric_Admin_Toffset.Minimum = new decimal(new int[] {
            32767,
            0,
            0,
            -2147483648});
            this.numeric_Admin_Toffset.Name = "numeric_Admin_Toffset";
            this.numeric_Admin_Toffset.Size = new System.Drawing.Size(173, 22);
            this.numeric_Admin_Toffset.TabIndex = 34;
            this.numeric_Admin_Toffset.ValueChanged += new System.EventHandler(this.numeric_Admin_Toffset_ValueChanged);
            // 
            // numeric_Admin_Ha1g
            // 
            this.numeric_Admin_Ha1g.Location = new System.Drawing.Point(113, 189);
            this.numeric_Admin_Ha1g.Maximum = new decimal(new int[] {
            32767,
            0,
            0,
            0});
            this.numeric_Admin_Ha1g.Minimum = new decimal(new int[] {
            32767,
            0,
            0,
            -2147483648});
            this.numeric_Admin_Ha1g.Name = "numeric_Admin_Ha1g";
            this.numeric_Admin_Ha1g.Size = new System.Drawing.Size(173, 22);
            this.numeric_Admin_Ha1g.TabIndex = 33;
            this.numeric_Admin_Ha1g.ValueChanged += new System.EventHandler(this.numeric_Admin_Ha1g_ValueChanged);
            // 
            // numeric_Admin_A1g
            // 
            this.numeric_Admin_A1g.Location = new System.Drawing.Point(113, 161);
            this.numeric_Admin_A1g.Maximum = new decimal(new int[] {
            32767,
            0,
            0,
            0});
            this.numeric_Admin_A1g.Minimum = new decimal(new int[] {
            32767,
            0,
            0,
            -2147483648});
            this.numeric_Admin_A1g.Name = "numeric_Admin_A1g";
            this.numeric_Admin_A1g.Size = new System.Drawing.Size(173, 22);
            this.numeric_Admin_A1g.TabIndex = 32;
            this.numeric_Admin_A1g.ValueChanged += new System.EventHandler(this.numeric_Admin_A1g_ValueChanged);
            // 
            // numeric_Admin_Ha0g
            // 
            this.numeric_Admin_Ha0g.Location = new System.Drawing.Point(113, 131);
            this.numeric_Admin_Ha0g.Maximum = new decimal(new int[] {
            32767,
            0,
            0,
            0});
            this.numeric_Admin_Ha0g.Minimum = new decimal(new int[] {
            32767,
            0,
            0,
            -2147483648});
            this.numeric_Admin_Ha0g.Name = "numeric_Admin_Ha0g";
            this.numeric_Admin_Ha0g.Size = new System.Drawing.Size(173, 22);
            this.numeric_Admin_Ha0g.TabIndex = 31;
            this.numeric_Admin_Ha0g.ValueChanged += new System.EventHandler(this.numeric_Admin_Ha0g_ValueChanged);
            // 
            // numeric_Admin_Z0g
            // 
            this.numeric_Admin_Z0g.Location = new System.Drawing.Point(113, 104);
            this.numeric_Admin_Z0g.Maximum = new decimal(new int[] {
            32767,
            0,
            0,
            0});
            this.numeric_Admin_Z0g.Minimum = new decimal(new int[] {
            32767,
            0,
            0,
            -2147483648});
            this.numeric_Admin_Z0g.Name = "numeric_Admin_Z0g";
            this.numeric_Admin_Z0g.Size = new System.Drawing.Size(173, 22);
            this.numeric_Admin_Z0g.TabIndex = 30;
            this.numeric_Admin_Z0g.ValueChanged += new System.EventHandler(this.numeric_Admin_Z0g_ValueChanged);
            // 
            // numeric_Admin_Y0g
            // 
            this.numeric_Admin_Y0g.Location = new System.Drawing.Point(113, 76);
            this.numeric_Admin_Y0g.Maximum = new decimal(new int[] {
            32767,
            0,
            0,
            0});
            this.numeric_Admin_Y0g.Minimum = new decimal(new int[] {
            32767,
            0,
            0,
            -2147483648});
            this.numeric_Admin_Y0g.Name = "numeric_Admin_Y0g";
            this.numeric_Admin_Y0g.Size = new System.Drawing.Size(173, 22);
            this.numeric_Admin_Y0g.TabIndex = 29;
            this.numeric_Admin_Y0g.ValueChanged += new System.EventHandler(this.numeric_Admin_Y0g_ValueChanged);
            // 
            // numeric_Admin_A0g
            // 
            this.numeric_Admin_A0g.Location = new System.Drawing.Point(113, 48);
            this.numeric_Admin_A0g.Maximum = new decimal(new int[] {
            32767,
            0,
            0,
            0});
            this.numeric_Admin_A0g.Minimum = new decimal(new int[] {
            32767,
            0,
            0,
            -2147483648});
            this.numeric_Admin_A0g.Name = "numeric_Admin_A0g";
            this.numeric_Admin_A0g.Size = new System.Drawing.Size(173, 22);
            this.numeric_Admin_A0g.TabIndex = 28;
            this.numeric_Admin_A0g.ValueChanged += new System.EventHandler(this.numeric_Admin_A0g_ValueChanged);
            // 
            // numeric_AdminSerial
            // 
            this.numeric_AdminSerial.Location = new System.Drawing.Point(113, 20);
            this.numeric_AdminSerial.Maximum = new decimal(new int[] {
            65534,
            0,
            0,
            0});
            this.numeric_AdminSerial.Name = "numeric_AdminSerial";
            this.numeric_AdminSerial.Size = new System.Drawing.Size(173, 22);
            this.numeric_AdminSerial.TabIndex = 27;
            this.numeric_AdminSerial.Value = new decimal(new int[] {
            10000,
            0,
            0,
            0});
            this.numeric_AdminSerial.ValueChanged += new System.EventHandler(this.numeric_AdminSerial_ValueChanged);
            // 
            // button_AdminRead
            // 
            this.button_AdminRead.Location = new System.Drawing.Point(109, 323);
            this.button_AdminRead.Name = "button_AdminRead";
            this.button_AdminRead.Size = new System.Drawing.Size(133, 52);
            this.button_AdminRead.TabIndex = 12;
            this.button_AdminRead.Text = "Get from EEPROM";
            this.button_AdminRead.UseVisualStyleBackColor = true;
            this.button_AdminRead.Click += new System.EventHandler(this.button_AdminRead_Click);
            // 
            // button_AdminSave
            // 
            this.button_AdminSave.Location = new System.Drawing.Point(307, 323);
            this.button_AdminSave.Name = "button_AdminSave";
            this.button_AdminSave.Size = new System.Drawing.Size(133, 52);
            this.button_AdminSave.TabIndex = 11;
            this.button_AdminSave.Text = "Save to EEPROM";
            this.button_AdminSave.UseVisualStyleBackColor = true;
            this.button_AdminSave.Click += new System.EventHandler(this.button_AdminSave_Click);
            // 
            // Console
            // 
            this.Console.Controls.Add(this.Console_textbox);
            this.Console.Location = new System.Drawing.Point(546, 235);
            this.Console.Name = "Console";
            this.Console.Size = new System.Drawing.Size(254, 186);
            this.Console.TabIndex = 2;
            this.Console.TabStop = false;
            this.Console.Text = "Console";
            // 
            // Console_textbox
            // 
            this.Console_textbox.Location = new System.Drawing.Point(14, 20);
            this.Console_textbox.Multiline = true;
            this.Console_textbox.Name = "Console_textbox";
            this.Console_textbox.Size = new System.Drawing.Size(228, 166);
            this.Console_textbox.TabIndex = 0;
            // 
            // progressBar1
            // 
            this.progressBar1.Location = new System.Drawing.Point(560, 428);
            this.progressBar1.Name = "progressBar1";
            this.progressBar1.Size = new System.Drawing.Size(214, 22);
            this.progressBar1.TabIndex = 0;
            // 
            // button_USBconnect
            // 
            this.button_USBconnect.Location = new System.Drawing.Point(560, 128);
            this.button_USBconnect.Name = "button_USBconnect";
            this.button_USBconnect.Size = new System.Drawing.Size(133, 23);
            this.button_USBconnect.TabIndex = 3;
            this.button_USBconnect.Text = "Connect...";
            this.button_USBconnect.UseVisualStyleBackColor = true;
            this.button_USBconnect.Click += new System.EventHandler(this.button_USBconnect_Click);
            // 
            // statusStrip1
            // 
            this.statusStrip1.ImageScalingSize = new System.Drawing.Size(20, 20);
            this.statusStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.status_SerialNumber});
            this.statusStrip1.Location = new System.Drawing.Point(0, 424);
            this.statusStrip1.Name = "statusStrip1";
            this.statusStrip1.RenderMode = System.Windows.Forms.ToolStripRenderMode.Professional;
            this.statusStrip1.Size = new System.Drawing.Size(800, 26);
            this.statusStrip1.TabIndex = 0;
            this.statusStrip1.Text = "statusStrip1";
            // 
            // status_SerialNumber
            // 
            this.status_SerialNumber.Name = "status_SerialNumber";
            this.status_SerialNumber.Size = new System.Drawing.Size(107, 20);
            this.status_SerialNumber.Text = "Not connected";
            // 
            // button_USBrescan
            // 
            this.button_USBrescan.Location = new System.Drawing.Point(560, 99);
            this.button_USBrescan.Name = "button_USBrescan";
            this.button_USBrescan.Size = new System.Drawing.Size(133, 23);
            this.button_USBrescan.TabIndex = 4;
            this.button_USBrescan.Text = "Rescan";
            this.button_USBrescan.UseVisualStyleBackColor = true;
            this.button_USBrescan.Click += new System.EventHandler(this.button_USBrescan_Click);
            // 
            // Serial_COMlist
            // 
            this.Serial_COMlist.FormattingEnabled = true;
            this.Serial_COMlist.Items.AddRange(new object[] {
            "-- Rescan first --"});
            this.Serial_COMlist.Location = new System.Drawing.Point(560, 157);
            this.Serial_COMlist.Name = "Serial_COMlist";
            this.Serial_COMlist.Size = new System.Drawing.Size(121, 24);
            this.Serial_COMlist.TabIndex = 5;
            this.Serial_COMlist.SelectedIndexChanged += new System.EventHandler(this.serial_COMlist_SelectedIndexChanged);
            // 
            // status_USBcon
            // 
            this.status_USBcon.BackColor = System.Drawing.Color.Red;
            this.status_USBcon.Enabled = false;
            this.status_USBcon.Font = new System.Drawing.Font("Microsoft Sans Serif", 9.75F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(238)));
            this.status_USBcon.Location = new System.Drawing.Point(560, 187);
            this.status_USBcon.Name = "status_USBcon";
            this.status_USBcon.Size = new System.Drawing.Size(133, 42);
            this.status_USBcon.TabIndex = 6;
            this.status_USBcon.Text = "Disconnected";
            this.status_USBcon.UseVisualStyleBackColor = false;
            this.status_USBcon.Click += new System.EventHandler(this.status_USBcon_Click);
            // 
            // Main_form
            // 
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.None;
            this.ClientSize = new System.Drawing.Size(800, 450);
            this.Controls.Add(label_Author);
            this.Controls.Add(label_SpaceConfig);
            this.Controls.Add(this.status_USBcon);
            this.Controls.Add(this.Serial_COMlist);
            this.Controls.Add(this.button_USBrescan);
            this.Controls.Add(this.button_USBconnect);
            this.Controls.Add(this.progressBar1);
            this.Controls.Add(this.Console);
            this.Controls.Add(this.tabControl1);
            this.Controls.Add(this.statusStrip1);
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.MaximizeBox = false;
            this.Name = "Main_form";
            this.SizeGripStyle = System.Windows.Forms.SizeGripStyle.Hide;
            this.Text = "SpaceConfig 0.1";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.Form1_FormClosing);
            this.Load += new System.EventHandler(this.Form1_Load);
            this.tabControl1.ResumeLayout(false);
            this.tabPage_liveview.ResumeLayout(false);
            this.tabPage_liveview.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.LiveView_OrientationIndicator)).EndInit();
            this.tabPage_config.ResumeLayout(false);
            this.tabPage_config.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Config4_DragFail)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Config3_DragFail)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Config2_DragFail)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Config1_DragFail)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Config4_SecondStageDelay)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Config4_LanuchpadLen)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Config4_MainParAlt)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Config3_SecondStageDelay)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Config3_LanuchpadLen)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Config3_MainParAlt)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Config2_SecondStageDelay)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Config2_LanuchpadLen)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Config2_MainParAlt)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Config1_SecondStageDelay)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Config1_LanuchpadLen)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Config1_MainParAlt)).EndInit();
            this.tabPage_admin.ResumeLayout(false);
            this.tabPage_admin.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Admin_Toffset)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Admin_Ha1g)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Admin_A1g)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Admin_Ha0g)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Admin_Z0g)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Admin_Y0g)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_Admin_A0g)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.numeric_AdminSerial)).EndInit();
            this.Console.ResumeLayout(false);
            this.Console.PerformLayout();
            this.statusStrip1.ResumeLayout(false);
            this.statusStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.IO.Ports.SerialPort serialPort_USB;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabPage_liveview;
        private System.Windows.Forms.TabPage tabPage_config;
        private System.Windows.Forms.TabPage tabPage_logger;
        private System.Windows.Forms.GroupBox Console;
        private System.Windows.Forms.ProgressBar progressBar1;
        private System.Windows.Forms.TabPage tabPage_admin;
        private System.Windows.Forms.Button button_USBconnect;
        private System.Windows.Forms.StatusStrip statusStrip1;
        private System.Windows.Forms.Button button_USBrescan;
        private System.Windows.Forms.ComboBox Serial_COMlist;
        private System.Windows.Forms.Button status_USBcon;
        private System.Windows.Forms.TextBox Console_textbox;
        private System.Windows.Forms.TextBox liveView_Battery;
        private System.Windows.Forms.TextBox liveView_Press;
        private System.Windows.Forms.TextBox liveView_Temp;
        private System.Windows.Forms.TextBox liveView_HAcc;
        private System.Windows.Forms.TextBox liveView_AccZ;
        private System.Windows.Forms.TextBox liveView_AccY;
        private System.Windows.Forms.TextBox liveView_AccX;
        private System.Windows.Forms.TextBox liveView_Angle;
        private System.Windows.Forms.Button button_ConfigRead;
        private System.Windows.Forms.Button button_ConfigRestoreDefault;
        private System.Windows.Forms.Button button_ConfigSave;
        private System.Windows.Forms.TextBox text_ConfigName;
        private System.Windows.Forms.TextBox text_ConfigPhone;
        private System.Windows.Forms.ToolStripStatusLabel status_SerialNumber;
        private System.Windows.Forms.Button button_AdminRead;
        private System.Windows.Forms.Button button_AdminSave;
        private System.Windows.Forms.NumericUpDown numeric_Admin_Toffset;
        private System.Windows.Forms.NumericUpDown numeric_Admin_Ha1g;
        private System.Windows.Forms.NumericUpDown numeric_Admin_A1g;
        private System.Windows.Forms.NumericUpDown numeric_Admin_Ha0g;
        private System.Windows.Forms.NumericUpDown numeric_Admin_Z0g;
        private System.Windows.Forms.NumericUpDown numeric_Admin_Y0g;
        private System.Windows.Forms.NumericUpDown numeric_Admin_A0g;
        private System.Windows.Forms.NumericUpDown numeric_AdminSerial;
        private System.Windows.Forms.NumericUpDown numeric_Config1_SecondStageDelay;
        private System.Windows.Forms.NumericUpDown numeric_Config1_LanuchpadLen;
        private System.Windows.Forms.NumericUpDown numeric_Config1_MainParAlt;
        private System.Windows.Forms.NumericUpDown numeric_Config4_SecondStageDelay;
        private System.Windows.Forms.NumericUpDown numeric_Config4_LanuchpadLen;
        private System.Windows.Forms.NumericUpDown numeric_Config4_MainParAlt;
        private System.Windows.Forms.NumericUpDown numeric_Config3_SecondStageDelay;
        private System.Windows.Forms.NumericUpDown numeric_Config3_LanuchpadLen;
        private System.Windows.Forms.NumericUpDown numeric_Config3_MainParAlt;
        private System.Windows.Forms.NumericUpDown numeric_Config2_SecondStageDelay;
        private System.Windows.Forms.NumericUpDown numeric_Config2_LanuchpadLen;
        private System.Windows.Forms.NumericUpDown numeric_Config2_MainParAlt;
        private System.Windows.Forms.Button button_SerialNumber_Increase;
        private System.Windows.Forms.Button button_CalibrationWizard;
        private System.ComponentModel.BackgroundWorker backgroundWorker1;
        public System.Windows.Forms.PictureBox LiveView_OrientationIndicator;
        private System.Windows.Forms.NumericUpDown numeric_Config4_DragFail;
        private System.Windows.Forms.NumericUpDown numeric_Config3_DragFail;
        private System.Windows.Forms.NumericUpDown numeric_Config2_DragFail;
        private System.Windows.Forms.NumericUpDown numeric_Config1_DragFail;
        private System.Windows.Forms.Button button_Ign_All;
        private System.Windows.Forms.Button button_Ign_SecondStage;
        private System.Windows.Forms.Button button_Ign_Main;
        private System.Windows.Forms.Button button_Ign_Drag;
        private System.Windows.Forms.Button status_Ign_SecondStage;
        private System.Windows.Forms.Button status_Ign_Main;
        private System.Windows.Forms.Button status_Ign_Drag;
        private System.Windows.Forms.Button button_UnlockIgn;
    }
}

