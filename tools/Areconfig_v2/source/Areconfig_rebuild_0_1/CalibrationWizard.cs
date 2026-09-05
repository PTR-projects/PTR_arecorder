using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;


namespace Areconfig_rebuild_0_1
{
    public partial class CalibrationWizard : Form
    {
        int calibration_loops = 20;
        int calibration_counter = 0;
        bool calibration_in_progress = false;
        Int32 are_counter_prev = 0;

        double accXp_sum = 0.0;
        double accXn_sum = 0.0;
        double accYp_sum = 0.0;
        double accYn_sum = 0.0;
        double accZp_sum = 0.0;
        double accZn_sum = 0.0;
        double HaccXp_sum = 0.0;
        double HaccXn_sum = 0.0;

        double accX_offset = 0.0;
        double accY_offset = 0.0;
        double accZ_offset = 0.0;
        double HaccX_offset = 0.0;

        public Arecorder_data arecorder_parent { get; set; }

        public CalibrationWizard()
        {
            InitializeComponent();
        }

        private void Form2_Load(object sender, EventArgs e)
        {

        }

        private void button_Cancel_Click(object sender, EventArgs e)
        {
            //wyłącz okno
            this.Close();
        }

        private void button_nextStep_Click(object sender, EventArgs e)
        {
            if (button_nextStep.Enabled)
            {
                if (CalWizard_Tabs.SelectedIndex < (CalWizard_Tabs.TabCount - 1))
                    CalWizard_Tabs.SelectedIndex++;
            }
        }

        private void button_prevStep_Click(object sender, EventArgs e)
        {
            if (button_prevStep.Enabled)
            {
                if (CalWizard_Tabs.SelectedIndex > 0)
                    CalWizard_Tabs.SelectedIndex--;
            }
        }

        private void button_CalNow_Click(object sender, EventArgs e)
        {
            button_CalNow.Enabled = false;
            calibration_in_progress = true;
            calibration_counter = calibration_loops;

            switch (CalWizard_Tabs.SelectedIndex)
            {
                case 0: //info
                    break;
                case 1: //Xp
                    accXp_sum = 0.0;
                    HaccXp_sum = 0.0;
                    break;
                case 2: //Xn
                    accXn_sum = 0.0;
                    HaccXn_sum = 0.0;
                    break;
                case 3: //Yp
                    accYp_sum = 0.0; break;
                case 4: //Yn
                    accYn_sum = 0.0; break;
                case 5: //Zp
                    accZp_sum = 0.0; break;
                case 6: //Zn
                    accZn_sum = 0.0; break;
            }
        }

        private void timer1_Tick(object sender, EventArgs e)
        {
            if (calibration_in_progress)
            {
                if(calibration_counter > 0)
                {
                    if (arecorder_parent.counter != are_counter_prev)
                    {
                        are_counter_prev = arecorder_parent.counter;
                        calibration_counter--;
                        int tmp = (100 * (calibration_loops - calibration_counter)) / calibration_loops;
                        if(tmp <= 99) progressBar.Value = tmp + 1;
                        progressBar.Value = tmp;

                        switch (CalWizard_Tabs.SelectedIndex)
                        {
                            case 0: //info
                                break;
                            case 1: //Xp
                                accXp_sum += arecorder_parent.accX_raw;
                                HaccXp_sum += arecorder_parent.hacc_raw;
                                break;
                            case 2: //Xn
                                accXn_sum += arecorder_parent.accX_raw;
                                HaccXn_sum += arecorder_parent.hacc_raw;
                                break;
                            case 3: //Yp
                                accYp_sum += arecorder_parent.accY_raw; break;
                            case 4: //Yn
                                accYn_sum += arecorder_parent.accY_raw; break;
                            case 5: //Zp
                                accZp_sum += arecorder_parent.accZ_raw; break;
                            case 6: //Zn
                                accZn_sum += arecorder_parent.accZ_raw; break;
                        }
                    }
                }

                if (calibration_counter == 0)
                {
                    calibration_in_progress = false;
                    button_CalNow.Enabled = true;

                    accX_offset = ((accXn_sum / calibration_loops) + (accXp_sum / calibration_loops)) / 2.0;
                    accY_offset = ((accYn_sum / calibration_loops) + (accYp_sum / calibration_loops)) / 2.0;
                    accZ_offset = ((accZn_sum / calibration_loops) + (accZp_sum / calibration_loops)) / 2.0;
                    HaccX_offset = ((HaccXn_sum / calibration_loops) + (HaccXp_sum / calibration_loops)) / 2.0;

                    textBox_accXp.Text  = (accXp_sum  / calibration_loops).ToString("F2");
                    textBox_accXn.Text  = (accXn_sum  / calibration_loops).ToString("F2");
                    textBox_accYp.Text  = (accYp_sum  / calibration_loops).ToString("F2");
                    textBox_accYn.Text  = (accYn_sum  / calibration_loops).ToString("F2");
                    textBox_accZp.Text  = (accZp_sum  / calibration_loops).ToString("F2");
                    textBox_accZn.Text  = (accZn_sum  / calibration_loops).ToString("F2");
                    textBox_HaccXp.Text = (HaccXp_sum / calibration_loops).ToString("F2");
                    textBox_HaccXn.Text = (HaccXn_sum / calibration_loops).ToString("F2");

                    CalWizard_Tabs.SelectedIndex++;
                    if(CalWizard_Tabs.SelectedIndex == (CalWizard_Tabs.TabCount - 1)){
                        button_CalNow.Enabled = false;
                    }
                }
            }
        }

        private void CalWizard_Tabs_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (CalWizard_Tabs.SelectedIndex == 0)
                button_prevStep.Enabled = false;
            else
                button_prevStep.Enabled = true;

            if (CalWizard_Tabs.SelectedIndex == (CalWizard_Tabs.TabCount - 1))
                button_nextStep.Enabled = false;
            else
                button_nextStep.Enabled = true;

            if ((CalWizard_Tabs.SelectedIndex == 0) || (CalWizard_Tabs.SelectedIndex == (CalWizard_Tabs.TabCount - 1)))
                button_CalNow.Enabled = false;
            else
                button_CalNow.Enabled = true;

            numericUpDown1.Value++;
        }

        private void button_SaveCalib_Click(object sender, EventArgs e)
        {
            arecorder_parent.aX_0_g = Convert.ToInt16(accX_offset);
            arecorder_parent.aY_0_g = Convert.ToInt16(accY_offset);
            arecorder_parent.aZ_0_g = Convert.ToInt16(accZ_offset);
            arecorder_parent.hA_0_g = Convert.ToInt16(HaccX_offset);
            arecorder_parent.saveCalibration = true;
            this.Close();
        }

        
    }
}

///------------------------------ blokada save jak nie ma wszystkiego
///------------------------------ formwatowanie stringa z kalibracją