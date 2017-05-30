/*
 * field.h
 *
 *  Created on: 27.05.2017
 *      Author: Ziemek
 */

#ifndef FIELD_H_
#define FIELD_H_

#include<string>

class Field{
		/** Contains text data */
	std::string field;
	 	 /** True - stored data must be enclosed in quotation marks (for fields containing quotes, separators or white characters) */
	bool quoReq;
public:
		/** Default ctr */
	Field(std::string& data, bool quo=false);

		/** Cpy ctr */
	Field(const Field& fcpy);

		/** Move ctr */
	Field(Field&& fmove);

		/** Destructor */
	~Field() {}

		/** Returns reqQuo*/
	bool getQuoReq() const;

		/** Returns stored data*/
	std::string getData() const;

		/** Cpy assignment*/
	Field& operator=(const Field& f2);

		/** Move assignment */
	Field& operator=(Field&& f2);
};



#endif /* FIELD_H_ */
