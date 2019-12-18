package src;

import java.lang.reflect.*;
import java.util.*;
import java.lang.Enum;
import java.security.NoSuchAlgorithmException;
import java.security.SecureRandom;

enum ExeTypes {
    UnDefinedExeTypes(-1, "未知"), DownExeTypes(2, "阴"), UpExeTypes(3, "阳");

    public final int exeValue;
    private final String InfoValue;

    private ExeTypes(int exeValue, String InfoValue) {
        this.exeValue = exeValue;
        this.InfoValue = InfoValue;
    }

    @Override
    public String toString() {
        return InfoValue;
    }
}

class BasedExe {
    public ExeTypes basedStatus;
    public ExeTypes changedStatus;
    public int basedValue;
    public boolean isNeedToChange;
    public int changedValue;
    public static final int Count = 3;
    public static final int BigDownValue = 6;
    public static final int BigUpValue = 9;

    ExeTypes[] results = new ExeTypes[Count];

    public BasedExe() {
        basedValue = 0;
        changedValue = 0;
        isNeedToChange = false;
        for (int i = 0; i < Count; ++i) {
            results[i] = ExeTypes.UnDefinedExeTypes;
        }
        basedStatus = ExeTypes.UnDefinedExeTypes;
        changedStatus = ExeTypes.UnDefinedExeTypes;
    }

    public void getRollData() {
        SecureRandom sr = null;
        try {
            sr = SecureRandom.getInstanceStrong();
            System.out.println("高强度安全随机数");
        } catch (NoSuchAlgorithmException e) {
            sr = new SecureRandom();
            System.out.println("普通的安全随机数");
        }
        for (int i = 0; i < Count; ++i) {
            int tmp = sr.nextInt(100); // 生成[0,100)的随机数
            if (tmp % 2 == 0) {
                results[i] = ExeTypes.DownExeTypes;
            } else {
                results[i] = ExeTypes.UpExeTypes;
            }
            basedValue += results[i].exeValue;
            System.out.println("i: " + results[i].toString());
        }
    }

    public void setBasedInfo() {
        basedStatus = (basedValue % 2 == 0) ? ExeTypes.DownExeTypes : ExeTypes.UpExeTypes;
        changedValue = basedValue;
        if (basedValue == BigDownValue || basedValue == BigUpValue) {
            isNeedToChange = true;
            changedValue = (basedValue == BigUpValue) ? BigDownValue : BigUpValue;
        }
        changedStatus = (changedValue % 2 == 0) ? ExeTypes.DownExeTypes : ExeTypes.UpExeTypes;
        System.out.println("basedStatus: " + basedStatus.toString());
        System.out.println("changedStatus: " + changedStatus.toString());
        System.out.println("isNeedToChange: " + (isNeedToChange?"True":"False"));
    }

    public void RollNow() {
        getRollData();
        setBasedInfo();
    }

    public static void main(String[] args) {
        BasedExe baseTest = new BasedExe();
        baseTest.RollNow();

    }

}