/*
 * Logger.h
 *
 *  Created on: 25-Jul-2018
 *      Author: subrahmanyam
 */

#ifndef POC1_FACERECOGNITION_SRC_LOGGER_H_
#define POC1_FACERECOGNITION_SRC_LOGGER_H_


#include <iostream>
#include <fstream>
#include <sstream>


class cLogger{

public:
	cLogger(){};
	void open(std::string sLogName){
		oFileHandler.open(sLogName);
		if(!oFileHandler.is_open()){
			std::cout<<"\n Unable to create a logger file please take care of this first";
		}
		else{
			std::cout<<"\n Success in logger creation";
			oFileHandler<<".........Successfully created the logger..........";
		}

	}
	~cLogger(){

		oFileHandler.close();
	}

	void operator<<(std::string texttoadd){
		oFileHandler<<std::endl<<texttoadd;
	}

private:
	std::ofstream oFileHandler;

};



#endif /* POC1_FACERECOGNITION_SRC_LOGGER_H_ */
