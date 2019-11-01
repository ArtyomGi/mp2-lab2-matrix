// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// utmatrix.h - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (21.04.2015)
//
// Верхнетреугольная матрица - реализация на основе шаблона вектора

#ifndef __TMATRIX_H__
#define __TMATRIX_H__

#include <iostream>

using namespace std;

const int MAX_VECTOR_SIZE = 100000000;
const int MAX_MATRIX_SIZE = 10000;

// Шаблон вектора
template <class ValType>
class TVector
{
protected:
  ValType *pVector;
  int Size;       // размер вектора
  int StartIndex; // индекс первого элемента вектора
public:
  TVector(int s = 10, int si = 0);
  TVector(const TVector &v);                // конструктор копирования
  ~TVector();
  int GetSize() const { return Size;       } // размер вектора
  int GetStartIndex() const { return StartIndex; } // индекс первого элемента
  ValType& operator[](int pos);             // доступ
  ValType operator[](int pos) const;        // константный доступ
  bool operator==(const TVector &v) const;  // сравнение
  bool operator!=(const TVector &v) const;  // сравнение
  TVector& operator=(const TVector &v);     // присваивание

  TVector<ValType> operator-();

  // скалярные операции
  TVector  operator+(const ValType &val);   // прибавить скаляр
  TVector  operator-(const ValType &val);   // вычесть скаляр
  TVector  operator*(const ValType &val);   // умножить на скаляр

  // векторные операции
  TVector  operator+(const TVector &v);     // сложение
  TVector  operator-(const TVector &v);     // вычитание
  ValType  operator*(const TVector &v);     // скалярное произведение

  // ввод-вывод
  friend istream& operator>>(istream &in, TVector &v)
  {
    for (int i = 0; i < v.Size; i++)
      in >> v.pVector[i];
    return in;
  }
  friend ostream& operator<<(ostream &out, const TVector &v)
  {
	  for (int i = 0; i < v.GetStartIndex(); i++)
		  out << 0 << ' ';
	  for (int i = v.GetStartIndex(); i < v.GetSize(); i++)
		  out << v[i] << ' ';
    return out;
  }
};

template <class ValType>
TVector<ValType>::TVector(int s, int si)
{
	if (s < 0 || s > MAX_VECTOR_SIZE) throw "Size should be positive and lower than MAX_VECTOR_SIZE";
	if (si < 0) throw "Start Index should be positive";

	Size = s;
	StartIndex = si;

	if (Size)
	{
		pVector = new ValType[Size - StartIndex];
		for (int i = 0; i < Size - StartIndex; i++)
			pVector[i] = 0;
	}
	else pVector = nullptr;
} /*-------------------------------------------------------------------------*/

template <class ValType> //конструктор копирования
TVector<ValType>::TVector(const TVector<ValType> &v)
{
	Size = v.Size;
	StartIndex = v.StartIndex;

	pVector = new ValType[Size - StartIndex];
	for (int i = 0; i < Size - StartIndex; i++)
		pVector[i] = v.pVector[i];
} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType>::~TVector()
{
	if (pVector != nullptr) delete[] pVector;
} /*-------------------------------------------------------------------------*/

template <class ValType> // доступ
ValType& TVector<ValType>::operator[](int pos)
{
	//if (pos < 0) throw "Position should be positive";
	if (pos >= Size) throw "Position should be lower than size of vector";
	if (pos < StartIndex) throw "Position should start from Start Index";
	return pVector[pos - StartIndex];
} /*-------------------------------------------------------------------------*/

template <class ValType>
ValType TVector<ValType>::operator[](int pos) const        // константный доступ
{
	if (pos >= Size) throw "Position should be lower than size of vector";
	if (pos < StartIndex) throw "Position should start from Start Index";
	return pVector[pos - StartIndex];
}

