using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ZhouyiExe
{


    class RollExe
    {
        public const int GuaCount = 3;
        public const int RollTimesMax = 6;
        BasedExe[] BasedExes = new BasedExe[RollTimesMax];// 还需要对每个对象进行new

        // BasedExe[] innerBasedExe = new BasedExe[Count];
        // BasedExe[] outterBasedExes = new BasedExe[Count];
        private int RollTimes;
        private static RollResults resultMap;
        // 卜卦结果记录
        private RollTypes oldOutterResult;
        private RollTypes oldInnerResult;
        private int changeTimes;
        private RollTypes freshOutterResult;
        private RollTypes freshInnerResult;

        private RollResult oldRollResult;
        private RollResult freshRollResult;
        private Dictionary<int, string> changeRules = new Dictionary<int, string>
        {
            {1,  "一爻变：用本卦变爻的爻辞占断吉凶" },
            {2,  "二爻变：用本卦变爻的爻辞占断吉凶，以居上的一爻为主" },
            {3,  "三爻变：用本卦与之卦的卦辞占断吉凶，以本卦为主而以之卦为辅" },
            {4,  "四爻变：用之卦的两个不变爻的爻辞占断吉凶，以居下的一爻为主" },
            {5,  "五爻变：用之卦的一个不变爻的爻辞占断吉凶" },
            {6,  "六爻变：若是乾或坤用用九或用六占断，其他的用之卦的卦辞占断吉凶" },
            {0, "六爻皆不变：用本卦的卦辞占断吉凶"}

        };
        public RollExe()
        {
            for (int i = 0; i < RollTimesMax; ++i)
            {
                BasedExes[i] = new BasedExe();
            }
            RollTimes = 0;

            oldOutterResult = RollTypes.UndefinedRollTypes;
            oldInnerResult = RollTypes.UndefinedRollTypes;
            changeTimes = 0;
            freshOutterResult = RollTypes.UndefinedRollTypes;
            freshInnerResult = RollTypes.UndefinedRollTypes;
            resultMap = new RollResults();

        }


        public void getRollNow()
        {
            if (RollTimes >= RollTimesMax)
            {
                return;
            }
            BasedExes[RollTimes].RollNow();
            BasedExes[RollTimes].getRollResult();
            RollTimes++;
        }
        public ExeTypes getRollGuaBasedInfos(int rollTimes)
        {
            return BasedExes[rollTimes].getBasedStatus();
        }
        public ExeTypes getRollGuaChangedInfos(int rollTimes)
        {
            return BasedExes[rollTimes].getChangedStatus();
        }
        public int getRollGuaBasedValue(int rollTimes)
        {
            return BasedExes[rollTimes].getBasedValue();
        }
        public int getRollGuaChangedValue(int rollTimes)
        {
            return BasedExes[rollTimes].getChangedValue();
        }
        public bool getIsNeedToChange(int rollTimes)
        {
            return BasedExes[rollTimes].getIsNeedToChange();
        }
        public ExeTypes[] getRollDetails(int rollTimes)
        {
            return BasedExes[rollTimes].getExeDetails();
        }
        public int getRollTimes()
        {
            return RollTimes;
        }

        public void resetRollTimes()
        {
            RollTimes = 0;

            oldOutterResult = RollTypes.UndefinedRollTypes;
            oldInnerResult = RollTypes.UndefinedRollTypes;
            changeTimes = 0;
            freshOutterResult = RollTypes.UndefinedRollTypes;
            freshInnerResult = RollTypes.UndefinedRollTypes;
            for (int i = 0; i < RollTimesMax; ++i)
            {
                BasedExes[i].resetValues();
            }
        }

        public RollTypes getGuaResult(ExeTypes first, ExeTypes second, ExeTypes third)
        {
            if (first.Equals(ExeTypes.UnDefinedExeTypes) || second.Equals(ExeTypes.UnDefinedExeTypes)
                    || third.Equals(ExeTypes.UnDefinedExeTypes))
            {
                return RollTypes.UndefinedRollTypes;
            }
            int value = (first.exeValue - ExeTypes.DownExeTypes.exeValue) * 2 * 2
                    + (second.exeValue - ExeTypes.DownExeTypes.exeValue) * 2
                    + (third.exeValue - ExeTypes.DownExeTypes.exeValue);
            return RollTypes.intToRollTypes(value);

        }

        public int RollTypesValueToGuaValue(int innerValue, int outterValue)
        {
            int column = RollTypes.RollTypesMax.rollValue;
            int result = innerValue + (outterValue * column);
            return result;
            // return inner.rollValue + (outer.rollValue * RollTypes.RollTypesMax.value);
        }

        public void getRollResults()
        {
            for (int i = 0; i < RollTimesMax; ++i)
            {
                changeTimes += BasedExes[i].isNeedToChange ? 1 : 0;
            }
            oldInnerResult = getGuaResult(BasedExes[0].basedStatus, BasedExes[1].basedStatus, BasedExes[2].basedStatus);
            oldOutterResult = getGuaResult(BasedExes[GuaCount].basedStatus, BasedExes[GuaCount + 1].basedStatus,
                    BasedExes[GuaCount + 2].basedStatus);
            //TODO
            Console.WriteLine("本卦外卦：" + oldOutterResult.toString() + "; 本卦内卦： " + oldInnerResult.toString());
            freshInnerResult = getGuaResult(BasedExes[0].changedStatus, BasedExes[1].changedStatus,
                    BasedExes[2].changedStatus);
            freshOutterResult = getGuaResult(BasedExes[GuaCount].changedStatus, BasedExes[GuaCount + 1].changedStatus,
                    BasedExes[GuaCount + 2].changedStatus);
            Console.WriteLine("变卦外卦：" + freshOutterResult.toString() + "; 变卦内卦： " + freshInnerResult.toString());
            Console.WriteLine("变爻数： ", changeTimes);

            // int oldValue = RollTypesValueToGuaValue(oldInnerResult, oldOutterResult);

            int oldValue = RollTypesValueToGuaValue(oldInnerResult.rollValue, oldOutterResult.rollValue);
            oldRollResult = resultMap.getRollResult(oldValue);
            // int freshValue = RollTypesValueToGuaValue(freshInnerResult,
            // freshOutterResult);
            int freshValue = RollTypesValueToGuaValue(freshInnerResult.rollValue, freshOutterResult.rollValue);
            freshRollResult = resultMap.getRollResult(freshValue);
            Console.WriteLine("本卦为： " + oldRollResult.getRollName());
            Console.WriteLine("变卦为： " + freshRollResult.getRollName());
        }
        // 根据是否为变爻，返回主爻，辅爻
        // changed = 0----取不变爻； = 1---取变爻
        // from = 0 -----取前为主； ==1---取后为主
        public void getYaoCount(List<int> resultYao, int changed, int from)
        {
            for (int i = 0; i < RollTimesMax; ++i)
            {
                if (changed == 1 && BasedExes[i].isNeedToChange)
                {
                    resultYao.Add(i);
                }
                else if (changed == 0 && !BasedExes[i].isNeedToChange)
                {
                    resultYao.Add(i);
                }
            }
            if (from == 1)
            {
                resultYao.Reverse();
            }
           
        }
        public string getChangedResultExplain(string type)
        {
            string result = "Unexpected Error!";
            int changed = -1;
            int from = -1;

            if (!oldRollResult.isJsonInited())
            {
                oldRollResult.getFullDesc();
            }
            if (!freshRollResult.isJsonInited())
            {
                freshRollResult.getFullDesc();
            }
            freshRollResult.getFullDesc();
            if (!oldRollResult.isJsonInited() || !freshRollResult.isJsonInited())
            {
                result = @"请将json文件放到正确的路径下（D:\Zhouyi\Resources\JsonFiles\）";
                return result;
            }
            List<int> resultYao = new List<int>();
            switch (changeTimes)
            {
                case 0: //用本卦的卦辞占断吉凶
                    result = "本卦卦辞： " + oldRollResult.getGuaCi() + "\n";
                    result += "参考释义：" + oldRollResult.getRollExplain() + "\n";
                    break;
                case 1: //一爻变：用本卦变爻的爻辞占断吉凶
                    changed = 1;
                    from = 0;
                    getYaoCount(resultYao, changed, from);
                    if (resultYao.Count == 1)
                    {
                        result = "本卦卦辞： " + oldRollResult.getGuaCi() + "\n";
                        result += "本卦爻辞： \n" + oldRollResult.getYaoCi() + "\n\n";
                        result += "本卦变爻： " + oldRollResult.getYaoName(resultYao[0]) + "\n";
                        result += "参考释义：" + oldRollResult.getYaoExplain(resultYao[0], type) + "\n";
                    }
                    break;
                case 2: //用本卦变爻的爻辞占断吉凶，以居上的一爻为主
                    changed = 1;
                    from = 1;
                    getYaoCount(resultYao, changed, from);
                    if (resultYao.Count == 2)
                    {
                        result = "本卦卦辞： " + oldRollResult.getGuaCi() + "\n";
                        result += "本卦爻辞： \n" + oldRollResult.getYaoCi() + "\n\n";
                        result += "本卦主变爻： " + oldRollResult.getYaoName(resultYao[0]) + "\n";
                        result += "本卦副变爻： " + oldRollResult.getYaoName(resultYao[1]) + "\n";
                        result += "主参考释义：" + oldRollResult.getYaoExplain(resultYao[0], type) + "\n";
                        result += "副参考释义：" + oldRollResult.getYaoExplain(resultYao[1], type) + "\n";
                    }
                    break;
                case 3: //用本卦与之卦的卦辞占断吉凶，以本卦为主而以之卦为辅
                    result = "本卦卦辞： " + oldRollResult.getGuaCi() + "\n";
                    result += "释义：" + oldRollResult.getRollExplain() + "\n";
                    result += "之卦卦辞： " + freshRollResult.getGuaCi() + "\n";
                    result += "参考释义：" + freshRollResult.getRollExplain() + "\n";
                    break;
                case 4: // 用之卦的两个不变爻的爻辞占断吉凶，以居下的一爻为主
                    changed = 0;
                    from = 0;
                    getYaoCount(resultYao, changed, from);
                    if (resultYao.Count == 2)
                    {
                        result = "之卦卦辞： " + freshRollResult.getGuaCi() + "\n";
                        result += "之卦爻辞： \n" + freshRollResult.getYaoCi() + "\n\n";
                        result += "之卦主变爻： " + freshRollResult.getYaoName(resultYao[0]) + "\n";
                        result += "之卦副变爻： " + freshRollResult.getYaoName(resultYao[1]) + "\n";
                        result += "主参考释义：" + freshRollResult.getYaoExplain(resultYao[0], type) + "\n";
                        result += "副参考释义：" + freshRollResult.getYaoExplain(resultYao[1], type) + "\n";
                    }
                    break;
                case 5: // 用之卦的一个不变爻的爻辞占断吉凶
                    changed = 0;
                    from = 0;
                    getYaoCount(resultYao, changed, from);
                    if (resultYao.Count == 1)
                    {
                        result = "之卦卦辞： " + freshRollResult.getGuaCi() + "\n";
                        result += "之卦爻辞： \n" + freshRollResult.getYaoCi() + "\n\n";
                        result += "之卦变爻： " + freshRollResult.getYaoName(resultYao[0]) + "\n";
                        result += "参考释义：" + freshRollResult.getYaoExplain(resultYao[0], type) + "\n";
                    }
                    break;
                case 6: // 若是乾或坤用用九或用六占断，其他的用之卦的卦辞占断吉凶
                    if (oldRollResult.getRollName() == "乾")
                    {
                        result = "本卦卦辞： " + oldRollResult.getGuaCi() + "\n";
                        result += "本卦爻辞： \n" + oldRollResult.getYaoCi() + "\n\n";
                        result += "本卦变爻： " + oldRollResult.getYaoName(6) + "\n"; //TODO-魔数
                        result += "参考释义：" + oldRollResult.getYaoExplain(6, type) + "\n";
                    }
                    else if (oldRollResult.getRollName() == "坤")
                    {
                        result = "本卦卦辞： " + oldRollResult.getGuaCi() + "\n";
                        result += "本卦爻辞： \n" + oldRollResult.getYaoCi() + "\n\n";
                        result += "本卦变爻： " + oldRollResult.getYaoName(7) + "\n"; //TODO-魔数
                        result += "参考释义：" + oldRollResult.getYaoExplain(7, type) + "\n";
                    }
                    else
                    {
                        result = "之卦卦辞： " + freshRollResult.getGuaCi() + "\n";
                        result += "参考释义：" + freshRollResult.getRollExplain() + "\n";
                    }
                    break;
                default:
                    
                    break;
            }
            return result;
        }
        public string getRollExplains(string type)
        {
            getRollResults();
            string result = "";
            result += "本卦为： 第" + oldRollResult.getRollCount().ToString() + "卦 " + oldRollResult.getRollNameDesc() + "\n";
            result += "变卦为： 第" + freshRollResult.getRollCount().ToString() + "卦 " + freshRollResult.getRollNameDesc() + "\n";
            result += "朱熹断卦： " + changeRules[changeTimes] + "\n\n";
            result += getChangedResultExplain(type);
            return result;
        }
        public bool presentRollResults()
        {
            if (RollTimes != RollTimesMax)
            {
                return false;
            }
            getRollResults();
            return true;
        }
    }
}
