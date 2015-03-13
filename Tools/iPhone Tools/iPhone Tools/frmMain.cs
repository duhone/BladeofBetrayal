using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using iPhone_Tools.Custom;
using iPhone_Tools.FileFormat;
using System.IO;
using iPhone_Tools.Builders;
using iPhone_Tools.Properties;

namespace iPhone_Tools
{
    public partial class frmMain : Form
    {
        #region Fields

        HGPFileManager _hgpFileManager;
        
        #endregion

        public frmMain()
        {
            InitializeComponent();
            LogManager.LogMessage += new EventHandler<LogEventArgs>(LogManager_LogMessage);

            _hgpFileManager = new HGPFileManager();
            GameFileClosed();
        }

        private void btnConvertFramesets_Click(object sender, EventArgs e)
        {
            MessageBox.Show(sizeof(Int32).ToString());
        }

        #region Menu Options

        private void newGameToolStripMenuItem_Click(object sender, EventArgs e)
        {
            DialogResult dr = newHGPDialog.ShowDialog();

            if (dr == DialogResult.OK)
            {
                try
                {
                    // Get the working directory of the file
                    string fileName = Path.GetFileName(newHGPDialog.FileName);
                    string tempPath = newHGPDialog.FileName;
                    tempPath = tempPath.Remove(tempPath.Length - fileName.Length, fileName.Length);
                    Environment.CurrentDirectory = tempPath;
                    HPTFileHelper.SetPath(tempPath);

                    _hgpFileManager.NewFile(newHGPDialog.FileName);

                    GameFileLoaded();
                }
                catch (Exception ex)
                {
                    ErrorManager.ShowError("New HGP file failed...", ex);
                    GameFileClosed();
                }
            }
        }

        private void openGameToolStripMenuItem_Click(object sender, EventArgs e)
        {
            DialogResult dr = openHGPDialog.ShowDialog();

            if (dr == DialogResult.OK)
            {
                try
                {
                    // Get the working directory of the file
                    string fileName = Path.GetFileName(openHGPDialog.FileName);
                    string tempPath = openHGPDialog.FileName;
                    tempPath = tempPath.Remove(tempPath.Length - fileName.Length, fileName.Length);
                    Environment.CurrentDirectory = tempPath;
                    HPTFileHelper.SetPath(tempPath);

                    _hgpFileManager.CloseFile();
                    _hgpFileManager.OpenFile(openHGPDialog.FileName);
                    
                    GameFileLoaded();
                }
                catch (Exception ex)
                {
                    ErrorManager.ShowError("Open HGP file failed...", ex);
                    GameFileClosed();
                }
            }
        }

        private void saveGameToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                _hgpFileManager.SaveFile();
            }
            catch (Exception ex)
            {
                ErrorManager.ShowError("Save HGP file failed...", ex);
            }
        }

        private void closeGameToolStripMenuItem_Click(object sender, EventArgs e)
        {
            try
            {
                _hgpFileManager.CloseFile();
                GameFileClosed();
            }
            catch (Exception ex)
            {
                ErrorManager.ShowError("Close HGP file failed...", ex);
            }
        }

        #endregion

        #region HGP File Loaded/Closed UI State Methods

        private void GameFileLoaded()
        {
            AppSettings.Instance.Load();

            newGameToolStripMenuItem.Enabled = true;
            openGameToolStripMenuItem.Enabled = true;
            saveGameToolStripMenuItem.Enabled = true;
            closeGameToolStripMenuItem.Enabled = true;
            tabControl1.Visible = true;

            // Set up bindings:
            hgfPanel1.HGPFileManager = _hgpFileManager;
            quickToolsPanel1.HGPFileManager = _hgpFileManager;
            levelPanel1.HGPFileManager = _hgpFileManager;
        }

        private void GameFileClosed()
        {
            AppSettings.Instance.Save();

            newGameToolStripMenuItem.Enabled = true;
            openGameToolStripMenuItem.Enabled = true;
            saveGameToolStripMenuItem.Enabled = false;
            closeGameToolStripMenuItem.Enabled = false;
            tabControl1.Visible = false;
        }

        #endregion

        #region Event Handlers

        void LogManager_LogMessage(object sender, LogEventArgs e)
        {
            logMessages.AppendText(e.Msg + "\r");
            logMessages.SelectionStart = logMessages.TextLength;
            logMessages.ScrollToCaret();
        }

        #endregion

        #region Builders

        private void selectedLevelToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LevelBuilder lb = new LevelBuilder();
            lb.Build(levelPanel1.SelectedLevel);
        }

        #endregion

        private void convertOldHTFsToIPhoneToolStripMenuItem_Click(object sender, EventArgs e)
        {
            LevelBuilder lb = new LevelBuilder();
            //lb.ConvertHTFsToiPhone(levelPanel1.SelectedLevel);
        }

        private void frmMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            AppSettings.Instance.Save();
        }

        private void tabControl1_SelectedIndexChanged(object sender, EventArgs e)
        {

            hgfPanel1.OnActivate();
        }
    }
}