template <class ValType> // сравнение
bool TVector<ValType>::operator==(const TVector &v) const
{
	if (this == &v) return 1;
	if (Size != v.Size) return 0;
	if (StartIndex < v.StartIndex) // в v больше нулей, чем в this
	{
		for (int i = 0; i < v.StartIndex - StartIndex; i++)
			if (pVector[i]!=0) return 0;
		for (int i = 0, j = v.StartIndex - StartIndex; i < Size - v.StartIndex; i++, j++) // i для v, j для this
			if (pVector[j] != v.pVector[i]) return 0;
	}
	else if (StartIndex > v.StartIndex) // в this больше нулей, чем в v
	{
		for (int i = 0; i < StartIndex - v.StartIndex; i++)
			if (v.pVector[i]!=0) return 0;
		for (int i = 0, j = StartIndex - v.StartIndex; i < Size - StartIndex; i++, j++) // j для v, i для this
			if (pVector[i] != v.pVector[j]) return 0;
	}
	else
	{
		for (int i = 0; i < Size - StartIndex; i++)
			if (pVector[i] != v.pVector[i]) return 0;
	}
	
	return 1;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TVector<ValType>::operator!=(const TVector &v) const
{
	return !operator==(v);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TVector<ValType>& TVector<ValType>::operator=(const TVector &v)
{	
	if (this == &v) return *this;
	if (pVector != nullptr) delete[] pVector;

	Size = v.Size;
	StartIndex = v.StartIndex;

	pVector = new ValType[Size - StartIndex];
	for (int i = 0; i < Size - StartIndex; i++)
		pVector[i] = v.pVector[i];
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // прибавить скаляр
TVector<ValType> TVector<ValType>::operator+(const ValType &val)
{
	TVector<ValType> Temp(Size, 0);
	for (int i = 0; i < StartIndex; i++)
		Temp[i] = val;
	for (int i = StartIndex; i < Size; i++)
		Temp[i] = operator[](i) + val;
	//for (int i = 0; i < Size - StartIndex; i++)
	//	Temp.pVector[i] += val;
	return Temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычесть скаляр
TVector<ValType> TVector<ValType>::operator-(const ValType &val)
{
	TVector<ValType> Temp(Size, 0);
	for (int i = 0; i < StartIndex; i++)
		Temp[i] = -val;
	for (int i = StartIndex; i < Size; i++)
		Temp[i] = operator[](i) - val;
	//for (int i = 0; i < Size - StartIndex; i++)
	//	Temp.pVector[i] -= val;
	return Temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // умножить на скаляр
TVector<ValType> TVector<ValType>::operator*(const ValType &val)
{
	TVector<ValType> Temp(*this);
	//for (int i = 0; i < StartIndex; i++)
	//	Temp[i] = 0;
	for (int i = StartIndex; i < Size; i++)
		Temp[i] *= val;
	//for (int i = 0; i < Size - StartIndex; i++)
	//	Temp.pVector[i] *= val;
	return Temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TVector<ValType> TVector<ValType>::operator+(const TVector<ValType> &v)
{
	if (Size != v.Size) throw "The dimensions of vectors should be equal";
	int SImin = StartIndex < v.StartIndex ? StartIndex : v.StartIndex;
	
	TVector<ValType> Temp(Size, SImin);
	if (StartIndex > v.StartIndex)
	{
		/*for (int i = 0; i < StartIndex - v.StartIndex; i++)
			Temp.pVector[i] = v.pVector[i];
		for (int i = StartIndex - v.StartIndex, j = 0; i < Size - v.StartIndex; i++, j++) // i для v, j для this
			Temp.pVector[i] = pVector[j] + v.pVector[i];*/
		for (int i = v.StartIndex; i < StartIndex; i++)
			Temp[i] = v[i];
		for (int i = StartIndex; i < Size; i++)
			Temp[i] = (*this)[i] + v[i];
	}
	else
	{
		/*for (int i = 0; i < v.StartIndex - StartIndex; i++)
			Temp.pVector[i] = pVector[i];
		for (int i = v.StartIndex - StartIndex, j = 0; i < Size - StartIndex; i++, j++) // j для v, i для this
			Temp.pVector[i] = pVector[i] + v.pVector[j];*/
		for (int i = StartIndex; i < v.StartIndex; i++)
			Temp[i] = (*this)[i];
		for (int i = v.StartIndex; i < Size; i++)
			Temp[i] = (*this)[i] + v[i];
	}

	return Temp;
		
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TVector<ValType> TVector<ValType>::operator-(const TVector<ValType> &v)
{
	if (Size != v.Size) throw "The dimensions of vectors should be equal";
	int SImin = StartIndex < v.StartIndex ? StartIndex : v.StartIndex;

	TVector<ValType> Temp(Size, SImin);
	if (StartIndex > v.StartIndex)
	{
		/*for (int i = 0; i < StartIndex - v.StartIndex; i++)
			Temp.pVector[i] = -v.pVector[i];
		for (int i = StartIndex - v.StartIndex, j = 0; i < Size - v.StartIndex; i++, j++) // i для v, j для this
			Temp.pVector[i] = pVector[j] - v.pVector[i];*/
		for (int i = v.StartIndex; i < StartIndex; i++)
			Temp[i] = -v[i];
		for (int i = StartIndex; i < Size; i++)
			Temp[i] = (*this)[i] - v[i];
	}
	else
	{
		/*for (int i = 0; i < v.StartIndex - StartIndex; i++)
			Temp.pVector[i] = pVector[i];
		for (int i = v.StartIndex - StartIndex, j = 0; i < Size - StartIndex; i++, j++) // j для v, i для this
			Temp.pVector[i] = pVector[i] + v.pVector[j];*/
		for (int i = StartIndex; i < v.StartIndex; i++)
			Temp[i] = (*this)[i];
		for (int i = v.StartIndex; i < Size; i++)
			Temp[i] = (*this)[i] - v[i];
	}

	return Temp;
} /*-------------------------------------------------------------------------*/

template <class ValType> // скалярное произведение
ValType TVector<ValType>::operator*(const TVector<ValType> &v)
{
	if (Size != v.Size) throw "The dimensions of vectors should be equal";

	ValType Dot = 0;
	if (StartIndex > v.StartIndex)
	{
		for (int i = StartIndex; i < Size; i++)
			Dot += (*this)[i] * v[i];
	}
	else
	{
		for (int i = v.StartIndex; i < Size; i++)
			Dot += (*this)[i] * v[i];
	}

	return Dot;
} /*-------------------------------------------------------------------------*/

template <class ValType>
TVector<ValType> TVector<ValType>::operator-()
{
	TVector<ValType> Temp(*this);
	for (int i = StartIndex; i < Size; i++)
		Temp[i] = -(*this)[i];
	return Temp;
}

// Верхнетреугольная матрица
template <class ValType>
class TMatrix : public TVector<TVector<ValType> >
{
public:
  TMatrix(int s = 10);                           
  TMatrix(const TMatrix &mt);                    // копирование
  TMatrix(const TVector<TVector<ValType> > &mt); // преобразование типа
  bool operator==(const TMatrix &mt) const;      // сравнение
  bool operator!=(const TMatrix &mt) const;      // сравнение
  TMatrix& operator= (const TMatrix &mt);        // присваивание
  TMatrix  operator+ (const TMatrix &mt);        // сложение
  TMatrix  operator- (const TMatrix &mt);        // вычитание

  // ввод / вывод
  friend istream& operator>>(istream &in, TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      in >> mt.pVector[i];
    return in;
  }
  friend ostream & operator<<( ostream &out, const TMatrix &mt)
  {
    for (int i = 0; i < mt.Size; i++)
      out << mt.pVector[i] << endl;
    return out;
  }
};

template <class ValType>
TMatrix<ValType>::TMatrix(int s): TVector<TVector<ValType> >(s)
{
	if (s < 0 || s > MAX_MATRIX_SIZE) throw "Size should be positive and lower than MAX_VECTOR_SIZE";
	//pVector - массив векторов (ValType = TVector<ValType>)
	//инициализация pVector
	for (int i = 0; i < s; i++)
		pVector[i] = TVector<ValType>(s, i);
} /*-------------------------------------------------------------------------*/

template <class ValType> // конструктор копирования
TMatrix<ValType>::TMatrix(const TMatrix<ValType> &mt):
  TVector<TVector<ValType> >(mt){}

template <class ValType> // конструктор преобразования типа
TMatrix<ValType>::TMatrix(const TVector<TVector<ValType> > &mt):
  TVector<TVector<ValType> >(mt) {}

template <class ValType> // сравнение
bool TMatrix<ValType>::operator==(const TMatrix<ValType> &mt) const
{
	return TVector<TVector<ValType> >::operator==(mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // сравнение
bool TMatrix<ValType>::operator!=(const TMatrix<ValType> &mt) const
{
	return TVector<TVector<ValType> >::operator!=(mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // присваивание
TMatrix<ValType>& TMatrix<ValType>::operator=(const TMatrix<ValType> &mt)
{
	TVector<TVector<ValType> >::operator=(mt);
	return *this;
} /*-------------------------------------------------------------------------*/

template <class ValType> // сложение
TMatrix<ValType> TMatrix<ValType>::operator+(const TMatrix<ValType> &mt)
{
	return TVector<TVector<ValType> >::operator+(mt);
} /*-------------------------------------------------------------------------*/

template <class ValType> // вычитание
TMatrix<ValType> TMatrix<ValType>::operator-(const TMatrix<ValType> &mt)
{
	return TVector<TVector<ValType> >::operator-(mt);
} /*-------------------------------------------------------------------------*/

// TVector О3 Л2 П4 С6
// TMatrix О2 Л2 П3 С3
#endif
