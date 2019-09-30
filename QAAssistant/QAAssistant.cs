using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Deployment.Application;
using System.Diagnostics;
using System.Drawing;
using System.IO;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace QATools
{
    public partial class CenposQA : Form
    {
        private string currentPath;
        private string bridgeVersion;
        private string wsVersion;
        private string current7zipPath;
        private string bridgeRelPath = @"\Resources\Temp\Bridge\";
        private string wsRelPath = @"\Resources\Temp\Websockets\";
        private string reportsRelPath = @"\Resources\Temp\Reports\";

        public CenposQA()
        {
            InitializeComponent();
        }

        private void CenposQA_Load(object sender, EventArgs e)
        {
            currentPath = Directory.GetCurrentDirectory();
            current7zipPath = get7zipInstallationPath();

            string bridgeFullPath = currentPath + bridgeRelPath;
            string wsFullPath = currentPath + wsRelPath;

            if (Directory.Exists(bridgeFullPath))
            {
                if (Directory.EnumerateDirectories(bridgeFullPath).Count() > 0)
                {
                    bridgeVersion = Path.GetFileName(Directory.EnumerateDirectories(bridgeFullPath).Last());
                }
            }

            if (Directory.Exists(wsFullPath))
            {
                if (Directory.EnumerateDirectories(wsFullPath).Count() > 0)
                {
                    wsVersion = Path.GetFileName(Directory.EnumerateDirectories(wsFullPath).Last());
                }
            }

            txtCurrentPath.Text = currentPath;
            txtBridgeVersion.Text = bridgeVersion;

            if (ApplicationDeployment.IsNetworkDeployed)
            {
                lblVersion.Text = string.Format("v{0}", ApplicationDeployment.CurrentDeployment.CurrentVersion.ToString(4));
            }
        }

        private string get7zipInstallationPath()
        {
            string x64Path = Environment.ExpandEnvironmentVariables("%PROGRAMFILES%");
            string x32Path = Environment.ExpandEnvironmentVariables("%PROGRAMFILES(X86)%");

            if (File.Exists(x64Path + @"\7-Zip\7z.exe"))
            {
                return x64Path + @"\7-Zip\7z.exe";
            }

            else if (File.Exists(x32Path + @"\7-Zip\7z.exe"))
            {
                return x32Path + @"\7-Zip\7z.exe";
            }

            else if (File.Exists("7z.exe"))
            {
                return "7z.exe";
            }

            else
            {
                return null;
            }
        }

        private void clearSession()
        {
            string bridgeFullPath = currentPath + bridgeRelPath + bridgeVersion;

            if (Directory.Exists(bridgeFullPath))
            {
                string empty = currentPath + @"\Resources\empty";
                cmdRunCommand("copy " + empty + " " + bridgeFullPath + @"\log\bridge.log > nul");
                cmdRunCommand("copy " + empty + " " + bridgeFullPath + @"\log\log.txt > nul");
            }

            try
            {
                HttpRequest request = new HttpRequest("http://control.charles/session/clear", "GET", "", "http://localhost:8888");
                request.GetResponseString();
            }

            catch
            {
                MessageBox.Show("Seems like Charles web interface is not enabled or Charles is not running at all!");
            }
        }

        private void cmdRunBatch(string dir, string file)
        {
            Process cmd = new Process();
            cmd.StartInfo.FileName = "cmd.exe";
            cmd.StartInfo.WorkingDirectory = dir;
            cmd.StartInfo.RedirectStandardInput = true;
            cmd.StartInfo.RedirectStandardOutput = true;
            cmd.StartInfo.CreateNoWindow = false;
            cmd.StartInfo.UseShellExecute = false;
            cmd.Start();

            cmd.StandardInput.WriteLine("start " + file);
            cmd.StandardInput.Flush();
            cmd.StandardInput.Close();
            cmd.WaitForExit();
        }

        private void cmdRunCommand(string command)
        {
            Process cmd = new Process();
            cmd.StartInfo.FileName = "cmd.exe";
            cmd.StartInfo.RedirectStandardInput = true;
            cmd.StartInfo.RedirectStandardOutput = true;
            cmd.StartInfo.CreateNoWindow = true;
            cmd.StartInfo.UseShellExecute = false;
            cmd.Start();

            cmd.StandardInput.WriteLine(command);
            cmd.StandardInput.Flush();
            cmd.StandardInput.Close();
            cmd.WaitForExit();
        }

        private void runExternalApp(string exeFile, string exeParams, bool showWindow = false)
        {
            if (!String.IsNullOrWhiteSpace(exeFile))
            {
                Process cmd = new Process();

                cmd.StartInfo.FileName = exeFile;

                if (!String.IsNullOrWhiteSpace(exeParams))
                {
                    cmd.StartInfo.Arguments = exeParams;
                }

                if (!showWindow)
                {
                    cmd.StartInfo.WindowStyle = ProcessWindowStyle.Hidden;
                }

                cmd.StartInfo.UseShellExecute = true;
                cmd.Start();

                if (!showWindow)
                {
                    cmd.WaitForExit();
                }
            }

            else
            {
                MessageBox.Show("Please provide a valid executable file!");
            }
        }

        private void clearDirectory(string path)
        {
            DirectoryInfo dir = new DirectoryInfo(path);

            if (dir.Exists)
            {
                try
                {
                    DirectoryInfo[] dirs = dir.GetDirectories();

                    // Get the files in the directory and copy them to the new location.
                    FileInfo[] files = dir.GetFiles();

                    foreach (FileInfo file in files)
                    {
                        file.Delete();
                    }

                    foreach (DirectoryInfo subdir in dirs)
                    {
                        clearDirectory(subdir.FullName);
                    }

                    dir.Delete(true);
                }

                catch
                {
                    //MessageBox.Show("An unknown error ocurred, please delete the directory manually.");
                }
            }
            
            Directory.CreateDirectory(path);
        }

        private static void DirectoryCopy(string sourceDirName, string destDirName, bool copySubDirs)
        {
            // Get the subdirectories for the specified directory.
            DirectoryInfo dir = new DirectoryInfo(sourceDirName);

            if (!dir.Exists)
            {
                throw new DirectoryNotFoundException(
                    "Source directory does not exist or could not be found: "
                    + sourceDirName);
            }

            DirectoryInfo[] dirs = dir.GetDirectories();
            // If the destination directory doesn't exist, create it.
            if (!Directory.Exists(destDirName))
            {
                Directory.CreateDirectory(destDirName);
            }

            // Get the files in the directory and copy them to the new location.
            FileInfo[] files = dir.GetFiles();
            foreach (FileInfo file in files)
            {
                string temppath = Path.Combine(destDirName, file.Name);
                file.CopyTo(temppath, false);
            }

            // If copying subdirectories, copy them and their contents to new location.
            if (copySubDirs)
            {
                foreach (DirectoryInfo subdir in dirs)
                {
                    string temppath = Path.Combine(destDirName, subdir.Name);
                    DirectoryCopy(subdir.FullName, temppath, copySubDirs);
                }
            }
        }

        private void btnLoadBridgeQa_Click(object sender, EventArgs e)
        {
            this.Enabled = false;
            Cursor.Current = Cursors.WaitCursor;

            string bridgeFullPath = currentPath + bridgeRelPath;

            if (! String.IsNullOrWhiteSpace(current7zipPath))
            {
                //clearDirectory(bridgeFullPath);

                OpenFileDialog openFileDialog1 = new OpenFileDialog();

                openFileDialog1.InitialDirectory = @"C:\";
                openFileDialog1.Title = "Browse Files";

                openFileDialog1.CheckFileExists = true;
                openFileDialog1.CheckPathExists = true;

                openFileDialog1.DefaultExt = "zip";
                openFileDialog1.Filter = "Zip files (*.zip)|*.zip|All files (*.*)|*.*";
                openFileDialog1.FilterIndex = 1;
                openFileDialog1.RestoreDirectory = true;

                openFileDialog1.ReadOnlyChecked = true;
                openFileDialog1.ShowReadOnly = true;

                if (openFileDialog1.ShowDialog() == DialogResult.OK)
                {
                    string fileSrc = openFileDialog1.FileName;
                    string fileNoExt = Path.GetFileNameWithoutExtension(fileSrc);

                    runExternalApp(current7zipPath, "x \"" + fileSrc + "\" -o" + "\"" + bridgeFullPath + "\" -y");

                    if (Directory.Exists(bridgeFullPath + @"\" + fileNoExt))
                    {
                        txtBridgeVersion.Text = bridgeVersion = fileNoExt;
                    }

                    MessageBox.Show("Operation completed successfully!");
                }

                else
                {
                    MessageBox.Show("Operation cancelled!");
                }
            }

            else
            {
                MessageBox.Show("Please install 7-zip to the standard directory or add it to your %PATH%.");
            }

            this.Enabled = true;
            Cursor.Current = Cursors.Default;
        }

        private void btnLoadWs_Click(object sender, EventArgs e)
        {
            this.Enabled = false;
            Cursor.Current = Cursors.WaitCursor;

            string wsFullPath = currentPath + wsRelPath;

            if (!String.IsNullOrWhiteSpace(current7zipPath))
            {
                //clearDirectory(wsFullPath);

                OpenFileDialog openFileDialog1 = new OpenFileDialog();

                openFileDialog1.InitialDirectory = @"C:\";
                openFileDialog1.Title = "Browse Files";

                openFileDialog1.CheckFileExists = true;
                openFileDialog1.CheckPathExists = true;

                openFileDialog1.DefaultExt = "zip";
                openFileDialog1.Filter = "Zip files (*.zip)|*.zip|All files (*.*)|*.*";
                openFileDialog1.FilterIndex = 1;
                openFileDialog1.RestoreDirectory = true;

                openFileDialog1.ReadOnlyChecked = true;
                openFileDialog1.ShowReadOnly = true;

                if (openFileDialog1.ShowDialog() == DialogResult.OK)
                {
                    string fileSrc = openFileDialog1.FileName;

                    runExternalApp(current7zipPath, "x \"" + fileSrc + "\" -o" + "\"" + wsFullPath + "\" -y");

                    if (Directory.Exists(wsFullPath))
                    {
                        if (Directory.EnumerateDirectories(wsFullPath).Count() > 0)
                        {
                            wsVersion = Path.GetFileName(Directory.EnumerateDirectories(wsFullPath).Last());
                        }
                    }

                    MessageBox.Show("Operation completed successfully!");
                }

                else
                {
                    MessageBox.Show("Operation cancelled!");
                }
            }

            else
            {
                MessageBox.Show("Please install 7-zip to the standard directory or add it to your %PATH%.");
            }

            this.Enabled = true;
            Cursor.Current = Cursors.Default;
        }

        private void btnRunBridgeQa_Click(object sender, EventArgs e)
        {
            string batDir = currentPath + bridgeRelPath + bridgeVersion;
            string batIni = "init.cmd";

            this.Enabled = false;
            Cursor.Current = Cursors.WaitCursor;

            if (File.Exists(batDir + @"\" + batIni))
            {
                cmdRunCommand("sc stop VirtualTerminalBridge.Service");
                cmdRunBatch(batDir, batIni);
            }

            else
            {
                MessageBox.Show("The executable file does not exist!");
            }

            this.Enabled = true;
            Cursor.Current = Cursors.Default;
        }

        private void btnRunWsQa_Click(object sender, EventArgs e)
        {
            string file = currentPath + wsRelPath + wsVersion + @"\CenPOSBridge.exe";

            this.Enabled = false;
            Cursor.Current = Cursors.WaitCursor;

            if (File.Exists(file))
            {
                cmdRunCommand("sc stop \"CenPOS Web Socket\"");
                runExternalApp(file, "", true);
            }

            else
            {
                MessageBox.Show("The executable file does not exist!");
            }

            this.Enabled = true;
            Cursor.Current = Cursors.Default;
        }

        private void btnClearSession_Click(object sender, EventArgs e)
        {
            this.Enabled = false;
            Cursor.Current = Cursors.WaitCursor;

            clearSession();
            txtCurrentSession.Text = "";
            
            this.Enabled = true;
            Cursor.Current = Cursors.Default;
        }

        private void btnStoreSession_Click(object sender, EventArgs e)
        {
            this.Enabled = false;
            Cursor.Current = Cursors.WaitCursor;

            string currentSession = txtCurrentSession.Text;

            if (! String.IsNullOrWhiteSpace(currentSession))
            {
                string bridgeFullPath = currentPath + bridgeRelPath + bridgeVersion;
                string reportsFullPath = currentPath + reportsRelPath + currentSession;
                string zipFullPath = reportsFullPath + @"\" + currentSession + @".zip";

                FolderBrowserDialog folderBrowserDialog1 = new FolderBrowserDialog();

                if (folderBrowserDialog1.ShowDialog() == DialogResult.OK)
                {
                    Directory.CreateDirectory(reportsFullPath);
                    Directory.CreateDirectory(reportsFullPath + @"\bridge");
                    Directory.CreateDirectory(reportsFullPath + @"\charles");

                    if (Directory.Exists(bridgeFullPath))
                    {
                        runExternalApp("xcopy.exe", "\"" + bridgeFullPath + @"\log\*" + "\" " + "\"" + reportsFullPath + @"\bridge\" + "\" /s");
                    }

                    HttpRequest request = new HttpRequest("http://control.charles/session/download", "GET", "", "http://localhost:8888");

                    request.SaveResponseToFile(reportsFullPath + @"\charles\" + currentSession + ".chls");

                    runExternalApp("7z.exe", "a -tzip \"" + zipFullPath + "\" \"" + reportsFullPath + @"\*");

                    FileInfo originalZipFile = new FileInfo(zipFullPath);
                    FileInfo outputZipFile = new FileInfo(folderBrowserDialog1.SelectedPath + @"\" + originalZipFile.Name);

                    if (originalZipFile.Exists)
                    {
                        originalZipFile.MoveTo(outputZipFile.FullName);
                    }

                    MessageBox.Show("Operation completed!");
                }

                else
                {
                    MessageBox.Show("Operation canceled!");
                }
            }

            else
            {
                MessageBox.Show("Invalid session name!");
            }

            this.Enabled = true;
            Cursor.Current = Cursors.Default;
        }

        private void btnRunBridgeProd_Click(object sender, EventArgs e)
        {
            string batDir = @"C:\VirtualTerminalBridge\";
            string batIni = "init.cmd";

            this.Enabled = false;
            Cursor.Current = Cursors.WaitCursor;

            if (File.Exists(batDir + batIni))
            {
                cmdRunCommand("sc stop VirtualTerminalBridge.Service");
                cmdRunBatch(batDir, batIni);
            }

            else
            {
                MessageBox.Show("The executable file does not exist!");
            }

            this.Enabled = true;
            Cursor.Current = Cursors.Default;
        }

        private void btnRunWsProd_Click(object sender, EventArgs e)
        {
            string file = @"C:\VirtualTerminalBridge\WS\CenPOSBridge.exe";

            this.Enabled = false;
            Cursor.Current = Cursors.WaitCursor;

            if (File.Exists(file))
            {
                cmdRunCommand("sc stop \"CenPOS Web Socket\"");
                runExternalApp(file, "", true);
            }

            else
            {
                MessageBox.Show("The executable file does not exist!");
            }

            this.Enabled = true;
            Cursor.Current = Cursors.Default;
        }
    }
}
