
#include "MslTools.h"
#include "OptionParser.h"
#include "release.h"
#include "getTripletCaMeasurements.h"
#include "System.h"
#include "Chain.h"
#include "Residue.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std;
using namespace MSL;
using namespace MslTools;

int main(int argc, char *argv[]) {

    Options opt = setupOptions(argc, argv);

    vector<string> lines;
    MslTools::readTextFile(lines,opt.pdblist);

    for (uint i = 0; i < lines.size();i++){

	System sys;
	sys.readPdb(lines[i]);

	// Each chain
	for (uint c = 0; c < sys.chainSize();c++){

	    stringstream ss;

	    // Walk through residues
	    Chain &ch = sys.getChain(c);
	    
	    char tmp[100];
	    sprintf(tmp,"%s_%1s.pdb",MslTools::getFileName(lines[i]).c_str(),ch.getChainId().c_str());

	    ss << tmp;
	    PDBWriter pout;
	    pout.open(ss.str());
	    pout.write(ch.getAtomPointers());
	    pout.close();
	}

    }

	

}

Options setupOptions(int theArgc, char * theArgv[]){
    // Create the options
    Options opt;

    // Parse the options
    OptionParser OP;
    OP.setRequired(opt.required);	
    OP.setDefaultArguments(opt.defaultArgs); // the default argument is the --configfile option
    OP.readArgv(theArgc, theArgv);

    if (OP.countOptions() == 0){
	cout << "Usage: splitIntoChains " << endl;
	cout << endl;
	cout << "\n";
	cout << "pdblist PDB\n";
	cout << endl;
	exit(0);
    }

    opt.pdblist = OP.getString("pdblist");
    if (OP.fail()){
	cerr << "ERROR 1111 no pdblist specified."<<endl;
	exit(1111);
    }
    return opt;
}

