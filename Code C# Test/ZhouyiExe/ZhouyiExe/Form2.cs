using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ZhouyiExe
{
    public partial class Form2 : Form
    {
        public Form2()
        {
            InitializeComponent();
        }

        private void Form2_Load(object sender, EventArgs e)
        {
           

        }
        public void changePics()
        {
            // pictureBox3
            // 
            this.pictureBox3.Image = global::ZhouyiExe.Properties.Resources.Up;

            // 
            // pictureBox2
            // 
            this.pictureBox2.Image = global::ZhouyiExe.Properties.Resources.Down;

            // 
            // pictureBox1
            // 
            this.pictureBox1.Image = global::ZhouyiExe.Properties.Resources.Up;

        }
    }
}
