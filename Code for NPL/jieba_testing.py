import jieba
from os import path
import jieba.analyse as analyse
'''
https://github.com/fxsjy/jieba
支持三种分词模式：
    精确模式，试图将句子最精确地切开，适合文本分析；
    全模式，把句子中所有的可以成词的词语都扫描出来, 速度非常快，但是不能解决歧义；
    搜索引擎模式，在精确模式的基础上，对长词再次切分，提高召回率，适合用于搜索引擎分词。
支持繁体分词
支持自定义词典
MIT 授权协议

基于前缀词典实现高效的词图扫描，生成句子中汉字所有可能成词情况所构成的有向无环图 (DAG)
采用了动态规划查找最大概率路径, 找出基于词频的最大切分组合
对于未登录词，采用了基于汉字成词能力的 HMM 模型，使用了 Viterbi 算法
'''

'''
jieba.cut 方法接受三个输入参数: 需要分词的字符串；cut_all 参数用来控制是否采用全模式；HMM 参数用来控制是否使用 HMM 模型
jieba.cut_for_search 方法接受两个参数：需要分词的字符串；是否使用 HMM 模型。该方法适合用于搜索引擎构建倒排索引的分词，粒度比较细
待分词的字符串可以是 unicode 或 UTF-8 字符串、GBK 字符串。注意：不建议直接输入 GBK 字符串，可能无法预料地错误解码成 UTF-8
jieba.cut 以及 jieba.cut_for_search 返回的结构都是一个可迭代的 generator，可以使用 for 循环来获得分词后得到的每一个词语(unicode)，或者用
jieba.lcut 以及 jieba.lcut_for_search 直接返回 list
jieba.Tokenizer(dictionary=DEFAULT_DICT) 新建自定义分词器，可用于同时使用不同词典。jieba.dt 为默认分词器，所有全局分词相关函数都是该分词器的映射。
'''
seg_list = jieba.cut("我来到北京清华大学", cut_all=True, HMM=False)
print("Full Mode " + "/".join(seg_list))  # 全模式

seg_list = jieba.cut("我来到北京清华大学", cut_all=False, HMM=True)
print("Default Mode " + "/".join(seg_list))  # 默认模式-精确模式

seg_list = jieba.cut("我来到北京清华大学", cut_all=False, HMM=False)
print("Search Engine Mode " + "/".join(seg_list))  # 搜索引擎模式

seg_list = jieba.cut_for_search("小明硕士毕业于中国科学院计算所，后在日本京都大学深造")  # 搜索引擎模式
print("Search Engine Mode " + ", ".join(seg_list))

seg_list = jieba.cut_for_search(
    "小明硕士毕业于中国科学院计算所，后在日本京都大学深造", HMM=False)  # 搜索引擎模式
print("Search Engine Mode " + ", ".join(seg_list))

seg_list = jieba.cut("小明硕士毕业于中国科学院计算所，后在日本京都大学深造", cut_all=False, HMM=True)
print("Default Mode " + "/".join(seg_list))  # 默认模式-精确模式

'''
关键字提取
'''
dir = path.dirname(__file__)
sample_path = "samples/骆驼祥子.txt"
print("path: " + path.join(dir, sample_path))
with open(path.join(dir, sample_path)) as f:
    text = f.read()
topK = 20
tags = analyse.extract_tags(text, topK)
print("extract result: " + "\n".join(tags))

textrank = analyse.textrank(text)
print("textrank extract: " + "\n".join(tags))
