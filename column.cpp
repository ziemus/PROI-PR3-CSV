/*
 * column.cpp
 *
 *  Created on: 26.05.2017
 *      Author: Ziemek
 */
#include"column.h"

Column::Column(bool quo){
	forceQuo=quo;
}

Column::Column(const Column& colcpy){
	column = colcpy.column;
	forceQuo = colcpy.forceQuo;
}

Column::Column(Column&& colcpy){
	column = std::move(colcpy.column);
	forceQuo = colcpy.forceQuo;
}

void Column::addField(Field& add){
	column.push_back(add);
}

void Column::addField(Field&& add){
	column.push_back(add);
}

void Column::setAllQuo(bool on){
	forceQuo=on;
}

size_t Column::recCnt() const{
	return column.size();
}

bool Column::getForcedQuo() const{
	return forceQuo;
}

Field Column::operator[](int recInd) const{
	return column[recInd];
}

Column& Column::operator=(Column&& rVal){
	column = std::move ( rVal.column );
	forceQuo = rVal.forceQuo;
	return *this;
}

Column& Column::operator=(const Column& lVal){
	column = lVal.column;
	forceQuo = lVal.forceQuo;
	return *this;
}
