/*
 * column.h
 *
 *  Created on: 26.05.2017
 *      Author: Ziemek
 */

#ifndef COLUMN_H_
#define COLUMN_H_

#include<vector>
#include"field.h"

class Column{
		/** Vector of the custom Field type, storing all fields a column stores in a CSV file */
	std::vector<Field> column;

		/** If true - user desired to store all data in quotation marks even if it's not necessary
		 *  False by default */
	bool forceQuo;
public:
		/** Default ctr */
	Column();

		/** Cpy ctr */
	Column(const Column& colcpy);

		/** Move ctr */
	Column(Column&& colcpy);

		/** Destructor */
	~Column() {}

		/** adds a L-val Field object to the column vector */
	void addField(Field& add);

		/** Adds a R-val Field object to the column vector  */
	void addField(Field&& add);

		/** Sets the forceQuo member to the desired value*/
	void setAllQuo(bool on);

		/** Returns the value of the forceQuo member */
	bool getForcedQuo() const;

		/** Returns the size of the column vector */
	size_t recCnt() const;

		/** Returns the value of the recInd-th Field object stored in the column vector */
	Field operator[](int recInd) const;

		/** Returns a reference to the recInd-th Field object stored in the column vector */
	Field& operator[](int recInd);

		/** Cpy assignment */
	Column& operator=(Column&& rVal);

		/** Move assignment */
	Column& operator=(const Column& lVal);
};



#endif /* COLUMN_H_ */
