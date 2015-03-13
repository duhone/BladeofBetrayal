namespace iPhone_Tools
{
    partial class QuickToolsPanel
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
            this.groupBox1 = new System.Windows.Forms.GroupBox();
            this.chkOnlyShowErrors = new System.Windows.Forms.CheckBox();
            this.txtPath = new System.Windows.Forms.TextBox();
            this.btnTruncatePath = new System.Windows.Forms.Button();
            this.btnConvertFramesets = new System.Windows.Forms.Button();
            this.groupBox1.SuspendLayout();
            this.SuspendLayout();
            // 
            // groupBox1
            // 
            this.groupBox1.Controls.Add(this.chkOnlyShowErrors);
            this.groupBox1.Controls.Add(this.txtPath);
            this.groupBox1.Controls.Add(this.btnTruncatePath);
            this.groupBox1.Controls.Add(this.btnConvertFramesets);
            this.groupBox1.Location = new System.Drawing.Point(4, 4);
            this.groupBox1.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.groupBox1.Name = "groupBox1";
            this.groupBox1.Padding = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.groupBox1.Size = new System.Drawing.Size(266, 294);
            this.groupBox1.TabIndex = 3;
            this.groupBox1.TabStop = false;
            this.groupBox1.Text = "HGF (Graphics Format) Quick Tools";
            // 
            // chkOnlyShowErrors
            // 
            this.chkOnlyShowErrors.AutoSize = true;
            this.chkOnlyShowErrors.Location = new System.Drawing.Point(9, 180);
            this.chkOnlyShowErrors.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.chkOnlyShowErrors.Name = "chkOnlyShowErrors";
            this.chkOnlyShowErrors.Size = new System.Drawing.Size(183, 21);
            this.chkOnlyShowErrors.TabIndex = 4;
            this.chkOnlyShowErrors.Text = "Only Show Errors In Log";
            this.chkOnlyShowErrors.UseVisualStyleBackColor = true;
            // 
            // txtPath
            // 
            this.txtPath.Location = new System.Drawing.Point(8, 23);
            this.txtPath.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.txtPath.Name = "txtPath";
            this.txtPath.Size = new System.Drawing.Size(241, 22);
            this.txtPath.TabIndex = 3;
            // 
            // btnTruncatePath
            // 
            this.btnTruncatePath.Location = new System.Drawing.Point(8, 55);
            this.btnTruncatePath.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnTruncatePath.Name = "btnTruncatePath";
            this.btnTruncatePath.Size = new System.Drawing.Size(243, 33);
            this.btnTruncatePath.TabIndex = 2;
            this.btnTruncatePath.Text = "Truncate Path";
            this.btnTruncatePath.UseVisualStyleBackColor = true;
            this.btnTruncatePath.Click += new System.EventHandler(this.btnTruncatePath_Click);
            // 
            // btnConvertFramesets
            // 
            this.btnConvertFramesets.Location = new System.Drawing.Point(8, 128);
            this.btnConvertFramesets.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.btnConvertFramesets.Name = "btnConvertFramesets";
            this.btnConvertFramesets.Size = new System.Drawing.Size(243, 43);
            this.btnConvertFramesets.TabIndex = 1;
            this.btnConvertFramesets.Text = "Update Framesets and Images to OpenGL Powers of 2 Sizes";
            this.btnConvertFramesets.UseVisualStyleBackColor = true;
            this.btnConvertFramesets.Click += new System.EventHandler(this.btnConvertFramesets_Click);
            // 
            // QuickToolsPanel
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(8F, 16F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.Controls.Add(this.groupBox1);
            this.Margin = new System.Windows.Forms.Padding(4, 4, 4, 4);
            this.Name = "QuickToolsPanel";
            this.Size = new System.Drawing.Size(1067, 431);
            this.groupBox1.ResumeLayout(false);
            this.groupBox1.PerformLayout();
            this.ResumeLayout(false);

        }

        #endregion

        private System.Windows.Forms.GroupBox groupBox1;
        private System.Windows.Forms.Button btnConvertFramesets;
        private System.Windows.Forms.Button btnTruncatePath;
        private System.Windows.Forms.TextBox txtPath;
        private System.Windows.Forms.CheckBox chkOnlyShowErrors;
    }
}
