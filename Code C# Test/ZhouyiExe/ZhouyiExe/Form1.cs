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
    
    public partial class Form1 : Form
    {
        public Form1()
        {
            InitializeComponent();
            this.pictureBox1.SendToBack();//将背景图片放到最下面
            this.panel1.Parent = this.pictureBox1;
            this.panel1.BringToFront();//将panel放在前面
            this.MaximizeBox = false;//使最大化窗口失效
            //下一句用来禁止对窗口大小进行拖拽
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            this.DoubleBuffered = true;//设置本窗体
            SetStyle(ControlStyles.UserPaint, true);
            SetStyle(ControlStyles.AllPaintingInWmPaint, true); // 禁止擦除背景.
            SetStyle(ControlStyles.DoubleBuffer, true); // 双缓冲
        }

        private string PathDefined = RollResult.PathDefined;

        private void tryOpen(string path)
        {
            if (System.IO.File.Exists(path))
            {
                //存在文件
                System.Diagnostics.Process.Start(path);
            }
            else
            {
                //不存在文件
                MessageBox.Show(path + "不存在");
            }

        }
        private void linkLabel1_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {

            tryOpen(PathDefined + "群经之首.pdf");
        }

        private void linkLabel2_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            tryOpen(PathDefined + "周易基础.pdf");
        }

        private void linkLabel3_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            tryOpen(PathDefined + "王者之道.pdf");
        }

        private void linkLabel4_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            tryOpen(PathDefined + "厚德载物.pdf");
        }

        private void linkLabel5_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            tryOpen(PathDefined + "修身养德.pdf");
        }

        private void linkLabel6_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            tryOpen(PathDefined + "诚至金开.pdf");
        }

        private void linkLabel7_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            tryOpen(PathDefined + "驭人有术.pdf");
        }

        private void linkLabel8_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            tryOpen(PathDefined + "管理有方.pdf");
        }

        private void linkLabel9_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            tryOpen(PathDefined + "警钟常鸣.pdf");
        }

        private void linkLabel10_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            tryOpen(PathDefined + "唯变所适.pdf");
        }

        private void linkLabel11_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            tryOpen(PathDefined + "常用易图.pdf");
        }

        private void linkLabel12_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            tryOpen(PathDefined + "课程简介.pdf");
        }

        private void linkLabel15_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            tryOpen(PathDefined + "参考资料.pdf");
        }

        private void linkLabel13_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {//TODO
            //Form_ExeChoice form2 = new Form_ExeChoice(); //生成一个Form2对象
            //form2.ShowDialog();  //将Form2窗体显示为模式对话框
            tryOpen(PathDefined + "易学.pdf");
        }

        private void linkLabel20_LinkClicked(object sender, LinkLabelLinkClickedEventArgs e)
        {
            //MessageBoxButtons messButton = MessageBoxButtons.OK;
            DialogResult dr = MessageBox.Show("反馈：微信号： seusxc 邮箱： ndqh@qq.com\n" +
                                               "声明：本课件仅供选修我课程的同学使用，请勿外传。");
        }

        private void panel1_Paint(object sender, PaintEventArgs e)
        {

        }

        private void button1_Click(object sender, EventArgs e)
        {
            Form_ExeChoice form2 = new Form_ExeChoice(); //生成一个Form2对象
            form2.ShowDialog();  //将Form2窗体显示为模式对话框
        }
    }
}
