using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using CR.Utility;
using System.Xml.Linq;
using System.IO;

namespace iPhone_Tools
{
    public class AppSettings : Singleton<AppSettings>
    {
        protected AppSettings()
        {

        }

        public string AssetListFile
        {
            get
            {
                var assetList = from a in document.Elements() 
                                where a.Name == "AssetListFile"
                                    select a.Value;
                return assetList.First();
            }
            set
            {
                var assetList = from a in document.Elements()
                                where a.Name == "AssetListFile"
                                select a;
                assetList.First().Value = value;
            }
        }
        
        public void Load()
        {
            if (File.Exists("Settings.xml"))
                document = XElement.Load("Settings.xml");
            else
            {
                document = new XElement("Settings",
                    new XElement("AssetListFile"));
            }
        }
        
        public void Save()
        {
            if(document != null)
                document.Save("Settings.xml");
            document = null;
        }

        private XElement document;



    }    
}
