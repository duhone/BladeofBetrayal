using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Drawing;
using System.Data;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using iPhone_Tools.FileFormat;
using iPhone_Tools.Custom;
using System.IO;

namespace iPhone_Tools
{
    public partial class LevelPanel : UserControl
    {        
        #region Fields

        HGPFileManager _hgpFileManager;

        #endregion

        #region Constructor(s)

        public LevelPanel()
        {
            InitializeComponent();
        }

        #endregion

        #region Methods

        private void SetupBindings()
        {
            //_hgfFileBindingSource.DataSource = typeof(HGFFile);
            //_hgfFileListBindingSource.DataSource = typeof(HGFFile);
            //_hptImageBindingSource.DataSource = typeof(HPTImage);
            //_hptImageListBindingSource.DataSource = typeof(HPTImage);

            //_hgfFileListBindingSource.DataSource = _hgpFileManager.HGFFiles;
            //_hgfFileListBindingSource.ResetBindings(false);

            //UpdateUI();

            //_hgpFileManager.Levels[0].
            _levelFileBindingSource.DataSource = typeof(Level);
            _levelFileListBindingSource.DataSource = _hgpFileManager.Levels;
            _levelFileListBindingSource.ResetBindings(false);
            UpdateUI();
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

        public Level SelectedLevel
        {
            get
            {
                return (Level)_levelFileBindingSource.Current;
            }
        }

        #endregion

        #region UI Updating

        private void UpdateUI()
        {
            // HLFFiles
            if (_levelFileBindingSource.Current != null)
            {
                groupBox1.Enabled = true;
                groupBox2.Enabled = true;
                groupBox4.Enabled = true;
                btnRemoveHLFFile.Enabled = true;
            }
            else
            {
                groupBox1.Enabled = false;
                groupBox2.Enabled = false;
                groupBox4.Enabled = false;
                btnRemoveHLFFile.Enabled = false;
            }
        }

        #endregion

        #region Event Handlers

        private void btnAddHLFFile_Click(object sender, EventArgs e)
        {
            _levelFileListBindingSource.AddNew();
        }

        private void btnRemoveHLFFile_Click(object sender, EventArgs e)
        {
            _levelFileListBindingSource.RemoveCurrent();
            UpdateUI();
        }

        #endregion

        #region Binding Sources

        private void _hlfFileListBindingSource_CurrentChanged(object sender, EventArgs e)
        {
            _levelFileBindingSource.DataSource = _levelFileListBindingSource.Current;
            UpdateUI();
        }

        #endregion

        #region File Browsing

        private void btnBrowseHLFFile_Click(object sender, EventArgs e)
        {
            DialogResult dr = saveHLFFileDialog.ShowDialog();
            if (dr == DialogResult.OK)
            {
                // remove the extension from the file name
                ((Level)_levelFileBindingSource.Current).Full_path_name = HPTFileHelper.AbsoluteToRelativePath(saveHLFFileDialog.FileName.Remove(saveHLFFileDialog.FileName.Length-4, 4));
                _levelFileBindingSource.ResetBindings(false);
                _levelFileListBindingSource.ResetBindings(false);
            }
        }

        private void btnBrowseMapData_Click(object sender, EventArgs e)
        {
            DialogResult dr = openMapDataDialog.ShowDialog();
            if (dr == DialogResult.OK)
            {
                ((Level)_levelFileBindingSource.Current).Map_data = HPTFileHelper.AbsoluteToRelativePath(openMapDataDialog.FileName);
                _levelFileBindingSource.ResetBindings(false);
            }
        }

        private void btnBrowseTileImage1_Click(object sender, EventArgs e)
        {
            DialogResult dr = openTilesImageDialog.ShowDialog();
            if (dr == DialogResult.OK)
            {
                ((Level)_levelFileBindingSource.Current).Tileimage_layer1 = HPTFileHelper.AbsoluteToRelativePath(openTilesImageDialog.FileName);
             
                // Open the file to calculate tile information
                FileStream fs = new FileStream(openTilesImageDialog.FileName, FileMode.Open);
                Image image = Bitmap.FromStream(fs);
                fs.Close();
                ((Level)_levelFileBindingSource.Current).Num_frontlayer_tiles = image.Width / 16;

                _levelFileBindingSource.ResetBindings(false);
            }
        }

        private void btnBrowseTileData1_Click(object sender, EventArgs e)
        {
            DialogResult dr = openTileDataDialog.ShowDialog();
            if (dr == DialogResult.OK)
            {
                ((Level)_levelFileBindingSource.Current).Tiledata_layer1 = HPTFileHelper.AbsoluteToRelativePath(openTileDataDialog.FileName);
                _levelFileBindingSource.ResetBindings(false);
            }
        }

        private void btnBrowseTileImage2_Click(object sender, EventArgs e)
        {
            DialogResult dr = openTilesImageDialog.ShowDialog();
            if (dr == DialogResult.OK)
            {
                ((Level)_levelFileBindingSource.Current).Tileimage_layer2 = HPTFileHelper.AbsoluteToRelativePath(openTilesImageDialog.FileName);
                
                // Open the file to calculate tile information
                FileStream fs = new FileStream(openTilesImageDialog.FileName, FileMode.Open);
                Image image = Bitmap.FromStream(fs);
                fs.Close();
                ((Level)_levelFileBindingSource.Current).Num_backlayer_tiles = image.Width / 16;

                _levelFileBindingSource.ResetBindings(false);
            }
        }

        private void btnBrowseTileData2_Click(object sender, EventArgs e)
        {
            DialogResult dr = openTileDataDialog.ShowDialog();
            if (dr == DialogResult.OK)
            {
                ((Level)_levelFileBindingSource.Current).Tiledata_layer2 = HPTFileHelper.AbsoluteToRelativePath(openTileDataDialog.FileName);
                _levelFileBindingSource.ResetBindings(false);
            }
        }

        #endregion
    }
}
