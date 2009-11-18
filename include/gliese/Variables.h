#ifndef VARIABLES_H_
#define VARIABLES_H_


#include "any.hpp"

#include "hash_map"
#include "ostream"
#include "string"


class Variables;


class VariablesIterator
{
    friend class Variables;

public:
    VariablesIterator();
    virtual ~VariablesIterator();

    bool operator == (const VariablesIterator & i) const;
    bool operator != (const VariablesIterator & i) const;

    const unsigned int & operator * ();
    const unsigned int * operator -> ();

    VariablesIterator & operator ++ ();
    VariablesIterator & operator ++ (int unused);

private:
    VariablesIterator(const Variables * variables, bool isBeginIterator);

private:
	const Variables * variables;
    std::hash_map<unsigned int, boost::any>::const_iterator iterator;
};


class Variables
{
	friend class VariablesIterator;
	friend std::ostream & operator << (std::ostream & output, const Variables & variables);

public:
    typedef VariablesIterator iterator;
    typedef VariablesIterator const_iterator;

public:
	Variables();
	Variables(const Variables & other);
	virtual ~Variables();

	Variables & operator = (const Variables & other);

	iterator begin() const;
    iterator end() const;

	template <typename Any> bool get(unsigned int id, Any & variable) const
	{
		std::hash_map<unsigned int, boost::any>::const_iterator i = variables.find(id);
		if (i != variables.end()) {
			 variable = boost::any_cast<Any>(i->second);
			 return true;
		} else
			 return false;
	}

	template <typename Any> void set(unsigned int id, const Any & variable)
	{
		variables[id] = variable;
	}

	void remove(unsigned int id);

	int getInteger(unsigned int id) const;
	double getDouble(unsigned int id) const;
	bool getBoolean(unsigned int id) const;
	char getChar(unsigned int id) const;
	std::string getString(unsigned int id) const;

	bool exists(unsigned int id) const;

	bool operator == (const Variables & other) const;

protected:
	bool get(unsigned int id, boost::any & variable) const;

protected:
	std::hash_map<unsigned int, boost::any> variables;
};


std::ostream & operator << (std::ostream & output, const Variables & variables);


#endif /*VARIABLES_H_*/
