#include "tset.h"

TSet::TSet(int mp) : MaxPower(mp), BitField(mp)
{
}

// конструктор копирования
TSet::TSet(const TSet& s) : MaxPower(s.MaxPower), BitField(s.BitField)
{
    MaxPower = s.MaxPower;
    BitField = TBitField(s.BitField);
}

// конструктор преобразования типа
TSet::TSet(const TBitField& bf) : MaxPower(bf.GetLength()), BitField(bf)
{
    MaxPower = bf.GetLength();
    BitField = bf;
}

TSet::operator TBitField()
{
    TBitField temp(this->BitField);
    return temp;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
    return MaxPower;
}

int TSet::IsMember(const int elem) const // элемент множества?
{
    if (elem < 0 || elem >= MaxPower)
    {
        throw ("Всё плохо");
    }
    return BitField.GetBit(elem);
}

void TSet::InsElem(const int elem) // включение элемента множества
{
    if (elem < 0 || elem >= MaxPower)
    {
        throw ("Всё плохо");
    }
    return BitField.SetBit(elem);
}

void TSet::DelElem(const int elem) // исключение элемента множества
{
    if (elem < 0 || elem >= MaxPower)
    {
        throw ("Всё плохо");
    }
    return BitField.ClrBit(elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet& s) // присваивание
{
    BitField = s.BitField;
    MaxPower = s.GetMaxPower();
    return *this;
}

int TSet::operator==(const TSet& s) const // сравнение
{
    return BitField == s.BitField;
}

int TSet::operator!=(const TSet& s) const // сравнение
{
    return BitField != s.BitField;
}

TSet TSet::operator+(const TSet& s) // объединение
{
    int len;
    if(MaxPower > s.MaxPower)
    {
        len = MaxPower;
    }
    else 
    {
        len = s.MaxPower;
    }
    TSet temp(BitField | s.BitField);
    return temp;
}

TSet TSet::operator+(const int elem) // объединение с элементом
{
    TSet resultSet(*this);
    resultSet.BitField.SetBit(elem);
    return resultSet;
}

TSet TSet::operator-(const int elem) // разность с элементом
{
    TSet resultSet(*this);
    resultSet.BitField.ClrBit(elem);
    return resultSet;
}

TSet TSet::operator*(const TSet& s) // пересечение
{
    TSet temp(BitField & s.BitField);
    return temp;
}

TSet TSet::operator~(void) // дополнение
{
    TSet temp(~BitField);
    return temp;
}

// перегрузка ввода/вывода

istream& operator>>(istream& istr, TSet& s) // ввод
{
    int element;
    istr >> element;
    while (element >= 0) {
        s.InsElem(element);
        istr >> element;
    }
    return istr;
}

ostream& operator<<(ostream& ostr, const TSet& s) // вывод
{
    for (int i = 0; i < s.GetMaxPower(); i++) {
        if (s.IsMember(i)) {
            ostr << i << " ";
        }
    }
    return ostr;
}