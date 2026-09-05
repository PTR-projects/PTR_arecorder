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
    public partial class Error_popup : Form
    {
        public string error_message = "Generic Error";
        public Error_popup()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            this.Close();
            this.Dispose();
        }

        private void Error_popup_Load(object sender, EventArgs e)
        {
            label_error_message.Text = error_message;
        }
    }
}
