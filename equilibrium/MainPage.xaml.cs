/*
 * Hoang Pham
 * 4/2/2014
 * window phone controlled quad
 * 
 * */


using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using Microsoft.Devices.Sensors;

using Windows.Networking.Sockets;
using Windows.Networking.Proximity;



using Microsoft.Xna.Framework;
using equilibrium.Resources;

using Windows.System.Threading;
using Windows.Devices.Geolocation;

using BluetoothConnectionManager;

using kuntakinte;
using TextureGraph;
using redbox;
using libvideo;
using Windows.Phone.Media.Capture;
using System.Windows.Resources;
using System.Windows.Media.Imaging;

using Windows.Phone.Speech.Recognition;
using Windows.Phone.Speech.Synthesis;
using System.Windows.Threading;



namespace equilibrium
{
    public partial class MainPage : PhoneApplicationPage
    {
        
        flightbox mflightbox;
        btConManager mConManager;


       

        float roll;
        float pitch;
        float yaw;

        float[] motors;

        //declare speechrecognizerUI 
        SpeechRecognizerUI recoWithUI;

        //timer
        DispatcherTimer timer;

        Motion motion;

        //throttle
        float mthrottle;

        // Constructor
        public MainPage()
        {
            InitializeComponent();


            motors = new float[4];

            //new bluetooth manager
            mConManager = new btConManager();

     
            mflightbox = new flightbox(); // initialize a new flightbox


            mflightbox.inclineEvent += fb_inclineEvent;

            //mflightbox.motorEvent += mflightbox_motorEvent;
            motion = new Motion();
            motion.TimeBetweenUpdates = TimeSpan.FromMilliseconds(5);
            motion.CurrentValueChanged += new EventHandler<SensorReadingEventArgs<MotionReading>>(motion_CurrentValueChanged);


            motion.Start();

            mConManager.Initialize();



            timer = new DispatcherTimer();
            timer.Interval = TimeSpan.FromSeconds(2);
            timer.Tick += new EventHandler(timer_Tick);
            //timer.Start();
            mthrottle = 0;

            

        }

        void motion_CurrentValueChanged(object sender, SensorReadingEventArgs<MotionReading> e)
        {

            float[] attitude = new float[3];
            attitude[0]=e.SensorReading.Attitude.Roll;
            attitude[1]=e.SensorReading.Attitude.Pitch;
            
            motors=mflightbox.compensate(attitude);
            Dispatcher.BeginInvoke(() =>
            {

                rollTextBlock.Text = attitude[0].ToString("f5");
                pitchTextBlock.Text = attitude[1].ToString("f5");
                motor0.Text = motors[0].ToString("f5");
                motor1.Text = motors[1].ToString("f5");
                motor2.Text = motors[2].ToString("f5");
                motor3.Text = motors[3].ToString("f5");

                //updateMotorDrive(data);
            });
            

        }

        void mflightbox_motorEvent(float[] data)
        {
            //throw new NotImplementedException();
            //updateMotorDrive(data);
            
           
            Dispatcher.BeginInvoke(() =>
            {

                
                motor0.Text = data[0].ToString();
                motor1.Text = data[1].ToString();
                motor2.Text = data[2].ToString();
                motor3.Text = data[3].ToString();

                //updateMotorDrive(data);
            });
            

            
           
        }

        void mflightbox_accelEvent(float[] __param0)
        {
            //updateMotorDrive(data);
            Dispatcher.BeginInvoke(() =>
            {
               
            });
        }
        
        private async void boutThatAction()
        {
            SpeechSynthesizer synth = new SpeechSynthesizer();
            await synth.SpeakTextAsync("nah, I'm Just about that action baus");

        }

        private async void Listen()
        {
            this.recoWithUI = new SpeechRecognizerUI();
            
            SpeechRecognitionUIResult recoResult = await recoWithUI.RecognizeWithUIAsync();
            if (recoResult.ResultStatus == SpeechRecognitionUIStatus.Succeeded)
                MessageBox.Show(string.Format("You said {0}.",
                                               recoResult.RecognitionResult.Text));

        }
     
        private async void AppToDevice()
        {

            ConnectAppToDeviceButton.Content = "Connecting...";
            PeerFinder.AlternateIdentities["Bluetooth:Paired"] = "";
            var pairedDevices = await PeerFinder.FindAllPeersAsync();

            if (pairedDevices.Count == 0)
            {
                MessageBox.Show("No paired devices were found.");
            }
            else
            {
                foreach (var pairedDevice in pairedDevices)
                {
                    if (pairedDevice.DisplayName == DeviceName.Text)
                    {
                        mConManager.Connect(pairedDevice.HostName);
                        ConnectAppToDeviceButton.Content = "Connected";
                        DeviceName.IsReadOnly = true;
                        ConnectAppToDeviceButton.IsEnabled = false;
                        continue;
                    }
                }
            }
        }


        void fb_accelEvent(float[] data)
        {
            //updateMotorDrive(data);
            Dispatcher.BeginInvoke(() =>
            {
                
            });

        }

        void fb_inclineEvent(float[] data)
        {

            Dispatcher.BeginInvoke(() =>
            {
                roll = data[0];
                pitch = data[1];
                yaw = data[2];
                rollTextBlock.Text = roll.ToString("f5");
                pitchTextBlock.Text = pitch.ToString("f5");
                yawTextBlock.Text = yaw.ToString("f5");

                

            });

            //updateMotorDrive(roll);
            //updateMotorDrive(yaw);
            
        }


        private async void updateMotorDrive(int[] cmd)
        {
            await mConManager.SendCommand(cmd);
        }

        private void ConnectAppToDeviceButton_Click(object sender, RoutedEventArgs e)
        {
            AppToDevice();
        }

        private async void Reco1_Click(object sender, RoutedEventArgs e)
        {
            //start recognition
            //SpeechRecognitionUIResult recoResult = await recoWithUI.RecognizeWithUIAsync();
        }

        private void Button_Click(object sender, RoutedEventArgs e)
        {
            //Reco1_Click(sender, e);
            //boutThatAction();
            timer.Start();
            //Listen();
        }

        private void throttleSlider_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
           mflightbox.throttle((float)e.NewValue);
        }

        void timer_Tick(object sender, EventArgs e)
        {

            mthrottle += 20;
            

            if (mthrottle > timedThrottle.Value)
            {
                mthrottle = 0;
                timer.Stop();              
            }
            mflightbox.throttle(mthrottle);
        }

        private void timedThrottle_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {

        }

        private void Button_Click_1(object sender, RoutedEventArgs e)
        {
            
        }

    }
}
