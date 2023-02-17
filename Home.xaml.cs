using MaterialDesignThemes.Wpf;
using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Controls;
using System.Windows.Data;
using System.Windows.Documents;
using System.Windows.Input;
using System.Windows.Media;
using System.Windows.Media.Imaging;
using System.Windows.Navigation;
using System.Windows.Shapes;

namespace Athena
{
    /// <summary>
    /// Interaction logic for Home.xaml
    /// </summary>
    public partial class Home : Page
    {
        public Home()
        {
            InitializeComponent();
            _paletteHelper.GetTheme().SetBaseTheme(Theme.Dark);
        }

       /* private void ToggleTheme(object sender, RoutedEventArgs e)
        {
            var theme = _paletteHelper.GetTheme();

            IsDarkTheme = theme.GetBaseTheme() == BaseTheme.Dark;
            if (IsDarkTheme)
            {
                IsDarkTheme = false;
                ThemeSwitch.Data = this.Resources["MoonGeo"] as Geometry;
                ThemeSwitch.Fill = Brushes.Black;
                theme.SetBaseTheme(Theme.Light);
            }
            else
            {
                ThemeSwitch.Data = this.Resources["SunGeo"] as Geometry;
                ThemeSwitch.Fill = Brushes.White;
                theme.SetBaseTheme(Theme.Dark);
            }
            _paletteHelper.SetTheme(theme);
        } */

        private bool IsDarkTheme { get; set; }
        private readonly PaletteHelper _paletteHelper = new PaletteHelper();
    } 
}
