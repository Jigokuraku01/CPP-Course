#include "employees.h"

employees::Employee::Employee(char *name, int32_t base_salary)
{
	int len = buffer_len;

	_name = new char[len + 1];
	for (int i = 0; i < len + 1; ++i)
		_name[i] = 0;
	if (name != nullptr)
		strcpy(_name, name);

	_base_salary = base_salary;
}

employees::Employee::~Employee()
{
	if (_name != nullptr)
		delete[] _name;
}

employees::Developer::Developer(char *name, int32_t base_salary, bool has_bonus) : Employee(name, base_salary)
{
	_has_bonus = has_bonus;
}

employees::Developer::Developer() : Employee(nullptr, 0)
{
	_has_bonus = 0;
}
employees::Developer::~Developer()
{
}

employees::SalesManager::SalesManager(char *name, int32_t base_salary, int32_t sold_nm, int32_t price) : Employee(name, base_salary)
{
	_sold_nm = sold_nm;
	_price = price;
}

employees::SalesManager::SalesManager() : Employee(nullptr, 0)
{
	_sold_nm = 0;
	_price = 0;
}

employees::SalesManager::~SalesManager()
{
}

employees::EmployeesArray::EmployeesArray(int32_t size)
{
	std::vector<const Employee *> _employees(size);
}

employees::EmployeesArray::~EmployeesArray()
{
	for (auto k : _employees)
		delete k;
}

void employees::EmployeesArray::add(const Employee *e)
{
	if (e == nullptr)
		throw("nullptr argument exception");
	_employees.push_back(e);
}

int employees::EmployeesArray::total_salary() const
{
	int ans = 0;
	for (size_t i = 0; i < _employees.size(); ++i)
		ans += _employees[i]->salary();
	return ans;
}

const employees::Employee *employees::EmployeesArray::operator[](int i) const
{
	return _employees[i];
}

int employees::EmployeesArray::size() const
{
	return _employees.size();
}

std::ostream &operator<<(std::ostream &os, const employees::Employee &empl)
{
	if (os.iword(Manip::get_bin_flag()))
		empl.out_b_info(os);
	else
		empl.out_info(os);
	return os;
}
std::istream &operator>>(std::istream &is, employees::Employee &empl)
{
	if (is.iword(Manip::get_bin_flag()))
		empl.in_b_info(is);
	else
		empl.in_info(is);
	return is;
}

void employees::Developer::out_info(std::ostream &os) const
{
	os << "Developer" << std::endl;
	os << "Name: " << Employee::_name << std::endl;
	os << "Base Salary: " << Employee::_base_salary << std::endl;
	os << "Has bonus: " << (_has_bonus ? '+' : '-') << std::endl;
}

void employees::SalesManager::out_info(std::ostream &os) const
{
	os << "Sales Manager" << std::endl;
	os << "Name: " << Employee::_name << std::endl;
	os << "Base Salary: " << Employee::_base_salary << std::endl;
	os << "Sold items: " << _sold_nm << std::endl;
	os << "Item price: " << _price << std::endl;
}

void employees::SalesManager::in_info(std::istream &os)
{
	os >> Employee::_name >> Employee::_base_salary >> _sold_nm >> _price;
}

void employees::Developer::in_info(std::istream &os)
{
	os >> Manip::read_c_str(Employee::_name, Employee::buffer_len) >> Employee::_base_salary >> _has_bonus;
}

void employees::Developer::out_b_info(std::ostream &os) const
{
	os << Manip::write_le_int32(1) << Manip::write_c_str(Employee::_name) << Manip::write_le_int32(Employee::_base_salary) << Manip::write_bool(_has_bonus);
}

void employees::SalesManager::out_b_info(std::ostream &os) const
{
	os << Manip::write_le_int32(2) << Manip::write_c_str(Employee::_name) << Manip::write_le_int32(Employee::_base_salary) << Manip::write_le_int32(_sold_nm) << Manip::write_le_int32(_price);
}

void employees::SalesManager::in_b_info(std::istream &is)
{
	is >> Manip::read_c_str(Employee::_name, Employee::buffer_len) >> Manip::read_le_int32(Employee::_base_salary) >> Manip::read_le_int32(_sold_nm) >> Manip::read_le_int32(_price);
}

void employees::Developer::in_b_info(std::istream &is)
{
	is >> Manip::read_c_str(Employee::_name, Employee::buffer_len) >> Manip::read_le_int32(Employee::_base_salary) >> Manip::read_bool(_has_bonus);
}

std::ostream &operator<<(std::ostream &os, const employees::EmployeesArray &empl_arr)
{
	if (os.iword(Manip::get_bin_flag()))
	{
		os << Manip::write_le_int32(empl_arr.size());
		for (int i = 0; i < empl_arr.size(); ++i)
		{
			auto k = empl_arr[i];
			const employees::Developer *d = dynamic_cast<const employees::Developer *>(k);
			if (d != nullptr)
				os << Manip::bin << *d;
			else
			{
				const employees::SalesManager *s = dynamic_cast<const employees::SalesManager *>(k);
				os << Manip::bin << *s;
			}
		}
	}
	else
	{
		for (int i = 0; i < empl_arr.size(); ++i)
		{
			os << Manip::nobin << i + 1 << ". ";
			const employees::Developer *d = dynamic_cast<const employees::Developer *>(empl_arr[i]);
			if (d != nullptr)
				os << Manip::nobin << *d;
			else
			{
				const employees::SalesManager *s = dynamic_cast<const employees::SalesManager *>(empl_arr[i]);
				os << Manip::nobin << *s;
			}
		}
		os << Manip::nobin << "== Total salary: " << empl_arr.total_salary() << std::endl
		   << std::endl;
	}
	return os;
}

std::istream &operator>>(std::istream &is, employees::EmployeesArray &empl_arr)
{
	int32_t len;
	is >> Manip::read_le_int32(len);
	for (int i = 0; i < len; ++i)
	{
		int32_t x;
		is >> Manip::read_le_int32(x);
		if (x == 1)
		{
			employees::Developer *tmp_dev = new employees::Developer();
			is >> *tmp_dev;
			empl_arr.add(tmp_dev);
		}
		else if (x == 2)
		{
			employees::SalesManager *tmp_sm = new employees::SalesManager();
			is >> *tmp_sm;
			empl_arr.add(tmp_sm);
		}
	}
	return is;
}
