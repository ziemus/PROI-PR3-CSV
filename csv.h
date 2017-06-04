/*

 * csv.h
 *
 *  Created on: 26.05.2017
 *      Author: Ziemek
 */

#ifndef CSV_H_
#define CSV_H_

#include<fstream>
#include"column.h"
#include<iostream>
class CSV {
		/** A vector object of Column objects.
		 * The idea here is for a CSV object to imitate an actual table. */
	std::vector<Column> table;

		/** The separator used in the CSV file; comma by default */
	char separator;

public:
		/** Default ctr */
	CSV(char sep=',');

		/** Destructor */
	~CSV() {}

		/** One of the CSV file modifications, allowing the user for deleting a column of the table */
	void deleteCol(int cInd);

		/** This method allows the user to swap two columns of the table by referring to their numbers */
	void swapCol(int cInd1, int cInd2);

		/** Returns a reference to the cInd-th Column object stored in the table vector */
	Column& operator[](int cInd);

		/** Returns the value of the cInd-th Column object stored in the table vector */
	Column operator[](int cInd) const;

		/** Changes the separator.
		 * Once it has been changed, while saving the data stored in the CSV object into a .txt file,
		 * the fields in the file will be separated by the set separator. */
	void setSep(char sep=',');

		/** Returns the value of the separator */
	char getSep() const;

		/** Reads data into a CSV object from a .txt file */
	CSV& operator<<(std::fstream& read);

		/** Writes data stored in a CSV object into a .txt file in the CSV format */
	std::fstream& operator>>(std::fstream& write) const;
};



#endif /* CSV_H_ */
