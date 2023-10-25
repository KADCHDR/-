#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0)
	{
		throw("Всё плохо");
	}
	else 
	{
		BitLen = len;
		MemLen = (len + (sizeof(TELEM) * 8 - 1)) / sizeof(TELEM);
		pMem = new TELEM[MemLen];
		if (pMem != NULL) 
		{
			for (int i = 0; i < MemLen; i++)
				pMem[i] = 0;
		}
	}

}


TBitField::TBitField(const TBitField& bf) // конструктор копирования
{
	if (bf.BitLen < 0)
	{
		throw("Всё плохо ");
	}
	else
	{
		BitLen = bf.BitLen;
		MemLen = bf.MemLen;
		pMem = new TELEM[MemLen];
		if (pMem != NULL) 
		{
			for (int i = 0; i < MemLen; i++)
				pMem[i] = bf.pMem[i];
		}
	}
}

TBitField::~TBitField()
{
	delete[] pMem;
}


int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n < 0 || n >= BitLen)
	{
		throw ("Всё плохо");
	}
	else
	{
		return n / (sizeof(TELEM) * 8);
	}
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if (n < 0 || n >= BitLen)
	{
		throw ("Всё плохо");
	}
	else
	{
		return 1 << (n % (sizeof(TELEM) * 8));
	}
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n > -1) && (n < BitLen))
	{
		pMem[GetMemIndex(n)] = pMem[GetMemIndex(n)] | (GetMemMask(n));
	}
	else
	{
		throw ("Всё плохо");
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n > -1) && (n < BitLen))
	{
		pMem[GetMemIndex(n)] &= ~GetMemMask(n);
	}
	else throw ("Всё плохо");
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n > -1) || (n < BitLen))
	{
		return (pMem[GetMemIndex(n)] & GetMemMask(n)) == 0 ? 0 : 1;
	}
	else
	{
		throw ("Всё плохо");
	}
}

// битовые операции

TBitField& TBitField::operator=(const TBitField& bf) // присваивание
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	delete[] pMem;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; i++) 
	{
		pMem[i] = bf.pMem[i];
	}
	return *this;
}

int TBitField::operator==(const TBitField& bf) const // сравнение
{
	if (bf.BitLen == BitLen) {
		for (int i = 0; i < MemLen; i++) 
		{
			if (pMem[i] != bf.pMem[i]) return 0;
		}
		return 1;
	}
	return 0;
}

int TBitField::operator!=(const TBitField& bf) const // сравнение
{
	return !(*this == bf);
}

TBitField TBitField::operator|(const TBitField& bf) // операция "или"
{
	int len = BitLen;
	if (len < bf.BitLen) len = bf.BitLen;

	TBitField tbf(len);

	for (int i = 0; i < MemLen; i++) 
	{
		tbf.pMem[i] = pMem[i];
	}

	for (int i = 0; i < bf.MemLen; i++) 
	{
		tbf.pMem[i] |= bf.pMem[i];
	}

	return tbf;
}

TBitField TBitField::operator&(const TBitField& bf) // операция "и"
{
	int len = BitLen;
	if (len < bf.BitLen) len = bf.BitLen;

	TBitField tbf(len);

	for (int i = 0; i < MemLen; i++) 
	{
		tbf.pMem[i] = pMem[i];
	}

	for (int i = 0; i < bf.MemLen; i++)
	{
		tbf.pMem[i] &= bf.pMem[i];
	}

	return tbf;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField tbf = (*this);
	for (int i = 0; i < BitLen; i++)
	{
		if (tbf.GetBit(i))
			tbf.ClrBit(i);
		else
			tbf.SetBit(i);
	}
	return tbf;
}

// ввод/вывод

istream& operator>>(istream& istr, TBitField& bf) // ввод
{
    string input;
    istr >> input;

    for (int i = 0; i < bf.BitLen; i++)
    {
        if (input[i] == '0')
        {
            bf.ClrBit(i);
        }
        else if (input[i] == '1')
        {
            bf.SetBit(i);
        }
        else
        {
            throw("Всё плохо");
        }
    }
    return istr;
}

ostream& operator<<(ostream& ostr, const TBitField& bf) // вывод
{
    for (int i = 0; i < bf.BitLen; i++)
    {
        ostr << bf.GetBit(i);
    }
    return ostr;
}