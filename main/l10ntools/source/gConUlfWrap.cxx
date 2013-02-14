/**************************************************************
 * 
 * Licensed to the Apache Software Foundation (ASF) under one
 * or more contributor license agreements.  See the NOTICE file
 * distributed with this work for additional information
 * regarding copyright ownership.  The ASF licenses this file
 * to you under the Apache License, Version 2.0 (the
 * "License"); you may not use this file except in compliance
 * with the License.  You may obtain a copy of the License at
 * 
 *   http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing,
 * software distributed under the License is distributed on an
 * "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY
 * KIND, either express or implied.  See the License for the
 * specific language governing permissions and limitations
 * under the License.
 * 
 *************************************************************/
#include "gConUlf.hxx"
#include <iostream>
#include <fstream>
#include <cstdlib>



/*****************************************************************************
 *********************   G C O N X C S W R A P . C X X   *********************
 *****************************************************************************
 * This includes the c code generated by flex
 *****************************************************************************/



/**********************   I M P L E M E N T A T I O N   **********************/
convert_ulf::convert_ulf(l10nMem& crMemory) : convert_gen_impl(crMemory) {}
convert_ulf::~convert_ulf()                                              {}



/**********************   I M P L E M E N T A T I O N   **********************/
namespace UlfWrap
{
#define IMPLptr convert_gen_impl::mcImpl
#define LOCptr ((convert_ulf *)convert_gen_impl::mcImpl)
#include "gConUlf_yy.c"
}



/**********************   I M P L E M E N T A T I O N   **********************/
void convert_ulf::execute()
{
  UlfWrap::genulf_lex();
}



/**********************   I M P L E M E N T A T I O N   **********************/
void convert_ulf::setKey(char *syyText)
{
  std::string sText = copySource(syyText);

  // locate key (is any)
  msKey = sText.substr(1,sText.size()-2);
}



/**********************   I M P L E M E N T A T I O N   **********************/
void convert_ulf::setText(char *syyText)
{
  std::string sText = copySource(syyText);
  int         nL, nE;


  // isolate text
  nL = sText.find("\"");
  if (nL == (int)std::string::npos)
	return;
  nE = sText.rfind("\"");
  sText = sText.substr(nL+1,nE - nL -1);

  if (mbMergeMode)
  {
    // get all languages (includes en-US)
    std::vector<l10nMem_entry *>& cExtraLangauges = mcMemory.getLanguagesForKey(msKey);
    std::string                   sNewLine;
    nL = cExtraLangauges.size();

	// and all other languages for that key
	for (int i = 0; i < nL; ++i)
    {
      sNewLine = cExtraLangauges[i]->msLanguage + " = \"" +
                 cExtraLangauges[i]->msText +
                 "\"\n";

      writeSourceFile(sNewLine);
    }
  }
  else
    mcMemory.setEnUsKey(msKey, std::string("dummy"), msCollector);
}
