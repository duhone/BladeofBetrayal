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
using System.Drawing.Imaging;
using iPhone_Tools.Custom;

using System.Windows;
using System.Diagnostics;

namespace iPhone_Tools
{
    public partial class QuickToolsPanel : UserControl
    {
        #region Fields

        HGPFileManager _hgpFileManager;

        #endregion

        #region Constructor(s)

        public QuickToolsPanel()
        {
            InitializeComponent();
        }

        #endregion

        #region Properties

        public HGPFileManager HGPFileManager
        {
            set
            {
                _hgpFileManager = value;
            }
        }

        #endregion

        private void btnTruncatePath_Click(object sender, EventArgs e)
        {
            foreach (HGFFile hgfFile in _hgpFileManager.HGFFiles)
            {
                // Truncate the front of the path if its the same as the specified
                if (hgfFile.Full_path_name.StartsWith(txtPath.Text))
                {
                    //hgfFile.Full_path_name.Replace(txtPath.Text, "." + Path.DirectorySeparatorChar);
                    hgfFile.Full_path_name = hgfFile.Full_path_name.Remove(0, txtPath.Text.Length);
                    hgfFile.Full_path_name = "." + Path.DirectorySeparatorChar + hgfFile.Full_path_name;
                }

                foreach (HPTImage hptImage in hgfFile.HPTImages)
                {
                    if (hptImage.Full_path_name.StartsWith(txtPath.Text))
                    {
                        //hgfFile.Full_path_name.Replace(txtPath.Text, "." + Path.DirectorySeparatorChar);
                        hptImage.Full_path_name = hptImage.Full_path_name.Remove(0, txtPath.Text.Length);
                        hptImage.Full_path_name = "." + Path.DirectorySeparatorChar + hptImage.Full_path_name;
                    }
                }
            }
        }

        //SolidBrush fillBrush = new SolidBrush(System.Drawing.Color.Magenta);
        private void btnConvertFramesets_Click(object sender, EventArgs e)
        {
            foreach (HGFFile hgfFile in _hgpFileManager.HGFFiles)
            {
                foreach (HPTImage hptImage in hgfFile.HPTImages)
                {
                    int newImageWidth = GetPowerOfTwo(hptImage.Img_width);
                    int newFrameHeight = GetPowerOfTwo(hptImage.Height);
                    int newImageHeight = newFrameHeight * hptImage.Num_frame_sets;

                    int imageWidthDiff = newImageWidth - hptImage.Img_width;
                    int frameHeightDiff = newFrameHeight - hptImage.Height;
                    int imageHeightDiff = newImageHeight - hptImage.Img_height;

                    // Determine if new frameset size is too large to be an iPhone OpenGL ES texture
                    if (newImageWidth > 1024 || newFrameHeight > 1024)
                    {
                        LogManager.OnLogMessage(this, string.Format("Frameset texture size is too large for iPhone, {0} - ({1}, {2}), not converting.", hptImage.Full_path_name, newImageWidth, newFrameHeight));
                        continue;
                    }

                    // If there is no difference in size then the image is fine
                    if (imageWidthDiff == 0 && imageHeightDiff == 0)
                    {
                        // Image does not need to be converted
                        if (!chkOnlyShowErrors.Checked)
                            LogManager.OnLogMessage(this, string.Format("Image OK - {0}", hptImage.Full_path_name));

                        
                        continue;
                    }
                    else
                    {
                        //LogManager.OnLogMessage(this, string.Format("Converting Image - {0}", hptImage.Full_path_name));

                        Image newImage;
                        Image oldImage;
                        try
                        {
                            FileStream fs = new FileStream(hptImage.Full_path_name, FileMode.Open);
                            oldImage = Bitmap.FromStream(fs);//FromFile(hptImage.Full_path_name, false);
                            fs.Close();

                            newImage = new Bitmap(newImageWidth, newImageHeight, oldImage.PixelFormat);
                        }
                        catch (Exception ex)
                        {
                            LogManager.OnLogMessage(this, string.Format("Image not found - {0}", hptImage.Full_path_name));
                            continue;
                        }

                        Graphics ng;
                        Graphics og;
                        try
                        {
                            ng = Graphics.FromImage(newImage); // New Graphics
                            og = Graphics.FromImage(oldImage); // Old Graphics

                            ng.CompositingMode = System.Drawing.Drawing2D.CompositingMode.SourceCopy;
                            og.CompositingMode = System.Drawing.Drawing2D.CompositingMode.SourceCopy;
                        }
                        catch (Exception ex)
                        {
                            LogManager.OnLogMessage(this, string.Format("Graphics object error, image not converted - {0}", hptImage.Full_path_name));
                            continue;
                        }

                        // Fill background with transparent color (Magenta)
                        Region region = new Region(new Rectangle(0, 0, newImage.Width, newImage.Height));
                        SolidBrush solidBrush = new SolidBrush(Color.Magenta);
                        ng.FillRegion(solidBrush, region);

                        // Retrieve old framesets and draw them to the new image
                        int locX = 0;
                        int locY = 0;
                        int newLocY = 0;
                        for (int i = 0; i < hptImage.Num_frame_sets; i++)
                        {
                            for (int j = 0; j < hptImage.Frames_per_set[i]; j++)
                            {
                                Rectangle sourceRect = new Rectangle(locX, locY, hptImage.Width, hptImage.Height);
                                Rectangle destRect = new Rectangle(locX, newLocY + (frameHeightDiff /2), hptImage.Width, hptImage.Height);
                                ng.DrawImage(oldImage, destRect, sourceRect, GraphicsUnit.Pixel);

                                locX += hptImage.Width;
                            }
                            locX = 0;
                            locY += hptImage.Height;
                            newLocY += newFrameHeight;
                        }

                        // TODO: Overwrite original image
                        //newImage.PixelFormat
                        //newImage.Save("D:\\stuffo.png", ImageFormat.Png);

                        //string appPath = Application.ExecutablePath.Remove(Application.ExecutablePath.Length - Path.GetFileName(Application.ExecutablePath).Length, Path.GetFileName(Application.ExecutablePath).Length);
                        //string processArguments = string.Format("\"{0} {1} /k0 /f0 /s3 /y /force", appPath + "tempImage.png\"", "\"" + Path.GetFullPath(hptImage.Full_path_name) + "\"");
                        //newImage.Save(appPath + "tempImage.png", ImageFormat.Png);
                        //Process p = System.Diagnostics.Process.Start(appPath + "pngout.exe", processArguments);
                        //p.WaitForExit();
                        newImage.Save(hptImage.Full_path_name);

                        //oldImage.Save("D:\\stuffo.png", ImageFormat.Png);
                    }

                }
            }
        }

        int GetPowerOfTwo(int n)
        {
            int i = 1;

            while (i < n)
            {
                i *= 2;
            }

            if (i == 1)
                return 2;

            return i;
        }
    }
}
