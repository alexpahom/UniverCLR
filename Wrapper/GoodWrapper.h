#pragma once
#include "../../../Kursova9DLL/Goods/Goods/Goods.h"
#include "../../../Kursova9DLL/Goods/Goods/Goods.cpp"

using namespace System;
using namespace System::Collections::Generic;

namespace Wrapper {
	// ������ �������� ������ ����� ������ System.String � std::string
	std::string MarshalStdString(String ^ s);
	String^ MarshalSysString(std::string s);

	//-----------------------------------------------------------------
	//-----------------			GOOD CLASS           ------------------
	//-----------------------------------------------------------------
	// 'ref' ��������� ������� �++ ����� �����������
	public ref class WGood {
		int id;
		String ^type, ^model, ^manufacturer;
		Good *instanceGood;

	public:
		// ������������
		WGood();
		WGood(int id, String^ type, String^ model, String^ manufacturer);
		WGood(Good good);

		// �������
		void setId(int id);
		void setType(String^ type);
		void setModel(String^ model);
		void setManufacturer(String^ manufacturer);

		// �������
		int getId();
		String^ getType();
		String^ getModel();
		String^ getManufacturer();
		Good self();
	};

	//---------------------------------------------------------------
	//
	//------------------		GOOD CONTAINER		-----------------
	//---------------------------------------------------------------
	// 'ref' ��������� ������� �++ ����� �����������
	public ref class WGoodContainer
	{
		List<WGood^>^ goods;
		GoodContainer *instanceContainer;
	public:
		WGoodContainer();
		typedef GoodIterator<Good> iterator;
		iterator begin();
		iterator end();

		List<WGood^>^ getGoods();

		WGoodContainer^ add(WGood^ good);
		WGoodContainer^ drop_by_id(int id);
		WGoodContainer^ clear();
		WGood^ find_by_id(int id);
		bool is_id_unique(int id);

		void save();
		void load();
	};
	//---------------------------------------------------------------
	//---------------------------------------------------------------
};