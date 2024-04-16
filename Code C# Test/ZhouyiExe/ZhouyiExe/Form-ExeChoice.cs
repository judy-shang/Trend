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
using System.Collections;
using System.IO;

namespace ZhouyiExe
{
    public partial class Form_ExeChoice : Form
    {
        //Form2 form2;
        RollExe rollTest;
        int rollTimes;
        Dictionary<int, PictureBox> mapBoxBase;
        Dictionary<int, PictureBox> mapBoxChange;
        Dictionary<int, TextBox> mapTextBase;
        Dictionary<int, TextBox> mapTextChange;
        public Form_ExeChoice()
        {
            InitializeComponent();
            this.MaximizeBox = false;//使最大化窗口失效
            //下一句用来禁止对窗口大小进行拖拽
            this.FormBorderStyle = System.Windows.Forms.FormBorderStyle.FixedSingle;
            rollTest = new RollExe();
            rollTimes = 0;
            mapBoxBase = new Dictionary<int, PictureBox>
            {
                { 0, this.pictureBox1},
                { 1, this.pictureBox2},
                { 2, this.pictureBox3},
                { 3, this.pictureBox4},
                { 4, this.pictureBox5 },
                { 5, this.pictureBox6}
            };
            mapBoxChange = new Dictionary<int, PictureBox>
            {
                { 0, this.pictureBox12},
                { 1, this.pictureBox11},
                { 2, this.pictureBox10},
                { 3, this.pictureBox9},
                { 4, this.pictureBox8},
                { 5, this.pictureBox7}
            };
            mapTextBase = new Dictionary<int, TextBox>
            {
                {0, this.textBox1 },
                {1, this.textBox2 },
                {2, this.textBox3 },
                {3, this.textBox4 },
                {4, this.textBox5 },
                {5, this.textBox6 }
            };
            mapTextChange = new Dictionary<int, TextBox>
            {
                {0, this.textBox7 },
                {1, this.textBox8 },
                {2, this.textBox9 },
                {3, this.textBox10 },
                {4, this.textBox11 },
                {5, this.textBox12 }
            };

        }

