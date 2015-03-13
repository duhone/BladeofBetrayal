namespace iPhone_Tools
{
    partial class frmMain
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

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.openHGPDialog = new System.Windows.Forms.OpenFileDialog();
            this.tabControl1 = new System.Windows.Forms.TabControl();
            this.tabQuickTools = new System.Windows.Forms.TabPage();
            this.quickToolsPanel1 = new iPhone_Tools.QuickToolsPanel();
            this.tabHGF = new System.Windows.Forms.TabPage();
            this.hgfPanel1 = new iPhone_Tools.HGFPanel();
            this.tabHLFHTF = new System.Windows.Forms.TabPage();
            this.levelPanel1 = new iPhone_Tools.LevelPanel();
            this.logMessages = new System.Windows.Forms.RichTextBox();
            this.splitContainer1 = new System.Windows.Forms.SplitContainer();
            this.menuStrip1 = new System.Windows.Forms.MenuStrip();
            this.fileToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newGameToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.openGameToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.saveGameToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.closeGameToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.buildToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.graphicsBuilderToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.buildAssetListToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.levelBuilderToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.allLevelsToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.selectedLevelToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.convertOldHTFsToIPhoneToolStripMenuItem = new System.Windows.Forms.ToolStripMenuItem();
            this.newHGPDialog = new System.Windows.Forms.SaveFileDialog();
            this.tabControl1.SuspendLayout();
            this.tabQuickTools.SuspendLayout();
            this.tabHGF.SuspendLayout();
            this.tabHLFHTF.SuspendLayout();
            this.splitContainer1.Panel1.SuspendLayout();
            this.splitContainer1.Panel2.SuspendLayout();
            this.splitContainer1.SuspendLayout();
            this.menuStrip1.SuspendLayout();
            this.SuspendLayout();
            // 
            // openHGPDialog
            // 
            this.openHGPDialog.DefaultExt = "hgp";
            this.openHGPDialog.Filter = "hgp files|*.hgp|All files|*.*";
            this.openHGPDialog.Title = "Open HGP";
            // 
            // tabControl1
            // 
            this.tabControl1.Controls.Add(this.tabQuickTools);
            this.tabControl1.Controls.Add(this.tabHGF);
            this.tabControl1.Controls.Add(this.tabHLFHTF);
            this.tabControl1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.tabControl1.Location = new System.Drawing.Point(0, 0);
            this.tabControl1.Margin = new System.Windows.Forms.Padding(4);
            this.tabControl1.Name = "tabControl1";
            this.tabControl1.SelectedIndex = 0;
            this.tabControl1.Size = new System.Drawing.Size(1095, 574);
            this.tabControl1.TabIndex = 2;
            this.tabControl1.SelectedIndexChanged += new System.EventHandler(this.tabControl1_SelectedIndexChanged);
            // 
            // tabQuickTools
            // 
            this.tabQuickTools.Controls.Add(this.quickToolsPanel1);
            this.tabQuickTools.Location = new System.Drawing.Point(4, 25);
            this.tabQuickTools.Margin = new System.Windows.Forms.Padding(4);
            this.tabQuickTools.Name = "tabQuickTools";
            this.tabQuickTools.Padding = new System.Windows.Forms.Padding(4);
            this.tabQuickTools.Size = new System.Drawing.Size(1087, 545);
            this.tabQuickTools.TabIndex = 0;
            this.tabQuickTools.Text = "Quick Tools";
            this.tabQuickTools.UseVisualStyleBackColor = true;
            // 
            // quickToolsPanel1
            // 
            this.quickToolsPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.quickToolsPanel1.Location = new System.Drawing.Point(4, 4);
            this.quickToolsPanel1.Margin = new System.Windows.Forms.Padding(5);
            this.quickToolsPanel1.Name = "quickToolsPanel1";
            this.quickToolsPanel1.Size = new System.Drawing.Size(1079, 537);
            this.quickToolsPanel1.TabIndex = 0;
            // 
            // tabHGF
            // 
            this.tabHGF.Controls.Add(this.hgfPanel1);
            this.tabHGF.Location = new System.Drawing.Point(4, 25);
            this.tabHGF.Margin = new System.Windows.Forms.Padding(4);
            this.tabHGF.Name = "tabHGF";
            this.tabHGF.Size = new System.Drawing.Size(1087, 545);
            this.tabHGF.TabIndex = 1;
            this.tabHGF.Text = "Graphics (.hgf)";
            this.tabHGF.UseVisualStyleBackColor = true;
            // 
            // hgfPanel1
            // 
            this.hgfPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.hgfPanel1.Location = new System.Drawing.Point(0, 0);
            this.hgfPanel1.Margin = new System.Windows.Forms.Padding(5);
            this.hgfPanel1.Name = "hgfPanel1";
            this.hgfPanel1.Size = new System.Drawing.Size(1087, 545);
            this.hgfPanel1.TabIndex = 0;
            // 
            // tabHLFHTF
            // 
            this.tabHLFHTF.Controls.Add(this.levelPanel1);
            this.tabHLFHTF.Location = new System.Drawing.Point(4, 25);
            this.tabHLFHTF.Margin = new System.Windows.Forms.Padding(4);
            this.tabHLFHTF.Name = "tabHLFHTF";
            this.tabHLFHTF.Padding = new System.Windows.Forms.Padding(4);
            this.tabHLFHTF.Size = new System.Drawing.Size(1087, 545);
            this.tabHLFHTF.TabIndex = 2;
            this.tabHLFHTF.Text = "Levels and Tiles (.hlf, .htf)";
            this.tabHLFHTF.UseVisualStyleBackColor = true;
            // 
            // levelPanel1
            // 
            this.levelPanel1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.levelPanel1.Location = new System.Drawing.Point(4, 4);
            this.levelPanel1.Margin = new System.Windows.Forms.Padding(5);
            this.levelPanel1.Name = "levelPanel1";
            this.levelPanel1.Size = new System.Drawing.Size(1079, 537);
            this.levelPanel1.TabIndex = 0;
            // 
            // logMessages
            // 
            this.logMessages.Dock = System.Windows.Forms.DockStyle.Fill;
            this.logMessages.Location = new System.Drawing.Point(0, 0);
            this.logMessages.Margin = new System.Windows.Forms.Padding(4);
            this.logMessages.Name = "logMessages";
            this.logMessages.Size = new System.Drawing.Size(1095, 35);
            this.logMessages.TabIndex = 3;
            this.logMessages.Text = "";
            // 
            // splitContainer1
            // 
            this.splitContainer1.Dock = System.Windows.Forms.DockStyle.Fill;
            this.splitContainer1.Location = new System.Drawing.Point(0, 29);
            this.splitContainer1.Margin = new System.Windows.Forms.Padding(4);
            this.splitContainer1.Name = "splitContainer1";
            this.splitContainer1.Orientation = System.Windows.Forms.Orientation.Horizontal;
            // 
            // splitContainer1.Panel1
            // 
            this.splitContainer1.Panel1.Controls.Add(this.tabControl1);
            // 
            // splitContainer1.Panel2
            // 
            this.splitContainer1.Panel2.Controls.Add(this.logMessages);
            this.splitContainer1.Size = new System.Drawing.Size(1095, 614);
            this.splitContainer1.SplitterDistance = 574;
            this.splitContainer1.SplitterWidth = 5;
            this.splitContainer1.TabIndex = 4;
            // 
            // menuStrip1
            // 
            this.menuStrip1.Items.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.fileToolStripMenuItem,
            this.buildToolStripMenuItem});
            this.menuStrip1.Location = new System.Drawing.Point(0, 0);
            this.menuStrip1.Name = "menuStrip1";
            this.menuStrip1.Padding = new System.Windows.Forms.Padding(8, 2, 0, 2);
            this.menuStrip1.Size = new System.Drawing.Size(1095, 29);
            this.menuStrip1.TabIndex = 5;
            this.menuStrip1.Text = "menuStrip1";
            // 
            // fileToolStripMenuItem
            // 
            this.fileToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.newGameToolStripMenuItem,
            this.openGameToolStripMenuItem,
            this.saveGameToolStripMenuItem,
            this.closeGameToolStripMenuItem});
            this.fileToolStripMenuItem.Name = "fileToolStripMenuItem";
            this.fileToolStripMenuItem.Size = new System.Drawing.Size(48, 25);
            this.fileToolStripMenuItem.Text = "&File";
            // 
            // newGameToolStripMenuItem
            // 
            this.newGameToolStripMenuItem.Name = "newGameToolStripMenuItem";
            this.newGameToolStripMenuItem.Size = new System.Drawing.Size(185, 26);
            this.newGameToolStripMenuItem.Text = "&New Game";
            this.newGameToolStripMenuItem.Click += new System.EventHandler(this.newGameToolStripMenuItem_Click);
            // 
            // openGameToolStripMenuItem
            // 
            this.openGameToolStripMenuItem.Name = "openGameToolStripMenuItem";
            this.openGameToolStripMenuItem.Size = new System.Drawing.Size(185, 26);
            this.openGameToolStripMenuItem.Text = "&Open Game";
            this.openGameToolStripMenuItem.Click += new System.EventHandler(this.openGameToolStripMenuItem_Click);
            // 
            // saveGameToolStripMenuItem
            // 
            this.saveGameToolStripMenuItem.Enabled = false;
            this.saveGameToolStripMenuItem.Name = "saveGameToolStripMenuItem";
            this.saveGameToolStripMenuItem.Size = new System.Drawing.Size(185, 26);
            this.saveGameToolStripMenuItem.Text = "&Save Game";
            this.saveGameToolStripMenuItem.Click += new System.EventHandler(this.saveGameToolStripMenuItem_Click);
            // 
            // closeGameToolStripMenuItem
            // 
            this.closeGameToolStripMenuItem.Enabled = false;
            this.closeGameToolStripMenuItem.Name = "closeGameToolStripMenuItem";
            this.closeGameToolStripMenuItem.Size = new System.Drawing.Size(185, 26);
            this.closeGameToolStripMenuItem.Text = "&Close Game";
            this.closeGameToolStripMenuItem.Click += new System.EventHandler(this.closeGameToolStripMenuItem_Click);
            // 
            // buildToolStripMenuItem
            // 
            this.buildToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.graphicsBuilderToolStripMenuItem,
            this.levelBuilderToolStripMenuItem});
            this.buildToolStripMenuItem.Enabled = false;
            this.buildToolStripMenuItem.Name = "buildToolStripMenuItem";
            this.buildToolStripMenuItem.Size = new System.Drawing.Size(58, 25);
            this.buildToolStripMenuItem.Text = "&Build";
            // 
            // graphicsBuilderToolStripMenuItem
            // 
            this.graphicsBuilderToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.buildAssetListToolStripMenuItem});
            this.graphicsBuilderToolStripMenuItem.Name = "graphicsBuilderToolStripMenuItem";
            this.graphicsBuilderToolStripMenuItem.Size = new System.Drawing.Size(217, 26);
            this.graphicsBuilderToolStripMenuItem.Text = "&Graphics Builder";
            // 
            // buildAssetListToolStripMenuItem
            // 
            this.buildAssetListToolStripMenuItem.Name = "buildAssetListToolStripMenuItem";
            this.buildAssetListToolStripMenuItem.Size = new System.Drawing.Size(211, 26);
            this.buildAssetListToolStripMenuItem.Text = "Build Asset List";
            // 
            // levelBuilderToolStripMenuItem
            // 
            this.levelBuilderToolStripMenuItem.DropDownItems.AddRange(new System.Windows.Forms.ToolStripItem[] {
            this.allLevelsToolStripMenuItem,
            this.selectedLevelToolStripMenuItem,
            this.convertOldHTFsToIPhoneToolStripMenuItem});
            this.levelBuilderToolStripMenuItem.Name = "levelBuilderToolStripMenuItem";
            this.levelBuilderToolStripMenuItem.Size = new System.Drawing.Size(217, 26);
            this.levelBuilderToolStripMenuItem.Text = "&Level Builder";
            // 
            // allLevelsToolStripMenuItem
            // 
            this.allLevelsToolStripMenuItem.Enabled = false;
            this.allLevelsToolStripMenuItem.Name = "allLevelsToolStripMenuItem";
            this.allLevelsToolStripMenuItem.Size = new System.Drawing.Size(339, 26);
            this.allLevelsToolStripMenuItem.Text = "&All Levels";
            // 
            // selectedLevelToolStripMenuItem
            // 
            this.selectedLevelToolStripMenuItem.Enabled = false;
            this.selectedLevelToolStripMenuItem.Name = "selectedLevelToolStripMenuItem";
            this.selectedLevelToolStripMenuItem.Size = new System.Drawing.Size(339, 26);
            this.selectedLevelToolStripMenuItem.Text = "&Selected Level";
            this.selectedLevelToolStripMenuItem.Click += new System.EventHandler(this.selectedLevelToolStripMenuItem_Click);
            // 
            // convertOldHTFsToIPhoneToolStripMenuItem
            // 
            this.convertOldHTFsToIPhoneToolStripMenuItem.Name = "convertOldHTFsToIPhoneToolStripMenuItem";
            this.convertOldHTFsToIPhoneToolStripMenuItem.Size = new System.Drawing.Size(339, 26);
            this.convertOldHTFsToIPhoneToolStripMenuItem.Text = "&Convert Selected HTFs to iPhone";
            this.convertOldHTFsToIPhoneToolStripMenuItem.Click += new System.EventHandler(this.convertOldHTFsToIPhoneToolStripMenuItem_Click);
            // 
            // newHGPDialog
            // 
            this.newHGPDialog.DefaultExt = "hgp";
            this.newHGPDialog.Filter = "hgp files|*.hgp|All files|*.*";
            this.newHGPDialog.Title = "New HGP";
            // 
            // frmMain
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1095, 643);
            this.Controls.Add(this.splitContainer1);
            this.Controls.Add(this.menuStrip1);
            this.MainMenuStrip = this.menuStrip1;
            this.Margin = new System.Windows.Forms.Padding(4);
            this.Name = "frmMain";
            this.Text = "iPhone Tools";
            this.FormClosing += new System.Windows.Forms.FormClosingEventHandler(this.frmMain_FormClosing);
            this.tabControl1.ResumeLayout(false);
            this.tabQuickTools.ResumeLayout(false);
            this.tabHGF.ResumeLayout(false);
            this.tabHLFHTF.ResumeLayout(false);
            this.splitContainer1.Panel1.ResumeLayout(false);
            this.splitContainer1.Panel2.ResumeLayout(false);
            this.splitContainer1.ResumeLayout(false);
            this.menuStrip1.ResumeLayout(false);
            this.menuStrip1.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.OpenFileDialog openHGPDialog;
        private System.Windows.Forms.TabControl tabControl1;
        private System.Windows.Forms.TabPage tabQuickTools;
        private System.Windows.Forms.RichTextBox logMessages;
        private System.Windows.Forms.SplitContainer splitContainer1;
        private System.Windows.Forms.MenuStrip menuStrip1;
        private System.Windows.Forms.ToolStripMenuItem fileToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem openGameToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem saveGameToolStripMenuItem;
        private System.Windows.Forms.TabPage tabHGF;
        private System.Windows.Forms.ToolStripMenuItem newGameToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem closeGameToolStripMenuItem;
        private System.Windows.Forms.SaveFileDialog newHGPDialog;
        private HGFPanel hgfPanel1;
        private QuickToolsPanel quickToolsPanel1;
        private System.Windows.Forms.TabPage tabHLFHTF;
        private LevelPanel levelPanel1;
        private System.Windows.Forms.ToolStripMenuItem buildToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem graphicsBuilderToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem levelBuilderToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem allLevelsToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem selectedLevelToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem convertOldHTFsToIPhoneToolStripMenuItem;
        private System.Windows.Forms.ToolStripMenuItem buildAssetListToolStripMenuItem;
    }
}

