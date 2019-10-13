using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.IO;
using System.IO.Ports;
using System.Xml;
using ZedGraph;
namespace WindowsFormsApplication1
{

    public partial class Form1 : Form
    {

        string InputData = String.Empty; // Khai báo string buff dùng cho hiển thị dữ liệu sau này.
        delegate void SetTextCallback(string text);

        int tickStart = 0;
        public Form1()
        {
            InitializeComponent();
            // Khai báo hàm delegate bằng phương thức DataReceived của Object SerialPort;
            // Cái này khi có sự kiện nhận dữ liệu sẽ nhảy đến phương thức DataReceive
            // Nếu ko hiểu đoạn này bạn có thể tìm hiểu về Delegate, còn ko cứ COPY . Ko cần quan tâm
            getAvailablePorts();
            serialPort1.DataReceived += new SerialDataReceivedEventHandler(serialPort1_DataReceived);

        }
        void getAvailablePorts()
        {
            var ports = SerialPort.GetPortNames();
            comboBox2.Items.Clear();
            comboBox2.Sorted = true;
            for (int i = 0; i < ports.Length; i++)
            {
                comboBox2.Items.Add(ports[i]);
                comboBox2.SelectedIndex = 0;
            }
        }

        private void Form1_Load(object sender, EventArgs e)
        {
            
            button1.Enabled = false;
            button4.Enabled = false;
            button5.Enabled = false;
            button6.Enabled = false;
            button8.Enabled = false;
     

            // initial Zedgraph
            GraphPane myPane = zedGraphControl1.GraphPane;
            myPane.Title.Text = "Motor DC Control";
            myPane.XAxis.Title.Text = "Time(s)";
            myPane.YAxis.Title.Text = "Speed";
            RollingPointPairList list1 = new RollingPointPairList(1200);
            RollingPointPairList list2 = new RollingPointPairList(1200);
            LineItem curve1 = myPane.AddCurve("SetPoint", list1, Color.Red, SymbolType.None);
            LineItem curve2 = myPane.AddCurve("Speed", list2, Color.Blue, SymbolType.None);
            timer1.Interval = 50; //50ms

            myPane.XAxis.Scale.Min = 0;
            myPane.XAxis.Scale.Max = 30;
            myPane.XAxis.Scale.MinorStep = 1;
            myPane.XAxis.Scale.MajorStep = 5;

            zedGraphControl1.AxisChange();

            tickStart = Environment.TickCount;

        }

        public void draw(double setpoint1, double setpoint2)
        {
            if (zedGraphControl1.GraphPane.CurveList.Count <= 0)
                return;
            LineItem curve1 = zedGraphControl1.GraphPane.CurveList[0] as LineItem;
            LineItem curve2 = zedGraphControl1.GraphPane.CurveList[1] as LineItem;
            if (curve1 == null)
                return;
            if (curve2 == null)
                return;

            IPointListEdit list1 = curve1.Points as IPointListEdit;
            IPointListEdit list2 = curve2.Points as IPointListEdit;

            if (list1 == null)
                return;
            if (list2 == null)
                return;
            // chia 1000 để tính ra ms
            double time = (Environment.TickCount - tickStart) / 1000.0;
            list1.Add(time, setpoint1); // ham hien thi dữ liệu
            list2.Add(time, setpoint2);

            Scale xScale = zedGraphControl1.GraphPane.XAxis.Scale;
            if (time > xScale.Max - xScale.MajorStep)
            {
                xScale.Max = time + xScale.MajorStep;
                xScale.Min = xScale.Max - 30.0;
            }
            // vẽ đồ thị
            zedGraphControl1.AxisChange();
            // 
            zedGraphControl1.Invalidate();
        }
        double setpoint = 0;
        double variable = 0;
        private void timer1_Tick(object sender, EventArgs e)
        {
            draw(setpoint, variable);
        }


        string sendData = string.Empty;


