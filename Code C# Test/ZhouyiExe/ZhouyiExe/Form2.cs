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
            this.MaximizeBox = false;//使最大化窗口失效
            //下一句用来禁止对窗口大小进行拖拽
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
        }
        public void ShowResults()
        {
            string result = Form_ExeChoice.getLog();
            this.richTextBox1.Text = result;
/*
            Form_ExeChoice.changeColor(this.richTextBox1, "本卦爻辞：", Color.Blue);
            Form_ExeChoice.changeColor(this.richTextBox1, "之卦爻辞：", Color.Blue);

            Form_ExeChoice.changeColor(this.richTextBox1, "本卦卦辞：", Color.Green);
            Form_ExeChoice.changeColor(this.richTextBox1, "之卦卦辞：", Color.Green);

            Form_ExeChoice.changeColor(this.richTextBox1, "本卦变爻：", Color.Blue);
            Form_ExeChoice.changeColor(this.richTextBox1, "本卦主变爻：", Color.Blue);
            Form_ExeChoice.changeColor(this.richTextBox1, "本卦副变爻：", Color.Blue);

            Form_ExeChoice.changeColor(this.richTextBox1, "之卦变爻：", Color.Blue);
            Form_ExeChoice.changeColor(this.richTextBox1, "之卦主变爻：", Color.Blue);
            Form_ExeChoice.changeColor(this.richTextBox1, "之卦副变爻：", Color.Blue);

            Form_ExeChoice.changeColor(this.richTextBox1, "初九：", Color.BlueViolet);
            Form_ExeChoice.changeColor(this.richTextBox1, "初六：", Color.BlueViolet);
            Form_ExeChoice.changeColor(this.richTextBox1, "九二：", Color.BlueViolet);
            Form_ExeChoice.changeColor(this.richTextBox1, "六二：", Color.BlueViolet);
            Form_ExeChoice.changeColor(this.richTextBox1, "九三：", Color.BlueViolet);
            Form_ExeChoice.changeColor(this.richTextBox1, "六三：", Color.BlueViolet);
            Form_ExeChoice.changeColor(this.richTextBox1, "九四：", Color.BlueViolet);
            Form_ExeChoice.changeColor(this.richTextBox1, "六四：", Color.BlueViolet);
            Form_ExeChoice.changeColor(this.richTextBox1, "九五：", Color.BlueViolet);
            Form_ExeChoice.changeColor(this.richTextBox1, "六五：", Color.BlueViolet);
            Form_ExeChoice.changeColor(this.richTextBox1, "上九：", Color.BlueViolet);
            Form_ExeChoice.changeColor(this.richTextBox1, "上六：", Color.BlueViolet);
            Form_ExeChoice.changeColor(this.richTextBox1, "用九：", Color.BlueViolet);
            Form_ExeChoice.changeColor(this.richTextBox1, "用六：", Color.BlueViolet);

            Form_ExeChoice.changeColor(this.richTextBox1, "朱熹断卦：", Color.Red);

    */
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Form_ExeChoice.cleanLog();
            ShowResults();
        }
    }
    
}
