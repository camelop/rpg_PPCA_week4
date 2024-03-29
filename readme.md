# 平凡的RPG

## 题目背景

勇者对史莱姆造成了233点伤害，史莱姆再起不能

## 题目描述

史前的RPG机制及其简单，你扮演的勇者有一些基本的属性：生命、力量、防御、速度。你的目的是拯救城堡里的公主，但是拯救公主之前，你先要帮师傅消灭妖怪。

所以下面是一道交互题。

妖怪有一些基本的属性：生命、力量、防御、速度。当你对战一个妖怪的时候，你们会粗暴的按速度决定攻击顺序，即如果你的速度+0.5（勇士之祝福）大于妖怪的速度，你先攻，否则妖怪先攻，接下来轮次进行攻击，当速度快的一方速度大于另一方的k倍时，会进行（且一定会进行）k次这样的攻击（即下取整）。

你攻击妖怪时，妖怪的生命会下降你的攻击力减去妖怪的防御力的数值（最小为0），妖怪攻击你时同理，战斗直到一方的生命小于等于0时结束。**战斗结束后你的生命不会恢复至上限。**

这个RPG游戏就是你不断消灭妖怪，直到战死或营救到公主的过程。当你开始游戏时，妖怪（公主？）会按照4个小怪、1个BOSS的顺序在你面前排成一列纵队，并依次和你战斗。每当你杀死一个BOSS，你都会获得能力的提升，【这时候作为程序员的你突然附身】，你可以在以下选项中选择一项：
- 恢复生命，恢复量为上限的**40%**，不溢出
- 将提高**500**点生命上限（**不会改变当前生命数值**）
- 增加**30**点攻击力
- 增加**10**点防御力
- 增加**10**点速度
- **什么都不做**

然后继续你的旅程、如你所料想的那样，你能打败越多的妖怪，得到的分数就越高。当然救走公主直接按满分记。

## 妖怪描述

和你一样，排的越靠后的妖怪越厉害。妖怪的水平参差不齐，但可以大致分为几类，具体的类型参照环境程序。

## 程序编写

请完成hpp文件中的upgrade函数并上传
参数

- step 当前妖怪编号（1-based）
- hp 当前人物血量
- hl 当前血量上限
- atk 当前人物攻击
- dfe 当前人物防御
- spd 当前人物速度

返回值：一个0-5的整数，分别依次代表题目描述中的六种行为

注意：函数内严禁进行输出或其他奇怪的未定义行为，由此导致的分数降低后果自负。

## 附加材料

为了大家能够更加轻松的解决本次的非传统题，助教为大家准备了一些参考资料：

- 退火算法
- 遗传算法
- 强化学习

注意：

参考资料的意义是，如果实在没有思路可以进行参考，**而非保证**你在实现某方法后分数能达到特定值，但**正确实现**的某种方法一定会对你的模型有积极的作用。