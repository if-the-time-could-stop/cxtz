#include "cxtz.h"

void Cxtz::encrypt(Int ss, void* src, Int sd, void* det, Int key)
{
}

void Cxtz::decrypt(Int ss, void* src, Int sd, void* det, Int key)
{
	/*嗬！这是CXTZ加密系统的·总加密函数·
	具体加密步骤如下：
	首先，将数据上叠加一随机波进行干扰；
	接着，对数据进行比特级重排。
	说明：
	本算法是一种·对称·加密算法，由于不含有检验密码正确与否的步骤，故若在数据本身经过特殊处理抹去特征的情形下无法使用简单穷举破解。
	本函数及算法仅为示例，后来者完全可以重写之。最重要的是上行所述之思想。
	*/
	
	/*嗬！2023年4月30日更新！
	*由于作者本人实在没有时间完成相关算法……猜猜我想到了什么？我用ChatGPT生成了相关代码，以下为原对话：

2023/4/30 18:43:49
我需要一段C++程序，用于将一段已给定长度和首地址的数据，据已给定的、以链表形式储存的随机数种子，逐比特无进位地加上一个0到1之间的随机值，然后将所得数据按先前所述的随机数种子进行随机重排，并将最终所得数据储存在堆中，以首地址形式输出。

2023/4/30 18:44:45

以下是一份可能实现您要求的C++程序：

c++
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <ctime>

using namespace std;

// 随机数种子链表节点
struct SeedNode {
    unsigned int seed;
    SeedNode *next;
};

// 初始化随机数生成器
void initRand(unsigned int seed) {
    srand(seed);
}

// 生成0到1之间的随机值
double getRandVal() {
    return (double)rand() / RAND_MAX;
}

// 按比特位加上随机值
void addRandVal(char *data, int len) {
    for (int i = 0; i < len; i++) {
        data[i] += (char)(getRandVal() * 256);
    }
}

// 随机重排
void shuffle(char *data, int len, SeedNode *seedNode) {
    unsigned int seed = seedNode->seed;
    unsigned int tmp;
    for (int i = 0; i < len; i++) {
        // 生成交换下标
        seed = (1103515245 * seed + 12345) % (i + 1);
        tmp = data[i];
        data[i] = data[seed];
        data[seed] = tmp;
    }
    // 更新种子链表
    seedNode->seed = seed;
    if (seedNode->next != nullptr) {
        shuffle(data, len, seedNode->next);
    }
}

// 堆内存分配
char *heapAlloc(int len) {
    char *data = new char[len];
    memset(data, 0, len);
    return data;
}

// 输出数据到控制台
void printData(char *data, int len) {
    for (int i = 0; i < len; i++) {
        printf("%d ", (unsigned char)data[i]);
    }
}

// 主函数
int main() {
    // 已给定长度和首地址的数据
    const int DATA_LEN = 10;
    char *data = new char[DATA_LEN];
    memset(data, 0, DATA_LEN);

    // 已给定的、以链表形式储存的随机数种子
    SeedNode *seedNode1 = new SeedNode{1234, nullptr};
    SeedNode *seedNode2 = new SeedNode{5678, seedNode1};

    // 按比特位加上随机值
    initRand(seedNode1->seed);
    addRandVal(data, DATA_LEN);

    // 随机重排
    initRand(seedNode2->seed);
    shuffle(data, DATA_LEN, seedNode2);

    // 输出结果
    char *result = heapAlloc(DATA_LEN);
    memcpy(result, data, DATA_LEN);
    printData(result, DATA_LEN);

    // 释放堆内存
    delete[] data;
    delete[] result;
    delete seedNode1;
    delete seedNode2;

    return 0;
}
这份程序使用了C++中的结构体（SeedNode）来储存随机数种子，用一个指针字段实现链表。initRand()函数可以在程序中任意位置调用，用于初始化rand()函数的生成种子，以实现不同的随机数序列。addRandVal()函数按比特位无进位地将数据加上随机值，使用getRandVal()函数来生成0到1之间的随机值。shuffle()函数实现了洗牌算法，其中交换用到了一个额外的变量tmp。最后，程序中实现了堆内存分配和释放、数据复制和控制台输出的函数。

您可以根据您的实际需求对这份程序进行修改和优化，比如增加适当的输入输出和错误处理，或者改变随机数生成器和随机重排算法等。
*/
}

Int Cxtz::random(Int rmax, Int seed)
{
	/*这是本算法中调用最多的函数。我们所需的是一个因变量分布均匀的、可复现的随机数生成系统。
	此处将使用平方取中法实现。
	*/

}

Int::Int()
	:value(Chain<int>())
{
	
}

Int::Int(Chain<int> *v)
	:value(Chain<int>())
{
	v->setptr(0);
	value.setptr(0);
	value.set(v->get());
	for (unsigned long long int i = 1; i < v->getsum(); i++) {
		value.attend(v->get());
		v->setptr(i);
		value.setptr(static_cast<unsigned long long>(value.getptr()) + 1);
	}
}

