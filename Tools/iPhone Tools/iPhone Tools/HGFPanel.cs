using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using iPhone_Tools.FileFormat;
using System.IO;
using iPhone_Tools.Custom;
using iPhone_Tools.Properties;
using HGFGenerator;

namespace iPhone_Tools
{
    public partial class HGFPanel : UserControl, IProgress
    {
        #region Fields

        HGPFileManager _hgpFileManager;
       
        #endregion

        #region Constructor(s)

        public HGFPanel()
        {
            InitializeComponent();
            _hgpFileManager = new HGPFileManager();
        }

        #endregion

        #region Methods

        private void SetupBindings()
        {
            _hgfFileBindingSource.DataSource = typeof(HGFFile);
            _hgfFileListBindingSource.DataSource = typeof(HGFFile);
            _hptImageBindingSource.DataSource = typeof(HPTImage);
            _hptImageListBindingSource.DataSource = typeof(HPTImage);

            _hgfFileListBindingSource.DataSource = _hgpFileManager.HGFFiles;
            _hgfFileListBindingSource.ResetBindings(false);

            UpdateUI();
        }

        public void OnActivate()
        {

            AssetListTextBox.Text = AppSettings.Instance.AssetListFile;
        }

        #endregion

        #region UI Updating

        private void UpdateUI()
        {
            // HPTImages
            if (_hptImageBindingSource.Current != null)
            {
                btnRemoveImage.Enabled = true;
            }
            else
            {
                btnRemoveImage.Enabled = false;
            }

            // HGFFiles
            if (_hgfFileBindingSource.Current != null)
            {
                groupBox2.Enabled = true;
                groupBox3.Enabled = true;
                groupBox4.Enabled = true;
                btnRemoveHGFFile.Enabled = true;
            }
            else
            {
                groupBox2.Enabled = false;
                groupBox3.Enabled = false;
                groupBox4.Enabled = false;
                btnRemoveHGFFile.Enabled = false;
            }
        }

        #endregion

        #region Properties

        public HGPFileManager HGPFileManager
        {
            set
            {
                _hgpFileManager = value;
                SetupBindings();
            }
        }

        #endregion

        #region Binding List Methods

        private void _hgfFileListBindingSource_CurrentChanged(object sender, EventArgs e)
        {
            _hgfFileBindingSource.DataSource = _hgfFileListBindingSource.Current;
            _hptImageListBindingSource.DataSource = ((HGFFile)_hgfFileListBindingSource.Current).HPTImages;

            UpdateUI();
        }

        private void _hptImageListBindingSource_CurrentChanged(object sender, EventArgs e)
        {
            _hptImageBindingSource.DataSource = _hptImageListBindingSource.Current;
            txtImageIndex.Text = _hptImageListBindingSource.Position.ToString();

            frameSetNumericUpDown.Value = 0;
            frameSetNumericUpDown.Maximum = ((HPTImage)_hptImageBindingSource.DataSource).Frames_per_set.Count-1;
            frameSetFramesTextBox.Text = ((HPTImage)_hptImageBindingSource.DataSource).Frames_per_set[(int)frameSetNumericUpDown.Value].ToString();
        }

        #endregion

        private void btnBrowseHGFFile_Click(object sender, EventArgs e)
        {
            DialogResult dr = saveHGFileDialog.ShowDialog();

            if (dr == DialogResult.OK)
            {
                ((HGFFile)_hgfFileBindingSource.DataSource).Full_path_name = HPTFileHelper.AbsoluteToRelativePath(saveHGFileDialog.FileName);
                _hgfFileBindingSource.ResetBindings(false);
            }
        }

        private void btnAddHGFFile_Click(object sender, EventArgs e)
        {
            _hgfFileListBindingSource.AddNew();
        }

        private void btnRemoveHGFFile_Click(object sender, EventArgs e)
        {
            _hgfFileListBindingSource.RemoveCurrent();
            UpdateUI();
        }

