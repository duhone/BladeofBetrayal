namespace iPhone_Tools
{
    partial class LevelPanel
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
            this.listBox1 = new System.Windows.Forms.ListBox();
            this._levelFileListBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.label9 = new System.Windows.Forms.Label();
            this.textBox7 = new System.Windows.Forms.TextBox();
            this._levelFileBindingSource = new System.Windows.Forms.BindingSource(this.components);
            this.textBox6 = new System.Windows.Forms.TextBox();
            this.textBox5 = new System.Windows.Forms.TextBox();
            this.textBox4 = new System.Windows.Forms.TextBox();
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.textBox2 = new System.Windows.Forms.TextBox();
            this.textBox1 = new System.Windows.Forms.TextBox();
            this.groupBox2 = new System.Windows.Forms.GroupBox();
            this.btnBrowseTileImage2 = new System.Windows.Forms.Button();
            this.btnBrowseTileData2 = new System.Windows.Forms.Button();
            this.label4 = new System.Windows.Forms.Label();
            this.label5 = new System.Windows.Forms.Label();
            this.label6 = new System.Windows.Forms.Label();
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.btnBrowseTileData1 = new System.Windows.Forms.Button();
            this.btnBrowseTileImage1 = new System.Windows.Forms.Button();
            this.label1 = new System.Windows.Forms.Label();
            this.label2 = new System.Windows.Forms.Label();
            this.label3 = new System.Windows.Forms.Label();
            this.label7 = new System.Windows.Forms.Label();
            this.groupBox4 = new System.Windows.Forms.GroupBox();
            this.label11 = new System.Windows.Forms.Label();
            this.textBox9 = new System.Windows.Forms.TextBox();
            this.label8 = new System.Windows.Forms.Label();
            this.textBox8 = new System.Windows.Forms.TextBox();
            this.btnBrowseMapData = new System.Windows.Forms.Button();
            this.btnBrowseHLFFile = new System.Windows.Forms.Button();
            this.textBox12 = new System.Windows.Forms.TextBox();
            this.label10 = new System.Windows.Forms.Label();
            this.btnAddHLFFile = new System.Windows.Forms.Button();
            this.btnRemoveHLFFile = new System.Windows.Forms.Button();
            this.saveHLFFileDialog = new System.Windows.Forms.SaveFileDialog();
            this.openMapDataDialog = new System.Windows.Forms.OpenFileDialog();
            this.openTilesImageDialog = new System.Windows.Forms.OpenFileDialog();
            this.openTileDataDialog = new System.Windows.Forms.OpenFileDialog();
            ((System.ComponentModel.ISupportInitialize)(this._levelFileListBindingSource)).BeginInit();
            ((System.ComponentModel.ISupportInitialize)(this._levelFileBindingSource)).BeginInit();
            this.groupBox2.SuspendLayout();
            this.groupBox1.SuspendLayout();
            this.groupBox4.SuspendLayout();
            this.SuspendLayout();
            // 
            // listBox1
            // 
            this.listBox1.DataSource = this._levelFileListBindingSource;
            this.listBox1.DisplayMember = "File_name";
            this.listBox1.FormattingEnabled = true;
            this.listBox1.Location = new System.Drawing.Point(6, 16);
            this.listBox1.Name = "listBox1";
            this.listBox1.Size = new System.Drawing.Size(165, 251);
            this.listBox1.TabIndex = 33;
            // 
            // _levelFileListBindingSource
            // 
            this._levelFileListBindingSource.DataSource = typeof(iPhone_Tools.FileFormat.Level);
            this._levelFileListBindingSource.CurrentChanged += new System.EventHandler(this._hlfFileListBindingSource_CurrentChanged);
            // 
            // label9
            // 
            this.label9.AutoSize = true;
            this.label9.Font = new System.Drawing.Font("Microsoft Sans Serif", 8.25F, System.Drawing.FontStyle.Bold, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.label9.Location = new System.Drawing.Point(3, 0);
            this.label9.Name = "label9";
            this.label9.Size = new System.Drawing.Size(48, 13);
            this.label9.TabIndex = 32;
            this.label9.Text = "Levels:";
            // 
            // textBox7
            // 
            this.textBox7.DataBindings.Add(new System.Windows.Forms.Binding("Text", this._levelFileBindingSource, "Num_backlayer_tiles", true));
            this.textBox7.Location = new System.Drawing.Point(78, 70);
            this.textBox7.Name = "textBox7";
            this.textBox7.ReadOnly = true;
            this.textBox7.Size = new System.Drawing.Size(64, 20);
            this.textBox7.TabIndex = 30;
            // 
            // _levelFileBindingSource
            // 
            this._levelFileBindingSource.DataSource = typeof(iPhone_Tools.FileFormat.Level);
            // 
            // textBox6
            // 
            this.textBox6.DataBindings.Add(new System.Windows.Forms.Binding("Text", this._levelFileBindingSource, "Tiledata_layer2", true));
            this.textBox6.Location = new System.Drawing.Point(78, 45);
            this.textBox6.Name = "textBox6";
            this.textBox6.Size = new System.Drawing.Size(449, 20);
            this.textBox6.TabIndex = 29;
            // 
            // textBox5
            // 
            this.textBox5.DataBindings.Add(new System.Windows.Forms.Binding("Text", this._levelFileBindingSource, "Tileimage_layer2", true));
            this.textBox5.Location = new System.Drawing.Point(78, 19);
            this.textBox5.Name = "textBox5";
            this.textBox5.Size = new System.Drawing.Size(449, 20);
            this.textBox5.TabIndex = 28;
            // 
            // textBox4
            // 
            this.textBox4.DataBindings.Add(new System.Windows.Forms.Binding("Text", this._levelFileBindingSource, "Num_frontlayer_tiles", true));
            this.textBox4.Location = new System.Drawing.Point(78, 66);
            this.textBox4.Name = "textBox4";
            this.textBox4.ReadOnly = true;
            this.textBox4.Size = new System.Drawing.Size(64, 20);
            this.textBox4.TabIndex = 27;
            // 
            // textBox3
            // 
            this.textBox3.DataBindings.Add(new System.Windows.Forms.Binding("Text", this._levelFileBindingSource, "Tiledata_layer1", true));
            this.textBox3.Location = new System.Drawing.Point(78, 43);
            this.textBox3.Name = "textBox3";
            this.textBox3.Size = new System.Drawing.Size(449, 20);
            this.textBox3.TabIndex = 26;
            // 
            // textBox2
            // 
            this.textBox2.DataBindings.Add(new System.Windows.Forms.Binding("Text", this._levelFileBindingSource, "Tileimage_layer1", true));
            this.textBox2.Location = new System.Drawing.Point(78, 17);
            this.textBox2.Name = "textBox2";
            this.textBox2.Size = new System.Drawing.Size(449, 20);
            this.textBox2.TabIndex = 25;
            // 
            // textBox1
            // 
            this.textBox1.DataBindings.Add(new System.Windows.Forms.Binding("Text", this._levelFileBindingSource, "Map_data", true));
            this.textBox1.Location = new System.Drawing.Point(99, 99);
            this.textBox1.Name = "textBox1";
            this.textBox1.Size = new System.Drawing.Size(428, 20);
            this.textBox1.TabIndex = 24;
            // 
            // groupBox2
            // 
            this.groupBox2.Controls.Add(this.btnBrowseTileImage2);
            this.groupBox2.Controls.Add(this.btnBrowseTileData2);
            this.groupBox2.Controls.Add(this.label4);
            this.groupBox2.Controls.Add(this.label5);
            this.groupBox2.Controls.Add(this.label6);
            this.groupBox2.Controls.Add(this.textBox5);
            this.groupBox2.Controls.Add(this.textBox7);
            this.groupBox2.Controls.Add(this.textBox6);
            this.groupBox2.Location = new System.Drawing.Point(177, 236);
            this.groupBox2.Name = "groupBox2";
            this.groupBox2.Size = new System.Drawing.Size(614, 100);
            this.groupBox2.TabIndex = 23;
            this.groupBox2.TabStop = false;
            this.groupBox2.Text = "Scrolling Background";
            // 
            // btnBrowseTileImage2
            // 
            this.btnBrowseTileImage2.Location = new System.Drawing.Point(533, 17);
            this.btnBrowseTileImage2.Name = "btnBrowseTileImage2";
            this.btnBrowseTileImage2.Size = new System.Drawing.Size(75, 23);
            this.btnBrowseTileImage2.TabIndex = 32;
            this.btnBrowseTileImage2.Text = "Browse";
            this.btnBrowseTileImage2.UseVisualStyleBackColor = true;
            this.btnBrowseTileImage2.Click += new System.EventHandler(this.btnBrowseTileImage2_Click);
            // 
            // btnBrowseTileData2
            // 
            this.btnBrowseTileData2.Location = new System.Drawing.Point(533, 43);
            this.btnBrowseTileData2.Name = "btnBrowseTileData2";
            this.btnBrowseTileData2.Size = new System.Drawing.Size(75, 23);
            this.btnBrowseTileData2.TabIndex = 31;
            this.btnBrowseTileData2.Text = "Browse";
            this.btnBrowseTileData2.UseVisualStyleBackColor = true;
            this.btnBrowseTileData2.Click += new System.EventHandler(this.btnBrowseTileData2_Click);
            // 
            // label4
            // 
            this.label4.AutoSize = true;
            this.label4.Location = new System.Drawing.Point(6, 22);
            this.label4.Name = "label4";
            this.label4.Size = new System.Drawing.Size(66, 13);
            this.label4.TabIndex = 3;
            this.label4.Text = "Tile\'s Image:";
            // 
            // label5
            // 
            this.label5.AutoSize = true;
            this.label5.Location = new System.Drawing.Point(17, 48);
            this.label5.Name = "label5";
            this.label5.Size = new System.Drawing.Size(53, 13);
            this.label5.TabIndex = 4;
            this.label5.Text = "Tile Data:";
            // 
            // label6
            // 
            this.label6.AutoSize = true;
            this.label6.Location = new System.Drawing.Point(16, 73);
            this.label6.Name = "label6";
            this.label6.Size = new System.Drawing.Size(54, 13);
            this.label6.TabIndex = 5;
            this.label6.Text = "# of Tiles:";
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.btnBrowseTileData1);
            this.groupBox1.Controls.Add(this.btnBrowseTileImage1);
            this.groupBox1.Controls.Add(this.label1);
            this.groupBox1.Controls.Add(this.label2);
            this.groupBox1.Controls.Add(this.label3);
            this.groupBox1.Controls.Add(this.textBox2);
            this.groupBox1.Controls.Add(this.textBox3);
            this.groupBox1.Controls.Add(this.textBox4);
            this.groupBox1.Location = new System.Drawing.Point(177, 134);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Size = new System.Drawing.Size(614, 96);
            this.groupBox1.TabIndex = 22;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "Front Layer";
            // 
            // btnBrowseTileData1
            // 
            this.btnBrowseTileData1.Location = new System.Drawing.Point(533, 41);
            this.btnBrowseTileData1.Name = "btnBrowseTileData1";
            this.btnBrowseTileData1.Size = new System.Drawing.Size(75, 23);
            this.btnBrowseTileData1.TabIndex = 29;
            this.btnBrowseTileData1.Text = "Browse";
            this.btnBrowseTileData1.UseVisualStyleBackColor = true;
            this.btnBrowseTileData1.Click += new System.EventHandler(this.btnBrowseTileData1_Click);
            // 
            // btnBrowseTileImage1
            // 
            this.btnBrowseTileImage1.Location = new System.Drawing.Point(533, 15);
            this.btnBrowseTileImage1.Name = "btnBrowseTileImage1";
            this.btnBrowseTileImage1.Size = new System.Drawing.Size(75, 23);
            this.btnBrowseTileImage1.TabIndex = 28;
            this.btnBrowseTileImage1.Text = "Browse";
            this.btnBrowseTileImage1.UseVisualStyleBackColor = true;
            this.btnBrowseTileImage1.Click += new System.EventHandler(this.btnBrowseTileImage1_Click);
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(6, 20);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(66, 13);
            this.label1.TabIndex = 0;
            this.label1.Text = "Tile\'s Image:";
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(19, 46);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(53, 13);
            this.label2.TabIndex = 1;
            this.label2.Text = "Tile Data:";
            // 
            // label3
            // 
            this.label3.AutoSize = true;
            this.label3.Location = new System.Drawing.Point(18, 69);
            this.label3.Name = "label3";
            this.label3.Size = new System.Drawing.Size(54, 13);
            this.label3.TabIndex = 2;
            this.label3.Text = "# of Tiles:";
            // 
            // label7
            // 
            this.label7.AutoSize = true;
            this.label7.Location = new System.Drawing.Point(36, 102);
            this.label7.Name = "label7";
            this.label7.Size = new System.Drawing.Size(57, 13);
            this.label7.TabIndex = 20;
            this.label7.Text = "Map Data:";
            // 
            // groupBox4
            // 
            this.groupBox4.Controls.Add(this.label11);
            this.groupBox4.Controls.Add(this.textBox9);
            this.groupBox4.Controls.Add(this.label8);
            this.groupBox4.Controls.Add(this.textBox8);
            this.groupBox4.Controls.Add(this.btnBrowseMapData);
            this.groupBox4.Controls.Add(this.btnBrowseHLFFile);
            this.groupBox4.Controls.Add(this.textBox12);
            this.groupBox4.Controls.Add(this.label10);
            this.groupBox4.Controls.Add(this.label7);
            this.groupBox4.Controls.Add(this.textBox1);
            this.groupBox4.Location = new System.Drawing.Point(177, 3);
            this.groupBox4.Name = "groupBox4";
            this.groupBox4.Size = new System.Drawing.Size(614, 125);
            this.groupBox4.TabIndex = 34;
            this.groupBox4.TabStop = false;
            this.groupBox4.Text = "Level Properties";
            // 
            // label11
            // 
            this.label11.AutoSize = true;
            this.label11.Location = new System.Drawing.Point(9, 73);
            this.label11.Name = "label11";
            this.label11.Size = new System.Drawing.Size(113, 13);
            this.label11.TabIndex = 39;
            this.label11.Text = "Back HTF Output File:";
            // 
            // textBox9
            // 
            this.textBox9.DataBindings.Add(new System.Windows.Forms.Binding("Text", this._levelFileBindingSource, "Back_HTF_file_path", true));
            this.textBox9.Location = new System.Drawing.Point(126, 70);
            this.textBox9.Name = "textBox9";
            this.textBox9.ReadOnly = true;
            this.textBox9.Size = new System.Drawing.Size(401, 20);
            this.textBox9.TabIndex = 38;
            // 
            // label8
            // 
            this.label8.AutoSize = true;
            this.label8.Location = new System.Drawing.Point(9, 47);
            this.label8.Name = "label8";
            this.label8.Size = new System.Drawing.Size(112, 13);
            this.label8.TabIndex = 37;
            this.label8.Text = "Front HTF Output File:";
            // 
            // textBox8
            // 
            this.textBox8.DataBindings.Add(new System.Windows.Forms.Binding("Text", this._levelFileBindingSource, "Front_HTF_file_path", true));
            this.textBox8.Location = new System.Drawing.Point(126, 44);
            this.textBox8.Name = "textBox8";
            this.textBox8.ReadOnly = true;
            this.textBox8.Size = new System.Drawing.Size(401, 20);
            this.textBox8.TabIndex = 36;
            // 
            // btnBrowseMapData
            // 
            this.btnBrowseMapData.Location = new System.Drawing.Point(533, 99);
            this.btnBrowseMapData.Name = "btnBrowseMapData";
            this.btnBrowseMapData.Size = new System.Drawing.Size(75, 23);
            this.btnBrowseMapData.TabIndex = 35;
            this.btnBrowseMapData.Text = "Browse";
            this.btnBrowseMapData.UseVisualStyleBackColor = true;
            this.btnBrowseMapData.Click += new System.EventHandler(this.btnBrowseMapData_Click);
            // 
            // btnBrowseHLFFile
            // 
            this.btnBrowseHLFFile.Location = new System.Drawing.Point(533, 15);
            this.btnBrowseHLFFile.Name = "btnBrowseHLFFile";
            this.btnBrowseHLFFile.Size = new System.Drawing.Size(75, 23);
            this.btnBrowseHLFFile.TabIndex = 2;
            this.btnBrowseHLFFile.Text = "Browse";
            this.btnBrowseHLFFile.UseVisualStyleBackColor = true;
            this.btnBrowseHLFFile.Click += new System.EventHandler(this.btnBrowseHLFFile_Click);
            // 
            // textBox12
            // 
            this.textBox12.DataBindings.Add(new System.Windows.Forms.Binding("Text", this._levelFileBindingSource, "HLF_file_path", true));
            this.textBox12.Location = new System.Drawing.Point(126, 17);
            this.textBox12.Name = "textBox12";
            this.textBox12.ReadOnly = true;
            this.textBox12.Size = new System.Drawing.Size(401, 20);
            this.textBox12.TabIndex = 1;
            // 
            // label10
            // 
            this.label10.AutoSize = true;
            this.label10.Location = new System.Drawing.Point(36, 20);
            this.label10.Name = "label10";
            this.label10.Size = new System.Drawing.Size(84, 13);
            this.label10.TabIndex = 0;
            this.label10.Text = "HLF Output File:";
            // 
            // btnAddHLFFile
            // 
            this.btnAddHLFFile.Location = new System.Drawing.Point(6, 273);
            this.btnAddHLFFile.Name = "btnAddHLFFile";
            this.btnAddHLFFile.Size = new System.Drawing.Size(165, 23);
            this.btnAddHLFFile.TabIndex = 35;
            this.btnAddHLFFile.Text = "Add Level";
            this.btnAddHLFFile.UseVisualStyleBackColor = true;
            this.btnAddHLFFile.Click += new System.EventHandler(this.btnAddHLFFile_Click);
            // 
            // btnRemoveHLFFile
            // 
            this.btnRemoveHLFFile.Location = new System.Drawing.Point(6, 302);
            this.btnRemoveHLFFile.Name = "btnRemoveHLFFile";
            this.btnRemoveHLFFile.Size = new System.Drawing.Size(165, 23);
            this.btnRemoveHLFFile.TabIndex = 36;
            this.btnRemoveHLFFile.Text = "Remove Level";
            this.btnRemoveHLFFile.UseVisualStyleBackColor = true;
            this.btnRemoveHLFFile.Click += new System.EventHandler(this.btnRemoveHLFFile_Click);
            // 
            // saveHLFFileDialog
            // 
            this.saveHLFFileDialog.Filter = "HLF files|*.hlf|All files|*.*";
            this.saveHLFFileDialog.Title = "HLF File Location";
            // 
            // openMapDataDialog
            // 
            this.openMapDataDialog.Filter = "Map data|*.dat|All files|*.*";
            this.openMapDataDialog.Title = "Map Data File Location";
            // 
            // openTilesImageDialog
            // 
            this.openTilesImageDialog.Filter = "Tile image|*.png|All files|*.*";
            this.openTilesImageDialog.Title = "Tile\'s Image Location";
            // 
            // openTileDataDialog
            // 
            this.openTileDataDialog.Filter = "Tile data|*.td|All files|*.*";
            this.openTileDataDialog.Title = "Tile Data Location";
            // 
            // LevelPanel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.btnRemoveHLFFile);
            this.Controls.Add(this.btnAddHLFFile);
            this.Controls.Add(this.groupBox4);
            this.Controls.Add(this.listBox1);
            this.Controls.Add(this.label9);
            this.Controls.Add(this.groupBox2);
            this.Controls.Add(this.groupBox1);
            this.Name = "LevelPanel";
            this.Size = new System.Drawing.Size(800, 350);
            ((System.ComponentModel.ISupportInitialize)(this._levelFileListBindingSource)).EndInit();
            ((System.ComponentModel.ISupportInitialize)(this._levelFileBindingSource)).EndInit();
            this.groupBox2.ResumeLayout(false);
            this.groupBox2.PerformLayout();
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.groupBox4.ResumeLayout(false);
            this.groupBox4.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.ListBox listBox1;
        private System.Windows.Forms.Label label9;
        private System.Windows.Forms.TextBox textBox7;
        private System.Windows.Forms.TextBox textBox6;
        private System.Windows.Forms.TextBox textBox5;
        private System.Windows.Forms.TextBox textBox4;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.TextBox textBox2;
        private System.Windows.Forms.TextBox textBox1;
        private System.Windows.Forms.GroupBox groupBox2;
        private System.Windows.Forms.Label label4;
        private System.Windows.Forms.Label label5;
        private System.Windows.Forms.Label label6;
        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.Label label3;
        private System.Windows.Forms.Label label7;
        private System.Windows.Forms.GroupBox groupBox4;
        private System.Windows.Forms.Button btnBrowseHLFFile;
        private System.Windows.Forms.TextBox textBox12;
        private System.Windows.Forms.Label label10;
        private System.Windows.Forms.Button btnBrowseMapData;
        private System.Windows.Forms.Button btnBrowseTileImage2;
        private System.Windows.Forms.Button btnBrowseTileData2;
        private System.Windows.Forms.Button btnBrowseTileData1;
        private System.Windows.Forms.Button btnBrowseTileImage1;
        private System.Windows.Forms.BindingSource _levelFileListBindingSource;
        private System.Windows.Forms.Button btnAddHLFFile;
        private System.Windows.Forms.Button btnRemoveHLFFile;
        private System.Windows.Forms.BindingSource _levelFileBindingSource;
        private System.Windows.Forms.SaveFileDialog saveHLFFileDialog;
        private System.Windows.Forms.OpenFileDialog openMapDataDialog;
        private System.Windows.Forms.OpenFileDialog openTilesImageDialog;
        private System.Windows.Forms.OpenFileDialog openTileDataDialog;
        private System.Windows.Forms.Label label8;
        private System.Windows.Forms.TextBox textBox8;
        private System.Windows.Forms.Label label11;
        private System.Windows.Forms.TextBox textBox9;
    }
}
