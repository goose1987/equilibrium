﻿#pragma checksum "C:\Users\hoang\Documents\GitHub\equilibrium\equilibrium\MainPage.xaml" "{406ea660-64cf-4c82-b6f0-42d48172a799}" "FAC0A58E7D73DAAEA4D838D642F9F39D"
//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:4.0.30319.34014
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

using Microsoft.Phone.Controls;
using System;
using System.Windows;
using System.Windows.Automation;
using System.Windows.Automation.Peers;
using System.Windows.Automation.Provider;
using System.Windows.Controls;
using System.Windows.Controls.Primitives;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Ink;
using System.Windows.Input;
using System.Windows.Interop;
using System.Windows.Markup;
using System.Windows.Media;
using System.Windows.Media.Animation;
using System.Windows.Media.Imaging;
using System.Windows.Resources;
using System.Windows.Shapes;
using System.Windows.Threading;


namespace equilibrium {
    
    
    public partial class MainPage : Microsoft.Phone.Controls.PhoneApplicationPage {
        
        internal System.Windows.Controls.Grid LayoutRoot;
        
        internal System.Windows.Controls.StackPanel TitlePanel;
        
        internal System.Windows.Controls.Grid ContentPanel;
        
        internal System.Windows.Controls.TextBlock rollTextBlock;
        
        internal System.Windows.Controls.TextBlock pitchTextBlock;
        
        internal System.Windows.Controls.TextBlock yawTextBlock;
        
        internal System.Windows.Controls.TextBlock motor0;
        
        internal System.Windows.Controls.Button ConnectAppToDeviceButton;
        
        internal System.Windows.Controls.TextBox DeviceName;
        
        internal System.Windows.Controls.TextBlock motor2;
        
        internal System.Windows.Controls.TextBlock motor1;
        
        internal System.Windows.Controls.TextBlock motor3;
        
        internal System.Windows.Controls.TextBox pGain;
        
        internal System.Windows.Controls.TextBox iGain;
        
        internal System.Windows.Controls.TextBox dGain;
        
        internal System.Windows.Controls.TextBlock zaccel;
        
        private bool _contentLoaded;
        
        /// <summary>
        /// InitializeComponent
        /// </summary>
        [System.Diagnostics.DebuggerNonUserCodeAttribute()]
        public void InitializeComponent() {
            if (_contentLoaded) {
                return;
            }
            _contentLoaded = true;
            System.Windows.Application.LoadComponent(this, new System.Uri("/equilibrium;component/MainPage.xaml", System.UriKind.Relative));
            this.LayoutRoot = ((System.Windows.Controls.Grid)(this.FindName("LayoutRoot")));
            this.TitlePanel = ((System.Windows.Controls.StackPanel)(this.FindName("TitlePanel")));
            this.ContentPanel = ((System.Windows.Controls.Grid)(this.FindName("ContentPanel")));
            this.rollTextBlock = ((System.Windows.Controls.TextBlock)(this.FindName("rollTextBlock")));
            this.pitchTextBlock = ((System.Windows.Controls.TextBlock)(this.FindName("pitchTextBlock")));
            this.yawTextBlock = ((System.Windows.Controls.TextBlock)(this.FindName("yawTextBlock")));
            this.motor0 = ((System.Windows.Controls.TextBlock)(this.FindName("motor0")));
            this.ConnectAppToDeviceButton = ((System.Windows.Controls.Button)(this.FindName("ConnectAppToDeviceButton")));
            this.DeviceName = ((System.Windows.Controls.TextBox)(this.FindName("DeviceName")));
            this.motor2 = ((System.Windows.Controls.TextBlock)(this.FindName("motor2")));
            this.motor1 = ((System.Windows.Controls.TextBlock)(this.FindName("motor1")));
            this.motor3 = ((System.Windows.Controls.TextBlock)(this.FindName("motor3")));
            this.pGain = ((System.Windows.Controls.TextBox)(this.FindName("pGain")));
            this.iGain = ((System.Windows.Controls.TextBox)(this.FindName("iGain")));
            this.dGain = ((System.Windows.Controls.TextBox)(this.FindName("dGain")));
            this.zaccel = ((System.Windows.Controls.TextBlock)(this.FindName("zaccel")));
        }
    }
}

