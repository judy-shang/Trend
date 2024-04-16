using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace ZhouyiExe
{
    class RollResults
    {
        private Dictionary<int, RollResult> rollResults = new Dictionary<int, RollResult>();
        private const int MaxCount = 64;

        public RollResults()
        {

            for (int i = 0; i < MaxCount; ++i)
            {
                BasedInfos info = BasedInfos.intToBasedInfos(i);
                rollResults.Add(i, new RollResult(info.value, info.toString(), info.getDescString()));
            }

        }

        public RollResult getRollResult(int value)
        {
            if (value >= 0 && value < MaxCount)
                return rollResults[value];
            else
                return null;

        }


    }
}
