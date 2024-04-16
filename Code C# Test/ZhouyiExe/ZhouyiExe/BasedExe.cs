using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ZhouyiExe
{
    public class BasedInfos
    {
        public static readonly BasedInfos KUN = new BasedInfos(0, 2, "坤", "坤为地");
        public static readonly BasedInfos QIAN = new BasedInfos(1, 15, "谦", "地山谦");
        public static readonly BasedInfos SHI = new BasedInfos(2, 7, "师", "地水师");
        public static readonly BasedInfos SHEN = new BasedInfos(3, 46, "升", "地风升");
        public static readonly BasedInfos FU = new BasedInfos(4, 24, "复", "地雷复");
        public static readonly BasedInfos MINGYI = new BasedInfos(5, 36, "明夷", "地火明夷");
        public static readonly BasedInfos LIN = new BasedInfos(6, 19, "临", "地泽临");
        public static readonly BasedInfos TAI = new BasedInfos(7, 11, "泰", "地天泰");
        public static readonly BasedInfos BO = new BasedInfos(8, 23, "剥", "山地剥");
        public static readonly BasedInfos GEN = new BasedInfos(9, 52, "艮", "艮为山");
        public static readonly BasedInfos MENG = new BasedInfos(10, 4, "蒙", "山水蒙");
        public static readonly BasedInfos GU = new BasedInfos(11, 18, "蛊", "山风蛊");
        public static readonly BasedInfos YI = new BasedInfos(12, 27, "颐", "山雷颐");
        public static readonly BasedInfos BEN = new BasedInfos(13, 22, "贲", "山火贲");
        public static readonly BasedInfos SUN = new BasedInfos(14, 41, "损", "山泽损");
        public static readonly BasedInfos DACHU = new BasedInfos(15, 26, "大畜", "山天大畜");
        public static readonly BasedInfos BI = new BasedInfos(16, 8, "比", "水地比");
        public static readonly BasedInfos JIAN = new BasedInfos(17, 39, "蹇", "水山蹇");
        public static readonly BasedInfos KAN = new BasedInfos(18, 29, "坎", "坎为水");
        public static readonly BasedInfos JING = new BasedInfos(19, 48, "井", "水风井");
        public static readonly BasedInfos TUN = new BasedInfos(20, 3, "屯", "水雷屯");
        public static readonly BasedInfos JIJI = new BasedInfos(21, 63, "既济", "水火既济");
        public static readonly BasedInfos JIE = new BasedInfos(22, 60, "节", "水泽节");
        public static readonly BasedInfos XU = new BasedInfos(23, 5, "需", "水天需");
        public static readonly BasedInfos GUAN = new BasedInfos(24, 20, "观", "风地观");
        public static readonly BasedInfos JIANGUA = new BasedInfos(25, 53, "渐", "风山渐");
        public static readonly BasedInfos HUAN = new BasedInfos(26, 59, "涣", "风水涣");
        public static readonly BasedInfos XUN = new BasedInfos(27, 57, "巽", "巽为风");
        public static readonly BasedInfos YIGUA = new BasedInfos(28, 42, "益", "风雷益");
        public static readonly BasedInfos JIAREN = new BasedInfos(29, 37, "家人", "风火家人");
        public static readonly BasedInfos ZHONGFU = new BasedInfos(30, 61, "中孚", "风泽中孚");
        public static readonly BasedInfos XIAOCHU = new BasedInfos(31, 9, "小畜", "风天小畜");
        public static readonly BasedInfos YU = new BasedInfos(32, 16, "豫", "雷地豫");
        public static readonly BasedInfos XIAOGUO = new BasedInfos(33, 62, "小过", "雷山小过");
        public static readonly BasedInfos JIEGUA = new BasedInfos(34, 40, "解", "雷水解");
        public static readonly BasedInfos HENG = new BasedInfos(35, 32, "恒", "雷风恒");
        public static readonly BasedInfos ZHENG = new BasedInfos(36, 51, "震", "震为雷");
        public static readonly BasedInfos FENG = new BasedInfos(37, 55, "丰", "雷火丰");
        public static readonly BasedInfos GUIZI = new BasedInfos(38, 54, "归妹", "雷泽归妹");
        public static readonly BasedInfos DAZHUANG = new BasedInfos(39, 34, "大壮", "雷天大壮");
        public static readonly BasedInfos JIN = new BasedInfos(40, 35, "晋", "火地晋");
        public static readonly BasedInfos LVGUA = new BasedInfos(41, 56, "旅", "火山旅");
        public static readonly BasedInfos WEIJI = new BasedInfos(42, 64, "未济", "火水未济");
        public static readonly BasedInfos DING = new BasedInfos(43, 50, "鼎", "火风鼎");
        public static readonly BasedInfos SHIKE = new BasedInfos(44, 21, "噬嗑", "火雷噬嗑");
        public static readonly BasedInfos LI = new BasedInfos(45, 30, "离", "离为火");
        public static readonly BasedInfos KUI = new BasedInfos(46, 38, "睽", "火泽睽");
        public static readonly BasedInfos DAYOU = new BasedInfos(47, 14, "大有", "火天大有");
        public static readonly BasedInfos CUI = new BasedInfos(48, 45, "萃", "泽地萃");
        public static readonly BasedInfos XIAN = new BasedInfos(49, 31, "咸", "泽山咸");
        public static readonly BasedInfos KUNGUA = new BasedInfos(50, 47, "困", "泽水困");
        public static readonly BasedInfos DAGUO = new BasedInfos(51, 28, "大过", "泽风大过");
        public static readonly BasedInfos SUI = new BasedInfos(52, 17, "随", "泽雷随");
        public static readonly BasedInfos GE = new BasedInfos(53, 49, "革", "泽火革");
        public static readonly BasedInfos DUI = new BasedInfos(54, 58, "兑", "兑为泽");
        public static readonly BasedInfos GUAI = new BasedInfos(55, 43, "夬", "泽天夬");
        public static readonly BasedInfos PI = new BasedInfos(56, 12, "否", "天地否");
        public static readonly BasedInfos DUN = new BasedInfos(57, 33, "遯", "天山遯");
        public static readonly BasedInfos SU = new BasedInfos(58, 6, "讼", "天水讼");
        public static readonly BasedInfos GOU = new BasedInfos(59, 44, "姤", "天风姤");
        public static readonly BasedInfos WUWANG = new BasedInfos(60, 25, "无妄", "天雷无妄");
        public static readonly BasedInfos TONGREN = new BasedInfos(61, 13, "同人", "天火同人");
        public static readonly BasedInfos LV = new BasedInfos(62, 10, "履", "天泽履");
        public static readonly BasedInfos QIANGUA = new BasedInfos(63, 1, "乾", "乾为天");
        public readonly int key;
        public readonly int value;
        private readonly String InfoValue;
        private readonly String InfoDesc;

        private BasedInfos(int key, int value, String InfoValue, String InfoDesc)
        {
            this.key = key;
            this.value = value;
            this.InfoValue = InfoValue;
            this.InfoDesc = InfoDesc;
        }


        public String toString()
        {
            return InfoValue;
        }

        public String getDescString()
        {
            return InfoDesc;
        }
        private static Dictionary<int, BasedInfos> EnumMap = new Dictionary<int, BasedInfos>();
        private static bool initialMap = false;

        public static void buildMap()
        {

            EnumMap.Add(KUN.key, KUN);
            EnumMap.Add(QIAN.key, QIAN);
            EnumMap.Add(SHI.key, SHI);
            EnumMap.Add(SHEN.key, SHEN);
            EnumMap.Add(FU.key, FU);
            EnumMap.Add(MINGYI.key, MINGYI);
            EnumMap.Add(LIN.key, LIN);
            EnumMap.Add(TAI.key, TAI);
            EnumMap.Add(BO.key, BO);
            EnumMap.Add(GEN.key, GEN);
            EnumMap.Add(MENG.key, MENG);
            EnumMap.Add(GU.key, GU);
            EnumMap.Add(YI.key, YI);
            EnumMap.Add(BEN.key, BEN);
            EnumMap.Add(SUN.key, SUN);
            EnumMap.Add(DACHU.key, DACHU);
            EnumMap.Add(BI.key, BI);
            EnumMap.Add(JIAN.key, JIAN);
            EnumMap.Add(KAN.key, KAN);
            EnumMap.Add(JING.key, JING);
            EnumMap.Add(TUN.key, TUN);
            EnumMap.Add(JIJI.key, JIJI);
            EnumMap.Add(JIE.key, JIE);
            EnumMap.Add(XU.key, XU);
            EnumMap.Add(GUAN.key, GUAN);
            EnumMap.Add(JIANGUA.key, JIANGUA);
            EnumMap.Add(HUAN.key, HUAN);
            EnumMap.Add(XUN.key, XUN);
            EnumMap.Add(YIGUA.key, YIGUA);
            EnumMap.Add(JIAREN.key, JIAREN);
            EnumMap.Add(ZHONGFU.key, ZHONGFU);
            EnumMap.Add(XIAOCHU.key, XIAOCHU);
            EnumMap.Add(YU.key, YU);
            EnumMap.Add(XIAOGUO.key, XIAOGUO);
            EnumMap.Add(JIEGUA.key, JIEGUA);
            EnumMap.Add(HENG.key, HENG);
            EnumMap.Add(ZHENG.key, ZHENG);
            EnumMap.Add(FENG.key, FENG);
            EnumMap.Add(GUIZI.key, GUIZI);
            EnumMap.Add(DAZHUANG.key, DAZHUANG);
            EnumMap.Add(JIN.key, JIN);
            EnumMap.Add(LVGUA.key, LVGUA);
            EnumMap.Add(WEIJI.key, WEIJI);
            EnumMap.Add(DING.key, DING);
            EnumMap.Add(SHIKE.key, SHIKE);
            EnumMap.Add(LI.key, LI);
            EnumMap.Add(KUI.key, KUI);
            EnumMap.Add(DAYOU.key, DAYOU);
            EnumMap.Add(CUI.key, CUI);
            EnumMap.Add(XIAN.key, XIAN);
            EnumMap.Add(KUNGUA.key, KUNGUA);
            EnumMap.Add(DAGUO.key, DAGUO);
            EnumMap.Add(SUI.key, SUI);
            EnumMap.Add(GE.key, GE);
            EnumMap.Add(DUI.key, DUI);
            EnumMap.Add(GUAI.key, GUAI);
            EnumMap.Add(PI.key, PI);
            EnumMap.Add(DUN.key, DUN);
            EnumMap.Add(SU.key, SU);
            EnumMap.Add(GOU.key, GOU);
            EnumMap.Add(WUWANG.key, WUWANG);
            EnumMap.Add(TONGREN.key, TONGREN);
            EnumMap.Add(LV.key, LV);
            EnumMap.Add(QIANGUA.key, QIANGUA);
            initialMap = true;
        }

        public static BasedInfos intToBasedInfos(int key)
        {
            if (!initialMap)
            {
                buildMap();
            }
            return EnumMap[key];
        }

    }


    public class RollTypes
    {

        public static readonly RollTypes UndefinedRollTypes = new RollTypes(-1, "未知");
        public static readonly RollTypes QUN = new RollTypes(0, "坤");
        public static readonly RollTypes GEN = new RollTypes(1, "艮");
        public static readonly RollTypes KAN = new RollTypes(2, "坎");
        public static readonly RollTypes XUN = new RollTypes(3, "巽");
        public static readonly RollTypes ZHEN = new RollTypes(4, "震");
        public static readonly RollTypes LI = new RollTypes(5, "离");
        public static readonly RollTypes DUI = new RollTypes(6, "兑");
        public static readonly RollTypes QIAN = new RollTypes(7, "乾");
        public static readonly RollTypes RollTypesMax = new RollTypes(8, "MAX");

        public readonly int rollValue;
        private readonly String InfoValue;

        private RollTypes(int rollValue, String InfoValue)
        {
            this.rollValue = rollValue;
            this.InfoValue = InfoValue;
        }


        public String toString()
        {
            return InfoValue;
        }

        private static Dictionary<int, RollTypes> EnumMap = new Dictionary<int, RollTypes>();
        private static bool initialMap = false;

        public static void buildMap()
        {
            EnumMap.Add(UndefinedRollTypes.rollValue, UndefinedRollTypes);
            EnumMap.Add(QUN.rollValue, QUN);
            EnumMap.Add(GEN.rollValue, GEN);
            EnumMap.Add(KAN.rollValue, KAN);
            EnumMap.Add(XUN.rollValue, XUN);
            EnumMap.Add(ZHEN.rollValue, ZHEN);
            EnumMap.Add(LI.rollValue, LI);
            EnumMap.Add(DUI.rollValue, DUI);
            EnumMap.Add(QIAN.rollValue, QIAN);
            EnumMap.Add(RollTypesMax.rollValue, RollTypesMax);
            initialMap = true;
        }

        public static RollTypes intToRollTypes(int key)
        {
            if (!initialMap)
            {
                buildMap();
            }
            return EnumMap[key];
        }

    }

    public class ExeTypes
    {
        public static readonly ExeTypes UnDefinedExeTypes = new ExeTypes(-1, "未知");
        public static readonly ExeTypes DownExeTypes = new ExeTypes(2, "阴");
        public static readonly ExeTypes UpExeTypes = new ExeTypes(3, "阳");

        public readonly int exeValue;
        private readonly String InfoValue;

        private ExeTypes(int exeValue, String InfoValue)
        {
            this.exeValue = exeValue;
            this.InfoValue = InfoValue;
        }


        public String toString()
        {
            return InfoValue;
        }
    }

    class BasedExe
    {
        public ExeTypes basedStatus;
        public ExeTypes changedStatus;
        public int basedValue;
        public bool isNeedToChange;
        public int changedValue;
        public static int Count = 3;
        public static int BigDownValue = 6;
        public static int BigUpValue = 9;

        ExeTypes[] results = new ExeTypes[Count];

        public BasedExe()
        {
            basedValue = 0;
            changedValue = 0;
            isNeedToChange = false;
            for (int i = 0; i < Count; ++i)
            {
                results[i] = ExeTypes.UnDefinedExeTypes;
            }
            basedStatus = ExeTypes.UnDefinedExeTypes;
            changedStatus = ExeTypes.UnDefinedExeTypes;
        }

        public void getRollData()
        {
            long tick = DateTime.Now.Ticks;
            Random sr = new Random((int)(tick & 0xffffffffL) | (int)(tick >> 32));

            for (int i = 0; i < Count; ++i)
            {
                int tmp = sr.Next(100); // 生成[0,100)的随机数
                if (tmp % 2 == 0)
                {
                    results[i] = ExeTypes.DownExeTypes;
                }
                else
                {
                    results[i] = ExeTypes.UpExeTypes;
                }
                basedValue += results[i].exeValue;
                Console.WriteLine("i: " + results[i].toString());
            }
        }

        public void setBasedInfo()
        {
            basedStatus = (basedValue % 2 == 0) ? ExeTypes.DownExeTypes : ExeTypes.UpExeTypes;
            changedValue = basedValue;
            if (basedValue == BigDownValue || basedValue == BigUpValue)
            {
                isNeedToChange = true;
                changedValue = (basedValue == BigUpValue) ? BigDownValue : BigUpValue;
            }
            changedStatus = (changedValue % 2 == 0) ? ExeTypes.DownExeTypes : ExeTypes.UpExeTypes;
            // Console.WriteLine("basedStatus: " + basedStatus.toString());
            // Console.WriteLine("changedStatus: " + changedStatus.toString());
            // Console.WriteLine("isNeedToChange: " + (isNeedToChange?"True":"False"));
        }

        public void RollNow()
        {
            getRollData();
            setBasedInfo();
        }

        public void getRollResult()
        {
            Console.WriteLine("basedStatus: " + basedStatus.toString());
            Console.WriteLine("changedStatus: " + changedStatus.toString());
            Console.WriteLine("isNeedToChange: " + (isNeedToChange ? "True" : "False"));
        }
        public ExeTypes[] getExeDetails()
        {
            return results;
        }
        public int getBasedValue()
        {
            return basedValue;
        }
        public int getChangedValue()
        {
            return changedValue;
        }
        public bool getIsNeedToChange()
        {
            return isNeedToChange;
        }
        public ExeTypes getBasedStatus()
        {
            return basedStatus;
        }
        public ExeTypes getChangedStatus()
        {
            return changedStatus;
        }
        public void resetValues()
        {
            basedValue = 0;
            changedValue = 0;
            isNeedToChange = false;
            for (int i = 0; i < Count; ++i)
            {
                results[i] = ExeTypes.UnDefinedExeTypes;
            }
            basedStatus = ExeTypes.UnDefinedExeTypes;
            changedStatus = ExeTypes.UnDefinedExeTypes;
        }
    }
}
