#include"csv.h"

CSV::CSV(char sep){
	separator=sep;
}

void CSV::deleteCol(int cInd){
	table.erase(table.begin()+cInd);
}

void CSV::swapCol(int cInd1, int cInd2){
	Column temp = std::move ( table[cInd1] );
	table[cInd1]= std::move ( table[cInd2] );
	table[cInd2]= std::move ( temp );
}

Column& CSV::operator[](int cInd){
	return table[cInd];
}

Column CSV::operator[](int cInd) const{
	return table[cInd];
}

void CSV::setSep(char sep){
	separator=sep;
}

char CSV::getSep() const{
	return separator;
}

CSV& CSV::operator<<(std::fstream& read){
	size_t colNo=0;
	char ch;
	bool req;
	std::string data;
	int state=1;

	while(state!=12){
		switch(state){
		case 1:
			data.clear();
			req=false;

			read >> std::noskipws >> ch;

			if (ch == '\"') state = 3;
			else if (ch == separator) state = 0;
			else if (ch == '\n' || read.eof() ) state = 11;
			else state = 2;

			break;
		case 2:
			data+=ch;

			read >> std::noskipws >> ch;

			if(ch == separator) state = 0;
			else if(ch == '\n' || read.eof() ) state = 11;

			break;
		case 3:
			read >> std::noskipws >> ch;

			if(ch == separator || ch == '\n') state = 7;
			else if (ch == '\"') state = 5;
			else state = 4;

			break;
		case 4:
			data+=ch;

			read >> std::noskipws >> ch;

			if(ch == separator || ch == '\n') state = 7;
			else if (ch == '\"') state = 5;

			break;
		case 5:
			read >> std::noskipws >> ch;

			if (ch == separator) state = 0;
			else if(ch == '\n' || read.eof() ) state = 11;
			else state = 6;

			break;
		case 6:
			data+="\"\"";
			req=true;

			read >> std::noskipws >> ch;

			ch=='\"' ? state = 9 : state = 8;

			break;
		case 7:
			data+=ch;
			req=true;

			read >> std::noskipws >> ch;

			ch=='\"' ? state = 9 : state = 8;

			break;
		case 8:
			data+=ch;

			read >> std::noskipws >> ch;

			if(ch=='\"') state = 9;

			break;
		case 9:
			read >> std::noskipws >> ch;

			if(ch=='\"') state = 10;
			else if(ch == separator) state = 0;
			else if(ch == '\n' || read.eof() ) state = 11;

			break;
		case 10:
			data+="\"\"";

			read >> std::noskipws >> ch;

			ch=='\"' ? state = 9 : state = 8;

			break;
		case 0:
			{table.push_back(false);
			Field f(data,req);
			table.back().addField( std::move(f) );

			state=1;}

			break;
		case 11:
			{table.push_back(false);
			Field f(data,req);
			table.back().addField( std::move(f) );

			state=12;}

			break;
		}
	}
	state = 1;

	while(state!=12){
		switch(state){
		case 1:
			data.clear();
			req=false;

			read >> std::noskipws >> ch;

			if (ch == '\"') state = 3;
			else if (ch == separator) state = 0;
			else if (ch == '\n' || read.eof() ) state = 11;
			else state = 2;

			break;
		case 2:
			data+=ch;

			read >> std::noskipws >> ch;

			if(ch == separator || ch == '\n') state = 0;
			else if(read.eof()) state = 11;

			break;
		case 3:
			read >> std::noskipws >> ch;

			if(ch == separator || ch == '\n') state = 7;
			else if (ch == '\"') state = 5;
			else state = 4;

			break;
		case 4:
			data+=ch;

			read >> std::noskipws >> ch;

			if(ch == separator || ch == '\n') state = 7;
			else if (ch == '\"') state = 5;

			break;
		case 5:
			read >> std::noskipws >> ch;

			if (ch == separator || ch == '\n') state = 0;
			else if(read.eof()) state = 11;
			else state = 6;

			break;
		case 6:
			data+="\"\"";
			req=true;

			read >> std::noskipws >> ch;

			ch=='\"' ? state = 9 : state = 8;

			break;
		case 7:
			data+=ch;
			req=true;

			read >> std::noskipws >> ch;

			ch=='\"' ? state = 9 : state = 8;

			break;
		case 8:
			data+=ch;

			read >> std::noskipws >> ch;

			if(ch=='\"') state = 9;

			break;
		case 9:
			read >> std::noskipws >> ch;

			if(ch=='\"') state = 10;
			else if(ch == separator || ch == '\n') state = 0;
			else if( read.eof() )state = 11;

			break;
		case 10:
			data+="\"\"";

			read >> std::noskipws >> ch;

			ch=='\"' ? state = 9 : state = 8;

			break;
		case 0:
			/*save data and req to a Field,
			 * add a column,
			 * add the Field to the column,
			 * set state to 1 so that the next field can be analyzed */
			{
			Field newField(data,req);
			table[ colNo ].addField(std::move(newField));
			colNo=(colNo+1) %table.size();
			state=1;
			}
			break;
		case 11:
			/*save data and req to a Field,
			 * add the Field to the proper column,
			 * do something so that the loop no longer executes*/
			{
            Field newField(data,req);
			table[ colNo ].addField(std::move(newField));
			colNo = (colNo+1) % table.size();
			state=12;
			}
			break;
		}
	}

	return *this;
}

std::fstream& CSV::operator>>(std::fstream& write) const{
	size_t colNo, recNo, colCnt, recCnt;
	recCnt = table[0].recCnt();
	colCnt = table.size();

	for (recNo=0 ; recNo<recCnt ; recNo++)
	{
		for(colNo=0 ; colNo<colCnt ; colNo++){
            std::cout<<table[colNo][recNo].getData()<<"\tp";
		}
		std::cout<<std::endl;
	}

	for (recNo=0 ; recNo<recCnt ; recNo++)
	{
		for(colNo=0 ; colNo<colCnt ; colNo++){
			if(table[colNo][recNo].getQuoReq() || table[colNo].getForcedQuo() )
				write << "\"" + table[colNo][recNo].getData() + "\"";
			else
				write << table[colNo][recNo].getData();

            if( colNo != colCnt-1 || recNo != recCnt-1 ){
                if(colNo == colCnt-1)
                    write << '\n';
                else
                    write << separator;
            }
		}
    }

	return write;
}