        private void button2_Click(object sender, EventArgs e)
        {

            if (comboBox1.Text == "" | comboBox2.Text == "")
            {
                MessageBox.Show("Please select port option", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            }
            else
            {
                if (groupBox1.Text == "Disconnect")
                {
                    serialPort1.PortName = comboBox2.Text;
                    serialPort1.BaudRate = Convert.ToInt32(comboBox1.Text);
                    serialPort1.StopBits = System.IO.Ports.StopBits.One;
                    serialPort1.Parity = System.IO.Ports.Parity.None;
                    serialPort1.DataBits = 8;
                    serialPort1.Open();
                    button1.Enabled = true;
                    button2.Text = "Disconnect";
                    button2.BackColor = Color.Red;
                    groupBox1.Text = "Connecting";
                    button4.Enabled = true;
                    button5.Enabled = false;
                    button6.Enabled = true;
                    button8.Enabled = true;
                }
                else
                {
                    serialPort1.Close();
                    button1.Enabled = false;
                    button2.Text = "Connect";
                    button2.BackColor = Color.LightSkyBlue;
                    groupBox1.Text = "Disconnect";
                    button4.Enabled = false;
                    button5.Enabled = false;
                    button6.Enabled = false;
                    button8.Enabled = false;
                    timer1.Enabled = false;
                }
            }
        }

        int check = 0;
        private void button4_Click(object sender, EventArgs e)
        {

            timer1.Enabled = true;
            button4.Enabled = false;
            button5.Enabled = true;
            if (check == 0)
            {
                check = 1;
                tickStart = Environment.TickCount;
            }


        }
        private void button5_Click(object sender, EventArgs e)
        {
            button4.Enabled = true;
            button5.Enabled = false;
            timer1.Enabled = false;
        }
        string test;
        Int32 test3;
        int test2;
        private void button1_Click(object sender, EventArgs e)
        {
            test = tocdomm.Text;
            if (test == ""||isNumber(test)==false)
                MessageBox.Show("Please fill a value", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            else
            {
                test3 = Convert.ToInt32(test);
                if (test3 < 0 || test3 > 37)
                {
                    MessageBox.Show("Please fill the correct value", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
                else
                {
                    setpoint = test3;
                    test2 = test.Length;
                    sendData = test;
                    for (int i = 0; i < (29 - test2); i++)
                    {
                        sendData += " ";

                    }

                    serialPort1.Write('A' + sendData);  //Chu y: dung serialPort1.writeline() Vdk ko doc dc
                }                                  // Mac du hien tren terminal
            }
        }
        Int32 test_position = 0, test_position_len = 0;
        string send_data_position;
/*        private void button7_Click(object sender, EventArgs e)
        {
            if (txtVitri.Text == "" || isNumber(txtVitri.Text) == false)
                MessageBox.Show("Please fill a value", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            else
            {
                test_position = Convert.ToInt32(txtVitri.Text);
                if (test_position < 0 )
                {
                    MessageBox.Show("Please fill the correct value", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
                }
                else
                {
                    setpoint = test_position;
                    test_position_len = txtVitri.Text.Length;
                    send_data_position = txtVitri.Text;
                    for (int i = 0; i < (29 - test_position_len); i++)
                        send_data_position += " ";
                    serialPort1.Write('B' + send_data_position);
                }
            }
        } */
        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {

            InputData = serialPort1.ReadExisting(); //Chu y
            if (InputData != String.Empty)
            {
                SetText(InputData); // Chính vì vậy phải sử dụng ủy quyền tại đây. Gọi delegate đã khai báo trước đó.
            }

        }


        string[] mang;
        string data_receive = "";
        
        Int32 distance;
              

        int temp;
        private void SetText(string text)
        {
            if (this.textBox2.InvokeRequired)
            {
                SetTextCallback d = new SetTextCallback(SetText); // khởi tạo 1 delegate mới gọi đến SetText
                this.Invoke(d, new object[] { text });
            }
            else data_receive += text;
            if (data_receive.EndsWith("!"))
            {
                data_receive = data_receive.Substring(0, data_receive.Length - 1);
          //      if(isNumber(data_receive)==true)
                    variable = double.Parse(data_receive);
                textBox2.Text = data_receive;
                data_receive = "";
            }
           
        }

        public bool isNumber(string pValue)
        {
            foreach (char c in pValue)
            {
                if (!char.IsDigit(c))
                    return false;
            }
            return true;
        }
        string sendData2;
        int lenght;

        private void button6_Click(object sender, EventArgs e)
        {
            if ((txtKd.Text == "" && txtKi.Text == "" && txtKp.Text == ""))
                MessageBox.Show("Please fill the correct value", "Error", MessageBoxButtons.OK, MessageBoxIcon.Error);
            else
            {
                sendData2 = "P" + txtKp.Text + "/" + txtKi.Text + "/" + txtKd.Text;
                lenght = sendData2.Length;

                for (int i = 0; i < (29 - lenght); i++)
                {
                    sendData2 += " ";
                }
                serialPort1.WriteLine(sendData2);
            }
        }

 

        string send_data_stop;
        private void button8_Click(object sender, EventArgs e)
        {
            send_data_stop = "S";
            for (int i = 0; i < 29; i++)
                send_data_stop += " ";
            serialPort1.Write(send_data_stop);  // !!!chu y: serialport1.writeline ko dc nha ( ko biet tai sao luon)
        }
    }
}