Int::~Int()
{
}

void Int::set(Chain<int>* v)
{
	v->setptr(0);
	value.setptr(0);
	value.set(v->get());
	for (unsigned long long int i = 1; i < v->getsum(); i++) {
		v->setptr(i);
		value.attend(v->get());
		value.setptr(static_cast<unsigned long long>(value.getptr()) + 1);
	}
}

Chain<int>* Int::get()
{
	return &value;
}

Int* Int::plus(Int* a)
{
	unsigned long long int length = (this->value.getsum() >= (a->get())->getsum()) ? (this->value.getsum()) : (a->get()->getsum());
	Chain<int>* result = &Chain<int>();
	bool flag = false;
	result->set(this->value.get() + a->get()->get());
	if (result->get() < this->value.get())
		flag = true;
	a->get()->setptr(1);
	for (unsigned long long int i = 0; i < length; i++) {
		result->attend(this->value.get() + a->get()->get() + (int)flag);
		result->setptr(static_cast<unsigned long long>(result->getptr()) + 1);
		this->value.setptr(static_cast<unsigned long long>(this->value.getptr()) + 1);
		a->get()->setptr(static_cast<unsigned long long>(a->get()->getptr()) + 1);
		flag = false;
		if (result->get() < this->value.get())
			flag = true;
	}
	Int *it = &Int();
	it->set(result);
	return it;
}

Int* Int::minus(Int* a)
{
	Chain<int> *b0 = &Chain<int>();
	a->get()->setptr(0);
	if (a->get()->getsum() == 1) {
		b0->set(-a->get()->get());
	}
	else {
		b0->set(~(a->get()->get()));
		for (unsigned long long int i = 1; i < a->get()->getsum() - 1; i++) {
			a->get()->setptr(i);
			b0->attend(~a->get()->get());
			b0->setptr(i + 1);
		}
		a->get()->setptr(a->get()->getsum() - 1);
		b0->attend(-a->get()->get());
	}
	Int it = Int();
	it.set(b0);
	return a->plus(&it);
}

Int* Int::times(Int* a)
{
	
}

Int* Int::operator/(Int a)
{
	return &Int();
}

Int* Int::operator++()
{
	return &Int();
}

Int* Int::operator--()
{
	return &Int();
}

Int* Int::operator%(Int a)
{
	return &Int();
}

template <class T>
ChainSpot<T>::ChainSpot()
	:nptr(nullptr)
	,lptr(nullptr)
{
}

template <class T>
ChainSpot<T>::~ChainSpot()
{
}

template<class T>
void ChainSpot<T>::set(T value)
{
	this->value = value;
}

template<class T>
T ChainSpot<T>::get()
{
	return value;
}

template<class T>
void ChainSpot<T>::setnext(ChainSpot* next)
{
	nptr = next;
}

template<class T>
void ChainSpot<T>::setlast(ChainSpot* last)
{
	lptr = last;
}

template<class T>
Chain<T>::Chain()
	:headchain(ChainSpot<T>())
	,verychain(headchain)
	,ptr(0)
	,sum(1)
{
}

template<class T>
Chain<T>::~Chain()
{
	num = 0;
	ptr = 0;
}

template<class T>
T Chain<T>::get()
{
	return verchain.value;
}

template<class T>
void Chain<T>::setptr(unsigned long long int p)
{
	if (ptr > p) {
		for (int i = (ptr - p); i--; i > 0) {
			verychain = *verychain.lptr;
		}
	}
	else if (ptr < p) {
		for (int i = (p - ptr); i--; i > 0) {
			verychain = *veryChain.nptr;
		}
	}
	else
		return;
}

template<class T>
int Chain<T>::getptr()
{
	return ptr;
}

template<class T>
void Chain<T>::attend(T v)
{
	verychain.nptr = &ChainSpot<T>(v);
	*(verychain.nptr).lptr = verychain.nptr;
	sum++;
}

template<class T>
void Chain<T>::set(T v)
{
	verychain.set(v);
}

template<class T>
unsigned long long int Chain<T>::getsum()
{
	return sum;
}

template <class T>
void Chain<T>::remove()
{
	if sum == 1
		return;
	if (verychain.lptr)
		verychain.lptr->setnext(*verychain.next);
	if (verychain.nptr) {
		verychain.nptr->setlast(*verychain.last);
		verychain = *verychain.nptr;
	}
	else {
		ptr--;
		verychain.verychain.lptr;
	}
	sum--;
}

template <class T>
void Chain<T>::sethead(ChainSpot<T> cs)
{
	headchain.lptr = &cs;
	cs.setlast = nullptr;
	cs.setnext = &headchain;
	headchain = cs;
	ptr++;
	sum++;
}
