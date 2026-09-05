using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.IO;
using System.Windows.Forms;
using System.Text.RegularExpressions;
//using OfficeOpenXml;

namespace Arecorder_Meas_Parser
{
    public partial class Form_main : Form
    {
        public Form_main()
        {
            InitializeComponent();
            button_process.Enabled = false;
        }

        private string selectedFilePath = "";
        private int clicker1cnt = 0;

        private void areParser(StreamReader reader, StreamWriter writer)
        {
            decimal X_1_g = 0, Hx_1_g = 0, X_0_g = 0, Hx_0_g = 0, Y_0_g = 0, Z_0_g = 0;
            int cal_complete = 6;

            string pattern = @"\d+$"; // match one or more digits at the end of the string

            string line;
            int line_number = 0;
            while ((line = reader.ReadLine()) != null)
            {
                if ((line_number++) > 20)
                {
                    string message_error = "Header error. Try different file.";
                    string title_error = "Error";
                    MessageBox.Show(message_error, title_error);
                    return;
                }
                    

                if (line.Contains("X_1_g"))
                {
                    // Found a line that contains the string "X_1_g"
                    Match match = Regex.Match(line, pattern);
                    if (match.Success)
                    {
                        if (decimal.TryParse(match.Value, out X_1_g))
                        {
                            cal_complete--;
                        }
                    }
                }

                if (line.Contains("Hx_1_g"))
                {
                    // Found a line that contains the string "X_1_g"
                    Match match = Regex.Match(line, pattern);
                    if (match.Success)
                    {
                        if (decimal.TryParse(match.Value, out Hx_1_g))
                        {
                            cal_complete--;
                        }
                    }
                }

                if (line.Contains("X_0_g"))
                {
                    // Found a line that contains the string "X_1_g"
                    Match match = Regex.Match(line, pattern);
                    if (match.Success)
                    {
                        if (decimal.TryParse(match.Value, out X_0_g))
                        {
                            cal_complete--;
                        }
                    }
                }

                if (line.Contains("Hx_0_g"))
                {
                    // Found a line that contains the string "X_1_g"
                    Match match = Regex.Match(line, pattern);
                    if (match.Success)
                    {
                        if (decimal.TryParse(match.Value, out Hx_0_g))
                        {
                            cal_complete--;
                        }
                    }
                }

                if (line.Contains("Y_0_g"))
                {
                    // Found a line that contains the string "X_1_g"
                    Match match = Regex.Match(line, pattern);
                    if (match.Success)
                    {
                        if (decimal.TryParse(match.Value, out Y_0_g))
                        {
                            cal_complete--;
                        }
                            
                    }
                }

                if (line.Contains("Z_0_g"))
                {
                    // Found a line that contains the string "X_1_g"
                    Match match = Regex.Match(line, pattern);
                    if (match.Success)
                    {
                        if(decimal.TryParse(match.Value, out Z_0_g))
                        {
                            cal_complete--;
                        }
                    }
                    
                }

                if (cal_complete == 0)
                    break;
            }

            while ((line = reader.ReadLine()) != null)
            {
                if (line.Contains("seconds"))
                {
                    writer.WriteLine("T [s];X_acc [G];Y_acc [G];Z_acc [G];HX_acc [G];Pressure [Pa];Kalman pressure [Pa];Temperature [C];Vaxis [m/s];AltitudeFromPressure [m];AltitudeFromAcc [m];State;VelocityPressure [m/s];ParachuteFailureSenseCnt");
                    //writer.WriteLine(line.Replace(',', ';'));
                    break;
                }
            }

            var currentCulture = System.Globalization.CultureInfo.InstalledUICulture;
            var numberFormat = (System.Globalization.NumberFormatInfo)currentCulture.NumberFormat.Clone();
            numberFormat.NumberDecimalSeparator = ".";

            decimal T_0 = -1;

            while ((line = reader.ReadLine()) != null)
            {
                string[] elements = line.Split(',');
                if (elements.Length == 14)
                {
                    decimal[] values = new decimal[elements.Length];
                    int i = 0;
                    foreach (string element in elements)
                    {
                        decimal value = Decimal.Parse(element, numberFormat);
                        values[i++] = value;
                    }

                    if (T_0 < 0)
                        T_0 = values[0];

                    values[0] = values[0] - T_0;
                    values[1] = (values[1] - X_0_g) / X_1_g;
                    values[2] = (values[2] - Y_0_g) / X_1_g;
                    values[3] = (values[3] - Z_0_g) / X_1_g;
                    values[4] = (values[4] - Hx_0_g) / Hx_1_g;

                    string new_line = "";
                    foreach (double value in values)
                    {
                        new_line += value.ToString() + ";";
                    }
                    writer.WriteLine(new_line);
                }
            }

            string message = "Complete";
            string title = "Complete";
            MessageBox.Show(message, title);
        }

        /*
        // First, add a reference to the EPPlus library
        using OfficeOpenXml;

        // Create a new Excel package and add a new worksheet to it
        ExcelPackage excel = new ExcelPackage();
            ExcelWorksheet worksheet = excel.Workbook.Worksheets.Add("Sheet1");

            // Write some data to cells A1, B1, and C1 on the worksheet
            worksheet.Cells[1, 1].Value = "This is cell A1";
        worksheet.Cells[1, 2].Value = "This is cell B1";
        worksheet.Cells[1, 3].Value = "This is cell C1";

        // Save the Excel package to a file
        excel.SaveAs(new FileInfo("C:\\Example\\ExcelWorkbook.xlsx"));
        */


        private void button_browseFile_Click(object sender, EventArgs e)
        {
            // Create an OpenFileDialog to prompt the user to select a file
            OpenFileDialog openFileDialog = new OpenFileDialog();

            // Set the filter to only show certain types of files
            openFileDialog.Filter = "CSV files (*.csv)|*.csv";

            if (openFileDialog.ShowDialog() == DialogResult.OK)
            {
                selectedFilePath = openFileDialog.FileName;
                textBox_filePath.Text = Path.GetFileName(selectedFilePath);
                button_process.Enabled = true;
            }
        }

        private void button_process_Click(object sender, EventArgs e)
        {
            string filePath = selectedFilePath;
            string parsedFilePath = Path.Combine(Path.GetDirectoryName(filePath),
                                                 Path.GetFileNameWithoutExtension(filePath) + "_parsed" +
                                                 Path.GetExtension(filePath));

            using (StreamReader reader = new StreamReader(filePath))
            using (StreamWriter writer = new StreamWriter(parsedFilePath))
            {
                areParser(reader, writer);
            }
        }

        private void Form_main_Load(object sender, EventArgs e)
        {

        }

        private void toolStripStatusLabel1_Click(object sender, EventArgs e)
        {
            clicker1cnt++;

            if(clicker1cnt > 4)
            {
                string message = "Arecorder Meas Parser by bartekM\ngrudzień 2022\n\nW przypadku błędów piszcie na:\nspace.tech@mail.com\n\nWysokich lotów!";
                string title = "About";
                MessageBox.Show(message, title);
            }
        }
    }
}
