# AVL树的操作

## 删除

因为删除最后都会转化成删除只有至多一个子女的结点，所以这里只讨论这种情况。

### case1

$p_r$是要删除结点$p$的父结点，若$p_r$的平衡因子是$0$，则删除$p$后$p_r$的平衡因子变为$-1$或者$1$，且以$p_r$为根的平衡树高度不变，所以整个AVL达到平衡，具体过程如下图。
![case1](E:\repositories\datastruct\some-implement-in-datastruct\tree\imag\case1.png)

