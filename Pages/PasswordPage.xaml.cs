using System.Windows;
using System.Windows.Controls;
using Athena.Windows;

namespace Athena.Pages
{
    public partial class PasswordPage : Page
    {
        public PasswordPage()
        {
            InitializeComponent();
        }

        private void OpenPassEntryWindow(object sender, RoutedEventArgs e)
        {
            var entryWindow = new PassEntryWindow();
            entryWindow.Show();
        }
    }
}