        private void comboBox1_SelectedIndexChanged(object sender, EventArgs e)
        {

        }
        private void resetForms()
        {//TODO
            this.pictureBox1.Image = global::ZhouyiExe.Properties.Resources.Null;
            this.pictureBox2.Image = global::ZhouyiExe.Properties.Resources.Null;
            this.pictureBox3.Image = global::ZhouyiExe.Properties.Resources.Null;
            this.pictureBox4.Image = global::ZhouyiExe.Properties.Resources.Null;
            this.pictureBox5.Image = global::ZhouyiExe.Properties.Resources.Null;
            this.pictureBox6.Image = global::ZhouyiExe.Properties.Resources.Null;
            this.pictureBox7.Image = global::ZhouyiExe.Properties.Resources.Null;
            this.pictureBox8.Image = global::ZhouyiExe.Properties.Resources.Null;
            this.pictureBox9.Image = global::ZhouyiExe.Properties.Resources.Null;
            this.pictureBox10.Image = global::ZhouyiExe.Properties.Resources.Null;
            this.pictureBox11.Image = global::ZhouyiExe.Properties.Resources.Null;
            this.pictureBox12.Image = global::ZhouyiExe.Properties.Resources.Null;
            this.pictureBox13.Image = null;
            this.pictureBox14.Image = null;
            this.pictureBox15.Image = null;
            //this.pictureBox13.Image = global::ZhouyiExe.Properties.Resources.Null;
            //this.pictureBox14.Image = global::ZhouyiExe.Properties.Resources.Null;
            //this.pictureBox15.Image = global::ZhouyiExe.Properties.Resources.Null;

            this.textBox1.Text = "";
            this.textBox2.Text = "";
            this.textBox3.Text = "";
            this.textBox4.Text = "";
            this.textBox5.Text = "";
            this.textBox6.Text = "";
            this.textBox7.Text = "";
            this.textBox8.Text = "";
            this.textBox9.Text = "";
            this.textBox10.Text = "";
            this.textBox11.Text = "";
            this.textBox12.Text = "";
        }
        private void setPicRollResult(ExeTypes based, PictureBox pic)
        {
            if (based== ExeTypes.DownExeTypes)
            {
                pic.Image = global::ZhouyiExe.Properties.Resources.Yin;
            }
            else
            {
                pic.Image = global::ZhouyiExe.Properties.Resources.Yang;
            }
            
        }
        private void setTextRollResult(int value, TextBox text, bool isNeedToChange)
        {
            if (isNeedToChange)
            {
                text.ForeColor = Color.Red;
            }
            else
            {
                text.ForeColor = Color.Black;
            }
            text.Text = value.ToString();
        }
        private void setRollResult()
        {

            setPicRollResult(rollTest.getRollGuaBasedInfos(rollTimes), mapBoxBase[rollTimes]);
            setPicRollResult(rollTest.getRollGuaChangedInfos(rollTimes), mapBoxChange[rollTimes]);
            setTextRollResult(rollTest.getRollGuaBasedValue(rollTimes), mapTextBase[rollTimes], rollTest.getIsNeedToChange(rollTimes));
            setTextRollResult(rollTest.getRollGuaChangedValue(rollTimes), mapTextChange[rollTimes], rollTest.getIsNeedToChange(rollTimes));
        }
        private Image getResultPics(ExeTypes val)
        {
            if (val == ExeTypes.DownExeTypes)
            {
                return global::ZhouyiExe.Properties.Resources.Down2;
            }
            else
            {
                return global::ZhouyiExe.Properties.Resources.Up2;
            }
        }
        public void changePics(ExeTypes[] results)
        {
            // pictureBox13
            // 
            if (results.Length < 3)
            {
                Console.WriteLine("changePics-results length error: ", results.Length);
                return;
            }
            this.pictureBox13.Image = getResultPics(results[2]);

            // 
            // pictureBox14
            // 
            this.pictureBox14.Image = getResultPics(results[1]);

            // 
            // pictureBox15
            // 
            this.pictureBox15.Image = getResultPics(results[0]);

        }
        private void button1_Click(object sender, EventArgs e)
        {
            //MessageBox.Show(this.comboBox1.SelectedItem.ToString());
            if (rollTimes < RollExe.RollTimesMax)
            {
                rollTest.getRollNow();
                this.pictureBox13.Image = global::ZhouyiExe.Properties.Resources.gif_coin;
                this.pictureBox14.Image = global::ZhouyiExe.Properties.Resources.gif_coin;
                this.pictureBox15.Image = global::ZhouyiExe.Properties.Resources.gif_coin;
                /*form2 = new Form2();
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
                form2.changePics(rollTest.getRollDetails(rollTimes));

                System.Threading.Thread.Sleep(2000);
                th.Abort();*/
                //Thread.Sleep(2000);
                this.timer1.Enabled = true;
                this.timer1.Interval = 2000;
                this.timer1.Start();
                
            }
            else
            {
                MessageBoxButtons messButton = MessageBoxButtons.OKCancel;
                DialogResult dr = MessageBox.Show("确定重新占卜？", "重新占卜", messButton);
                if (dr == DialogResult.OK)
                {
                    rollTimes = 0;
                    rollTest.resetRollTimes();
                    this.richTextBox1.Text = "";
                    resetForms();
                }

            }
            
        }
        /*public void threadPro()
        {
            form2.ShowDialog(); 
        }
        */
        public struct ColorArray
        {
            public int start;
            public int end;
            public ColorArray(int start_index, int end_index)
            {
                start = start_index;
                end = end_index;
            }
        }
        static public void changeColor(RichTextBox richTextBox, string str, Color color)
        {
            List<ColorArray> list = new List<ColorArray>();
            getIndexArray(list, richTextBox.Text, str);
            for (int i = 0; i < list.Count; i++)
            {
                int index = list[i].start;
                int index_end = list[i].end;
                richTextBox.Select(index, index_end - index);
                richTextBox.SelectionColor = color;
            }
        }
        
        static public void getIndexArray(List<ColorArray> list, String inputStr, String findStr)
        {
            //ArrayList list = new ArrayList();
            int start = 0;
            while (start < inputStr.Length)
            {
                int index = inputStr.IndexOf(findStr, start);
                if (index >= 0)
                {
                    int index_end = inputStr.IndexOf("\n", index);
                    if (index_end >= index)
                    {
                        list.Add(new ColorArray(index, index_end));
                    }
                    else
                    {
                        list.Add(new ColorArray(index, index + findStr.Length));
                    }
                    //start = index + findStr.Length;
                    start = index_end;
                }
                else
                {
                    break;
                }
            }
        }
       
