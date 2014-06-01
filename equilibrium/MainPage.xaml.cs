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
using libfilter;
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

        short roll;
        short pitch;
        short yaw;

        short rollrate;
        short pitchrate;
        short yawrate;

        float myPgain = 0;
        float myIgain = 0;
        float myDgain = 0;

        
        //declare speechrecognizerUI 
        SpeechRecognizerUI recoWithUI;

        //timer
        DispatcherTimer timer;

        Motion motion;
        FilterDesign filterDesigner = null;
        Filter myfilter = null;

        float[] gyroreading;
        float[] mImpulseResponse;

        //throttle
        float mthrottle;

        // Constructor
        public MainPage()
        {
            InitializeComponent();

            //new bluetooth manager
            mConManager = new btConManager();

            gyroreading = new float[5];
            
            //set up filter object
            filterDesigner = new FilterDesign();
            mImpulseResponse = filterDesigner.FIRDesignWindowed((float)0.0, (float)0.5,WindowType.HAMMING);
            //mflightbox = new flightbox(); // initialize a new flightbox
            myfilter = new Filter(mImpulseResponse);

            //mflightbox.inclineEvent += fb_inclineEvent;

            //mflightbox.motorEvent += mflightbox_motorEvent;
            
            motion = new Motion();
            motion.TimeBetweenUpdates = TimeSpan.FromMilliseconds(5);
            motion.CurrentValueChanged += new EventHandler<SensorReadingEventArgs<MotionReading>>(motion_CurrentValueChanged);
            

            mConManager.Initialize();

            motion.Start();

            timer = new DispatcherTimer();
            timer.Interval = TimeSpan.FromSeconds(5);
            timer.Tick += new EventHandler(timer_Tick);
            //timer.Start();
            mthrottle = 0;

        }

        void motion_CurrentValueChanged(object sender, SensorReadingEventArgs<MotionReading> e)
        {
            //throw new NotImplementedException();
            //float foo=myfilter.filter(e.SensorReading.DeviceRotationRate.X);
            //mConManager.SendCommand(e.SensorReading.Attitude.Pitch * 100);
                Dispatcher.BeginInvoke(() =>
                {

                    //await mConManager.SendCommand(e.SensorReading.Attitude.Pitch * 100);
                    //rollTextBlock.Text = foo.ToString("f4");
                    pitchTextBlock.Text = (e.SensorReading.Attitude.Pitch).ToString("f1");
                    rollTextBlock.Text = myfilter.filter(e.SensorReading.DeviceRotationRate.X).ToString("f3");

                });



            
            
            
            
        }

        void mflightbox_motorEvent(float[] data)
        {
            //throw new NotImplementedException();
            //updateMotorDrive(data);
            //await mConManager.SendCommand(data);
            
            rollrate = Convert.ToInt16(data[0]);
            pitchrate = Convert.ToInt16(data[1]);

            
            Dispatcher.BeginInvoke(() =>
            {
                rollrateindicator.Text = rollrate.ToString();
                pitchrateindicator.Text = pitchrate.ToString();
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
            await synth.SpeakTextAsync("PETER WHERES MY PASEO !!!!");

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
            

        }

        void fb_inclineEvent(float[] data)
        {

            //roll = Convert.ToInt16(data[0]);
            //pitch = Convert.ToInt16(data[1]);




            Dispatcher.BeginInvoke(() =>
            {
                rollTextBlock.Text = data[0].ToString("f4");

            });
            
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
            boutThatAction();
            //timer.Start();
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
            if (float.TryParse(pGain.Text, out myPgain)&&float.TryParse(iGain.Text,out myIgain)&&float.TryParse(dGain.Text,out myDgain))
            {
                mflightbox.rollPID(myPgain,myIgain,myDgain);
                mflightbox.pitchPID(myPgain, myIgain, myDgain);
            }
        }

    }
}
