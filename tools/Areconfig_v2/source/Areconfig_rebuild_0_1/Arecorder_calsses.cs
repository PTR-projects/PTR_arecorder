using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace Areconfig_rebuild_0_1
{    public struct Configuration_t
    {
        public decimal mainAltitude;
        public decimal lauchpadLength;
        public decimal secondStageDelay;
        public decimal dragFail;
    }

    public class Arecorder_data
    {

        public decimal HvInfo = 0;
        public decimal SvInfo = 0;

        public double accX_raw;
        public double accY_raw;
        public double accZ_raw;
        public double hacc_raw;

        public double accX;
        public double accY;
        public double accZ;
        public double hacc;
        public double pressure;
        public double temperature;
        public double rocket_angle;
        public double fuse1;
        public double fuse2;
        public double fuse3;
        public double vbat;

        public Int16 aX_0_g;
        public Int16 aY_0_g;
        public Int16 aZ_0_g;
        public Int16 a_1_g;
        public Int16 hA_0_g;
        public Int16 hA_1_g;
        public Int16 Toffset;

        public string ownerName;
        public string ownerPhone;

        public UInt16 serialNumber;

        public string[] frame;

        public Configuration_t[] Config = new Configuration_t[5];
        public bool Version_ok = false;
        public bool ConfigP1_ok = false;
        public bool ConfigP2_ok = false;
        public bool Init_ok = false;

        public Int32 counter = 0;
        public bool saveCalibration = false;
        public string calibration_string = "";

        public string FindSerial()
        {
            return "";
        }

        public void Connect(string com_name)
        {

        }

        public void Close()
        {

        }

        public void StartMeas()
        {

        }

        public void StopMeas()
        {

        }

        public string Decoder(string str)
        {
            // Ramka z konfiguracją part 1
            if (str.Substring(0, 5).Contains("P1,"))
            {
                string[] substr = str.Split(',');

                this.frame = substr;
                if (substr.Length != 20)
                    return "Config 1 frame - wrong lenght";

                this.aX_0_g  = Int16.Parse(substr[1]);
                this.aY_0_g  = Int16.Parse(substr[2]);
                this.aZ_0_g  = Int16.Parse(substr[3]);
                this.hA_0_g  = Int16.Parse(substr[4]);
                this.a_1_g   = Int16.Parse(substr[5]);
                this.hA_1_g  = Int16.Parse(substr[6]);
                this.Toffset = Int16.Parse(substr[7]);

                this.Config[1].mainAltitude = Int16.Parse(substr[8]);
                this.Config[2].mainAltitude = Int16.Parse(substr[9]);
                this.Config[3].mainAltitude = Int16.Parse(substr[10]);
                this.Config[4].mainAltitude = Int16.Parse(substr[11]);

                this.Config[1].secondStageDelay = Int16.Parse(substr[12]);
                this.Config[2].secondStageDelay = Int16.Parse(substr[13]);
                this.Config[3].secondStageDelay = Int16.Parse(substr[14]);
                this.Config[4].secondStageDelay = Int16.Parse(substr[15]);

                this.Config[1].lauchpadLength = Int16.Parse(substr[16]);
                this.Config[2].lauchpadLength = Int16.Parse(substr[17]);
                this.Config[3].lauchpadLength = Int16.Parse(substr[18]);
                this.Config[4].lauchpadLength = Int16.Parse(substr[19]);

                this.ConfigP1_ok = true;
                return "Config 1 frame";
            }

            // Ramka z konfiguracją part 2
            else if (str.Substring(0, 5).Contains("P2,"))
            {
                string[] substr = str.Split(',');

                this.frame = substr;

                if (substr.Length != 8)
                    return "Config 2 frame - wrong lenght";
                
                this.Config[1].dragFail = Int16.Parse(substr[1]);
                this.Config[2].dragFail = Int16.Parse(substr[2]);
                this.Config[3].dragFail = Int16.Parse(substr[3]);
                this.Config[4].dragFail = Int16.Parse(substr[4]);
                this.serialNumber = UInt16.Parse(substr[5]);
                this.ownerPhone = substr[6];
                this.ownerName = substr[7];

                this.ConfigP2_ok = true;
                return "Config 2 frame";
            }

            // Ramka z pomiarami
            else if (str.Substring(0, 5).Contains("M,"))
            {
                try
                {
                    string[] substr = str.Split(',');

                    this.frame = substr;        //---------------------------------------------- Poprawić filtrowanie
                    this.accX_raw = Double.Parse(substr[1]);
                    this.accY_raw = Double.Parse(substr[2]);
                    this.accZ_raw = Double.Parse(substr[3]);
                    this.hacc_raw = Double.Parse(substr[4]);
                    this.pressure = Double.Parse(substr[5]);
                    this.temperature = Double.Parse(substr[6]);
                    this.rocket_angle = 0.8 * this.rocket_angle + 0.2 * Double.Parse(substr[7]);
                    this.fuse1 = Double.Parse(substr[8]);
                    this.fuse2 = Double.Parse(substr[9]);
                    this.fuse3 = Double.Parse(substr[10]);
                    this.vbat = Double.Parse(substr[11]);

                    this.accX = 0.9 * this.accX + 0.1 * (this.accX_raw - this.aX_0_g) / a_1_g;
                    this.accY = 0.9 * this.accY + 0.1 * (this.accY_raw - this.aY_0_g) / a_1_g;
                    this.accZ = 0.9 * this.accZ + 0.1 * (this.accZ_raw - this.aZ_0_g) / a_1_g;
                    this.hacc = 0.9 * this.hacc + 0.1 * (this.hacc_raw - this.hA_0_g) / hA_1_g;

                    this.counter++;
                }
                catch (Exception err)
                {
                    throw err;
                }



                return "Meas frame";
            }

            // Ramka z wersją Arecordera
            else if (str.Substring(0, 5).Contains("I,"))
            {
                string[] substr = str.Split(',');
                string SV = "";

                if (substr.Length != 6)
                    return "Vesrion frame - wrong lenght";

                this.HvInfo = Decimal.Parse(substr[3]);
                
                SV = substr[4].Remove(0, 3);
                if(SV.Length == 0)
                {
                    this.SvInfo = 0;
                }
                else
                {
                    this.SvInfo = Decimal.Parse(substr[4].Remove(0, 3));
                }

                this.Version_ok = true;
                return "Arecorder ver frame";
            }

            // Ramka z po zapisaniu rejestru
            else if (str.Substring(0, 5).Contains("ATW(,"))
            {

                return "Reg updated frame";
            }

            // Ramka z błędem zapisu do EEPROM
            else if (str.Substring(0, 5).Contains("ATE"))
            {

                return "EEPROM error frame";
            }

            return "Invalid frame";
        }

        public int ConfigRead()
        {

            return 0;
        }

        public int ConfigSave()
        {
            return 0;
        }

        public int ConfigRestoreDefault()
        {
            this.Config[1].mainAltitude = 200;
            this.Config[2].mainAltitude = 150;
            this.Config[3].mainAltitude = 100;
            this.Config[4].mainAltitude = 50;

            this.Config[1].lauchpadLength = 2;
            this.Config[2].lauchpadLength = 2;
            this.Config[3].lauchpadLength = 2;
            this.Config[4].lauchpadLength = 2;

            this.Config[1].secondStageDelay = 0;
            this.Config[2].secondStageDelay = 0;
            this.Config[3].secondStageDelay = 0;
            this.Config[4].secondStageDelay = 0;

            this.Config[1].dragFail = 50;
            this.Config[2].dragFail = 50;
            this.Config[3].dragFail = 50;
            this.Config[4].dragFail = 50;
            return 0;
        }
    }
}
