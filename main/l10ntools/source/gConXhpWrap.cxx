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
#include "gConXhp.hxx"
#include <iostream>
#include <fstream>
#include <cstdlib>



/*****************************************************************************
 *********************   G C O N X H P W R A P . C X X   *********************
 *****************************************************************************
 * This includes the c code generated by flex
 *****************************************************************************/



/************   I N T E R F A C E   I M P L E M E N T A T I O N   ************/
convert_xhp::convert_xhp(l10nMem& crMemory)
	                    : convert_gen_impl(crMemory),
                          mbCollectingData(false)
{
}



/************   I N T E R F A C E   I M P L E M E N T A T I O N   ************/
convert_xhp::~convert_xhp()
{
}



/**********************   I M P L E M E N T A T I O N   **********************/
namespace XhpWrap
{
#define IMPLptr convert_gen_impl::mcImpl
#define LOCptr ((convert_xhp *)convert_gen_impl::mcImpl)
#include "gConXhp_yy.c"
}


/**********************   I M P L E M E N T A T I O N   **********************/
void convert_xhp::execute()
{
  XhpWrap::genXhp_lex();

  if (mbMergeMode)
    writeSourceFile(msCollector);
}



/**********************   I M P L E M E N T A T I O N   **********************/
void convert_xhp::startCollectData(std::string sType, std::string& sCollectedText)
{
  if (mbMergeMode)
    writeSourceFile(msCollector+sCollectedText);
  msCollector.clear();

  // Only start if tag is not imidiatly closed !
  if (sCollectedText[sCollectedText.size()-2] != '/')
  {
    mbCollectingData = true;
    msMergeType      = sType;
    msTag            = sCollectedText;
  }
}



/**********************   I M P L E M E N T A T I O N   **********************/
void convert_xhp::stopCollectData(std::string sType, std::string& sCollectedText)
{
  std::string sKey;
  int    nL;


  // check tag match
  if (sType != msMergeType)
	throw "Conflicting tags: " + msTag + msCollector + sCollectedText;

  // locate key and extract it
  nL    = msTag.find("id=") +4;
  sKey  = msTag.substr(nL, msTag.find("\"", nL+1) - nL);

  if (mbMergeMode)
  {
    // get all languages (includes en-US)
    std::vector<l10nMem_entry *>& cExtraLangauges = mcMemory.getLanguagesForKey(sKey);
    std::string                   sNewLine;
    nL = cExtraLangauges.size();

	// write en-US entry
    writeSourceFile(msCollector+sCollectedText);

	// and all other languages for that key
    for (int i = 0; i < nL; ++i)
    {
      sNewLine = "\n<" + sType + " id=\"" + sKey + "\"" + " xml:lang=\"" +
                 cExtraLangauges[i]->msLanguage + "\">" +
                 cExtraLangauges[i]->msText +
                 "</" + sType + ">";

      writeSourceFile(sNewLine);
    }
  }
  else
    mcMemory.setEnUsKey(sKey, std::string("dummy"), msCollector);

  mbCollectingData = false;
  msCollector.clear();
}  
