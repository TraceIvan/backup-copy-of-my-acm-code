﻿//基本术语
//①结点:每个元素对应一个结点，包含元素值及其逻辑关系信息
//②结点的度:结点拥有的子树数目
//③树的度:树中所有结点的度的最大值
//④叶子结点:度为0的点，简称叶结点又称终端结点或外部结点
//⑤分支结点:度大于0的点，又称非终端结点，或内部结点
//⑥孩子结点和双亲结点:如结点有子树，则所有子树的根结点为该结点的孩子结点，简称孩子。反过来，称此结点为孩子结点的双亲结点，简称双亲。叶结点没有孩子，整棵树的根没有双亲
//⑦结点的层次:根结点的层次为1，其孩子结点的层次为2。任一结点的层次为其双亲结点的层次加1
//⑧树的高度:叶子结点所在的最大层次
//⑨兄弟结点:同一双亲的孩子结点互称，简称兄弟
//⑩①堂兄弟结点:在同一层，但双亲不同的结点
//⑩②祖先结点:从根结点到此结点所经分支上的所有结点
//⑩③子孙结点:某一结点的孩子，以及这些孩子的孩子…直到叶结点，都是此结点的子孙结点
//⑩④路径:从树的一个结点到另一个结点的分支
//⑩⑤有序树:树中结点的各子树从左至右有次序，即子树之间存在确定的次序关系
//⑩⑥无序树:子树之间不存在确定的次序关系，可以互相交换位置
//⑩⑦森林:m(m≥0)棵互不相交的树的集合构成森林。对树中的每个结点而言，其子树的集合即为森林，通常称为子树森林
//二叉树性质
//①在二叉树的第i层上最多有2^(i-1)个结点
//②高度为k的二叉树上至多有2^k-1个结点
//③对任何一棵二叉树，若它含有n0个叶子结点，n2个度为2的结点，则必存在关系式:n0=n2+1
//证明:
//设二叉树上结点总数为n,用ni表示二叉树中度为i的结点个数，则:n=n0+n1+n2;因为除了根结点以外的每个结点都有且仅有一个双亲结点，所以边(分支)数目b=n-1;因为度为0的结点发出0条边，度为1的结点发出1条边，度为2的结点发出两条边，所以b=n1+2n2;所以n-1=n1+2n2,得n0=n2+1
//满二叉树:只含度为0和2的结点，且度为0的结点只出现在最后一层的二叉树。空二叉树和只含一个根结点的二叉树也是满二叉树
//完全二叉树:对任意一棵满二叉树，从它的最后一层的最右结点起，按从下到上，从右到左的次序，去掉若干个结点后，所得到的二叉树
//非完全二叉树:剩下的…
//④具有n个结点的完全二叉树的高度为⌊log2n⌋+1.根据性质②和完全二叉树定义可知:2^(k-1)≤n＜2^k,k-1≤log2n＜k,由于k为整数，所以k=⌊log2n⌋+1.
//⌊x⌋表示不大于x的最大整数，称下取整
//⌈x⌉表示不小于x的最小整数，称上取整
//⑤若对含n个结点的完全二叉树，按照从上到下，从左到右的次序进行1至n的编号，对结点i:⑴若i=1,则为根结点，无双亲结点，若i＞1，则结点⌊i/2⌋为双亲结点;⑵若2i＞n,则结点i无左孩子，否则，结点2i为左孩子;⑶若2i+1＞n,则结点i无右孩子，否则结点2i+1为右孩子
//在完全二叉树中，结点i的左孩子为2i,右孩子为2i+1

