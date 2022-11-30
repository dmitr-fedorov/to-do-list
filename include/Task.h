#pragma once

#include <string>
#include <string_view>
#include <ostream>

enum TaskStatus
{
	on,
	done,  	
};

/*
  �����, �������������� ����� ������.
*/
class Task
{
public:
	// ������ ������ �� ������������� ������� ������������ ��-���������.

	Task(const std::string_view& name, const std::string_view& descr,
		const std::string_view& date, const std::string_view& categ);
	~Task();

	/*
	  ���������� �������� TaskStatus, ������� ����������
	  ������ ���������� ���� ������.
	*/
	TaskStatus GetCompletionStatus() const;

	/*
	  ������������� ��� ������ � ������ �����������. 
	*/
	void SetDone();

	/*
	  ����������� ����� ���� ������ �������� �� ����������.
	*/
	void Update(const std::string_view& descr, const std::string_view& date,
		const std::string_view& categ);

	void Display(std::ostream& out) const;

	bool NameIs(const std::string& op, const std::string& value);
	bool DescriptionIs(const std::string& op, const std::string& value);
	bool DateIs(const std::string& op, const std::string& value);
	bool CategoryIs(const std::string& op, const std::string& value);
	bool StatusIs(const std::string& op, const std::string& value);

private:	
	std::string m_name;
	std::string m_description;
	std::string m_date;
	std::string m_category;
	TaskStatus m_status;
};