        private void btnAddImage_Click(object sender, EventArgs e)
        {
            _hptImageListBindingSource.AddNew();
        }

        private void btnRemoveImage_Click(object sender, EventArgs e)
        {
            _hptImageListBindingSource.RemoveCurrent();
            UpdateUI();
        }

        private void btnBrowseImage_Click(object sender, EventArgs e)
        {
            DialogResult dr = openImageDialog.ShowDialog();

            if (dr == DialogResult.OK)
            {
                ((HPTImage)_hptImageBindingSource.Current).Full_path_name = HPTFileHelper.AbsoluteToRelativePath(openImageDialog.FileName);
                _hptImageBindingSource.ResetBindings(false);
            }
        }

        private void txtFrameSets_Validated(object sender, EventArgs e)
        {
            frameSetNumericUpDown.Value = 0;
            frameSetNumericUpDown.Maximum = ((HPTImage)_hptImageBindingSource.DataSource).Frames_per_set.Count-1;
            frameSetFramesTextBox.Text = ((HPTImage)_hptImageBindingSource.DataSource).Frames_per_set[(int)frameSetNumericUpDown.Value].ToString();
        }

        private void frameSetNumericUpDown_ValueChanged(object sender, EventArgs e)
        {
            frameSetFramesTextBox.Text = ((HPTImage)_hptImageBindingSource.DataSource).Frames_per_set[(int)frameSetNumericUpDown.Value].ToString();
        }

        private void frameSetFramesTextBox_Validated(object sender, EventArgs e)
        {
            ((HPTImage)_hptImageBindingSource.DataSource).Frames_per_set[(int)frameSetNumericUpDown.Value] = Int32.Parse(frameSetFramesTextBox.Text);
        }

        private void txtFrameSets_Validating(object sender, CancelEventArgs e)
        {
            if (Int32.Parse(txtFrameSets.Text) <= 0)
                e.Cancel = true;
        }

        private void ChangeAssetListButton_Click(object sender, EventArgs e)
        {
            if (AssetListTextBox.Text.Length != 0)
                assetListFileDialog.FileName = AssetListTextBox.Text;
            assetListFileDialog.ShowDialog();
            AssetListTextBox.Text = HPTFileHelper.AbsoluteToRelativePath(assetListFileDialog.FileName);
            AppSettings.Instance.AssetListFile = AssetListTextBox.Text;
        }

        private void button1_Click(object sender, EventArgs e)
        {
            if (AppSettings.Instance.AssetListFile.Length != 0)
            {
                using (StreamWriter writer = 
                    new StreamWriter(AppSettings.Instance.AssetListFile))
                {
                    writer.WriteLine("//Do not modify. This file is auto generated");
                    writer.WriteLine();
                    writer.WriteLine("#pragma once");
                    writer.WriteLine("namespace CR");
                    writer.WriteLine("{");
                        writer.WriteLine("\tnamespace AssetList");
                        writer.WriteLine("\t{");
                    foreach(var hgffile in _hgpFileManager.HGFFiles)
                    {
                        for (int i = 0;i < hgffile.HPTImages.Count;i++)
                        {
                            writer.Write("\t\t const int ");
                            writer.Write(hgffile.HPTImages[i].Desc.Replace(' ','_'));
                            writer.WriteLine(" = " + i+";");
                        }
                    }
                        writer.WriteLine("\t}");
                    writer.WriteLine("}");
                }
            }
        }

        private void button2_Click(object sender, EventArgs e)
        {
            Generator.Instance().GenerateImage(((HGFFile)_hgfFileBindingSource.DataSource),this);
            MessageBox.Show("Finished Creating the HGF!");
        }

        #region IProgress Members

        public void ProgressUpdate(int _percent)
        {
            LogManager.OnLogMessage(this, "HGF Generator " + _percent + "% complete");
        }

        #endregion
    }
}
