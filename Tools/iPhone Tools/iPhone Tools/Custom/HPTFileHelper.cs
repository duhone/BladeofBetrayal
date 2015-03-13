using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace iPhone_Tools.Custom
{
    public static class HPTFileHelper
    {
        public static string GetString(BinaryReader br)
        {
            int str_len = 0;
            char[] buffer = new char[512];
            string ansi_buffer = string.Empty;

            str_len = br.ReadInt32();
            buffer = new char[str_len];
            br.ReadChars(str_len).CopyTo(buffer, 0);
            ansi_buffer = new string(buffer);

            return ansi_buffer;
        }

        public static void SetPath(string _path)
        {
            mainDirPath = _path;
        }

        public static string AbsoluteToRelativePath(string absoluteFilePath)
        {
            string[] firstPathParts = mainDirPath.Trim(Path.DirectorySeparatorChar).Split(Path.DirectorySeparatorChar);
            string[] secondPathParts = absoluteFilePath.Trim(Path.DirectorySeparatorChar).Split(Path.DirectorySeparatorChar);

            int sameCounter = 0;
            for (int i = 0; i < Math.Min(firstPathParts.Length, secondPathParts.Length); i++)
            {
                if (!firstPathParts[i].ToLower().Equals(secondPathParts[i].ToLower()))
                {
                    break;
                }
                sameCounter++;
            }

            if (sameCounter == 0)
            {
                return absoluteFilePath;
            }

            string newPath = String.Empty;
            for (int i = sameCounter; i < firstPathParts.Length; i++)
            {
                if (i > sameCounter)
                {
                    newPath += Path.DirectorySeparatorChar;
                }
                newPath += "..";
            }
            if (newPath.Length == 0)
            {
                newPath = ".";
            }
            for (int i = sameCounter; i < secondPathParts.Length; i++)
            {
                newPath += Path.DirectorySeparatorChar;
                newPath += secondPathParts[i];
            }
            return newPath;
        }

        public static byte[] convertStringToByteArray(string input)
        {
            System.Text.ASCIIEncoding enc = new System.Text.ASCIIEncoding();
            return enc.GetBytes(input);
        }

        public static string convertByteArrayToString(byte[] bytes)
        {
            return System.Text.ASCIIEncoding.ASCII.GetString(bytes);
        }

        private static string mainDirPath;
    }
}
