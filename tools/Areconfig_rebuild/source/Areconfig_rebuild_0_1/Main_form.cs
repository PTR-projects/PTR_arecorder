using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO.Ports;
using System.Management;

namespace Areconfig_rebuild_0_1
{
    public partial class Main_form : Form
    {
        Arecorder_data Arecorder = new Arecorder_data();
        public string serial_indata;
        Image LiveView_OrientationImageOrg;
        bool CalibWizard_Active = false;
        public Main_form()
        {
            InitializeComponent();
            Serial_COMlist.SelectedIndex = 0;


        }

        private void toolStripStatusLabel1_Click(object sender, EventArgs e)
        {
            
        }

        private void tabPage1_Click(object sender, EventArgs e)
        {

        }

        private void serial_COMlist_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void button_USBconnect_Click(object sender, EventArgs e)
        {
            Arecorder.ConfigP1_ok = false;
            Arecorder.ConfigP2_ok = false;
            Arecorder.Version_ok  = false;
            Arecorder.Init_ok     = false;

            if (!serialPort_USB.IsOpen)
            {
                try
                {
                    serialPort_USB.PortName = Serial_COMlist.Text;
                    serialPort_USB.BaudRate = 115200;
                    serialPort_USB.ReadTimeout = 500;
                    serialPort_USB.WriteTimeout = 500;
                    serialPort_USB.Open();

                    //Console_textbox.AppendText("Serial port " + Serial_COMlist.Text + " connected" + "\r\n");
                    status_USBcon.Text = "Connected";
                    status_USBcon.BackColor = Color.LightGreen;
                    button_USBconnect.Text = "Disconnect";
                }
                catch (Exception err)
                {
                    //Console_textbox.AppendText("Connection to port " + Serial_COMlist.Text + " failed!" + "\r\n");
                    MessageBox.Show(err.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }
            else
            {
                try
                {
                    send2Arecorder("ATS0");
                    while (serialPort_USB.BytesToWrite > 0) { }
                    
                    serialPort_USB.Close();

                    //Console_textbox.AppendText("\r\n" + "Serial port " + Serial_COMlist.Text + " disconnected" + "\r\n");
                    status_USBcon.Text = "Disconnected";
                    status_USBcon.BackColor = Color.Red;
                    button_USBconnect.Text = "Connect";
                    status_SerialNumber.Text = "Not connected";
                }
                catch (Exception err)
                {
                    //Console_textbox.AppendText("\r\n" + "Disconnection from port " + Serial_COMlist.Text + " failed!" + "\r\n");
                    MessageBox.Show(err.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }

            if (serialPort_USB.IsOpen)
            {
                try
                {
                    Arecorder.ConfigRead();
                    send2Arecorder("ATI");  while (serialPort_USB.BytesToWrite > 0) { }
                    send2Arecorder("ATP1"); while (serialPort_USB.BytesToWrite > 0) { }
                    send2Arecorder("ATP2"); while (serialPort_USB.BytesToWrite > 0) { }


                    //Console_textbox.AppendText("Config received" + "\r\n");

                    //status_SerialNumber.Text = "Serial Number " + Arecorder.serialNumber.ToString();
                    send2Arecorder("ATS1");
                }
                catch (Exception err)
                {
                    //Console_textbox.AppendText("\r\n" + "Config read failed!" + "\r\n");
                    MessageBox.Show(err.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
            }


           
        }
        
        private void button_USBrescan_Click(object sender, EventArgs e)
        {
            Serial_COMlist.Items.Clear();
            string[] ports = SerialPort.GetPortNames();
            Array.Sort(ports);
            Serial_COMlist.Items.AddRange(new object[] { "--- Sellect port ---" });
            Serial_COMlist.Items.AddRange(ports);
            Serial_COMlist.SelectedIndex = 0;
        }

        private void status_USBcon_Click(object sender, EventArgs e)
        {

        }

        private void Form1_Load(object sender, EventArgs e)
        {
            Serial_COMlist.Items.Clear();

            using (var searcher = new ManagementObjectSearcher
                ("SELECT * FROM WIN32_SerialPort"))
            {
                string[] portnames = SerialPort.GetPortNames();
                var portss = searcher.Get().Cast<ManagementBaseObject>().ToList().Select(p => p["Caption"].ToString());
                var portList = portnames.Select(n => n + " - " + portss.FirstOrDefault(s => s.Contains(n))).ToList();

                foreach (string s in portList)
                {
                    //Console_textbox.AppendText(s + "\r\n");
                }
            }




            LiveView_OrientationImageOrg = (Bitmap)LiveView_OrientationIndicator.Image.Clone();





        string [] ports = SerialPort.GetPortNames();
            Array.Sort(ports);
            Serial_COMlist.Items.AddRange(new object[] { "--- Sellect port ---" });
            Serial_COMlist.Items.AddRange(ports);
            Serial_COMlist.SelectedIndex = 0;
        }

        private void Form1_FormClosing(object sender, FormClosingEventArgs e)
        {
            if (serialPort_USB.IsOpen)
            {
                serialPort_USB.Close();
            }
        }

        private delegate void LiveViewDelegate();
        private delegate void ConfigViewDelegate();

        private void serialPort_USB_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            try
            {
                //-------------------------------------------------------------------------------- Jakiś srogi problem
                while (serialPort_USB.BytesToRead > 1)
                {
                    try
                    {
                        serial_indata = serialPort_USB.ReadLine();
                    }
                    catch (TimeoutException) {
                        return;
                    }
                    

                    if (serial_indata.Length > 2)
                    {
                        string frameType = "";

                        serial_indata = serial_indata.Replace("\0", "");    //pierwszy Byte to z reguły 0                                                  //Console_textbox.AppendText("In: " + serial_indata + "\r\n");
                        frameType = Arecorder.Decoder(serial_indata);

                        
                        if ((frameType == "Meas frame") && Arecorder.ConfigP1_ok)
                        {
                            if (InvokeRequired)
                                this.Invoke(new LiveViewDelegate(this.LiveViewUpdate));
                            else
                                LiveViewUpdate();
                        }
                           

                        if (frameType == "Config 1 frame")
                        {
                            if (InvokeRequired)
                                this.Invoke(new LiveViewDelegate(this.ConfigViewUpdate));
                            else
                                ConfigViewUpdate();
                        }

                        if (frameType == "Config 2 frame")
                        {
                            if (InvokeRequired)
                                this.Invoke(new LiveViewDelegate(this.ConfigViewUpdate));
                            else
                                ConfigViewUpdate();
                        }
                        
                        if (!Arecorder.Init_ok && (Arecorder.ConfigP1_ok && Arecorder.ConfigP2_ok && Arecorder.Version_ok))
                        {
                            //Console_textbox.AppendText("Init done!" + "\r\n");
                            Arecorder.Init_ok = true;
                        }

                    }

                }
            }
            catch (Exception err)
            {
                MessageBox.Show(err.Message, "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
        }

        private void LiveViewUpdate()
        {
            liveView_Battery.Text = Arecorder.vbat.ToString("F2");
            liveView_Angle.Text = Arecorder.rocket_angle.ToString("F1");
            liveView_AccX.Text = Arecorder.accX.ToString("F2");
            liveView_AccY.Text = Arecorder.accY.ToString("F2");
            liveView_AccZ.Text = Arecorder.accZ.ToString("F2");
            liveView_HAcc.Text = Arecorder.hacc.ToString("F2");
            liveView_Temp.Text = Arecorder.temperature.ToString("F1");
            liveView_Press.Text = Arecorder.pressure.ToString("F0");

            if(Arecorder.fuse1 == 1) 
                status_Ign_Drag.BackColor = Color.Red;
            else
                status_Ign_Drag.BackColor = Color.Gray;

            if (Arecorder.fuse2 == 1)
                status_Ign_Main.BackColor = Color.Red;
            else
                status_Ign_Main.BackColor = Color.Gray;

            if (Arecorder.fuse3 == 1)
                status_Ign_SecondStage.BackColor = Color.Red;
            else
                status_Ign_SecondStage.BackColor = Color.Gray;

            //---- Orientation indicator update ------------
            Image oldImg = LiveView_OrientationIndicator.Image;
            var MaximumSize = (LiveView_OrientationImageOrg.Width > LiveView_OrientationImageOrg.Height) ? LiveView_OrientationImageOrg.Width : LiveView_OrientationImageOrg.Height;

            Bitmap rotatedImg = new Bitmap(MaximumSize, MaximumSize);
            rotatedImg.SetResolution(LiveView_OrientationImageOrg.HorizontalResolution, LiveView_OrientationImageOrg.VerticalResolution);
            Graphics g = Graphics.FromImage(rotatedImg);
            g.TranslateTransform(MaximumSize / 2f, MaximumSize / 2f);
            g.RotateTransform((float)Arecorder.rocket_angle - 90.0f);
            g.TranslateTransform(-MaximumSize / 2f, -MaximumSize / 2f);
            g.DrawImage(LiveView_OrientationImageOrg, new PointF(0, 0));
            LiveView_OrientationIndicator.Image = rotatedImg;
            LiveView_OrientationIndicator.Refresh();
            rotatedImg = null;
            GC.Collect();
        }

        private void ConfigViewUpdate()
        {
            numeric_AdminSerial.Value = Arecorder.serialNumber;

            numeric_Admin_A0g.Value = Arecorder.aX_0_g;
            numeric_Admin_Y0g.Value = Arecorder.aY_0_g;
            numeric_Admin_Z0g.Value = Arecorder.aZ_0_g;

            numeric_Admin_Ha0g.Value = Arecorder.hA_0_g;
            numeric_Admin_A1g.Value = Arecorder.a_1_g;
            numeric_Admin_Ha1g.Value = Arecorder.hA_1_g;
            numeric_Admin_Toffset.Value = Arecorder.Toffset;

            numeric_Config1_MainParAlt.Value = Arecorder.Config[1].mainAltitude;
            numeric_Config2_MainParAlt.Value = Arecorder.Config[2].mainAltitude;
            numeric_Config3_MainParAlt.Value = Arecorder.Config[3].mainAltitude;
            numeric_Config4_MainParAlt.Value = Arecorder.Config[4].mainAltitude;

            numeric_Config1_LanuchpadLen.Value = Arecorder.Config[1].lauchpadLength;
            numeric_Config2_LanuchpadLen.Value = Arecorder.Config[2].lauchpadLength;
            numeric_Config3_LanuchpadLen.Value = Arecorder.Config[3].lauchpadLength;
            numeric_Config4_LanuchpadLen.Value = Arecorder.Config[4].lauchpadLength;

            numeric_Config1_SecondStageDelay.Value = Arecorder.Config[1].secondStageDelay;
            numeric_Config2_SecondStageDelay.Value = Arecorder.Config[2].secondStageDelay;
            numeric_Config3_SecondStageDelay.Value = Arecorder.Config[3].secondStageDelay;
            numeric_Config4_SecondStageDelay.Value = Arecorder.Config[4].secondStageDelay;

            numeric_Config1_DragFail.Value = Arecorder.Config[1].dragFail;
            numeric_Config2_DragFail.Value = Arecorder.Config[2].dragFail;
            numeric_Config3_DragFail.Value = Arecorder.Config[3].dragFail;
            numeric_Config4_DragFail.Value = Arecorder.Config[4].dragFail;

            //combo_Config1_DragChuteFailDetect.

            status_SerialNumber.Text = "Arecorder v" + Arecorder.HvInfo.ToString() + "-" + Arecorder.SvInfo.ToString() + "  Serial Number " + Arecorder.serialNumber.ToString();
            text_ConfigName.Text = Arecorder.ownerName;
            text_ConfigPhone.Text = Arecorder.ownerPhone;
        }

        private void tabPage_liveview_Click(object sender, EventArgs e)
        {

        }

        private void button_ConfigSave_Click(object sender, EventArgs e)
        {
            if (serialPort_USB.IsOpen == false)
            {
                showErrorPopup("Arecorder not connected!");
                return;
            }

            Arecorder.Config[1].mainAltitude = Convert.ToInt16(numeric_Config1_MainParAlt.Value);
            Arecorder.Config[2].mainAltitude = Convert.ToInt16(numeric_Config2_MainParAlt.Value);
            Arecorder.Config[3].mainAltitude = Convert.ToInt16(numeric_Config3_MainParAlt.Value);
            Arecorder.Config[4].mainAltitude = Convert.ToInt16(numeric_Config4_MainParAlt.Value);

            Arecorder.Config[1].secondStageDelay = Convert.ToInt16(numeric_Config1_SecondStageDelay.Value);
            Arecorder.Config[2].secondStageDelay = Convert.ToInt16(numeric_Config2_SecondStageDelay.Value);
            Arecorder.Config[3].secondStageDelay = Convert.ToInt16(numeric_Config3_SecondStageDelay.Value);
            Arecorder.Config[4].secondStageDelay = Convert.ToInt16(numeric_Config4_SecondStageDelay.Value);

            Arecorder.Config[1].lauchpadLength = Convert.ToInt16(numeric_Config1_LanuchpadLen.Value);
            Arecorder.Config[2].lauchpadLength = Convert.ToInt16(numeric_Config2_LanuchpadLen.Value);
            Arecorder.Config[3].lauchpadLength = Convert.ToInt16(numeric_Config3_LanuchpadLen.Value);
            Arecorder.Config[4].lauchpadLength = Convert.ToInt16(numeric_Config4_LanuchpadLen.Value);

            Arecorder.Config[1].dragFail = Convert.ToInt16(numeric_Config1_DragFail.Value);
            Arecorder.Config[2].dragFail = Convert.ToInt16(numeric_Config2_DragFail.Value);
            Arecorder.Config[3].dragFail = Convert.ToInt16(numeric_Config3_DragFail.Value);
            Arecorder.Config[4].dragFail = Convert.ToInt16(numeric_Config4_DragFail.Value);

            send2Arecorder("ATS0"); //while (serialPort_USB.BytesToWrite > 0) { }
            send2Arecorder("ATW(8,"  + Arecorder.Config[1].mainAltitude       + ")"); //while (serialPort_USB.BytesToWrite > 0) { }
            send2Arecorder("ATW(9,"  + Arecorder.Config[2].mainAltitude       + ")"); //while (serialPort_USB.BytesToWrite > 0) { }
            send2Arecorder("ATW(10," + Arecorder.Config[3].mainAltitude       + ")"); //while (serialPort_USB.BytesToWrite > 0) { }
            send2Arecorder("ATW(11," + Arecorder.Config[4].mainAltitude       + ")"); //while (serialPort_USB.BytesToWrite > 0) { }
            send2Arecorder("ATW(12," + Arecorder.Config[1].secondStageDelay   + ")"); //while (serialPort_USB.BytesToWrite > 0) { }
            send2Arecorder("ATW(13," + Arecorder.Config[2].secondStageDelay   + ")"); //while (serialPort_USB.BytesToWrite > 0) { }
            send2Arecorder("ATW(14," + Arecorder.Config[3].secondStageDelay   + ")"); //while (serialPort_USB.BytesToWrite > 0) { }
            send2Arecorder("ATW(15," + Arecorder.Config[4].secondStageDelay   + ")"); //while (serialPort_USB.BytesToWrite > 0) { }
            send2Arecorder("ATW(16," + Arecorder.Config[1].lauchpadLength     + ")"); //while (serialPort_USB.BytesToWrite > 0) { }
            send2Arecorder("ATW(17," + Arecorder.Config[2].lauchpadLength     + ")"); //while (serialPort_USB.BytesToWrite > 0) { }
            send2Arecorder("ATW(18," + Arecorder.Config[3].lauchpadLength     + ")"); //while (serialPort_USB.BytesToWrite > 0) { }
            send2Arecorder("ATW(19," + Arecorder.Config[4].lauchpadLength     + ")"); //while (serialPort_USB.BytesToWrite > 0) { }
            send2Arecorder("ATW(20," + Arecorder.Config[1].dragFail           + ")"); //while (serialPort_USB.BytesToWrite > 0) { }
            send2Arecorder("ATW(21," + Arecorder.Config[2].dragFail           + ")"); //while (serialPort_USB.BytesToWrite > 0) { }
            send2Arecorder("ATW(22," + Arecorder.Config[3].dragFail           + ")"); //while (serialPort_USB.BytesToWrite > 0) { }
            send2Arecorder("ATW(23," + Arecorder.Config[4].dragFail           + ")"); //while (serialPort_USB.BytesToWrite > 0) { }
            send2Arecorder("ATP1");
            send2Arecorder("ATS1"); //while (serialPort_USB.BytesToWrite > 0) { }

            numeric_Config1_MainParAlt_ValueChanged(null, null);
            numeric_Config2_MainParAlt_ValueChanged(null, null);
            numeric_Config3_MainParAlt_ValueChanged(null, null);
            numeric_Config4_MainParAlt_ValueChanged(null, null);

            numeric_Config1_LanuchpadLen_ValueChanged(null, null);
            numeric_Config2_LanuchpadLen_ValueChanged(null, null);
            numeric_Config3_LanuchpadLen_ValueChanged(null, null);
            numeric_Config4_LanuchpadLen_ValueChanged(null, null);

            numeric_Config1_SecondStageDelay_ValueChanged(null, null);
            numeric_Config2_SecondStageDelay_ValueChanged(null, null);
            numeric_Config3_SecondStageDelay_ValueChanged(null, null);
            numeric_Config4_SecondStageDelay_ValueChanged(null, null);

            numeric_Config1_DragFail_ValueChanged(null, null);
            numeric_Config2_DragFail_ValueChanged(null, null);
            numeric_Config3_DragFail_ValueChanged(null, null);
            numeric_Config4_DragFail_ValueChanged(null, null);
        }

        private void button_ConfigRead_Click(object sender, EventArgs e)
        {
            if (serialPort_USB.IsOpen == false)
            {
                showErrorPopup("Arecorder not connected!");
                return;
            }

            send2Arecorder("ATS0");
            send2Arecorder("ATP1");
            send2Arecorder("ATP2");
            send2Arecorder("ATS1");
        }

        private void button_ConfigRestoreDefault_Click(object sender, EventArgs e)
        {
            if (serialPort_USB.IsOpen == false)
            {
                showErrorPopup("Arecorder not connected!");
                return;
            }

            numeric_Config1_MainParAlt.Value = 200;
            numeric_Config2_MainParAlt.Value = 150;
            numeric_Config3_MainParAlt.Value = 100;
            numeric_Config4_MainParAlt.Value = 50;

            numeric_Config1_LanuchpadLen.Value = 2;
            numeric_Config2_LanuchpadLen.Value = 2;
            numeric_Config3_LanuchpadLen.Value = 2;
            numeric_Config4_LanuchpadLen.Value = 2;

            numeric_Config1_SecondStageDelay.Value = 0;
            numeric_Config2_SecondStageDelay.Value = 0;
            numeric_Config3_SecondStageDelay.Value = 0;
            numeric_Config4_SecondStageDelay.Value = 0;

            numeric_Config1_DragFail.Value = 50;
            numeric_Config2_DragFail.Value = 50;
            numeric_Config3_DragFail.Value = 50;
            numeric_Config4_DragFail.Value = 50;

            numeric_Config1_MainParAlt_ValueChanged(null, null);
            numeric_Config2_MainParAlt_ValueChanged(null, null);
            numeric_Config3_MainParAlt_ValueChanged(null, null);
            numeric_Config4_MainParAlt_ValueChanged(null, null);

            numeric_Config1_LanuchpadLen_ValueChanged(null, null);
            numeric_Config2_LanuchpadLen_ValueChanged(null, null);
            numeric_Config3_LanuchpadLen_ValueChanged(null, null);
            numeric_Config4_LanuchpadLen_ValueChanged(null, null);

            numeric_Config1_SecondStageDelay_ValueChanged(null, null);
            numeric_Config2_SecondStageDelay_ValueChanged(null, null);
            numeric_Config3_SecondStageDelay_ValueChanged(null, null);
            numeric_Config4_SecondStageDelay_ValueChanged(null, null);

            numeric_Config1_DragFail_ValueChanged(null, null);
            numeric_Config2_DragFail_ValueChanged(null, null);
            numeric_Config3_DragFail_ValueChanged(null, null);
            numeric_Config4_DragFail_ValueChanged(null, null);
        }

        private void numeric_AdminSerial_ValueChanged(object sender, EventArgs e)
        {
            if (numeric_AdminSerial.Value != Arecorder.serialNumber)
                numeric_AdminSerial.BackColor = Color.Goldenrod;
            else
                numeric_AdminSerial.BackColor = Color.White;
        }

        private void numeric_Admin_A0g_ValueChanged(object sender, EventArgs e)
        {
            if (numeric_Admin_A0g.Value != Arecorder.aX_0_g)
                numeric_Admin_A0g.BackColor = Color.Goldenrod;
            else
                numeric_Admin_A0g.BackColor = Color.White;
        }

        private void numeric_Admin_Y0g_ValueChanged(object sender, EventArgs e)
        {
            if (numeric_Admin_Y0g.Value != Arecorder.aY_0_g)
                numeric_Admin_Y0g.BackColor = Color.Goldenrod;
            else
                numeric_Admin_Y0g.BackColor = Color.White;
        }

        private void numeric_Admin_Z0g_ValueChanged(object sender, EventArgs e)
        {
            if (numeric_Admin_Z0g.Value != Arecorder.aZ_0_g)
                numeric_Admin_Z0g.BackColor = Color.Goldenrod;
            else
                numeric_Admin_Z0g.BackColor = Color.White;
        }

        private void numeric_Admin_Ha0g_ValueChanged(object sender, EventArgs e)
        {
            if (numeric_Admin_Ha0g.Value != Arecorder.hA_0_g)
                numeric_Admin_Ha0g.BackColor = Color.Goldenrod;
            else
                numeric_Admin_Ha0g.BackColor = Color.White;
        }

        private void numeric_Admin_A1g_ValueChanged(object sender, EventArgs e)
        {
            if (numeric_Admin_A1g.Value != Arecorder.a_1_g)
                numeric_Admin_A1g.BackColor = Color.Goldenrod;
            else
                numeric_Admin_A1g.BackColor = Color.White;
        }

        private void numeric_Admin_Ha1g_ValueChanged(object sender, EventArgs e)
        {
            if (numeric_Admin_Ha1g.Value != Arecorder.hA_1_g)
                numeric_Admin_Ha1g.BackColor = Color.Goldenrod;
            else
                numeric_Admin_Ha1g.BackColor = Color.White;
        }

        private void numeric_Admin_Toffset_ValueChanged(object sender, EventArgs e)
        {
            if (numeric_Admin_Toffset.Value != Arecorder.Toffset)
                numeric_Admin_Toffset.BackColor = Color.Goldenrod;
            else
                numeric_Admin_Toffset.BackColor = Color.White;
        }

        private void numeric_Config1_MainParAlt_ValueChanged(object sender, EventArgs e)
        {
            if (numeric_Config1_MainParAlt.Value != Arecorder.Config[1].mainAltitude)
                numeric_Config1_MainParAlt.BackColor = Color.Goldenrod;
            else
                numeric_Config1_MainParAlt.BackColor = Color.White;
        }

        private void numeric_Config1_LanuchpadLen_ValueChanged(object sender, EventArgs e)
        {
            if (numeric_Config1_LanuchpadLen.Value != Arecorder.Config[1].lauchpadLength)
                numeric_Config1_LanuchpadLen.BackColor = Color.Goldenrod;
            else
                numeric_Config1_LanuchpadLen.BackColor = Color.White;
        }

        private void numeric_Config1_SecondStageDelay_ValueChanged(object sender, EventArgs e)
        {
            if (numeric_Config1_SecondStageDelay.Value != Arecorder.Config[1].secondStageDelay)
                numeric_Config1_SecondStageDelay.BackColor = Color.Goldenrod;
            else
                numeric_Config1_SecondStageDelay.BackColor = Color.White;
        }

        private void numeric_Config2_MainParAlt_ValueChanged(object sender, EventArgs e)
        {
            if (numeric_Config2_MainParAlt.Value != Arecorder.Config[2].mainAltitude)
                numeric_Config2_MainParAlt.BackColor = Color.Goldenrod;
            else
                numeric_Config2_MainParAlt.BackColor = Color.White;
        }

        private void numeric_Config2_LanuchpadLen_ValueChanged(object sender, EventArgs e)
        {
            if (numeric_Config2_LanuchpadLen.Value != Arecorder.Config[2].lauchpadLength)
                numeric_Config2_LanuchpadLen.BackColor = Color.Goldenrod;
            else
                numeric_Config2_LanuchpadLen.BackColor = Color.White;
        }

        private void numeric_Config2_SecondStageDelay_ValueChanged(object sender, EventArgs e)
        {
            if (numeric_Config2_SecondStageDelay.Value != Arecorder.Config[2].secondStageDelay)
                numeric_Config2_SecondStageDelay.BackColor = Color.Goldenrod;
            else
                numeric_Config2_SecondStageDelay.BackColor = Color.White;
        }

        private void numeric_Config3_MainParAlt_ValueChanged(object sender, EventArgs e)
        {
            if (numeric_Config3_MainParAlt.Value != Arecorder.Config[3].mainAltitude)
                numeric_Config3_MainParAlt.BackColor = Color.Goldenrod;
            else
                numeric_Config3_MainParAlt.BackColor = Color.White;
        }

        private void numeric_Config3_LanuchpadLen_ValueChanged(object sender, EventArgs e)
        {
            if (numeric_Config3_LanuchpadLen.Value != Arecorder.Config[3].lauchpadLength)
                numeric_Config3_LanuchpadLen.BackColor = Color.Goldenrod;
            else
                numeric_Config3_LanuchpadLen.BackColor = Color.White;
        }

        private void numeric_Config3_SecondStageDelay_ValueChanged(object sender, EventArgs e)
        {
            if (numeric_Config3_SecondStageDelay.Value != Arecorder.Config[3].secondStageDelay)
                numeric_Config3_SecondStageDelay.BackColor = Color.Goldenrod;
            else
                numeric_Config3_SecondStageDelay.BackColor = Color.White;
        }

        private void numeric_Config4_MainParAlt_ValueChanged(object sender, EventArgs e)
        {
            if (numeric_Config4_MainParAlt.Value != Arecorder.Config[4].mainAltitude)
                numeric_Config4_MainParAlt.BackColor = Color.Goldenrod;
            else
                numeric_Config4_MainParAlt.BackColor = Color.White;
        }

        private void numeric_Config4_LanuchpadLen_ValueChanged(object sender, EventArgs e)
        {
            if (numeric_Config4_LanuchpadLen.Value != Arecorder.Config[4].lauchpadLength)
                numeric_Config4_LanuchpadLen.BackColor = Color.Goldenrod;
            else
                numeric_Config4_LanuchpadLen.BackColor = Color.White;
        }

        private void numeric_Config4_SecondStageDelay_ValueChanged(object sender, EventArgs e)
        {
            if (numeric_Config4_SecondStageDelay.Value != Arecorder.Config[4].secondStageDelay)
                numeric_Config4_SecondStageDelay.BackColor = Color.Goldenrod;
            else
                numeric_Config4_SecondStageDelay.BackColor = Color.White;
        }

        private void numeric_Config1_DragFail_ValueChanged(object sender, EventArgs e)
        {
            if (numeric_Config1_DragFail.Value != Arecorder.Config[1].dragFail)
                numeric_Config1_DragFail.BackColor = Color.Goldenrod;
            else
                numeric_Config1_DragFail.BackColor = Color.White;
        }

        private void numeric_Config2_DragFail_ValueChanged(object sender, EventArgs e)
        {
            if (numeric_Config2_DragFail.Value != Arecorder.Config[2].dragFail)
                numeric_Config2_DragFail.BackColor = Color.Goldenrod;
            else
                numeric_Config2_DragFail.BackColor = Color.White;
        }

        private void numeric_Config3_DragFail_ValueChanged(object sender, EventArgs e)
        {
            if (numeric_Config3_DragFail.Value != Arecorder.Config[3].dragFail)
                numeric_Config3_DragFail.BackColor = Color.Goldenrod;
            else
                numeric_Config3_DragFail.BackColor = Color.White;
        }

        private void numeric_Config4_DragFail_ValueChanged(object sender, EventArgs e)
        {
            if (numeric_Config4_DragFail.Value != Arecorder.Config[4].dragFail)
                numeric_Config4_DragFail.BackColor = Color.Goldenrod;
            else
                numeric_Config4_DragFail.BackColor = Color.White;
        }

        private void text_ConfigName_TextChanged(object sender, EventArgs e)
        {
            if (text_ConfigName.Text != Arecorder.ownerName)
                text_ConfigName.BackColor = Color.Goldenrod;
            else
                text_ConfigName.BackColor = Color.White;
        }

        private void text_ConfigPhone_TextChanged(object sender, EventArgs e)
        {
            if (text_ConfigPhone.Text != Arecorder.ownerPhone)
                text_ConfigPhone.BackColor = Color.Goldenrod;
            else
                text_ConfigPhone.BackColor = Color.White;
        }

        private void button_SerialNumber_Increase_Click(object sender, EventArgs e)
        {
            numeric_AdminSerial.Value++;
        }

        private void button_CalibrationWizard_Click(object sender, EventArgs e)
        {
            if (serialPort_USB.IsOpen == false)
            {
                showErrorPopup("Arecorder not connected!");
                return;
            }

            try
            {
                using (CalibrationWizard popup = new CalibrationWizard())
                {
                    Arecorder.saveCalibration = false;
                    popup.arecorder_parent = Arecorder;
                    popup.ShowDialog();
                    popup.Disposed += new System.EventHandler(calibrationWizardClosed);
                    CalibWizard_Active = true;
                }
            }
            catch (Exception err)
            {
                throw;
            }
        }
        private void calibrationWizardClosed(object sender, EventArgs e)
        {
            if (Arecorder.saveCalibration)
                calibrationSave();
        }

        private void calibrationSave()
        {
            try
            {
                send2Arecorder("ATS0"); //while (serialPort_USB.BytesToWrite > 0) { }
                send2Arecorder("ATW(1," + Arecorder.aX_0_g + ")"); //while (serialPort_USB.BytesToWrite > 0) { }
                send2Arecorder("ATW(2," + Arecorder.aY_0_g + ")"); //while (serialPort_USB.BytesToWrite > 0) { }
                send2Arecorder("ATW(3," + Arecorder.aZ_0_g + ")"); //while (serialPort_USB.BytesToWrite > 0) { }
                send2Arecorder("ATW(4," + Arecorder.hA_0_g + ")"); //while (serialPort_USB.BytesToWrite > 0) { }
                send2Arecorder("ATP1");
                send2Arecorder("ATS1"); //while (serialPort_USB.BytesToWrite > 0) { }
            }
            catch (Exception err)
            {
                throw;
            }
        }

        private void serialNumberSave()
        {
            send2Arecorder("ATS0"); //while (serialPort_USB.BytesToWrite > 0) { }
            send2Arecorder("ATW(28," + Arecorder.serialNumber + ")"); //while (serialPort_USB.BytesToWrite > 0) { }
            send2Arecorder("ATP2");
            send2Arecorder("ATS1"); //while (serialPort_USB.BytesToWrite > 0) { }
        }

        private void button_AdminSave_Click(object sender, EventArgs e)
        {
            if (   (Convert.ToInt16(numeric_Admin_A0g.Value)  != Arecorder.aX_0_g)
                || (Convert.ToInt16(numeric_Admin_Y0g.Value)  != Arecorder.aY_0_g)
                || (Convert.ToInt16(numeric_Admin_Z0g.Value)  != Arecorder.aZ_0_g)
                || (Convert.ToInt16(numeric_Admin_Ha0g.Value) != Arecorder.hA_0_g))
            {
                Arecorder.aX_0_g = Convert.ToInt16(numeric_Admin_A0g.Value);  
                Arecorder.aY_0_g = Convert.ToInt16(numeric_Admin_Y0g.Value);  
                Arecorder.aZ_0_g = Convert.ToInt16(numeric_Admin_Z0g.Value);  
                Arecorder.hA_0_g = Convert.ToInt16(numeric_Admin_Ha0g.Value); 

                calibrationSave();

                numeric_Admin_A0g_ValueChanged(null, null);
                numeric_Admin_Y0g_ValueChanged(null, null);
                numeric_Admin_Z0g_ValueChanged(null, null);
                numeric_Admin_Ha0g_ValueChanged(null, null);
            }

            if(Convert.ToUInt16(numeric_AdminSerial.Value) != Arecorder.serialNumber)
            {
                Arecorder.serialNumber = Convert.ToUInt16(numeric_AdminSerial.Value); 
                serialNumberSave();
                numeric_AdminSerial_ValueChanged(null, null);
            }
            
        }

        private void button_AdminRead_Click(object sender, EventArgs e)
        {
            if (serialPort_USB.IsOpen == false)
            {
                showErrorPopup("Arecorder not connected!");
                return;
            }

            send2Arecorder("ATS0");
            send2Arecorder("ATP1");
            send2Arecorder("ATP2");
            send2Arecorder("ATS1");
        }

        private void button_Ign_Drag_Click(object sender, EventArgs e)
        {
            send2Arecorder("ATFP1");
        }

        private void button_Ign_Main_Click(object sender, EventArgs e)
        {
            send2Arecorder("ATFP2");
        }

        private void button_Ign_SecondStage_Click(object sender, EventArgs e)
        {
            send2Arecorder("ATFS2");
        }

        private void button_Ign_All_Click(object sender, EventArgs e)
        {
            send2Arecorder("ATFALL");
        }

        private void button_UnlockIgn_Click(object sender, EventArgs e)
        {
            if (button_Ign_Drag.Enabled == false)
            {
                button_Ign_Drag.Enabled = true;
                button_Ign_Main.Enabled = true;
                button_Ign_SecondStage.Enabled = true;
                button_Ign_All.Enabled = true;
                button_UnlockIgn.Text = "Lock Igniters";
            }
            else
            {
                button_Ign_Drag.Enabled = false;
                button_Ign_Main.Enabled = false;
                button_Ign_SecondStage.Enabled = false;
                button_Ign_All.Enabled = false;
                button_UnlockIgn.Text = "Unlock Igniters";
            }
            
        }

        private bool send2Arecorder(string var)
        {
            if (serialPort_USB.IsOpen)
            {
                serialPort_USB.WriteLine(var);
                return false;
            } 
            else
            {
                showErrorPopup("Arecorder not connected!");
                return true;
            }
        }

        private void showErrorPopup(string var)
        {
            try
            {
                using (Error_popup popup = new Error_popup())
                {
                    popup.StartPosition = FormStartPosition.CenterParent;
                    popup.error_message = var;
                    popup.ShowDialog();
                }
            }
            catch (Exception err)
            {
                throw;
            }
        }
    }
}
