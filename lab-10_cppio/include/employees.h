#ifndef LAB10_EMPLOYEES_H_INCLUDED
#define LAB10_EMPLOYEES_H_INCLUDED

#include <stdint.h>
#include <vector>
#include <cstring>
#include <ostream>
#include <istream>
#include "bin_manip.h"
#include <iomanip>
#include <algorithm>
namespace employees
{

  class Employee
  {
  public:
    virtual int salary() const = 0;
    Employee(char *name, int32_t base_salary);
    virtual ~Employee();

    virtual void out_b_info(std::ostream &) const = 0;
    virtual void out_info(std::ostream &) const = 0;
    virtual void in_b_info(std::istream &) = 0;
    virtual void in_info(std::istream &) = 0;

  protected:
    int32_t buffer_len = 100;
    char *_name;
    int32_t _base_salary;
  };

  class Developer : virtual public Employee
  {
  public:
    int salary() const override
    {
      int salary = _base_salary;
      if (_has_bonus)
      {
        salary += 1000;
      }
      return salary;
    }
    Developer();
    Developer(char *name, int32_t base_salary, bool has_bonus);
    virtual ~Developer() override;

    void out_b_info(std::ostream &) const override;
    void out_info(std::ostream &) const override;
    void in_b_info(std::istream &) override;
    void in_info(std::istream &) override;

  private:
    bool _has_bonus;
  };

  class SalesManager : virtual public Employee
  {
  public:
    int salary() const override
    {
      return _base_salary + _sold_nm * _price * 0.01;
    }
    SalesManager();
    SalesManager(char *name, int32_t base_salary, int32_t sold_nm, int32_t price);
    virtual ~SalesManager() override;

    void out_b_info(std::ostream &) const override;
    void out_info(std::ostream &) const override;
    void in_b_info(std::istream &) override;
    void in_info(std::istream &) override;

  private:
    int32_t _sold_nm, _price;
  };

  class EmployeesArray
  {
  public:
    EmployeesArray(int32_t size = 0);
    void add(const Employee *e);
    int total_salary() const;
    ~EmployeesArray();
    int size() const;

    const Employee *operator[](int i) const;

  private:
    std::vector<const Employee *> _employees;
  };
}

std::ostream &operator<<(std::ostream &, const employees::Employee &);
std::istream &operator>>(std::istream &, employees::Employee &);
std::ostream &operator<<(std::ostream &, const employees::EmployeesArray &);
std::istream &operator>>(std::istream &, employees::EmployeesArray &);
#endif
