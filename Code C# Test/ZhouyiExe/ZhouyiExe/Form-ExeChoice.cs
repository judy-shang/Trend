using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace ZhouyiExe
{
    public partial class Form_ExeChoice : Form
    {
        Form2 form2;
        public Form_ExeChoice()
        {
            InitializeComponent();
        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            MessageBox.Show(this.comboBox1.SelectedItem.ToString());
            form2 = new Form2();
            Thread th = new Thread(() =>
            {
                try
                {
                    threadPro();
                }
                catch (Exception)
                {

                }
            });
            th.Start();
            Thread.Sleep(2000);   //you can update this time as your requirement
            form2.changePics();
            System.Threading.Thread.Sleep(2000);
            th.Abort();
        }
        public void threadPro()
        {
            form2.ShowDialog(); 
        }

    }
}
