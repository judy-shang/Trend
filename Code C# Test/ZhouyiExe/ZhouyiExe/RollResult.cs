using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using Newtonsoft.Json;
using System.IO;
using System.Configuration;

namespace ZhouyiExe
{
    class RollResult
    {
        private String RollExplain;
        private int RollCount;
        private String RollName;
        private String RollNameDesc;
        private String GuaCi;
        private String YaoCi;
        private Dictionary<string, string> Infos;
        private Dictionary<String, Dictionary<String, String> > DetailedExplain;
        private static String[] JsonKeys = { "卦辞", "爻辞", "详细解释" };
        private static String[] JsonDescTypes = { "管理" };
        private static String[] JsonDescKeys = { "初爻", "二爻", "三爻", "四爻", "五爻", "六爻", "用九", "用六" };
        
        static string ResourcePath = ConfigurationManager.AppSettings["ResourcePath"];
        static public string PathDefined = ResourcePath != "" ? ResourcePath : @"D:\Zhouyi\Resources\";
        public bool JsonInited = false;
        /**
         * 读取json文件，返回json串
         * 
         * @param fileName
         * @return
         */
        public static String readJsonFile(String fileName)
        {
            String jsonStr = "";
            try
            {
                StreamReader sr = new StreamReader(fileName);
                jsonStr = sr.ReadToEnd().ToString();
                sr.Close();

                return jsonStr;
            }
            catch (IOException e)
            {
                Console.WriteLine(e.StackTrace);
                return "";
            }
        }

        public void getFullDesc()
        {
            Infos = new Dictionary<string, string>();
            DetailedExplain = new Dictionary<string, Dictionary<string, string>>();
            // String file_path = path.
             string filePath = PathDefined + @"JsonFiles\" + RollName + ".json";
            if (!System.IO.File.Exists(filePath))
            {
                //不存在文件
                Console.WriteLine(filePath + "不存在");
                return;
            }
            String s = readJsonFile(filePath);
            dynamic jsonObj = JsonConvert.DeserializeObject(s);
            foreach(var  val in JsonKeys)
            {
                if (jsonObj.Property(val) != null)
                {
                    Infos[val] = jsonObj[val];
                }
                else
                {
                    Console.WriteLine("Leak of info: ", val);
                    return;
                }
            }
            //
            GuaCi = Infos["卦辞"];
            YaoCi = Infos["爻辞"];
            RollExplain = Infos["详细解释"];

            foreach (var val in JsonDescTypes)
            {
                if (jsonObj.Property(val) == null)
                {
                    Console.WriteLine("Leak of info: ", val);
                    return;
                }
                else
                {
                    DetailedExplain[val] = new Dictionary<string, string>();
                    foreach (var details in JsonDescKeys)
                    {
                        if (jsonObj[val].Property(details) == null)
                        {
                            Console.WriteLine("no such detail info: ", val, RollName);
                            continue;
                        }
                        else
                        {
                            DetailedExplain[val][details] = jsonObj[val][details];
                        }
                    }
                }
            }
            JsonInited = true;
        }

        public RollResult(int rollCount, String rollName, String rollNameDesc)
        {
            // todo by baseinfo, load the detailed infos
            RollCount = rollCount;
            RollName = rollName;
            RollNameDesc = rollNameDesc;
            getFullDesc();

        }

        public RollResult()
        {
            RollCount = -1;
            RollName = "";
        }
        public bool isJsonInited()
        {
            return JsonInited;
        }

        public String getRollName()
        {
            return RollName;
        }

        public String getRollNameDesc()
        {
            return RollNameDesc;
        }
       
        public void setRollName(String rollName)
        {
            RollName = rollName;
        }

        public int getRollCount()
        {
            return RollCount;
        }

        public void setRollCount(int rollCount)
        {
            RollCount = rollCount;
        }
        public string getGuaCi()
        {
            return GuaCi;
        }
        public string getYaoCi()
        {
            return YaoCi;
        }
        public string getYaoName(int i)
        {
            return JsonDescKeys[i];
        }
        public string getYaoExplain(int i, string type)
        {
            if (JsonDescTypes.Contains(type))
            {
                return DetailedExplain[type][JsonDescKeys[i]];
            }
            else
            {
                return DetailedExplain[JsonDescTypes[0]][JsonDescKeys[i]];
            }
            
        }
        public String getRollExplain()
        {
            return RollExplain;
        }

        public void setRollExplain(String rollExplain)
        {
            RollExplain = rollExplain;
        }
    }
}
