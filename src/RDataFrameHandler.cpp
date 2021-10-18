/* RDataFrame Handler Module
Much of this (for now) takes from theh RDataFrame tutorial
*/

// Standard Includes
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <streambuf>
#include <iterator>
#include <map>

// ROOT
#include <TTree.h>
#include <TFile.h>
#include <TKey.h>

#include <ROOT/RDF/RDisplay.hxx>

// Header
#include "RDataFrameHandler.h"

////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Creates the RDataFrame objecct with the file list in the RDataFrameHandler
 * Returns 0 if successful
 * Returns 1 if not successful
 * @return ROOT::RDataFrame
 */
ROOT::RDataFrame RDataFrameHandler::CreateRDataFrame()
{
   std::cout << "Getting tree names\n";
   // just the first file. Should probably check all the others too.
   std::string treeName = GetTreeName(filenames.at(0));

   // We read the tree from the file and create a RDataFrame, a class that
   // allows us to interact with the data contained in the tree.
   // We select a default column, a *branch* to adopt ROOT jargon, which will
   // be looked at if none is specified by the user when dealing with filters
   // and actions.
   // std::cout << "Filename1: " << filenames[0] << "\n";
   ROOT::RDataFrame df(treeName, filenames);

   return df;
}

////////////////////////////////////////////////////////////////////////////////
/// @brief Gets the tree name of the top level tree in the root file at filepath
std::string RDataFrameHandler::GetTreeName(std::string filepath)
{
   TFile *f = TFile::Open(filepath.c_str());

   TIter       next(f->GetListOfKeys());
   TKey *      key;
   TTree *     T;
   std::string keyname;
   while ((key = (TKey *)next())) {
      if (strcmp(key->GetClassName(), "TTree")) continue; // do not use keys that are not trees
      T = (TTree *)f->Get(key->GetName());                // fetch the Tree header in memory
      // totalEvents = T->GetEntries();
      printf("tree name: %50s\t\n", key->GetName());
      keyname = key->GetName();
      delete T;
   }

   // TObject *obj = key->ReadObj();

   return keyname;
}

////////////////////////////////////////////////////////////////////////////////
/**
 * @brief Adds a file to the RDataFrameHandler's list of filenames. Want the absolute path to the file
 * Return 0 if no problems and the file exists.
 * Return 1 if the file does not exist
 * @param filename
 * @return Int_t
 */
Int_t RDataFrameHandler::AddFile(std::string filename)
{
   filenames.push_back(filename);
   // Check if exists first
   return 0;
}

////////////////////////////////////////////////////////////////////////////////
/**
 * @brief adds multiple files
 *
 */
Int_t RDataFrameHandler::AddFiles(std::vector<std::string> filenames)
{
   for (auto iter = filenames.begin(); iter != filenames.end(); ++iter) {
      // If iter is a valid file:
      // std::cout << "adding " << iter->c_str() << "\n";
      AddFile(iter->c_str());
      // attack->makeDamage();
   }
   return 0;
}

RDataFrameHandler::RDataFrameHandler() {}