        private void timer1_Tick(object sender, EventArgs e)
        {
            changePics(rollTest.getRollDetails(rollTimes));
            setRollResult();
            rollTimes++;
            
            if (rollTimes == RollExe.RollTimesMax)
            {// TODO show result, result save to txt
                string type = this.comboBox2.Text;
                string result = rollTest.getRollExplains(type);
                this.richTextBox1.Text = result;
                changeColor(this.richTextBox1, "朱熹断卦：", Color.Red);

                changeColor(this.richTextBox1, "本卦爻辞：", Color.Blue);
                changeColor(this.richTextBox1, "之卦爻辞：", Color.Blue);

                changeColor(this.richTextBox1, "本卦卦辞：", Color.Green);
                changeColor(this.richTextBox1, "之卦卦辞：", Color.Green);

                changeColor(this.richTextBox1, "本卦变爻：", Color.Blue);
                changeColor(this.richTextBox1, "本卦主变爻：", Color.Blue);
                changeColor(this.richTextBox1, "本卦副变爻：", Color.Blue);

                changeColor(this.richTextBox1, "之卦变爻：", Color.Blue);
                changeColor(this.richTextBox1, "之卦主变爻：", Color.Blue);
                changeColor(this.richTextBox1, "之卦副变爻：", Color.Blue);

                changeColor(this.richTextBox1, "初九：", Color.BlueViolet);
                changeColor(this.richTextBox1, "初六：", Color.BlueViolet);
                changeColor(this.richTextBox1, "九二：", Color.BlueViolet);
                changeColor(this.richTextBox1, "六二：", Color.BlueViolet);
                changeColor(this.richTextBox1, "九三：", Color.BlueViolet);
                changeColor(this.richTextBox1, "六三：", Color.BlueViolet);
                changeColor(this.richTextBox1, "九四：", Color.BlueViolet);
                changeColor(this.richTextBox1, "六四：", Color.BlueViolet);
                changeColor(this.richTextBox1, "九五：", Color.BlueViolet);
                changeColor(this.richTextBox1, "六五：", Color.BlueViolet);
                changeColor(this.richTextBox1, "上九：", Color.BlueViolet);
                changeColor(this.richTextBox1, "上六：", Color.BlueViolet);
                changeColor(this.richTextBox1, "用九：", Color.BlueViolet);
                changeColor(this.richTextBox1, "用六：", Color.BlueViolet);

                string log = "占卜方法：" + this.comboBox1.Text + ", 占卜类型：" + this.comboBox2.Text + "\n";
                log += result;
                WriteLog(log);
            }
            this.timer1.Enabled = false;
            this.timer1.Stop();
        }
        static public void cleanLog()
        {
            try
            {
                string path = getLogPath();
                FileStream fs = new FileStream(path, FileMode.Truncate);
            }
            catch
            {
                return;
            }
        }
        static public string getLogPath()
        {

            string path = AppDomain.CurrentDomain.BaseDirectory.ToString();
            path = path + "Results/";

            if (!System.IO.Directory.Exists(path))
            {
                Directory.CreateDirectory(path);
            }
            path += "zhouyi_log.log";
            return path;
        }
        public void WriteLog(string strExp)
        {
            try
            {
                string path = getLogPath();
                FileStream fs = new FileStream(path, FileMode.Append);
                StreamWriter sw = new StreamWriter(fs);
                
                sw.Write("[" + DateTime.Now.ToString("yyy-MM-dd HH:mm:ss") + "]\n" + strExp + "\r\n");
                sw.Flush();
                sw.Close();
            }
            catch
            {
                return;
            }
        }
        static public string getLog()
        {
            string log = "";
            try
            {
                string path = getLogPath();
            
                FileStream fs = new FileStream(path, FileMode.OpenOrCreate);
                StreamReader sr = new StreamReader(fs);
                log = sr.ReadToEnd().ToString();
                sr.Close();
            }
            catch
            {
                return log;
            }
            return log;
        }
        private void button2_Click(object sender, EventArgs e)
        {
            Form2 form2 = new Form2();
            form2.ShowResults();
            form2.ShowDialog();
        }
    }
}
