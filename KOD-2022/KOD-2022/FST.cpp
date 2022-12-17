#include "pch.h"
#include "Header.h"
#include <iostream>

namespace FST //конечный автомат
{
	RELATION::RELATION(char c = NULL, short ns = NULL)
	{
		this->symbol = c;
		this->nnode = ns;
	};

	NODE::NODE()
	{
		this->n_relation = NULL;
		this->relations = NULL;
	};

	NODE::NODE(short n, RELATION rel, ...)
	{
		RELATION* temp = &rel;
		this->relations = new RELATION[n];
		this->n_relation = n;
		for (short i = 0; i < n; i++)
			this->relations[i] = *(temp + i);
	};

	FST::FST(short ns, NODE n, ...)
	{
		this->node = new NODE[ns];
		NODE* temp = &n;
		this->nstates = ns;
		this->rstates = new short[ns];
		for (short i = 0; i < ns; i++)
			this->node[i] = *(temp + i);
		rstates[0] = 0;
		position = -1;
	}

	FST::FST(char* s, FST& fst)
	{
		this->node = new NODE[fst.nstates];
		NODE* temp = fst.node;
		this->string = s;
		this->nstates = fst.nstates;
		this->rstates = new short[this->nstates];
		for (short i = 0; i < this->nstates; i++)
			this->node[i] = *(temp + i);
		rstates[0] = 0;
		position = -1;

	}
	bool step(FST& fst, short*& rstates)           //шаг конечного автомата
	{
		bool rc = false;                                //флаг - результат шага
		std::swap(rstates, fst.rstates);                        //ћен€ем местами два массива возможных состо€ний
		for (short i = 0; i < fst.nstates; i++)                      //проход по всей цепочке (массиву)
		{
			if (rstates[i] == fst.position)                        //если позици€ i массива равна текущей позиции в графе(если предыдущий шаг не выполнен - выход)
			{
				for (short j = 0; j < fst.node[i].n_relation; j++)            //возможностей перехода
				{
					if (fst.node[i].relations[j].symbol == fst.string[fst.position])  //инцидентное ребро равно текущей позиции
					{
						fst.rstates[fst.node[i].relations[j].nnode] = fst.position + 1;//позици€ в  ј++
						rc = true;                            //шаг выполнен успешно
					};
				};
			}

		};
		return rc;
	};
	bool execute(FST& fst)                      //выполнение  ј
	{
		short* rstates = new short[fst.nstates];          //¬озможные состо€ни€ графа
		memset(rstates, 0xff, sizeof(short) * fst.nstates);      //заполнение области пам€ти значением 255 (последний парам. - кол-во байт)
		short lstring = strlen(fst.string);            //длина цепочки (почему не strlen??????)
		bool rc = true;                        //флаг, указывающий на правильность выполнение каждого шага
		for (short i = 0; i < lstring && rc; i++)          //проход по цепочке. ћожет выйти заранее, если пред. шаг выполнен неправильно
		{
			fst.position++;                      //позици€ в цепочке
			rc = step(fst, rstates);                //шаг в цепочке
		};
		delete[] rstates;                      //удаление второго массива
		return (rc ? (fst.rstates[fst.nstates - 1] == lstring) : rc);//если false - вернуть false иначе вернуть равенство(последний элемент в массиве равен числу длины цепочки)
	};
	//bool execute(FST& fst)
	//{
	//	int i, j;
	//	memset(fst.rstates, -1, fst.nstates * sizeof(short)); // «аполн€ем fst.rstates массив -1-ами размером  fst.nstates * sizeof(short)
	//	for (fst.rstates[0] = 0, fst.position = 0; fst.position < (signed)(strlen(fst.string)); fst.position++)
	//	{
	//		for (i = 0; i < fst.nstates; i++)
	//		{
	//			if (fst.rstates[i] == fst.position)
	//			{
	//				for (j = 0; j < fst.node[i].n_relation; j++) //релейшены 
	//				{
	//					if (fst.node[i].relations[j].symbol == fst.string[fst.position])
	//					{
	//						fst.rstates[fst.node[i].relations[j].nnode] = fst.position + 1;
	//					}
	//				};
	//			};
	//		};
	//	};
	//	return (fst.rstates[fst.nstates - 1] == (strlen(fst.string))); // —овпадает ли конечна€ позици€ с длиной строки
	//};
}