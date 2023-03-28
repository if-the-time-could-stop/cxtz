#include "cxtz.h"

void Cxtz::encrypt(Int ss, void* src, Int sd, void* det, Int key)
{
}

void Cxtz::decrypt(Int ss, void* src, Int sd, void* det, Int key)
{
	/*��������CXTZ����ϵͳ�ġ��ܼ��ܺ�����
	������ܲ������£�
	���ȣ��������ϵ���һ��������и��ţ�
	���ţ������ݽ��б��ؼ����š�
	˵����
	���㷨��һ�֡��Գơ������㷨�����ڲ����м���������ȷ���Ĳ��裬���������ݱ��������⴦��Ĩȥ�������������޷�ʹ�ü�����ƽ⡣
	��������Ϊʵ������������ȫ������д֮������Ҫ������������֮˼�롣
	*/

}

Int Cxtz::random(Int rmax, Int seed)
{
	/*���Ǳ��㷨�е������ĺ����������������һ��������ֲ����ȵġ��ɸ��ֵ����������ϵͳ��
	�˴�ʹ��ƽ��ȡ�з�ʵ�֡�
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
