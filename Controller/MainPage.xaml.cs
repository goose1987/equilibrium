using System;
using System.Collections.Generic;
using System.Linq;
using System.Net;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Navigation;
using Microsoft.Phone.Controls;
using Microsoft.Phone.Shell;
using Controller.Resources;
using System.Collections.ObjectModel;
using Windows.Networking.Sockets;
using Windows.Networking.Proximity;
using Windows.Storage.Streams;
using System.Windows.Threading;

namespace Controller
{
    public partial class MainPage : PhoneApplicationPage
    {

        ObservableCollection<PeerAppInfo> _peerApps;
        StreamSocket _socket;

        string _peerName = string.Empty;

        PeerInformation receiver;

        bool connected = false;

        DataWriter _datawriter;

        DispatcherTimer timer;
        // Constructor
        public MainPage()
        {
            InitializeComponent();

            


            _peerApps = new ObservableCollection<PeerAppInfo>();
            PeerFinder.ConnectionRequested += PeerFinder_ConnectionRequested;

            PeerFinder.DisplayName = "NewSender";
            PeerFinder.Start();


            
            // Sample code to localize the ApplicationBar
            //BuildLocalizedApplicationBar();
        }

        private async void RefreshPeerAppList()
        {

            

            try
            {
                var peers = await PeerFinder.FindAllPeersAsync();

                _peerApps.Clear();
                if (peers.Count == 0)
                {
                    MessageBox.Show("no peers");
                }
                else
                {

                    foreach(var peer in peers){
                        if(peer.DisplayName=="NewReceivers"){
                            //_peerApps.Add(new PeerAppInfo(peer));

                            receiver = peer;
                        }
                    }
                    
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }


            try
            {
                _socket = await PeerFinder.ConnectAsync(receiver);

                PeerFinder.Stop();
                _peerName = receiver.DisplayName;

                connected = true;
                _datawriter = new DataWriter(_socket.OutputStream);


            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        void PeerFinder_ConnectionRequested(object sender, ConnectionRequestedEventArgs args)
        {
            throw new NotImplementedException();
        }

       

        private void Connect_Click(object sender, RoutedEventArgs e)
        {
            RefreshPeerAppList();

            //ConnectToPeer(receiver);


        }

        async void ConnectToPeer(PeerInformation peer)
        {




            try
            {
                _socket = await PeerFinder.ConnectAsync(peer);

                PeerFinder.Stop();
                _peerName = peer.DisplayName;

                connected = true;
                _datawriter = new DataWriter(_socket.OutputStream);
               

            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }

            
        }

        private void Throttle_ValueChanged(object sender, RoutedPropertyChangedEventArgs<double> e)
        {
            
            if (connected)
            {
                SendMessage((Int16)e.NewValue);
            }
            Dispatcher.BeginInvoke(() =>
            {
                ThrottleText.Text = "Throttle:" + e.NewValue.ToString();

            });
            
        }

        private async void SendMessage(Int16 message)
        {
            if (_socket == null)
            {
                MessageBox.Show("bro you new");
                return;
            }
            

            _datawriter.WriteInt16(message);
            await _datawriter.StoreAsync();
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

        
    }

    public class PeerAppInfo
    {
        internal PeerAppInfo(PeerInformation peerInformation)
        {
            this.PeerInfo = peerInformation;
            this.DisplayName = this.PeerInfo.DisplayName;
        }

        public string DisplayName { get; private set; }
        public PeerInformation PeerInfo { get; private set; }
    }
}