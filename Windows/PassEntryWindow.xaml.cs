using System.Runtime.InteropServices;
using System.Windows;
using System.Windows.Input;

namespace Athena.Windows
{
    public partial class PassEntryWindow : Window
    {
        public PassEntryWindow()
        {
            InitializeComponent();
        }
        protected override void OnMouseLeftButtonDown(MouseButtonEventArgs e)
        {
            base.OnMouseLeftButtonDown(e);
            DragMove();
        }

        private void CloseWindow(object sender, RoutedEventArgs e)
        {
            this.Close();
        }

        private void TryAddPassword(object sender, RoutedEventArgs e)
        {
            if (string.IsNullOrEmpty(TxtSource.Text))
            {
                PassNoMatch.Text = "Invalid Source!";
                PassNoMatch.Visibility = Visibility.Visible;
                return;
            } //!Check for duplicate source MAYBE?
            
            if (TxtPassword.Password != TxtRepeatPassword.Password)
            {
                PassNoMatch.Visibility = Visibility.Visible;
                return;
            }
            
            PassNoMatch.Visibility = Visibility.Hidden;
            if (!store_from_csharp(TxtSource.Text, TxtPassword.Password, "db/passwords.sqlite"))
            {
                PassNoMatch.Text = "An unknown error has occurred.\nTry reopening the application.";
                PassNoMatch.Visibility = Visibility.Visible;
                return;
            }
            
            this.Close();
        }

        [DllImport("PasswordManager.dll")]
        private static extern bool store_from_csharp(string source,string password,string path);
    }
}