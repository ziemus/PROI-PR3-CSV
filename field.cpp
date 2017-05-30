/*
 * field.cpp
 *
 *  Created on: 27.05.2017
 *      Author: Ziemek
 */
#include"field.h"

Field::Field(std::string& data, bool quo=false){
	field=data,quoReq=quo;
}

Field::Field(const Field& fcpy){
	field = fcpy.field;
	quoReq = fcpy.quoReq;
}

Field::Field(Field&& fmove){
	field = std::move(fmove.field);
	quoReq = fmove.quoReq;
}

bool Field::getQuoReq() const{
	return quoReq;
}
std::string Field::getData() const{
	return field;
}
Field& Field::operator=(const Field& f2){
	field=f2.field;
	quoReq=f2.quoReq;
	return *this;
}
Field& Field::operator=(Field&& f2){
	field = std::move(f2.field);
	quoReq = f2.quoReq;
	return *this;
}




