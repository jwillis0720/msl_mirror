/*
----------------------------------------------------------------------------
This file is part of MSL (Molecular Software Libraries) 
 Copyright (C) 2008-2012 The MSL Developer Group (see README.TXT)
 MSL Libraries: http://msl-libraries.org

If used in a scientific publication, please cite: 
 Kulp DW, Subramaniam S, Donald JE, Hannigan BT, Mueller BK, Grigoryan G and 
 Senes A "Structural informatics, modeling and design with a open source 
 Molecular Software Library (MSL)" (2012) J. Comput. Chem, 33, 1645-61 
 DOI: 10.1002/jcc.22968

This library is free software; you can redistribute it and/or
 modify it under the terms of the GNU Lesser General Public
 License as published by the Free Software Foundation; either
 version 2.1 of the License, or (at your option) any later version.

This library is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU
 Lesser General Public License for more details.

You should have received a copy of the GNU Lesser General Public
 License along with this library; if not, write to the Free Software
 Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307, 
 USA, or go to http://www.gnu.org/copyleft/lesser.txt.
----------------------------------------------------------------------------
*/

#ifndef CHARMMTOPOLOGYREADER_H
#define CHARMMTOPOLOGYREADER_H
// STL Includes
#include <vector>
#include <map>
#include <iostream>

//MSL Includes
#include "Reader.h"
#include "CharmmTopologyResidue.h"
#include "MslTools.h"



namespace MSL { 
class CharmmTopologyReader : public Reader {

	public:
		CharmmTopologyReader();
		CharmmTopologyReader(const std::string & _filename);
		CharmmTopologyReader(const CharmmTopologyReader & _top);
		~CharmmTopologyReader();

		void operator=(const CharmmTopologyReader & _top);

		bool read();

		bool residueExists(std::string _name);
		CharmmTopologyResidue & getResidue(std::string _name);
		CharmmTopologyResidue & getLastFoundResidue();
		std::vector<CharmmTopologyResidue*> & getResidues();

		std::string getCharmmVersion() const; 
		std::string getCharmmSubVersion() const; 
		std::string getCharmmFileName() const;
		void setCharmmFileName(std::string &_filename); 

		bool getAutoGenerateAngles() const;
		bool getAutoGenerateDihedrals() const;

		std::string getElement(std::string _atomName);
		double getMass(std::string _atomName);

		void reset();

	private:
		void setup();
		void copy(const CharmmTopologyReader & _top);
		void deletePointers();

                std::string charmmFileName;
		std::vector<CharmmTopologyResidue*> residues; 
		std::map<std::string, CharmmTopologyResidue*> residueMap;
		std::map<std::string, CharmmTopologyResidue*>::iterator foundResidue;
		std::string charmmVersion;
		std::string charmmSubVersion;
		
		std::string defaultFirstPatch;
		std::string defaultLastPatch;

		struct AtomMass {
			unsigned int index;
			std::string atomName;
			double mass;
			std::string element;
		};
		std::map<std::string, AtomMass> masses;

		bool autoGenerateAngles;
		bool autoGenerateDihedrals;

  };

inline bool CharmmTopologyReader::residueExists(std::string _name) {if (_name == "") {_name = "NONE";}; foundResidue = residueMap.find(_name); return foundResidue != residueMap.end(); }
inline CharmmTopologyResidue & CharmmTopologyReader::getResidue(std::string _name) {if (_name == "") {_name = "NONE";}; residueExists(_name); return getLastFoundResidue();}
inline CharmmTopologyResidue & CharmmTopologyReader::getLastFoundResidue() {return *(foundResidue->second);}
inline bool CharmmTopologyReader::getAutoGenerateAngles() const {return autoGenerateAngles;}
inline bool CharmmTopologyReader::getAutoGenerateDihedrals() const {return autoGenerateDihedrals;}
inline std::string CharmmTopologyReader::getCharmmFileName() const { return charmmFileName;}
inline void CharmmTopologyReader::setCharmmFileName(std::string &_filename) { charmmFileName = _filename;}
inline std::string CharmmTopologyReader::getElement(std::string _atomName) { if(masses.find(_atomName) != masses.end()) { return masses[_atomName].element; } else { return std::string(_atomName,1);} } 
inline double CharmmTopologyReader::getMass(std::string _atomName) {
	 if(masses.find(_atomName) != masses.end()) {
		 return masses[_atomName].mass; 
	 } else {
		 std::cerr << "WARNING: 2345 " << _atomName << "not found" << std::endl;
		 return 0.0;
	 } 
} 
inline std::vector<CharmmTopologyResidue*> & CharmmTopologyReader::getResidues() { return residues;}
}

#endif