namespace iPhone_Tools
{
    partial class HGFPanel
    {
        /// <summary> 
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary> 
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Component Designer generated code

        /// <summary> 
        /// Required method for Designer support - do not modify 
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.btnBrowseHGFFile = new System.Windows.Forms.Button();
            this.textBox12 = new System.Windows.Forms.TextBox();
            this._hgfFileBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.label3 = new System.Windows.Forms.Label();
            this.groupBox3 = new System.Windows.Forms.GroupBox();
            this.btnRemoveImage = new System.Windows.Forms.Button();
            this.btnAddImage = new System.Windows.Forms.Button();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.m_highQualityCBox = new System.Windows.Forms.CheckBox();
            this._hptImageBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.frameSetNumericUpDown = new System.Windows.Forms.NumericUpDown();
            this.txtImageIndex = new System.Windows.Forms.TextBox();
            this.btnBrowseImage = new System.Windows.Forms.Button();
            this.textBox7 = new System.Windows.Forms.TextBox();
            this.frameSetFramesTextBox = new System.Windows.Forms.TextBox();
            this.txtFrameSets = new System.Windows.Forms.TextBox();
            this.checkBox1 = new System.Windows.Forms.CheckBox();
            this.textBox4 = new System.Windows.Forms.TextBox();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.label9 = new System.Windows.Forms.Label();
            this.label8 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label4 = new System.Windows.Forms.Label();
            this.comboBox1 = new System.Windows.Forms.ComboBox();
            this._hptImageListBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.label2 = new System.Windows.Forms.Label();
            this.label1 = new System.Windows.Forms.Label();
            this.listBox1 = new System.Windows.Forms.ListBox();
            this._hgfFileListBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.saveHGFileDialog = new System.Windows.Forms.SaveFileDialog();
            this.btnAddHGFFile = new System.Windows.Forms.Button();
            this.btnRemoveHGFFile = new System.Windows.Forms.Button();
            this.openImageDialog = new System.Windows.Forms.OpenFileDialog();
            this.ChangeAssetListButton = new System.Windows.Forms.Button();
            this.AssetListTextBox = new System.Windows.Forms.TextBox();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.button1 = new System.Windows.Forms.Button();
            this.assetListFileDialog = new System.Windows.Forms.OpenFileDialog();
            this.button2 = new System.Windows.Forms.Button();
            this.groupBox4.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this._hgfFileBindingSource)).BeginInit();
            this.groupBox3.SuspendLayout();
            this.groupBox2.SuspendLayout();
            ((System.ComponentModel.ISupportInitialize)(this._hptImageBindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this.frameSetNumericUpDown)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this._hptImageListBindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this._hgfFileListBindingSource)).BeginInit();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.btnBrowseHGFFile);
            this.groupBox4.Controls.Add(this.textBox12);
            this.groupBox4.Controls.Add(this.label3);
            this.groupBox4.Enabled = false;
            this.groupBox4.Location = new System.Drawing.Point(232, 4);
            this.groupBox4.Margin = new System.Windows.Forms.Padding(4);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Padding = new System.Windows.Forms.Padding(4);
            this.groupBox4.Size = new System.Drawing.Size(819, 58);
            this.groupBox4.TabIndex = 9;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "HGF Properties";
            // 
            // btnBrowseHGFFile
            // 
            this.btnBrowseHGFFile.Location = new System.Drawing.Point(711, 15);
            this.btnBrowseHGFFile.Margin = new System.Windows.Forms.Padding(4);
            this.btnBrowseHGFFile.Name = "btnBrowseHGFFile";
            this.btnBrowseHGFFile.Size = new System.Drawing.Size(100, 28);
            this.btnBrowseHGFFile.TabIndex = 2;
            this.btnBrowseHGFFile.Text = "Browse";
            this.btnBrowseHGFFile.UseVisualStyleBackColor = true;
            this.btnBrowseHGFFile.Click += new System.EventHandler(this.btnBrowseHGFFile_Click);
            // 
            // textBox12
            // 
            this.textBox12.DataBindings.Add(new System.Windows.Forms.Binding("Text", this._hgfFileBindingSource, "Full_path_name", true));
            this.textBox12.Location = new System.Drawing.Point(99, 15);
            this.textBox12.Margin = new System.Windows.Forms.Padding(4);
            this.textBox12.Name = "textBox12";
            this.textBox12.Size = new System.Drawing.Size(603, 22);
            this.textBox12.TabIndex = 1;
            // 
            // _hgfFileBindingSource
            // 
            this._hgfFileBindingSource.DataSource = typeof(iPhone_Tools.FileFormat.HGFFile);
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(9, 25);
            this.label3.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(81, 17);
            this.label3.TabIndex = 0;
            this.label3.Text = "Output File:";
            // 
            // groupBox3
            // 
            this.groupBox3.Controls.Add(this.btnRemoveImage);
            this.groupBox3.Controls.Add(this.btnAddImage);
            this.groupBox3.Enabled = false;
            this.groupBox3.Location = new System.Drawing.Point(845, 73);
            this.groupBox3.Margin = new System.Windows.Forms.Padding(4);
            this.groupBox3.Name = "groupBox3";
            this.groupBox3.Padding = new System.Windows.Forms.Padding(4);
            this.groupBox3.Size = new System.Drawing.Size(205, 345);
            this.groupBox3.TabIndex = 8;
            this.groupBox3.TabStop = false;
            this.groupBox3.Text = "HGF Actions";
            // 
            // btnRemoveImage
            // 
            this.btnRemoveImage.Location = new System.Drawing.Point(9, 60);
            this.btnRemoveImage.Margin = new System.Windows.Forms.Padding(4);
            this.btnRemoveImage.Name = "btnRemoveImage";
            this.btnRemoveImage.Size = new System.Drawing.Size(188, 28);
            this.btnRemoveImage.TabIndex = 1;
            this.btnRemoveImage.Text = "Remove Image";
            this.btnRemoveImage.UseVisualStyleBackColor = true;
            this.btnRemoveImage.Click += new System.EventHandler(this.btnRemoveImage_Click);
            // 
            // btnAddImage
            // 
            this.btnAddImage.Location = new System.Drawing.Point(8, 23);
            this.btnAddImage.Margin = new System.Windows.Forms.Padding(4);
            this.btnAddImage.Name = "btnAddImage";
            this.btnAddImage.Size = new System.Drawing.Size(189, 28);
            this.btnAddImage.TabIndex = 0;
            this.btnAddImage.Text = "Add Image";
            this.btnAddImage.UseVisualStyleBackColor = true;
            this.btnAddImage.Click += new System.EventHandler(this.btnAddImage_Click);
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.m_highQualityCBox);
            this.groupBox2.Controls.Add(this.frameSetNumericUpDown);
            this.groupBox2.Controls.Add(this.txtImageIndex);
            this.groupBox2.Controls.Add(this.btnBrowseImage);
            this.groupBox2.Controls.Add(this.textBox7);
            this.groupBox2.Controls.Add(this.frameSetFramesTextBox);
            this.groupBox2.Controls.Add(this.txtFrameSets);
            this.groupBox2.Controls.Add(this.checkBox1);
            this.groupBox2.Controls.Add(this.textBox4);
            this.groupBox2.Controls.Add(this.textBox3);
            this.groupBox2.Controls.Add(this.textBox2);
            this.groupBox2.Controls.Add(this.textBox1);
            this.groupBox2.Controls.Add(this.label10);
            this.groupBox2.Controls.Add(this.label9);
            this.groupBox2.Controls.Add(this.label8);
            this.groupBox2.Controls.Add(this.label7);
            this.groupBox2.Controls.Add(this.label6);
            this.groupBox2.Controls.Add(this.label5);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.comboBox1);
            this.groupBox2.Controls.Add(this.label2);
            this.groupBox2.Enabled = false;
            this.groupBox2.Location = new System.Drawing.Point(232, 69);
            this.groupBox2.Margin = new System.Windows.Forms.Padding(4);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Padding = new System.Windows.Forms.Padding(4);
            this.groupBox2.Size = new System.Drawing.Size(605, 348);
            this.groupBox2.TabIndex = 5;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "HGF Contents";
            // 
            // m_highQualityCBox
            // 
            this.m_highQualityCBox.AutoSize = true;
            this.m_highQualityCBox.DataBindings.Add(new System.Windows.Forms.Binding("Checked", this._hptImageBindingSource, "HighQuality", true));
            this.m_highQualityCBox.Location = new System.Drawing.Point(328, 130);
            this.m_highQualityCBox.Name = "m_highQualityCBox";
            this.m_highQualityCBox.Size = new System.Drawing.Size(103, 21);
            this.m_highQualityCBox.TabIndex = 29;
            this.m_highQualityCBox.Text = "HighQuality";
            this.m_highQualityCBox.UseVisualStyleBackColor = true;
            // 
            // _hptImageBindingSource
            // 
            this._hptImageBindingSource.DataSource = typeof(iPhone_Tools.FileFormat.HPTImage);
            // 
            // frameSetNumericUpDown
            // 
            this.frameSetNumericUpDown.Location = new System.Drawing.Point(141, 239);
            this.frameSetNumericUpDown.Margin = new System.Windows.Forms.Padding(4);
            this.frameSetNumericUpDown.Name = "frameSetNumericUpDown";
            this.frameSetNumericUpDown.Size = new System.Drawing.Size(64, 22);
            this.frameSetNumericUpDown.TabIndex = 28;
            this.frameSetNumericUpDown.ValueChanged += new System.EventHandler(this.frameSetNumericUpDown_ValueChanged);
            // 
            // txtImageIndex
            // 
            this.txtImageIndex.Location = new System.Drawing.Point(537, 21);
            this.txtImageIndex.Margin = new System.Windows.Forms.Padding(4);
            this.txtImageIndex.Name = "txtImageIndex";
            this.txtImageIndex.ReadOnly = true;
            this.txtImageIndex.Size = new System.Drawing.Size(59, 22);
            this.txtImageIndex.TabIndex = 27;
            // 
            // btnBrowseImage
            // 
            this.btnBrowseImage.Location = new System.Drawing.Point(497, 98);
            this.btnBrowseImage.Margin = new System.Windows.Forms.Padding(4);
            this.btnBrowseImage.Name = "btnBrowseImage";
            this.btnBrowseImage.Size = new System.Drawing.Size(100, 28);
            this.btnBrowseImage.TabIndex = 26;
            this.btnBrowseImage.Text = "Browse";
            this.btnBrowseImage.UseVisualStyleBackColor = true;
            this.btnBrowseImage.Click += new System.EventHandler(this.btnBrowseImage_Click);
            // 
            // textBox7
            // 
            this.textBox7.DataBindings.Add(new System.Windows.Forms.Binding("Text", this._hptImageBindingSource, "Default_frame_rate", true));
            this.textBox7.Location = new System.Drawing.Point(140, 273);
            this.textBox7.Margin = new System.Windows.Forms.Padding(4);
            this.textBox7.Name = "textBox7";
            this.textBox7.Size = new System.Drawing.Size(132, 22);
            this.textBox7.TabIndex = 22;
            // 
            // frameSetFramesTextBox
            // 
            this.frameSetFramesTextBox.Location = new System.Drawing.Point(213, 239);
            this.frameSetFramesTextBox.Margin = new System.Windows.Forms.Padding(4);
            this.frameSetFramesTextBox.Name = "frameSetFramesTextBox";
            this.frameSetFramesTextBox.Size = new System.Drawing.Size(59, 22);
            this.frameSetFramesTextBox.TabIndex = 21;
            this.frameSetFramesTextBox.Validated += new System.EventHandler(this.frameSetFramesTextBox_Validated);
            // 
            // txtFrameSets
            // 
            this.txtFrameSets.DataBindings.Add(new System.Windows.Forms.Binding("Text", this._hptImageBindingSource, "Num_frame_sets", true));
            this.txtFrameSets.Location = new System.Drawing.Point(141, 209);
            this.txtFrameSets.Margin = new System.Windows.Forms.Padding(4);
            this.txtFrameSets.Name = "txtFrameSets";
            this.txtFrameSets.Size = new System.Drawing.Size(132, 22);
            this.txtFrameSets.TabIndex = 20;
            this.txtFrameSets.Validated += new System.EventHandler(this.txtFrameSets_Validated);
            this.txtFrameSets.Validating += new System.ComponentModel.CancelEventHandler(this.txtFrameSets_Validating);
            // 
            // checkBox1
            // 
            this.checkBox1.AutoSize = true;
            this.checkBox1.DataBindings.Add(new System.Windows.Forms.Binding("Checked", this._hptImageBindingSource, "Default_auto_animate", true));
            this.checkBox1.Location = new System.Drawing.Point(140, 305);
            this.checkBox1.Margin = new System.Windows.Forms.Padding(4);
            this.checkBox1.Name = "checkBox1";
            this.checkBox1.Size = new System.Drawing.Size(114, 21);
            this.checkBox1.TabIndex = 19;
            this.checkBox1.Text = "Auto Animate";
            this.checkBox1.UseVisualStyleBackColor = true;
            // 
            // textBox4
            // 
            this.textBox4.DataBindings.Add(new System.Windows.Forms.Binding("Text", this._hptImageBindingSource, "Height", true));
            this.textBox4.Location = new System.Drawing.Point(141, 162);
            this.textBox4.Margin = new System.Windows.Forms.Padding(4);
            this.textBox4.Name = "textBox4";
            this.textBox4.Size = new System.Drawing.Size(132, 22);
            this.textBox4.TabIndex = 18;
            // 
            // textBox3
            // 
            this.textBox3.DataBindings.Add(new System.Windows.Forms.Binding("Text", this._hptImageBindingSource, "Width", true));
            this.textBox3.Location = new System.Drawing.Point(141, 130);
            this.textBox3.Margin = new System.Windows.Forms.Padding(4);
            this.textBox3.Name = "textBox3";
            this.textBox3.Size = new System.Drawing.Size(132, 22);
            this.textBox3.TabIndex = 17;
            // 
            // textBox2
            // 
            this.textBox2.DataBindings.Add(new System.Windows.Forms.Binding("Text", this._hptImageBindingSource, "Full_path_name", true));
            this.textBox2.Location = new System.Drawing.Point(141, 98);
            this.textBox2.Margin = new System.Windows.Forms.Padding(4);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(347, 22);
            this.textBox2.TabIndex = 16;
            // 
            // textBox1
            // 
            this.textBox1.DataBindings.Add(new System.Windows.Forms.Binding("Text", this._hptImageBindingSource, "Desc", true));
            this.textBox1.Location = new System.Drawing.Point(141, 66);
            this.textBox1.Margin = new System.Windows.Forms.Padding(4);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(347, 22);
            this.textBox1.TabIndex = 15;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(45, 273);
            this.label10.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(86, 17);
            this.label10.TabIndex = 10;
            this.label10.Text = "Frame Rate:";
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Location = new System.Drawing.Point(7, 241);
            this.label9.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(124, 17);
            this.label9.TabIndex = 9;
            this.label9.Text = "FrameSet/Frames:";
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(48, 209);
            this.label8.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(84, 17);
            this.label8.TabIndex = 8;
            this.label8.Text = "Frame Sets:";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(35, 162);
            this.label7.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(97, 17);
            this.label7.TabIndex = 7;
            this.label7.Text = "Frame Height:";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(39, 130);
            this.label6.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(92, 17);
            this.label6.TabIndex = 6;
            this.label6.Text = "Frame Width:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(21, 98);
            this.label5.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(108, 17);
            this.label5.TabIndex = 5;
            this.label5.Text = "Image Location:";
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(49, 70);
            this.label4.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(83, 17);
            this.label4.TabIndex = 4;
            this.label4.Text = "Description:";
            // 
            // comboBox1
            // 
            this.comboBox1.DataSource = this._hptImageListBindingSource;
            this.comboBox1.DisplayMember = "Desc";
            this.comboBox1.FormattingEnabled = true;
            this.comboBox1.Location = new System.Drawing.Point(69, 25);
            this.comboBox1.Margin = new System.Windows.Forms.Padding(4);
            this.comboBox1.Name = "comboBox1";
            this.comboBox1.Size = new System.Drawing.Size(459, 24);
            this.comboBox1.TabIndex = 1;
            // 
            // _hptImageListBindingSource
            // 
            this._hptImageListBindingSource.DataSource = typeof(iPhone_Tools.FileFormat.HPTImage);
            this._hptImageListBindingSource.CurrentChanged += new System.EventHandler(this._hptImageListBindingSource_CurrentChanged);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(9, 25);
            this.label2.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(50, 17);
            this.label2.TabIndex = 0;
            this.label2.Text = "Image:";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label1.Location = new System.Drawing.Point(4, 4);
            this.label1.Margin = new System.Windows.Forms.Padding(4, 0, 4, 0);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(84, 17);
            this.label1.TabIndex = 7;
            this.label1.Text = "HGF Files:";
            // 
            // listBox1
            // 
            this.listBox1.DataSource = this._hgfFileListBindingSource;
            this.listBox1.DisplayMember = "File_name";
            this.listBox1.FormattingEnabled = true;
            this.listBox1.ItemHeight = 16;
            this.listBox1.Location = new System.Drawing.Point(4, 28);
            this.listBox1.Margin = new System.Windows.Forms.Padding(4);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(219, 404);
            this.listBox1.TabIndex = 6;
            // 
            // _hgfFileListBindingSource
            // 
            this._hgfFileListBindingSource.DataSource = typeof(iPhone_Tools.FileFormat.HGFFile);
            this._hgfFileListBindingSource.CurrentChanged += new System.EventHandler(this._hgfFileListBindingSource_CurrentChanged);
            // 
            // saveHGFileDialog
            // 
            this.saveHGFileDialog.DefaultExt = "hgf";
            this.saveHGFileDialog.Filter = "HGF files|*.hgf|All files|*.*";
            this.saveHGFileDialog.Title = "HGF File Location";
            // 
            // btnAddHGFFile
            // 
            this.btnAddHGFFile.Location = new System.Drawing.Point(3, 450);
            this.btnAddHGFFile.Margin = new System.Windows.Forms.Padding(4);
            this.btnAddHGFFile.Name = "btnAddHGFFile";
            this.btnAddHGFFile.Size = new System.Drawing.Size(220, 28);
            this.btnAddHGFFile.TabIndex = 10;
            this.btnAddHGFFile.Text = "Add HGF File";
            this.btnAddHGFFile.UseVisualStyleBackColor = true;
            this.btnAddHGFFile.Click += new System.EventHandler(this.btnAddHGFFile_Click);
            // 
            // btnRemoveHGFFile
            // 
            this.btnRemoveHGFFile.Location = new System.Drawing.Point(4, 490);
            this.btnRemoveHGFFile.Margin = new System.Windows.Forms.Padding(4);
            this.btnRemoveHGFFile.Name = "btnRemoveHGFFile";
            this.btnRemoveHGFFile.Size = new System.Drawing.Size(220, 28);
            this.btnRemoveHGFFile.TabIndex = 11;
            this.btnRemoveHGFFile.Text = "Remove HGF File";
            this.btnRemoveHGFFile.UseVisualStyleBackColor = true;
            this.btnRemoveHGFFile.Click += new System.EventHandler(this.btnRemoveHGFFile_Click);
            // 
            // openImageDialog
            // 
            this.openImageDialog.DefaultExt = "png";
            this.openImageDialog.Filter = "png files|*.png|All files|*.*";
            this.openImageDialog.Title = "Open Image File";
            // 
            // ChangeAssetListButton
            // 
            this.ChangeAssetListButton.Location = new System.Drawing.Point(252, 32);
            this.ChangeAssetListButton.Name = "ChangeAssetListButton";
            this.ChangeAssetListButton.Size = new System.Drawing.Size(174, 23);
            this.ChangeAssetListButton.TabIndex = 14;
            this.ChangeAssetListButton.Text = "Change Asset List File";
            this.ChangeAssetListButton.UseVisualStyleBackColor = true;
            this.ChangeAssetListButton.Click += new System.EventHandler(this.ChangeAssetListButton_Click);
            // 
            // AssetListTextBox
            // 
            this.AssetListTextBox.Location = new System.Drawing.Point(6, 32);
            this.AssetListTextBox.Name = "AssetListTextBox";
            this.AssetListTextBox.Size = new System.Drawing.Size(240, 22);
            this.AssetListTextBox.TabIndex = 13;
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.button1);
            this.groupBox1.Controls.Add(this.AssetListTextBox);
            this.groupBox1.Controls.Add(this.ChangeAssetListButton);
            this.groupBox1.Location = new System.Drawing.Point(232, 424);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(605, 95);
            this.groupBox1.TabIndex = 15;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Asset List";
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(6, 66);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(240, 23);
            this.button1.TabIndex = 15;
            this.button1.Text = "Create Asset List";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // assetListFileDialog
            // 
            this.assetListFileDialog.CheckFileExists = false;
            this.assetListFileDialog.DefaultExt = "h";
            this.assetListFileDialog.Filter = "c++ Header Files|*.h";
            this.assetListFileDialog.RestoreDirectory = true;
            // 
            // button2
            // 
            this.button2.Font = new System.Drawing.Font("Microsoft Sans Serif", 16F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.button2.Location = new System.Drawing.Point(845, 426);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(197, 87);
            this.button2.TabIndex = 16;
            this.button2.Text = "Generate HGF File";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // HGFPanel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.button2);
            this.Controls.Add(this.groupBox1);
            this.Controls.Add(this.btnRemoveHGFFile);
            this.Controls.Add(this.btnAddHGFFile);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.groupBox3);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.listBox1);
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "HGFPanel";
            this.Size = new System.Drawing.Size(1067, 522);
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this._hgfFileBindingSource)).EndInit();
            this.groupBox3.ResumeLayout(false);
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            ((System.ComponentModel.ISupportInitialize)(this._hptImageBindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this.frameSetNumericUpDown)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this._hptImageListBindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this._hgfFileListBindingSource)).EndInit();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Button btnBrowseHGFFile;
        private System.Windows.Forms.TextBox textBox12;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.GroupBox groupBox3;
        private System.Windows.Forms.Button btnRemoveImage;
        private System.Windows.Forms.Button btnAddImage;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.TextBox txtImageIndex;
        private System.Windows.Forms.Button btnBrowseImage;
        private System.Windows.Forms.TextBox textBox7;
        private System.Windows.Forms.TextBox frameSetFramesTextBox;
        private System.Windows.Forms.TextBox txtFrameSets;
        private System.Windows.Forms.CheckBox checkBox1;
        private System.Windows.Forms.TextBox textBox4;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.ComboBox comboBox1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.BindingSource _hgfFileListBindingSource;
        private System.Windows.Forms.BindingSource _hgfFileBindingSource;
        private System.Windows.Forms.BindingSource _hptImageListBindingSource;
        private System.Windows.Forms.BindingSource _hptImageBindingSource;
        private System.Windows.Forms.SaveFileDialog saveHGFileDialog;
        private System.Windows.Forms.Button btnAddHGFFile;
        private System.Windows.Forms.Button btnRemoveHGFFile;
        private System.Windows.Forms.OpenFileDialog openImageDialog;
        private System.Windows.Forms.NumericUpDown frameSetNumericUpDown;
        private System.Windows.Forms.Button ChangeAssetListButton;
        private System.Windows.Forms.TextBox AssetListTextBox;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.OpenFileDialog assetListFileDialog;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.CheckBox m_highQualityCBox;
    }
}
