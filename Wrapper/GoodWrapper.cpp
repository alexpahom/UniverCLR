#include "stdafx.h"
#include "../../../Kursova9DLL/Goods/Goods/Goods.h"
#include "../../../Kursova9DLL/Goods/Goods/Goods.cpp"
#include "GoodWrapper.h"
#include <string>

namespace Wrapper {
	//
	//		GOOD CLASS
	//
	// Каждый конструктор создает экземпляр С++ класса Good
	WGood::WGood() {
		instanceGood = new Good();
	};
	WGood::~WGood() {
		delete instanceGood;
	};
	WGood::WGood(int id, String^ type, String^ model, String^ manufacturer) {
		std::string _type = MarshalStdString(type);
		std::string _model = MarshalStdString(model);
		std::string _manufacturer = MarshalStdString(manufacturer);
		instanceGood = new Good(id, _type, _model, _manufacturer);
	}

	WGood::WGood(Good good) {
		int id = good.getId();
		std::string type = good.getType();
		std::string model = good.getModel();
		std::string manufacturer = good.getManufacturer();
		instanceGood = new Good(id, type, model, manufacturer);
	};

	// Конвертация строки типа System.String в std::string
	std::string MarshalStdString(String ^ s) {
		using namespace Runtime::InteropServices;
		std::string os = "";
		const char* chars =
			(const char*)(Marshal::StringToHGlobalAnsi(s)).ToPointer();
		os = chars;
		Marshal::FreeHGlobal(IntPtr((void*)chars));
		return os;
	}

	// Конвертация строки типа std::string в System.String
	String^ MarshalSysString(std::string s) { return gcnew String(s.c_str()); }

	// Сеттеры
	void WGood::setId(int id) { instanceGood->setId(id); };
	void WGood::setType(String^ type) { instanceGood->setType(MarshalStdString(type)); };
	void WGood::setModel(String^ model) { instanceGood->setModel(MarshalStdString(model)); };
	void WGood::setManufacturer(String^ manufacturer) { instanceGood->setManufacturer(MarshalStdString(manufacturer)); };

	// Геттеры
	int WGood::getId() { return instanceGood->getId(); };
	String^ WGood::getType() { return MarshalSysString(instanceGood->getType()); };
	String^ WGood::getModel() { return MarshalSysString(instanceGood->getModel()); };
	String^ WGood::getManufacturer() { return MarshalSysString(instanceGood->getManufacturer()); };
	Good WGood::self() { return *instanceGood; }

	//------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------
	//------------------------------------------------------------------------------------------
	//
	//		GOOD CONTAINER CLASS
	//
	// Конструктор создает экземпляр С++ класса GoodContainer и список
	WGoodContainer::WGoodContainer() {
		instanceContainer = new GoodContainer();
		goods = gcnew List<WGood^>();
	};
	WGoodContainer::~WGoodContainer() {
		delete instanceContainer;
	};

	WGoodContainer::iterator WGoodContainer::begin() {
		return instanceContainer->begin();
	};

	WGoodContainer::iterator WGoodContainer::end() {
		return instanceContainer->end();
	};

	List<WGood^>^ WGoodContainer::getGoods() {
		// создается временная переменная векторного типа
		std::vector<Good> v = instanceContainer->getGoods();
		goods->Clear();
		for each (auto good in v)
		{
			// В список типа List добавляются все элементы из вектора 
			goods->Add(gcnew WGood(good));
		}
		return goods;
	};

	WGoodContainer^ WGoodContainer::add(WGood^ good) {
		instanceContainer->add(good->self());
		return this;
	};

	WGoodContainer^ WGoodContainer::drop_by_id(int id)
	{
		instanceContainer->drop_by_id(id);
		return this;
	};

	WGoodContainer^ WGoodContainer::clear() {
		instanceContainer->clear();
		return this;
	}

	WGood^ WGoodContainer::find_by_id(int id)
	{
		return gcnew WGood(instanceContainer->find_by_id(id));
	}

	bool WGoodContainer::is_id_unique(int id)
	{
		return instanceContainer->is_id_unique(id);
	}

	void WGoodContainer::save() {
		instanceContainer->save();
	}

	void WGoodContainer::load() {
		instanceContainer->load();
	}
}