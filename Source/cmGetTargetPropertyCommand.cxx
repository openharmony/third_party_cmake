/*=========================================================================

  Program:   CMake - Cross-Platform Makefile Generator
  Module:    $RCSfile$
  Language:  C++
  Date:      $Date$
  Version:   $Revision$

  Copyright (c) 2002 Kitware, Inc., Insight Consortium.  All rights reserved.
  See Copyright.txt or http://www.cmake.org/HTML/Copyright.html for details.

     This software is distributed WITHOUT ANY WARRANTY; without even 
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR 
     PURPOSE.  See the above copyright notices for more information.

=========================================================================*/
#include "cmGetTargetPropertyCommand.h"

// cmSetTargetPropertyCommand
bool cmGetTargetPropertyCommand::InitialPass(
  std::vector<std::string> const& args)
{
  if(args.size() != 3 )
    {
    this->SetError("called with incorrect number of arguments");
    return false;
    }
  const char* var = args[0].c_str();
  const char* targetName = args[1].c_str();

  cmTarget *tgt = m_Makefile->GetLocalGenerator()->GetGlobalGenerator()
    ->FindTarget(0,targetName);
  if (tgt)
    {
    cmTarget& target = *tgt;
    const char *prop = target.GetProperty(args[2].c_str());
    if (prop)
      {
      m_Makefile->AddDefinition(var, prop);
      return true;
      }
    }
  m_Makefile->AddDefinition(var, "NOTFOUND");
  return true;
}

