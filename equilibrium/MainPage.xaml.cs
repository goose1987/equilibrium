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
using Windows.Phone.Speech.Recognition;
using Windows.Phone.Speech.Synthesis;


namespace equilibrium
{
    public partial class MainPage : PhoneApplicationPage
    {
        
        flightbox mflightbox;
        btConManager mConManager;

        float roll;
        float pitch;
        float yaw;


        //declare speechrecognizerUI 
        SpeechRecognizerUI recoWithUI;




        // Constructor
        public MainPage()
        {
            InitializeComponent();

            //new bluetooth manager
            mConManager = new btConManager();

     
            mflightbox = new flightbox(); // initialize a new flightbox


            //mflightbox.inclineEvent += fb_inclineEvent;
            mflightbox.accelEvent += mflightbox_accelEvent;
            

            //initialize objects ahead of time to avoid delays when starting recognition.
            //recoWithUI = new SpeechRecognizerUI();

            //set path to SRGS compliant XML file
            //Uri citiesGrammar = new Uri("ms-appx:///CitiesList.grxml", UriKind.Absolute);

            //add SRGS grammar to grammar set
            //recoWithUI.Recognizer.Grammars.AddGrammarFromUri("cities", citiesGrammar);

            //let user know what to say
            //recoWithUI.Settings.ListenText = "Fly to what city?";

            //give example of expected input
            //recoWithUI.Settings.ExampleText = "'Barcelona','Montreal','Santiago'";
            mConManager.Initialize();
        }

        void mflightbox_accelEvent(float[] __param0)
        {
            //updateMotorDrive(data);
            Dispatcher.BeginInvoke(() =>
            {
                heightTextBlock.Text = __param0[0].ToString("f3") ;
            });
        }
        

        // Sample code for building a localized ApplicationBar
        //private void BuildLocalizedApplicationBar()
        //{
        //    // Set the page's ApplicationBar to a new instance of ApplicationBar.
        //    ApplicationBar = new ApplicationBar();

        //    // Create a new button and set the text value to the localized string from AppResources.
        //    ApplicationBarIconButton appBarButton = new ApplicationBarIconButton(new Uri("/Assets/AppBar/appbar.add.rest.png", UriKind.Relative));
        //    appBarButton.Text = AppResources.AppBarButtonText;
        //    ApplicationBar.Buttons.Add(appBarButton);

        //    // Create a new menu item with the localized string from AppResources.
        //    ApplicationBarMenuItem appBarMenuItem = new ApplicationBarMenuItem(AppResources.AppBarMenuItemText);
        //    ApplicationBar.MenuItems.Add(appBarMenuItem);
        //}

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
                heightTextBlock.Text ="foo";
            });

        }

        void fb_inclineEvent(float[] data)
        {

            Dispatcher.BeginInvoke(() =>
            {
                roll = data[0];
                pitch = data[1];
                yaw = data[2];
                rollTextBlock.Text = roll.ToString("f2");
                pitchTextBlock.Text = pitch.ToString("f2");
                yawTextBlock.Text = yaw.ToString("f2");

                

            });

            //updateMotorDrive(roll);
            //updateMotorDrive(yaw);
            
        }


        private async void updateMotorDrive(float cmd)
        {
            await mConManager.SendCommand(cmd.ToString("f2"));
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
            //Listen();
        }

    }
}